extern unsigned char ServiceLatch_CheckTriggered(void);
extern void *Sci2Card_Singleton_Get(void);
extern unsigned char Sci2Card_SendCmdOptions(void *card, unsigned char read,
                                           unsigned char option);

extern int lbl_806CF0E4;
extern int lbl_806D1210;
extern unsigned char lbl_806D121C;
extern unsigned char lbl_806D122A;

unsigned char card_send_read_cmd_init_dup_unused(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }

    lbl_806D121C = Sci2Card_SendCmdOptions(Sci2Card_Singleton_Get(), 1, 0);
    return 1;
}
