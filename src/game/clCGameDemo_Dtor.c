/*
 * clCGameDemo deleting destructor @ 0x800AE6BC (size 0x60, 24 instr).
 *
 * C++ deleting dtor for clCGameDemo (vtable @ 0x80419F0C, RTTI
 * "clCGameDemo" @ 0x80328E7C). Compared to the trivial leaf dtors
 * (ObjectBase_Dtor / CardTaskWelcome_Dtor), this one delegates the base
 * subobject teardown to ObjectBase_Dtor (= dtor_8002CDF4) with the
 * non-delete flag (0):
 *
 *   1. if (this != NULL) demote *this back to the clCGameDemo vtable
 *      (&lbl_80419F0C) so the inherited ObjectBase teardown sees the
 *      base subobject after the vptr has been reset on this layer.
 *   2. call ObjectBase_Dtor(this, 0) to run the base destructor without
 *      freeing storage (the base layer must not free; this layer owns
 *      the decision).
 *   3. if the second arg (delete-flag, passed as a short) is > 0, call
 *      `MemoryManager_TimedFree(this)` (= MemoryManager_TimedFree) to release the
 *      allocation.
 *   4. return this in r3.
 *
 * Both `this` (r30) and the original flag (r31) are saved across the
 * bl ObjectBase_Dtor call, so the extab body advertises Saved GPR range
 * r30-r31 (vs the sibling leaf dtors which only save r31).
 *
 * CW 1.3.2 + #pragma exceptions on auto-emits the matching extab body
 * (Large Frame: Yes / Saved GPR: r30-r31, 0x10080000 / 0x00000000).
 *
 * The flag argument is sign-extended (`extsh. r0, r31`) before the > 0
 * check, which matches a `short` parameter type at the source level.
 *
 * Renames pending (HANDOFF.md):
 *   dtor_800AE6BC -> clCGameDemo_Dtor
 */

extern void *dtor_8002CDF4(void *this, short flag);  /* ObjectBase_Dtor */
extern void MemoryManager_TimedFree(void *);                    /* MemoryManager_TimedFree */
extern char lbl_80419F0C[];                           /* clCGameDemo vtable @ 0x80419F0C */

#pragma exceptions on
void *clCGameDemo_Dtor(void *this, short flag) {
    if (this != 0) {
        *(char **)this = lbl_80419F0C;
        dtor_8002CDF4(this, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(this);
        }
    }
    return this;
}
#pragma exceptions reset
