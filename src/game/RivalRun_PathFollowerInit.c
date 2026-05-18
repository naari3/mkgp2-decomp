/*
 * RivalRun_PathFollowerInit @ 0x80137588 (size 0x50).
 *
 * Initializer for the per-rival PathFollower context (0x2C bytes).
 *
 * Field layout (from Ghidra decompile of related fns at 0x80135EFC etc):
 *   +0x00: u8  needsSearch (set to 1, "request waypoint search")
 *   +0x04: u32 laneIndex   (= 0)
 *   +0x08: u32 segmentCount(= 0)
 *   +0x0C: u32 currentSeg  (= 0)
 *   +0x10..+0x18: float[3] targetPos (untouched here)
 *   +0x1C..+0x24: float[3] direction (untouched here)
 *   +0x28: float speed     (= 0.0f via sdata2 constant pool ref to lbl_806D738C)
 *
 * After init the context is handed to RivalRun_UpdatePathFollower so the
 * caller-visible state (target pos, direction, speed) is populated on the
 * same frame; the returned pointer is the same `self` for chained init.
 *
 * The TU lives in `game` lib (CW 1.3.2). #pragma exceptions on/reset wraps
 * the function so CW auto-emits the extab/extabindex entry (matches the
 * AI_GetYaw / NamCam_LoadImage template; the extab block flags
 * "Has Elf Vector: Yes, Saved GPR range: r31" which matches a single
 * non-volatile save inside a try-scope frame).
 */

extern void RivalRun_UpdatePathFollower(void *self);

#pragma exceptions on
void *RivalRun_PathFollowerInit(void *self) {
    *(unsigned char *)((char *)self + 0x00) = 1;
    *(unsigned int  *)((char *)self + 0x04) = 0;
    *(unsigned int  *)((char *)self + 0x08) = 0;
    *(unsigned int  *)((char *)self + 0x0C) = 0;
    *(float        *)((char *)self + 0x28) = 0.0f;
    RivalRun_UpdatePathFollower(self);
    return self;
}
#pragma exceptions reset
