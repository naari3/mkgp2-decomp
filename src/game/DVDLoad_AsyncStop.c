/* Stop the async load: fire the pending completion callback, then reset the
 * TEV callback and the HSD render state. */
typedef void (*DVDLoadCallback)(void *arg0, void *arg1);

extern int lbl_806D1150;
extern DVDLoadCallback lbl_806D1154;
extern void *lbl_806D1158;
extern void *lbl_806D115C;
extern void HSD_MObjSetTevStageCallback(void *cb);
extern void HSD_StateInvalidate(int state);

void DVDLoad_AsyncStop(void)
{
    if (lbl_806D1154 != 0) {
        lbl_806D1154(lbl_806D115C, lbl_806D1158);
    }
    HSD_MObjSetTevStageCallback(0);
    lbl_806D1150 = 0;
    lbl_806D1154 = 0;
    HSD_StateInvalidate(-1);
}
