/* Stop the async load: fire the pending completion callback, then reset the
 * TEV callback and the HSD render state. */
typedef void (*DVDLoadCallback)(void *arg0, void *arg1);

extern int DVDLoad_bss_806D1150;
extern DVDLoadCallback DVDLoad_bss_806D1154;
extern void *DVDLoad_bss_806D1158;
extern void *DVDLoad_bss_806D115C;
extern void HSD_MObjSetTevStageCallback(void *cb);
extern void HSD_StateInvalidate(int state);

void DVDLoad_AsyncStop(void)
{
    if (DVDLoad_bss_806D1154 != 0) {
        DVDLoad_bss_806D1154(DVDLoad_bss_806D115C, DVDLoad_bss_806D1158);
    }
    HSD_MObjSetTevStageCallback(0);
    DVDLoad_bss_806D1150 = 0;
    DVDLoad_bss_806D1154 = 0;
    HSD_StateInvalidate(-1);
}
