/*
 * SceneRender base-class deleting destructor @ 0x8003A71C (size 0x48).
 *
 * Same trivial CW C++ ABI deleting dtor pattern as ObjectBase_Dtor
 * (game/ObjectBase.c, commit 9807e6c). Only the vtable address differs:
 *   ObjectBase_Dtor : *this = &lbl_803F5658
 *   SceneRender_BaseDtor : *this = &lbl_803F58E0
 *
 * Body:
 *   1. if (this != NULL) demote *this back to the SceneRender base vtable
 *      (&lbl_803F58E0) so any derived dtor chain that follows sees a
 *      cleanly typed base subobject.
 *   2. if the second arg (delete-flag, passed as a short) is > 0, call
 *      `MemoryManager_TimedFree(this)` (= MemoryManager_TimedFree) to release the
 *      allocation. Otherwise leave the storage alive.
 *   3. return this in r3 (C++ ABI deleting-dtor convention).
 *
 * The flag argument is sign-extended (`extsh. r0, r4`) before the > 0
 * check, which matches a `short` parameter type at the source level.
 *
 * #pragma exceptions on so CW 1.3.2 auto-emits the matching extab body
 * (Large Frame: Yes / Saved GPR: r31, body 0x08080000 / 0x00000000).
 *
 * Renames pending (HANDOFF.md):
 *   dtor_8003A71C -> SceneRender_BaseDtor
 */

extern void MemoryManager_TimedFree(void *);
extern char lbl_803F58E0[];  /* SceneRender base vtable @ 0x803F58E0 */

#pragma exceptions on
void *dtor_8003A71C(void *this, short flag) {
    if (this != 0) {
        *(char **)this = lbl_803F58E0;
        if (flag > 0) {
            MemoryManager_TimedFree(this);
        }
    }
    return this;
}
#pragma exceptions reset
