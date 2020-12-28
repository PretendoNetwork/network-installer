#include "log.h"
#include "util.hpp"

#include <cstdio>
#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include <whb/log_console.h>
#include <whb/proc.h>
#include <coreinit/mcp.h>

#include <iosuhax.h>
#include <iosuhax_devoptab.h>
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

    auto mcp = MCP_Open();
    if (mcp < 0) {
        printf("couldn't open MCP: %d\n", mcp);
        return -1;
    }

    MCPTitleListType miiverse_title;
    uint32_t title_count;
    ret = MCP_TitleListByAppType(mcp, MCP_APP_TYPE_MIIVERSE, &title_count, &miiverse_title, sizeof(miiverse_title));
    if (ret != 0 || title_count != 1) {
        printf("failed to find Miiverse title!\n");
        return -1;
    }
    //std::filesystem::path is kinda cursed
    std::filesystem::path miiverse_path(std::string("iosu:") + miiverse_title.path);
    printf("miiverse: %s\n", miiverse_path.c_str());

    if (mcp >= 0) MCP_Close(mcp);

    //haxchi compat: don't use any MCP functions after this point

    ret = IOSUHAX_Open(NULL);
    if (ret < 0) {
        printf("couldn't open iosuhax!\n");
        return -1;
    }
    OnLeavingScope _ios_c([&] {
        IOSUHAX_Close();
    });

    int fsa_fd = IOSUHAX_FSA_Open();
    if (fsa_fd < 0) {
        printf("couldn't open fsa!\n");
        return -1;
    }
    OnLeavingScope _fsa_c([&] {
        if (fsa_fd >= 0) IOSUHAX_FSA_Close(fsa_fd);
    });

    ret = mount_fs("iosu", fsa_fd, NULL, "/");
    //I know this is a bit odd
    printf("mount ret: %d\n", ret);
    OnLeavingScope _mnt_c([&] {
        unmount_fs("iosu");
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
