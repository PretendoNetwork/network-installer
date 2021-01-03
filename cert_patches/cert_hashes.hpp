#pragma once

#include <fstream>

enum Cert_ID {
    CERT_ID_UNKNOWN,

    //stock
    CERT_ID_THWATE_PREMIUM_SERVER,

    //pretendo replacements
    CERT_ID_ISRG_ROOT_X1,
    CERT_ID_DST_ROOT_X3,
};
const char* cert_id_name(Cert_ID id);

#define CURRENT_PRETENDO_CERT CERT_ID_DST_ROOT_X3
#define CURRENT_SACRIFICIAL_CERT CERT_ID_THWATE_PREMIUM_SERVER

enum Cert_PatchState {
    CERT_PATCH_STATE_UNKNOWN,
    CERT_PATCH_STATE_STOCK,
    CERT_PATCH_STATE_PRETENDO,
};

typedef struct Cert_State {
    Cert_ID id;
    Cert_PatchState patch;
} Cert_State;

Cert_State cert_hash(std::ifstream& is);
