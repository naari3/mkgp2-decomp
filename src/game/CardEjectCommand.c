extern unsigned char ServiceLatch_CheckTriggered(void);
extern void *Sci2Card_Singleton_Get(void);
extern unsigned int card_eject(int *self);

extern unsigned char lbl_806CF0D4;
extern int lbl_806CF0E4;
extern int lbl_806D1210;
extern unsigned char lbl_806D121C;
extern unsigned char lbl_806D1227;
extern unsigned char lbl_806D122A;

unsigned char card_eject_init(void)
{
    lbl_806D1210 = 0;
    lbl_806D122A = 1;
    lbl_806D121C = 0;
    lbl_806CF0E4 = 5;
    if (!ServiceLatch_CheckTriggered()) {
        lbl_806D1210 = 1;
        return 1;
    }

    lbl_806D1227 = 0;
    lbl_806D121C = card_eject(Sci2Card_Singleton_Get());
    lbl_806CF0D4 = 0;
    return 1;
}
