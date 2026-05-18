/*
 * Trivial deleting destructor @ 0x801BA14C (size 0x48, 18 instr).
 *
 * Same CW C++ ABI deleting dtor pattern as ObjectBase_Dtor (commit
 * 9807e6c, src/game/ObjectBase.c) and the rest of the
 * ObjectBase_Dtor-shaped sibling set. Only the vtable address differs:
 *
 *   ObjectBase_Dtor          : *this = &lbl_803F5658
 *   SceneRender_BaseDtor     : *this = &lbl_803F58E0
 *   dtor_801BA14C (here)     : *this = &lbl_8049A844  (PTR_PTR_8049A844)
 *
 * Body:
 *   1. if (this != NULL) demote *this back to the base vtable
 *      (&lbl_8049A844) so any derived dtor chain that follows sees a
 *      cleanly typed base subobject.
 *   2. if the second arg (delete-flag, passed as a short) is > 0, call
 *      `dtor_8003AFB8(this)` (= MemoryManager_TimedFree placeholder) to
 *      release the allocation. Otherwise leave the storage alive.
 *   3. return this in r3 (C++ ABI deleting-dtor convention).
 *
 * The flag argument is sign-extended (`extsh. r0, r4`) before the > 0
 * check, which matches a `short` parameter type at the source level.
 *
 * #pragma exceptions on so CW 1.3.2 auto-emits the matching extab body
 * (Large Frame: Yes / Saved GPR: r31, body 0x08080000 / 0x00000000).
 *
 * Parent class for &lbl_8049A844 is currently unidentified; keeping the
 * function name as the placeholder `dtor_801BA14C` (no rename in this
 * commit).
 *
 * extab      @ 0x80013114-0x8001311C
 * extabindex @ 0x800279BC-0x800279C8
 */

extern void dtor_8003AFB8(void *);
extern char lbl_8049A844[];  /* unidentified base vtable @ 0x8049A844 */

#pragma exceptions on
void *dtor_801BA14C(void *this, short flag) {
    if (this != 0) {
        *(char **)this = lbl_8049A844;
        if (flag > 0) {
            dtor_8003AFB8(this);
        }
    }
    return this;
}
#pragma exceptions reset
