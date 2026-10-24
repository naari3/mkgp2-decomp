extern char lbl_805AC2E0[];
extern char lbl_80598A60[];
extern char lbl_805A5EA0[];
extern unsigned char lbl_806CF008;
extern void *lbl_806D11E0;
extern unsigned char lbl_806D11E4;
extern int lbl_806D11F0;
extern void PlayStats_CopyStatsBlock(void *dst, void *src);
extern unsigned char ServiceButtonExtra_Get(void);

void PlayStats_LoadOrInitForBoot(void) {
    PlayStats_CopyStatsBlock(lbl_805AC2E0, lbl_80598A60 + 0x274);
    if (ServiceButtonExtra_Get() == 1) {
        lbl_806CF008 = 0;
    } else {
        lbl_806CF008 = 1;
        lbl_806D11E0 = lbl_805A5EA0;
        lbl_806D11E4 = 0;
        lbl_806D11F0 = 0;
    }
}
