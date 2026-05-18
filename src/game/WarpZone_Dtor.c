/*
 * WarpZone deleting destructor @ 0x800AA888 (size 0x48, 18 instr).
 *
 * Single-WarpZone trivial deleting-dtor. Same shape as ObjectBase_Dtor
 * (commit 9807e6c) and the other small CW C++ deleting dtors in this lib:
 *   1. if (this != NULL) demote *this back to the WarpZone vtable
 *      (&lbl_80411DD0) so any derived dtor chain that follows sees a
 *      cleanly typed base subobject. The WarpZone class owns no heap
 *      resources besides self.
 *   2. if the second arg (delete-flag, passed as a short) is > 0, call
 *      `dtor_8003AFB8(this)` (= MemoryManager_TimedFree placeholder) to
 *      release the allocation. Otherwise leave the storage alive.
 *   3. return this in r3 (C++ ABI deleting-dtor convention).
 *
 * CW 1.3.2 + #pragma exceptions on auto-emits matching extab body
 * (Large Frame: Yes / Saved GPR: r31, body 0x08080000 / 0x00000000) and
 * the extabindex entry alongside the .text body.
 *
 * The flag arg is sign-extended (`extsh. r0, r4`) before the > 0 compare,
 * which matches a `short` source-level parameter.
 *
 * Renames pending (HANDOFF.md):
 *   dtor_800AA888 -> WarpZone_Dtor
 */

extern void dtor_8003AFB8(void *);
extern char lbl_80411DD0[];  /* WarpZone vtable @ 0x80411DD0 */

#pragma exceptions on
void *dtor_800AA888(void *this, short flag) {
    if (this != 0) {
        *(char **)this = lbl_80411DD0;
        if (flag > 0) {
            dtor_8003AFB8(this);
        }
    }
    return this;
}
#pragma exceptions reset
