extern unsigned char ServiceLatch_CheckTriggered(void);
extern void *Sci2Card_Singleton_Get(void);
extern unsigned char Sci2Card_SendCmdPing(void *card);

extern int lbl_806CF0E4;
extern int lbl_806D1210;
extern unsigned char lbl_806D121C;
extern int lbl_806D1220;
extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D122A;

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
