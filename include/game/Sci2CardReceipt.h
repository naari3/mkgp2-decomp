#ifndef GAME_SCI2CARDRECEIPT_H
#define GAME_SCI2CARDRECEIPT_H

/* Receipt print flow shared by the card session ticks. The out-of-line
 * copies live in Sci2Card_PrintReceipt.c; the session ticks inline them. */

extern void *Sci2Card_Singleton_Get(void);
extern unsigned char Sci2Card_IsIdleOrExhausted(void *card);
extern unsigned char Sci2Card_IsStatusOkNonTerm(void *card);
extern unsigned char Sci2Card_IsStatus3Five(void *card);
extern unsigned char Sci2Card_IsRetryExhausted(void *card);
extern unsigned char Sci2Card_IsStatus2Two(void *card);
extern unsigned char Sci2Card_IsStatus2One(void *card);
extern unsigned char Sci2Card_IsStatus2Three(void *card);
extern unsigned char Sci2Card_IsStatus2Five(void *card);
extern unsigned char Sci2Card_IsStatus2A(void *card);
extern void Sci2Card_GetResponseStatus(void *card, unsigned char *a, unsigned char *b, unsigned char *c);
extern unsigned char ServiceLatch_CheckTriggered(void);
extern unsigned char Sci2Card_IsStatus3Zero(void *card);
extern int Sci2Card_BuildScoreReceiptLine(int line);
extern int Sci2Card_BuildRetryReceiptLine(int line);
unsigned char Sci2Card_PrintReceipt_PollState(void);
unsigned char Sci2Card_PrintReceipt_StartFlow(int mode, unsigned char header, unsigned char retry);

extern int lbl_806D1210;
extern int lbl_806CF0DC;
extern int lbl_806CF0E0;
extern int lbl_806CF0E4;
extern int lbl_806CF0E8;
extern int lbl_806CF0EC;
extern int lbl_806D1214;
extern int lbl_806D1218;
extern unsigned char lbl_806D121C;
extern unsigned char lbl_806D1228;
extern unsigned char lbl_806D1229;
extern unsigned char lbl_806D122A;
extern unsigned char lbl_806D122B;
extern int lbl_806D123C;
extern signed char g_playerData[];

/* Map the card's failure status to an error code (0 = not determined). */
static inline void Sci2Card_SetFailCode(void)
{
    void *card = Sci2Card_Singleton_Get();
    unsigned char status1;
    unsigned char status2;
    unsigned char status3;

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
        Sci2Card_GetResponseStatus(card, &status1, &status2, &status3);
        if (status3 == 50) {
            lbl_806D1210 = 100;
        } else {
            lbl_806D1210 = 1;
        }
    }
}

static inline unsigned char Receipt_IsDone(int line)
{
    unsigned char done = 0;

    if (line >= 9 && lbl_806CF0EC == 1) {
        done = 1;
    } else if (line >= 10) {
        done = 1;
    } else if (line >= 2 && lbl_806CF0EC == 0) {
        done = 1;
    }
    return done;
}

static inline void Receipt_BuildLine(int line)
{
    int next;

    if (lbl_806D122B == 0) {
        next = Sci2Card_BuildScoreReceiptLine(line);
    } else {
        next = Sci2Card_BuildRetryReceiptLine(line);
    }
    lbl_806D1218 = next;
}

static inline unsigned char Receipt_Advance(void)
{
    int line = lbl_806D1218;

    if (Receipt_IsDone(line) == 1) {
        lbl_806D122A = 0;
        lbl_806D1210 = 1;
        lbl_806D122B = 0;
        return 1;
    }
    Receipt_BuildLine(line);
    return 0;
}

static inline unsigned char Receipt_StartFlow(int mode, unsigned char header, unsigned char retry)
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

static inline unsigned char Receipt_PollState(void)
{
    void *card;
    unsigned char status1;
    unsigned char status2;
    unsigned char status3;

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

#endif
