#include "menu/menu_miiverse_confirm.hpp"
#include "menu/menu.hpp"

#include "rpx_patches/rpx_hashes.hpp"

void RenderMenuMiiverseConfirm(const BackupState& state) {
    if (!state.strategy) {
        printf("menu_miiverse_confirm: wtf?\n");
        return;
    }
    auto& strategy = *state.strategy;
    RenderMenuBasic();

    std::string main_text("Applet: ");
    main_text += rpx_id_name(state.main_state.id);

    std::string back_text("Backup: ");
    if (state.backup_exists) {
        back_text += rpx_id_name(state.backup_state.id);
    } else {
        back_text += "None";
    }

    std::string action_text("Installer will ");
    if (strategy.backup_action == B_MAKE_BACKUP) {
        if (state.backup_exists) {
            action_text += "overwrite your backup ";
        } else {
            action_text += "create a backup ";
        }
    } else if (strategy.backup_action == B_RESTORE_BACKUP) {
        action_text += "restore your backup ";
    }

    if (strategy.backup_action != B_DO_NOTHING && strategy.patch_action != P_DO_NOTHING) {
        action_text += "then ";
    }

    if (strategy.patch_action == P_PATCH_FROM_REAL) {
        action_text += "apply Juxtaposition patches.";
    } else if (strategy.patch_action == P_PATCH_FROM_BACKUP) {
        action_text += "apply Juxtaposition patches, from a backup.";
    }

    OSScreenPutFontEx(SCREEN_TV, 0, 18, "Please review the state of the installed Miiverse applet:");
    OSScreenPutFontEx(SCREEN_TV, 0, 19, main_text.c_str());
    OSScreenPutFontEx(SCREEN_TV, 0, 20, back_text.c_str());
    OSScreenPutFontEx(SCREEN_TV, 0, 22, action_text.c_str());
    if (strategy.need_confirmation) {
        OSScreenPutFontEx(SCREEN_TV, 0, 23, "This is an unexpected configuration. You could lose data or patches.");
    }

    OSScreenPutFontEx(SCREEN_TV, 0, 26, "HOME: Cancel");
    OSScreenPutFontEx(SCREEN_TV, 80, 26, "A: Apply Patches");

    OSScreenPutFontEx(SCREEN_DRC, 0,  9, "Please review the state of the installed Miiverse applet:");
    OSScreenPutFontEx(SCREEN_DRC, 0, 10, main_text.c_str());
    OSScreenPutFontEx(SCREEN_DRC, 0, 11, back_text.c_str());
    //the bare minimum text wrapping
    if (action_text.length() > 62) {
        std::string first_line = action_text.substr(0, 62);
        std::string second_line = action_text.substr(62);
        if (first_line.back() != ' ' && second_line.front() != ' ') {
            first_line.push_back('-');
        } else if (second_line.front() == ' ') {
            second_line.erase(0, 1);
        }
        OSScreenPutFontEx(SCREEN_DRC, 0, 13, first_line.c_str());
        OSScreenPutFontEx(SCREEN_DRC, 0, 14, second_line.c_str());
    } else {
        OSScreenPutFontEx(SCREEN_DRC, 0, 13, action_text.c_str());
    }

    if (strategy.need_confirmation) {
        OSScreenPutFontEx(SCREEN_DRC, 0, 15, "This is an unexpected setup. You could lose data or patches.");
    }

    OSScreenPutFontEx(SCREEN_DRC, 0, 17, "HOME: Cancel");
    OSScreenPutFontEx(SCREEN_DRC, 46, 17, "A: Apply Patches");
}
