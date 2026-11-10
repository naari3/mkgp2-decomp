#pragma inline_max_size(10000)
#include "game/CardLoadShadowMatchPrivate.h"
extern "C" {
extern unsigned char lbl_806D1228, lbl_806D122A, g_cardCmdResult, lbl_806D1227;
extern unsigned int g_cardSaveStartTick;
extern int lbl_806D1210, lbl_806CF0E4, lbl_806D1220, g_cardRwSubState;
unsigned int OSGetTick(void);
unsigned char ServiceLatch_CheckTriggered(void);
unsigned char card_rw_state_machine(void);

unsigned char CardSavedata_LoadShadow_TriggerUnused(void)
{
    /* Restore the saved fields, including both unlock flag arrays. */
    struct ShadowPlayerSnapshot *source = &lbl_80598A60.player;
    g_playerData = *source;
    if (lbl_806D1228 != 1) {
        g_cardSaveStartTick = OSGetTick();
        lbl_806D1210 = 0;
        lbl_806D122A = 1;
        g_cardCmdResult = 0;
        lbl_806CF0E4 = 5;
        if (!ServiceLatch_CheckTriggered()) {
            lbl_806D1210 = 1;
        } else {
            lbl_806D1227 = 0;
            lbl_806D1220 = 0;
            g_cardRwSubState = 0;
            card_rw_state_machine();
        }
    }
    return 1;
}
}
