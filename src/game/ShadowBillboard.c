#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * ShadowBillboard update/flash and the play camera, 0x80061954..0x80064CD4.
 * Tick uses native matrix and camera updates. PlayCamera_Init is the C++
 * constructor of clPlayCamera; its mangled name and the member dtors are
 * bridged to the C symbols via tools/extab_user_renames.json.
 * The TU owns .rodata 0x802EE320..0x802EE510 (camera table, lerp weights,
 * zero vectors, "playcamera.cpp"), addressed as one pooled base.
 */

#include "game/ShadowBillboardPrivate.h"
#include "game/singleton.h"

/* Camera assertion strings. */
extern char lbl_806D2BCC[7];
extern char lbl_806D2BD4[5];

#include "game/types/ShadowBillboardSrc.h"

typedef struct SBShake {
    int timer;
    int fieldBC;
    Vec3f offset;
} SBShake;

typedef struct ShadowBillboard {
    unsigned char active; /* 0x00 */
    unsigned char pad01[0x04 - 0x01];
    int mode; /* 0x04 */
    unsigned char pad08[0x0C - 0x08];
    int level; /* 0x0C */
    unsigned char pad10[0x14 - 0x10];
    ShadowBillboardSrc *src;
    unsigned char flag18; /* 0x18 */
    unsigned char flag19; /* 0x19 */
    unsigned char pad1A[0x1C - 0x1A];
    float mtx1C[16]; /* 0x1C */
    float *camMtx; /* 0x5C */
    float fade60;
    float fade64;
    int fadeMode; /* 0x68 */
    int field6C;
    Vec3f vec70;
    Vec3f camPos;
    Vec3f axis;
    float field94;
    float targetSaturation; /* 0x98 */
    float saturation; /* 0x9C */
    float introA0; /* 0xA0 */
    float heightA4;
    float bumpA8; /* 0xA8 */
    unsigned char spinFlash; /* 0xAC */
    unsigned char padAD[3];
    float spinB0;
    float spinB4;
    struct SBShake shake; /* 0xB8 */
    int courseCam; /* 0xCC */
    float fxD0; /* 0xD0 */
} ShadowBillboard;

typedef struct PlayCamera {
    unsigned char pad00[0x5C];
    void *buffer; /* 0x5C */
} PlayCamera;

extern const float lbl_806D2B6C;
extern const float lbl_806D2B74;
extern const float lbl_806D2B78;
extern const float lbl_806D2C0C;
extern const float lbl_806D2C10;
extern const float lbl_806D2C14;
extern void *lbl_806D109C; /* camera effect singleton */

void *GetCourseScene3D(void);
void CObj_LoadProjMatrix(void *scene, Vec3f *out);
void CameraEffect_Apply(void *effect, int kind, float value);
void MemoryManager_TimedFree(void *p);

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
void CObj_ApplyViewport(void *cobj, Vec3f *pos);
float *CObj_GetViewMatrix_Cached(void *scene);
void CObj_LinePath_Step(void *cobj, float (*m)[4], float a, float b, float c);
void CObj_LoadIntoGX(void *cobj, Vec3f *pos);
void CObj_SetWorldMatrix(void *cobj, float (*m)[4]);
float FAbs_FloatAsDouble(float x);
void *MemoryManager_AllocTagged(unsigned int size, const char *file, int line);
void Mtx4x4_TransposeTo4x3(const float *src, float (*dst)[4]);
unsigned int PSMTXInverse(float (*src)[4], float (*dst)[4]);
void PSMTXMultVec(float (*m)[4], Vec3f *src, Vec3f *dst);
void ShadowBillboard_LerpMtx4x4(struct ShadowBillboard *sb, const float *target, float t);
void ShadowBillboard_SetEffectParams(void *fx, int kind, float a, float b, float c, float d);
unsigned char Terrain_GetGroundHeightWithPenetration(Vec3f *pos, float *out, void *a, void *b, float range);
void Vec3_Copy(Vec3f *dst, const Vec3f *src);
void Vec3_Lerp(Vec3f *out, const Vec3f *a, const Vec3f *b, float t);
void __assert(const char *file, int line, const char *expr);
double cos(double x);
double sin(double x);

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_cupId;
extern unsigned int g_gameMode;
extern unsigned int g_longRoundFlag;
extern unsigned int g_reverseRoundFlag;
extern unsigned int g_roundIndex;
extern unsigned int PlayCamera_Init_data_806CEEF0;
extern unsigned int lbl_806D2B68;
extern unsigned int lbl_806D2B70;
extern unsigned int lbl_806D2B80;
extern unsigned int lbl_806D2B88;
extern unsigned int lbl_806D2B90;
extern unsigned int lbl_806D2B98;
extern unsigned int lbl_806D2BA0;
extern unsigned int lbl_806D2BA8;
extern unsigned int lbl_806D2BB0;
extern unsigned int lbl_806D2BB4;
extern unsigned int lbl_806D2BB8;
extern unsigned int lbl_806D2BBC;
extern unsigned int lbl_806D2BC0;
extern unsigned int lbl_806D2BC4;
extern unsigned int lbl_806D2BC8;
extern unsigned int lbl_806D2BDC;
extern unsigned int lbl_806D2BE0;
extern unsigned int lbl_806D2BE4;
extern unsigned int lbl_806D2BE8;
extern unsigned int lbl_806D2BEC;
extern unsigned int lbl_806D2BF0;
extern unsigned int lbl_806D2BF4;
extern unsigned int lbl_806D2BF8;
extern unsigned int lbl_806D2BFC;
extern unsigned int lbl_806D2C00;
extern unsigned int lbl_806D2C08;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
/* .rodata 0x802EE320..0x802EE50B: play camera tables */
extern const float ShadowBillboard_rodata_802EE320[13][2][4] = {
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 57.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 60.0f, 10.0f}},
    {{18.0f, 25.0f, 50.0f, 10.0f}, {18.0f, 30.0f, 55.0f, 10.0f}},
};
extern const float lbl_802EE4C0[3] = {1.0f, 0.7f, 0.9f};
extern const float ShadowBillboard_LerpMtx4x4_rodata_802EE4CC[3] = {0.075f, 0.075f, 0.075f};
#define sCamTable ShadowBillboard_rodata_802EE320



/* --- function index (11 fns, .text 0x80061954..0x80064CD4) ---
 * [  0] 0x80061954 size:0x134   global ShadowBillboard_SetField0x6CAndComputeAxis
 * [  1] 0x80061A88 size:0x1E14  global ShadowBillboard_Tick
 * [  2] 0x8006389C size:0x5B4   global ShadowBillboard_StepSimple
 * [  3] 0x80063E50 size:0x8     global ShadowBillboard_SetTargetSaturation
 * [  4] 0x80063E58 size:0x88    global ShadowBillboard_TriggerSpinFlash
 * [  5] 0x80063EE0 size:0x28    global ShadowBillboard_BeginFadeCleanup
 * [  6] 0x80063F08 size:0x28    global ShadowBillboard_BeginBoostScale
 * [  7] 0x80063F30 size:0x380   global Camera_RotateByYaw
 * [  8] 0x800642B0 size:0x5C    global PlayCamera_Dtor
 * [  9] 0x8006430C size:0x614   global PlayCamera_Init
 * [ 10] 0x80064920 size:0x3B4   global Mtx34_Orthonormalize
 */


/* per-course play camera overrides (0x7C-byte entries) */
#include "game/types/PCCourseCamEntry.h"

extern PCCourseCamEntry ShadowBillboard_data_803F9F30[];

/* --- forward decls --- */
struct LineCam;
void ShadowBillboard_Tick(struct ShadowBillboard *sb, struct LineCam *lineCam, void *worldObj);
void ShadowBillboard_StepSimple(struct ShadowBillboard *sb, void *lineCam, void *worldObj);
void Camera_RotateByYaw(PlayCamera *cam, float yaw);
void Mtx34_Orthonormalize(float (*m)[4]);

/* --- function bodies --- */
static inline void Vec3f_Set(Vec3f *v, float x, float y, float z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

#pragma exceptions on

void ShadowBillboard_SetField0x6CAndComputeAxis(ShadowBillboard *sb, int value) {
    Vec3f cam;
    float len;
    float inv;

    sb->field6C = value;
    CObj_LoadProjMatrix(GetCourseScene3D(), &cam);
    Vec3f_Set(&sb->camPos, cam.x, cam.y, cam.z);
    Vec3f_Set(&sb->axis, sb->src->mtx[8], 0.0f, sb->src->mtx[10]);
    len = MathInline_sqrtf(sb->axis.x * sb->axis.x + sb->axis.y * sb->axis.y + sb->axis.z * sb->axis.z);
    if (len <= 0.0f) {
        sb->axis.z = 0.0f;
        sb->axis.y = 0.0f;
        sb->axis.x = 0.0f;
    } else {
        inv = 1.0f / len;
        sb->axis.x *= inv;
        sb->axis.y *= inv;
        sb->axis.z *= inv;
    }
    sb->field94 = 0.0f;
}

#pragma exceptions reset

static inline float cosf(float x) {
    return (float)cos(x);
}

static inline float sinf(float x) {
    return (float)sin(x);
}

static inline void Mtx44_SetTrans(float *m, float x, float y, float z) {
    m[12] = x;
    m[13] = y;
    m[14] = z;
}

static inline unsigned char SBShake_IsActive(const SBShake *sh) {
    return sh->timer > 0;
}

static inline void SBShake_SetFromView(SBShake *sh, float dir) {
    void *scene = GetCourseScene3D();
    if (scene != 0) {
        float *m = CObj_GetViewMatrix_Cached(scene);
        sh->offset.x = 0.5f * (m[0] * dir);
        sh->offset.y = 0.5f * (m[4] * dir);
        sh->offset.z = 0.5f * (m[8] * dir);
    }
}

static inline void SBShake_Step(SBShake *sh) {
    sh->timer--;
    if ((sh->timer & 3) <= 1) {
        SBShake_SetFromView(sh, 1.0f);
    } else {
        SBShake_SetFromView(sh, -1.0f);
    }
    if (SBShake_IsActive(sh) == 1) {
        sh->timer = 0;
        sh->fieldBC = 0;
        sh->offset.x = 0.0f;
        sh->offset.y = 0.0f;
        sh->offset.z = 0.0f;
    }
}

static inline void Vec3f_Zero(Vec3f *v) {
    Vec3f zero = {0.0f, 0.0f, 0.0f};
    *v = zero;
}

static const Vec3f lbl_802EE4E4 = {0.0f, 0.0f, 0.0f}; /* used by ShadowBillboard_Tick */
static const Vec3f lbl_802EE4F0 = {0.0f, 0.0f, 0.0f};

static inline Vec3f SBShake_GetOffset(SBShake *sh) {
    if (SBShake_IsActive(sh) == 1) {
        return sh->offset;
    }
    return lbl_802EE4F0;
}

#include "game/types/Mtx44S.h"

/* Alias-safe 4x4 product (out may be a or b), result through a scratch buffer. */
static inline void Mtx44S_Mul(Mtx44S *out, const Mtx44S *a, const Mtx44S *b) {
    float tmp[16];
    float *m;
    int k;
    int i;
    int j;

    if (out == a || out == b) {
        m = tmp;
    } else {
        m = out->v;
    }
    k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            float sum = a->v[k + 0] * b->v[0 * 4 + j];
            sum += a->v[k + 1] * b->v[1 * 4 + j];
            sum += a->v[k + 2] * b->v[2 * 4 + j];
            sum += a->v[k + 3] * b->v[3 * 4 + j];
            m[k + j] = sum;
        }
        k += 4;
    }
    if (out == a || out == b) {
        for (i = 0; i < 16; i++) {
            out->v[i] = tmp[i];
        }
    }
}




static inline void LineCamCObj_ClearFlag2(LineCamCObj *cobj) {
    if (cobj == 0) {
        __assert(lbl_806D2BCC, 0x1AE, lbl_806D2BD4);
    }
    cobj->flags &= ~2;
}

static inline void PCPath_Lerp(Vec3f *out, Vec3f to, Vec3f from, float t) {
    Vec3_Lerp(out, &to, &from, t);
}

static inline double SB_fabsd(double x) {
    return __fabs(x);
}

static inline void *CamFx_Get(void) {
    return SINGLETON_INSTANCE(lbl_806D109C);
}

static inline void Mtx44S_RotY(Mtx44S *dst, float deg) {
    Mtx44S rot;
    float c;
    float s;
    int i;

    for (i = 0; i < 16; i++) {
        rot.v[i] = 0.0f;
    }
    rot.v[0] = rot.v[5] = rot.v[10] = rot.v[15] = 1.0f;
    c = cosf(0.017453292519943295 * deg);
    s = sinf(0.017453292519943295 * deg);
    rot.v[0] = c;
    rot.v[8] = s;
    rot.v[10] = c;
    rot.v[2] = -s;
    Mtx44S_Mul(&rot, &rot, dst);
    *dst = rot;
}

static inline void Mtx44S_RotY180(Mtx44S *m) {
    Mtx44S_RotY(m, 180.0f);
}

static inline float SB_Radians(float degrees) {
    return 0.017453292519943295 * degrees;
}

static inline void Mtx44S_RotX(Mtx44S *dst, float deg) {
    Mtx44S rot;
    float rad;
    float c;
    float s;
    int i;

    rad = SB_Radians(deg);
    for (i = 0; i < 16; i++) {
        rot.v[i] = 0.0f;
    }
    rot.v[0] = rot.v[5] = rot.v[10] = rot.v[15] = 1.0f;
    c = cosf(rad);
    s = sinf(rad);
    rot.v[10] = c;
    rot.v[6] = s;
    rot.v[5] = c;
    rot.v[9] = -s;
    Mtx44S_Mul(&rot, &rot, dst);
    *dst = rot;
}

#pragma exceptions on
#pragma push
#pragma use_lmw_stmw on

void ShadowBillboard_Tick(ShadowBillboard *sb, LineCam *lineCam, void *worldObj) {
    float d;

    if (sb->spinFlash != 0) {
        sb->spinB4 += sb->spinB0;
        if (sb->spinB0 > 0.0f) {
            if (sb->spinB4 > 1.0f) {
                sb->spinB0 = -sb->spinB0;
            }
        } else if (sb->spinB4 < 0.0f) {
            sb->spinFlash = 0;
            sb->spinB0 = 0.0f;
            sb->spinB4 = 0.0f;
        }
    }

    if (SBShake_IsActive(&sb->shake) != 0) {
        SBShake_Step(&sb->shake);
    }

    d = 0.05f * (float)SB_fabsd(sb->targetSaturation - sb->saturation);
    if (sb->targetSaturation > sb->saturation) {
        sb->saturation += d;
        if (sb->targetSaturation < sb->saturation) {
            sb->saturation = sb->targetSaturation;
        }
    } else {
        sb->saturation -= d;
        if (sb->targetSaturation > sb->saturation) {
            sb->saturation = sb->targetSaturation;
        }
    }

    if (lineCam != 0) {
        if (sb->introA0 > 0.0f) {
            int t;
            int idx;
            int rem;
            sb->introA0 -= 0.0027777778f;
            if (sb->introA0 < 0.0f) {
                sb->introA0 = 0.0f;
            }
            t = (int)(360.0f - 360.0f * sb->introA0);
            idx = (int)((float)t / 120.0f);
            if (idx < 0) {
                idx = 0;
            }
            if (idx > 2) {
                idx = 2;
            }
            rem = (int)((float)t - 120.0f * (float)idx);
            {
                Vec3f out;
                Vec3f at;
                PCPath_Lerp(&out, ShadowBillboard_data_803F9F30[sb->courseCam].seg[idx].b,
                            ShadowBillboard_data_803F9F30[sb->courseCam].seg[idx].a, (float)rem / 120.0f);
                CObj_LoadIntoGX(lineCam, &out);
                Vec3_Copy(&at, &ShadowBillboard_data_803F9F30[sb->courseCam].seg[idx].c);
                CObj_ApplyViewport(lineCam, &at);
            }
            if (rem < 20) {
                sb->fxD0 -= 0.05f;
                if (sb->fxD0 < 0.0f) {
                    sb->fxD0 = 0.0f;
                }
                ShadowBillboard_SetEffectParams(CamFx_Get(), 5, 0.0f, 0.0f, 0.0f, sb->fxD0);
            } else if (100.0f < (float)rem) {
                sb->fxD0 += 0.05f;
                if (1.0f < sb->fxD0) {
                    sb->fxD0 = 1.0f;
                }
                ShadowBillboard_SetEffectParams(CamFx_Get(), 5, 0.0f, 0.0f, 0.0f, sb->fxD0);
            }
        } else if (sb->flag18 == 0) {
            float x;
            float y;
            float lo;
            float hi;
            float v;
            if (sb->fxD0) {
                ShadowBillboard_SetEffectParams(CamFx_Get(), 5, 0.0f, 0.0f, 0.0f, 0.0f);
                sb->fxD0 = 0.0f;
            }
            {
                LineCamCObj *cobj = lineCam->cobj;
                if (cobj != 0) {
                    LineCamCObj_ClearFlag2(cobj);
                }
            }
            if (sb->bumpA8 > 0.0f) {
                sb->bumpA8 *= 0.8f;
            }
            x = 0.8333333f * sCamTable[sb->mode][sb->level][0];
            y = 0.8333333f * sCamTable[sb->mode][sb->level][1] - sb->heightA4;
            lo = 0.8333333f * sCamTable[sb->mode][sb->level][2] + 0.8333333f * (15.0f * sb->saturation);
            hi = 0.8333333f * sCamTable[sb->mode][sb->level][3] + lo;
            if (sb->fadeMode == 0) {
                hi = lo;
            } else {
                sb->fade60 -= sb->fade64;
                if (sb->fade60 < 0.0f) {
                    sb->fade60 = 0.0f;
                }
                if (sb->fadeMode == 1) {
                    v = 1.0f - (float)sin((float)(0.017453292519943295 * (90.0f * sb->fade60)));
                    if (sb->fade60 <= 0.0f) {
                        sb->fadeMode = 0;
                    }
                } else {
                    v = (float)sin((float)(0.017453292519943295 * (90.0f * sb->fade60)));
                }
                hi = lo * v + hi * (1.0f - v);
            }
            {
                Mtx44S m;
                float out[3][4];
                int i;
                for (i = 0; i < 16; i++) {
                    m.v[i] = sb->src->mtx[i];
                }
                Mtx44S_RotY180(&m);
                Mtx44S_RotX(&m, 70.0f * -sb->spinB4);
                ShadowBillboard_LerpMtx4x4(sb, m.v, sb->src->lerpT);
                Mtx4x4_TransposeTo4x3(sb->camMtx, out);
                {
                    Vec3f sh = SBShake_GetOffset(&sb->shake);
                    out[0][3] += sh.x;
                    out[1][3] += sh.y;
                    out[2][3] += sh.z;
                }
                {
                Vec3f p;
                float ground;
                ground = 0.0f;
                p = lbl_802EE4E4;
                p.y = y + sb->bumpA8;
                p.z = hi - sb->bumpA8;
                PSMTXMultVec(out, &p, &p);
                if (Terrain_GetGroundHeightWithPenetration(&p, &ground, 0, 0, 10.0f) == 1 && p.y < ground) {
                    if (FAbs_FloatAsDouble(ground - p.y) >= 2.0f) {
                        sb->bumpA8 = 2.0f;
                    } else {
                        sb->bumpA8 += 1.2f * (ground - p.y);
                    }
                }
                }
                y += sb->bumpA8;
                CObj_LinePath_Step(lineCam, out, x, y, hi - sb->bumpA8);
            }
        } else {
            float x;
            float y;
            float lo;
            float hi;
            float v;
            if (sb->fxD0) {
                ShadowBillboard_SetEffectParams(CamFx_Get(), 5, 0.0f, 0.0f, 0.0f, 0.0f);
                sb->fxD0 = 0.0f;
            }
            {
                Mtx44S m;
                Mtx44S m2;
                float out[3][4];
                float dx;
                float dz;
                int i;
                for (i = 0; i < 16; i++) {
                    m.v[i] = sb->src->mtx[i];
                }
                Mtx44S_RotY180(&m);
                Mtx44S_RotX(&m, 70.0f * -sb->spinB4);
                ShadowBillboard_LerpMtx4x4(sb, m.v, sb->src->lerpT);
                for (i = 0; i < 16; i++) {
                    m2.v[i] = sb->src->mtx58[i];
                }
                Mtx44S_RotY(&m2, 180.0f);
                m2.v[13] += 8.0f;
                dx = m2.v[12] - sb->mtx1C[12];
                dz = m2.v[14] - sb->mtx1C[14];
                if (dx * dx + dz * dz >= 3000.0f) {
                    sb->flag19 = 1;
                }
                if (sb->flag19 == 0) {
                    for (i = 0; i < 16; i++) {
                        m2.v[i] = sb->mtx1C[i] + (m2.v[i] - sb->mtx1C[i]) / 3.0f;
                    }
                } else {
                    sb->flag19 = 0;
                }
                for (i = 0; i < 16; i++) {
                    sb->mtx1C[i] = m2.v[i];
                }
                Mtx4x4_TransposeTo4x3(m2.v, out);
                {
                    Vec3f sh = SBShake_GetOffset(&sb->shake);
                    out[0][0] += sh.x;
                    out[1][0] += sh.y;
                    out[2][0] += sh.z;
                }
                x = 0.8333333f * sCamTable[sb->mode][sb->level][0];
                y = 0.8333333f * sCamTable[sb->mode][sb->level][1] - sb->heightA4;
                lo = 0.8333333f * sCamTable[sb->mode][sb->level][2] + 0.8333333f * (15.0f * sb->saturation);
                hi = 0.8333333f * sCamTable[sb->mode][sb->level][3] + lo;
                if (sb->fadeMode == 0) {
                    hi = lo;
                } else {
                    sb->fade60 -= sb->fade64;
                    if (sb->fade60 < 0.0f) {
                        sb->fade60 = 0.0f;
                    }
                    if (sb->fadeMode == 1) {
                        v = 1.0f - (float)sin((float)(0.017453292519943295 * (90.0f * sb->fade60)));
                        if (sb->fade60 <= 0.0f) {
                            sb->fadeMode = 0;
                        }
                    } else {
                        v = (float)sin((float)(0.017453292519943295 * (90.0f * sb->fade60)));
                    }
                    hi = lo * v + hi * (1.0f - v);
                }
                CObj_LinePath_Step(lineCam, out, x, y, hi);
                PSMTXInverse(out, out);
                CObj_SetWorldMatrix(lineCam, out);
            }
        }
    }

    if (worldObj != 0) {
        float m[16];
        float out[3][4];
        int i;
        ShadowBillboardSrc *src = sb->src;
        for (i = 0; i < 16; i++) {
            m[i] = src->mtx[i];
        }
        m[13] += 4.0f;
        Mtx4x4_TransposeTo4x3(m, out);
        PSMTXInverse(out, out);
        CObj_SetWorldMatrix(worldObj, out);
    }
}

#pragma pop
#pragma exceptions reset


#pragma exceptions on

void ShadowBillboard_StepSimple(ShadowBillboard *sb, void *lineCam, void *worldObj) {
    float y;
    float x;
    float lo;
    float hi;
    float v;
    ShadowBillboardSrc *src;

    if (SBShake_IsActive(&sb->shake) != 0) {
        SBShake_Step(&sb->shake);
    }

    if (lineCam != 0) {
        y = 0.8333333f * sCamTable[sb->mode][sb->level][0] + sb->heightA4;
        x = 0.8333333f * sCamTable[sb->mode][sb->level][1];
        lo = 0.8333333f * sCamTable[sb->mode][sb->level][2];
        hi = 0.8333333f * sCamTable[sb->mode][sb->level][3] + lo;
        src = sb->src;
        if (sb->field6C == 0) {
            Vec3f sh = SBShake_GetOffset(&sb->shake);
            Mtx44_SetTrans(sb->camMtx, sh.x + src->mtx[12], sh.y + src->mtx[13], sh.z + src->mtx[14]);
            if (sb->fadeMode == 0) {
                hi = lo;
            } else {
                sb->fade60 -= sb->fade64;
                if (sb->fade60 < 0.0f) {
                    sb->fade60 = 0.0f;
                }
                if (sb->fadeMode == 1) {
                    v = 1.0f - (float)sin((float)(0.017453292519943295 * (90.0f * sb->fade60)));
                    if (sb->fade60 <= 0.0f) {
                        sb->fadeMode = 0;
                    }
                } else {
                    v = (float)sin((float)(0.017453292519943295 * (90.0f * sb->fade60)));
                }
                hi = lo * v + hi * (1.0f - v);
            }
            {
                float out[3][4];
                Mtx4x4_TransposeTo4x3(sb->camMtx, out);
                CObj_LinePath_Step(lineCam, out, y, x, hi);
            }
        } else {
            Vec3f sh = SBShake_GetOffset(&sb->shake);
            Vec3f pos;
            int mode = sb->field6C;
            if (mode == 1) {
                pos.x = src->mtx[12];
                pos.y = y + src->mtx[13];
                pos.z = src->mtx[14];
            } else if (mode == 3) {
                pos.x = src->mtx[12];
                pos.y = y + src->mtx[13];
                pos.z = src->mtx[14];
                sb->camPos.y = 20.0f + pos.y;
                {
                    Vec3f at;
                    Vec3f_Zero(&at);
                    at.x = sb->camPos.x;
                    at.y = sb->camPos.y;
                    at.z = sb->camPos.z;
                    CObj_LoadIntoGX(lineCam, &at);
                }
            } else if (mode == 4) {
                pos.x = sb->vec70.x;
                pos.y = sb->vec70.y + y;
                pos.z = sb->vec70.z;
            } else {
                pos.x = sb->vec70.x;
                pos.y = y + src->mtx[13];
                pos.z = sb->vec70.z;
            }
            pos.x += sh.x;
            pos.y += sh.y;
            pos.z += sh.z;
            CObj_ApplyViewport(lineCam, &pos);
        }
    }

    if (worldObj != 0) {
        float m[16];
        float out[3][4];
        int i;
        src = sb->src;
        for (i = 0; i < 16; i++) {
            m[i] = src->mtx[i];
        }
        m[13] += 8.0f;
        Mtx4x4_TransposeTo4x3(m, out);
        PSMTXInverse(out, out);
        CObj_SetWorldMatrix(worldObj, out);
    }
}

#pragma exceptions reset

/* rest of the play camera .rodata: Tick's zero vector, file name */
extern const char lbl_802EE4FC[15] = "playcamera.cpp";

void ShadowBillboard_SetTargetSaturation(ShadowBillboard *sb, float value) {
    sb->targetSaturation = value;
}

#pragma exceptions on

int ShadowBillboard_TriggerSpinFlash(ShadowBillboard *sb) {
    if (sb->spinFlash == 1) {
        return 0;
    }
    sb->spinFlash = 0;
    sb->spinB0 = lbl_806D2B74;
    sb->spinB4 = lbl_806D2B74;
    sb->spinFlash = 1;
    sb->spinB0 = lbl_806D2B78;
    if (sb->active == 1) {
        CameraEffect_Apply(lbl_806D109C == 0 ? 0 : lbl_806D109C, 2, lbl_806D2C0C);
    }
    return 1;
}

#pragma exceptions reset

void ShadowBillboard_BeginFadeCleanup(ShadowBillboard *sb) {
    if (sb->fadeMode == 1) {
        return;
    }
    sb->fade60 = lbl_806D2B6C;
    sb->fade64 = lbl_806D2C10;
    sb->fadeMode = 1;
}

void ShadowBillboard_BeginBoostScale(ShadowBillboard *sb) {
    if (sb->fadeMode == 2) {
        return;
    }
    sb->fade60 = lbl_806D2B6C;
    sb->fade64 = lbl_806D2C14;
    sb->fadeMode = 2;
}

#pragma exceptions on

void Camera_RotateByYaw(PlayCamera *cam, float yaw) {
    Mtx44S rot;
    Mtx44S *dst = (Mtx44S *)cam->buffer;
    float c;
    float s;
    int i;

    for (i = 0; i < 16; i++) {
        rot.v[i] = 0.0f;
    }
    rot.v[0] = rot.v[5] = rot.v[10] = rot.v[15] = 1.0f;
    c = cosf(0.017453292519943295 * yaw);
    s = sinf(0.017453292519943295 * yaw);
    rot.v[0] = c;
    rot.v[8] = s;
    rot.v[10] = c;
    rot.v[2] = -s;
    Mtx44S_Mul(&rot, &rot, dst);
    *dst = rot;
}

#pragma exceptions reset

#pragma exceptions on

PlayCamera *PlayCamera_Dtor(PlayCamera *cam, short flags) {
    if (cam != 0) {
        if (&cam->buffer != 0) {
            MemoryManager_TimedFree(cam->buffer);
        }
        if (flags > 0) {
            MemoryManager_TimedFree(cam);
        }
    }
    return cam;
}

#pragma exceptions reset


#pragma exceptions on
C_REGION_END
#pragma cplusplus on

static inline void Mtx44_Identity(float *m) {
    int i;

    for (i = 0; i < 16; i++) {
        m[i] = 0.0f;
    }
    m[0] = m[5] = m[10] = m[15] = 1.0f;
}

struct PCVec3 {
    float x, y, z;
    PCVec3() {}
    ~PCVec3();
};

/* heap-owned 4x4 view matrix (dtor_80064CD4 frees it) */
struct PCMtxBuf {
    float *m;
    PCMtxBuf(float *p) : m(p) {}
    ~PCMtxBuf();
};

struct PCSpin {
    unsigned char on;
    float b0;
    float b4;
    PCSpin() : on(0), b0(0.0f), b4(0.0f) {}
    ~PCSpin();
};

struct PCShake {
    int timer;
    int fieldBC;
    Vec3f offset;
    PCShake() : timer(0), fieldBC(0) {
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = 0.0f;
    }
    ~PCShake();
};

struct clPlayCamera {
    unsigned char active;
    void *owner;
    int viewIndex;
    int multiView;
    void *scene;
    void *src;
    unsigned char flag18;
    unsigned char flag19;
    float mtx[16];
    PCMtxBuf view;
    float fade60;
    float fade64;
    int fadeMode;
    int field6C;
    PCVec3 vec70;
    PCVec3 camPos;
    PCVec3 axis;
    float field94;
    float field98;
    float targetSaturation;
    float fieldA0;
    float heightA4;
    float fieldA8;
    PCSpin spin;
    PCShake shake;
    int courseCam;
    float courseCamWeight;

    clPlayCamera(void *owner, int viewIndex, void *scene, void *src, unsigned char active,
                 unsigned char isPlayer, unsigned char flag18, float yaw);
    void RotateByYaw(float yaw) {
        Mtx44S rot;
        Mtx44S *dst = (Mtx44S *)view.m;
        float c;
        float s;
        int i;

        for (i = 0; i < 16; i++) {
            rot.v[i] = 0.0f;
        }
        rot.v[0] = rot.v[5] = rot.v[10] = rot.v[15] = 1.0f;
        c = cosf(0.017453292519943295 * yaw);
        s = sinf(0.017453292519943295 * yaw);
        rot.v[0] = c;
        rot.v[8] = s;
        rot.v[10] = c;
        rot.v[2] = -s;
        Mtx44S_Mul(&rot, &rot, dst);
        *dst = rot;
    }
};

clPlayCamera::clPlayCamera(void *owner_, int viewIndex_, void *scene_, void *src_, unsigned char active_,
                           unsigned char isPlayer, unsigned char flag18_, float yaw)
    : active(active_), owner(owner_), viewIndex(viewIndex_), multiView(viewIndex_ > 1), scene(scene_),
      src(src_), flag18(flag18_), flag19(1),
      view((float *)MemoryManager_AllocTagged(0x40, lbl_802EE4FC, 0x8E)),
      fade60(0.0f), fade64(0.0f), fadeMode(0), field6C(0),
      field98(0.0f), targetSaturation(0.0f), fieldA0(0.0f), heightA4(0.0f), fieldA8(0.0f) {
    if (isPlayer == 1) {
        fieldA0 = 1.0f;
    }
    Mtx44_Identity(view.m);
    RotateByYaw(180.0f + yaw);
    Mtx44_Identity(mtx);
    courseCamWeight = 0.0f;
    courseCam = -1;
    if (isPlayer == 1) {
        int mode = (int)g_gameMode;
        int round;
        int cup;
        int cc;
        int i;
        PCCourseCamEntry *e;

        if (mode == 0) {
            round = (int)g_roundIndex;
        } else if ((int)g_reverseRoundFlag == 0) {
            if ((int)g_longRoundFlag == 0) {
                round = 0;
            } else {
                round = 1;
            }
        } else if ((int)g_longRoundFlag == 0) {
            round = 4;
        } else {
            round = 5;
        }
        cup = (int)g_cupId;
        cc = (int)g_ccClass;
        for (i = 0; i < (int)PlayCamera_Init_data_806CEEF0; i++) {
            e = &ShadowBillboard_data_803F9F30[i];
            if ((e->gameMode == -1 || mode == e->gameMode) && (e->cupId == -1 || cup == e->cupId) &&
                (e->ccClass == -1 || cc == e->ccClass) && (e->roundType == -1 || round == e->roundType)) {
                courseCam = i;
                courseCamWeight = 1.0f;
                break;
            }
        }
        if (courseCam == -1) {
            fieldA0 = 0.0f;
        }
    }
}

struct OrthoVec {
    float x, y, z;
    OrthoVec(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    ~OrthoVec() {}
    OrthoVec &operator=(const OrthoVec &o) {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
    float Dot(const OrthoVec &o) const {
        float xx = x * o.x;
        float yy = y * o.y;
        float zz = z * o.z;
        return zz + (xx + yy);
    }
    void Cross(const OrthoVec &a, const OrthoVec &b) {
        float cx = a.y * b.z - a.z * b.y;
        float cy = a.z * b.x - a.x * b.z;
        float cz = a.x * b.y - a.y * b.x;
        x = cx;
        y = cy;
        z = cz;
    }
    void Normalize() {
        float len = MathInline_sqrtf(Dot(*this));
        if (len <= 0.0f) {
            z = 0.0f;
            y = 0.0f;
            x = 0.0f;
        } else {
            float s = 1.0f / len;
            x *= s;
            y *= s;
            z *= s;
        }
    }
};

extern "C" void Mtx34_Orthonormalize(float (*m)[4]) {
    OrthoVec x(m[0][0], m[0][1], m[0][2]);
    OrthoVec y(m[1][0], m[1][1], m[1][2]);
    OrthoVec z(m[2][0], m[2][1], m[2][2]);

    y = x;
    y.Cross(z, y);
    x = z;
    x.Cross(y, x);
    x.Normalize();
    y.Normalize();
    z.Normalize();
    m[0][0] = x.x;
    m[0][1] = x.y;
    m[0][2] = x.z;
    m[1][0] = y.x;
    m[1][1] = y.y;
    m[1][2] = y.z;
    m[2][0] = z.x;
    m[2][1] = z.y;
    m[2][2] = z.z;
}

#pragma cplusplus reset
C_REGION_BEGIN
#pragma exceptions reset
C_REGION_END

