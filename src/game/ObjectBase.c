/*
 * ObjectBase deleting destructor @ 0x8002CDF4 (size 0x48, 18 instr).
 *
 * CW C++ ABI trivial deleting dtor for the ObjectBase root class:
 *   1. if (this != NULL) demote *this back to the ObjectBase vtable
 *      (&lbl_803F5658) so any derived dtor chain that follows sees a
 *      cleanly typed base subobject.
 *   2. if the second arg (delete-flag, passed as a short) is > 0, call
 *      `dtor_8003AFB8(this)` (= MemoryManager_TimedFree) to release the
 *      allocation. Otherwise leave the storage alive.
 *   3. return this in r3 (this is what makes downstream `bl <this dtor>`
 *      chains work with the C++ ABI deleting-dtor convention).
 *
 * Uses the same shape as the other small deleting dtors in this lib
 * (dtor_8006178C / dtor_80036988 ...): #pragma exceptions on so CW 1.3.2
 * auto-emits the matching extab body (Large Frame: Yes / Saved GPR: r31).
 *
 * The flag argument is sign-extended (`extsh. r0, r4`) before the > 0
 * check, which matches a `short` parameter type at the source level.
 *
 * Renames pending (HANDOFF.md):
 *   dtor_8002CDF4 -> ObjectBase_Dtor
 */

extern void dtor_8003AFB8(void *);
extern char lbl_803F5658[];  /* ObjectBase vtable @ 0x803F5658 */

#pragma exceptions on
void *dtor_8002CDF4(void *this, short flag) {
    if (this != 0) {
        *(char **)this = lbl_803F5658;
        if (flag > 0) {
            dtor_8003AFB8(this);
        }
    }
    return this;
}
#pragma exceptions reset
