/*
 * SyncSlot_ApplyCourseChoice
 *   Reads the sync-slot byte at lbl_805AC258 (delivered via msg_type 4) and
 *   applies the selected cup/course/lap-flag to the local race configuration.
 *
 *   Bit layout of lbl_805AC258 (halfword):
 *     bits[10:4] = cupId  (7-bit, fed to GetCourseSelectEntry)
 *     bit[3]     = "lap shifted" flag (passed as 4th arg to SetCourseParams)
 *
 *   The selected cupId is also cached at lbl_806CF12C for later reads.
 *
 *   Held in its own TU (separate from SyncSlot.c) because SyncSlot.c declares
 *   lbl_805AC258 as an `unsigned char[0x38]` blob to satisfy the manual asm
 *   prologue in SyncSlot_Reset; this function needs the same address treated
 *   as halfword-aligned storage to reproduce the target's lhz/lbz access mix.
 */

extern unsigned short lbl_805AC258[0x1c];
extern unsigned int lbl_806CF12C;

extern int *GetCourseSelectEntry(int cupId);
extern void SetCourseParams(int arg0, int arg1, int arg2, int lapShifted);

int SyncSlot_ApplyCourseChoice(void) {
    int *entry = GetCourseSelectEntry((lbl_805AC258[0] >> 4) & 0x7f);
    SetCourseParams(entry[0], entry[1], entry[2],
                    (((unsigned char *)lbl_805AC258)[1] >> 3) & 1);
    lbl_806CF12C = (lbl_805AC258[0] >> 4) & 0x7f;
    return 1;
}
