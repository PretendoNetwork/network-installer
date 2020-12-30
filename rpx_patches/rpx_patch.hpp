#pragma once

#include "rpx_patches/rpx_backup_strategy.hpp"
#include <string>

bool patch_rpx(
    PatchAction action,
    const std::string& main_path,
    const std::string& backup_path
);
