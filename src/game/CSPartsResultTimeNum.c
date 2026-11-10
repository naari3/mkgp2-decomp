/*
 * 0x80144258..0x80144430: clCSPartsResultTimeNum, a two-model digit part on
 * the result screen built from one resource id.
 */
#pragma cplusplus on

#define CSPARTS_INLINE_DTOR
#include "game/CSParts.h"

static const unsigned int CSPartsResultTimeNum_rodata_80361C48[11] = {
    0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000,
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct CSPartsResultTimeNum_rodata_80361C74_Row {
    int i_00;
    int i_04;
    int i_08;
    int i_0C;
    float f_10;
    float f_14;
    float f_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} CSPartsResultTimeNum_rodata_80361C74_Row;
static const CSPartsResultTimeNum_rodata_80361C74_Row CSPartsResultTimeNum_rodata_80361C74[4] = {
    { 0, 0, 0, 0, 0.0f, 0.0f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 20, 0, 0, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 20, 0, 0, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.8f },
    { 3, 0, 0, 0, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f }
};

struct clCSPartsResultTimeNum : clCSParts {
    clCSPartsResultTimeNum(int res);
    virtual ~clCSPartsResultTimeNum();
};

clCSPartsResultTimeNum::clCSPartsResultTimeNum(int res) {
    PreloadResource(res);
    Add(new clCSModel(res, 0, 0, CSPartsResultTimeNum_rodata_80361C48, 0));
    Add(new clCSModel(res, 3, 0, CSPartsResultTimeNum_rodata_80361C74, 0));
}

clCSPartsResultTimeNum::~clCSPartsResultTimeNum() {
    if (model) {
        delete model;
    }
    model = 0;
}
