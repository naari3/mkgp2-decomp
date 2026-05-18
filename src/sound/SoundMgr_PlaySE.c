/*
 * SoundMgr_PlaySE @ 0x8016C3FC (size 0x48).
 *
 * Standalone TU because dtk reversed-extab group
 * `auto_SoundMgr_PlaySE_text` is a 1-function bundle with its own
 * extab/extabindex entries (8B / 12B).
 *
 * Pass-through wrapper around SoundMgr_Play. The sound_id arrives in r3
 * from the caller (`li r3, <id>; bl SoundMgr_PlaySE`) and is forwarded
 * verbatim to SoundMgr_Play in the fall-through path. The two early
 * return arms (`return 0` / `return 1`) overwrite r3 with the literal
 * return value (target codegen: `li r3, 0` / `li r3, 1`).
 *
 * g_weatherSystem (.sbss 0x806D15C0) is a pointer; field at +0x2C is a
 * one-byte "suppress SE" flag.
 */

extern int SoundMgr_Play(int sound_id);
extern void *g_weatherSystem;

#pragma exceptions on
int SoundMgr_PlaySE(int sound_id) {
    if (g_weatherSystem == 0) {
        return 0;
    }
    if (*((unsigned char *)g_weatherSystem + 0x2c) != 0) {
        return 1;
    }
    return SoundMgr_Play(sound_id);
}
#pragma exceptions reset
