/* Logging support bits */
/* TODO: don't use devoptab for this, lest the Wrath of Mute come upon us */

#include <unistd.h>
#include <sys/iosupport.h>
#include <whb/log.h>
#include <whb/log_udp.h>
#include <whb/log_cafe.h>
static ssize_t wiiu_log_write(struct _reent* r, void* fd, const char* ptr, size_t len) {
    WHBLogPrintf("%*.*s", len, len, ptr);
    return len;
}
static const devoptab_t dotab_stdout = {
    .name = "stdout_whb",
    .write_r = wiiu_log_write,
};

void LOGInit() {
    WHBLogUdpInit();
    WHBLogCafeInit();
    devoptab_list[STD_OUT] = &dotab_stdout;
    devoptab_list[STD_ERR] = &dotab_stdout;
}

void LOGShutdown() {
    WHBLogUdpDeinit();
}
