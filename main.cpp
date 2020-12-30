#include "menu/menu_done.hpp"
#include "menu/menu_loading.hpp"
#include "menu/menu_miiverse_confirm.hpp"
#include "menu/menu.hpp"
#include "rpx_patches/rpx_backup_strategy.hpp"
#include "rpx_patches/rpx_backup.hpp"
#include "rpx_patches/rpx_hashes.hpp"
#include "rpx_patches/rpx_patch.hpp"
#include "util/log.h"
#include "util/util.hpp"
#include "util/titles.hpp"
#include "util/iosu_fs.hpp"

#include <cstdio>
#include <array>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include <whb/log_console.h>
#include <whb/proc.h>
#include <coreinit/mcp.h>
#include <vpad/input.h>

#include <romfs-wiiu.h>

static constexpr int task_percent(int task) { return (task*100)/4; };

int main(int argc, char** argv) {
    int ret;
    bool bret;

    LOGInit();
    ramfsInit();
    //WHBLogConsoleInit();
    WHBProcInit();
    OnLeavingScope _log_c([&] {
        WHBProcShutdown();
        //WHBLogConsoleFree();
        ramfsExit();
        LOGShutdown();
    });

    bret = InitMenu();
    if (!bret) {
        printf("failed to set up menu!\n");
        return -1;
    }
    OnLeavingScope _mnu_c([&] { QuitMenu(); });

    printf("Pretendo Network Installer indev\n");

    RenderMenuLoading(task_percent(0), "Finding Miiverse title...");
    PresentMenu();

    std::filesystem::path miiverse_path;
    /* Haxchi requires MCP functions to be kept somewhat isolated, so we get
     * them all out of the way early before we set up iosuhax. */
    {
        auto mcp = MCP_Open();
        if (mcp < 0) {
            printf("couldn't open MCP: %d\n", mcp);
            while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_MCP_FAIL); PresentMenu(); }
            return -1;
        }
        OnLeavingScope _mcp_c([&] {
            MCP_Close(mcp);
            mcp = -1;
        });

        miiverse_path = GetTitlePath(mcp, MCP_APP_TYPE_MIIVERSE);
        if (miiverse_path.empty()) {
            printf("couldn't find Miiverse title!\n");
            while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_NO_MIIVERSE); PresentMenu(); }
            return -1;
        }
        printf("miiverse found at %s\n", miiverse_path.c_str());
    }
    /* No more MCP functions from here on out. OK to set up iosuhax. */

    RenderMenuLoading(task_percent(1), "Checking CFW...");
    PresentMenu();

    ret = iosu_fs_setup();
    if (ret < 0) {
        printf("failed to set up iosuhax!\n");
        while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_CFW_FAIL); PresentMenu(); }
        return -1;
    }
    OnLeavingScope _ios_c([&] {
        iosu_fs_stop();
    });

    //goal: get a state together; ready to show a menu or something
    //https://marcan.st/2011/01/safe-hacking/

    RenderMenuLoading(task_percent(2), "Examining current Miiverse state...");
    PresentMenu();

    std::filesystem::path wave_path = miiverse_path/"code/wave.rpx";
    std::filesystem::path wave_bak_path = miiverse_path/"code/wave.rpx.orig";

    std::error_code fserr;

    BackupState backup = GetBackupStrategy(wave_path, wave_bak_path);
    if (!backup.strategy) {
        //couldn't come up with a way to continue
        printf("Could not find a suitable backup strategy!\n");
        while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_NO_BACKUP); PresentMenu(); }
        return -1;
    }
    BackupStrategy strategy = *backup.strategy;

    bool proc = true;
    while ((proc = WHBProcIsRunning())) {
        VPADStatus vpad;
        VPADReadError error;
        VPADRead(VPAD_CHAN_0, &vpad, 1, &error);
        if (error == VPAD_READ_SUCCESS) {
            if (vpad.trigger & VPAD_BUTTON_A) break;
        }
        RenderMenuMiiverseConfirm(backup);
        PresentMenu();
    }

    if (!proc) {
        //loop broke because user quit from menu overlay
        return 0;
    }
    //otherwise we can continue

    bool error = false;

    RenderMenuLoading(task_percent(3), "Creating Miiverse backup...");
    PresentMenu();

    bret = backup_rpx(strategy.backup_action, wave_path, wave_bak_path);
    if (!bret) {
        printf("Failed to backup wave!\n");
        strategy.patch_action = P_DO_NOTHING;
        while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_BACKUP_FAIL); PresentMenu(); }
        return -1;
    }

    RenderMenuLoading(task_percent(4), "Applying Miiverse patches...");
    PresentMenu();

    bret = patch_rpx(strategy.patch_action, wave_path, wave_bak_path);
    if (!bret) {
        printf("Failed to patch wave!\n");
        while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_PATCH_FAIL_DANGEROUS); PresentMenu(); }
        return -1;
    }

    while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_NO_ERROR); PresentMenu(); }

    return 0;
}
