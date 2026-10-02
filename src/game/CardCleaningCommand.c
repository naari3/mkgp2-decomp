extern unsigned char ServiceLatch_CheckTriggered(void);
extern void *Sci2Card_Singleton_Get(void);
extern unsigned char Sci2Card_SendCmdOptions(void *card, unsigned char read,
                                             unsigned char option);
extern unsigned char Sci2Card_ForceFailState(void *card);

extern int lbl_806CF0E4;
extern int lbl_806D1210;
extern int lbl_806D1214;
extern unsigned char lbl_806D121C;
extern unsigned char lbl_806D1224;
extern unsigned char lbl_806D122A;
extern unsigned char lbl_806D1237;
extern unsigned char lbl_806D1238;

unsigned char card_send_cleaning_cmd_init(void)
{
    void *card;

    if (lbl_806D1238 == 1) {
        return 1;
    }
    lbl_806D1238 = 1;

    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806CF0E4 = 5;
        lbl_806D1224 = 0;
        lbl_806D1214 = 0;
        lbl_806D1210 = 1;
        return 1;
    }

    card = Sci2Card_Singleton_Get();
    if (lbl_806D1237 == 0) {
        lbl_806D1210 = 0;
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806D121C = Sci2Card_SendCmdOptions(card, 0, 1);
    } else {
        lbl_806D1210 = 0;
        lbl_806D122A = 1;
        lbl_806D121C = 0;
        lbl_806CF0E4 = 5;
        Sci2Card_ForceFailState(card);
    }
    return 1;
}
