/* Reset card retry count and command state, 0x80099284..0x800992C0. */
extern unsigned char ServiceLatch_CheckTriggered(void);
extern void *Sci2Card_Singleton_Get(void);
extern void Sci2Card_ResetRetryCount(void *card);
extern int lbl_806D1210;
extern int lbl_806D1214;

#pragma exceptions on
void Sci2Card_ResetRetryAndStatus(void)
{
    if (ServiceLatch_CheckTriggered()) {
        Sci2Card_ResetRetryCount(Sci2Card_Singleton_Get());
        lbl_806D1210 = 0;
        lbl_806D1214 = 0;
    }
}
#pragma exceptions reset
