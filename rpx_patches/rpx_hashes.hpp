#pragma once

#include <fstream>

enum RPX_ID {
    RPX_ID_UNKNOWN,

    //stock
    RPX_ID_WAVE_STOCK_v113,
    RPX_ID_NN_OLV_STOCK_v15702,

    //pretendo patches
    RPX_ID_WAVE_PRETENDO_v113p1,
    RPX_ID_NN_OLV_PRETENDO_v15072p1,
};
const char* rpx_id_name(RPX_ID id);

#define CURRENT_PRETENDO_WAVE RPX_ID_WAVE_PRETENDO_v113p1
#define CURRENT_PRETENDO_NN_OLV RPX_ID_NN_OLV_PRETENDO_v15072p1

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
