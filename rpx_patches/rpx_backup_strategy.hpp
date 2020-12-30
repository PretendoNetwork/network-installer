#pragma once

#include "rpx_hashes.hpp"

#include <optional>
#include <filesystem>

enum BackupAction {
    B_DO_NOTHING,
    B_MAKE_BACKUP,
    B_RESTORE_BACKUP,
};
enum PatchAction {
    P_DO_NOTHING,
    P_PATCH_FROM_REAL,
    P_PATCH_FROM_BACKUP, //load from backup, save over real
};

typedef struct BackupStrategy {
    bool need_confirmation;
    BackupAction backup_action;
    PatchAction patch_action;
} BackupStrategy;

typedef struct BackupState {
    std::optional<BackupStrategy> strategy;
    RPX_State main_state;
    bool backup_exists = false;
    RPX_State backup_state;
} BackupState;

BackupState GetBackupStrategy(
    std::filesystem::path main_file,
    std::filesystem::path backup_file
);
