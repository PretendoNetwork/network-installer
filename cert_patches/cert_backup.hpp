#pragma once

#include "cert_patches/cert_backup_strategy.hpp"

bool backup_cert(
    BackupAction action,
    const std::string& main_path,
    const std::string& backup_path
);
