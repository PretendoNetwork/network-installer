#include "menu/menu_loading.hpp"
#include "menu/menu.hpp"

#include <cstdio>

#include <coreinit/screen.h>

void RenderMenuLoading(uint8_t progress, const char* message) {
    RenderMenuBasic();

    printf("STATE(%d%%): %s\n", progress, message);

    OSScreenPutFontEx(SCREEN_TV, 0, 20, message);
    OSScreenPutFontEx(SCREEN_DRC, 0, 12, message);

    uint32_t* tv_pixels = GetMenuBuf(SCREEN_TV);
    for (int y = 720-(MENU_BASE_UNIT_TV*4); y < 720-(MENU_BASE_UNIT_TV*3); y++) {
        for (int x = MENU_BASE_UNIT_TV; x < 1280-(MENU_BASE_UNIT_TV*2); x++) {
            auto p = ((x-MENU_BASE_UNIT_TV)*100)/(1280-(MENU_BASE_UNIT_TV*2));
            tv_pixels[x + y*1280] = (p < progress) ?
                menu_colour_palette.text_colour :
                menu_colour_palette.text_secondary_colour;
        }
    }

    uint32_t* drc_pixels = GetMenuBuf(SCREEN_DRC);
    for (int y = 480-(MENU_BASE_UNIT_DRC*4); y < 480-(MENU_BASE_UNIT_DRC*3); y++) {
        for (int x = MENU_BASE_UNIT_DRC; x < 854-(MENU_BASE_UNIT_DRC*2); x++) {
            auto p = ((x-MENU_BASE_UNIT_DRC)*100)/(854-(MENU_BASE_UNIT_DRC*2));
            drc_pixels[x + y*896] = (p < progress) ?
                menu_colour_palette.text_colour :
                menu_colour_palette.text_secondary_colour;
        }
    }
}
