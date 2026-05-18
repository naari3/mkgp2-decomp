/*
 * CourseBgm_Load @ 0x80064ED0 (size 0x88).
 *
 * Loads the course BGM blob via DVDFile_LoadSync(GetCourseBgmFilePath()) and
 * initialises the playback state. On failure (null path) the data pointers
 * are cleared instead of dispatching to DVD.
 *
 * Companion of CourseBgm_Free (0x80064EA0). Both functions live in the same
 * .text region but were dispatched as separate singletons; this TU only
 * contains CourseBgm_Load.
 *
 * State written:
 *   g_courseBgm      (0x806D10E8) = loaded ptr (or 0)
 *   g_courseBgmSize  (0x806D10EC) = loaded ptr again (companion store --
 *                                   misleading legacy symbol name)
 *   lbl_806D10E0     (.sbss)      = number of leading zero header slots
 *                                   skipped (stride 16 = 4 ints)
 *   lbl_806D10E4     (.sbss)      = 0 (cursor reset)
 *   lbl_806CEEF8     (.sdata)     = 6 (state)
 *   lbl_806CEEFC     (.sdata)     = -1 (reset)
 *
 * Note: the loop walks the loaded blob in 16-byte strides reading int[0] of
 * each block until non-zero, counting how many leading "empty" entries are
 * present. The cursor pointer (r3) is register-only and not stored back.
 *
 * The target has extab/extabindex entries (Large Frame). #pragma exceptions
 * on/reset wraps the function so CW auto-emits them (same idiom as
 * BootNotice_CheckEnterCondition.c).
 */

extern char *GetCourseBgmFilePath(void);          /* GetCourseBgmFilePath */
extern int  *DVDFile_LoadSync(char *path);    /* DVDFile_LoadSync */

extern int  *g_courseBgm;                /* .sbss 0x806D10E8 */
extern int  *g_courseBgmSize;            /* .sbss 0x806D10EC (ptr companion) */
extern int   lbl_806D10E0;               /* .sbss 0x806D10E0 (skip count) */
extern int   lbl_806D10E4;               /* .sbss 0x806D10E4 (cursor reset) */
extern int   lbl_806CEEF8;               /* .sdata 0x806CEEF8 (state) */
extern int   lbl_806CEEFC;               /* .sdata 0x806CEEFC (reset) */

#pragma exceptions on
void CourseBgm_Load(void) {
    char *path;
    int *p;

    path = GetCourseBgmFilePath();
    if (path != 0) {
        g_courseBgm = DVDFile_LoadSync(path);
        g_courseBgmSize = g_courseBgm;
        lbl_806D10E0 = 0;
        for (p = g_courseBgm; *p == 0; p += 4) {
            lbl_806D10E0 = lbl_806D10E0 + 1;
        }
    } else {
        g_courseBgm = 0;
        g_courseBgmSize = 0;
        lbl_806D10E0 = 0;
    }
    lbl_806CEEF8 = 6;
    lbl_806CEEFC = -1;
    lbl_806D10E4 = 0;
}
#pragma exceptions reset
