#include "game/FlowScene.h"
#include "game/TestMenuPage.h"
struct AttractInputPlayer : InputPlayer {
    virtual void v8();
    virtual unsigned int v9(int mask);
};
struct AttractJoinState {
    char pad00[6];
    signed char inputDelay;
    char pad07;
    float brightness, coins;
    int next;
};
extern "C" {
extern unsigned char lbl_806D117C;
extern int lbl_806D11A8, g_gameMode;
extern const float lbl_806DA200, lbl_806DA204;
void SetRumbleMode(int, int, int);
int CountPeersWithRole(int);
unsigned char CreditMgr_AcceptorIsAbsent();
unsigned char CreditMgr_TryConfirmPlay(int);
void PlayStats_IncSinglePlayJoin();
void PlayStats_BeginPlaySession();
void SetTimerModeEnabled(int);
void SetLocalPcbRole(int);
void SetSyncTarget(int);
int fn_801DA1C4(AttractJoinState *self) {
    if (self->next != -1) return self->next;
    AttractInputPlayer *player = (AttractInputPlayer *)InputMgr_GetPlayer(GetInputManager(), 0);
    if (player->Held(0x400)) SetRumbleMode(1, 1, 1);
    unsigned char pressed = 0;
    if (self->inputDelay != 0) self->inputDelay--;
    else if (GetInput()->held == 1) pressed = 1;
    if (lbl_806D117C == 0) {
        if (self->coins != (float)CreditMgr_GetCoinCount(0, -1)) pressed = 1;
    }
    if (self->brightness <= lbl_806DA200 || CountPeersWithRole(1) == 0) {
        self->next = 2;
    } else if (pressed) {
        unsigned char confirmed = 0;
        if (CreditMgr_AcceptorIsAbsent()) {
            confirmed = 1;
            PlayStats_IncSinglePlayJoin();
            PlayStats_BeginPlaySession();
        } else if (CreditMgr_TryConfirmPlay(0)) confirmed = 1;
        if (confirmed) {
            SetRumbleMode(0, 1, 1);
            if (self->brightness <= lbl_806DA204 || player->v9(0x400) != 0) {
                g_gameMode = 0;
                SetTimerModeEnabled(0);
                self->next = 9;
            } else {
                lbl_806D11A8 = 1;
                SetLocalPcbRole(1);
                self->next = 7;
            }
            SetSyncTarget(self->next);
        } else {
            if (self->coins != (float)CreditMgr_GetCoinCount(0, -1)) lbl_806D11A8 = 1;
        }
    } else {
        if (self->coins != (float)CreditMgr_GetCoinCount(0, -1)) lbl_806D11A8 = 1;
    }
    self->coins = (float)CreditMgr_GetCoinCount(0, -1);
    return self->next;
}
}
