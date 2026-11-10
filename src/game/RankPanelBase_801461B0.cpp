/*
 * 0x801461B0..0x8014640C: ranking panel base dtor and ctor.
 *
 * fn_80146260 is the constructor of a clCSParts-derived result panel
 * (vtable clCSPartsResultPanel_vtable_8048EF98): the inlined clCSPartsInerface / clCSParts ctors,
 * then four clCSModel children built from this TU's .rodata parameter
 * blocks (0x80361ED0..0x803625E4). Mangled names are bridged to the
 * binary's symbols via tools/extab_user_renames.json; the inline
 * clCSPartsInerface dtor is emitted as a weak copy (dtor_8013EB50).
 */
#pragma cplusplus on

#include "game/types/InputPlayer.h"
#include "game/types/VObjC.h"
#include "game/types/Countdown.h"
#include "game/types/SelSlot.h"
#include "game/types/LapSel.h"
#include "game/types/TripleObj.h"

/* TOP-END */

extern "C" {
void MemoryManager_TimedFree(void *p);
void fn_8013B87C(void *p, int flag);
extern void *lbl_8048EB44[];
extern void *clCSParts_vtable_8048EE48[];
extern void *clCSPartsResultPanel_vtable_8048EF98[];
TripleObj *fn_801461B0(TripleObj *self, short flag);
}

#include "game/CSParts.h"

extern "C" TripleObj *fn_801461B0(TripleObj *self, short flag)
{
    if (self) {
        self->vt14 = clCSPartsResultPanel_vtable_8048EF98;
        if (self->p18) {
            fn_8013B87C(self->p18, 1);
        }
        self->p18 = 0;
        if (self) {
            self->vt14 = clCSParts_vtable_8048EE48;
            if (self->p18) {
                fn_8013B87C(self->p18, 1);
            }
            if (self) {
                self->vt14 = lbl_8048EB44;
            }
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

/* element type read off the values (all floats), not from code */
static const float RankPanelBase_801461B0_rodata_80361ED0[255] = {
    1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f,
    0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f,
    83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f,
    83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_803622CC_Row {
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
} lbl_803622CC_Row;
static const lbl_803622CC_Row lbl_803622CC[4] = {
    { 2, 10, 314.0f, 300.0f, 0.8f, 0.8f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 330.0f, 300.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 1.0f },
    { 1, 30, 346.0f, 300.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.3f },
    { 5, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_8036237C_Row {
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
} lbl_8036237C_Row;
static const lbl_8036237C_Row lbl_8036237C[5] = {
    { 1, 10, 0.0f, 0.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 314.0f, 300.0f, 0.8f, 0.8f, 0, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 330.0f, 300.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 1.0f },
    { 1, 20, 346.0f, 300.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.3f },
    { 5, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 0.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80362458_Row {
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
} lbl_80362458_Row;
static const lbl_80362458_Row lbl_80362458[4] = {
    { 2, 10, 326.0f, 300.0f, 0.8f, 0.8f, 3.1415927f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 310.0f, 300.0f, 1.0f, 1.0f, 3.1415927f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 1, 30, 294.0f, 300.0f, 1.0f, 1.0f, 3.1415927f, 1.0f, 1.0f, 1.0f, 0.3f },
    { 5, 0, 0.0f, 0.0f, 1.0f, 1.0f, 3.1415927f, 1.0f, 1.0f, 1.0f, 0.0f }
};

/* row layout read off the values (per column: all floats, all small integers, one byte, or
 * two 16-bit values), not from code */
typedef struct lbl_80362508_Row {
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
} lbl_80362508_Row;
static const lbl_80362508_Row lbl_80362508[5] = {
    { 1, 10, 0.0f, 0.0f, 1.0f, 1.0f, 3.1415927f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 326.0f, 300.0f, 0.8f, 0.8f, 3.1415927f, 1.0f, 1.0f, 1.0f, 0.0f },
    { 2, 10, 310.0f, 300.0f, 1.0f, 1.0f, 3.1415927f, 1.0f, 1.0f, 1.0f, 1.0f },
    { 1, 20, 294.0f, 300.0f, 1.0f, 1.0f, 3.1415927f, 1.0f, 1.0f, 1.0f, 0.3f },
    { 5, 0, 0.0f, 0.0f, 1.0f, 1.0f, 3.1415927f, 1.0f, 1.0f, 1.0f, 0.0f }
};
struct clCSPartsResultPanel : clCSParts {
    clCSPartsResultPanel();
    virtual ~clCSPartsResultPanel();
};

clCSPartsResultPanel::clCSPartsResultPanel() {
    PreloadResource(0x8CD);
    Add(new clCSModel(0x8CD, 0, 0, lbl_803622CC, 1));
    Add(new clCSModel(0x8CD, 0, 0, lbl_8036237C, 1));
    Add(new clCSModel(0x8CD, 0, 0, lbl_80362458, 0));
    Add(new clCSModel(0x8CD, 0, 0, lbl_80362508, 0));
}
