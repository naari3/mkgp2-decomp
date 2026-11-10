#ifndef GAME_RANKING_DISPLAY_BASE_PRIVATE_H
#define GAME_RANKING_DISPLAY_BASE_PRIVATE_H
#include "game/RankingDisplayDispatch_private.h"
#ifndef __MWERKS__ /* the name fn_801D1D9C.cpp uses; the build renames the static after compiling */
#define rankingDispatch RankingFlow_vtable_8049B51C
#endif
extern "C" { extern RankingDispatch rankingDispatch; }
extern "C" void InitializeFrameSelection(void *);
/* Explicit dispatch view of the shared scene base. */
struct RankingDisplayBase {
    RankingDispatch *dispatch;
    RankingDisplayBase() {
        InitializeFrameSelection(this);
        dispatch = &rankingDispatch;
    }
    ~RankingDisplayBase();
};
#endif
