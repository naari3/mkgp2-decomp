#include "mkgp2_names.h"

#include "mtx.h"

#include <math.h>

#include "debug.h"

extern float __float_epsilon[];
#undef FLT_EPSILON
#define FLT_EPSILON (*__float_epsilon)
extern float lbl_806DCD88;
extern float lbl_806DCD8C;
extern float lbl_806DCD90;
extern float lbl_806DCD98;
extern float lbl_806DCDA0;
extern float lbl_806DCDA4;
extern float lbl_806DCDA8;
extern float lbl_806DCDAC;
extern float lbl_806DCDB0;
extern float lbl_806DCDB8;
extern float __float_min;
double sin(double);
void _savegpr_27();
void _restgpr_27();
double atan2(double, double);
double asin(double);
double acos(double);
f32 PSVECSquareMag(Vec3*);
double cos(double);

#define EPSILON 0.0000000001f
#define FLOAT_MIN 1.1754943E-38f

HSD_ObjAllocData HSD_Mtx_804C2310;
HSD_ObjAllocData HSD_Mtx_804C233C;

/// Calculates the determinant of the top 3x3 section of a 3x4 matrix
static inline f32 HSD_CalcDeterminantMatrix3x4(Mtx m)
{
    return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] +
           m[0][2] * m[1][0] * m[2][1] - m[2][0] * m[1][1] * m[0][2] -
           m[1][0] * m[0][1] * m[2][2] - m[0][0] * m[2][1] * m[1][2];
}


#ifdef MUST_MATCH
asm void HSD_MtxInverseConcat(Mtx inv, Mtx src, Mtx dest)
{
    nofralloc
    stwu r1, -0xd0(r1)
    mflr r0
    stw r0, 0xd4(r1)
    stfd f31, 0xc0(r1)
    psq_st f31, 0xc8(r1), 0, 0
    stfd f30, 0xb0(r1)
    psq_st f30, 0xb8(r1), 0, 0
    stfd f29, 0xa0(r1)
    psq_st f29, 0xa8(r1), 0, 0
    stfd f28, 0x90(r1)
    psq_st f28, 0x98(r1), 0, 0
    stfd f27, 0x80(r1)
    psq_st f27, 0x88(r1), 0, 0
    stfd f26, 0x70(r1)
    psq_st f26, 0x78(r1), 0, 0
    stfd f25, 0x60(r1)
    psq_st f25, 0x68(r1), 0, 0
    stfd f24, 0x50(r1)
    psq_st f24, 0x58(r1), 0, 0
    stfd f23, 0x40(r1)
    psq_st f23, 0x48(r1), 0, 0
    lfs f7, 0x18(r3)
    lfs f23, 0x4(r3)
    lfs f3, 0x10(r3)
    fmuls f8, f23, f7
    lfs f24, 0x20(r3)
    lfs f1, 0x14(r3)
    fmuls f10, f3, f23
    lfs f6, 0x0(r3)
    lfs f2, 0x8(r3)
    fmuls f11, f6, f1
    lfs f4, 0x28(r3)
    fmuls f9, f24, f8
    lfs f5, 0x24(r3)
    fmuls f0, f2, f3
    lfs f12, lbl_806DCD88(r2)
    fmadds f13, f4, f11, f9
    fmuls f9, f24, f1
    fmuls f29, f6, f5
    fmadds f13, f5, f0, f13
    fnmsubs f13, f2, f9, f13
    fnmsubs f13, f4, f10, f13
    fnmsubs f25, f7, f29, f13
    fcmpu cr0, f12, f25
    bne HSD_MtxInverseConcat_L_802D62A4
    li r3, 0x0
    b HSD_MtxInverseConcat_L_802D65C0
HSD_MtxInverseConcat_L_802D62A4:
    lfs f13, lbl_806DCD8C(r2)
    fmuls f28, f5, f7
    fmuls f27, f5, f2
    lfs f12, 0x1c(r3)
    fdivs f30, f13, f25
    lfs f13, 0xc(r3)
    lfs f31, 0x2c(r3)
    cmplw r3, r5
    fmuls f26, f24, f7
    fmuls f25, f24, f2
    fnmsubs f24, f24, f23, f29
    fmsubs f29, f1, f4, f28
    fnmsubs f28, f23, f4, f27
    fnmsubs f27, f3, f4, f26
    fmsubs f26, f6, f4, f25
    fmsubs f25, f3, f5, f9
    fneg f24, f24
    fmuls f3, f30, f29
    fmuls f4, f30, f28
    fmuls f5, f30, f27
    fmuls f9, f30, f26
    fmuls f29, f30, f25
    fmuls f28, f30, f24
    fnmsubs f26, f1, f2, f8
    fnmsubs f25, f6, f7, f0
    fsubs f24, f11, f10
    fneg f10, f3
    fmuls f1, f4, f12
    fneg f8, f5
    fmuls f2, f9, f12
    fneg f7, f29
    fmuls f6, f28, f12
    fmuls f0, f30, f26
    fmsubs f11, f10, f13, f1
    fmuls f1, f30, f25
    fmsubs f10, f8, f13, f2
    fmuls f2, f30, f24
    fmsubs f8, f7, f13, f6
    fnmsubs f6, f0, f31, f11
    fnmsubs f7, f1, f31, f10
    fnmsubs f8, f2, f31, f8
    beq HSD_MtxInverseConcat_L_802D6354
    cmplw r4, r5
    bne HSD_MtxInverseConcat_L_802D6460
HSD_MtxInverseConcat_L_802D6354:
    lfs f10, 0x10(r4)
    addi r3, r1, 0x8
    lfs f13, 0x0(r4)
    fmuls f12, f4, f10
    lfs f24, 0x20(r4)
    fmuls f11, f9, f10
    fmuls f10, f28, f10
    fmadds f12, f3, f13, f12
    fmadds f11, f5, f13, f11
    fmadds f10, f29, f13, f10
    fmadds f13, f0, f24, f12
    fmadds f31, f1, f24, f11
    fmadds f12, f2, f24, f10
    stfs f13, 0x8(r1)
    lfs f10, 0x14(r4)
    lfs f24, 0x4(r4)
    fmuls f13, f4, f10
    lfs f25, 0x24(r4)
    fmuls f11, f9, f10
    fmuls f10, f28, f10
    fmadds f13, f3, f24, f13
    fmadds f11, f5, f24, f11
    fmadds f10, f29, f24, f10
    fmadds f13, f0, f25, f13
    fmadds f30, f1, f25, f11
    fmadds f11, f2, f25, f10
    stfs f13, 0xc(r1)
    lfs f10, 0x18(r4)
    lfs f25, 0x8(r4)
    fmuls f24, f4, f10
    lfs f26, 0x28(r4)
    fmuls f13, f9, f10
    fmuls f10, f28, f10
    fmadds f24, f3, f25, f24
    fmadds f13, f5, f25, f13
    fmadds f10, f29, f25, f10
    fmadds f24, f0, f26, f24
    fmadds f13, f1, f26, f13
    fmadds f10, f2, f26, f10
    stfs f24, 0x10(r1)
    lfs f26, 0x1c(r4)
    lfs f25, 0xc(r4)
    fmuls f27, f4, f26
    lfs f24, 0x2c(r4)
    fmuls f9, f9, f26
    mr r4, r5
    fmuls f4, f28, f26
    stfs f31, 0x18(r1)
    fmadds f28, f3, f25, f27
    stfs f30, 0x1c(r1)
    fmadds f5, f5, f25, f9
    fmadds f3, f29, f25, f4
    stfs f13, 0x20(r1)
    fmadds f4, f0, f24, f28
    fmadds f1, f1, f24, f5
    stfs f12, 0x28(r1)
    fmadds f0, f2, f24, f3
    fadds f2, f6, f4
    stfs f11, 0x2c(r1)
    fadds f1, f7, f1
    fadds f0, f8, f0
    stfs f10, 0x30(r1)
    stfs f2, 0x14(r1)
    stfs f1, 0x24(r1)
    stfs f0, 0x34(r1)
    bl PSMTXCopy
    b HSD_MtxInverseConcat_L_802D65BC
HSD_MtxInverseConcat_L_802D6460:
    lfs f10, 0x10(r4)
    lfs f11, 0x0(r4)
    fmuls f10, f4, f10
    lfs f12, 0x20(r4)
    fmadds f10, f3, f11, f10
    fmadds f10, f0, f12, f10
    stfs f10, 0x0(r5)
    lfs f10, 0x14(r4)
    lfs f11, 0x4(r4)
    fmuls f10, f4, f10
    lfs f12, 0x24(r4)
    fmadds f10, f3, f11, f10
    fmadds f10, f0, f12, f10
    stfs f10, 0x4(r5)
    lfs f10, 0x18(r4)
    lfs f11, 0x8(r4)
    fmuls f10, f4, f10
    lfs f12, 0x28(r4)
    fmadds f10, f3, f11, f10
    fmadds f10, f0, f12, f10
    stfs f10, 0x8(r5)
    lfs f10, 0x1c(r4)
    lfs f11, 0xc(r4)
    fmuls f4, f4, f10
    lfs f10, 0x2c(r4)
    fmadds f3, f3, f11, f4
    fmadds f0, f0, f10, f3
    fadds f0, f6, f0
    stfs f0, 0xc(r5)
    lfs f0, 0x10(r4)
    lfs f3, 0x0(r4)
    fmuls f0, f9, f0
    lfs f4, 0x20(r4)
    fmadds f0, f5, f3, f0
    fmadds f0, f1, f4, f0
    stfs f0, 0x10(r5)
    lfs f0, 0x14(r4)
    lfs f3, 0x4(r4)
    fmuls f0, f9, f0
    lfs f4, 0x24(r4)
    fmadds f0, f5, f3, f0
    fmadds f0, f1, f4, f0
    stfs f0, 0x14(r5)
    lfs f0, 0x18(r4)
    lfs f3, 0x8(r4)
    fmuls f0, f9, f0
    lfs f4, 0x28(r4)
    fmadds f0, f5, f3, f0
    fmadds f0, f1, f4, f0
    stfs f0, 0x18(r5)
    lfs f0, 0x1c(r4)
    lfs f3, 0xc(r4)
    fmuls f0, f9, f0
    lfs f4, 0x2c(r4)
    fmadds f0, f5, f3, f0
    fmadds f0, f1, f4, f0
    fadds f0, f7, f0
    stfs f0, 0x1c(r5)
    lfs f0, 0x10(r4)
    lfs f1, 0x0(r4)
    fmuls f0, f28, f0
    lfs f3, 0x20(r4)
    fmadds f0, f29, f1, f0
    fmadds f0, f2, f3, f0
    stfs f0, 0x20(r5)
    lfs f0, 0x14(r4)
    lfs f1, 0x4(r4)
    fmuls f0, f28, f0
    lfs f3, 0x24(r4)
    fmadds f0, f29, f1, f0
    fmadds f0, f2, f3, f0
    stfs f0, 0x24(r5)
    lfs f0, 0x18(r4)
    lfs f1, 0x8(r4)
    fmuls f0, f28, f0
    lfs f3, 0x28(r4)
    fmadds f0, f29, f1, f0
    fmadds f0, f2, f3, f0
    stfs f0, 0x28(r5)
    lfs f0, 0x1c(r4)
    lfs f1, 0xc(r4)
    fmuls f0, f28, f0
    lfs f3, 0x2c(r4)
    fmadds f0, f29, f1, f0
    fmadds f0, f2, f3, f0
    fadds f0, f8, f0
    stfs f0, 0x2c(r5)
HSD_MtxInverseConcat_L_802D65BC:
    li r3, 0x1
HSD_MtxInverseConcat_L_802D65C0:
    psq_l f31, 0xc8(r1), 0, 0
    lfd f31, 0xc0(r1)
    psq_l f30, 0xb8(r1), 0, 0
    lfd f30, 0xb0(r1)
    psq_l f29, 0xa8(r1), 0, 0
    lfd f29, 0xa0(r1)
    psq_l f28, 0x98(r1), 0, 0
    lfd f28, 0x90(r1)
    psq_l f27, 0x88(r1), 0, 0
    lfd f27, 0x80(r1)
    psq_l f26, 0x78(r1), 0, 0
    lfd f26, 0x70(r1)
    psq_l f25, 0x68(r1), 0, 0
    lfd f25, 0x60(r1)
    psq_l f24, 0x58(r1), 0, 0
    lfd f24, 0x50(r1)
    psq_l f23, 0x48(r1), 0, 0
    lwz r0, 0xd4(r1)
    lfd f23, 0x40(r1)
    mtlr r0
    addi r1, r1, 0xd0
    blr
}
#else
void HSD_MtxInverseConcat(Mtx inv, Mtx src, Mtx dest)
{
    Mtx m;
    f32 det;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;
    f32 temp5;
    f32 temp6;
    f32 temp7;
    f32 temp8;
    f32 temp9;
    f32 temp10;
    f32 temp11;
    f32 temp12;
    f32 new_var; ///< @todo try to get rid of this

    det = HSD_CalcDeterminantMatrix3x4(inv);

    if (fabsf_bitwise(det) < EPSILON) {
        if (src != dest) {
            MTXCopy(src, dest);
        }
    } else {
        det = 1.0f / det;
        temp1 = ((inv[1][1] * inv[2][2]) - (inv[2][1] * inv[1][2])) * det;
        temp2 = (-((inv[0][1] * inv[2][2]) - (inv[2][1] * inv[0][2]))) * det;
        new_var = inv[1][1];
        temp3 = (-((inv[1][0] * inv[2][2]) - (inv[2][0] * inv[1][2]))) * det;
        temp7 = ((inv[0][1] * inv[1][2]) - (new_var * inv[0][2])) * det;
        temp4 = ((inv[0][0] * inv[2][2]) - (inv[2][0] * inv[0][2])) * det;
        temp8 = (-((inv[0][0] * inv[1][2]) - (inv[1][0] * inv[0][2]))) * det;
        temp5 = ((inv[1][0] * inv[2][1]) - (inv[2][0] * new_var)) * det;
        temp6 = (-((inv[0][0] * inv[2][1]) - (inv[2][0] * inv[0][1]))) * det;
        temp9 = ((inv[0][0] * inv[1][1]) - (inv[1][0] * inv[0][1])) * det;
        temp10 = -((temp7 * inv[2][3]) -
                   (((-temp1) * inv[0][3]) - (temp2 * inv[1][3])));
        temp11 = -((temp8 * inv[2][3]) -
                   (((-temp3) * inv[0][3]) - (temp4 * inv[1][3])));
        temp12 = -((temp9 * inv[2][3]) -
                   (((-temp5) * (new_var = inv[0][3])) - (temp6 * inv[1][3])));

        if (inv == dest || src == dest) {
            m[0][0] =
                temp7 * src[2][0] + (temp1 * src[0][0] + temp2 * src[1][0]);
            m[0][1] =
                temp7 * src[2][1] + (temp1 * src[0][1] + temp2 * src[1][1]);
            m[0][2] =
                temp7 * src[2][2] + (temp1 * src[0][2] + temp2 * src[1][2]);
            m[0][3] = temp7 * src[2][3] +
                      (temp1 * src[0][3] + temp2 * src[1][3]) + temp10;
            m[1][0] =
                temp8 * src[2][0] + (temp3 * src[0][0] + temp4 * src[1][0]);
            m[1][1] =
                temp8 * src[2][1] + (temp3 * src[0][1] + temp4 * src[1][1]);
            m[1][2] =
                temp8 * src[2][2] + (temp3 * src[0][2] + temp4 * src[1][2]);
            m[1][3] = temp8 * src[2][3] +
                      (temp3 * src[0][3] + temp4 * src[1][3]) + temp11;
            m[2][0] =
                temp9 * src[2][0] + (temp5 * src[0][0] + temp6 * src[1][0]);
            m[2][1] =
                temp9 * src[2][1] + (temp5 * src[0][1] + temp6 * src[1][1]);
            m[2][2] =
                temp9 * src[2][2] + (temp5 * src[0][2] + temp6 * src[1][2]);
            m[2][3] = temp9 * src[2][3] +
                      (temp5 * src[0][3] + temp6 * src[1][3]) + temp12;

            MTXCopy(m, dest);
        } else {
            dest[0][0] =
                temp7 * src[2][0] + (temp1 * src[0][0] + temp2 * src[1][0]);
            dest[0][1] =
                temp7 * src[2][1] + (temp1 * src[0][1] + temp2 * src[1][1]);
            dest[0][2] =
                temp7 * src[2][2] + (temp1 * src[0][2] + temp2 * src[1][2]);
            dest[0][3] = temp7 * src[2][3] +
                         (temp1 * src[0][3] + temp2 * src[1][3]) + temp10;
            dest[1][0] =
                temp8 * src[2][0] + (temp3 * src[0][0] + temp4 * src[1][0]);
            dest[1][1] =
                temp8 * src[2][1] + (temp3 * src[0][1] + temp4 * src[1][1]);
            dest[1][2] =
                temp8 * src[2][2] + (temp3 * src[0][2] + temp4 * src[1][2]);
            dest[1][3] = temp8 * src[2][3] +
                         (temp3 * src[0][3] + temp4 * src[1][3]) + temp11;
            dest[2][0] =
                temp9 * src[2][0] + (temp5 * src[0][0] + temp6 * src[1][0]);
            dest[2][1] =
                temp9 * src[2][1] + (temp5 * src[0][1] + temp6 * src[1][1]);
            dest[2][2] =
                temp9 * src[2][2] + (temp5 * src[0][2] + temp6 * src[1][2]);
            dest[2][3] = temp9 * src[2][3] +
                         (temp5 * src[0][3] + temp6 * src[1][3]) + temp12;
        }
    }
}
#endif


static inline f32 calcVal(f32 x, f32 y)
{
    if (fabsf_bitwise(x) <= FLOAT_MIN) {
        if (y >= 0) {
            return M_PI / 2;
        } else {
            return -M_PI / 2;
        }
    } else {
        return atan2f(y, x);
    }
}

#ifdef MUST_MATCH
asm void HSD_MtxGetRotation(Mtx m, Vec3* vec)
{
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stfd f30, 0x20(r1)
    psq_st f30, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    lfs f1, lbl_806DCD88(r2)
    lfs f2, 0x0(r3)
    mr r31, r4
    lfs f0, 0x10(r3)
    fmuls f2, f2, f2
    lfs f3, 0x20(r3)
    fmuls f0, f0, f0
    fmuls f3, f3, f3
    fadds f0, f2, f0
    fadds f0, f3, f0
    fcmpo cr0, f0, f1
    ble HSD_MtxGetRotation_L_802D66BC
    frsqrte f2, f0
    lfd f4, lbl_806DCD90(r2)
    lfd f3, lbl_806DCD98(r2)
    fmul f1, f2, f2
    fmul f2, f4, f2
    fnmsub f1, f0, f1, f3
    fmul f2, f2, f1
    fmul f1, f2, f2
    fmul f2, f4, f2
    fnmsub f1, f0, f1, f3
    fmul f2, f2, f1
    fmul f1, f2, f2
    fmul f2, f4, f2
    fnmsub f1, f0, f1, f3
    fmul f1, f2, f1
    fmul f0, f0, f1
    frsp f0, f0
    stfs f0, 0x10(r1)
    lfs f0, 0x10(r1)
HSD_MtxGetRotation_L_802D66BC:
    lis r3, __float_min@ha
    lfs f1, __float_min@l(r3)
    fcmpo cr0, f0, f1
    blt HSD_MtxGetRotation_L_802D6910
    lfs f2, 0x4(r30)
    lfs f1, 0x14(r30)
    fmuls f3, f2, f2
    lfs f4, 0x24(r30)
    fmuls f2, f1, f1
    lfs f1, lbl_806DCD88(r2)
    fmuls f4, f4, f4
    fadds f2, f3, f2
    fadds f31, f4, f2
    fcmpo cr0, f31, f1
    ble HSD_MtxGetRotation_L_802D6744
    frsqrte f2, f31
    lfd f4, lbl_806DCD90(r2)
    lfd f3, lbl_806DCD98(r2)
    fmul f1, f2, f2
    fmul f2, f4, f2
    fnmsub f1, f31, f1, f3
    fmul f2, f2, f1
    fmul f1, f2, f2
    fmul f2, f4, f2
    fnmsub f1, f31, f1, f3
    fmul f2, f2, f1
    fmul f1, f2, f2
    fmul f2, f4, f2
    fnmsub f1, f31, f1, f3
    fmul f1, f2, f1
    fmul f1, f31, f1
    frsp f1, f1
    stfs f1, 0xc(r1)
    lfs f31, 0xc(r1)
HSD_MtxGetRotation_L_802D6744:
    lis r3, __float_min@ha
    lfs f1, __float_min@l(r3)
    fcmpo cr0, f31, f1
    blt HSD_MtxGetRotation_L_802D6910
    lfs f2, 0x8(r30)
    lfs f1, 0x18(r30)
    fmuls f3, f2, f2
    lfs f4, 0x28(r30)
    fmuls f2, f1, f1
    lfs f1, lbl_806DCD88(r2)
    fmuls f4, f4, f4
    fadds f2, f3, f2
    fadds f30, f4, f2
    fcmpo cr0, f30, f1
    ble HSD_MtxGetRotation_L_802D67CC
    frsqrte f2, f30
    lfd f4, lbl_806DCD90(r2)
    lfd f3, lbl_806DCD98(r2)
    fmul f1, f2, f2
    fmul f2, f4, f2
    fnmsub f1, f30, f1, f3
    fmul f2, f2, f1
    fmul f1, f2, f2
    fmul f2, f4, f2
    fnmsub f1, f30, f1, f3
    fmul f2, f2, f1
    fmul f1, f2, f2
    fmul f2, f4, f2
    fnmsub f1, f30, f1, f3
    fmul f1, f2, f1
    fmul f1, f30, f1
    frsp f1, f1
    stfs f1, 0x8(r1)
    lfs f30, 0x8(r1)
HSD_MtxGetRotation_L_802D67CC:
    lis r3, __float_min@ha
    lfs f1, __float_min@l(r3)
    fcmpo cr0, f30, f1
    blt HSD_MtxGetRotation_L_802D6910
    lfs f1, 0x20(r30)
    lfs f2, lbl_806DCD8C(r2)
    fneg f1, f1
    fdivs f1, f1, f0
    fcmpo cr0, f1, f2
    cror eq, gt, eq
    bne HSD_MtxGetRotation_L_802D6800
    lfs f0, lbl_806DCDA0(r2)
    b HSD_MtxGetRotation_L_802D6820
HSD_MtxGetRotation_L_802D6800:
    lfs f0, lbl_806DCDA4(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne HSD_MtxGetRotation_L_802D6818
    lfs f0, lbl_806DCDA8(r2)
    b HSD_MtxGetRotation_L_802D6820
HSD_MtxGetRotation_L_802D6818:
    bl asin
    frsp f0, f1
HSD_MtxGetRotation_L_802D6820:
    stfs f0, 0x4(r31)
    lfs f1, 0x4(r31)
    bl cos
    lis r3, __float_min@ha
    frsp f1, f1
    lfs f0, __float_min@l(r3)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne HSD_MtxGetRotation_L_802D68C8
    lfs f0, 0x28(r30)
    lfs f1, 0x24(r30)
    fdivs f2, f0, f30
    lfs f0, lbl_806DCD88(r2)
    fdivs f1, f1, f31
    fcmpu cr0, f0, f2
    bne HSD_MtxGetRotation_L_802D687C
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne HSD_MtxGetRotation_L_802D6874
    lfs f0, lbl_806DCDA0(r2)
    b HSD_MtxGetRotation_L_802D6884
HSD_MtxGetRotation_L_802D6874:
    lfs f0, lbl_806DCDA8(r2)
    b HSD_MtxGetRotation_L_802D6884
HSD_MtxGetRotation_L_802D687C:
    bl atan2
    frsp f0, f1
HSD_MtxGetRotation_L_802D6884:
    stfs f0, 0x0(r31)
    lfs f0, lbl_806DCD88(r2)
    lfs f2, 0x0(r30)
    lfs f1, 0x10(r30)
    fcmpu cr0, f0, f2
    bne HSD_MtxGetRotation_L_802D68B8
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne HSD_MtxGetRotation_L_802D68B0
    lfs f0, lbl_806DCDA0(r2)
    b HSD_MtxGetRotation_L_802D68C0
HSD_MtxGetRotation_L_802D68B0:
    lfs f0, lbl_806DCDA8(r2)
    b HSD_MtxGetRotation_L_802D68C0
HSD_MtxGetRotation_L_802D68B8:
    bl atan2
    frsp f0, f1
HSD_MtxGetRotation_L_802D68C0:
    stfs f0, 0x8(r31)
    b HSD_MtxGetRotation_L_802D6920
HSD_MtxGetRotation_L_802D68C8:
    lfs f2, 0x14(r30)
    lfs f0, lbl_806DCD88(r2)
    lfs f1, 0x4(r30)
    fcmpu cr0, f0, f2
    bne HSD_MtxGetRotation_L_802D68F8
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne HSD_MtxGetRotation_L_802D68F0
    lfs f0, lbl_806DCDA0(r2)
    b HSD_MtxGetRotation_L_802D6900
HSD_MtxGetRotation_L_802D68F0:
    lfs f0, lbl_806DCDA8(r2)
    b HSD_MtxGetRotation_L_802D6900
HSD_MtxGetRotation_L_802D68F8:
    bl atan2
    frsp f0, f1
HSD_MtxGetRotation_L_802D6900:
    stfs f0, 0x0(r31)
    lfs f0, lbl_806DCD88(r2)
    stfs f0, 0x8(r31)
    b HSD_MtxGetRotation_L_802D6920
HSD_MtxGetRotation_L_802D6910:
    lfs f0, lbl_806DCD88(r2)
    stfs f0, 0x0(r31)
    stfs f0, 0x4(r31)
    stfs f0, 0x8(r31)
HSD_MtxGetRotation_L_802D6920:
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    psq_l f30, 0x28(r1), 0, 0
    lfd f30, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r0, 0x44(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}
#else
void HSD_MtxGetRotation(Mtx m, Vec3* vec)
{
    f32 length0;
    f32 length1;
    f32 length2;
    f32 testVal_1;
    f32 val_01;

    length0 = sqrtf(m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]);
    if (!(length0 < FLOAT_MIN)) {
        length1 =
            sqrtf(m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1]);
        if (!(length1 < FLOAT_MIN)) {
            length2 = sqrtf(m[0][2] * m[0][2] + m[1][2] * m[1][2] +
                            m[2][2] * m[2][2]);
            if (!(length2 < FLOAT_MIN)) {
                testVal_1 = -m[2][0];
                testVal_1 /= length0;

                if (testVal_1 >= 1.0f) {
                    val_01 = M_PI / 2;
                } else if (testVal_1 <= -1) {
                    val_01 = -M_PI / 2;
                } else {
                    val_01 = asinf(testVal_1);
                }

                vec->y = val_01;

                if (cosf(vec->y) >= FLOAT_MIN) {
                    f32 testVal_2_pre = m[2][2] / length2;
                    f32 testVal_3_pre = m[2][1] / length1;

                    vec->x = calcVal(testVal_2_pre, testVal_3_pre);
                    vec->z = calcVal(m[0][0], m[1][0]);
                    return;
                }

                vec->x = calcVal(m[1][1], m[0][1]);
                vec->z = 0;
                return;
            }
        }
    }

    vec->x = 0;
    vec->y = 0;
    vec->z = 0;
}
#endif

/// These parameters may not be right
void HSD_MtxGetTranslate(Mtx mat, Vec3* vec)
{
    vec->x = mat[0][3];
    vec->y = mat[1][3];
    vec->z = mat[2][3];
}

#ifdef MUST_MATCH
asm void HSD_MtxGetScale(Mtx arg0, Vec3* arg1)
{
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stw r31, 0x5c(r1)
    mr r31, r4
    stw r30, 0x58(r1)
    mr r30, r3
    lfs f0, 0x0(r3)
    addi r3, r1, 0x40
    stfs f0, 0x40(r1)
    lfs f0, 0x10(r30)
    stfs f0, 0x44(r1)
    lfs f0, 0x20(r30)
    stfs f0, 0x48(r1)
    bl PSVECSquareMag
    lfs f0, lbl_806DCDAC(r2)
    fcmpo cr0, f1, f0
    ble HSD_MtxGetScale_L_802D6CFC
    lfs f2, lbl_806DCD8C(r2)
    lfs f0, lbl_806DCD88(r2)
    fdivs f1, f2, f1
    fcmpo cr0, f1, f0
    ble HSD_MtxGetScale_L_802D6A0C
    frsqrte f2, f1
    lfd f4, lbl_806DCD90(r2)
    lfd f3, lbl_806DCD98(r2)
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f2, f2, f0
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f2, f2, f0
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f0, f2, f0
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x18(r1)
    lfs f1, 0x18(r1)
HSD_MtxGetScale_L_802D6A0C:
    lfs f0, lbl_806DCD8C(r2)
    addi r3, r1, 0x40
    mr r4, r3
    fdivs f0, f0, f1
    stfs f0, 0x0(r31)
    bl PSVECScale
    lfs f0, 0x4(r30)
    addi r3, r1, 0x40
    addi r4, r1, 0x34
    stfs f0, 0x34(r1)
    lfs f0, 0x14(r30)
    stfs f0, 0x38(r1)
    lfs f0, 0x24(r30)
    stfs f0, 0x3c(r1)
    bl Vec3_Dot
    addi r3, r1, 0x40
    addi r4, r1, 0x1c
    bl PSVECScale
    addi r3, r1, 0x34
    addi r4, r1, 0x1c
    mr r5, r3
    bl Vec3_Subtract
    addi r3, r1, 0x34
    bl PSVECSquareMag
    lfs f0, lbl_806DCDAC(r2)
    fcmpo cr0, f1, f0
    ble HSD_MtxGetScale_L_802D6C34
    lfs f2, lbl_806DCD8C(r2)
    lfs f0, lbl_806DCD88(r2)
    fdivs f1, f2, f1
    fcmpo cr0, f1, f0
    ble HSD_MtxGetScale_L_802D6AD8
    frsqrte f2, f1
    lfd f4, lbl_806DCD90(r2)
    lfd f3, lbl_806DCD98(r2)
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f2, f2, f0
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f2, f2, f0
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f0, f2, f0
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x14(r1)
    lfs f1, 0x14(r1)
HSD_MtxGetScale_L_802D6AD8:
    lfs f0, lbl_806DCD8C(r2)
    addi r3, r1, 0x34
    mr r4, r3
    fdivs f0, f0, f1
    stfs f0, 0x4(r31)
    bl PSVECScale
    lfs f0, 0x8(r30)
    addi r3, r1, 0x34
    addi r4, r1, 0x28
    stfs f0, 0x28(r1)
    lfs f0, 0x18(r30)
    stfs f0, 0x2c(r1)
    lfs f0, 0x28(r30)
    stfs f0, 0x30(r1)
    bl Vec3_Dot
    addi r3, r1, 0x34
    addi r4, r1, 0x1c
    bl PSVECScale
    addi r3, r1, 0x28
    addi r4, r1, 0x1c
    mr r5, r3
    bl Vec3_Subtract
    addi r3, r1, 0x40
    addi r4, r1, 0x28
    bl Vec3_Dot
    addi r3, r1, 0x40
    addi r4, r1, 0x1c
    bl PSVECScale
    addi r3, r1, 0x28
    addi r4, r1, 0x1c
    mr r5, r3
    bl Vec3_Subtract
    addi r3, r1, 0x28
    bl PSVECSquareMag
    lfs f0, lbl_806DCDAC(r2)
    fcmpo cr0, f1, f0
    ble HSD_MtxGetScale_L_802D6C28
    lfs f0, lbl_806DCD88(r2)
    fcmpo cr0, f1, f0
    ble HSD_MtxGetScale_L_802D6BC4
    frsqrte f2, f1
    lfd f4, lbl_806DCD90(r2)
    lfd f3, lbl_806DCD98(r2)
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f2, f2, f0
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f2, f2, f0
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f0, f2, f0
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x10(r1)
    lfs f1, 0x10(r1)
HSD_MtxGetScale_L_802D6BC4:
    stfs f1, 0x8(r31)
    addi r3, r1, 0x34
    addi r4, r1, 0x28
    addi r5, r1, 0x1c
    bl PSVECCrossProduct
    addi r3, r1, 0x40
    addi r4, r1, 0x1c
    bl Vec3_Dot
    lfd f0, lbl_806DCDB0(r2)
    fcmpo cr0, f1, f0
    bge HSD_MtxGetScale_L_802D6E24
    lfs f0, 0x0(r31)
    lfd f1, lbl_806DCDB8(r2)
    fmul f0, f0, f1
    frsp f0, f0
    stfs f0, 0x0(r31)
    lfs f0, 0x4(r31)
    fmul f0, f0, f1
    frsp f0, f0
    stfs f0, 0x4(r31)
    lfs f0, 0x8(r31)
    fmul f0, f0, f1
    frsp f0, f0
    stfs f0, 0x8(r31)
    b HSD_MtxGetScale_L_802D6E24
HSD_MtxGetScale_L_802D6C28:
    lfs f0, lbl_806DCD88(r2)
    stfs f0, 0x8(r31)
    b HSD_MtxGetScale_L_802D6E24
HSD_MtxGetScale_L_802D6C34:
    lfs f0, lbl_806DCD88(r2)
    addi r3, r1, 0x40
    addi r4, r1, 0x28
    stfs f0, 0x4(r31)
    lfs f0, 0x8(r30)
    stfs f0, 0x28(r1)
    lfs f0, 0x18(r30)
    stfs f0, 0x2c(r1)
    lfs f0, 0x28(r30)
    stfs f0, 0x30(r1)
    bl Vec3_Dot
    addi r3, r1, 0x40
    addi r4, r1, 0x1c
    bl PSVECScale
    addi r3, r1, 0x28
    addi r4, r1, 0x1c
    mr r5, r3
    bl Vec3_Subtract
    addi r3, r1, 0x28
    bl PSVECSquareMag
    lfs f0, lbl_806DCDAC(r2)
    fcmpo cr0, f1, f0
    ble HSD_MtxGetScale_L_802D6CF0
    lfs f0, lbl_806DCD88(r2)
    fcmpo cr0, f1, f0
    ble HSD_MtxGetScale_L_802D6CE8
    frsqrte f2, f1
    lfd f4, lbl_806DCD90(r2)
    lfd f3, lbl_806DCD98(r2)
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f2, f2, f0
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f2, f2, f0
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f0, f2, f0
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0xc(r1)
    lfs f1, 0xc(r1)
HSD_MtxGetScale_L_802D6CE8:
    stfs f1, 0x8(r31)
    b HSD_MtxGetScale_L_802D6E24
HSD_MtxGetScale_L_802D6CF0:
    lfs f0, lbl_806DCD88(r2)
    stfs f0, 0x8(r31)
    b HSD_MtxGetScale_L_802D6E24
HSD_MtxGetScale_L_802D6CFC:
    lfs f0, lbl_806DCD88(r2)
    addi r3, r1, 0x34
    stfs f0, 0x0(r31)
    lfs f0, 0x4(r30)
    stfs f0, 0x34(r1)
    lfs f0, 0x14(r30)
    stfs f0, 0x38(r1)
    lfs f0, 0x24(r30)
    stfs f0, 0x3c(r1)
    bl PSVECSquareMag
    lfs f0, lbl_806DCDAC(r2)
    fcmpo cr0, f1, f0
    ble HSD_MtxGetScale_L_802D6DF8
    lfs f2, lbl_806DCD8C(r2)
    lfs f0, lbl_806DCD88(r2)
    fdivs f1, f2, f1
    fcmpo cr0, f1, f0
    ble HSD_MtxGetScale_L_802D6D90
    frsqrte f2, f1
    lfd f4, lbl_806DCD90(r2)
    lfd f3, lbl_806DCD98(r2)
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f2, f2, f0
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f2, f2, f0
    fmul f0, f2, f2
    fmul f2, f4, f2
    fnmsub f0, f1, f0, f3
    fmul f0, f2, f0
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x8(r1)
    lfs f1, 0x8(r1)
HSD_MtxGetScale_L_802D6D90:
    lfs f0, lbl_806DCD8C(r2)
    addi r3, r1, 0x34
    mr r4, r3
    fdivs f0, f0, f1
    stfs f0, 0x4(r31)
    bl PSVECScale
    lfs f0, 0x8(r30)
    addi r3, r1, 0x34
    addi r4, r1, 0x28
    stfs f0, 0x28(r1)
    lfs f0, 0x18(r30)
    stfs f0, 0x2c(r1)
    lfs f0, 0x28(r30)
    stfs f0, 0x30(r1)
    bl Vec3_Dot
    addi r3, r1, 0x34
    addi r4, r1, 0x1c
    bl PSVECScale
    addi r3, r1, 0x28
    addi r4, r1, 0x1c
    mr r5, r3
    bl Vec3_Subtract
    addi r3, r1, 0x28
    bl Vec3_Magnitude
    stfs f1, 0x8(r31)
    b HSD_MtxGetScale_L_802D6E24
HSD_MtxGetScale_L_802D6DF8:
    lfs f0, lbl_806DCD88(r2)
    addi r3, r1, 0x28
    stfs f0, 0x4(r31)
    lfs f0, 0x8(r30)
    stfs f0, 0x28(r1)
    lfs f0, 0x18(r30)
    stfs f0, 0x2c(r1)
    lfs f0, 0x28(r30)
    stfs f0, 0x30(r1)
    bl Vec3_Magnitude
    stfs f1, 0x8(r31)
HSD_MtxGetScale_L_802D6E24:
    lwz r0, 0x64(r1)
    lwz r31, 0x5c(r1)
    lwz r30, 0x58(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}
#else
void HSD_MtxGetScale(Mtx arg0, Vec3* arg1)
{
    f64 scale;

    u8 _[8];

    Vec3 vec1;
    Vec3 vec2;
    Vec3 vec3;
    Vec3 vec4;

    vec1.x = arg0[0][0];
    vec1.y = arg0[1][0];
    vec1.z = arg0[2][0];

    arg1->x = VECMag(&vec1);
    VECNormalize(&vec1, &vec1);

    vec2.x = arg0[0][1];
    vec2.y = arg0[1][1];
    vec2.z = arg0[2][1];

    VECScale(&vec1, &vec4, VECDotProduct(&vec1, &vec2));
    VECSubtract(&vec2, &vec4, &vec2);
    arg1->y = VECMag(&vec2);
    VECNormalize(&vec2, &vec2);

    vec3.x = arg0[0][2];
    vec3.y = arg0[1][2];
    vec3.z = arg0[2][2];

    VECScale(&vec2, &vec4, VECDotProduct(&vec2, &vec3));
    VECSubtract(&vec3, &vec4, &vec3);
    VECScale(&vec1, &vec4, VECDotProduct(&vec1, &vec3));
    VECSubtract(&vec3, &vec4, &vec3);
    arg1->z = VECMag(&vec3);
    VECNormalize(&vec3, &vec3);
    VECCrossProduct(&vec2, &vec3, &vec4);

    if (VECDotProduct(&vec1, &vec4) < 0.0) {
        scale = -1.0;
        arg1->x *= scale;
        arg1->y *= scale;
        arg1->z *= scale;
    }
}
#endif

void HSD_MkRotationMtx(Mtx arg0, Vec3* arg1)
{
    f32 sinX;
    f32 cosX;
    f32 sinY;
    f32 cosY;
    f32 sinZ;
    f32 cosZ;
    f32 temp1;
    f32 temp2;

    sinX = sin(arg1->x);
    cosX = cos(arg1->x);
    sinY = sin(arg1->y);
    cosY = cos(arg1->y);
    sinZ = sin(arg1->z);
    cosZ = cos(arg1->z);

    temp1 = sinX * sinY;
    arg0[0][0] = cosY * cosZ;
    arg0[1][0] = cosY * sinZ;
    arg0[2][0] = -sinY;
    temp2 = cosX * sinY;
    arg0[0][1] = (cosZ * temp1) - (cosX * sinZ);
    arg0[1][1] = (sinZ * temp1) + (cosX * cosZ);
    arg0[2][1] = sinX * cosY;
    arg0[0][2] = (cosZ * temp2) + (sinX * sinZ);
    arg0[1][2] = (sinZ * temp2) - (sinX * cosZ);
    arg0[2][2] = cosX * cosY;
    arg0[0][3] = 0;
    arg0[1][3] = 0;
    arg0[2][3] = 0;
}


static inline f32 HSD_SafeInv(f32 x)
{
    if (x >= 0.0F) {
        return 1.0F / (x + FLT_EPSILON);
    } else {
        return 1.0F / (x - FLT_EPSILON);
    }
}

#ifdef MUST_MATCH
asm void HSD_MtxSRT(Mtx m, Vec3* vec1, Vec3* vec2, Vec3* vec3, Vec3* vec4)
{
    nofralloc
    stwu r1, -0xd0(r1)
    mflr r0
    stw r0, 0xd4(r1)
    stfd f31, 0xc0(r1)
    psq_st f31, 0xc8(r1), 0, 0
    stfd f30, 0xb0(r1)
    psq_st f30, 0xb8(r1), 0, 0
    stfd f29, 0xa0(r1)
    psq_st f29, 0xa8(r1), 0, 0
    stfd f28, 0x90(r1)
    psq_st f28, 0x98(r1), 0, 0
    stfd f27, 0x80(r1)
    psq_st f27, 0x88(r1), 0, 0
    stfd f26, 0x70(r1)
    psq_st f26, 0x78(r1), 0, 0
    stfd f25, 0x60(r1)
    psq_st f25, 0x68(r1), 0, 0
    stfd f24, 0x50(r1)
    psq_st f24, 0x58(r1), 0, 0
    stfd f23, 0x40(r1)
    psq_st f23, 0x48(r1), 0, 0
    stfd f22, 0x30(r1)
    psq_st f22, 0x38(r1), 0, 0
    stfd f21, 0x20(r1)
    psq_st f21, 0x28(r1), 0, 0
    addi r11, r1, 0x20
    bl _savegpr_27
    mr r29, r5
    mr r27, r3
    lfs f1, 0x0(r5)
    mr r28, r4
    mr r30, r6
    mr r31, r7
    bl sin
    frsp f31, f1
    lfs f1, 0x0(r29)
    bl cos
    frsp f30, f1
    lfs f1, 0x4(r29)
    bl sin
    frsp f29, f1
    lfs f1, 0x4(r29)
    bl cos
    frsp f28, f1
    lfs f1, 0x8(r29)
    bl sin
    frsp f27, f1
    lfs f1, 0x8(r29)
    bl cos
    lfs f10, 0x0(r28)
    cmplwi r31, 0x0
    lfs f11, 0x4(r28)
    frsp f1, f1
    lfs f12, 0x8(r28)
    fmr f7, f10
    fmr f4, f10
    fmr f8, f11
    fmr f5, f11
    fmr f9, f12
    fmr f6, f12
    beq HSD_MtxSRT_L_802D715C
    lfs f3, 0x0(r31)
    lfs f0, lbl_806DCD88(r2)
    fcmpo cr0, f3, f0
    cror eq, gt, eq
    bne HSD_MtxSRT_L_802D7098
    lis r3, __float_epsilon@ha
    lfs f2, lbl_806DCD8C(r2)
    lfs f0, __float_epsilon@l(r3)
    fadds f0, f3, f0
    fdivs f0, f2, f0
    b HSD_MtxSRT_L_802D70AC
HSD_MtxSRT_L_802D7098:
    lis r3, __float_epsilon@ha
    lfs f2, lbl_806DCD8C(r2)
    lfs f0, __float_epsilon@l(r3)
    fsubs f0, f3, f0
    fdivs f0, f2, f0
HSD_MtxSRT_L_802D70AC:
    lfs f2, 0x4(r31)
    lfs f13, lbl_806DCD88(r2)
    fcmpo cr0, f2, f13
    cror eq, gt, eq
    bne HSD_MtxSRT_L_802D70D8
    lis r3, __float_epsilon@ha
    lfs f24, lbl_806DCD8C(r2)
    lfs f13, __float_epsilon@l(r3)
    fadds f13, f2, f13
    fdivs f23, f24, f13
    b HSD_MtxSRT_L_802D70EC
HSD_MtxSRT_L_802D70D8:
    lis r3, __float_epsilon@ha
    lfs f24, lbl_806DCD8C(r2)
    lfs f13, __float_epsilon@l(r3)
    fsubs f13, f2, f13
    fdivs f23, f24, f13
HSD_MtxSRT_L_802D70EC:
    lfs f21, 0x8(r31)
    lfs f13, lbl_806DCD88(r2)
    fcmpo cr0, f21, f13
    cror eq, gt, eq
    bne HSD_MtxSRT_L_802D7118
    lis r3, __float_epsilon@ha
    lfs f24, lbl_806DCD8C(r2)
    lfs f13, __float_epsilon@l(r3)
    fadds f13, f21, f13
    fdivs f22, f24, f13
    b HSD_MtxSRT_L_802D712C
HSD_MtxSRT_L_802D7118:
    lis r3, __float_epsilon@ha
    lfs f24, lbl_806DCD8C(r2)
    lfs f13, __float_epsilon@l(r3)
    fsubs f13, f21, f13
    fdivs f22, f24, f13
HSD_MtxSRT_L_802D712C:
    fmuls f24, f2, f0
    fmuls f25, f21, f0
    fmuls f26, f3, f23
    fmuls f13, f21, f23
    fmuls f3, f3, f22
    fmuls f0, f2, f22
    fmuls f5, f5, f24
    fmuls f6, f6, f25
    fmuls f7, f7, f26
    fmuls f9, f9, f13
    fmuls f10, f10, f3
    fmuls f11, f11, f0
HSD_MtxSRT_L_802D715C:
    fmuls f0, f4, f28
    fmuls f4, f7, f28
    fneg f3, f10
    fmuls f7, f1, f0
    fmuls f13, f31, f29
    fmuls f2, f30, f27
    fmuls f0, f30, f1
    stfs f7, 0x0(r27)
    fmuls f10, f27, f4
    fmsubs f2, f1, f13, f2
    fmadds f7, f27, f13, f0
    fmuls f4, f11, f31
    stfs f10, 0x10(r27)
    fmuls f0, f3, f29
    fmuls f5, f5, f2
    fmuls f10, f30, f29
    fmuls f3, f31, f27
    stfs f0, 0x20(r27)
    fmuls f2, f31, f1
    fmuls f0, f12, f30
    stfs f5, 0x4(r27)
    fmuls f5, f8, f7
    fmadds f3, f1, f10, f3
    fmsubs f1, f27, f10, f2
    fmuls f4, f28, f4
    stfs f5, 0x14(r27)
    fmuls f2, f6, f3
    fmuls f1, f9, f1
    stfs f4, 0x24(r27)
    fmuls f0, f28, f0
    stfs f2, 0x8(r27)
    stfs f1, 0x18(r27)
    stfs f0, 0x28(r27)
    lfs f0, 0x0(r30)
    stfs f0, 0xc(r27)
    lfs f0, 0x4(r30)
    stfs f0, 0x1c(r27)
    lfs f0, 0x8(r30)
    stfs f0, 0x2c(r27)
    psq_l f31, 0xc8(r1), 0, 0
    lfd f31, 0xc0(r1)
    psq_l f30, 0xb8(r1), 0, 0
    lfd f30, 0xb0(r1)
    psq_l f29, 0xa8(r1), 0, 0
    lfd f29, 0xa0(r1)
    psq_l f28, 0x98(r1), 0, 0
    lfd f28, 0x90(r1)
    psq_l f27, 0x88(r1), 0, 0
    lfd f27, 0x80(r1)
    psq_l f26, 0x78(r1), 0, 0
    lfd f26, 0x70(r1)
    psq_l f25, 0x68(r1), 0, 0
    lfd f25, 0x60(r1)
    psq_l f24, 0x58(r1), 0, 0
    lfd f24, 0x50(r1)
    psq_l f23, 0x48(r1), 0, 0
    lfd f23, 0x40(r1)
    psq_l f22, 0x38(r1), 0, 0
    lfd f22, 0x30(r1)
    psq_l f21, 0x28(r1), 0, 0
    addi r11, r1, 0x20
    lfd f21, 0x20(r1)
    bl _restgpr_27
    lwz r0, 0xd4(r1)
    mtlr r0
    addi r1, r1, 0xd0
    blr
}
#else
void HSD_MtxSRT(Mtx m, Vec3* vec1, Vec3* vec2, Vec3* vec3, Vec3* vec4)
{
    f32 sinX = sin(vec2->x);
    f32 cosX = cos(vec2->x);
    f32 sinY = sin(vec2->y);
    f32 cosY = cos(vec2->y);
    f32 sinZ = sin(vec2->z);
    f32 cosZ = cos(vec2->z);
    f32 vec1x_2;
    f32 vec1y_2;
    f32 vec1z_2;
    f32 vec1x_1;
    f32 vec1y_1;
    f32 vec1z_1;
    f32 vec1x;
    f32 vec1y;
    f32 vec1z;

    vec1x_2 = vec1x_1 = vec1x = vec1->x;
    vec1y_2 = vec1y_1 = vec1y = vec1->y;
    vec1z_2 = vec1z_1 = vec1z = vec1->z;

    if (vec4 != NULL) {
        f32 temp1 = vec4->x >= 0.0F ? 1.0F / (vec4->x + FLT_EPSILON) : 1.0F / (vec4->x - FLT_EPSILON);
        f32 temp2 = vec4->y >= 0.0F ? 1.0F / (vec4->y + FLT_EPSILON) : 1.0F / (vec4->y - FLT_EPSILON);
        f32 temp3 = vec4->z >= 0.0F ? 1.0F / (vec4->z + FLT_EPSILON) : 1.0F / (vec4->z - FLT_EPSILON);

        vec1y_2 *= vec4->y * temp1;
        vec1z_2 *= vec4->z * temp1;
        vec1x_1 *= vec4->x * temp2;
        vec1z_1 *= vec4->z * temp2;
        vec1x *= vec4->x * temp3;
        vec1y *= vec4->y * temp3;
    }

    m[0][0] = cosZ * (vec1x_2 * cosY);
    m[1][0] = sinZ * (vec1x_1 * cosY);
    m[2][0] = -vec1x * sinY;
    m[0][1] = vec1y_2 * ((cosZ * (sinX * sinY)) - (cosX * sinZ));
    m[1][1] = vec1y_1 * ((sinZ * (sinX * sinY)) + (cosX * cosZ));
    m[2][1] = cosY * (vec1y * sinX);
    m[0][2] = vec1z_2 * ((cosZ * (cosX * sinY)) + (sinX * sinZ));
    m[1][2] = vec1z_1 * ((sinZ * (cosX * sinY)) - (sinX * cosZ));
    m[2][2] = cosY * (vec1z * cosX);
    m[0][3] = vec3->x;
    m[1][3] = vec3->y;
    m[2][3] = vec3->z;
}
#endif


/// might be a fakematch?
asm void HSD_MtxSRTQuat(Mtx m, Vec3* s, Quaternion* r, Vec3* t, Vec3* ps)
{
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    mr r31, r7
    stw r30, 0x48(r1)
    mr r30, r6
    stw r29, 0x44(r1)
    mr r29, r5
    stw r28, 0x40(r1)
    mr r28, r3
    lfs f1, 0x0(r4)
    lfs f2, 0x4(r4)
    lfs f3, 0x8(r4)
    bl PSMTXScale
    mr r4, r29
    addi r3, r1, 0x8
    bl PSMTXQuat
    cmplwi r31, 0x0
    beq HSD_MtxSRTQuat_L_802D73E4
    lfs f2, 0x0(r31)
    lfs f0, lbl_806DCD88(r2)
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    bne HSD_MtxSRTQuat_L_802D72E4
    lis r3, __float_epsilon@ha
    lfs f1, lbl_806DCD8C(r2)
    lfs f0, __float_epsilon@l(r3)
    fadds f0, f2, f0
    fdivs f4, f1, f0
    b HSD_MtxSRTQuat_L_802D72F8
HSD_MtxSRTQuat_L_802D72E4:
    lis r3, __float_epsilon@ha
    lfs f1, lbl_806DCD8C(r2)
    lfs f0, __float_epsilon@l(r3)
    fsubs f0, f2, f0
    fdivs f4, f1, f0
HSD_MtxSRTQuat_L_802D72F8:
    lfs f3, 0x4(r31)
    lfs f0, lbl_806DCD88(r2)
    fcmpo cr0, f3, f0
    cror eq, gt, eq
    bne HSD_MtxSRTQuat_L_802D7324
    lis r3, __float_epsilon@ha
    lfs f1, lbl_806DCD8C(r2)
    lfs f0, __float_epsilon@l(r3)
    fadds f0, f3, f0
    fdivs f7, f1, f0
    b HSD_MtxSRTQuat_L_802D7338
HSD_MtxSRTQuat_L_802D7324:
    lis r3, __float_epsilon@ha
    lfs f1, lbl_806DCD8C(r2)
    lfs f0, __float_epsilon@l(r3)
    fsubs f0, f3, f0
    fdivs f7, f1, f0
HSD_MtxSRTQuat_L_802D7338:
    lfs f2, 0x8(r31)
    lfs f0, lbl_806DCD88(r2)
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    bne HSD_MtxSRTQuat_L_802D7364
    lis r3, __float_epsilon@ha
    lfs f1, lbl_806DCD8C(r2)
    lfs f0, __float_epsilon@l(r3)
    fadds f0, f2, f0
    fdivs f8, f1, f0
    b HSD_MtxSRTQuat_L_802D7378
HSD_MtxSRTQuat_L_802D7364:
    lis r3, __float_epsilon@ha
    lfs f1, lbl_806DCD8C(r2)
    lfs f0, __float_epsilon@l(r3)
    fsubs f0, f2, f0
    fdivs f8, f1, f0
HSD_MtxSRTQuat_L_802D7378:
    fmuls f0, f3, f4
    lfs f1, 0xc(r1)
    lfs f6, 0x10(r1)
    lfs f5, 0x18(r1)
    fmuls f0, f1, f0
    lfs f3, 0x20(r1)
    lfs f2, 0x28(r1)
    lfs f1, 0x2c(r1)
    stfs f0, 0xc(r1)
    lfs f0, 0x4(r31)
    fmuls f4, f0, f4
    fmuls f0, f0, f8
    fmuls f4, f6, f4
    fmuls f0, f1, f0
    stfs f4, 0x10(r1)
    lfs f1, 0x0(r31)
    fmuls f4, f1, f7
    fmuls f1, f1, f8
    fmuls f4, f5, f4
    fmuls f1, f2, f1
    stfs f4, 0x18(r1)
    lfs f2, 0x8(r31)
    fmuls f2, f2, f7
    stfs f1, 0x28(r1)
    stfs f0, 0x2c(r1)
    fmuls f0, f3, f2
    stfs f0, 0x20(r1)
HSD_MtxSRTQuat_L_802D73E4:
    mr r4, r28
    mr r5, r28
    addi r3, r1, 0x8
    bl PSMTXConcat
    lfs f0, 0x0(r30)
    stfs f0, 0xc(r28)
    lfs f0, 0x4(r30)
    stfs f0, 0x1c(r28)
    lfs f0, 0x8(r30)
    stfs f0, 0x2c(r28)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    lwz r29, 0x44(r1)
    lwz r28, 0x40(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

void HSD_MtxScaledAdd(Mtx arg0, Mtx arg1, Mtx arg2, f32 arg3)
{
    f32* arr0 = (&arg0[0][0]);
    f32* arr1 = (&arg1[0][0]);
    f32* arr2 = (&arg2[0][0]);

    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);

    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);

    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
}

asm void fn_802D74F0(Vec3* v, Vec3* out)
{
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    mr r5, r4
    stw r0, 0x24(r1)
    lfs f1, 0x0(r3)
    lfs f2, 0x4(r3)
    fcmpo cr0, f1, f2
    cror eq, lt, eq
    bne fn_802D74F0_L_802D756C
    lfs f0, 0x8(r3)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne fn_802D74F0_L_802D7548
    lfs f0, lbl_806DCD88(r2)
    mr r4, r3
    lfs f1, lbl_806DCD8C(r2)
    addi r3, r1, 0x8
    stfs f0, 0xc(r1)
    stfs f1, 0x8(r1)
    stfs f0, 0x10(r1)
    bl PSVECCrossProduct
    b fn_802D74F0_L_802D75C0
fn_802D74F0_L_802D7548:
    lfs f1, lbl_806DCD88(r2)
    mr r4, r3
    lfs f0, lbl_806DCD8C(r2)
    addi r3, r1, 0x8
    stfs f1, 0x8(r1)
    stfs f1, 0xc(r1)
    stfs f0, 0x10(r1)
    bl PSVECCrossProduct
    b fn_802D74F0_L_802D75C0
fn_802D74F0_L_802D756C:
    lfs f0, 0x8(r3)
    fcmpo cr0, f2, f0
    cror eq, lt, eq
    bne fn_802D74F0_L_802D75A0
    lfs f1, lbl_806DCD88(r2)
    mr r4, r3
    lfs f0, lbl_806DCD8C(r2)
    addi r3, r1, 0x8
    stfs f1, 0x8(r1)
    stfs f0, 0xc(r1)
    stfs f1, 0x10(r1)
    bl PSVECCrossProduct
    b fn_802D74F0_L_802D75C0
fn_802D74F0_L_802D75A0:
    lfs f1, lbl_806DCD88(r2)
    mr r4, r3
    lfs f0, lbl_806DCD8C(r2)
    addi r3, r1, 0x8
    stfs f1, 0x8(r1)
    stfs f1, 0xc(r1)
    stfs f0, 0x10(r1)
    bl PSVECCrossProduct
fn_802D74F0_L_802D75C0:
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

void* HSD_VecAlloc(void)
{
    void* vec = HSD_ObjAlloc(&HSD_Mtx_804C2310);

    HSD_ASSERT(908, vec);

    return vec;
}

void HSD_VecFree(void* arg0)
{
    if (arg0 != NULL) {
        HSD_ObjFree(&HSD_Mtx_804C2310, arg0);
    }
}

void* HSD_MtxAlloc(void)
{
    void* mtx;

    mtx = HSD_ObjAlloc(&HSD_Mtx_804C233C);
    HSD_ASSERT(939, mtx);
    return mtx;
}

void HSD_MtxFree(void* arg0)
{
    if (arg0 != NULL) {
        HSD_ObjFree(&HSD_Mtx_804C233C, arg0);
    }
}

HSD_ObjAllocData* HSD_VecGetAllocData(void)
{
    return &HSD_Mtx_804C2310;
}

void HSD_VecInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_VecGetAllocData(), sizeof(Vec), 4);
}

HSD_ObjAllocData* HSD_MtxGetAllocData(void)
{
    return &HSD_Mtx_804C233C;
}

void HSD_MtxInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_MtxGetAllocData(), sizeof(Mtx), 4);
}
