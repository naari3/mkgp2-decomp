// Vec3 paired-single math helpers (GameCube PS unit).
//
// Reference: doldecomp/mkdd libs/dolphin/mtx/vec.c PSVECMag / PSVECDotProduct.
//
// Constants live in .sdata2 (shared pool):
//   lbl_806DC2A0 = 0.5f  (Newton-Raphson half coefficient)
//   lbl_806DC2A4 = 3.0f  (Newton-Raphson three coefficient)

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern float lbl_806DC2A0;
extern float lbl_806DC2A4;

// mwcc 1.3.2 collapses `beq label / ... / label: blr` to `beqlr` via peephole
// pass, even in `asm` functions. Emit the conditional branch as a raw 4-byte
// encoding so the peephole pass does not match. Encoding:
//   beq cr0, +0x20  =>  0x41820020
asm float Vec3_Magnitude(register const Vec3 *v) {
    nofralloc
    lfs       f4, lbl_806DC2A0
    psq_l     f0, 0(v), 0, 0
    ps_mul    f0, f0, f0
    lfs       f1, 8(v)
    fsubs     f2, f4, f4
    ps_madd   f1, f1, f1, f0
    ps_sum0   f1, f1, f0, f0
    fcmpu     cr0, f1, f2
    opword    0x41820020
    frsqrte   f0, f1
    lfs       f3, lbl_806DC2A4
    fmuls     f2, f0, f0
    fmuls     f0, f0, f4
    fnmsubs   f2, f2, f1, f3
    fmuls     f0, f2, f0
    fmuls     f1, f1, f0
    blr
}

asm float Vec3_Dot(register const Vec3 *a, register const Vec3 *b) {
    nofralloc
    psq_l     f2, 4(a), 0, 0
    psq_l     f3, 4(b), 0, 0
    ps_mul    f2, f2, f3
    psq_l     f5, 0(a), 0, 0
    psq_l     f4, 0(b), 0, 0
    ps_madd   f3, f5, f4, f2
    ps_sum0   f1, f3, f2, f2
    blr
}
