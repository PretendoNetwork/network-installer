#include "cert_patches/cert_backup_strategy.hpp"
#include "cert_patches/cert_backup.hpp"
#include "cert_patches/cert_hashes.hpp"
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

#include "task.hpp"
#include "juxt.hpp"

#include <cstdio>
#include <array>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <thread>

#include <whb/log_console.h>
#include <whb/proc.h>
#include <coreinit/mcp.h>
#include <vpad/input.h>
#include <coreinit/time.h>
#include <coreinit/thread.h>
#include <proc_ui/procui.h>

#include <romfs-wiiu.h>

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

    RenderMenuLoading(0, "Finding Miiverse title...");
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

    RenderMenuLoading(0, "Checking CFW...");
    PresentMenu();

    ret = iosu_fs_setup();
    if (ret < 0) {
        printf("failed to set up iosuhax!\n");
        while (WHBProcIsRunning()) { RenderMenuDone(MENU_DONE_NO_CFW); PresentMenu(); }
        return -1;
    }
    OnLeavingScope _ios_c([&] {
        iosu_fs_stop();
    });

    bool proc_running = true;
    //otherwise we can continue
    Task::State state;
    {
        Task juxt_task;
        std::thread juxt_thread(JuxtPermaPatch, std::ref(juxt_task), miiverse_path);
        OnLeavingScope _thr_c([&] {
            printf("task done, waiting\n");
            juxt_thread.join();
        });

        int last_percent;
        std::string last_message;

        while (1) {
            state = juxt_task.GetState();

            //terrible confirmation menu sub-loop thing
            if (state.confirmation_menu) {
                auto menu_type = *state.confirmation_menu;

                while ((proc_running = WHBProcIsRunning())) {
                    VPADStatus vpad;
                    VPADReadError error;
                    VPADRead(VPAD_CHAN_0, &vpad, 1, &error);
                    if (error == VPAD_READ_SUCCESS) {
                        if (vpad.trigger & VPAD_BUTTON_A) break;
                    }
                    if (menu_type == CONFIRMATION_MENU_MIIVERSE) {
                        RenderMenuMiiverseConfirm(state.miiverse_backup_state);
                        PresentMenu();
                    }
                }

                //if proc = false, user hit home button, we should not continue
                //if proc = true, user hit A, we can continue
                juxt_task.ConfirmationMenuDone(proc_running);
                if (!proc_running) break;
                continue;
            }

            //actual in-progress task rendering
            if (state.done) break;
            if (state.error != MENU_DONE_NO_ERROR) {
                //todo actually use this message
                printf("backend err: %s\n", state.message.c_str());
                break;
            }

            if (last_percent != state.percent || last_message != state.message) {
                RenderMenuLoading(state.percent, state.message.c_str());
                PresentMenu();
                last_percent = state.percent;
                last_message = state.message;
            }

            //temp
            OSSleepTicks(OSMillisecondsToTicks(16*2));
        }
    }

    //woo!
    if (proc_running) {
        while (WHBProcIsRunning()) { RenderMenuDone(state.error); PresentMenu(); }
    }

    return 0;
}
