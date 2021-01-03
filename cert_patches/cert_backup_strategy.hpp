#pragma once

//borrow BackupStrategy from the rpx side
#include "rpx_patches/rpx_backup_strategy.hpp"

#include <optional>

std::optional<BackupStrategy> GetCertBackupStrategy(
    std::filesystem::path main_path,
    std::filesystem::path backup_path
);
