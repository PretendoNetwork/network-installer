#include "rpx_patch.hpp"

#include "util/copy_file.hpp"
#include "util/memory_streambuf.hpp"

#include <libbps.h>
#include <rpx.hpp>

//I'm not really sure I'm ever going to try using std::streams for anything.
//ever again.

bool patch_rpx(PatchAction action,
    const std::string& main_path,
    const std::string& backup_path,
    const std::string& output_path
)
{
    std::string source_path;

    //return false; //TODO

    switch (action) {
        case P_DO_NOTHING: return true;
        case P_PATCH_FROM_REAL: {
            source_path = main_path;
            break;
        }
        case P_PATCH_FROM_BACKUP: {
            source_path = backup_path;
            break;
        }
    }


    std::vector<char> patch;
    {
        //todo don't hardcode this. lookup via RPX_State?
        std::ifstream patch_file("resin:/patches/wave.d.v113.p1.bps", std::ios::binary | std::ios::ate);
        auto size = patch_file.tellg();
        if (size < 0) {
            printf("patch file didn't open!\n");
            return false;
        }
        patch_file.seekg(0, std::ios::beg);

        patch.resize(size);
        if (!patch_file.read(patch.data(), patch.size())) {
            printf("failed to read in patch file!\n");
            return false;
        }
    }

    rpx::rpx clean_rpx;
    {
        std::ifstream source_file(source_path, std::ios::binary);
        if (!source_file.good()) {
            printf("failed to open %s for patching!\n", source_path.c_str());
            return false;
        }
        //std::ofstream backup_wave("");
        auto rpx_ret = rpx::readrpx(source_file);
        if (!rpx_ret) {
            printf("couldn't parse %s!\n", source_path.c_str());
            return false;
        }
        clean_rpx = *rpx_ret;
    }

    rpx::decompress(clean_rpx);

    auto decompressed_sz = writerpxsize(clean_rpx);
    printf("decompressed sz: %x\n", decompressed_sz);

    std::vector<char> decompressed_rpx(decompressed_sz);
    {
        memory_streambuf sbuf(decompressed_rpx);
        std::ostream os(&sbuf);

        rpx::writerpx(clean_rpx, os);
        os.flush();
    }

    auto decompressed_rpx_mem = mem_make(decompressed_rpx);
    auto patch_mem = mem_make(patch);

    struct mem patched_decompressed_rpx_mem;

    bpserror err = bps_apply(patch_mem, decompressed_rpx_mem, &patched_decompressed_rpx_mem, nullptr, false);

    if (err != bps_ok) {
        printf("bps error %d\n", err);
        return false;
    }

    rpx::rpx patched_rpx;
    {
        memory_streambuf<char> patched_decompressed_rpx((char*)patched_decompressed_rpx_mem.ptr, patched_decompressed_rpx_mem.len);
        std::istream patched_decompressed_rpx_is(&patched_decompressed_rpx);

        auto rpx_ret = rpx::readrpx(patched_decompressed_rpx_is);
        if (!rpx_ret) {
            printf("couldn't parse patched rpx!\n");
            return false;
        }
        patched_rpx = *rpx_ret;
    }

    bps_free(patched_decompressed_rpx_mem);
    patched_decompressed_rpx_mem = (struct mem) { .ptr = nullptr };

    rpx::compress(patched_rpx);

    auto compressed_sz = writerpxsize(patched_rpx);
    printf("compressed sz: %x\n", compressed_sz);

    std::vector<char> compressed_rpx(compressed_sz);
    {
        //unfortunately writing to the file with ostream doesn't seem to work, so
        //another layer of indirection and another copy is needed
        memory_streambuf sbuf(compressed_rpx);
        std::ostream os(&sbuf);

        rpx::writerpx(patched_rpx, os);
        os.flush();
    }

    //write result
    fast_write_file(output_path, {(uint8_t*)compressed_rpx.data(), compressed_rpx.size()});

    return true;
}
