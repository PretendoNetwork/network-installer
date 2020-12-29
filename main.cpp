#include "util/log.h"
#include "util/util.hpp"
#include "util/titles.hpp"
#include "util/iosu_fs.hpp"

#include <cstdio>
#include <array>
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

    printf("hi!\n");

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

    bool need_wave_backup = true;

    std::filesystem::path wave_path = miiverse_path/"code/wave.rpx";
    std::filesystem::path wave_bak_path = miiverse_path/"code/wave.rpx.orig";

    std::error_code fserr;

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
