/*
 * RnkDisp_SetPosition @ 0x80249984 (size 0x70).
 *
 * Clamps newPosition to [0,7], compares against self->currentPos at +0x18,
 * and on change kicks the animation tween via fn_8020A734 (cookie at
 * self+0x28, mode 4, two sdata2 float constants).
 *
 * fn_8020A734 takes (cookie, mode, f1, f2): GPR and FPR args are numbered
 * independently, so this order gives the target's r3/r4/f1/f2 setup order.
 */

extern float lbl_806DBF64;
extern float lbl_806DBF68;
extern void fn_8020A734(void *cookie, int mode, float f1, float f2);

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
        fn_8020A734(*(void **)((char *)self + 0x28), 4, lbl_806DBF64, lbl_806DBF68);
    }
    *(int *)((char *)self + 0x18) = p;
}
#pragma exceptions reset
