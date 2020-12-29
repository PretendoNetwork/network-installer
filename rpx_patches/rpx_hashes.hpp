#pragma once

#include <fstream>

enum RPX_ID {
    RPX_ID_UNKNOWN,

    //stock
    RPX_ID_WAVE_STOCK_v113,

    //pretendo patches
    RPX_ID_WAVE_PRETENDO_v113p1,
};
const char* rpx_id_name(RPX_ID id);

enum RPX_PatchState {
    RPX_PATCH_STATE_UNKNOWN,
    RPX_PATCH_STATE_STOCK,
    RPX_PATCH_STATE_PRETENDO,
};

typedef struct RPX_State {
    RPX_ID id;
    RPX_PatchState patch;
} RPX_State;

RPX_State rpx_hash(std::ifstream& is);
