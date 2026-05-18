/*
 * BootNotice_CheckEnterCondition @ 0x80084D98 (size 0x60).
 *
 * Gate check called from BootDispatcher (0x8002F0C0) before entering the
 * 599-frame "notice" loop (4-cabinet PCB linkup notice). Returns 1 to
 * authorize entry, 0 to skip.
 *
 * Behaviour:
 *   - if (g_BootNoticeArm == 0) return 0;            (lbl_806D11B8)
 *   - if (g_BootNoticeOverlay == 0)                  (lbl_806D1880)
 *         fn_801DB68C(g_BootNoticeOverlay, 1);       (cleanup, value is 0)
 *         g_BootNoticeOverlay = 0;                   (dead store: emitted)
 *   - g_BootNoticeArm = 0;
 *   - SetSyncTarget(2);
 *   - return 1;
 *
 * extab/extabindex entries are present in the target (Large Frame, no GPR
 * save, header word 0x00080000). Emitted via #pragma exceptions on/reset so
 * CW auto-generates them.
 */

extern unsigned int lbl_806D11B8;   // .sbss size 0x4: notice-arm flag
extern unsigned int lbl_806D1880;   // .sbss size 0x8: notice overlay alloc slot
extern void fn_801DB68C(unsigned int p, int q);
extern void SetSyncTarget(int target);

#pragma exceptions on
int BootNotice_CheckEnterCondition(void) {
    if (lbl_806D11B8 == 0) {
        return 0;
    }
    if (lbl_806D1880 == 0) {
        fn_801DB68C(lbl_806D1880, 1);
        lbl_806D1880 = 0;
    }
    lbl_806D11B8 = 0;
    SetSyncTarget(2);
    return 1;
}
#pragma exceptions reset
