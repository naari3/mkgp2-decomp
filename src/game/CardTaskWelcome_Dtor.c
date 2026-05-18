/*
 * CardTaskWelcome deleting destructor @ 0x8008A058 (size 0x48, 18 instr).
 *
 * Same shape as ObjectBase_Dtor (commit 9807e6c, src/game/ObjectBase.c):
 * trivial C++ deleting dtor with vtable demote + conditional delete.
 *
 *   1. if (this != NULL) demote *this back to the CardTaskWelcome vtable
 *      (&lbl_803FE8B8) so any derived chain that follows sees a cleanly
 *      typed base subobject.
 *   2. if the second arg (delete-flag, passed as a short) is > 0, call
 *      `MemoryManager_TimedFree(this)` (= MemoryManager_TimedFree) to release the
 *      allocation.
 *   3. return this in r3.
 *
 * CW 1.3.2 + #pragma exceptions on auto-emits the matching extab body
 * (Large Frame: Yes / Saved GPR: r31, body 0x08080000 / 0x00000000).
 *
 * The flag argument is sign-extended (`extsh. r0, r4`) before the > 0
 * check, which matches a `short` parameter type at the source level.
 *
 * Renames pending (HANDOFF.md):
 *   dtor_8008A058 -> CardTaskWelcome_Dtor
 *   lbl_803FE8B8  -> g_CardTaskWelcomeVtable (left as lbl_ for now,
 *                    block-level rename is owned by separate batch)
 */

extern void MemoryManager_TimedFree(void *);
extern char lbl_803FE8B8[];  /* CardTaskWelcome vtable @ 0x803FE8B8 */

#pragma exceptions on
void *dtor_8008A058(void *this, short flag) {
    if (this != 0) {
        *(char **)this = lbl_803FE8B8;
        if (flag > 0) {
            MemoryManager_TimedFree(this);
        }
    }
    return this;
}
#pragma exceptions reset
