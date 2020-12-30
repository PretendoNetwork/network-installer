#include "rpx_patches/rpx_backup_strategy.hpp"

BackupState GetBackupStrategy(
    std::filesystem::path main_path,
    std::filesystem::path backup_path
) {
    BackupState result;
    std::error_code fserr;

    std::ifstream main_file(main_path, std::ios::binary);

    printf("hashing %s...\n", main_path.c_str());
    result.main_state = rpx_hash(main_file);
    printf("found rpx: %s\n", rpx_id_name(result.main_state.id));

    // fserr doesn't matter for ::exists, it's just here for the noexcept path
    if (std::filesystem::exists(backup_path, fserr)) {
        //we have a backup - open and hash
        std::ifstream backup_file(backup_path, std::ios::binary);
        result.backup_state = rpx_hash(backup_file);
        printf("backup is: %s\n", rpx_id_name(result.backup_state.id));
        result.backup_exists = true;

        if (result.backup_state.patch == RPX_PATCH_STATE_STOCK) {
            //backup is good
            if (result.backup_state.id == result.main_state.id) {
                //backup and real wave are identical
                //proceed as normal
                result.strategy = {
                    .need_confirmation = false,
                    .backup_action = B_DO_NOTHING,
                    .patch_action = P_PATCH_FROM_REAL,
                };
            } else if (result.main_state.patch == RPX_PATCH_STATE_STOCK) {
                //backup and real wave are stock, but different versions
                //get confirmation, overwrite backup with real, proceed
                result.strategy = {
                    .need_confirmation = true,
                    .backup_action = B_MAKE_BACKUP,
                    .patch_action = P_PATCH_FROM_REAL,
                };
            } else if (result.main_state.patch == RPX_PATCH_STATE_PRETENDO) {
                //real wave is pretendo - we are likely "updating"
                //get confirmation, load backup, patch, overwrite real
                //TODO confirmation may not be needed here
                result.strategy = {
                    .need_confirmation = true,
                    .backup_action = B_DO_NOTHING,
                    .patch_action = P_PATCH_FROM_BACKUP,
                };
            } else if (result.main_state.patch == RPX_PATCH_STATE_UNKNOWN) {
                //real wave is bad
                //get confirmation, load backup, patch, overwrite real
                result.strategy = {
                    .need_confirmation = true,
                    .backup_action = B_DO_NOTHING,
                    .patch_action = P_PATCH_FROM_BACKUP,
                };
            } else {
                printf("bug: impossible state 1\n"); //[should] be impossible
                result.strategy = std::nullopt;
            }
        } else {
            //backup is bad
            if (result.main_state.patch == RPX_PATCH_STATE_STOCK) {
                //real wave is good
                //get confirmation, overwrite backup, proceed
                result.strategy = {
                    .need_confirmation = true,
                    .backup_action = B_MAKE_BACKUP,
                    .patch_action = P_PATCH_FROM_REAL,
                };
            } else {
                //real wave is bad
                //error out
                printf("backup and real wave are both patched/corrupt!\n");
                result.strategy = std::nullopt;
            }
        }
    } else {
        //no backup file
        if (result.main_state.patch == RPX_PATCH_STATE_STOCK) {
            //real wave is good
            //copy real->backup, proceed
            result.strategy = {
                .need_confirmation = false,
                .backup_action = B_MAKE_BACKUP,
                .patch_action = P_PATCH_FROM_REAL,
            };
        } else {
            //real wave is bad
            //error out
            printf("real wave is patched/corrupt without a backup!\n");
            result.strategy = std::nullopt;
        }
    }

    return result;
}
