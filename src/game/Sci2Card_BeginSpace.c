extern void *Sci2Card_Singleton_Get(void);
extern unsigned char Sci2Card_SendCmdSpace(void *self);

extern int lbl_806CF0E4;
extern int lbl_806D1210;
extern unsigned char g_cardCmdResult;
extern unsigned char lbl_806D122A;

/* 0x80092B18: start a space command and remember whether it was sent. */
unsigned char Sci2Card_BeginSpace(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    g_cardCmdResult = 0;
    lbl_806CF0E4 = 5;
    g_cardCmdResult = Sci2Card_SendCmdSpace(Sci2Card_Singleton_Get());
    return g_cardCmdResult;
}
