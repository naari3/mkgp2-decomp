extern unsigned char ServiceLatch_CheckTriggered(void);
extern void *Sci2Card_Singleton_Get(void);
extern unsigned char Sci2Card_SendCmdOptions(void *card, unsigned char read,
                                             unsigned char option);
extern unsigned char Sci2Card_ForceFailState(void *card);

extern int lbl_806CF0E4;
extern int lbl_806D1210;
extern int lbl_806D1214;
extern unsigned char lbl_806D121C;
extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D122A;
extern unsigned char lbl_806D1237;
extern unsigned char lbl_806D1238;

extern unsigned char Sci2Card_IsIdleOrExhausted(void *card);
extern unsigned char Sci2Card_IsStatusOk02(void *card);
extern unsigned char Sci2Card_IsStatusOkNonTerm(void *card);
extern unsigned char Sci2Card_IsStatus1OneTwoThree(void *card);
extern unsigned char lbl_806CF0D4;
extern unsigned char lbl_806D122B;

/* Restart has no active-cleaning guard. Its return marks initialization and
 * deliberately replaces the send result with pending at the caller. */
static inline unsigned char CardCleaning_Begin(void)
{
    void *card;

    lbl_806D1238 = 1;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806CF0E4 = 5;
        lbl_806D1224 = 0;
        lbl_806D1214 = 0;
        lbl_806D1210 = 1;
        return 1;
    }

    card = Sci2Card_Singleton_Get();
    if (lbl_806D1237 == 0) {
        lbl_806D1210 = 0;
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806D121C = Sci2Card_SendCmdOptions(card, 0, 1);
    } else {
        lbl_806D1210 = 0;
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806CF0E4 = 5;
        Sci2Card_ForceFailState(card);
    }
    return 1;
}

unsigned char card_cleaning_state_machine(void)
{
    void *card;

    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1224 = 0;
        lbl_806D1214 = 0;
        lbl_806D1210 = 1;
        lbl_806D1238 = 0;
        return 1;
    }
    if (lbl_806D1210 != 0) {
        return 1;
    }

    card = Sci2Card_Singleton_Get();
    if (lbl_806D121C == 0) {
        lbl_806D121C = CardCleaning_Begin();
        return 0;
    }

    if (Sci2Card_IsIdleOrExhausted(card) == 1) {
        if (Sci2Card_IsStatusOk02(card) == 1) {
            lbl_806D122A = 0;
            lbl_806D1210 = 6;
            lbl_806D122B = 0;
            if (--lbl_806CF0E4 <= 0) {
                lbl_806D1210 = 104;
            }
            lbl_806D1237 = 0;
        } else if (!Sci2Card_IsStatusOkNonTerm(card)) {
            lbl_806D122A = 0;
            lbl_806D1210 = 6;
            lbl_806D122B = 0;
            lbl_806D1237 = 0;
            if (--lbl_806CF0E4 <= 0) {
                lbl_806D1210 = 104;
            }
        } else if (Sci2Card_IsStatus1OneTwoThree(card) == 1) {
            lbl_806D1224 = 1;
            lbl_806D1237 = 0;
            lbl_806CF0D4 = 0;
            lbl_806D122A = 0;
            lbl_806D1210 = 1;
            lbl_806D122B = 0;
        } else {
            lbl_806D1237 = 1;
            lbl_806D122A = 0;
            lbl_806D1210 = 6;
            lbl_806D122B = 0;
        }
        lbl_806D1238 = 0;
        return 1;
    }
    return 0;
}

unsigned char card_send_cleaning_cmd_init(void)
{
    void *card;

    if (lbl_806D1238 == 1) {
        return 1;
    }
    lbl_806D1238 = 1;

    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806CF0E4 = 5;
        lbl_806D1224 = 0;
        lbl_806D1214 = 0;
        lbl_806D1210 = 1;
        return 1;
    }

    card = Sci2Card_Singleton_Get();
    if (lbl_806D1237 == 0) {
        lbl_806D1210 = 0;
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806D121C = Sci2Card_SendCmdOptions(card, 0, 1);
    } else {
        lbl_806D1210 = 0;
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806CF0E4 = 5;
        Sci2Card_ForceFailState(card);
    }
    return 1;
}
