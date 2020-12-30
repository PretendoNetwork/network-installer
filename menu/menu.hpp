#pragma once

#include <cstdint>
#include <coreinit/screen.h>

bool InitMenu();
void QuitMenu();

void RenderMenuBasic();
void PresentMenu();

uint32_t* GetMenuBuf(OSScreenID id);

static struct {
    int background_colour = 0x1b1f3bff;
    int text_colour = 0xffffffff;
    int dot_colour = 0x9d6ff3ff;
    int text_secondary_colour = 0xa1a8d9ff;
} menu_colour_palette;

#define MENU_BASE_UNIT_TV 39
#define MENU_BASE_UNIT_DRC 26
