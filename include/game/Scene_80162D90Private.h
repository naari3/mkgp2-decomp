#ifndef GAME_SCENE_80162D90_PRIVATE_H
#define GAME_SCENE_80162D90_PRIVATE_H

#include "game/DemoKartScene.h"

struct CreditPanel162 {
    int Tick();
    char pad0[0x84];
    int credits;
    unsigned char noCredits;
    unsigned char expired;
    unsigned char pad8a;
    unsigned char changed;
    unsigned char confirmed;
};
struct InputState162 { char pad0[0x14]; int state; };

extern "C" {
extern InputState162 *g_pInputState;
extern void *lbl_806D10A0;
extern unsigned char lbl_806D17F0;
int CreditMgr_GetCreditCount(int);
unsigned char CreditMgr_TryConfirmPlay(int);
void fn_80147574(void *, int);
unsigned char fn_80147530(void *);
void fn_80147470(void *, int);
int fn_80147468(void *);
void fn_801474FC(void *, int);
void SetRumbleMode(int, int, int);
void TitleStats_ResetRaceStagingState(void *);
void RankLog_OnRoundComplete(void *);
}

static inline InputState162 *InputState() { return g_pInputState == 0 ? 0 : g_pInputState; }
static inline void *TitleTracker() { return lbl_806D10A0 == 0 ? 0 : lbl_806D10A0; }

#endif
