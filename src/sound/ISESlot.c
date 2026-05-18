/*
 * ISESlot (Interactive Sound Effect Slot) — small op pair.
 *
 * dtk reversed-extab group `auto_03_80049B40_text` (eg_sz=2 forced bundle).
 * No extab/extabindex entries in this group (text-only).
 *
 * Layout (inferred):
 *   +0x00 : (unknown, written by FrameUpdate to 0.0f via lfs)
 *   +0x04 : u8  active flag
 *   +0x05 : u8  cleanup_pending flag
 *   +0x08 : u32 cleanup param (opaque; consumed by ISESlot_FrameUpdate)
 *   +0x0C : u32 state (FrameUpdate dispatch)
 *
 * Functions:
 *   ISESlot_StartCleanup @ 0x80049B40 size 0x28
 *   ISESlot_IsActive     @ 0x80049B68 size 0x08
 */

int ISESlot_StartCleanup(unsigned char *self, unsigned int param) {
    if (self[4] == 0) {
        return 0;
    }
    self[5] = 1;
    *(unsigned int *)(self + 8) = param;
    return 1;
}

unsigned char ISESlot_IsActive(unsigned char *self) {
    return self[4];
}
