/*
 * CourseAuxClass (?) deleting destructor @ 0x8007D0D4 (size 0x48, 18 instr).
 *
 * Same generic CW C++ ABI deleting-dtor shape as ObjectBase_Dtor
 * (src/game/ObjectBase.c, dtor_8002CDF4):
 *   1. if (this != NULL) demote *this to the parent vtable
 *      (&lbl_803FE0C8, an 0x18-byte vtable object — exact owner class
 *      not yet identified; no live callers, no other xrefs to
 *      PTR_PTR_803FE0C8 found at audit time).
 *   2. if the short flag arg is > 0, call MemoryManager_TimedFree(this)
 *      (= MemoryManager_TimedFree placeholder) to free the storage.
 *   3. return this in r3 for downstream `bl <this dtor>` chains.
 *
 * Built with CW 1.3.2 + #pragma exceptions on so the matching extab
 * body (Large Frame: Yes / Saved GPR: r31, 0x08080000 / 0x00000000)
 * and extabindex entry auto-emit alongside the .text body.
 *
 * The flag arg is sign-extended (`extsh. r0, r4`) before the > 0
 * compare, which matches a `short` source-level parameter.
 *
 * Renames pending (HANDOFF.md):
 *   dtor_8007D0D4 -> CourseAuxClass_VtableDtor
 */

extern void MemoryManager_TimedFree(void *);
extern char lbl_803FE0C8[];  /* parent-class vtable @ 0x803FE0C8, size 0x18 */

#pragma exceptions on
void *dtor_8007D0D4(void *this, short flag) {
    if (this != 0) {
        *(char **)this = lbl_803FE0C8;
        if (flag > 0) {
            MemoryManager_TimedFree(this);
        }
    }
    return this;
}
#pragma exceptions reset
