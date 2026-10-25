/*
 * 0x80144258..0x80144430: clCSPartsResultTimeNum, a two-model digit part on
 * the result screen built from one resource id.
 */
#pragma cplusplus on

#define CSPARTS_INLINE_DTOR
#include "game/CSParts.h"

static const unsigned int lbl_80361C48[11] = {
    0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000,
};

static const unsigned int lbl_80361C74[44] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xBFC90FDB, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F000000, 0x00000002,
    0x00000014, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x00000000,
    0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000002, 0x00000014,
    0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x00000000, 0x3F800000,
    0x3F800000, 0x3F800000, 0x3F4CCCCD, 0x00000003, 0x00000000, 0x00000000,
    0x00000000, 0x3F800000, 0x3F800000, 0x00000000, 0x3F800000, 0x3F800000,
    0x3F800000, 0x00000000,
};

struct clCSPartsResultTimeNum : clCSParts {
    clCSPartsResultTimeNum(int res);
    virtual ~clCSPartsResultTimeNum();
};

clCSPartsResultTimeNum::clCSPartsResultTimeNum(int res) {
    PreloadResource(res);
    Add(new clCSModel(res, 0, 0, lbl_80361C48, 0));
    Add(new clCSModel(res, 3, 0, lbl_80361C74, 0));
}

clCSPartsResultTimeNum::~clCSPartsResultTimeNum() {
    if (model) {
        delete model;
    }
    model = 0;
}
