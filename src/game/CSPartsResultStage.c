#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * 0x80143F8C..0x80144258: clCSPartsResultStage, the cup/stage banner on the
 * result screen. Model resources are picked per cup from two [cup][2]
 * tables (by mode and by the long-round flag).
 */
C_REGION_END
#pragma cplusplus on

#define CSPARTS_INLINE_DTOR
#include "game/CSParts.h"

extern "C" {
extern int g_longRoundFlag;
extern int g_roundIndex;
}

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct CSPartsResultStage_rodata_80361970_Row {
    int i_00;
    int i_04;
    float f_08;
    float f_0C;
    float f_10;
    float f_14;
    int i_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} CSPartsResultStage_rodata_80361970_Row;
static const CSPartsResultStage_rodata_80361970_Row CSPartsResultStage_rodata_80361970[3] = {
    { 1, 37, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 15, 682.0f, 30.0f, 0.6f, 0.6f, 0, 1.0f, 1.0f, 1.0f, 1.0f },
    { 4, 0, 420.0f, 30.0f, 0.6f, 0.6f, 0, 1.0f, 1.0f, 1.0f, 1.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_803619F4_Row {
    int i_00;
    int i_04;
    float f_08;
    float f_0C;
    float f_10;
    float f_14;
    int i_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} lbl_803619F4_Row;
static const lbl_803619F4_Row lbl_803619F4[3] = {
    { 1, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 15, 725.0f, 30.0f, 0.6f, 0.6f, 0, 1.0f, 1.0f, 1.0f, 1.0f },
    { 4, 0, 463.0f, 30.0f, 0.6f, 0.6f, 0, 1.0f, 1.0f, 1.0f, 1.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80361A78_Row {
    int i_00;
    int i_04;
    float f_08;
    float f_0C;
    float f_10;
    float f_14;
    int i_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} lbl_80361A78_Row;
static const lbl_80361A78_Row lbl_80361A78[3] = {
    { 1, 43, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 15, 754.0f, 28.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 1.0f },
    { 4, 0, 559.0f, 28.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 1.0f }
};

static const int lbl_80361AFC[17][2] = {
    {-1, -1},
    {0x16EE, 0x16EE},
    {0x16F0, 0x16F0},
    {0x1705, 0x1705},
    {0x1706, 0x1706},
    {0x1707, 0x1707},
    {0x1708, 0x1708},
    {0x16ED, 0x16ED},
    {0x16EF, 0x16EF},
    {0x16EE, 0x16EE},
    {0x16F0, 0x16F0},
    {0x1705, 0x1705},
    {0x1706, 0x1706},
    {0x1707, 0x1707},
    {0x1708, 0x1708},
    {0x16ED, 0x16ED},
    {0x16EF, 0x16EF},
};

static const int lbl_80361B84[17][2] = {
    {-1, -1},
    {0x1A7A, 0x1A7B},
    {0x1A7E, 0x1A7F},
    {0x1A80, 0x1A81},
    {0x1A82, 0x1A83},
    {0x1A84, 0x1A85},
    {0x1A86, 0x1A87},
    {0x1A78, 0x1A79},
    {0x1A7C, 0x1A7D},
    {0x1A7A, 0x1A7B},
    {0x1A7E, 0x1A7F},
    {0x1A80, 0x1A81},
    {0x1A82, 0x1A83},
    {0x1A84, 0x1A85},
    {0x1A86, 0x1A87},
    {0x1A78, 0x1A79},
    {0x1A7C, 0x1A7D},
};

struct clCSPartsResultStage : clCSParts {
    int mode;
    int cup;
    int longRound;

    clCSPartsResultStage();
    virtual ~clCSPartsResultStage();
};

clCSPartsResultStage::clCSPartsResultStage() {
    if (g_gameMode == 0) {
        mode = 0;
    } else {
        mode = 1;
    }
    cup = g_cupId;
    longRound = g_longRoundFlag;
    PreloadResource(lbl_80361AFC[cup][mode]);
    Add(new clCSModel(lbl_80361AFC[cup][mode], 0, 0, lbl_803619F4, 0));
    PreloadResource(lbl_80361B84[cup][longRound]);
    Add(new clCSModel(lbl_80361B84[cup][longRound], 0, 0, lbl_80361A78, 0));
    if (g_roundIndex >= 4 && g_gameMode == 0) {
        PreloadResource(0x15F4);
        Add(new clCSModel(0x15F4, 0, 0, CSPartsResultStage_rodata_80361970, 0));
    }
}

clCSPartsResultStage::~clCSPartsResultStage() {
    if (model) {
        delete model;
    }
    model = 0;
}
