#include "rpx_patches/rpx_backup_strategy.hpp"
#include "rpx_patches/rpx_hashes.hpp"
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

#include <rpx.hpp>

// /vol/system_slc/title/00050010/1000400a/code

int main(int argc, char** argv) {
    int ret;

    LOGInit();
    //WHBLogConsoleInit();
    WHBProcInit();
    OnLeavingScope _log_c([&] {
        WHBProcShutdown();
        //WHBLogConsoleFree();
        LOGShutdown();
    });

    printf("Pretendo Network Installer indev\n");

    std::filesystem::path miiverse_path;
    /* Haxchi requires MCP functions to be kept somewhat isolated, so we get
     * them all out of the way early before we set up iosuhax. */
    {
        auto mcp = MCP_Open();
        if (mcp < 0) {
            printf("couldn't open MCP: %d\n", mcp);
            return -1;
        }
        OnLeavingScope _mcp_c([&] {
            MCP_Close(mcp);
            mcp = -1;
        });

        miiverse_path = GetTitlePath(mcp, MCP_APP_TYPE_MIIVERSE);
        if (miiverse_path.empty()) {
            printf("couldn't find Miiverse title!\n");
            return -1;
        }
        printf("miiverse found at %s\n", miiverse_path.c_str());
    }
    /* No more MCP functions from here on out. OK to set up iosuhax. */

    ret = iosu_fs_setup();
    if (ret < 0) {
        printf("failed to set up iosuhax!\n");
        return -1;
    }
    OnLeavingScope _ios_c([&] {
        iosu_fs_stop();
    });

    //goal: get a state together; ready to show a menu or something
    //https://marcan.st/2011/01/safe-hacking/

    std::filesystem::path wave_path = miiverse_path/"code/wave.rpx";
    std::filesystem::path wave_bak_path = miiverse_path/"code/wave.rpx.orig";

    BackupState backup = GetBackupStrategy(wave_path, wave_bak_path);
    if (!backup.strategy) {
        //couldn't come up with a way to continue
        //TODO a nice gui
        printf("Could not find a suitable backup strategy!\n");
        return -1;
    }
    BackupStrategy strategy = *backup.strategy;

    //temp things to test logic before a GUI is put together
    //imagine this is a render loop or something
    if (strategy.need_confirmation) {
        printf("confirmation!\n");
    }

    const std::map<BackupAction, std::string> backup_action_descriptions = {
        { B_DO_NOTHING, "do nothing" },
        //todo: change to "overwrite" if a backup exists
        { B_MAKE_BACKUP, "create a backup of the miiverse applet" },
        { B_RESTORE_BACKUP, "restore a backup of the miiverse applet" },
    };
    const std::map<PatchAction, std::string> patch_action_descriptions = {
        { P_DO_NOTHING, "do nothing" },
        { P_PATCH_FROM_REAL, "install juxt patches" },
        { P_PATCH_FROM_BACKUP, "install juxt patches, using a backup of the miiverse applet" },
    };

    if (strategy.backup_action != B_DO_NOTHING && strategy.patch_action != P_DO_NOTHING) {
        printf("Installer will %s then %s.\n", backup_action_descriptions.at(strategy.backup_action).c_str(), patch_action_descriptions.at(strategy.patch_action).c_str());
    } else if (strategy.backup_action != B_DO_NOTHING) {
        printf("Installer will %s.\n", backup_action_descriptions.at(strategy.backup_action).c_str());
    } else if (strategy.patch_action != P_DO_NOTHING) {
        printf("Installer will %s.\n", patch_action_descriptions.at(strategy.patch_action).c_str());
    } else {
        printf("bug: impossible state 2\n");
    }

    /*rpx::rpx wave_rpx;
    {
        std::ifstream original_wave(wave_path, std::ios::binary);
        //std::ofstream backup_wave("");
        auto rpx_ret = rpx::readrpx(original_wave);
        if (!rpx_ret) {
            printf("couldn't parse Miiverse rpx!\n");
            return -1;
        }
        wave_rpx = *rpx_ret;
    }

    std::stringstream decompressed_wave;
    rpx::decompress(wave_rpx);
    rpx::writerpx(wave_rpx, decompressed_wave);*/

    while (WHBProcIsRunning()) {}

    return 0;
}
