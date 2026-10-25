#include "game/Sci2CardReceipt.h"

extern signed char g_playerData[];

/* 0x80091FD4: drive the receipt print job: start it on the first tick, then
 * poll the printer and emit receipt lines until the job is finished. */
void Sci2Card_PollAndAdvanceState(void)
{
    if (ServiceLatch_CheckTriggered() && lbl_806D1228 != 0) {
        if (++lbl_806CF0E0 == 1) {
            Receipt_StartFlow(1, 0, 0);
        } else if (lbl_806CF0E0 > 1) {
            if (Receipt_PollState() == 1) {
                if (lbl_806D1210 == 1) {
                    lbl_806CF0E8 = 2;
                }
                lbl_806CF0E0 = -1;
                lbl_806D1228 = 0;
                if (lbl_806D1214 != 5 && g_playerData[0x1D9] == 2) {
                    lbl_806CF0DC = 0;
                    lbl_806D1229 = 1;
                }
            }
        }
    }
}
