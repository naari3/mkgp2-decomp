/*
 * 0x80143F8C..0x80144258: clCSPartsResultStage, the cup/stage banner on the
 * result screen. Model resources are picked per cup from two [cup][2]
 * tables (by mode and by the long-round flag).
 */
#pragma cplusplus on

#define CSPARTS_INLINE_DTOR
#include "game/CSParts.h"

extern "C" {
extern int g_longRoundFlag;
extern int g_roundIndex;
}

static const unsigned int lbl_80361970[33] = {
    0x00000001, 0x00000025, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000002,
    0x0000000F, 0x442A8000, 0x41F00000, 0x3F19999A, 0x3F19999A, 0x00000000,
    0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000004, 0x00000000,
    0x43D20000, 0x41F00000, 0x3F19999A, 0x3F19999A, 0x00000000, 0x3F800000,
    0x3F800000, 0x3F800000, 0x3F800000,
};

static const unsigned int lbl_803619F4[33] = {
    0x00000001, 0x00000028, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000002,
    0x0000000F, 0x44354000, 0x41F00000, 0x3F19999A, 0x3F19999A, 0x00000000,
    0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000004, 0x00000000,
    0x43E78000, 0x41F00000, 0x3F19999A, 0x3F19999A, 0x00000000, 0x3F800000,
    0x3F800000, 0x3F800000, 0x3F800000,
};

static const unsigned int lbl_80361A78[33] = {
    0x00000001, 0x0000002B, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000002,
    0x0000000F, 0x443C8000, 0x41E00000, 0x3F800000, 0x3F800000, 0x00000000,
    0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000004, 0x00000000,
    0x440BC000, 0x41E00000, 0x3F800000, 0x3F800000, 0x00000000, 0x3F800000,
    0x3F800000, 0x3F800000, 0x3F800000,
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
        Add(new clCSModel(0x15F4, 0, 0, lbl_80361970, 0));
    }
}

clCSPartsResultStage::~clCSPartsResultStage() {
    if (model) {
        delete model;
    }
    model = 0;
}
