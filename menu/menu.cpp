#include "menu/menu.hpp"

#include <coreinit/screen.h>
#include <coreinit/cache.h>
#include <proc_ui/procui.h>

#include <malloc.h>
#include <string.h>
#include <array>
#include <vector>

#include <zstr.hpp>

//OSScreen bits

static uint32_t* tv_buffer = nullptr;
static size_t tv_size;
static uint32_t* drc_buffer = nullptr;
static size_t drc_size;

static std::array<decltype(tv_buffer), 2> tv_pixel_buffers;
static std::array<decltype(drc_buffer), 2> drc_pixel_buffers;
static int cbuf = 1;

uint32_t* GetMenuBuf(OSScreenID id) {
    return (id == SCREEN_TV) ? tv_pixel_buffers.at(cbuf) : drc_pixel_buffers.at(cbuf);
}

static bool is_init = false;
static bool has_foreground = false;

//basic menu assets

// TV assets
static const int line1_720p_y = MENU_BASE_UNIT_TV*2;
static const int line2_720p_y = 720-line1_720p_y;

static std::vector<uint32_t> logo_720p;
static const int logo_720p_x = 320;
static const int logo_720p_y = line1_720p_y+(MENU_BASE_UNIT_TV);
static const int logo_720p_w = 640;
static const int logo_720p_h = 213;

//DRC assets
static const int line1_480p_y = MENU_BASE_UNIT_DRC*2;
static const int line2_480p_y = 480-line1_480p_y;

static std::vector<uint32_t> logo_480p;
static const int logo_480p_x = 213;
static const int logo_480p_y = line1_480p_y+(MENU_BASE_UNIT_DRC);
static const int logo_480p_w = 427;
static const int logo_480p_h = 142;

union pixel_t {
    uint32_t rgba;
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
};

//I forgot how much fun doing this by hand is
static constexpr uint8_t blend(uint8_t vA, uint8_t aA, uint8_t vB, uint8_t aB, uint8_t aO) {
    return (vA * aA + vB * aB * (255 - aA) / 255) / aO;
}
static void blit(uint32_t* target, uint32_t target_w, uint32_t* src, uint32_t src_w, uint32_t src_h, uint32_t dx, uint32_t dy) {
    for (unsigned int y = 0; y < src_h; y++) {
        for (unsigned int x = 0; x < src_w; x++) {
            pixel_t pixel;
            pixel.rgba = src[x + y*src_w];

            auto rx = x + dx;
            auto ry = y + dy;

            if (pixel.a == 0xff) {
                target[rx + ry*target_w] = pixel.rgba;
            } else if (pixel.a) {
                pixel_t old_pixel;
                old_pixel.rgba = target[rx + ry*target_w];
                pixel_t new_pixel;
                new_pixel.a = pixel.a + (old_pixel.a * (255 - pixel.a) / 255);
                new_pixel.r = blend(pixel.r, pixel.a, old_pixel.r, old_pixel.a, new_pixel.a);
                new_pixel.g = blend(pixel.g, pixel.a, old_pixel.g, old_pixel.a, new_pixel.a);
                new_pixel.b = blend(pixel.b, pixel.a, old_pixel.b, old_pixel.a, new_pixel.a);

                target[rx + ry*target_w] = new_pixel.rgba;
            }
        }
    }
}

void RenderMenuBasic() {
    OSScreenClearBufferEx(SCREEN_TV, menu_colour_palette.background_colour);

    //software rendering let's goo
    uint32_t* tv_pixels = GetMenuBuf(SCREEN_TV);
    for (int x = 0; x < 1280; x++) {
        tv_pixels[x + line1_720p_y*1280] = menu_colour_palette.text_colour;
    }
    blit(tv_pixels, 1280, logo_720p.data(), logo_720p_w, logo_720p_h, logo_720p_x, logo_720p_y);
    for (int x = 0; x < 1280; x++) {
        tv_pixels[x + line2_720p_y*1280] = menu_colour_palette.text_colour;
    }

    OSScreenClearBufferEx(SCREEN_DRC, menu_colour_palette.background_colour);
    uint32_t* drc_pixels = GetMenuBuf(SCREEN_DRC);
    for (int x = 0; x < 854; x++) {
        drc_pixels[x + line1_480p_y*896] = menu_colour_palette.text_colour;
    }
    blit(drc_pixels, 896, logo_480p.data(), logo_480p_w, logo_480p_h, logo_480p_x, logo_480p_y);
    for (int x = 0; x < 854; x++) {
        drc_pixels[x + line2_480p_y*896] = menu_colour_palette.text_colour;
    }
}

void PresentMenu() {
    DCFlushRange(tv_buffer, tv_size);
    DCFlushRange(drc_buffer, drc_size);
    OSScreenFlipBuffersEx(SCREEN_TV);
    OSScreenFlipBuffersEx(SCREEN_DRC);
    cbuf = !cbuf;
}

static unsigned int ProcCallbackAcquire(void* context) {
    tv_buffer = (decltype(tv_buffer))memalign(0x100, tv_size);
    drc_buffer = (decltype(drc_buffer))memalign(0x100, drc_size);

    if (!tv_buffer || !drc_buffer) {
        printf("fatal: out-of-memory while allocating screen buffers!\n");
        return 1;
    }

    tv_pixel_buffers = { tv_buffer, (uint32_t*)((uint32_t)tv_buffer + (tv_size / 2)) };
    drc_pixel_buffers = { drc_buffer, (uint32_t*)((uint32_t)drc_buffer + (drc_size / 2)) };

    OSScreenSetBufferEx(SCREEN_TV, tv_buffer);
    OSScreenSetBufferEx(SCREEN_DRC, drc_buffer);

    has_foreground = true;
    return 0;
}
static unsigned int ProcCallbackRelease(void* context) {
    if (tv_buffer) {
        free(tv_buffer);
        tv_buffer = nullptr;
        tv_pixel_buffers = { nullptr, nullptr };
    }
    if (drc_buffer) {
        free(drc_buffer);
        drc_buffer = nullptr;
        drc_pixel_buffers = { nullptr, nullptr };
    }

    has_foreground = false;
    return 0;
}

bool InitMenu() {
    OSScreenInit();

    tv_size = OSScreenGetBufferSizeEx(SCREEN_TV);
    drc_size = OSScreenGetBufferSizeEx(SCREEN_DRC);

    ProcCallbackAcquire(nullptr);
    if (!tv_buffer || !drc_buffer) {
        QuitMenu();
        return false;
    }

    ProcUIRegisterCallback(PROCUI_CALLBACK_ACQUIRE, ProcCallbackAcquire, NULL, 100);
    ProcUIRegisterCallback(PROCUI_CALLBACK_RELEASE, ProcCallbackRelease, NULL, 100);
    OSScreenEnableEx(SCREEN_TV, true);
    OSScreenEnableEx(SCREEN_DRC, true);

    //some nice, slow texture decompression
    zstr::ifstream logo_720p_is("resin:/logo_720p.data.gz", std::ios::binary);
    while (true) {
        uint32_t pixel;
        logo_720p_is.read((char*)&pixel, sizeof(pixel));
        auto cnt = logo_720p_is.gcount();
        if (cnt < 4) break;
        logo_720p.push_back(pixel);
    }
    zstr::ifstream logo_480p_is("resin:/logo_480p.data.gz", std::ios::binary);
    while (true) {
        uint32_t pixel;
        logo_480p_is.read((char*)&pixel, sizeof(pixel));
        auto cnt = logo_480p_is.gcount();
        if (cnt < 4) break;
        logo_480p.push_back(pixel);
    }

    is_init = true;
    return true;
}

void QuitMenu() {
    if (has_foreground) {
        OSScreenShutdown();
        ProcCallbackRelease(nullptr);
    }

    is_init = false;
}
