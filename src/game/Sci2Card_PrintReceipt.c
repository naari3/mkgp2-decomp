#include "game/Sci2CardReceipt.h"

/* 0x80094950: poll the receipt printer; returns 1 once the job is over. */
unsigned char Sci2Card_PrintReceipt_PollState(void)
{
    void *card;
    unsigned char status3;
    unsigned char status2;
    unsigned char status1;

    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }
    if (lbl_806D1210 != 0) {
        return 1;
    }
    card = Sci2Card_Singleton_Get();
    Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &status1, &status2, &status3);
    if (Sci2Card_IsIdleOrExhausted(card) == 1) {
        if (!Sci2Card_IsStatusOkNonTerm(card)) {
            Sci2Card_SetFailCode();
            return 1;
        }
        if (Sci2Card_IsStatus3Zero(card) == 1) {
            if (Receipt_Advance() == 1) {
                lbl_806D122A = 0;
                lbl_806D1210 = 1;
                lbl_806D122B = 0;
                return 1;
            }
        }
    }
    return 0;
}

/* 0x80094BCC: start a receipt print job of the given mode. */
unsigned char Sci2Card_PrintReceipt_StartFlow(int mode, unsigned char header, unsigned char retry)
{
    lbl_806D122B = retry;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806CF0E4 = 5;
        lbl_806D1210 = 1;
        return 1;
    }
    lbl_806CF0EC = mode;
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    lbl_806D1218 = 0;
    lbl_806D123C = 0;
    Sci2Card_Singleton_Get();
    if (lbl_806CF0EC == 0 || lbl_806CF0EC == 3) {
        if (header == 1) {
            Receipt_BuildLine(-3);
        } else {
            Receipt_BuildLine(0);
        }
    } else {
        lbl_806D1218 = lbl_806CF0EC == 2 ? 9 : 2;
        if (Receipt_Advance() == 1) {
            return 1;
        }
    }
    return 1;
}
