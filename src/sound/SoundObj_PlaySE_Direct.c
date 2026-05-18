/*
 * SoundObj_PlaySE_Direct @ 0x800594D4 (size 0xA8).
 *
 * Singleton TU: dtk reversed-extab group `auto_SoundObj_PlaySE_Dire_text`
 * is a 1-function bundle with its own extab/extabindex entries
 * (8B / 12B; flags 0x100A0000: has elf-vector, large frame, r30-r31 saved).
 *
 * Behavior:
 *   1) Always fire SoundMgr_PlaySE(mask | (self->channel_bits & 0xF) << 0x1B).
 *      The 4-bit channel id at +0x8 is rotated into the upper portion of
 *      the sound-id word.
 *   2) If the +0x4 gate byte is clear and the sub pointer at +0xC is
 *      non-null, build a local Vec3 by (a) struct-copying the constant
 *      template at lbl_802EDD24 (12 bytes, all-zero in the rom but emitted
 *      via lwz/stw so source must mirror that shape) and (b) overwriting
 *      each lane with sub->fXX. Pass &local as the second arg to
 *      fn_8016C288, reusing the same channel-id expression (CW 1.3.2
 *      does NOT CSE the `(self+8 & 0xF) << 0x1B` recompute).
 *
 * Struct shapes (opaque, byte offsets only):
 *   self  +0x4  : u8  gate (skip Vec3 branch when non-zero)
 *   self  +0x8  : u32 packed flags; low nibble = channel id
 *   self  +0xC  : sub*
 *   sub   +0xC  : float x
 *   sub   +0x1C : float y
 *   sub   +0x2C : float z
 */

extern int SoundMgr_PlaySE(unsigned int sound_id);
extern void fn_8016C288(unsigned int sound_id, float *vec);

extern const struct {
    unsigned int a, b, c;
} lbl_802EDD24;

#pragma exceptions on
void SoundObj_PlaySE_Direct(unsigned char *self, unsigned int mask) {
    float local[3];

    SoundMgr_PlaySE(mask | (*(unsigned int *)(self + 8) & 0xF) << 0x1B);

    if (self[4] == 0) {
        void *sub = *(void **)(self + 0xC);
        if (sub != 0) {
            *(unsigned int *)&local[0] = lbl_802EDD24.a;
            *(unsigned int *)&local[1] = lbl_802EDD24.b;
            *(unsigned int *)&local[2] = lbl_802EDD24.c;
            local[0] = *(float *)((char *)sub + 0xC);
            local[1] = *(float *)((char *)sub + 0x1C);
            local[2] = *(float *)((char *)sub + 0x2C);
            fn_8016C288(
                mask | (*(unsigned int *)(self + 8) & 0xF) << 0x1B, local);
        }
    }
}
#pragma exceptions reset
