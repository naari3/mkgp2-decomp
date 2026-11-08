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
static inline void Notify(void *ctrl) {
    void *coll = lbl_806D1928;
    if (coll) fn_80208FA0(coll, fn_801E6DDC(ctrl), 0);
}
static inline void UpdateKart(RankingManager *self, int i) {
    void *ctrl = Read_U32[i];
    if (ctrl) {
        self->box->UpdateKart(i);
        Notify(ctrl);
    }
}
static inline void UpdateAll(RankingManager *self) {
    for (int i = 0; i < 8; ++i) UpdateKart(self, i);
}
void RankingMgr_UpdatePositions(RankingManager *self) {
    if (g_gameMode == 1) return;
    if (IsRaceStarted()) {
        RankingThinkBox *box = self->box;
        box->lastCar = FindLast();
        box->firstCar = FindFirst();
        self->box->Update();
        fn_801DC774();
    }
    UpdateAll(self);
}
}
