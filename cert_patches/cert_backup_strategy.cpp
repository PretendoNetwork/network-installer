#include "cert_patches/cert_backup_strategy.hpp"
#include "cert_patches/cert_hashes.hpp"

std::optional<BackupStrategy> GetCertBackupStrategy(
    std::filesystem::path main_path,
    std::filesystem::path backup_path
) {
    std::error_code fserr;

    std::ifstream main_file(main_path, std::ios::binary);

    printf("hashing %s...\n", main_path.c_str());
    auto main_state = cert_hash(main_file);
    printf("found cert: %s\n", cert_id_name(main_state.id));

    // fserr doesn't matter for ::exists, it's just here for the noexcept path
    if (std::filesystem::exists(backup_path, fserr)) {
        //we have a backup - open and hash
        std::ifstream backup_file(backup_path, std::ios::binary);
        auto backup_state = cert_hash(backup_file);
        printf("backup is: %s\n", cert_id_name(backup_state.id));

        if (backup_state.patch == CERT_PATCH_STATE_STOCK) {
            //backup is good
            if (backup_state.id == main_state.id) {
                //backup and real cert are identical
                //proceed as normal
                return (BackupStrategy) {
                    .backup_action = B_DO_NOTHING,
                };
            } else if (main_state.patch == CERT_PATCH_STATE_STOCK) {
                //backup and real cert are stock, but different versions
                //get confirmation, overwrite backup with real, proceed
                return (BackupStrategy) {
                    .backup_action = B_MAKE_BACKUP,
                };
            } else if (main_state.patch == CERT_PATCH_STATE_PRETENDO) {
                //real cert is pretendo - we are likely "updating"
                //get confirmation, load backup, patch, overwrite real
                //TODO confirmation may not be needed here
                return (BackupStrategy) {
                    .backup_action = B_DO_NOTHING,
                };
            } else if (main_state.patch == CERT_PATCH_STATE_UNKNOWN) {
                //real cert is bad
                //get confirmation, load backup, patch, overwrite real
                return (BackupStrategy) {
                    .backup_action = B_DO_NOTHING,
                };
            } else {
                printf("bug: impossible state 1\n"); //[should] be impossible
                return std::nullopt;
            }
        } else {
            //backup is bad
            if (main_state.patch == CERT_PATCH_STATE_STOCK) {
                //real cert is good
                //get confirmation, overwrite backup, proceed
                return (BackupStrategy) {
                    .backup_action = B_MAKE_BACKUP,
                };
            } else {
                //real cert is bad
                //error out
                printf("backup and real cert are both patched/corrupt!\n");
                return std::nullopt;
            }
        }
    } else {
        //no backup file
        if (main_state.patch == CERT_PATCH_STATE_STOCK) {
            //real cert is good
            //copy real->backup, proceed
            return (BackupStrategy) {
                .backup_action = B_MAKE_BACKUP,
            };
        } else {
            //real cert is bad
            //error out
            printf("real cert is patched/corrupt without a backup!\n");
            return std::nullopt;
        }
    }

    return std::nullopt;
}
