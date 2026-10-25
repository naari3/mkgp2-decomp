#include "game/Sci2CardReceipt.h"

extern void *CardPrintJob_GetFontPagePayload(int page);
extern unsigned char Sci2Card_SendCmdRetry(void *card, int arg);
extern unsigned char Sci2Card_SendCmdPrint(void *card, int page, void *payload);
extern unsigned int OSGetTick(void);

extern int lbl_806D1220;
extern int lbl_806D1240;
extern unsigned int lbl_806D1244;

/* 0x8009450C: send the receipt font to the printer one page at a time. */
unsigned char CardPrintJob_TickFontTransfer(void)
{
    void *card;
    void *payload;

    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }
    if (lbl_806D1210 != 0) {
        return 1;
    }
    card = Sci2Card_Singleton_Get();
    payload = CardPrintJob_GetFontPagePayload(lbl_806D1240);
    switch (lbl_806D1220) {
    case 0:
        Sci2Card_SendCmdRetry(card, 0);
        lbl_806D1220++;
        break;
    case 1:
        if (!Sci2Card_IsIdleOrExhausted(card)) {
            return 0;
        }
        if (Sci2Card_IsStatusOkNonTerm(card) == 1) {
            lbl_806D1220++;
            break;
        }
        Sci2Card_SetFailCode();
        return 1;
    case 2:
        if (payload == 0) {
            lbl_806D122A = 0;
            lbl_806D1210 = 1;
            lbl_806D122B = 0;
            return 1;
        }
        lbl_806D1244 = OSGetTick();
        Sci2Card_SendCmdPrint(card, lbl_806D1240 + 1, payload);
        lbl_806D1220++;
        break;
    case 3:
        if (Sci2Card_IsIdleOrExhausted(card) == 1) {
            if (!Sci2Card_IsStatusOkNonTerm(card)) {
                Sci2Card_SetFailCode();
                return 1;
            }
            if (Sci2Card_IsStatus3Zero(card) == 1) {
                lbl_806D1240++;
            }
            lbl_806D1220 = 2;
        }
        break;
    }
    return 0;
}
