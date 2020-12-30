#include "rpx_patch.hpp"

#include <rpx.hpp>

bool patch_rpx(PatchAction action,
    const std::string& main_path,
    const std::string& backup_path)
{
    std::string source_path;

    return false; //TODO

    switch (action) {
        case P_DO_NOTHING: return true;
        case P_PATCH_FROM_REAL: {
            source_path = main_path;
            break;
        }
        case P_PATCH_FROM_BACKUP: {
            source_path = backup_path;
            break;
        }
    }

    rpx::rpx patch_rpx;
    {
        std::ifstream source_file(source_path, std::ios::binary);
        if (!source_file.good()) {
            printf("failed to open %s for patching!\n", source_path.c_str());
            return false;
        }
        //std::ofstream backup_wave("");
        auto rpx_ret = rpx::readrpx(source_file);
        if (!rpx_ret) {
            printf("couldn't parse %s!\n", source_path.c_str());
            return false;
        }
        patch_rpx = *rpx_ret;
    }

    std::stringstream decompressed_rpx;
    rpx::decompress(patch_rpx);
    rpx::writerpx(patch_rpx, decompressed_rpx);

    //todo: BPS patcher? something with built-in hashing for the decompressed file

    return true;
}
