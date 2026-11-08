#ifndef GAME_RANKING_DISPLAY_BASE_PRIVATE_H
#define GAME_RANKING_DISPLAY_BASE_PRIVATE_H
#include "game/RankingDisplayDispatch_private.h"
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
