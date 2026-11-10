/* Start an async load: install the draw-done TEV callback and remember the
 * request and its completion callback. Fails while one is already running. */
extern void *DVDLoad_bss_806D1150;
extern void *DVDLoad_bss_806D1154;
extern void *DVDLoad_bss_806D1158;
extern void DVDLoad_DrawDoneCallback(void);
extern void HSD_MObjSetTevStageCallback(void *cb);

int DVDLoad_AsyncStart(void *request, void *callback, void *arg)
{
    if (request == 0 || DVDLoad_bss_806D1150 != 0) {
        return 0;
    }
    HSD_MObjSetTevStageCallback(DVDLoad_DrawDoneCallback);
    DVDLoad_bss_806D1150 = request;
    DVDLoad_bss_806D1154 = callback;
    DVDLoad_bss_806D1158 = arg;
    return 1;
}
