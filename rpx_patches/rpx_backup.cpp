#include "rpx_patches/rpx_backup.hpp"
#include "util/copy_file.hpp"

#include <unistd.h>
#include <fcntl.h>

bool backup_rpx(
    BackupAction action,
    const std::string& main_path,
    const std::string& backup_path
) {
    bool bret;

    std::string source_path;
    std::string dest_path;

    switch (action) {
        case B_DO_NOTHING: return true;
        case B_MAKE_BACKUP: {
            source_path = main_path;
            dest_path = backup_path;
            break;
        }
        case B_RESTORE_BACKUP: {
            source_path = backup_path;
            dest_path = main_path;
            break;
        }
    }

    bret = fast_copy_file(source_path, dest_path);
    if (!bret) {
        printf("failed to copy backup!\nfrom: %s\nto: %s\n", source_path.c_str(), dest_path.c_str());
        return false;
    }
    //double-double check
    std::ifstream finished_file(dest_path, std::ios::binary);
    auto hash = rpx_hash(finished_file);
    if (hash.patch != RPX_PATCH_STATE_STOCK) {
        printf("made or restored a corrupt backup!\n");
        return false;
    }
    printf("file is now: %s\n", rpx_id_name(hash.id));

    return true;
}
