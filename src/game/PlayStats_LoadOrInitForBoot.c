extern char PlayStats_bss_805AC2E0[];
extern char lbl_80598A60[];
extern char g_operationClock[];
extern unsigned char PlayStats_data_806CF008;
extern void *PlayStats_bss_806D11E0;
extern unsigned char PlayStats_bss_806D11E4;
extern int PlayStats_bss_806D11F0;
extern void PlayStats_CopyStatsBlock(void *dst, void *src);
extern unsigned char ServiceButtonExtra_Get(void);

void PlayStats_LoadOrInitForBoot(void) {
    PlayStats_CopyStatsBlock(PlayStats_bss_805AC2E0, lbl_80598A60 + 0x274);
    if (ServiceButtonExtra_Get() == 1) {
        PlayStats_data_806CF008 = 0;
    } else {
        PlayStats_data_806CF008 = 1;
        PlayStats_bss_806D11E0 = g_operationClock;
        PlayStats_bss_806D11E4 = 0;
        PlayStats_bss_806D11F0 = 0;
    }
}
