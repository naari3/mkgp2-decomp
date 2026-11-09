#include "game/RankingMgrPrivate.h"
extern "C" {
static inline void *FindLast() {
    void *last = 0;
    int worst = 0;
    for (int i = 0; i < 4; ++i) {
        void *car = GetPlayerCarBySlot(i);
        if (car) {
            int rank = CarObject_GetRenderObj(car)->rank;
            if (worst < rank || last == 0) { worst = rank; last = car; }
        }
    }
    return last;
}
static inline void *FindFirst() {
    void *first = 0;
    int best = 8;
    for (int i = 0; i < 4; ++i) {
        void *car = GetPlayerCarBySlot(i);
        if (car) {
            int rank = CarObject_GetRenderObj(car)->rank;
            if (rank < best || first == 0) { best = rank; first = car; }
        }
    }
    return first;
}
/* fakematch (split lifetime ranges): the target keeps `box` and the
 * Read_U32 walker in r26, coloured in that order, and loads the walker
 * straight into its register. A named walker leaves `addi r0; mr r26,r0`
 * (named <- temp copies never coalesce), so both must be later lifetime
 * ranges of reused variables (SplitOffRange temps, regalloc_patterns 57, 72).
 * The dummy first ranges hold g_gameMode and IsRaceStarted(); propagation
 * is off so they are not folded away. Split temps are created per variable,
 * first declared first. Natural code: `RankingThinkBox *box = self->box;`
 * and a `for (i = 0; i < 8; ++i)` loop over Read_U32[i] with a Notify inline. */
#pragma push
#pragma opt_propagation off
void RankingMgr_UpdatePositions(RankingManager *self) {
    void **b;
    void **p;
    int i;
    void *ctrl;
    void *coll;
    b = (void **)g_gameMode;
    if ((int)b == 1) return;
    p = (void **)IsRaceStarted();
    if ((unsigned char)(int)p) {
        b = (void **)self->box;
        ((RankingThinkBox *)b)->lastCar = FindLast();
        ((RankingThinkBox *)b)->firstCar = FindFirst();
        self->box->Update();
        fn_801DC774();
    }
    p = Read_U32;
    for (i = 0; i < 8; i++, p++) {
        ctrl = *p;
        if (ctrl) {
            self->box->UpdateKart(i);
            if ((coll = lbl_806D1928) != 0) fn_80208FA0(coll, fn_801E6DDC(ctrl), 0);
        }
    }
}
#pragma pop
}
