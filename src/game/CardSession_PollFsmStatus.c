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
extern unsigned char card_rw_state_machine(void);

extern int lbl_806D1210;

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

/* 0x80092F4C: step the card read/write state machine; once it finishes,
 * keep a success code or record the failure code. */
unsigned char CardSession_PollFsmStatus(void)
{
    if (!card_rw_state_machine()) {
        return 0;
    }
    if (lbl_806D1210 == 1) {
        lbl_806D1210 = 1;
        return 1;
    }
    Sci2Card_SetFailCode();
    return 1;
}
