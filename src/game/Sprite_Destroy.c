/*
 * Sprite_Destroy @ 0x801A0684 (size 0x74, 29 instr).
 *
 * Sprite teardown helper with the C++ ABI delete-flag tail:
 *   1. NULL-check `self`. If non-NULL...
 *   2. If `self->resource_handle` (+0x28) is non-zero, call
 *      `fn_801A12F0()` (Sprite resource release / detach, 0-arg) and
 *      clear both `self->resource_handle` (+0x28) and the companion
 *      slot at +0x24. Order in the asm: store +0x28 first, then +0x24.
 *   3. Decrement the global live-sprite counter `lbl_806D16E4`
 *      (single `int` in .sbss, sda21-addressed). This decrement runs
 *      unconditionally on non-NULL `self`, even when the inner branch
 *      was skipped.
 *   4. If the delete-flag (short, sign-extended via `extsh.`) is > 0,
 *      release the allocation via `dtor_8003AFB8` (=
 *      MemoryManager_TimedFree). Otherwise leave storage alive (caller
 *      owns it, e.g. embedded sprite member of another object).
 *   5. Return `self` in r3 (preserves the C++ ABI deleting-dtor
 *      convention so callers can chain `bl <Sprite_Destroy>`).
 *
 * Frame: 0x10 stack, saves r30-r31 (Saved GPR range r30-r31). The
 * extab body at 0x800129C0 (`0x10080000`) is `Large Frame: Yes /
 * Saved GPR r30-r31`, the dtk auto group reports it as the matching
 * extab entry. extabindex entry sits at 0x80027548 (12 bytes).
 *
 * Register layout (CW 1.3.2 standard for 2-arg deleting-dtor):
 *   r30 = self           (mr. r30, r3 — also sets cr0 for the NULL test)
 *   r31 = deleteFlag     (mr r31, r4 — sign-extended later via extsh.)
 *
 * Approach: `#pragma exceptions on` lets CW 1.3.2 auto-emit the
 * matching extab / extabindex entries, mirroring the
 * InputObj_Ctor / LakituStart_Dtor recipe.
 *
 * Schedule note: target asm interleaves
 *   lwz r3, lbl_806D16E4@sda21(r0)
 *   extsh. r0, r31
 *   subi r0, r3, 1
 *   stw r0, lbl_806D16E4@sda21(r0)
 *   ble .L_801A06DC
 * — i.e. the sign-extend of the flag is scheduled between the load and
 * the subi/stw of the counter decrement. CW 1.3.2 emits this naturally
 * from the source order below (counter decrement first, then `flag > 0`
 * branch) because the two dependency chains are disjoint and the
 * scheduler pulls the independent `extsh.` ahead.
 */

extern int lbl_806D16E4;            /* .sbss live-sprite counter */
extern void fn_801A12F0(void *);    /* sprite resource release / detach, takes handle */
extern void dtor_8003AFB8(void *);  /* MemoryManager_TimedFree */

#pragma exceptions on
void *Sprite_Destroy(void *self, short deleteFlag) {
    void *handle;
    if (self != 0) {
        handle = *(void **)((char *)self + 0x28);
        if (handle != 0) {
            fn_801A12F0(handle);
            *(void **)((char *)self + 0x28) = 0;
            *(int *)((char *)self + 0x24) = 0;
        }
        lbl_806D16E4 = lbl_806D16E4 - 1;
        if (deleteFlag > 0) {
            dtor_8003AFB8(self);
        }
    }
    return self;
}
#pragma exceptions reset
