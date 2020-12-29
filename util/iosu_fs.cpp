#include "iosu_fs.hpp"

#include <cstdio>

#include <iosuhax.h>
#include <iosuhax_devoptab.h>

static int fsa_fd = -1;

int iosu_fs_setup() {
    int ret;

    //first, open IOSUHAX. todo: mcp hook
    ret = IOSUHAX_Open(NULL);
    if (ret < 0) {
        printf("couldn't open iosuhax!\n");
        return -1;
    }

    //open fsa handle
    int fsa_fd = IOSUHAX_FSA_Open();
    if (fsa_fd < 0) {
        printf("couldn't open fsa!\n");
        return -1;
    }

    //mount iosu path "/" onto "iosu:/"
    //I know it's a bit odd but it works!
    ret = mount_fs(IOSU_FS_DEVICE, fsa_fd, NULL, "/");
    if (ret < 0) {
        printf("couldn't mount iosu fs!\n");
        return -1;
    }

    return 0;
}

void iosu_fs_stop() {
    unmount_fs(IOSU_FS_DEVICE);
    if (fsa_fd >= 0) IOSUHAX_FSA_Close(fsa_fd);
    IOSUHAX_Close();
}
