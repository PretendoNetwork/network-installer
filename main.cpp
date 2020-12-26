#include "log.h"

#include <cstdio>
#include <whb/log_console.h>

int main(int argc, char** argv) {
    LOGInit();
    WHBLogConsoleInit();

    

    WHBLogConsoleFree();
    LOGShutdown();
}
