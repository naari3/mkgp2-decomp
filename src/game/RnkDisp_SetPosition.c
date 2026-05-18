/*
 * RnkDisp_SetPosition @ 0x80249984 (size 0x70, 28 instr).
 *
 * NonMatching: 4-instr scheduler reorder around the fn_8020A734 call. The
 * target emits arg setup in physical-register-class group order
 * (r3 cookie -> r4 mode -> f1 -> f2), whereas CW 1.3.2 on a stand-alone
 * caller emits the source-order grouping (f1 -> r4 -> f2 -> r3). Every
 * source-level idiom tried (named local cooking each arg ahead of the call,
 * arg expression reordering, prototype-less callee, short vs int mode arg,
 * shrinking arg evaluation chain) still produces the f1/r4/f2/r3 group order.
 * Falls into the "CW scheduler arg-class grouping" reproducible-only-with-
 * register-chase bucket (see docs/per_fn_matching_strategy.md §14.3).
 *
 * Semantically the C body is byte-equivalent: same clamp ordering, same
 * compare, same store, same callee signature, same sda2 float refs.
 *
 * Clamps newPosition to [0,7], compares against self->currentPos at +0x18,
 * and on change kicks the animation tween via fn_8020A734 with two sdata2
 * float constants (lbl_806DBF64 / lbl_806DBF68) and the cookie at self+0x28.
 * The 4th arg (literal 4) is the tween mode / duration. Called by
 * HUD_SetRacePosition (matched) via the fn_80271340 CDispInterface lookup.
 *
 * Notes:
 *  - sdata2 floats need scope:global + sized extern to keep CW on the single
 *    `lfs fX, lbl@sda21(r2)` path (it already chooses sda21 here for free).
 *  - extab/extabindex entry is auto-emitted under #pragma exceptions on
 *    (Has Elf Vector + Large Frame, saved GPR range r30-r31).
 *  - `int p = newPosition;` (vs reusing the arg) is the idiom that triggers
 *    `cmpwi r4, 0x8 / blt` in the prologue (target form) rather than the
 *    `cmpwi r31, 0x7 / ble` form. Keep it even in NonMatching state since it
 *    locks the first half of the function to byte-identical output.
 */

extern float lbl_806DBF64;
extern float lbl_806DBF68;
extern void fn_8020A734(double f1, double f2, void *cookie, int mode);

#pragma exceptions on
void RnkDisp_SetPosition(void *self, int newPosition) {
    int p = newPosition;
    if (p >= 8) {
        p = 7;
    }
    if (p < 0) {
        p = 0;
    }
    if (*(int *)((char *)self + 0x18) != p) {
        fn_8020A734((double)lbl_806DBF64, (double)lbl_806DBF68,
                    *(void **)((char *)self + 0x28), 4);
    }
    *(int *)((char *)self + 0x18) = p;
}
#pragma exceptions reset
