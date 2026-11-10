#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * 0x8014388C..0x80143F8C: clCSParts (the model-chain result part, its
 * forwarding virtuals and dtor) and clCSPartsResultRank, the rank badge on
 * the result screen. fn_80143DB0 preloads the resources the badge can use.
 * Built with deferred inlining, so functions are emitted in reverse order.
 */
C_REGION_END
#pragma cplusplus on

#include "game/CSParts.h"

extern "C" {
extern unsigned char *RankSlot_GetByIndex(int i);
extern int fn_8013BF70(int cup, int mode);
extern void fn_8013B4FC(clCSModel *m, int n);
extern void fn_8013B300(clCSModel *m, int n);
extern void fn_8013AE20(clCSModel *m, float x, float y, float a);
extern void fn_8013AB74(clCSModel *m, int obj, int n);
}

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct CSPartsResultRank_rodata_80360C70_Row {
    int i_00;
    int i_04;
    float f_08;
    float f_0C;
    float f_10;
    float f_14;
    float f_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} CSPartsResultRank_rodata_80360C70_Row;
static const CSPartsResultRank_rodata_80360C70_Row CSPartsResultRank_rodata_80360C70[6] = {
    { 1, 60, 0.0f, 0.0f, 0.0f, 0.0f, 1.5707964f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 2, 15, 320.0f, -111.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 2, 2, 320.0f, 110.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 2, 13, 320.0f, 126.0f, 1.25f, 0.65f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f },
    { 2, 15, 320.0f, 107.0f, 0.98f, 1.09f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f },
    { 4, 0, 320.0f, 110.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80360D78_Row {
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
} lbl_80360D78_Row;
static const lbl_80360D78_Row lbl_80360D78[3] = {
    { 1, 37, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 15, 320.0f, 130.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 4, 0, 320.0f, 130.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 1.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80360DFC_Row {
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
} lbl_80360DFC_Row;
static const lbl_80360DFC_Row lbl_80360DFC[4] = {
    { 1, 37, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 15, 320.0f, 130.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 15, 320.0f, 130.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 1.0f },
    { 5, 0, 320.0f, 130.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80360EAC_Row {
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
} lbl_80360EAC_Row;
static const lbl_80360EAC_Row lbl_80360EAC[3] = {
    { 1, 37, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 15, 320.0f, 211.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 4, 0, 320.0f, 211.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 1.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80360F30_Row {
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
} lbl_80360F30_Row;
static const lbl_80360F30_Row lbl_80360F30[4] = {
    { 1, 37, 0.0f, 0.0f, 0.0f, 0.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 15, 320.0f, 211.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 15, 320.0f, 211.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 1.0f },
    { 5, 0, 320.0f, 211.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80360FE0_Row {
    int i_00;
    int i_04;
    float f_08;
    float f_0C;
    float f_10;
    float f_14;
    float f_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} lbl_80360FE0_Row;
static const lbl_80360FE0_Row lbl_80360FE0[6] = {
    { 1, 25, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 12, 320.0f, 110.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 4, 320.0f, 117.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 2, 6, 320.0f, 120.0f, 1.05f, 0.81f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 2, 5, 320.0f, 108.0f, 0.92f, 1.03f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 4, 0, 320.0f, 110.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_803610E8_Row {
    int i_00;
    int i_04;
    float f_08;
    float f_0C;
    float f_10;
    float f_14;
    float f_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} lbl_803610E8_Row;
static const lbl_803610E8_Row lbl_803610E8[6] = {
    { 1, 25, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 12, 320.0f, 110.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 4, 320.0f, 117.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 2, 6, 320.0f, 120.0f, 1.05f, 0.81f, 0.0f, 1.0f, 1.0f, 1.0f, 0.73f },
    { 2, 5, 320.0f, 108.0f, 0.92f, 1.03f, 0.0f, 1.0f, 1.0f, 1.0f, 0.33f },
    { 5, 0, 320.0f, 110.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_803611F0_Row {
    int i_00;
    int i_04;
    float f_08;
    float f_0C;
    float f_10;
    float f_14;
    float f_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} lbl_803611F0_Row;
static const lbl_803611F0_Row lbl_803611F0[3] = {
    { 1, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 13, 320.0f, 110.0f, 0.5f, 0.5f, -1.5707964f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 5, 0, 320.0f, 110.0f, 2.5f, 2.5f, -0.17453292f, 1.0f, 1.0f, 1.0f, 0.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80361274_Row {
    int i_00;
    int i_04;
    float f_08;
    float f_0C;
    float f_10;
    float f_14;
    float f_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} lbl_80361274_Row;
static const lbl_80361274_Row lbl_80361274[9] = {
    { 1, 45, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 258.0f, 156.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 5, 258.0f, 156.0f, 1.0f, 1.0f, -0.5235988f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 2, 15, 258.0f, 156.0f, 1.125f, 1.125f, 0.0f, 1.0f, 1.0f, 1.0f, 0.75f },
    { 1, 10, 258.0f, 156.0f, 1.5f, 1.5f, 1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 368.0f, 166.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 5, 368.0f, 166.0f, 1.0f, 1.0f, -0.5235988f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 2, 15, 368.0f, 166.0f, 1.125f, 1.125f, 0.0f, 1.0f, 1.0f, 1.0f, 0.75f },
    { 5, 0, 368.0f, 166.0f, 1.5f, 1.5f, 1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80361400_Row {
    int i_00;
    int i_04;
    float f_08;
    float f_0C;
    float f_10;
    float f_14;
    float f_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} lbl_80361400_Row;
static const lbl_80361400_Row lbl_80361400[19] = {
    { 1, 55, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 438.0f, 96.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 5, 438.0f, 96.0f, 1.0f, 1.0f, -0.5235988f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 2, 15, 438.0f, 96.0f, 1.125f, 1.125f, 0.0f, 1.0f, 1.0f, 1.0f, 0.75f },
    { 1, 30, 438.0f, 96.0f, 1.5f, 1.5f, 1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 10, 328.0f, 116.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 30, 328.0f, 116.0f, 1.0f, 1.0f, -0.5235988f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 1, 20, 328.0f, 116.0f, 2.0f, 2.0f, 1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 338.0f, 166.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 10, 338.0f, 166.0f, 1.0f, 1.0f, -0.5235988f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 1, 13, 338.0f, 166.0f, 2.0f, 2.0f, 1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 278.0f, 96.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 10, 278.0f, 96.0f, 1.0f, 1.0f, -0.5235988f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 1, 3, 278.0f, 96.0f, 2.0f, 2.0f, 1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 368.0f, 166.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 10, 368.0f, 166.0f, 1.0f, 1.0f, -0.5235988f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 1, 4, 368.0f, 166.0f, 2.0f, 2.0f, 1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 3, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80361744_Row {
    int i_00;
    int i_04;
    float f_08;
    float f_0C;
    float f_10;
    float f_14;
    float f_18;
    float f_1C;
    float f_20;
    float f_24;
    float f_28;
} lbl_80361744_Row;
static const lbl_80361744_Row lbl_80361744[11] = {
    { 1, 65, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 258.0f, 146.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 5, 258.0f, 146.0f, 1.0f, 1.0f, -0.5235988f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 2, 15, 258.0f, 146.0f, 1.125f, 1.125f, 0.0f, 1.0f, 1.0f, 1.0f, 0.75f },
    { 1, 20, 258.0f, 146.0f, 1.5f, 1.5f, 1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 1, 15, 258.0f, 146.0f, 1.5f, 1.5f, 1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 288.0f, 176.0f, 0.3f, 0.3f, -1.5707964f, 1.0f, 1.0f, 1.0f, 0.5f },
    { 2, 30, 288.0f, 176.0f, 1.0f, 1.0f, -0.5235988f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 1, 20, 288.0f, 176.0f, 2.0f, 2.0f, 1.5707964f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 3, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }
};

static const int CSPartsResultRank_rodata_80361928[5] = {0x1E94, 0x1E96, 0x1E98, 0x1E9A, 0x1E9C};

struct clCSPartsResultRank : clCSParts {
    int slot;
    int cup;
    int mode;

    clCSPartsResultRank();
    virtual ~clCSPartsResultRank();
};

clCSParts::~clCSParts() {
    if (model) {
        delete model;
    }
}

void clCSParts::Draw() {
    fn_8013AB74(model, obj, -1);
}

void clCSParts::Update() {
    fn_8013AE20(model, x, y, alpha);
}

void clCSParts::m10() {
    fn_8013B300(model, -1);
}

void clCSParts::m0C() {
    fn_8013B4FC(model, -1);
}

extern "C" void fn_80143DB0(void) {
    int n;
    int cup;
    int mode;
    int i;

    mode = (unsigned)(-g_gameMode | g_gameMode) >> 31;
    cup = g_cupId;

    PreloadResource(0x1E91);
    PreloadResource(0x1E90);
    n = (g_gameMode == 2) ? 3 : 5;
    for (i = 0; i < n; i++) {
        PreloadResource(CSPartsResultRank_rodata_80361928[i]);
    }
    if (g_gameMode != 2) {
        PreloadResource(0x96A);
    }
    PreloadResource(fn_8013BF70(cup, mode));
}

clCSPartsResultRank::clCSPartsResultRank() {
    int i;

    cup = g_cupId;
    if (g_gameMode == 0) {
        mode = 0;
    } else {
        mode = 1;
    }
    slot = 5;
    for (i = 0; i < 6; i++) {
        if (*RankSlot_GetByIndex(i)) {
            slot = i;
            break;
        }
    }
    if (slot == 0) {
        PreloadResource(0x1E91);
        Add(new clCSModel(0x1E91, 0, 0, lbl_80360D78, 0));
        Add(new clCSModel(0x1E91, 3, 0, lbl_80360DFC, 0));
        if (fn_8013BF70(cup, mode) != -1) {
            PreloadResource(fn_8013BF70(cup, mode));
            Add(new clCSModel(fn_8013BF70(cup, mode), 0, 0, lbl_80360EAC, 0));
            Add(new clCSModel(fn_8013BF70(cup, mode), 3, 0, lbl_80360F30, 0));
        }
        PreloadResource(0x1E90);
        Add(new clCSModel(0x1E90, 0, 0, lbl_80360FE0, 0));
        Add(new clCSModel(0x1E90, 3, 0, lbl_803610E8, 0));
        Add(new clCSModel(0x1E90, 0, 1, lbl_803611F0, 0));
        if (g_gameMode != 2) {
            PreloadResource(0x96A);
            Add(new clCSModel(0x96A, 0, 1, lbl_80361274, 0));
            Add(new clCSModel(0x96A, 0, 1, lbl_80361400, 0));
            Add(new clCSModel(0x96A, 0, 1, lbl_80361744, 0));
        }
    } else {
        PreloadResource(CSPartsResultRank_rodata_80361928[slot - 1]);
        Add(new clCSModel(CSPartsResultRank_rodata_80361928[slot - 1], 0, 0, CSPartsResultRank_rodata_80360C70, 0));
    }
}

clCSPartsResultRank::~clCSPartsResultRank() {
    if (model) {
        delete model;
    }
    model = 0;
}
