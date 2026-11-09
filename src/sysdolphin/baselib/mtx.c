#include "mkgp2_names.h"

/* the shared melee header declares the older void version */
#define HSD_MtxInverseConcat HSD_MtxInverseConcat_melee
#include "mtx.h"
#undef HSD_MtxInverseConcat

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
extern float __float_min[];
double sin(double);
void _savegpr_27();
void _restgpr_27();
double atan2(double, double);
double asin(double);
double acos(double);
f32 PSVECSquareMag(Vec3*);
double cos(double);

#define EPSILON 0.0000000001f
#define FLOAT_MIN (*__float_min)

HSD_ObjAllocData HSD_Mtx_804C2310;
HSD_ObjAllocData HSD_Mtx_804C233C;

/// Calculates the determinant of the top 3x3 section of a 3x4 matrix
static inline f32 HSD_CalcDeterminantMatrix3x4(Mtx m)
{
    return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] +
           m[0][2] * m[1][0] * m[2][1] - m[2][0] * m[1][1] * m[0][2] -
           m[1][0] * m[0][1] * m[2][2] - m[0][0] * m[2][1] * m[1][2];
}


/* mkgp2's HSD returns whether the matrix was invertible and tests det == 0
 * (melee's version is void and uses an epsilon). The determinant is written
 * out here: calling HSD_CalcDeterminantMatrix3x4 colors one FPR differently
 * (f22 gets used). */
int HSD_MtxInverseConcat(Mtx inv, Mtx src, Mtx dest)
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

    det = inv[0][0] * inv[1][1] * inv[2][2] + inv[0][1] * inv[1][2] * inv[2][0] +
          inv[0][2] * inv[1][0] * inv[2][1] - inv[2][0] * inv[1][1] * inv[0][2] -
          inv[1][0] * inv[0][1] * inv[2][2] - inv[0][0] * inv[2][1] * inv[1][2];
    if (det == 0.0f) {
        return 0;
    }
    det = 1.0f / det;
    temp1 = ((inv[1][1] * inv[2][2]) - (inv[2][1] * inv[1][2])) * det;
    temp2 = (-((inv[0][1] * inv[2][2]) - (inv[2][1] * inv[0][2]))) * det;
    temp3 = (-((inv[1][0] * inv[2][2]) - (inv[2][0] * inv[1][2]))) * det;
    temp7 = ((inv[0][1] * inv[1][2]) - (inv[1][1] * inv[0][2])) * det;
    temp4 = ((inv[0][0] * inv[2][2]) - (inv[2][0] * inv[0][2])) * det;
    temp8 = (-((inv[0][0] * inv[1][2]) - (inv[1][0] * inv[0][2]))) * det;
    temp5 = ((inv[1][0] * inv[2][1]) - (inv[2][0] * inv[1][1])) * det;
    temp6 = (-((inv[0][0] * inv[2][1]) - (inv[2][0] * inv[0][1]))) * det;
    temp9 = ((inv[0][0] * inv[1][1]) - (inv[1][0] * inv[0][1])) * det;
    temp10 = -((temp7 * inv[2][3]) -
               (((-temp1) * inv[0][3]) - (temp2 * inv[1][3])));
    temp11 = -((temp8 * inv[2][3]) -
               (((-temp3) * inv[0][3]) - (temp4 * inv[1][3])));
    temp12 = -((temp9 * inv[2][3]) -
               (((-temp5) * inv[0][3]) - (temp6 * inv[1][3])));

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

        PSMTXCopy(m, dest);
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
    return 1;
}


static inline f32 mk_asinf(f32 x) { return asin(x); }
static inline f32 mk_atan2f(f32 y, f32 x) { return atan2(y, x); }
static inline f32 mk_sinf(f32 x) { return sin(x); }
static inline f32 mk_cosf(f32 x) { return cos(x); }

static inline f32 calcVal(f32 x, f32 y)
{
    if (x == 0.0F) {
        if (y >= 0) {
            return M_PI / 2;
        } else {
            return -M_PI / 2;
        }
    } else {
        return mk_atan2f(y, x);
    }
}

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
                    val_01 = mk_asinf(testVal_1);
                }

                vec->y = val_01;

                if (mk_cosf(vec->y) >= FLOAT_MIN) {
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

/// These parameters may not be right
void HSD_MtxGetTranslate(Mtx mat, Vec3* vec)
{
    vec->x = mat[0][3];
    vec->y = mat[1][3];
    vec->z = mat[2][3];
}

void HSD_MtxGetScale(Mtx arg0, Vec3* arg1)
{
    Vec3 vec1;
    Vec3 vec2;
    Vec3 vec3;
    Vec3 vec4;
    f32 sq;
    f32 inv;
    f64 scale;

    vec1.x = arg0[0][0];
    vec1.y = arg0[1][0];
    vec1.z = arg0[2][0];
    sq = VECSquareMag(&vec1);
    if (sq > EPSILON) {
        inv = sqrtf(1.0F / sq);
        arg1->x = 1.0F / inv;
        VECScale(&vec1, &vec1, inv);

        vec2.x = arg0[0][1];
        vec2.y = arg0[1][1];
        vec2.z = arg0[2][1];
        VECScale(&vec1, &vec4, VECDotProduct(&vec1, &vec2));
        VECSubtract(&vec2, &vec4, &vec2);
        sq = VECSquareMag(&vec2);
        if (sq > EPSILON) {
            inv = sqrtf(1.0F / sq);
            arg1->y = 1.0F / inv;
            VECScale(&vec2, &vec2, inv);

            vec3.x = arg0[0][2];
            vec3.y = arg0[1][2];
            vec3.z = arg0[2][2];
            VECScale(&vec2, &vec4, VECDotProduct(&vec2, &vec3));
            VECSubtract(&vec3, &vec4, &vec3);
            VECScale(&vec1, &vec4, VECDotProduct(&vec1, &vec3));
            VECSubtract(&vec3, &vec4, &vec3);
            sq = VECSquareMag(&vec3);
            if (sq > EPSILON) {
                arg1->z = sqrtf(sq);
                VECCrossProduct(&vec2, &vec3, &vec4);
                if (VECDotProduct(&vec1, &vec4) < 0.0) {
                    scale = -1.0;
                    arg1->x *= scale;
                    arg1->y *= scale;
                    arg1->z *= scale;
                }
            } else {
                arg1->z = 0.0F;
            }
        } else {
            arg1->y = 0.0F;
            vec3.x = arg0[0][2];
            vec3.y = arg0[1][2];
            vec3.z = arg0[2][2];
            VECScale(&vec1, &vec4, VECDotProduct(&vec1, &vec3));
            VECSubtract(&vec3, &vec4, &vec3);
            sq = VECSquareMag(&vec3);
            if (sq > EPSILON) {
                arg1->z = sqrtf(sq);
            } else {
                arg1->z = 0.0F;
            }
        }
    } else {
        arg1->x = 0.0F;
        vec2.x = arg0[0][1];
        vec2.y = arg0[1][1];
        vec2.z = arg0[2][1];
        sq = VECSquareMag(&vec2);
        if (sq > EPSILON) {
            inv = sqrtf(1.0F / sq);
            arg1->y = 1.0F / inv;
            VECScale(&vec2, &vec2, inv);

            vec3.x = arg0[0][2];
            vec3.y = arg0[1][2];
            vec3.z = arg0[2][2];
            VECScale(&vec2, &vec4, VECDotProduct(&vec2, &vec3));
            VECSubtract(&vec3, &vec4, &vec3);
            arg1->z = VECMag(&vec3);
        } else {
            arg1->y = 0.0F;
            vec3.x = arg0[0][2];
            vec3.y = arg0[1][2];
            vec3.z = arg0[2][2];
            arg1->z = VECMag(&vec3);
        }
    }
}

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

void HSD_MtxSRT(Mtx m, Vec3* vec1, Vec3* vec2, Vec3* vec3, Vec3* vec4)
{
    f32 vec1x_2;
    f32 vec1y_2;
    f32 vec1z_2;
    f32 vec1x_1;
    f32 vec1y_1;
    f32 vec1z_1;
    f32 vec1x;
    f32 vec1y;
    f32 vec1z;
    f32 sinX = mk_sinf(vec2->x);
    f32 cosX = mk_cosf(vec2->x);
    f32 sinY = mk_sinf(vec2->y);
    f32 cosY = mk_cosf(vec2->y);
    f32 sinZ = mk_sinf(vec2->z);
    f32 cosZ = mk_cosf(vec2->z);

    vec1x_2 = vec1x_1 = vec1x = vec1->x;
    vec1y_2 = vec1y_1 = vec1y = vec1->y;
    vec1z_2 = vec1z_1 = vec1z = vec1->z;

    if (vec4 != NULL) {
        f32 temp1 = HSD_SafeInv(vec4->x);
        f32 temp2 = HSD_SafeInv(vec4->y);
        f32 temp3 = HSD_SafeInv(vec4->z);

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


void HSD_MtxSRTQuat(Mtx m, Vec3* s, Quaternion* r, Vec3* t, Vec3* ps)
{
    Mtx temp;

    PSMTXScale(m, s->x, s->y, s->z);
    PSMTXQuat(temp, r);
    if (ps != NULL) {
        f32 ix = HSD_SafeInv(ps->x);
        f32 iy = HSD_SafeInv(ps->y);
        f32 iz = HSD_SafeInv(ps->z);

        /* mkgp2 scales [0][2] by ps->y (melee's HSD_MtxSRT uses ps->z) */
        temp[0][1] *= ps->y * ix;
        temp[0][2] *= ps->y * ix;
        temp[1][0] *= ps->x * iy;
        temp[1][2] *= ps->z * iy;
        temp[2][0] *= ps->x * iz;
        temp[2][1] *= ps->y * iz;
    }
    PSMTXConcat(temp, m, m);
    m[0][3] = t->x;
    m[1][3] = t->y;
    m[2][3] = t->z;
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

void fn_802D74F0(Vec3* v, Vec3* out)
{
    Vec3 axis;

    if (v->x <= v->y) {
        if (v->x <= v->z) {
            axis.x = 1.0F;
            axis.y = 0.0F;
            axis.z = 0.0F;
            PSVECCrossProduct(&axis, v, out);
        } else {
            axis.x = 0.0F;
            axis.y = 0.0F;
            axis.z = 1.0F;
            PSVECCrossProduct(&axis, v, out);
        }
    } else if (v->y <= v->z) {
        axis.x = 0.0F;
        axis.y = 1.0F;
        axis.z = 0.0F;
        PSVECCrossProduct(&axis, v, out);
    } else {
        axis.x = 0.0F;
        axis.y = 0.0F;
        axis.z = 1.0F;
        PSVECCrossProduct(&axis, v, out);
    }
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
