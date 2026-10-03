extern unsigned char ServiceLatch_CheckTriggered(void);
extern void *Sci2Card_Singleton_Get(void);
extern unsigned char Sci2Card_SendCmdPing(void *card);
extern unsigned char Sci2Card_IsIdleOrExhausted(void *card);
extern unsigned char Sci2Card_IsStatusOkNonTerm(void *card);
extern unsigned char Sci2Card_IsStatus3Five(void *card);
extern unsigned char Sci2Card_IsRetryExhausted(void *card);
extern unsigned char Sci2Card_IsStatus2Two(void *card);
extern unsigned char Sci2Card_IsStatus2One(void *card);
extern unsigned char Sci2Card_IsStatus2Three(void *card);
extern unsigned char Sci2Card_IsStatus2Five(void *card);
extern unsigned char Sci2Card_IsStatus2A(void *card);
extern unsigned char Sci2Card_GetResponseStatus(void *card,
                                              unsigned char *status1,
                                              unsigned char *status2,
                                              unsigned char *status3);

extern int lbl_806CF0E4;
extern int lbl_806D1210;
extern unsigned char lbl_806D121C;
extern int lbl_806D1220;
extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D122A;
extern unsigned char lbl_806D122B;
extern unsigned char lbl_806D1237;

/* Initialization completes even when the ping command is not accepted.
 * The caller replaces the command result with this return value. Keep the
 * helper inline to preserve the branch-local initialization-result joins.
 */
static inline unsigned char CardPing_Begin(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }

    if (lbl_806D1224 == 1) {
        return 1;
    }

    lbl_806D1220 = 0;
    lbl_806D121C = Sci2Card_SendCmdPing(Sci2Card_Singleton_Get());
    return 1;
}

unsigned char card_ping_state_machine(void)
{
    void *card;
    unsigned char completedStatus3;
    unsigned char completedStatus2;
    unsigned char completedStatus1;
    unsigned char activeStatus3;
    unsigned char activeStatus2;
    unsigned char activeStatus1;

    if (!ServiceLatch_CheckTriggered() || lbl_806D1224 == 1) {
        lbl_806D1210 = 1;
        lbl_806D1224 = 0;
        return 1;
    }
    if (lbl_806D1210 != 0) {
        return 1;
    }

    card = Sci2Card_Singleton_Get();
    if (lbl_806D121C == 0) {
        lbl_806D121C = CardPing_Begin();
    }

    if (Sci2Card_IsIdleOrExhausted(card) == 1) {
        if (!Sci2Card_IsStatusOkNonTerm(card)) {
            card = Sci2Card_Singleton_Get();
            lbl_806D1210 = 0;
            if (Sci2Card_IsStatus3Five(card) == 1) {
                lbl_806D1210 = 2;
            }
            if (Sci2Card_IsRetryExhausted(card) == 1) {
                lbl_806D1210 = 101;
            }
            if (Sci2Card_IsStatus2Two(card) == 1) {
                lbl_806D1210 = 102;
            }
            if (Sci2Card_IsStatus2One(card) == 1) {
                lbl_806D1210 = 103;
            }
            if (Sci2Card_IsStatus2Three(card) == 1) {
                lbl_806D1210 = 104;
            }
            if (Sci2Card_IsStatus2Five(card) == 1) {
                lbl_806D1210 = 105;
            }
            if (Sci2Card_IsStatus2A(card) == 1) {
                lbl_806D1210 = 106;
            }
            if (lbl_806D1210 == 0) {
                Sci2Card_GetResponseStatus(card, &completedStatus1,
                                          &completedStatus2, &completedStatus3);
                if (completedStatus3 == 0x32) {
                    lbl_806D1210 = 100;
                } else {
                    lbl_806D1210 = 1;
                }
            }
            if (lbl_806D1210 == 100) {
                lbl_806D1237 = 0;
            }
            return 1;
        }
        lbl_806D1237 = 0;
        lbl_806D122A = 0;
        lbl_806D1210 = 1;
        lbl_806D122B = 0;
        return 1;
    }

    if (!Sci2Card_IsStatusOkNonTerm(card)) {
        card = Sci2Card_Singleton_Get();
        lbl_806D1210 = 0;
        if (Sci2Card_IsStatus3Five(card) == 1) {
            lbl_806D1210 = 2;
        }
        if (Sci2Card_IsRetryExhausted(card) == 1) {
            lbl_806D1210 = 101;
        }
        if (Sci2Card_IsStatus2Two(card) == 1) {
            lbl_806D1210 = 102;
        }
        if (Sci2Card_IsStatus2One(card) == 1) {
            lbl_806D1210 = 103;
        }
        if (Sci2Card_IsStatus2Three(card) == 1) {
            lbl_806D1210 = 104;
        }
        if (Sci2Card_IsStatus2Five(card) == 1) {
            lbl_806D1210 = 105;
        }
        if (Sci2Card_IsStatus2A(card) == 1) {
            lbl_806D1210 = 106;
        }
        if (lbl_806D1210 == 0) {
            Sci2Card_GetResponseStatus(card, &activeStatus1,
                                      &activeStatus2, &activeStatus3);
            if (activeStatus3 == 0x32) {
                lbl_806D1210 = 100;
            } else {
                lbl_806D1210 = 1;
            }
        }
    }
    return 0;
}

unsigned char card_send_ping_cmd_init(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }

    if (lbl_806D1224 == 1) {
        return 1;
    }

    lbl_806D1220 = 0;
    lbl_806D121C = Sci2Card_SendCmdPing(Sci2Card_Singleton_Get());
    return 1;
}
