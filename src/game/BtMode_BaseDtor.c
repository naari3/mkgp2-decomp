/*
 * BtMode base deleting destructor @ 0x800A0688 (size 0x48, 18 instr).
 *
 * Trivial deleting-dtor for the BtMode base class. Same shape as
 * ObjectBase_Dtor (commit 9807e6c):
 *   1. if (this != NULL) demote *this back to the BtMode base vtable
 *      (&lbl_8040E76C) so any derived dtor chain that follows sees a
 *      cleanly typed base subobject.
 *   2. if the second arg (delete-flag, passed as a short) is > 0, call
 *      `dtor_8003AFB8(this)` (= MemoryManager_TimedFree) to release the
 *      allocation. Otherwise leave the storage alive.
 *   3. return this in r3 (C++ ABI deleting-dtor convention).
 *
 * Note: BtMode has a separate full scene-teardown path at BtMode_Dtor
 * (0x8009F47C). This function is the trivial vtable-slot dtor.
 *
 * CW 1.3.2 + #pragma exceptions on auto-emits matching extab body
 * (Large Frame: Yes / Saved GPR: r31, body 0x08080000 / 0x00000000).
 *
 * The flag argument is sign-extended (`extsh. r0, r4`) before the > 0
 * check, which matches a `short` parameter type at the source level.
 *
 * Renames pending (HANDOFF.md):
 *   dtor_800A0688 -> BtMode_BaseDtor
 */

extern void dtor_8003AFB8(void *);
extern char lbl_8040E76C[];  /* BtMode base vtable @ 0x8040E76C */

#pragma exceptions on
void *dtor_800A0688(void *this, short flag) {
    if (this != 0) {
        *(char **)this = lbl_8040E76C;
        if (flag > 0) {
            dtor_8003AFB8(this);
        }
    }
    return this;
}
#pragma exceptions reset
