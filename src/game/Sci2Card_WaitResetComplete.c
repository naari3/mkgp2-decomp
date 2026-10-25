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
extern void Backup_PublishShadowCopy_Inline();

extern int lbl_806D1210;
extern int lbl_806D1214;
extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D1226;
extern unsigned char lbl_806D122A;
extern unsigned char lbl_806D122B;
extern unsigned char lbl_80598A60[];

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

/* 0x80092D4C: wait for the reset command; on success clear the card state,
 * otherwise flag the error and record a failure code. */
unsigned char Sci2Card_WaitResetComplete(void)
{
    void *card = Sci2Card_Singleton_Get();

    if (!Sci2Card_IsIdleOrExhausted(card)) {
        return 0;
    }
    if (Sci2Card_IsStatusOkNonTerm(card) == 1) {
        lbl_806D1214 = 0;
        lbl_806D1224 = 1;
        lbl_806D122A = 0;
        lbl_806D1210 = 1;
        lbl_806D122B = 0;
        lbl_806D1226 = 0;
        lbl_80598A60[0x270] = 0;
        Backup_PublishShadowCopy_Inline(lbl_80598A60);
        return 1;
    }
    lbl_806D1226 = 1;
    lbl_80598A60[0x270] = 1;
    Backup_PublishShadowCopy_Inline(lbl_80598A60);
    Sci2Card_SetFailCode();
    return 1;
}
