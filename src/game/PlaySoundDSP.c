/*
 * PlaySoundDSP @ 0x801B3928 (size 0x58).
 *
 * Standalone TU (extab_group=None, no shared extab/extabindex entries).
 *
 * Looks up a DSP filename pointer in g_voicePlayCountTable (a packed array
 * of 12-byte entries laid out as { char *path; void *unused; float unused; })
 * and starts streaming it via ClStream_PlayMono. On success, the returned
 * slot handle is poked with pan = 0xFF through fn_80194AE0.
 *
 * Target asm computes the entry pointer with `lis/subi` against the
 * g_voicePlayCountTable base plus `add r3,r3,r0; lwz r3, 0x8(r3)` so the
 * source expression must keep the constant offset (+8) out of the index
 * multiplier; (char*)base + soundId*12 + 8 reproduces this codegen on
 * GC/1.3.2 cflags_base.
 */

extern int ClStream_PlayMono(void *path, int volume, int channelFlag);
extern int fn_80194AE0(int handle, int pan);
extern unsigned char g_voicePlayCountTable[0x1EF4];

int PlaySoundDSP(int soundId) {
    int handle = ClStream_PlayMono(
        ((void **)(g_voicePlayCountTable + 8))[soundId * 3],
        0, 1);
    if (handle == -1) {
        return 0;
    }
    fn_80194AE0(handle, 0xff);
    return 1;
}
