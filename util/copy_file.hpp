#pragma once

#include "util/util.hpp"

#include <filesystem>
#include <array>
#include <span>
#include <unistd.h>
#include <fcntl.h>

#define COPY_FILE_CHUNK_SZ (512*1024)

[[maybe_unused]] static bool fast_copy_file(const std::filesystem::path& srcpath, const std::filesystem::path& destpath) {
    //thanks Maschell
    size_t size;

    if (destpath.string().find("1000400a") != std::string::npos ||
        destpath.string().find("1000400A") != std::string::npos) {
        printf("CRITICAL BUG: tried to write to OSv10!\n");
        return false;
    }

    int source = open(srcpath.c_str(), O_RDONLY, 0);
    if (source < 0) return false;
    OnLeavingScope _src_c([&] {
        if (source >= 0) close(source);
        source = -1;
    });
    int dest = open(destpath.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (dest < 0) return false;
    OnLeavingScope _dst_c([&] {
        if (dest >= 0) close(dest);
        dest = -1;
    });

    char* buf = (char*)malloc(COPY_FILE_CHUNK_SZ);
    if (!buf) return false;
    OnLeavingScope _buf_c([&] {
        if (buf) free(buf);
        buf = NULL;
    });

    while ((size = read(source, buf, COPY_FILE_CHUNK_SZ)) > 0) {
        write(dest, buf, size);
    }

    if (size < 0) {
        printf("failed %d\n", size);
        return false;
    }

    return true;
}

[[maybe_unused]] static bool fast_write_file(const std::filesystem::path& destpath, std::span<uint8_t> data) {
    if (destpath.string().find("1000400a") != std::string::npos ||
        destpath.string().find("1000400A") != std::string::npos) {
        printf("CRITICAL BUG: tried to write to OSv10!\n");
        return false;
    }

    int dest = open(destpath.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (dest < 0) return false;
    OnLeavingScope _dst_c([&] {
        if (dest >= 0) close(dest);
        dest = -1;
    });

    size_t remaining = data.size();
    while (remaining > 0) {
        auto ret = write(dest, data.data() + (data.size() - remaining), remaining);
        if (ret < 0) {
            printf("failed write %d\n", ret);
            return false;
        }

        remaining -= ret;
    }

    return true;
}
