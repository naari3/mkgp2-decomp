extern unsigned char ServiceLatch_CheckTriggered(void);

extern int lbl_806CF0E4;
extern int lbl_806CF0E8;
extern int lbl_806D1210;
extern unsigned char lbl_806D121C;
extern int lbl_806D1220;
extern unsigned char lbl_806D122A;
extern int lbl_806D1240;

static inline void CardPrintJob_ResetCommand(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
}

/* 0x800948D4: start the font transfer of a print job. */
unsigned char CardPrintJob_KickFontTransfer(void)
{
    if (!ServiceLatch_CheckTriggered()) {
        CardPrintJob_ResetCommand();
        lbl_806D1210 = 1;
        return 1;
    }
    lbl_806CF0E8 = 3;
    CardPrintJob_ResetCommand();
    lbl_806D1220 = 0;
    lbl_806D1240 = 0;
    return 1;
}
