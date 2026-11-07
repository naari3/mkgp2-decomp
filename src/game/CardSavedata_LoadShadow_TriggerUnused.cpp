#pragma inline_max_size(10000)
#include "game/CardLoadShadowPrivate.h"
extern "C" {
extern unsigned char lbl_806D1228, lbl_806D122A, lbl_806D121C, lbl_806D1227;
extern unsigned int lbl_806D122C;
extern int lbl_806D1210, lbl_806CF0E4, lbl_806D1220, lbl_806CF0D8;
unsigned int OSGetTick(void);
unsigned char ServiceLatch_CheckTriggered(void);
unsigned char card_rw_state_machine(void);

unsigned char CardSavedata_LoadShadow_TriggerUnused(void)
{
    /* Restore the saved fields, including both unlock flag arrays. */
    g_playerData = lbl_80598A60.player;
    if (lbl_806D1228 != 1) {
        lbl_806D122C = OSGetTick();
        lbl_806D1210 = 0;
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806CF0E4 = 5;
        if (!ServiceLatch_CheckTriggered()) {
            lbl_806D1210 = 1;
        } else {
            lbl_806D1227 = 0;
            lbl_806D1220 = 0;
            lbl_806CF0D8 = 0;
            card_rw_state_machine();
        }
    }
    return 1;
}
}
