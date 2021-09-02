#include "rpx_hashes.hpp"

#include <map>
#include <string>
#include <array>
#include <cstdio>
#include <charconv>

#include <picosha2.h>

typedef std::array<uint8_t, picosha2::k_digest_size> sha256;

/* C++!
 * I actually cannot believe this is allowed as constexpr
 * converts a string to a "sha256" / byte array */
constexpr sha256 operator ""_sha(const char* s, size_t l) {
    sha256 out;
    uint8_t val;
    for (size_t i = 0; i < l; i += 2) {
        std::from_chars(&s[i], &s[i+2], val, 16);
        out[i/2] = val;
    }
    return out;
}

const static std::map<sha256, RPX_State> rpx_hashes = {
    {"61aebcc528b9dff0cda1eb99000fe95a217d2a5193deb0d0256aa77f1d2e84b1"_sha,{
        .id = RPX_ID_WAVE_STOCK_v113,
        .patch = RPX_PATCH_STATE_STOCK,
    }},
    {"f1b464e82de4d69eea44db136dfed12e93a105a93e6510ea6c71418b428cea31"_sha, {
        .id = RPX_ID_WAVE_PRETENDO_v113p1,
        .patch = RPX_PATCH_STATE_PRETENDO,
    }},
    {"aaea8cab3e48896737f679deaa898e701d6adeb2090a6d87d50ec8ea1b8c3854"_sha, {
        .id = RPX_ID_NN_OLV_STOCK_v15702,
        .patch = RPX_PATCH_STATE_STOCK,
    }},
    {"e6c912ce354723cefdad80ae692fd9b5ae5d193ef9ca634268340911a16c5f4a"_sha, {
        .id = RPX_ID_NN_OLV_PRETENDO_v15072p1,
        .patch = RPX_PATCH_STATE_PRETENDO,
    }},
};

RPX_State rpx_hash(std::ifstream& is) {
    sha256 hash;
    picosha2::hash256(is, hash.begin(), hash.end());
    printf("rpx: ");
    for (auto c : hash) {
        printf("%02x", c);
    }
    printf("\n");

    if (rpx_hashes.contains(hash)) {
        return rpx_hashes.at(hash);
    }

    return (RPX_State) {
        .id = RPX_ID_UNKNOWN,
        .patch = RPX_PATCH_STATE_UNKNOWN,
    };
}

#define ENUM_NAME(e) case e: return #e
const char* rpx_id_name(RPX_ID id) {
    switch (id) {
        ENUM_NAME(RPX_ID_UNKNOWN);
        ENUM_NAME(RPX_ID_WAVE_STOCK_v113);
        ENUM_NAME(RPX_ID_NN_OLV_STOCK_v15702);
        ENUM_NAME(RPX_ID_WAVE_PRETENDO_v113p1);
        ENUM_NAME(RPX_ID_NN_OLV_PRETENDO_v15072p1);
    }
    return "bug: unknown";
}