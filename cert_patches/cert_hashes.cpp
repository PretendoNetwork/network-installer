#include "cert_hashes.hpp"

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

const static std::map<sha256, Cert_State> cert_hashes = {
    {"ab7036365c7154aa29c2c29f5d4191163b162a2225011357d56d07ffa7bc1f72"_sha,{
        .id = CERT_ID_THWATE_PREMIUM_SERVER,
        .patch = CERT_PATCH_STATE_STOCK,
    }},
    {"96bcec06264976f37460779acf28c5a7cfe8a3c0aae11a8ffcee05c0bddf08c6"_sha, {
        .id = CERT_ID_ISRG_ROOT_X1,
        .patch = CERT_PATCH_STATE_PRETENDO,
    }},
    {"0687260331a72403d909f105e69bcf0d32e1bd2493ffc6d9206d11bcd6770739"_sha, {
        .id = CERT_ID_DST_ROOT_X3,
        .patch = CERT_PATCH_STATE_PRETENDO,
    }},
};

Cert_State cert_hash(std::ifstream& is) {
    sha256 hash;
    picosha2::hash256(is, hash.begin(), hash.end());
    printf("cert: ");
    for (auto c : hash) {
        printf("%02x", c);
    }
    printf("\n");

    if (cert_hashes.contains(hash)) {
        return cert_hashes.at(hash);
    }

    return (Cert_State) {
        .id = CERT_ID_UNKNOWN,
        .patch = CERT_PATCH_STATE_UNKNOWN,
    };
}

#define ENUM_NAME(e) case e: return #e
const char* cert_id_name(Cert_ID id) {
    switch (id) {
        ENUM_NAME(CERT_ID_UNKNOWN);
        ENUM_NAME(CERT_ID_THWATE_PREMIUM_SERVER);
        ENUM_NAME(CERT_ID_ISRG_ROOT_X1);
        ENUM_NAME(CERT_ID_DST_ROOT_X3);
    }
    return "bug: unknown";
}
