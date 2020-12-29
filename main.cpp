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
    WHBLogConsoleInit();
    WHBProcInit();
    OnLeavingScope _log_c([&] {
        WHBProcShutdown();
        WHBLogConsoleFree();
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

    std::error_code fserr;

    std::ifstream wave_file(wave_path, std::ios::binary);

    printf("hashing %s...\n", wave_path.c_str());
    auto wave_state = rpx_hash(wave_file);
    printf("found rpx: %s\n", rpx_id_name(wave_state.id));

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

    bool need_confirmation = true;
    bool error = false;
    BackupAction backup_action = B_DO_NOTHING;
    PatchAction patch_action = P_DO_NOTHING;

    // fserr doesn't matter for ::exists, it's just here for the noexcept path
    if (std::filesystem::exists(wave_bak_path, fserr)) {
        //we have a backup - open and hash
        std::ifstream wave_bak_file(wave_bak_path, std::ios::binary);
        auto wave_bak_state = rpx_hash(wave_bak_file);
        printf("backup is: %s\n", rpx_id_name(wave_bak_state.id));

        if (wave_bak_state.patch == RPX_PATCH_STATE_STOCK) {
            //backup is good
            if (wave_bak_state.id == wave_state.id) {
                //backup and real wave are identical
                //proceed as normal
                need_confirmation = false;
                backup_action = B_DO_NOTHING;
                patch_action = P_PATCH_FROM_REAL;
            } else if (wave_state.patch == RPX_PATCH_STATE_STOCK) {
                //backup and real wave are stock, but different versions
                //get confirmation, overwrite backup with real, proceed
                need_confirmation = true;
                backup_action = B_MAKE_BACKUP;
                patch_action = P_PATCH_FROM_REAL;
            } else if (wave_state.patch == RPX_PATCH_STATE_PRETENDO) {
                //real wave is pretendo - we are likely "updating"
                //get confirmation, load backup, patch, overwrite real
                //TODO confirmation may not be needed here
                need_confirmation = true;
                backup_action = B_DO_NOTHING;
                patch_action = P_PATCH_FROM_BACKUP;
            } else if (wave_state.patch == RPX_PATCH_STATE_UNKNOWN) {
                //real wave is bad
                //get confirmation, load backup, patch, overwrite real
                need_confirmation = true;
                backup_action = B_DO_NOTHING;
                patch_action = P_PATCH_FROM_BACKUP;
            } else printf("bug: impossible state 1\n"); //[should] be impossible
        } else {
            //backup is bad
            if (wave_state.patch == RPX_PATCH_STATE_STOCK) {
                //real wave is good
                //get confirmation, overwrite backup, proceed
                need_confirmation = true;
                backup_action = B_MAKE_BACKUP;
                patch_action = P_PATCH_FROM_REAL;
            } else {
                //real wave is bad
                //error out
                printf("backup and real wave are both patched/corrupt!\n");
                error = true;
            }
        }
    } else {
        //no backup file
        if (wave_state.patch == RPX_PATCH_STATE_STOCK) {
            //real wave is good
            //copy real->backup, proceed
            need_confirmation = false;
            backup_action = B_MAKE_BACKUP;
            patch_action = P_PATCH_FROM_REAL;
        } else {
            //real wave is bad
            //error out
            printf("real wave is patched/corrupt without a backup!\n");
            error = true;
        }
    }

    if (error) return -1; //TODO

    //temp things to test logic before a GUI is put together
    //imagine this is a render loop or something
    if (need_confirmation) {
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

    if (backup_action != B_DO_NOTHING && patch_action != P_DO_NOTHING) {
        printf("Installer will %s then %s.\n", backup_action_descriptions.at(backup_action).c_str(), patch_action_descriptions.at(patch_action).c_str());
    } else if (backup_action != B_DO_NOTHING) {
        printf("Installer will %s.\n", backup_action_descriptions.at(backup_action).c_str());
    } else if (patch_action != P_DO_NOTHING) {
        printf("Installer will %s.\n", patch_action_descriptions.at(patch_action).c_str());
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

    //while (WHBProcIsRunning()) {}

    return 0;
}
