/*
 * ISESlot_StopEffect @ 0x80049AFC (size 0x44).
 *
 * Standalone TU because dtk reversed-extab group
 * `auto_ISESlot_StopEffect_text` is a 1-function bundle distinct from
 * `auto_03_80049B40_text` (which holds ISESlot_StartCleanup /
 * ISESlot_IsActive in src/sound/ISESlot.c).
 *
 * The pending handle stored at +0x18 is forwarded to fn_800DD874 along
 * with the caller-supplied (idx, value) pair (passed transparently in
 * r4/r5 — target codegen never touches them, so we model the function
 * as a 3-arg pass-through).
 *
 * Layout (opaque ISESlot block):
 *   +0x04 : u8   active flag
 *   +0x18 : void * pending effect handle (consumed by fn_800DD874)
 */

extern void fn_800DD874(void *handle, int idx, unsigned char value);

#pragma exceptions on
int ISESlot_StopEffect(void *self, int idx, unsigned char value) {
    void *handle;
    if (*(unsigned char *)((char *)self + 4) == 0) {
        return 0;
    }
    handle = *(void **)((char *)self + 0x18);
    if (handle != 0) {
        fn_800DD874(handle, idx, value);
    }
    return 1;
}
#pragma exceptions reset
