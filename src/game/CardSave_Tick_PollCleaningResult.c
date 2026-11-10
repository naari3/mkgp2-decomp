#include "game/Sci2CardReceipt.h"

extern unsigned char Sci2Card_SendCmdCleaning(void *card);
extern void Sci2Card_ResetRetryCount(void *card);
extern void Backup_PublishShadowCopy_Inline(void);
extern int lbl_806CF0D0;
extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D1225;
extern unsigned char g_cardReceiptTestFlag;
extern unsigned char lbl_806D1248;
extern unsigned char lbl_80598A60[];

static inline void Cleaning_MarkFailed(void)
{
    g_cardReceiptTestFlag = 1;
    lbl_80598A60[0x270] = 1;
    Backup_PublishShadowCopy_Inline();
}

#pragma exceptions on
int CardSave_Tick_PollCleaningResult(void)
{
    void *card;
    unsigned char status3;
    unsigned char status2;
    unsigned char status1;

    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }
    card = Sci2Card_Singleton_Get();
    if (lbl_806D1210 != 0) {
        return 1;
    }
    if (g_cardCmdResult == 0) {
        g_cardCmdResult = Sci2Card_SendCmdCleaning(card);
        return 0;
    }
    if (!Sci2Card_IsIdleOrExhausted(card)) {
        return 0;
    }
    Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &status1, &status2, &status3);
    if (!Sci2Card_IsStatusOkNonTerm(card)) {
        if (lbl_806D1248 == 0) {
            Sci2Card_SetFailCode();
            if (lbl_806D1210 == 2) {
                Cleaning_MarkFailed();
            }
        } else {
            if (Sci2Card_IsStatus3Five(card) == 1) {
                Cleaning_MarkFailed();
            }
            Sci2Card_ResetRetryCount(card);
            lbl_806D122A = 0;
            lbl_806D1210 = 1;
            lbl_806D122B = 0;
        }
        lbl_806CF0D0 = 5;
        return 1;
    }
    if (Sci2Card_IsStatus3Zero(card) == 1) {
        lbl_806D122A = 0;
        lbl_806D1210 = 1;
        lbl_806D122B = 0;
        if (lbl_806D1248 == 1) {
            return 1;
        }
        lbl_806D1224 = 1;
        lbl_806D1214 = lbl_806D1225 == 1 ? 4 : 1;
        lbl_806D1225 = 0;
        g_cardCmdResult = Sci2Card_SendCmdCleaning(card);
        lbl_806D1248 = 1;
        lbl_806D1210 = 0;
        if (ServiceLatch_CheckTriggered()) {
            lbl_806D1229 = 1;
        }
        lbl_806CF0DC = 0;
    }
    return 0;
}
#pragma exceptions reset
