extern unsigned char ServiceLatch_CheckTriggered(void);
extern void *Sci2Card_Singleton_Get(void);
extern unsigned int card_eject(int *self);
extern unsigned int Sci2Card_SendCmdSpace(int *self);
extern unsigned char Sci2Card_IsIdleOrExhausted(int *self);
extern unsigned char Sci2Card_IsStatusOkNonTerm(int *self);
extern unsigned char Sci2Card_IsStatus1OneTwoThree(int *self);
extern unsigned char Sci2Card_IsStatus1Zero(int *self);

extern unsigned char lbl_806CF0D4;
extern int lbl_806CF0E4;
extern int lbl_806CF0F8[2];
extern int lbl_806D1210;
extern int lbl_806D1214;
extern unsigned char lbl_806D121C;
extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D1227;
extern unsigned char lbl_806D122A;
extern unsigned char lbl_806D122B;

/* The return value marks initialization, not whether card_eject accepted it.
 * Assigning it to pending deliberately replaces the send result at two sites.
 * Keep this inline so those stores and their branch-local joins are preserved.
 */
static inline unsigned char CardEject_Begin(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }

    lbl_806D1227 = 0;
    lbl_806D121C = card_eject(Sci2Card_Singleton_Get());
    lbl_806CF0D4 = 0;
    return 1;
}

/* 0x80098A90: eject, poll the space command, and retry failed transactions. */
unsigned char card_eject_state_machine(void)
{
    int *card;

    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }
    if (lbl_806D1210 != 0) {
        return 1;
    }

    card = Sci2Card_Singleton_Get();
    if (lbl_806D1227 == 0) {
        if (lbl_806D121C == 0) {
            lbl_806D121C = CardEject_Begin();
        } else if (Sci2Card_IsIdleOrExhausted(card) == 1) {
            if (!Sci2Card_IsStatusOkNonTerm(card)) {
                if (--lbl_806CF0F8[0] > 0) {
                    lbl_806D122B = 0;
                    CardEject_Begin();
                    return 0;
                }
                lbl_806D1210 = 100;
                return 1;
            }
            if (Sci2Card_IsStatus1OneTwoThree(card) == 1) {
                lbl_806D121C = CardEject_Begin();
            } else {
                lbl_806D1227 = 1;
                Sci2Card_SendCmdSpace(card);
            }
        }
    } else if (Sci2Card_IsIdleOrExhausted(card) == 1) {
        if (!Sci2Card_IsStatusOkNonTerm(card)) {
            if (--lbl_806CF0F8[0] > 0) {
                lbl_806D122B = 0;
                CardEject_Begin();
                return 0;
            }
            lbl_806D1210 = 100;
            return 1;
        }
        if (Sci2Card_IsStatus1OneTwoThree(card) == 1) {
            lbl_806D1227 = 0;
            lbl_806D122B = 0;
            CardEject_Begin();
            return 0;
        }
        if (Sci2Card_IsStatus1Zero(card) == 1) {
            lbl_806D1224 = 0;
            lbl_806D1214 = 0;
            lbl_806CF0F8[0] = 5;
            lbl_806D122A = 0;
            lbl_806D1210 = 1;
            lbl_806D122B = 0;
            return 1;
        }
        Sci2Card_SendCmdSpace(card);
    }
    return 0;
}

unsigned char card_eject_init(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }

    lbl_806D1227 = 0;
    lbl_806D121C = card_eject(Sci2Card_Singleton_Get());
    lbl_806CF0D4 = 0;
    return 1;
}
