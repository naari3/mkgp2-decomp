/* Card response status poll, 0x800991FC..0x8009927C. */
extern unsigned char ServiceLatch_CheckTriggered(void);
extern void *Sci2Card_Singleton_Get(void);
extern unsigned char Sci2Card_IsIdleOrExhausted(void *card);
extern unsigned char Sci2Card_GetResponseStatus(void *card, unsigned char *status1,
                                              unsigned char *status2, unsigned char *status3);

#pragma exceptions on
int Sci2Card_PollResponseStatusTri(void)
{
    void *card;
    unsigned char status1;
    unsigned char status2;
    unsigned char status3;

    if (!ServiceLatch_CheckTriggered()) {
        return 0;
    }
    card = Sci2Card_Singleton_Get();
    if (Sci2Card_IsIdleOrExhausted(card) == 1) {
        return 0;
    }
    return -(unsigned char)(Sci2Card_GetResponseStatus(card, &status1, &status2, &status3) == 0) + 2;
}
#pragma exceptions reset
