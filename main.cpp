#include "menu/menu_done.hpp"
#include "menu/menu_loading.hpp"
#include "menu/menu_miiverse_confirm.hpp"
#include "menu/menu.hpp"
#include "rpx_patches/rpx_backup_strategy.hpp"
#include "rpx_patches/rpx_backup.hpp"
#include "rpx_patches/rpx_hashes.hpp"
#include "rpx_patches/rpx_patch.hpp"
#include "util/log.h"
#include "util/copy_file.hpp"
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

static constexpr int task_percent(int task) { return (task*100)/7; };

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
    std::filesystem::path wave_patched_path = miiverse_path/"code/wave.rpx.patched";

    std::filesystem::path pn_olv_path = miiverse_path/"code/pn_olv.rpl";
    std::filesystem::path nn_olv_path = "iosu:/vol/system_slc/title/00050010/1000400a/code/nn_olv.rpl";
    std::filesystem::path pn_olv_patched_path = miiverse_path/"code/pn_olv.rpl.patched";

    std::error_code fserr;

    BackupState wave_state = GetBackupStrategy(wave_path, wave_bak_path);
    if (!wave_state.strategy) {
        //couldn't come up with a way to continue
        printf("Could not find a suitable backup strategy!\n");
        while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_NO_BACKUP); PresentMenu(); }
        return -1;
    }
    BackupStrategy wave_strategy = *wave_state.strategy;

    //we can be a bit less careful with nn_olv, since we always have the stock file on hand
    //if the stock file is bad, the patcher should catch it
    BackupStrategy olv_strategy = {
        .need_confirmation = false,
        .backup_action = B_DO_NOTHING,
        .patch_action = P_PATCH_FROM_BACKUP,
    };

    bool proc = true;
    while ((proc = WHBProcIsRunning())) {
        VPADStatus vpad;
        VPADReadError error;
        VPADRead(VPAD_CHAN_0, &vpad, 1, &error);
        if (error == VPAD_READ_SUCCESS) {
            if (vpad.trigger & VPAD_BUTTON_A) break;
        }
        RenderMenuMiiverseConfirm(wave_state);
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

    bret = backup_rpx(wave_strategy.backup_action, wave_path, wave_bak_path);
    if (!bret) {
        printf("Failed to backup wave!\n");
        wave_strategy.patch_action = P_DO_NOTHING;
        while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_BACKUP_FAIL); PresentMenu(); }
        return -1;
    }

    bret = backup_rpx(olv_strategy.backup_action, pn_olv_path, nn_olv_path);
    if (!bret) {
        printf("Failed to backup olv!\n");
        olv_strategy.patch_action = P_DO_NOTHING;
        while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_BACKUP_FAIL); PresentMenu(); }
        return -1;
    }

    RenderMenuLoading(task_percent(4), "Applying Miiverse patches...");
    PresentMenu();

    bret = patch_rpx(wave_strategy.patch_action, wave_path, wave_bak_path, wave_patched_path, "resin:/patches/wave.d.v113.p1.bps");
    if (!bret) {
        printf("Failed to patch wave!\n");
        while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_PATCH_FAIL); PresentMenu(); }
        return -1;
    }

    //DANGER: getting argument order wrong here could cause brickable writes to OSv10!
    bret = patch_rpx(olv_strategy.patch_action, pn_olv_path, nn_olv_path, pn_olv_patched_path, "resin:/patches/nn_olv.d.v15072.p1.bps");
    if (!bret) {
        printf("Failed to patch olv!\n");
        while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_PATCH_FAIL); PresentMenu(); }
        return -1;
    }

    RenderMenuLoading(task_percent(5), "Verifying patched files...");
    PresentMenu();

    {
        std::ifstream is(wave_patched_path, std::ios::binary);
        auto hash = rpx_hash(is);
        if (hash.id != CURRENT_PRETENDO_WAVE) {
            printf("Patcher made a corrupt file!\n");
            while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_PATCH_BAD); PresentMenu(); }
            return -1;
        }
    }

    {
        std::ifstream is(pn_olv_patched_path, std::ios::binary);
        auto hash = rpx_hash(is);
        if (hash.id != CURRENT_PRETENDO_NN_OLV) {
            printf("Patcher made a corrupt file!\n");
            while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_PATCH_BAD); PresentMenu(); }
            return -1;
        }
    }

    //the point of no return
    RenderMenuLoading(task_percent(6), "Committing changes...");
    PresentMenu();

    bret = fast_copy_file(wave_patched_path, wave_path);
    if (!bret) {
        printf("Final file copy failed!\n");
        //the next step is verification. on the off chance the copy 100% failed
        //and the stock wave is still there, we could still quit gracefully, so
        //we don't hard-fail here.
    }

    bret = fast_copy_file(pn_olv_patched_path, pn_olv_path);
    if (!bret) {
        printf("Final olv file copy failed!\n");
    }

    RenderMenuLoading(task_percent(7), "Verifying final patches...");
    PresentMenu();

    {
        std::ifstream is(wave_path, std::ios::binary);
        auto hash = rpx_hash(is);
        if (hash.patch == RPX_PATCH_STATE_STOCK) {
            printf("Failed to commit patches - stock wave in place\n");
            while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_PATCH_FAIL); PresentMenu(); }
            return -1;
        } else if (hash.id != CURRENT_PRETENDO_WAVE) {
            printf("Failed to commit patches - wave corrupt!\n");
            while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_PATCH_FAIL_DANGEROUS); PresentMenu(); }
            return -1;
        }
    }

    {
        std::ifstream is(pn_olv_path, std::ios::binary);
        auto hash = rpx_hash(is);
        if (hash.id != CURRENT_PRETENDO_NN_OLV) {
            //we've already modified wave, so this is always dangerous
            printf("Failed to commit patches - pn_olv corrupt!\n");
            while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_PATCH_FAIL_DANGEROUS); PresentMenu(); }
            return -1;
        }
    }

    //todo: flush volume on supported CFWs

    //woo!
    while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_NO_ERROR); PresentMenu(); }

    return 0;
}
