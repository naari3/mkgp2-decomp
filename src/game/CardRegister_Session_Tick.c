#include "game/Sci2CardReceipt.h"

extern unsigned char card_rw_state_machine_short(void);
extern unsigned char lbl_806CF0D4;
extern unsigned char lbl_806D1250;
extern signed char g_playerData[];

static inline void Register_Tick(void)
{
    if (lbl_806D1229 == 0) {
        return;
    }
    if (lbl_806CF0DC == 0) {
        lbl_806D1250 = 1;
    }
    if (lbl_806D1250 == 1 && !card_rw_state_machine_short()) {
        return;
    }
    if (g_playerData[0x1D9] != 2) {
        return;
    }
    if (++lbl_806CF0DC == 5) {
        int saved = lbl_806D1214;

        Receipt_StartFlow(0, lbl_806CF0D4 != 1, 0);
        lbl_806D1214 = saved;
        lbl_806D1250 = 0;
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

/* 0x80092460: after a card session, print the registration receipt: wait
 * for the card job, start the print on the fifth tick and poll it after.
 *
 * NonMatching: the target tests lbl_806D1229 as `bne body; b end`, and the
 * receipt poll's card pointer gets r31 there (r30 here). */
void CardRegister_Session_Tick(void)
{
    if (ServiceLatch_CheckTriggered() && lbl_806D1228 != 1 && lbl_806CF0DC >= 0) {
        Register_Tick();
    }
}
