/*
 * LakituStart_Dtor @ 0x8003DAE0 (size 0x60).
 *
 * Owner-of-pointer dtor variant of dtor_80064CD4 (commit 6a570d8):
 * the heap-allocated member sits at offset 0x44 of `this` (vs offset
 * 0 in dtor_80064CD4), and the inner cleanup is a 2-arg call
 * `fn_800346E4(member, 1)` (Object dtor with GX sync) rather than a
 * direct free. The trailing `if (flag > 0) MemoryManager_TimedFree(this);`
 * is the same C++ ABI delete-flag tail.
 *
 * Target asm shows the inner call passes `r4 = 1` (extsh. is not used
 * for the inner branch, only the member NULL check), so the second
 * argument is a literal `1` — matching the dtor-style "delete inner
 * subobject" convention used elsewhere in the project. `fn_800346E4`
 * (placeholder name, size 0xB4) is the GX-sync object dtor referred
 * to as `Object_DtorWithGXSync` in Ghidra's prototype, but kept under
 * its current placeholder name in symbols.txt.
 *
 * Frame: 0x10, saves r30-r31 (Large Frame: Yes, Saved GPR r30-r31)
 * — matches the extab body at 0x800060D0 (`0x10080000`).
 *
 * Approach: `#pragma exceptions on` lets CW 1.3.2 auto-emit the
 * matching extab (0x800060D0, size 0x8) and extabindex (0x8001FCE8,
 * size 0xC) entries, mirroring the dtor_80064CD4 recipe.
 */

extern void fn_800346E4(void *member, int flag);
extern void dtor_8003AFB8(void *p);

#pragma exceptions on
void *LakituStart_Dtor(void *this, short flag) {
    if (this != 0) {
        void *member = *(void **)((char *)this + 0x44);
        if (member != 0) {
            fn_800346E4(member, 1);
        }
        if (flag > 0) {
            dtor_8003AFB8(this);
        }
    }
    return this;
}
#pragma exceptions reset
