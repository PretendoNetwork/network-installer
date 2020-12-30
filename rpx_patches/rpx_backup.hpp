#pragma once

#include "rpx_patches/rpx_backup_strategy.hpp"

bool backup_rpx(
    BackupAction action,
    const std::string& main_path,
    const std::string& backup_path
);
