#include "game/Sci2CardReceipt.h"

extern unsigned char card_rw_state_machine_short(void);
extern unsigned char lbl_806CF0D4;
extern unsigned char CardRegister_Session_Tick_bss_806D1250;
extern signed char g_playerData[];

/* 0x80092460: print the registration receipt after a card session.
 * NonMatching: receipt polling uses r30 where the target reuses r31. */
void CardRegister_Session_Tick(void)
{
    if (!ServiceLatch_CheckTriggered() || lbl_806D1228 == 1 ||
        lbl_806CF0DC < 0 || lbl_806D1229 == 0) {
        return;
    }
    if (lbl_806CF0DC == 0) {
        CardRegister_Session_Tick_bss_806D1250 = 1;
    }
    if (CardRegister_Session_Tick_bss_806D1250 == 1 && !card_rw_state_machine_short()) {
        return;
    }
    if (g_playerData[0x1D9] != 2) {
        return;
    }
    if (++lbl_806CF0DC == 5) {
        int saved = lbl_806D1214;
        int flag;

        flag = lbl_806CF0D4 != 1;
        Receipt_StartFlow(0, flag, 0);
        lbl_806D1214 = saved;
        CardRegister_Session_Tick_bss_806D1250 = 0;
    } else if (lbl_806CF0DC > 5) {
        if (Receipt_PollState() == 1) {
            if (lbl_806D1210 == 1) {
                lbl_806CF0E8 = 1;
            }
            lbl_806CF0DC = 0;
            lbl_806D1229 = 0;
        }
    }
}
