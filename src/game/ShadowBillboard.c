/*
 * ShadowBillboard update/flash and the play camera, 0x80061954..0x80064CD4.
 * The large Tick/StepSimple/camera functions are still asm bodies.
 */

#include "game/MathInline.h"

/* sdata symbols referenced from asm */
extern unsigned char lbl_806D2BCC[7];
extern unsigned char lbl_806D2BD4[5];

typedef struct ShadowBillboardSrc {
    unsigned char pad000[0xF8];
    float axisX;
    float padFC;
    float axisZ;
} ShadowBillboardSrc;

typedef struct ShadowBillboard {
    unsigned char active; /* 0x00 */
    unsigned char pad01[0x14 - 0x01];
    ShadowBillboardSrc *src;
    unsigned char pad18[0x60 - 0x18];
    float fade60;
    float fade64;
    int fadeMode; /* 0x68 */
    int field6C;
    Vec3f vec70;
    Vec3f camPos;
    Vec3f axis;
    float field94;
    float targetSaturation; /* 0x98 */
    unsigned char pad9C[0xAC - 0x9C];
    unsigned char spinFlash; /* 0xAC */
    unsigned char padAD[3];
    float spinB0;
    float spinB4;
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
extern void CObj_ApplyViewport();
extern void CObj_GetViewMatrix_Cached();
extern void CObj_LinePath_Step();
extern void CObj_LoadIntoGX();
extern void CObj_SetWorldMatrix();
extern void FAbs_FloatAsDouble();
extern void MemoryManager_AllocTagged();
extern void Mtx4x4_TransposeTo4x3();
extern void PSMTXInverse();
extern void PSMTXMultVec();
extern void ShadowBillboard_LerpMtx4x4();
extern void ShadowBillboard_SetEffectParams();
extern void Terrain_GetGroundHeightWithPenetration();
extern void Vec3_Copy();
extern void Vec3_Lerp();
extern void __assert();
extern void cos();
extern void sin();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_cupId;
extern unsigned int g_gameMode;
extern unsigned int g_longRoundFlag;
extern unsigned int g_reverseRoundFlag;
extern unsigned int g_roundIndex;
extern unsigned int lbl_806CEEF0;
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
extern unsigned int lbl_802EE320[];
extern unsigned int lbl_802EE4FC[];
extern unsigned int lbl_803F9F30[];

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

/* --- forward decls --- */
asm void ShadowBillboard_Tick(void);
asm void ShadowBillboard_StepSimple(void);
asm void Camera_RotateByYaw(void);
asm void PlayCamera_Init(void);
asm void Mtx34_Orthonormalize(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void dtor_80036E40();
extern void dtor_8006178C();
extern void dtor_800617C8();
extern void dtor_80064CD4();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Mtx34_Orthonormalize[8] = {
    0x01, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_ShadowBillboard_Tick[8] = {
    0x59, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_ShadowBillboard_StepSimple[8] = {
    0x21, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_Camera_RotateByYaw[8] = {
    0x10, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; void *f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; unsigned int f11; void *f12; unsigned int f13; unsigned int f14; void *f15; unsigned int f16; unsigned int f17; void *f18; unsigned int f19; unsigned int f20; void *f21; } extab_PlayCamera_Init = { 0x208A0000, 0x000001B4, 0x00030010, 0x00000000, 0x0780001D, 0x000000B8, (void *)&dtor_8006178C, 0x0780001D, 0x000000AC, (void *)&dtor_800617C8, 0x0780001D, 0x00000088, (void *)&dtor_80036E40, 0x0780001D, 0x0000007C, (void *)&dtor_80036E40, 0x0780001D, 0x00000070, (void *)&dtor_80036E40, 0x8780001D, 0x0000005C, (void *)&dtor_80064CD4 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ShadowBillboard_Tick = {
    (void *)&ShadowBillboard_Tick, 0x00001E14, (void *)extab_ShadowBillboard_Tick
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ShadowBillboard_StepSimple = {
    (void *)&ShadowBillboard_StepSimple, 0x000005B4, (void *)extab_ShadowBillboard_StepSimple
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Camera_RotateByYaw = {
    (void *)&Camera_RotateByYaw, 0x00000380, (void *)extab_Camera_RotateByYaw
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_PlayCamera_Init = {
    (void *)&PlayCamera_Init, 0x00000614, (void *)&extab_PlayCamera_Init
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Mtx34_Orthonormalize = {
    (void *)&Mtx34_Orthonormalize, 0x000003B4, (void *)extab_Mtx34_Orthonormalize
};

/* --- asm function bodies (.text order = fn address order) --- */
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
    Vec3f_Set(&sb->axis, sb->src->axisX, 0.0f, sb->src->axisZ);
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

asm void ShadowBillboard_Tick(void) { /* 0x80061A88 size:0x1E14 */
    nofralloc
    stwu r1, -0x540(r1)
    mflr r0
    stw r0, 0x544(r1)
    stfd f31, 0x530(r1)
    psq_st f31, 0x538(r1), 0, 0
    stfd f30, 0x520(r1)
    psq_st f30, 0x528(r1), 0, 0
    stfd f29, 0x510(r1)
    psq_st f29, 0x518(r1), 0, 0
    stfd f28, 0x500(r1)
    psq_st f28, 0x508(r1), 0, 0
    stfd f27, 0x4f0(r1)
    psq_st f27, 0x4f8(r1), 0, 0
    stmw r21, 0x4c4(r1)
    mr r29, r3
    lis r3, lbl_802EE320@ha
    lbz r0, 0xac(r29)
    mr r30, r4
    mr r31, r5
    addi r28, r3, lbl_802EE320@l
    cmplwi r0, 0x0
    beq ShadowBillboard_Tick_L_80061B38
    lfs f2, 0xb4(r29)
    lfs f0, 0xb0(r29)
    lfs f1, lbl_806D2B74(r2)
    fadds f0, f2, f0
    stfs f0, 0xb4(r29)
    lfs f2, 0xb0(r29)
    fcmpo cr0, f2, f1
    ble ShadowBillboard_Tick_L_80061B1C
    lfs f1, 0xb4(r29)
    lfs f0, lbl_806D2B6C(r2)
    fcmpo cr0, f1, f0
    ble ShadowBillboard_Tick_L_80061B38
    fneg f0, f2
    stfs f0, 0xb0(r29)
    b ShadowBillboard_Tick_L_80061B38
    ShadowBillboard_Tick_L_80061B1C:
    lfs f0, 0xb4(r29)
    fcmpo cr0, f0, f1
    bge ShadowBillboard_Tick_L_80061B38
    li r0, 0x0
    stb r0, 0xac(r29)
    stfs f1, 0xb0(r29)
    stfs f1, 0xb4(r29)
    ShadowBillboard_Tick_L_80061B38:
    lwz r3, 0xb8(r29)
    neg r0, r3
    andc r0, r0, r3
    srwi. r0, r0, 31
    beq ShadowBillboard_Tick_L_80061C30
    lwz r3, 0xb8(r29)
    subi r0, r3, 0x1
    stw r0, 0xb8(r29)
    lwz r0, 0xb8(r29)
    clrlwi r0, r0, 30
    cmpwi r0, 0x1
    bgt ShadowBillboard_Tick_L_80061BB4
    bl GetCourseScene3D
    cmplwi r3, 0x0
    beq ShadowBillboard_Tick_L_80061BFC
    bl CObj_GetViewMatrix_Cached
    lfs f0, 0x0(r3)
    lfs f1, lbl_806D2B6C(r2)
    lfs f2, lbl_806D2B68(r2)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc0(r29)
    lfs f0, 0x10(r3)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc4(r29)
    lfs f0, 0x20(r3)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc8(r29)
    b ShadowBillboard_Tick_L_80061BFC
    ShadowBillboard_Tick_L_80061BB4:
    bl GetCourseScene3D
    cmplwi r3, 0x0
    beq ShadowBillboard_Tick_L_80061BFC
    bl CObj_GetViewMatrix_Cached
    lfs f0, 0x0(r3)
    lfs f1, lbl_806D2B70(r2)
    lfs f2, lbl_806D2B68(r2)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc0(r29)
    lfs f0, 0x10(r3)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc4(r29)
    lfs f0, 0x20(r3)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc8(r29)
    ShadowBillboard_Tick_L_80061BFC:
    lwz r3, 0xb8(r29)
    neg r0, r3
    andc r0, r0, r3
    srwi r0, r0, 31
    cmplwi r0, 0x1
    bne ShadowBillboard_Tick_L_80061C30
    li r0, 0x0
    lfs f0, lbl_806D2B74(r2)
    stw r0, 0xb8(r29)
    stw r0, 0xbc(r29)
    stfs f0, 0xc0(r29)
    stfs f0, 0xc4(r29)
    stfs f0, 0xc8(r29)
    ShadowBillboard_Tick_L_80061C30:
    lfs f3, 0x98(r29)
    lfs f2, 0x9c(r29)
    lfs f1, lbl_806D2BB8(r2)
    fsubs f0, f3, f2
    fcmpo cr0, f3, f2
    fabs f0, f0
    frsp f0, f0
    fmuls f0, f1, f0
    ble ShadowBillboard_Tick_L_80061C74
    fadds f0, f2, f0
    stfs f0, 0x9c(r29)
    lfs f1, 0x98(r29)
    lfs f0, 0x9c(r29)
    fcmpo cr0, f1, f0
    bge ShadowBillboard_Tick_L_80061C90
    stfs f1, 0x9c(r29)
    b ShadowBillboard_Tick_L_80061C90
    ShadowBillboard_Tick_L_80061C74:
    fsubs f0, f2, f0
    stfs f0, 0x9c(r29)
    lfs f1, 0x98(r29)
    lfs f0, 0x9c(r29)
    fcmpo cr0, f1, f0
    ble ShadowBillboard_Tick_L_80061C90
    stfs f1, 0x9c(r29)
    ShadowBillboard_Tick_L_80061C90:
    cmplwi r30, 0x0
    beq ShadowBillboard_Tick_L_800637A0
    lfs f2, 0xa0(r29)
    lfs f1, lbl_806D2B74(r2)
    fcmpo cr0, f2, f1
    ble ShadowBillboard_Tick_L_80061EE8
    lfs f0, lbl_806D2BBC(r2)
    fsubs f0, f2, f0
    stfs f0, 0xa0(r29)
    lfs f0, 0xa0(r29)
    fcmpo cr0, f0, f1
    bge ShadowBillboard_Tick_L_80061CC4
    stfs f1, 0xa0(r29)
    ShadowBillboard_Tick_L_80061CC4:
    lfs f1, lbl_806D2BC0(r2)
    lis r0, 0x4330
    lfs f0, 0xa0(r29)
    stw r0, 0x490(r1)
    fnmsubs f1, f1, f0, f1
    lfd f2, lbl_806D2C00(r2)
    lfs f0, lbl_806D2BC4(r2)
    fctiwz f1, f1
    stfd f1, 0x488(r1)
    lwz r3, 0x48c(r1)
    xoris r0, r3, 0x8000
    stw r0, 0x494(r1)
    lfd f1, 0x490(r1)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x498(r1)
    lwz r5, 0x49c(r1)
    cmpwi r5, 0x0
    bge ShadowBillboard_Tick_L_80061D18
    li r5, 0x0
    ShadowBillboard_Tick_L_80061D18:
    cmpwi r5, 0x2
    ble ShadowBillboard_Tick_L_80061D24
    li r5, 0x2
    ShadowBillboard_Tick_L_80061D24:
    lis r6, 0x4330
    xoris r0, r5, 0x8000
    xoris r4, r3, 0x8000
    stw r0, 0x4a4(r1)
    lwz r0, 0xcc(r29)
    lis r3, lbl_803F9F30@ha
    stw r6, 0x4a0(r1)
    mulli r28, r5, 0x24
    lfd f2, lbl_806D2C00(r2)
    addi r5, r3, lbl_803F9F30@l
    lfd f0, 0x4a0(r1)
    addi r3, r1, 0x6c
    stw r4, 0x4ac(r1)
    fsubs f1, f0, f2
    lfs f3, lbl_806D2BC4(r2)
    stw r6, 0x4a8(r1)
    mulli r0, r0, 0x7c
    addi r4, r1, 0x30
    lfd f0, 0x4a8(r1)
    add r0, r5, r0
    stw r6, 0x4b8(r1)
    fsubs f0, f0, f2
    add r6, r0, r28
    lwz r10, 0x10(r6)
    addi r5, r1, 0x24
    lwz r0, 0x14(r6)
    fnmsubs f0, f3, f1, f0
    lwz r9, 0x18(r6)
    lwz r8, 0x1c(r6)
    fctiwz f0, f0
    lwz r7, 0x20(r6)
    lwz r6, 0x24(r6)
    stw r10, 0x24(r1)
    stfd f0, 0x4b0(r1)
    lwz r21, 0x4b4(r1)
    stw r0, 0x28(r1)
    xoris r0, r21, 0x8000
    stw r0, 0x4bc(r1)
    lfd f0, 0x4b8(r1)
    stw r9, 0x2c(r1)
    fsubs f0, f0, f2
    stw r8, 0x30(r1)
    fdivs f1, f0, f3
    stw r7, 0x34(r1)
    stw r6, 0x38(r1)
    bl Vec3_Lerp
    mr r3, r30
    addi r4, r1, 0x6c
    bl CObj_LoadIntoGX
    lwz r4, 0xcc(r29)
    lis r3, lbl_803F9F30@ha
    addi r0, r3, lbl_803F9F30@l
    addi r3, r1, 0x60
    mulli r4, r4, 0x7c
    add r0, r0, r4
    add r4, r0, r28
    addi r4, r4, 0x28
    bl Vec3_Copy
    mr r3, r30
    addi r4, r1, 0x60
    bl CObj_ApplyViewport
    cmpwi r21, 0x14
    bge ShadowBillboard_Tick_L_80061E70
    lfs f2, 0xd0(r29)
    lfs f1, lbl_806D2BB8(r2)
    lfs f0, lbl_806D2B74(r2)
    fsubs f1, f2, f1
    stfs f1, 0xd0(r29)
    lfs f1, 0xd0(r29)
    fcmpo cr0, f1, f0
    bge ShadowBillboard_Tick_L_80061E44
    stfs f0, 0xd0(r29)
    ShadowBillboard_Tick_L_80061E44:
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne ShadowBillboard_Tick_L_80061E54
    li r3, 0x0
    ShadowBillboard_Tick_L_80061E54:
    lfs f1, lbl_806D2B74(r2)
    li r4, 0x5
    lfs f4, 0xd0(r29)
    fmr f2, f1
    fmr f3, f1
    bl ShadowBillboard_SetEffectParams
    b ShadowBillboard_Tick_L_800637A0
    ShadowBillboard_Tick_L_80061E70:
    xoris r3, r21, 0x8000
    lis r0, 0x4330
    stw r3, 0x4bc(r1)
    lfd f1, lbl_806D2C00(r2)
    stw r0, 0x4b8(r1)
    lfs f2, lbl_806D2BC8(r2)
    lfd f0, 0x4b8(r1)
    fsubs f0, f0, f1
    fcmpo cr0, f2, f0
    bge ShadowBillboard_Tick_L_800637A0
    lfs f2, 0xd0(r29)
    lfs f0, lbl_806D2BB8(r2)
    lfs f1, lbl_806D2B6C(r2)
    fadds f0, f2, f0
    stfs f0, 0xd0(r29)
    lfs f0, 0xd0(r29)
    fcmpo cr0, f1, f0
    bge ShadowBillboard_Tick_L_80061EBC
    stfs f1, 0xd0(r29)
    ShadowBillboard_Tick_L_80061EBC:
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne ShadowBillboard_Tick_L_80061ECC
    li r3, 0x0
    ShadowBillboard_Tick_L_80061ECC:
    lfs f1, lbl_806D2B74(r2)
    li r4, 0x5
    lfs f4, 0xd0(r29)
    fmr f2, f1
    fmr f3, f1
    bl ShadowBillboard_SetEffectParams
    b ShadowBillboard_Tick_L_800637A0
    ShadowBillboard_Tick_L_80061EE8:
    lbz r0, 0x18(r29)
    cmplwi r0, 0x0
    bne ShadowBillboard_Tick_L_8006290C
    lfs f0, 0xd0(r29)
    fcmpu cr0, f0, f1
    beq ShadowBillboard_Tick_L_80061F30
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne ShadowBillboard_Tick_L_80061F10
    li r3, 0x0
    ShadowBillboard_Tick_L_80061F10:
    lfs f1, lbl_806D2B74(r2)
    li r4, 0x5
    fmr f2, f1
    fmr f3, f1
    fmr f4, f1
    bl ShadowBillboard_SetEffectParams
    lfs f0, lbl_806D2B74(r2)
    stfs f0, 0xd0(r29)
    ShadowBillboard_Tick_L_80061F30:
    lwz r21, 0x4(r30)
    cmplwi r21, 0x0
    beq ShadowBillboard_Tick_L_80061F5C
    bne ShadowBillboard_Tick_L_80061F50
    la r3, lbl_806D2BCC(r2)  /* lbl_806D2BCC */
    li r4, 0x1ae
    la r5, lbl_806D2BD4(r2)  /* lbl_806D2BD4 */
    bl __assert
    ShadowBillboard_Tick_L_80061F50:
    lwz r0, 0x8(r21)
    rlwinm r0, r0, 0, 31, 29
    stw r0, 0x8(r21)
    ShadowBillboard_Tick_L_80061F5C:
    lfs f1, 0xa8(r29)
    lfs f0, lbl_806D2B74(r2)
    fcmpo cr0, f1, f0
    ble ShadowBillboard_Tick_L_80061F78
    lfs f0, lbl_806D2BDC(r2)
    fmuls f0, f1, f0
    stfs f0, 0xa8(r29)
    ShadowBillboard_Tick_L_80061F78:
    lwz r0, 0x4(r29)
    addi r5, r28, 0x0
    lwz r3, 0xc(r29)
    slwi r6, r0, 5
    lwz r0, 0x68(r29)
    slwi r4, r3, 4
    lfs f5, lbl_806D2BE0(r2)
    add r3, r5, r6
    lfs f2, lbl_806D2BB0(r2)
    add r3, r3, r4
    lfs f1, 0x9c(r29)
    lfs f0, 0x8(r3)
    add r4, r6, r4
    fmuls f1, f2, f1
    lfsx f4, r5, r4
    fmuls f0, f5, f0
    lfs f3, 0x4(r3)
    lfs f2, 0xa4(r29)
    cmpwi r0, 0x0
    fmadds f31, f5, f1, f0
    lfs f0, 0xc(r3)
    fmuls f30, f5, f4
    fmsubs f29, f5, f3, f2
    fmadds f28, f5, f0, f31
    bne ShadowBillboard_Tick_L_80061FE0
    b ShadowBillboard_Tick_L_80062088
    ShadowBillboard_Tick_L_80061FE0:
    lfs f2, 0x60(r29)
    lfs f1, 0x64(r29)
    lfs f0, lbl_806D2B74(r2)
    fsubs f1, f2, f1
    stfs f1, 0x60(r29)
    lfs f1, 0x60(r29)
    fcmpo cr0, f1, f0
    bge ShadowBillboard_Tick_L_80062004
    stfs f0, 0x60(r29)
    ShadowBillboard_Tick_L_80062004:
    lwz r0, 0x68(r29)
    cmpwi r0, 0x1
    bne ShadowBillboard_Tick_L_80062058
    lfs f1, lbl_806D2BB4(r2)
    lfs f0, 0x60(r29)
    lfd f2, lbl_806D2B80(r2)
    fmuls f0, f1, f0
    fmul f1, f2, f0
    frsp f1, f1
    bl sin
    frsp f3, f1
    lfs f1, 0x60(r29)
    lfs f0, lbl_806D2B74(r2)
    lfs f2, lbl_806D2B6C(r2)
    fcmpo cr0, f1, f0
    fsubs f1, f2, f3
    cror eq, lt, eq
    bne ShadowBillboard_Tick_L_80062078
    li r0, 0x0
    stw r0, 0x68(r29)
    b ShadowBillboard_Tick_L_80062078
    ShadowBillboard_Tick_L_80062058:
    lfs f1, lbl_806D2BB4(r2)
    lfs f0, 0x60(r29)
    lfd f2, lbl_806D2B80(r2)
    fmuls f0, f1, f0
    fmul f1, f2, f0
    frsp f1, f1
    bl sin
    frsp f1, f1
    ShadowBillboard_Tick_L_80062078:
    lfs f0, lbl_806D2B6C(r2)
    fsubs f0, f0, f1
    fmuls f0, f28, f0
    fmadds f31, f31, f1, f0
    ShadowBillboard_Tick_L_80062088:
    lwz r3, 0x14(r29)
    addi r21, r1, 0x1f8
    lfs f2, lbl_806D2B74(r2)
    lfs f3, 0xd8(r3)
    stfs f2, 0x1f8(r1)
    lfs f0, lbl_806D2B6C(r2)
    stfs f3, 0x448(r1)
    lfd f1, lbl_806D2BA8(r2)
    lfs f3, 0xdc(r3)
    stfs f2, 0x20c(r1)
    stfs f3, 0x44c(r1)
    lfs f3, 0xe0(r3)
    stfs f2, 0x220(r1)
    stfs f3, 0x450(r1)
    lfs f3, 0xe4(r3)
    stfs f2, 0x234(r1)
    stfs f3, 0x454(r1)
    lfs f3, 0xe8(r3)
    stfs f2, 0x1fc(r1)
    stfs f3, 0x458(r1)
    lfs f3, 0xec(r3)
    stfs f2, 0x200(r1)
    stfs f3, 0x45c(r1)
    lfs f3, 0xf0(r3)
    stfs f2, 0x204(r1)
    stfs f3, 0x460(r1)
    lfs f3, 0xf4(r3)
    stfs f2, 0x208(r1)
    stfs f3, 0x464(r1)
    lfs f3, 0xf8(r3)
    stfs f2, 0x210(r1)
    stfs f3, 0x468(r1)
    lfs f3, 0xfc(r3)
    stfs f2, 0x214(r1)
    stfs f3, 0x46c(r1)
    lfs f3, 0x100(r3)
    stfs f2, 0x218(r1)
    stfs f3, 0x470(r1)
    lfs f3, 0x104(r3)
    stfs f2, 0x21c(r1)
    stfs f3, 0x474(r1)
    lfs f3, 0x108(r3)
    stfs f2, 0x224(r1)
    stfs f3, 0x478(r1)
    lfs f3, 0x10c(r3)
    stfs f2, 0x228(r1)
    stfs f3, 0x47c(r1)
    lfs f3, 0x110(r3)
    stfs f2, 0x22c(r1)
    stfs f3, 0x480(r1)
    lfs f3, 0x114(r3)
    stfs f2, 0x230(r1)
    stfs f3, 0x484(r1)
    stfs f0, 0x234(r1)
    stfs f0, 0x220(r1)
    stfs f0, 0x20c(r1)
    stfs f0, 0x1f8(r1)
    bl cos
    frsp f28, f1
    lfd f1, lbl_806D2BA8(r2)
    bl sin
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f28, 0x1f8(r1)
    mr r4, r5
    addi r6, r1, 0xb8
    fneg f0, f1
    stfs f1, 0x218(r1)
    stfs f28, 0x220(r1)
    stfs f0, 0x200(r1)
    mtctr r0
    ShadowBillboard_Tick_L_800621A8:
    lfs f7, 0x0(r21)
    slwi r0, r5, 2
    lfs f6, 0x448(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r21)
    fmuls f8, f7, f6
    lfs f4, 0x458(r1)
    lfs f3, 0x8(r21)
    lfs f2, 0x468(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r21)
    lfs f0, 0x478(r1)
    lfs f6, 0x44c(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x45c(r1)
    lfs f2, 0x46c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x47c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x450(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x460(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x470(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x480(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x454(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x464(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x474(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x484(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r21)
    slwi r0, r5, 2
    lfs f6, 0x448(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r21)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x458(r1)
    lfs f3, 0x18(r21)
    lfs f1, 0x1c(r21)
    addi r21, r21, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x468(r1)
    lfs f0, 0x478(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x44c(r1)
    lfs f4, 0x45c(r1)
    lfs f2, 0x46c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x47c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x450(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x460(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x470(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x480(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x454(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x464(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x474(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x484(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz ShadowBillboard_Tick_L_800621A8
    lfs f8, 0xb8(r1)
    addi r27, r1, 0x2b8
    lfs f7, 0xbc(r1)
    stfs f8, 0x1f8(r1)
    lfs f6, 0xc0(r1)
    stfs f7, 0x1fc(r1)
    lfs f5, 0xc4(r1)
    stfs f6, 0x200(r1)
    lfs f4, 0xc8(r1)
    stfs f5, 0x204(r1)
    lfs f3, 0xcc(r1)
    stfs f4, 0x208(r1)
    lfs f1, 0xd0(r1)
    stfs f3, 0x20c(r1)
    lfs f0, 0xd4(r1)
    stfs f1, 0x210(r1)
    lfs f8, 0xd8(r1)
    stfs f0, 0x214(r1)
    lfs f7, 0xdc(r1)
    lfs f6, 0xe0(r1)
    lfs f5, 0xe4(r1)
    lfs f4, 0xe8(r1)
    lfs f3, 0xec(r1)
    lfs f2, lbl_806D2B74(r2)
    lfs f1, 0xf0(r1)
    lfs f0, 0xf4(r1)
    stfs f8, 0x218(r1)
    lwz r25, 0x1f8(r1)
    stfs f7, 0x21c(r1)
    lwz r24, 0x1fc(r1)
    stfs f6, 0x220(r1)
    lwz r23, 0x200(r1)
    stfs f5, 0x224(r1)
    lwz r22, 0x204(r1)
    stfs f4, 0x228(r1)
    lwz r21, 0x208(r1)
    stfs f3, 0x22c(r1)
    lwz r12, 0x20c(r1)
    stfs f1, 0x230(r1)
    lwz r11, 0x210(r1)
    stfs f0, 0x234(r1)
    lwz r10, 0x214(r1)
    lwz r9, 0x218(r1)
    lwz r8, 0x21c(r1)
    lwz r7, 0x220(r1)
    lwz r6, 0x224(r1)
    lwz r5, 0x228(r1)
    lwz r4, 0x22c(r1)
    lwz r3, 0x230(r1)
    lwz r0, 0x234(r1)
    stw r25, 0x448(r1)
    lfs f3, lbl_806D2B88(r2)
    stw r24, 0x44c(r1)
    lfd f4, lbl_806D2B80(r2)
    stw r23, 0x450(r1)
    lfs f0, lbl_806D2B6C(r2)
    stfs f2, 0x2b8(r1)
    stfs f2, 0x2cc(r1)
    stfs f2, 0x2e0(r1)
    stfs f2, 0x2f4(r1)
    stw r22, 0x454(r1)
    stw r21, 0x458(r1)
    stw r12, 0x45c(r1)
    stw r11, 0x460(r1)
    stw r10, 0x464(r1)
    stw r9, 0x468(r1)
    stw r8, 0x46c(r1)
    stw r7, 0x470(r1)
    stw r6, 0x474(r1)
    stw r5, 0x478(r1)
    stw r4, 0x47c(r1)
    stw r3, 0x480(r1)
    stw r0, 0x484(r1)
    lfs f1, 0xb4(r29)
    stfs f2, 0x2bc(r1)
    fneg f1, f1
    stfs f2, 0x2c0(r1)
    fmuls f1, f3, f1
    stfs f2, 0x2c4(r1)
    stfs f2, 0x2c8(r1)
    fmul f28, f4, f1
    stfs f2, 0x2d0(r1)
    stfs f2, 0x2d4(r1)
    frsp f28, f28
    stfs f2, 0x2d8(r1)
    fmr f1, f28
    stfs f2, 0x2dc(r1)
    stfs f2, 0x2e4(r1)
    stfs f2, 0x2e8(r1)
    stfs f2, 0x2ec(r1)
    stfs f2, 0x2f0(r1)
    stfs f0, 0x2f4(r1)
    stfs f0, 0x2e0(r1)
    stfs f0, 0x2cc(r1)
    stfs f0, 0x2b8(r1)
    bl cos
    frsp f27, f1
    fmr f1, f28
    bl sin
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f27, 0x2e0(r1)
    mr r4, r5
    addi r6, r1, 0x1b8
    fneg f0, f1
    stfs f1, 0x2d0(r1)
    stfs f27, 0x2cc(r1)
    stfs f0, 0x2dc(r1)
    mtctr r0
    ShadowBillboard_Tick_L_800624EC:
    lfs f7, 0x0(r27)
    slwi r0, r5, 2
    lfs f6, 0x448(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r27)
    fmuls f8, f7, f6
    lfs f4, 0x458(r1)
    lfs f3, 0x8(r27)
    lfs f2, 0x468(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r27)
    lfs f0, 0x478(r1)
    lfs f6, 0x44c(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x45c(r1)
    lfs f2, 0x46c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x47c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x450(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x460(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x470(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x480(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x454(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x464(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x474(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x484(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r27)
    slwi r0, r5, 2
    lfs f6, 0x448(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r27)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x458(r1)
    lfs f3, 0x18(r27)
    lfs f1, 0x1c(r27)
    addi r27, r27, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x468(r1)
    lfs f0, 0x478(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x44c(r1)
    lfs f4, 0x45c(r1)
    lfs f2, 0x46c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x47c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x450(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x460(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x470(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x480(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x454(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x464(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x474(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x484(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz ShadowBillboard_Tick_L_800624EC
    lfs f7, 0x1b8(r1)
    mr r3, r29
    lfs f6, 0x1bc(r1)
    addi r4, r1, 0x448
    stfs f7, 0x2b8(r1)
    lfs f5, 0x1c0(r1)
    stfs f6, 0x2bc(r1)
    lfs f4, 0x1c4(r1)
    stfs f5, 0x2c0(r1)
    lfs f3, 0x1c8(r1)
    stfs f4, 0x2c4(r1)
    lfs f2, 0x1cc(r1)
    stfs f3, 0x2c8(r1)
    lfs f1, 0x1d0(r1)
    stfs f2, 0x2cc(r1)
    lfs f0, 0x1d4(r1)
    stfs f1, 0x2d0(r1)
    lfs f7, 0x1d8(r1)
    stfs f0, 0x2d4(r1)
    lfs f6, 0x1dc(r1)
    lfs f5, 0x1e0(r1)
    lfs f4, 0x1e4(r1)
    lfs f3, 0x1e8(r1)
    lfs f2, 0x1ec(r1)
    lfs f1, 0x1f0(r1)
    lfs f0, 0x1f4(r1)
    stfs f7, 0x2d8(r1)
    lwz r27, 0x2b8(r1)
    stfs f6, 0x2dc(r1)
    lwz r26, 0x2bc(r1)
    stfs f5, 0x2e0(r1)
    lwz r25, 0x2c0(r1)
    stfs f4, 0x2e4(r1)
    lwz r24, 0x2c4(r1)
    stfs f3, 0x2e8(r1)
    lwz r23, 0x2c8(r1)
    stfs f2, 0x2ec(r1)
    lwz r22, 0x2cc(r1)
    stfs f1, 0x2f0(r1)
    lwz r21, 0x2d0(r1)
    stfs f0, 0x2f4(r1)
    lwz r12, 0x2d4(r1)
    lwz r11, 0x2d8(r1)
    lwz r10, 0x2dc(r1)
    lwz r9, 0x2e0(r1)
    lwz r8, 0x2e4(r1)
    lwz r7, 0x2e8(r1)
    lwz r6, 0x2ec(r1)
    lwz r5, 0x2f0(r1)
    lwz r0, 0x2f4(r1)
    stw r27, 0x448(r1)
    stw r26, 0x44c(r1)
    stw r25, 0x450(r1)
    stw r24, 0x454(r1)
    stw r23, 0x458(r1)
    stw r22, 0x45c(r1)
    stw r21, 0x460(r1)
    stw r12, 0x464(r1)
    stw r11, 0x468(r1)
    stw r10, 0x46c(r1)
    stw r9, 0x470(r1)
    stw r8, 0x474(r1)
    stw r7, 0x478(r1)
    stw r6, 0x47c(r1)
    stw r5, 0x480(r1)
    stw r0, 0x484(r1)
    lwz r5, 0x14(r29)
    lfs f1, 0x1d8(r5)
    bl ShadowBillboard_LerpMtx4x4
    lwz r3, 0x5c(r29)
    addi r4, r1, 0x418
    bl Mtx4x4_TransposeTo4x3
    lwz r3, 0xb8(r29)
    neg r0, r3
    andc r0, r0, r3
    srwi r0, r0, 31
    cmplwi r0, 0x1
    bne ShadowBillboard_Tick_L_800627D0
    lwz r4, 0xc0(r29)
    addi r8, r1, 0x18
    lwz r3, 0xc4(r29)
    lwz r0, 0xc8(r29)
    stw r4, 0x18(r1)
    stw r3, 0x1c(r1)
    stw r0, 0x20(r1)
    b ShadowBillboard_Tick_L_800627EC
    ShadowBillboard_Tick_L_800627D0:
    lwz r4, 0x1d0(r28)
    addi r8, r1, 0x18
    lwz r3, 0x1d4(r28)
    lwz r0, 0x1d8(r28)
    stw r4, 0x18(r1)
    stw r3, 0x1c(r1)
    stw r0, 0x20(r1)
    ShadowBillboard_Tick_L_800627EC:
    lwz r7, 0x0(r8)
    addi r4, r1, 0x48
    lwz r6, 0x4(r8)
    mr r5, r4
    lwz r0, 0x8(r8)
    addi r3, r1, 0x418
    stw r7, 0x54(r1)
    lfs f1, 0x424(r1)
    stw r6, 0x58(r1)
    lfs f0, 0x54(r1)
    stw r0, 0x5c(r1)
    fadds f5, f1, f0
    lfs f0, lbl_806D2B74(r2)
    lwz r7, 0x1c4(r28)
    lwz r6, 0x1c8(r28)
    lwz r0, 0x1cc(r28)
    lfs f4, 0x434(r1)
    lfs f3, 0x58(r1)
    lfs f2, 0x444(r1)
    lfs f1, 0x5c(r1)
    fadds f3, f4, f3
    stfs f5, 0x424(r1)
    fadds f1, f2, f1
    stfs f3, 0x434(r1)
    stfs f1, 0x444(r1)
    stfs f0, 0x8(r1)
    stw r7, 0x48(r1)
    stw r6, 0x4c(r1)
    stw r0, 0x50(r1)
    lfs f0, 0xa8(r29)
    fadds f1, f29, f0
    fsubs f0, f31, f0
    stfs f1, 0x4c(r1)
    stfs f0, 0x50(r1)
    bl PSMTXMultVec
    lfs f1, lbl_806D2BE4(r2)
    addi r3, r1, 0x48
    addi r4, r1, 0x8
    li r5, 0x0
    li r6, 0x0
    bl Terrain_GetGroundHeightWithPenetration
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne ShadowBillboard_Tick_L_800628E8
    lfs f0, 0x4c(r1)
    lfs f1, 0x8(r1)
    fcmpo cr0, f0, f1
    bge ShadowBillboard_Tick_L_800628E8
    fsubs f1, f1, f0
    bl FAbs_FloatAsDouble
    lfs f0, lbl_806D2BE8(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne ShadowBillboard_Tick_L_800628CC
    stfs f0, 0xa8(r29)
    b ShadowBillboard_Tick_L_800628E8
    ShadowBillboard_Tick_L_800628CC:
    lfs f1, 0x8(r1)
    lfs f0, 0x4c(r1)
    lfs f2, lbl_806D2BEC(r2)
    fsubs f1, f1, f0
    lfs f0, 0xa8(r29)
    fmadds f0, f2, f1, f0
    stfs f0, 0xa8(r29)
    ShadowBillboard_Tick_L_800628E8:
    lfs f0, 0xa8(r29)
    fmr f1, f30
    mr r3, r30
    addi r4, r1, 0x418
    fadds f29, f29, f0
    fsubs f3, f31, f0
    fmr f2, f29
    bl CObj_LinePath_Step
    b ShadowBillboard_Tick_L_800637A0
    ShadowBillboard_Tick_L_8006290C:
    lfs f0, 0xd0(r29)
    fcmpu cr0, f0, f1
    beq ShadowBillboard_Tick_L_80062948
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne ShadowBillboard_Tick_L_80062928
    li r3, 0x0
    ShadowBillboard_Tick_L_80062928:
    lfs f1, lbl_806D2B74(r2)
    li r4, 0x5
    fmr f2, f1
    fmr f3, f1
    fmr f4, f1
    bl ShadowBillboard_SetEffectParams
    lfs f0, lbl_806D2B74(r2)
    stfs f0, 0xd0(r29)
    ShadowBillboard_Tick_L_80062948:
    lwz r3, 0x14(r29)
    addi r21, r1, 0x178
    lfs f2, lbl_806D2B74(r2)
    lfs f3, 0xd8(r3)
    stfs f2, 0x178(r1)
    lfs f0, lbl_806D2B6C(r2)
    stfs f3, 0x3d8(r1)
    lfd f1, lbl_806D2BA8(r2)
    lfs f3, 0xdc(r3)
    stfs f2, 0x18c(r1)
    stfs f3, 0x3dc(r1)
    lfs f3, 0xe0(r3)
    stfs f2, 0x1a0(r1)
    stfs f3, 0x3e0(r1)
    lfs f3, 0xe4(r3)
    stfs f2, 0x1b4(r1)
    stfs f3, 0x3e4(r1)
    lfs f3, 0xe8(r3)
    stfs f2, 0x17c(r1)
    stfs f3, 0x3e8(r1)
    lfs f3, 0xec(r3)
    stfs f2, 0x180(r1)
    stfs f3, 0x3ec(r1)
    lfs f3, 0xf0(r3)
    stfs f2, 0x184(r1)
    stfs f3, 0x3f0(r1)
    lfs f3, 0xf4(r3)
    stfs f2, 0x188(r1)
    stfs f3, 0x3f4(r1)
    lfs f3, 0xf8(r3)
    stfs f2, 0x190(r1)
    stfs f3, 0x3f8(r1)
    lfs f3, 0xfc(r3)
    stfs f2, 0x194(r1)
    stfs f3, 0x3fc(r1)
    lfs f3, 0x100(r3)
    stfs f2, 0x198(r1)
    stfs f3, 0x400(r1)
    lfs f3, 0x104(r3)
    stfs f2, 0x19c(r1)
    stfs f3, 0x404(r1)
    lfs f3, 0x108(r3)
    stfs f2, 0x1a4(r1)
    stfs f3, 0x408(r1)
    lfs f3, 0x10c(r3)
    stfs f2, 0x1a8(r1)
    stfs f3, 0x40c(r1)
    lfs f3, 0x110(r3)
    stfs f2, 0x1ac(r1)
    stfs f3, 0x410(r1)
    lfs f3, 0x114(r3)
    stfs f2, 0x1b0(r1)
    stfs f3, 0x414(r1)
    stfs f0, 0x1b4(r1)
    stfs f0, 0x1a0(r1)
    stfs f0, 0x18c(r1)
    stfs f0, 0x178(r1)
    bl cos
    frsp f27, f1
    lfd f1, lbl_806D2BA8(r2)
    bl sin
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f27, 0x178(r1)
    mr r4, r5
    addi r6, r1, 0x78
    fneg f0, f1
    stfs f1, 0x198(r1)
    stfs f27, 0x1a0(r1)
    stfs f0, 0x180(r1)
    mtctr r0
    ShadowBillboard_Tick_L_80062A68:
    lfs f7, 0x0(r21)
    slwi r0, r5, 2
    lfs f6, 0x3d8(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r21)
    fmuls f8, f7, f6
    lfs f4, 0x3e8(r1)
    lfs f3, 0x8(r21)
    lfs f2, 0x3f8(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r21)
    lfs f0, 0x408(r1)
    lfs f6, 0x3dc(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x3ec(r1)
    lfs f2, 0x3fc(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x40c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x3e0(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x3f0(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x400(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x410(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x3e4(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x3f4(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x404(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x414(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r21)
    slwi r0, r5, 2
    lfs f6, 0x3d8(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r21)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x3e8(r1)
    lfs f3, 0x18(r21)
    lfs f1, 0x1c(r21)
    addi r21, r21, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x3f8(r1)
    lfs f0, 0x408(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x3dc(r1)
    lfs f4, 0x3ec(r1)
    lfs f2, 0x3fc(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x40c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x3e0(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x3f0(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x400(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x410(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x3e4(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x3f4(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x404(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x414(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz ShadowBillboard_Tick_L_80062A68
    lfs f8, 0x78(r1)
    addi r27, r1, 0x278
    lfs f7, 0x7c(r1)
    stfs f8, 0x178(r1)
    lfs f6, 0x80(r1)
    stfs f7, 0x17c(r1)
    lfs f5, 0x84(r1)
    stfs f6, 0x180(r1)
    lfs f4, 0x88(r1)
    stfs f5, 0x184(r1)
    lfs f3, 0x8c(r1)
    stfs f4, 0x188(r1)
    lfs f1, 0x90(r1)
    stfs f3, 0x18c(r1)
    lfs f0, 0x94(r1)
    stfs f1, 0x190(r1)
    lfs f8, 0x98(r1)
    stfs f0, 0x194(r1)
    lfs f7, 0x9c(r1)
    lfs f6, 0xa0(r1)
    lfs f5, 0xa4(r1)
    lfs f4, 0xa8(r1)
    lfs f3, 0xac(r1)
    lfs f2, lbl_806D2B74(r2)
    lfs f1, 0xb0(r1)
    lfs f0, 0xb4(r1)
    stfs f8, 0x198(r1)
    lwz r25, 0x178(r1)
    stfs f7, 0x19c(r1)
    lwz r24, 0x17c(r1)
    stfs f6, 0x1a0(r1)
    lwz r23, 0x180(r1)
    stfs f5, 0x1a4(r1)
    lwz r22, 0x184(r1)
    stfs f4, 0x1a8(r1)
    lwz r21, 0x188(r1)
    stfs f3, 0x1ac(r1)
    lwz r12, 0x18c(r1)
    stfs f1, 0x1b0(r1)
    lwz r11, 0x190(r1)
    stfs f0, 0x1b4(r1)
    lwz r10, 0x194(r1)
    lwz r9, 0x198(r1)
    lwz r8, 0x19c(r1)
    lwz r7, 0x1a0(r1)
    lwz r6, 0x1a4(r1)
    lwz r5, 0x1a8(r1)
    lwz r4, 0x1ac(r1)
    lwz r3, 0x1b0(r1)
    lwz r0, 0x1b4(r1)
    stw r25, 0x3d8(r1)
    lfs f3, lbl_806D2B88(r2)
    stw r24, 0x3dc(r1)
    lfd f4, lbl_806D2B80(r2)
    stw r23, 0x3e0(r1)
    lfs f0, lbl_806D2B6C(r2)
    stfs f2, 0x278(r1)
    stfs f2, 0x28c(r1)
    stfs f2, 0x2a0(r1)
    stfs f2, 0x2b4(r1)
    stw r22, 0x3e4(r1)
    stw r21, 0x3e8(r1)
    stw r12, 0x3ec(r1)
    stw r11, 0x3f0(r1)
    stw r10, 0x3f4(r1)
    stw r9, 0x3f8(r1)
    stw r8, 0x3fc(r1)
    stw r7, 0x400(r1)
    stw r6, 0x404(r1)
    stw r5, 0x408(r1)
    stw r4, 0x40c(r1)
    stw r3, 0x410(r1)
    stw r0, 0x414(r1)
    lfs f1, 0xb4(r29)
    stfs f2, 0x27c(r1)
    fneg f1, f1
    stfs f2, 0x280(r1)
    fmuls f1, f3, f1
    stfs f2, 0x284(r1)
    stfs f2, 0x288(r1)
    fmul f27, f4, f1
    stfs f2, 0x290(r1)
    stfs f2, 0x294(r1)
    frsp f27, f27
    stfs f2, 0x298(r1)
    fmr f1, f27
    stfs f2, 0x29c(r1)
    stfs f2, 0x2a4(r1)
    stfs f2, 0x2a8(r1)
    stfs f2, 0x2ac(r1)
    stfs f2, 0x2b0(r1)
    stfs f0, 0x2b4(r1)
    stfs f0, 0x2a0(r1)
    stfs f0, 0x28c(r1)
    stfs f0, 0x278(r1)
    bl cos
    frsp f28, f1
    fmr f1, f27
    bl sin
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f28, 0x2a0(r1)
    mr r4, r5
    addi r6, r1, 0x138
    fneg f0, f1
    stfs f1, 0x290(r1)
    stfs f28, 0x28c(r1)
    stfs f0, 0x29c(r1)
    mtctr r0
    ShadowBillboard_Tick_L_80062DAC:
    lfs f7, 0x0(r27)
    slwi r0, r5, 2
    lfs f6, 0x3d8(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r27)
    fmuls f8, f7, f6
    lfs f4, 0x3e8(r1)
    lfs f3, 0x8(r27)
    lfs f2, 0x3f8(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r27)
    lfs f0, 0x408(r1)
    lfs f6, 0x3dc(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x3ec(r1)
    lfs f2, 0x3fc(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x40c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x3e0(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x3f0(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x400(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x410(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x3e4(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x3f4(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x404(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x414(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r27)
    slwi r0, r5, 2
    lfs f6, 0x3d8(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r27)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x3e8(r1)
    lfs f3, 0x18(r27)
    lfs f1, 0x1c(r27)
    addi r27, r27, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x3f8(r1)
    lfs f0, 0x408(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x3dc(r1)
    lfs f4, 0x3ec(r1)
    lfs f2, 0x3fc(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x40c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x3e0(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x3f0(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x400(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x410(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x3e4(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x3f4(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x404(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x414(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz ShadowBillboard_Tick_L_80062DAC
    lfs f7, 0x138(r1)
    mr r3, r29
    lfs f6, 0x13c(r1)
    addi r4, r1, 0x3d8
    stfs f7, 0x278(r1)
    lfs f5, 0x140(r1)
    stfs f6, 0x27c(r1)
    lfs f4, 0x144(r1)
    stfs f5, 0x280(r1)
    lfs f3, 0x148(r1)
    stfs f4, 0x284(r1)
    lfs f2, 0x14c(r1)
    stfs f3, 0x288(r1)
    lfs f1, 0x150(r1)
    stfs f2, 0x28c(r1)
    lfs f0, 0x154(r1)
    stfs f1, 0x290(r1)
    lfs f7, 0x158(r1)
    stfs f0, 0x294(r1)
    lfs f6, 0x15c(r1)
    lfs f5, 0x160(r1)
    lfs f4, 0x164(r1)
    lfs f3, 0x168(r1)
    lfs f2, 0x16c(r1)
    lfs f1, 0x170(r1)
    lfs f0, 0x174(r1)
    stfs f7, 0x298(r1)
    lwz r21, 0x278(r1)
    stfs f6, 0x29c(r1)
    lwz r22, 0x27c(r1)
    stfs f5, 0x2a0(r1)
    lwz r27, 0x280(r1)
    stfs f4, 0x2a4(r1)
    lwz r26, 0x284(r1)
    stfs f3, 0x2a8(r1)
    lwz r25, 0x288(r1)
    stfs f2, 0x2ac(r1)
    lwz r24, 0x28c(r1)
    stfs f1, 0x2b0(r1)
    lwz r23, 0x290(r1)
    stfs f0, 0x2b4(r1)
    lwz r12, 0x294(r1)
    lwz r11, 0x298(r1)
    lwz r10, 0x29c(r1)
    lwz r9, 0x2a0(r1)
    lwz r8, 0x2a4(r1)
    lwz r7, 0x2a8(r1)
    lwz r6, 0x2ac(r1)
    lwz r5, 0x2b0(r1)
    lwz r0, 0x2b4(r1)
    stw r21, 0x3d8(r1)
    stw r22, 0x3dc(r1)
    stw r27, 0x3e0(r1)
    stw r26, 0x3e4(r1)
    stw r25, 0x3e8(r1)
    stw r24, 0x3ec(r1)
    stw r23, 0x3f0(r1)
    stw r12, 0x3f4(r1)
    stw r11, 0x3f8(r1)
    stw r10, 0x3fc(r1)
    stw r9, 0x400(r1)
    stw r8, 0x404(r1)
    stw r7, 0x408(r1)
    stw r6, 0x40c(r1)
    stw r5, 0x410(r1)
    stw r0, 0x414(r1)
    lwz r5, 0x14(r29)
    lfs f1, 0x1d8(r5)
    bl ShadowBillboard_LerpMtx4x4
    lwz r3, 0x14(r29)
    addi r27, r1, 0x398
    lfs f2, lbl_806D2B74(r2)
    addi r21, r1, 0x238
    lfs f3, 0x58(r3)
    stfs f2, 0x238(r1)
    lfs f0, lbl_806D2B6C(r2)
    stfs f3, 0x398(r1)
    lfd f1, lbl_806D2BA8(r2)
    lfs f3, 0x5c(r3)
    stfs f2, 0x24c(r1)
    stfs f3, 0x39c(r1)
    lfs f3, 0x60(r3)
    stfs f2, 0x260(r1)
    stfs f3, 0x3a0(r1)
    lfs f3, 0x64(r3)
    stfs f2, 0x274(r1)
    stfs f3, 0x3a4(r1)
    lfs f3, 0x68(r3)
    stfs f2, 0x23c(r1)
    stfs f3, 0x3a8(r1)
    lfs f3, 0x6c(r3)
    stfs f2, 0x240(r1)
    stfs f3, 0x3ac(r1)
    lfs f3, 0x70(r3)
    stfs f2, 0x244(r1)
    stfs f3, 0x3b0(r1)
    lfs f3, 0x74(r3)
    stfs f2, 0x248(r1)
    stfs f3, 0x3b4(r1)
    lfs f3, 0x78(r3)
    stfs f2, 0x250(r1)
    stfs f3, 0x3b8(r1)
    lfs f3, 0x7c(r3)
    stfs f2, 0x254(r1)
    stfs f3, 0x3bc(r1)
    lfs f3, 0x80(r3)
    stfs f2, 0x258(r1)
    stfs f3, 0x3c0(r1)
    lfs f3, 0x84(r3)
    stfs f2, 0x25c(r1)
    stfs f3, 0x3c4(r1)
    lfs f3, 0x88(r3)
    stfs f2, 0x264(r1)
    stfs f3, 0x3c8(r1)
    lfs f3, 0x8c(r3)
    stfs f2, 0x268(r1)
    stfs f3, 0x3cc(r1)
    lfs f3, 0x90(r3)
    stfs f2, 0x26c(r1)
    stfs f3, 0x3d0(r1)
    lfs f3, 0x94(r3)
    stfs f2, 0x270(r1)
    stfs f3, 0x3d4(r1)
    stfs f0, 0x274(r1)
    stfs f0, 0x260(r1)
    stfs f0, 0x24c(r1)
    stfs f0, 0x238(r1)
    bl cos
    frsp f27, f1
    lfd f1, lbl_806D2BA8(r2)
    bl sin
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f27, 0x238(r1)
    mr r4, r5
    addi r6, r1, 0xf8
    fneg f0, f1
    stfs f1, 0x258(r1)
    stfs f27, 0x260(r1)
    stfs f0, 0x240(r1)
    mtctr r0
    ShadowBillboard_Tick_L_80063170:
    lfs f7, 0x0(r21)
    slwi r0, r5, 2
    lfs f6, 0x398(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r21)
    fmuls f8, f7, f6
    lfs f4, 0x3a8(r1)
    lfs f3, 0x8(r21)
    lfs f2, 0x3b8(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r21)
    lfs f0, 0x3c8(r1)
    lfs f6, 0x39c(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x3ac(r1)
    lfs f2, 0x3bc(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3cc(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x3a0(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x3b0(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x3c0(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3d0(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x3a4(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x3b4(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x3c4(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3d4(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r21)
    slwi r0, r5, 2
    lfs f6, 0x398(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r21)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x3a8(r1)
    lfs f3, 0x18(r21)
    lfs f1, 0x1c(r21)
    addi r21, r21, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x3b8(r1)
    lfs f0, 0x3c8(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x39c(r1)
    lfs f4, 0x3ac(r1)
    lfs f2, 0x3bc(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3cc(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x3a0(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x3b0(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x3c0(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3d0(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x3a4(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x3b4(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x3c4(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3d4(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz ShadowBillboard_Tick_L_80063170
    lfs f0, 0x10c(r1)
    lfs f6, 0xf8(r1)
    stfs f0, 0x24c(r1)
    lfs f0, 0x12c(r1)
    stfs f6, 0x238(r1)
    lfs f5, 0xfc(r1)
    stfs f0, 0x26c(r1)
    lfs f4, 0x100(r1)
    lwz r0, 0x26c(r1)
    stfs f5, 0x23c(r1)
    lfs f3, 0x104(r1)
    stfs f4, 0x240(r1)
    lfs f2, 0x108(r1)
    stfs f3, 0x244(r1)
    lfs f1, 0x110(r1)
    stfs f2, 0x248(r1)
    lfs f0, 0x114(r1)
    stfs f1, 0x250(r1)
    lfs f6, 0x118(r1)
    stfs f0, 0x254(r1)
    lfs f5, 0x11c(r1)
    stw r0, 0x3cc(r1)
    lfs f4, 0x120(r1)
    lfs f3, 0x124(r1)
    lfs f2, 0x128(r1)
    lfs f1, 0x130(r1)
    lfs f0, 0x134(r1)
    stfs f6, 0x258(r1)
    lwz r23, 0x238(r1)
    stfs f5, 0x25c(r1)
    lwz r24, 0x23c(r1)
    stfs f4, 0x260(r1)
    lwz r25, 0x240(r1)
    stfs f3, 0x264(r1)
    lwz r26, 0x244(r1)
    stfs f2, 0x268(r1)
    lwz r12, 0x248(r1)
    stfs f1, 0x270(r1)
    lwz r11, 0x24c(r1)
    stfs f0, 0x274(r1)
    lwz r10, 0x250(r1)
    lwz r9, 0x254(r1)
    lwz r8, 0x258(r1)
    lwz r7, 0x25c(r1)
    lwz r6, 0x260(r1)
    lwz r5, 0x264(r1)
    lwz r4, 0x268(r1)
    lwz r3, 0x270(r1)
    lwz r0, 0x274(r1)
    stw r4, 0x3c8(r1)
    lfs f1, 0x3cc(r1)
    lfs f0, lbl_806D2BF0(r2)
    stw r3, 0x3d0(r1)
    fadds f1, f1, f0
    lfs f4, 0x3c8(r1)
    stw r23, 0x398(r1)
    lfs f2, 0x3d0(r1)
    stw r24, 0x39c(r1)
    lfs f0, lbl_806D2BF4(r2)
    stw r25, 0x3a0(r1)
    stw r26, 0x3a4(r1)
    stw r12, 0x3a8(r1)
    stw r11, 0x3ac(r1)
    stw r10, 0x3b0(r1)
    stw r9, 0x3b4(r1)
    stw r8, 0x3b8(r1)
    stw r7, 0x3bc(r1)
    stw r6, 0x3c0(r1)
    stw r5, 0x3c4(r1)
    stw r0, 0x3d4(r1)
    stfs f1, 0x3cc(r1)
    lfs f1, 0x54(r29)
    lfs f3, 0x4c(r29)
    fsubs f1, f2, f1
    fsubs f2, f4, f3
    fmuls f1, f1, f1
    fmadds f1, f2, f2, f1
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne ShadowBillboard_Tick_L_80063444
    li r0, 0x1
    stb r0, 0x19(r29)
    ShadowBillboard_Tick_L_80063444:
    lbz r0, 0x19(r29)
    cmplwi r0, 0x0
    bne ShadowBillboard_Tick_L_80063530
    li r0, 0x2
    mr r3, r29
    lfs f1, lbl_806D2BF8(r2)
    mtctr r0
    ShadowBillboard_Tick_L_80063460:
    lfs f2, 0x1c(r3)
    lfs f0, 0x0(r27)
    fsubs f0, f0, f2
    fdivs f0, f0, f1
    fadds f0, f2, f0
    stfs f0, 0x0(r27)
    lfs f2, 0x20(r3)
    lfs f0, 0x4(r27)
    fsubs f0, f0, f2
    fdivs f0, f0, f1
    fadds f0, f2, f0
    stfs f0, 0x4(r27)
    lfs f2, 0x24(r3)
    lfs f0, 0x8(r27)
    fsubs f0, f0, f2
    fdivs f0, f0, f1
    fadds f0, f2, f0
    stfs f0, 0x8(r27)
    lfs f2, 0x28(r3)
    lfs f0, 0xc(r27)
    fsubs f0, f0, f2
    fdivs f0, f0, f1
    fadds f0, f2, f0
    stfs f0, 0xc(r27)
    lfs f2, 0x2c(r3)
    lfs f0, 0x10(r27)
    fsubs f0, f0, f2
    fdivs f0, f0, f1
    fadds f0, f2, f0
    stfs f0, 0x10(r27)
    lfs f2, 0x30(r3)
    lfs f0, 0x14(r27)
    fsubs f0, f0, f2
    fdivs f0, f0, f1
    fadds f0, f2, f0
    stfs f0, 0x14(r27)
    lfs f2, 0x34(r3)
    lfs f0, 0x18(r27)
    fsubs f0, f0, f2
    fdivs f0, f0, f1
    fadds f0, f2, f0
    stfs f0, 0x18(r27)
    lfs f2, 0x38(r3)
    addi r3, r3, 0x20
    lfs f0, 0x1c(r27)
    fsubs f0, f0, f2
    fdivs f0, f0, f1
    fadds f0, f2, f0
    stfs f0, 0x1c(r27)
    addi r27, r27, 0x20
    bdnz ShadowBillboard_Tick_L_80063460
    b ShadowBillboard_Tick_L_80063538
    ShadowBillboard_Tick_L_80063530:
    li r0, 0x0
    stb r0, 0x19(r29)
    ShadowBillboard_Tick_L_80063538:
    lfs f0, 0x398(r1)
    addi r3, r1, 0x398
    addi r4, r1, 0x368
    stfs f0, 0x1c(r29)
    lfs f0, 0x39c(r1)
    stfs f0, 0x20(r29)
    lfs f0, 0x3a0(r1)
    stfs f0, 0x24(r29)
    lfs f0, 0x3a4(r1)
    stfs f0, 0x28(r29)
    lfs f0, 0x3a8(r1)
    stfs f0, 0x2c(r29)
    lfs f0, 0x3ac(r1)
    stfs f0, 0x30(r29)
    lfs f0, 0x3b0(r1)
    stfs f0, 0x34(r29)
    lfs f0, 0x3b4(r1)
    stfs f0, 0x38(r29)
    lfs f0, 0x3b8(r1)
    stfs f0, 0x3c(r29)
    lfs f0, 0x3bc(r1)
    stfs f0, 0x40(r29)
    lfs f0, 0x3c0(r1)
    stfs f0, 0x44(r29)
    lfs f0, 0x3c4(r1)
    stfs f0, 0x48(r29)
    lfs f0, 0x3c8(r1)
    stfs f0, 0x4c(r29)
    lfs f0, 0x3cc(r1)
    stfs f0, 0x50(r29)
    lfs f0, 0x3d0(r1)
    stfs f0, 0x54(r29)
    lfs f0, 0x3d4(r1)
    stfs f0, 0x58(r29)
    bl Mtx4x4_TransposeTo4x3
    lwz r3, 0xb8(r29)
    neg r0, r3
    andc r0, r0, r3
    srwi r0, r0, 31
    cmplwi r0, 0x1
    bne ShadowBillboard_Tick_L_800635FC
    lwz r4, 0xc0(r29)
    addi r6, r1, 0xc
    lwz r3, 0xc4(r29)
    lwz r0, 0xc8(r29)
    stw r4, 0xc(r1)
    stw r3, 0x10(r1)
    stw r0, 0x14(r1)
    b ShadowBillboard_Tick_L_80063618
    ShadowBillboard_Tick_L_800635FC:
    lwz r4, 0x1d0(r28)
    addi r6, r1, 0xc
    lwz r3, 0x1d4(r28)
    lwz r0, 0x1d8(r28)
    stw r4, 0xc(r1)
    stw r3, 0x10(r1)
    stw r0, 0x14(r1)
    ShadowBillboard_Tick_L_80063618:
    lwz r4, 0x0(r6)
    addi r5, r28, 0x0
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r4, 0x3c(r1)
    lfs f1, 0x368(r1)
    stw r3, 0x40(r1)
    lfs f0, 0x3c(r1)
    stw r0, 0x44(r1)
    fadds f4, f1, f0
    lfs f3, 0x378(r1)
    lfs f2, 0x40(r1)
    lfs f1, 0x388(r1)
    lfs f0, 0x44(r1)
    fadds f2, f3, f2
    stfs f4, 0x368(r1)
    fadds f0, f1, f0
    lfs f6, lbl_806D2BE0(r2)
    stfs f2, 0x378(r1)
    lfs f1, lbl_806D2BB0(r2)
    stfs f0, 0x388(r1)
    lwz r3, 0x4(r29)
    lwz r0, 0xc(r29)
    slwi r6, r3, 5
    lfs f0, 0x9c(r29)
    slwi r4, r0, 4
    lwz r0, 0x68(r29)
    add r3, r5, r6
    fmuls f2, f1, f0
    add r3, r3, r4
    add r4, r6, r4
    lfs f0, 0x8(r3)
    cmpwi r0, 0x0
    lfsx f5, r5, r4
    fmuls f1, f6, f0
    lfs f4, 0x4(r3)
    lfs f3, 0xa4(r29)
    fmuls f28, f6, f5
    lfs f0, 0xc(r3)
    fmadds f30, f6, f2, f1
    fmsubs f29, f6, f4, f3
    fmadds f31, f6, f0, f30
    bne ShadowBillboard_Tick_L_800636CC
    fmr f3, f30
    b ShadowBillboard_Tick_L_80063774
    ShadowBillboard_Tick_L_800636CC:
    lfs f2, 0x60(r29)
    lfs f1, 0x64(r29)
    lfs f0, lbl_806D2B74(r2)
    fsubs f1, f2, f1
    stfs f1, 0x60(r29)
    lfs f1, 0x60(r29)
    fcmpo cr0, f1, f0
    bge ShadowBillboard_Tick_L_800636F0
    stfs f0, 0x60(r29)
    ShadowBillboard_Tick_L_800636F0:
    lwz r0, 0x68(r29)
    cmpwi r0, 0x1
    bne ShadowBillboard_Tick_L_80063744
    lfs f1, lbl_806D2BB4(r2)
    lfs f0, 0x60(r29)
    lfd f2, lbl_806D2B80(r2)
    fmuls f0, f1, f0
    fmul f1, f2, f0
    frsp f1, f1
    bl sin
    frsp f3, f1
    lfs f1, 0x60(r29)
    lfs f0, lbl_806D2B74(r2)
    lfs f2, lbl_806D2B6C(r2)
    fcmpo cr0, f1, f0
    fsubs f1, f2, f3
    cror eq, lt, eq
    bne ShadowBillboard_Tick_L_80063764
    li r0, 0x0
    stw r0, 0x68(r29)
    b ShadowBillboard_Tick_L_80063764
    ShadowBillboard_Tick_L_80063744:
    lfs f1, lbl_806D2BB4(r2)
    lfs f0, 0x60(r29)
    lfd f2, lbl_806D2B80(r2)
    fmuls f0, f1, f0
    fmul f1, f2, f0
    frsp f1, f1
    bl sin
    frsp f1, f1
    ShadowBillboard_Tick_L_80063764:
    lfs f0, lbl_806D2B6C(r2)
    fsubs f0, f0, f1
    fmuls f0, f31, f0
    fmadds f3, f30, f1, f0
    ShadowBillboard_Tick_L_80063774:
    fmr f1, f28
    mr r3, r30
    fmr f2, f29
    addi r4, r1, 0x368
    bl CObj_LinePath_Step
    addi r3, r1, 0x368
    mr r4, r3
    bl PSMTXInverse
    mr r3, r30
    addi r4, r1, 0x368
    bl CObj_SetWorldMatrix
    ShadowBillboard_Tick_L_800637A0:
    cmplwi r31, 0x0
    beq ShadowBillboard_Tick_L_80063860
    lwz r5, 0x14(r29)
    addi r3, r1, 0x328
    lfs f0, lbl_806D2BFC(r2)
    addi r4, r1, 0x2f8
    lfs f1, 0xd8(r5)
    stfs f1, 0x328(r1)
    lfs f1, 0xdc(r5)
    stfs f1, 0x32c(r1)
    lfs f1, 0xe0(r5)
    stfs f1, 0x330(r1)
    lfs f1, 0xe4(r5)
    stfs f1, 0x334(r1)
    lfs f1, 0xe8(r5)
    stfs f1, 0x338(r1)
    lfs f1, 0xec(r5)
    stfs f1, 0x33c(r1)
    lfs f2, 0xf0(r5)
    stfs f2, 0x340(r1)
    lfs f1, 0xf4(r5)
    stfs f1, 0x344(r1)
    lfs f1, 0xf8(r5)
    stfs f1, 0x348(r1)
    lfs f1, 0xfc(r5)
    stfs f1, 0x34c(r1)
    lfs f1, 0x100(r5)
    stfs f1, 0x350(r1)
    lfs f1, 0x104(r5)
    stfs f1, 0x354(r1)
    lfs f1, 0x108(r5)
    stfs f1, 0x358(r1)
    lfs f1, 0x10c(r5)
    stfs f1, 0x35c(r1)
    frsp f1, f1
    lfs f2, 0x110(r5)
    fadds f0, f1, f0
    stfs f2, 0x360(r1)
    lfs f1, 0x114(r5)
    stfs f1, 0x364(r1)
    stfs f0, 0x35c(r1)
    bl Mtx4x4_TransposeTo4x3
    addi r3, r1, 0x2f8
    mr r4, r3
    bl PSMTXInverse
    mr r3, r31
    addi r4, r1, 0x2f8
    bl CObj_SetWorldMatrix
    ShadowBillboard_Tick_L_80063860:
    psq_l f31, 0x538(r1), 0, 0
    lfd f31, 0x530(r1)
    psq_l f30, 0x528(r1), 0, 0
    lfd f30, 0x520(r1)
    psq_l f29, 0x518(r1), 0, 0
    lfd f29, 0x510(r1)
    psq_l f28, 0x508(r1), 0, 0
    lfd f28, 0x500(r1)
    psq_l f27, 0x4f8(r1), 0, 0
    lfd f27, 0x4f0(r1)
    lmw r21, 0x4c4(r1)
    lwz r0, 0x544(r1)
    mtlr r0
    addi r1, r1, 0x540
    blr
}

asm void ShadowBillboard_StepSimple(void) { /* 0x8006389C size:0x5B4 */
    nofralloc
    stwu r1, -0x140(r1)
    mflr r0
    stw r0, 0x144(r1)
    stfd f31, 0x130(r1)
    psq_st f31, 0x138(r1), 0, 0
    stfd f30, 0x120(r1)
    psq_st f30, 0x128(r1), 0, 0
    stfd f29, 0x110(r1)
    psq_st f29, 0x118(r1), 0, 0
    stfd f28, 0x100(r1)
    psq_st f28, 0x108(r1), 0, 0
    stw r31, 0xfc(r1)
    stw r30, 0xf8(r1)
    stw r29, 0xf4(r1)
    stw r28, 0xf0(r1)
    mr r28, r3
    lwz r3, 0xb8(r3)
    lis r6, lbl_802EE320@ha
    mr r29, r4
    neg r0, r3
    mr r30, r5
    andc r0, r0, r3
    addi r31, r6, lbl_802EE320@l
    srwi. r0, r0, 31
    beq ShadowBillboard_StepSimple_L_800639E4
    lwz r3, 0xb8(r28)
    subi r0, r3, 0x1
    stw r0, 0xb8(r28)
    lwz r0, 0xb8(r28)
    clrlwi r0, r0, 30
    cmpwi r0, 0x1
    bgt ShadowBillboard_StepSimple_L_80063968
    bl GetCourseScene3D
    cmplwi r3, 0x0
    beq ShadowBillboard_StepSimple_L_800639B0
    bl CObj_GetViewMatrix_Cached
    lfs f0, 0x0(r3)
    lfs f1, lbl_806D2B6C(r2)
    lfs f2, lbl_806D2B68(r2)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc0(r28)
    lfs f0, 0x10(r3)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc4(r28)
    lfs f0, 0x20(r3)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc8(r28)
    b ShadowBillboard_StepSimple_L_800639B0
    ShadowBillboard_StepSimple_L_80063968:
    bl GetCourseScene3D
    cmplwi r3, 0x0
    beq ShadowBillboard_StepSimple_L_800639B0
    bl CObj_GetViewMatrix_Cached
    lfs f0, 0x0(r3)
    lfs f1, lbl_806D2B70(r2)
    lfs f2, lbl_806D2B68(r2)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc0(r28)
    lfs f0, 0x10(r3)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc4(r28)
    lfs f0, 0x20(r3)
    fmuls f0, f0, f1
    fmuls f0, f2, f0
    stfs f0, 0xc8(r28)
    ShadowBillboard_StepSimple_L_800639B0:
    lwz r3, 0xb8(r28)
    neg r0, r3
    andc r0, r0, r3
    srwi r0, r0, 31
    cmplwi r0, 0x1
    bne ShadowBillboard_StepSimple_L_800639E4
    li r0, 0x0
    lfs f0, lbl_806D2B74(r2)
    stw r0, 0xb8(r28)
    stw r0, 0xbc(r28)
    stfs f0, 0xc0(r28)
    stfs f0, 0xc4(r28)
    stfs f0, 0xc8(r28)
    ShadowBillboard_StepSimple_L_800639E4:
    cmplwi r29, 0x0
    beq ShadowBillboard_StepSimple_L_80063D50
    lwz r0, 0x4(r28)
    addi r5, r31, 0x0
    lwz r3, 0xc(r28)
    slwi r6, r0, 5
    lwz r0, 0x6c(r28)
    slwi r4, r3, 4
    lfs f4, lbl_806D2BE0(r2)
    add r3, r5, r6
    lfs f2, 0xa4(r28)
    add r3, r3, r4
    add r4, r6, r4
    lfs f0, 0x8(r3)
    cmpwi r0, 0x0
    lfsx f3, r5, r4
    lfs f1, 0x4(r3)
    fmuls f29, f4, f0
    lfs f0, 0xc(r3)
    fmadds f31, f4, f3, f2
    fmuls f30, f4, f1
    lwz r5, 0x14(r28)
    fmadds f28, f4, f0, f29
    bne ShadowBillboard_StepSimple_L_80063BC8
    lwz r3, 0xb8(r28)
    neg r0, r3
    andc r0, r0, r3
    srwi r0, r0, 31
    cmplwi r0, 0x1
    bne ShadowBillboard_StepSimple_L_80063A7C
    lwz r4, 0xc0(r28)
    addi r6, r1, 0x14
    lwz r3, 0xc4(r28)
    lwz r0, 0xc8(r28)
    stw r4, 0x14(r1)
    stw r3, 0x18(r1)
    stw r0, 0x1c(r1)
    b ShadowBillboard_StepSimple_L_80063A98
    ShadowBillboard_StepSimple_L_80063A7C:
    lwz r4, 0x1d0(r31)
    addi r6, r1, 0x14
    lwz r3, 0x1d4(r31)
    lwz r0, 0x1d8(r31)
    stw r4, 0x14(r1)
    stw r3, 0x18(r1)
    stw r0, 0x1c(r1)
    ShadowBillboard_StepSimple_L_80063A98:
    lwz r0, 0x0(r6)
    lwz r3, 0x4(r6)
    stw r0, 0x44(r1)
    lwz r0, 0x8(r6)
    stw r3, 0x48(r1)
    lfs f1, 0x44(r1)
    lfs f0, 0x108(r5)
    stw r0, 0x4c(r1)
    fadds f0, f1, f0
    lfs f2, 0x48(r1)
    lfs f1, 0x10c(r5)
    lfs f3, 0x110(r5)
    lwz r3, 0x5c(r28)
    fadds f2, f2, f1
    lfs f1, 0x4c(r1)
    stfs f0, 0x30(r3)
    fadds f0, f1, f3
    stfs f2, 0x34(r3)
    stfs f0, 0x38(r3)
    lwz r0, 0x68(r28)
    cmpwi r0, 0x0
    bne ShadowBillboard_StepSimple_L_80063AF8
    fmr f28, f29
    b ShadowBillboard_StepSimple_L_80063BA0
    ShadowBillboard_StepSimple_L_80063AF8:
    lfs f2, 0x60(r28)
    lfs f1, 0x64(r28)
    lfs f0, lbl_806D2B74(r2)
    fsubs f1, f2, f1
    stfs f1, 0x60(r28)
    lfs f1, 0x60(r28)
    fcmpo cr0, f1, f0
    bge ShadowBillboard_StepSimple_L_80063B1C
    stfs f0, 0x60(r28)
    ShadowBillboard_StepSimple_L_80063B1C:
    lwz r0, 0x68(r28)
    cmpwi r0, 0x1
    bne ShadowBillboard_StepSimple_L_80063B70
    lfs f1, lbl_806D2BB4(r2)
    lfs f0, 0x60(r28)
    lfd f2, lbl_806D2B80(r2)
    fmuls f0, f1, f0
    fmul f1, f2, f0
    frsp f1, f1
    bl sin
    frsp f3, f1
    lfs f1, 0x60(r28)
    lfs f0, lbl_806D2B74(r2)
    lfs f2, lbl_806D2B6C(r2)
    fcmpo cr0, f1, f0
    fsubs f1, f2, f3
    cror eq, lt, eq
    bne ShadowBillboard_StepSimple_L_80063B90
    li r0, 0x0
    stw r0, 0x68(r28)
    b ShadowBillboard_StepSimple_L_80063B90
    ShadowBillboard_StepSimple_L_80063B70:
    lfs f1, lbl_806D2BB4(r2)
    lfs f0, 0x60(r28)
    lfd f2, lbl_806D2B80(r2)
    fmuls f0, f1, f0
    fmul f1, f2, f0
    frsp f1, f1
    bl sin
    frsp f1, f1
    ShadowBillboard_StepSimple_L_80063B90:
    lfs f0, lbl_806D2B6C(r2)
    fsubs f0, f0, f1
    fmuls f0, f28, f0
    fmadds f28, f29, f1, f0
    ShadowBillboard_StepSimple_L_80063BA0:
    lwz r3, 0x5c(r28)
    addi r4, r1, 0xc0
    bl Mtx4x4_TransposeTo4x3
    fmr f1, f31
    mr r3, r29
    fmr f2, f30
    addi r4, r1, 0xc0
    fmr f3, f28
    bl CObj_LinePath_Step
    b ShadowBillboard_StepSimple_L_80063D50
    ShadowBillboard_StepSimple_L_80063BC8:
    lwz r3, 0xb8(r28)
    neg r0, r3
    andc r0, r0, r3
    srwi r0, r0, 31
    cmplwi r0, 0x1
    bne ShadowBillboard_StepSimple_L_80063C00
    lwz r4, 0xc0(r28)
    addi r6, r1, 0x8
    lwz r3, 0xc4(r28)
    lwz r0, 0xc8(r28)
    stw r4, 0x8(r1)
    stw r3, 0xc(r1)
    stw r0, 0x10(r1)
    b ShadowBillboard_StepSimple_L_80063C1C
    ShadowBillboard_StepSimple_L_80063C00:
    lwz r4, 0x1d0(r31)
    addi r6, r1, 0x8
    lwz r3, 0x1d4(r31)
    lwz r0, 0x1d8(r31)
    stw r4, 0x8(r1)
    stw r3, 0xc(r1)
    stw r0, 0x10(r1)
    ShadowBillboard_StepSimple_L_80063C1C:
    lwz r7, 0x6c(r28)
    lwz r4, 0x0(r6)
    lwz r3, 0x4(r6)
    cmpwi r7, 0x1
    lwz r0, 0x8(r6)
    stw r4, 0x38(r1)
    stw r3, 0x3c(r1)
    stw r0, 0x40(r1)
    bne ShadowBillboard_StepSimple_L_80063C60
    lfs f0, 0x108(r5)
    stfs f0, 0x2c(r1)
    lfs f0, 0x10c(r5)
    fadds f0, f31, f0
    stfs f0, 0x30(r1)
    lfs f0, 0x110(r5)
    stfs f0, 0x34(r1)
    b ShadowBillboard_StepSimple_L_80063D14
    ShadowBillboard_StepSimple_L_80063C60:
    cmpwi r7, 0x3
    bne ShadowBillboard_StepSimple_L_80063CD0
    lfs f1, 0x108(r5)
    mr r3, r29
    lfs f0, lbl_806D2C08(r2)
    addi r4, r1, 0x20
    stfs f1, 0x2c(r1)
    lfs f1, 0x10c(r5)
    fadds f1, f31, f1
    stfs f1, 0x30(r1)
    fadds f0, f0, f1
    lfs f1, 0x110(r5)
    stfs f1, 0x34(r1)
    stfs f0, 0x80(r28)
    lwz r6, 0x1b8(r31)
    lwz r5, 0x1bc(r31)
    lwz r0, 0x1c0(r31)
    stw r6, 0x20(r1)
    stw r5, 0x24(r1)
    stw r0, 0x28(r1)
    lfs f0, 0x7c(r28)
    stfs f0, 0x20(r1)
    lfs f0, 0x80(r28)
    stfs f0, 0x24(r1)
    lfs f0, 0x84(r28)
    stfs f0, 0x28(r1)
    bl CObj_LoadIntoGX
    b ShadowBillboard_StepSimple_L_80063D14
    ShadowBillboard_StepSimple_L_80063CD0:
    cmpwi r7, 0x4
    bne ShadowBillboard_StepSimple_L_80063CF8
    lfs f0, 0x70(r28)
    stfs f0, 0x2c(r1)
    lfs f0, 0x74(r28)
    fadds f0, f0, f31
    stfs f0, 0x30(r1)
    lfs f0, 0x78(r28)
    stfs f0, 0x34(r1)
    b ShadowBillboard_StepSimple_L_80063D14
    ShadowBillboard_StepSimple_L_80063CF8:
    lfs f0, 0x70(r28)
    stfs f0, 0x2c(r1)
    lfs f0, 0x10c(r5)
    fadds f0, f31, f0
    stfs f0, 0x30(r1)
    lfs f0, 0x78(r28)
    stfs f0, 0x34(r1)
    ShadowBillboard_StepSimple_L_80063D14:
    lfs f1, 0x2c(r1)
    mr r3, r29
    lfs f0, 0x38(r1)
    addi r4, r1, 0x2c
    lfs f3, 0x30(r1)
    lfs f2, 0x3c(r1)
    fadds f4, f1, f0
    lfs f1, 0x34(r1)
    lfs f0, 0x40(r1)
    fadds f2, f3, f2
    stfs f4, 0x2c(r1)
    fadds f0, f1, f0
    stfs f2, 0x30(r1)
    stfs f0, 0x34(r1)
    bl CObj_ApplyViewport
    ShadowBillboard_StepSimple_L_80063D50:
    cmplwi r30, 0x0
    beq ShadowBillboard_StepSimple_L_80063E10
    lwz r5, 0x14(r28)
    addi r3, r1, 0x80
    lfs f0, lbl_806D2BF0(r2)
    addi r4, r1, 0x50
    lfs f1, 0xd8(r5)
    stfs f1, 0x80(r1)
    lfs f1, 0xdc(r5)
    stfs f1, 0x84(r1)
    lfs f1, 0xe0(r5)
    stfs f1, 0x88(r1)
    lfs f1, 0xe4(r5)
    stfs f1, 0x8c(r1)
    lfs f1, 0xe8(r5)
    stfs f1, 0x90(r1)
    lfs f1, 0xec(r5)
    stfs f1, 0x94(r1)
    lfs f2, 0xf0(r5)
    stfs f2, 0x98(r1)
    lfs f1, 0xf4(r5)
    stfs f1, 0x9c(r1)
    lfs f1, 0xf8(r5)
    stfs f1, 0xa0(r1)
    lfs f1, 0xfc(r5)
    stfs f1, 0xa4(r1)
    lfs f1, 0x100(r5)
    stfs f1, 0xa8(r1)
    lfs f1, 0x104(r5)
    stfs f1, 0xac(r1)
    lfs f1, 0x108(r5)
    stfs f1, 0xb0(r1)
    lfs f1, 0x10c(r5)
    stfs f1, 0xb4(r1)
    frsp f1, f1
    lfs f2, 0x110(r5)
    fadds f0, f1, f0
    stfs f2, 0xb8(r1)
    lfs f1, 0x114(r5)
    stfs f1, 0xbc(r1)
    stfs f0, 0xb4(r1)
    bl Mtx4x4_TransposeTo4x3
    addi r3, r1, 0x50
    mr r4, r3
    bl PSMTXInverse
    mr r3, r30
    addi r4, r1, 0x50
    bl CObj_SetWorldMatrix
    ShadowBillboard_StepSimple_L_80063E10:
    psq_l f31, 0x138(r1), 0, 0
    lfd f31, 0x130(r1)
    psq_l f30, 0x128(r1), 0, 0
    lfd f30, 0x120(r1)
    psq_l f29, 0x118(r1), 0, 0
    lfd f29, 0x110(r1)
    psq_l f28, 0x108(r1), 0, 0
    lfd f28, 0x100(r1)
    lwz r31, 0xfc(r1)
    lwz r30, 0xf8(r1)
    lwz r29, 0xf4(r1)
    lwz r0, 0x144(r1)
    lwz r28, 0xf0(r1)
    mtlr r0
    addi r1, r1, 0x140
    blr
}

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

asm void Camera_RotateByYaw(void) { /* 0x80063F30 size:0x380 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stfd f31, 0xa0(r1)
    psq_st f31, 0xa8(r1), 0, 0
    stfd f30, 0x90(r1)
    psq_st f30, 0x98(r1), 0, 0
    stw r31, 0x8c(r1)
    stw r30, 0x88(r1)
    lfd f0, lbl_806D2B80(r2)
    addi r30, r1, 0x48
    lfs f2, lbl_806D2B74(r2)
    fmul f30, f0, f1
    lfs f0, lbl_806D2B6C(r2)
    stfs f2, 0x48(r1)
    lwz r31, 0x5c(r3)
    stfs f2, 0x5c(r1)
    frsp f1, f30
    stfs f2, 0x70(r1)
    stfs f2, 0x84(r1)
    stfs f2, 0x4c(r1)
    stfs f2, 0x50(r1)
    stfs f2, 0x54(r1)
    stfs f2, 0x58(r1)
    stfs f2, 0x60(r1)
    stfs f2, 0x64(r1)
    stfs f2, 0x68(r1)
    stfs f2, 0x6c(r1)
    stfs f2, 0x74(r1)
    stfs f2, 0x78(r1)
    stfs f2, 0x7c(r1)
    stfs f2, 0x80(r1)
    stfs f0, 0x84(r1)
    stfs f0, 0x70(r1)
    stfs f0, 0x5c(r1)
    stfs f0, 0x48(r1)
    bl cos
    frsp f31, f1
    frsp f1, f30
    bl sin
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f31, 0x48(r1)
    mr r4, r5
    addi r6, r1, 0x8
    fneg f0, f1
    stfs f1, 0x68(r1)
    stfs f31, 0x70(r1)
    stfs f0, 0x50(r1)
    mtctr r0
    Camera_RotateByYaw_L_80063FFC:
    lfs f7, 0x0(r30)
    slwi r0, r5, 2
    lfs f6, 0x0(r31)
    addi r3, r5, 0x1
    lfs f5, 0x4(r30)
    fmuls f8, f7, f6
    lfs f4, 0x10(r31)
    lfs f3, 0x8(r30)
    lfs f2, 0x20(r31)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r30)
    lfs f0, 0x30(r31)
    lfs f6, 0x4(r31)
    fmadds f8, f3, f2, f8
    lfs f4, 0x14(r31)
    lfs f2, 0x24(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x34(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x8(r31)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x18(r31)
    fmadds f8, f3, f2, f8
    lfs f2, 0x28(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x38(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0xc(r31)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1c(r31)
    fmadds f8, f3, f2, f8
    lfs f2, 0x2c(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3c(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r30)
    slwi r0, r5, 2
    lfs f6, 0x0(r31)
    addi r3, r5, 0x1
    lfs f5, 0x14(r30)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x10(r31)
    lfs f3, 0x18(r30)
    lfs f1, 0x1c(r30)
    addi r30, r30, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x20(r31)
    lfs f0, 0x30(r31)
    fmadds f8, f3, f2, f8
    lfs f6, 0x4(r31)
    lfs f4, 0x14(r31)
    lfs f2, 0x24(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x34(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x8(r31)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x18(r31)
    fmadds f8, f3, f2, f8
    lfs f2, 0x28(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x38(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0xc(r31)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1c(r31)
    fmadds f8, f3, f2, f8
    lfs f2, 0x2c(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3c(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz Camera_RotateByYaw_L_80063FFC
    lfs f1, 0x8(r1)
    lfs f0, 0xc(r1)
    stfs f1, 0x48(r1)
    lfs f1, 0x10(r1)
    stfs f0, 0x4c(r1)
    lwz r3, 0x48(r1)
    stfs f1, 0x50(r1)
    lfs f0, 0x14(r1)
    lfs f1, 0x18(r1)
    stfs f0, 0x54(r1)
    lfs f0, 0x1c(r1)
    stfs f1, 0x58(r1)
    lfs f1, 0x20(r1)
    stfs f0, 0x5c(r1)
    lfs f0, 0x24(r1)
    stfs f1, 0x60(r1)
    lfs f1, 0x28(r1)
    stfs f0, 0x64(r1)
    lfs f0, 0x2c(r1)
    stfs f1, 0x68(r1)
    lfs f1, 0x30(r1)
    stfs f0, 0x6c(r1)
    lfs f0, 0x34(r1)
    stfs f1, 0x70(r1)
    lfs f1, 0x38(r1)
    stfs f0, 0x74(r1)
    lfs f0, 0x3c(r1)
    stfs f1, 0x78(r1)
    lfs f1, 0x40(r1)
    stfs f0, 0x7c(r1)
    lfs f0, 0x44(r1)
    stfs f1, 0x80(r1)
    lwz r0, 0x4c(r1)
    stw r3, 0x0(r31)
    lwz r3, 0x50(r1)
    stw r0, 0x4(r31)
    lwz r0, 0x54(r1)
    stw r3, 0x8(r31)
    lwz r3, 0x58(r1)
    stw r0, 0xc(r31)
    lwz r0, 0x5c(r1)
    stw r3, 0x10(r31)
    lwz r3, 0x60(r1)
    stw r0, 0x14(r31)
    lwz r0, 0x64(r1)
    stw r3, 0x18(r31)
    lwz r3, 0x68(r1)
    stw r0, 0x1c(r31)
    lwz r0, 0x6c(r1)
    stw r3, 0x20(r31)
    lwz r3, 0x70(r1)
    stw r0, 0x24(r31)
    lwz r0, 0x74(r1)
    stw r3, 0x28(r31)
    lwz r3, 0x78(r1)
    stw r0, 0x2c(r31)
    lwz r0, 0x7c(r1)
    stw r3, 0x30(r31)
    lwz r3, 0x80(r1)
    stfs f0, 0x84(r1)
    stw r0, 0x34(r31)
    lwz r0, 0x84(r1)
    stw r3, 0x38(r31)
    stw r0, 0x3c(r31)
    psq_l f31, 0xa8(r1), 0, 0
    lfd f31, 0xa0(r1)
    psq_l f30, 0x98(r1), 0, 0
    lfd f30, 0x90(r1)
    lwz r31, 0x8c(r1)
    lwz r0, 0xb4(r1)
    lwz r30, 0x88(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

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

asm void PlayCamera_Init(void) { /* 0x8006430C size:0x614 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stfd f30, 0xa0(r1)
    psq_st f30, 0xa8(r1), 0, 0
    stw r31, 0x9c(r1)
    stw r30, 0x98(r1)
    stw r29, 0x94(r1)
    stw r28, 0x90(r1)
    stb r8, 0x0(r3)
    mr r29, r3
    li r11, 0x1
    lis r3, lbl_802EE4FC@ha
    stw r4, 0x4(r29)
    xor r0, r5, r11
    addi r4, r3, lbl_802EE4FC@l
    fmr f30, f1
    srawi r3, r0, 1
    and r0, r0, r5
    subf r0, r0, r3
    stw r5, 0x8(r29)
    srwi r0, r0, 31
    stw r0, 0xc(r29)
    mr r30, r9
    li r3, 0x40
    li r5, 0x8e
    stw r6, 0x10(r29)
    stw r7, 0x14(r29)
    stb r10, 0x18(r29)
    stb r11, 0x19(r29)
    bl MemoryManager_AllocTagged
    stw r3, 0x5c(r29)
    clrlwi r0, r30, 24
    lfs f0, lbl_806D2B74(r2)
    li r3, 0x0
    cmplwi r0, 0x1
    stfs f0, 0x60(r29)
    stfs f0, 0x64(r29)
    stw r3, 0x68(r29)
    stw r3, 0x6c(r29)
    stfs f0, 0x98(r29)
    stfs f0, 0x9c(r29)
    stfs f0, 0xa0(r29)
    stfs f0, 0xa4(r29)
    stfs f0, 0xa8(r29)
    stb r3, 0xac(r29)
    stfs f0, 0xb0(r29)
    stfs f0, 0xb4(r29)
    stw r3, 0xb8(r29)
    stw r3, 0xbc(r29)
    stfs f0, 0xc0(r29)
    stfs f0, 0xc4(r29)
    stfs f0, 0xc8(r29)
    bne PlayCamera_Init_L_800643F4
    lfs f0, lbl_806D2B6C(r2)
    stfs f0, 0xa0(r29)
    PlayCamera_Init_L_800643F4:
    lfs f3, lbl_806D2B74(r2)
    addi r28, r1, 0x48
    lwz r3, 0x5c(r29)
    lfs f0, lbl_806D2BA0(r2)
    stfs f3, 0x0(r3)
    lfs f2, lbl_806D2B6C(r2)
    fadds f0, f0, f30
    stfs f3, 0x4(r3)
    lfd f1, lbl_806D2B80(r2)
    stfs f3, 0x8(r3)
    fmul f30, f1, f0
    stfs f3, 0xc(r3)
    stfs f3, 0x10(r3)
    frsp f1, f30
    stfs f3, 0x14(r3)
    stfs f3, 0x18(r3)
    stfs f3, 0x1c(r3)
    stfs f3, 0x20(r3)
    stfs f3, 0x24(r3)
    stfs f3, 0x28(r3)
    stfs f3, 0x2c(r3)
    stfs f3, 0x30(r3)
    stfs f3, 0x34(r3)
    stfs f3, 0x38(r3)
    stfs f3, 0x3c(r3)
    stfs f2, 0x3c(r3)
    stfs f2, 0x28(r3)
    stfs f2, 0x14(r3)
    stfs f2, 0x0(r3)
    stfs f3, 0x48(r1)
    lwz r31, 0x5c(r29)
    stfs f3, 0x5c(r1)
    stfs f3, 0x70(r1)
    stfs f3, 0x84(r1)
    stfs f3, 0x4c(r1)
    stfs f3, 0x50(r1)
    stfs f3, 0x54(r1)
    stfs f3, 0x58(r1)
    stfs f3, 0x60(r1)
    stfs f3, 0x64(r1)
    stfs f3, 0x68(r1)
    stfs f3, 0x6c(r1)
    stfs f3, 0x74(r1)
    stfs f3, 0x78(r1)
    stfs f3, 0x7c(r1)
    stfs f3, 0x80(r1)
    stfs f2, 0x84(r1)
    stfs f2, 0x70(r1)
    stfs f2, 0x5c(r1)
    stfs f2, 0x48(r1)
    bl cos
    frsp f31, f1
    frsp f1, f30
    bl sin
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f31, 0x48(r1)
    mr r4, r5
    addi r6, r1, 0x8
    fneg f0, f1
    stfs f1, 0x68(r1)
    stfs f31, 0x70(r1)
    stfs f0, 0x50(r1)
    mtctr r0
    PlayCamera_Init_L_800644F8:
    lfs f7, 0x0(r28)
    slwi r0, r5, 2
    lfs f6, 0x0(r31)
    addi r3, r5, 0x1
    lfs f5, 0x4(r28)
    fmuls f8, f7, f6
    lfs f4, 0x10(r31)
    lfs f3, 0x8(r28)
    lfs f2, 0x20(r31)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r28)
    lfs f0, 0x30(r31)
    lfs f6, 0x4(r31)
    fmadds f8, f3, f2, f8
    lfs f4, 0x14(r31)
    lfs f2, 0x24(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x34(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x8(r31)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x18(r31)
    fmadds f8, f3, f2, f8
    lfs f2, 0x28(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x38(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0xc(r31)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1c(r31)
    fmadds f8, f3, f2, f8
    lfs f2, 0x2c(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3c(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r28)
    slwi r0, r5, 2
    lfs f6, 0x0(r31)
    addi r3, r5, 0x1
    lfs f5, 0x14(r28)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x10(r31)
    lfs f3, 0x18(r28)
    lfs f1, 0x1c(r28)
    addi r28, r28, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x20(r31)
    lfs f0, 0x30(r31)
    fmadds f8, f3, f2, f8
    lfs f6, 0x4(r31)
    lfs f4, 0x14(r31)
    lfs f2, 0x24(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x34(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x8(r31)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x18(r31)
    fmadds f8, f3, f2, f8
    lfs f2, 0x28(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x38(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0xc(r31)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1c(r31)
    fmadds f8, f3, f2, f8
    lfs f2, 0x2c(r31)
    fmadds f8, f1, f0, f8
    lfs f0, 0x3c(r31)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz PlayCamera_Init_L_800644F8
    lfs f1, 0x8(r1)
    clrlwi r0, r30, 24
    lfs f0, 0xc(r1)
    cmplwi r0, 0x1
    stfs f1, 0x48(r1)
    li r0, -0x1
    lfs f1, 0x10(r1)
    stfs f0, 0x4c(r1)
    lwz r4, 0x48(r1)
    stfs f1, 0x50(r1)
    lfs f0, 0x14(r1)
    lfs f1, 0x18(r1)
    stfs f0, 0x54(r1)
    lfs f0, 0x1c(r1)
    stfs f1, 0x58(r1)
    lfs f1, 0x20(r1)
    stfs f0, 0x5c(r1)
    lfs f0, 0x24(r1)
    stfs f1, 0x60(r1)
    lfs f1, 0x28(r1)
    stfs f0, 0x64(r1)
    lfs f0, 0x2c(r1)
    stfs f1, 0x68(r1)
    lfs f1, 0x30(r1)
    stfs f0, 0x6c(r1)
    lfs f0, 0x34(r1)
    stfs f1, 0x70(r1)
    lfs f1, 0x38(r1)
    stfs f0, 0x74(r1)
    lfs f0, 0x3c(r1)
    stfs f1, 0x78(r1)
    lfs f1, 0x40(r1)
    stfs f0, 0x7c(r1)
    lfs f0, 0x44(r1)
    stfs f1, 0x80(r1)
    lwz r3, 0x4c(r1)
    stw r4, 0x0(r31)
    lwz r4, 0x50(r1)
    stw r3, 0x4(r31)
    lwz r3, 0x54(r1)
    stw r4, 0x8(r31)
    lwz r4, 0x58(r1)
    stw r3, 0xc(r31)
    lwz r3, 0x5c(r1)
    stw r4, 0x10(r31)
    lwz r4, 0x60(r1)
    stw r3, 0x14(r31)
    lwz r3, 0x64(r1)
    stw r4, 0x18(r31)
    lwz r4, 0x68(r1)
    stw r3, 0x1c(r31)
    lwz r3, 0x6c(r1)
    stw r4, 0x20(r31)
    lwz r4, 0x70(r1)
    stw r3, 0x24(r31)
    lwz r3, 0x74(r1)
    stw r4, 0x28(r31)
    lwz r4, 0x78(r1)
    stw r3, 0x2c(r31)
    lwz r3, 0x7c(r1)
    stw r4, 0x30(r31)
    lwz r4, 0x80(r1)
    stfs f0, 0x84(r1)
    lfs f1, lbl_806D2B74(r2)
    stw r3, 0x34(r31)
    lwz r3, 0x84(r1)
    stw r4, 0x38(r31)
    lfs f0, lbl_806D2B6C(r2)
    stw r3, 0x3c(r31)
    stfs f1, 0x1c(r29)
    stfs f1, 0x20(r29)
    stfs f1, 0x24(r29)
    stfs f1, 0x28(r29)
    stfs f1, 0x2c(r29)
    stfs f1, 0x30(r29)
    stfs f1, 0x34(r29)
    stfs f1, 0x38(r29)
    stfs f1, 0x3c(r29)
    stfs f1, 0x40(r29)
    stfs f1, 0x44(r29)
    stfs f1, 0x48(r29)
    stfs f1, 0x4c(r29)
    stfs f1, 0x50(r29)
    stfs f1, 0x54(r29)
    stfs f1, 0x58(r29)
    stfs f0, 0x58(r29)
    stfs f0, 0x44(r29)
    stfs f0, 0x30(r29)
    stfs f0, 0x1c(r29)
    stfs f1, 0xd0(r29)
    stw r0, 0xcc(r29)
    bne PlayCamera_Init_L_800648EC
    lwz r4, g_gameMode(r13)
    cmpwi r4, 0x0
    bne PlayCamera_Init_L_80064808
    lwz r5, g_roundIndex(r13)
    b PlayCamera_Init_L_80064848
    PlayCamera_Init_L_80064808:
    lwz r0, g_reverseRoundFlag(r13)
    cmpwi r0, 0x0
    bne PlayCamera_Init_L_80064830
    lwz r0, g_longRoundFlag(r13)
    cmpwi r0, 0x0
    bne PlayCamera_Init_L_80064828
    li r5, 0x0
    b PlayCamera_Init_L_80064848
    PlayCamera_Init_L_80064828:
    li r5, 0x1
    b PlayCamera_Init_L_80064848
    PlayCamera_Init_L_80064830:
    lwz r0, g_longRoundFlag(r13)
    cmpwi r0, 0x0
    bne PlayCamera_Init_L_80064844
    li r5, 0x4
    b PlayCamera_Init_L_80064848
    PlayCamera_Init_L_80064844:
    li r5, 0x5
    PlayCamera_Init_L_80064848:
    lwz r0, lbl_806CEEF0(r13)
    lis r3, lbl_803F9F30@ha
    addi r3, r3, lbl_803F9F30@l
    lwz r6, g_cupId(r13)
    lwz r7, g_ccClass(r13)
    li r8, 0x0
    mtctr r0
    cmpwi r0, 0x0
    ble PlayCamera_Init_L_800648D8
    PlayCamera_Init_L_8006486C:
    lwz r0, 0x0(r3)
    cmpwi r0, -0x1
    beq PlayCamera_Init_L_80064880
    cmpw r4, r0
    bne PlayCamera_Init_L_800648CC
    PlayCamera_Init_L_80064880:
    lwz r0, 0x4(r3)
    cmpwi r0, -0x1
    beq PlayCamera_Init_L_80064894
    cmpw r6, r0
    bne PlayCamera_Init_L_800648CC
    PlayCamera_Init_L_80064894:
    lwz r0, 0x8(r3)
    cmpwi r0, -0x1
    beq PlayCamera_Init_L_800648A8
    cmpw r7, r0
    bne PlayCamera_Init_L_800648CC
    PlayCamera_Init_L_800648A8:
    lwz r0, 0xc(r3)
    cmpwi r0, -0x1
    beq PlayCamera_Init_L_800648BC
    cmpw r5, r0
    bne PlayCamera_Init_L_800648CC
    PlayCamera_Init_L_800648BC:
    stw r8, 0xcc(r29)
    lfs f0, lbl_806D2B6C(r2)
    stfs f0, 0xd0(r29)
    b PlayCamera_Init_L_800648D8
    PlayCamera_Init_L_800648CC:
    addi r3, r3, 0x7c
    addi r8, r8, 0x1
    bdnz PlayCamera_Init_L_8006486C
    PlayCamera_Init_L_800648D8:
    lwz r0, 0xcc(r29)
    cmpwi r0, -0x1
    bne PlayCamera_Init_L_800648EC
    lfs f0, lbl_806D2B74(r2)
    stfs f0, 0xa0(r29)
    PlayCamera_Init_L_800648EC:
    mr r3, r29
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    psq_l f30, 0xa8(r1), 0, 0
    lfd f30, 0xa0(r1)
    lwz r31, 0x9c(r1)
    lwz r30, 0x98(r1)
    lwz r29, 0x94(r1)
    lwz r0, 0xc4(r1)
    lwz r28, 0x90(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

asm void Mtx34_Orthonormalize(void) { /* 0x80064920 size:0x3B4 */
    nofralloc
    stwu r1, -0xa0(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stfd f30, 0x80(r1)
    psq_st f30, 0x88(r1), 0, 0
    stfd f29, 0x70(r1)
    psq_st f29, 0x78(r1), 0, 0
    stfd f28, 0x60(r1)
    psq_st f28, 0x68(r1), 0, 0
    stfd f27, 0x50(r1)
    psq_st f27, 0x58(r1), 0, 0
    stfd f26, 0x40(r1)
    psq_st f26, 0x48(r1), 0, 0
    lfs f9, 0x4(r3)
    lfs f8, 0x0(r3)
    frsp f4, f9
    lfs f31, 0x28(r3)
    lfs f10, 0x8(r3)
    frsp f3, f8
    lfs f13, 0x24(r3)
    frsp f26, f31
    lfs f6, 0x20(r3)
    frsp f5, f10
    fmuls f1, f13, f3
    lfs f12, 0x18(r3)
    fmuls f0, f31, f4
    lfs f11, 0x14(r3)
    fmuls f2, f6, f5
    fmsubs f30, f6, f4, f1
    fmsubs f5, f13, f5, f0
    lfs f7, 0x10(r3)
    frsp f28, f13
    stfs f8, 0x2c(r1)
    fmsubs f29, f31, f3, f2
    frsp f4, f6
    fmuls f3, f5, f26
    stfs f9, 0x30(r1)
    fmuls f1, f30, f28
    lfs f0, lbl_806D2B74(r2)
    fmuls f2, f29, f4
    fmsubs f27, f30, f4, f3
    fmsubs f4, f29, f26, f1
    stfs f10, 0x34(r1)
    fmsubs f28, f5, f28, f2
    fmuls f1, f27, f27
    stfs f7, 0x20(r1)
    fmuls f2, f4, f4
    stfs f11, 0x24(r1)
    fmuls f3, f28, f28
    fadds f1, f2, f1
    stfs f12, 0x28(r1)
    stfs f8, 0x20(r1)
    fadds f7, f3, f1
    stfs f9, 0x24(r1)
    stfs f10, 0x28(r1)
    fcmpo cr0, f7, f0
    stfs f6, 0x2c(r1)
    stfs f13, 0x30(r1)
    stfs f31, 0x34(r1)
    stfs f6, 0x14(r1)
    stfs f13, 0x18(r1)
    stfs f31, 0x1c(r1)
    stfs f5, 0x20(r1)
    stfs f29, 0x24(r1)
    stfs f30, 0x28(r1)
    stfs f4, 0x2c(r1)
    stfs f27, 0x30(r1)
    stfs f28, 0x34(r1)
    ble Mtx34_Orthonormalize_L_80064A80
    frsqrte f1, f7
    lfd f3, lbl_806D2B90(r2)
    lfd f2, lbl_806D2B98(r2)
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f7, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f7, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f7, f0, f2
    fmul f0, f1, f0
    fmul f0, f7, f0
    frsp f0, f0
    stfs f0, 0x10(r1)
    lfs f7, 0x10(r1)
    Mtx34_Orthonormalize_L_80064A80:
    lfs f0, lbl_806D2B74(r2)
    fcmpo cr0, f7, f0
    cror eq, lt, eq
    bne Mtx34_Orthonormalize_L_80064AA0
    stfs f0, 0x34(r1)
    stfs f0, 0x30(r1)
    stfs f0, 0x2c(r1)
    b Mtx34_Orthonormalize_L_80064ACC
    Mtx34_Orthonormalize_L_80064AA0:
    lfs f0, lbl_806D2B6C(r2)
    lfs f2, 0x2c(r1)
    fdivs f3, f0, f7
    lfs f1, 0x30(r1)
    lfs f0, 0x34(r1)
    fmuls f2, f2, f3
    fmuls f1, f1, f3
    fmuls f0, f0, f3
    stfs f2, 0x2c(r1)
    stfs f1, 0x30(r1)
    stfs f0, 0x34(r1)
    Mtx34_Orthonormalize_L_80064ACC:
    lfs f1, 0x20(r1)
    lfs f0, 0x24(r1)
    fmuls f2, f1, f1
    lfs f3, 0x28(r1)
    fmuls f1, f0, f0
    lfs f0, lbl_806D2B74(r2)
    fmuls f3, f3, f3
    fadds f1, f2, f1
    fadds f4, f3, f1
    fcmpo cr0, f4, f0
    ble Mtx34_Orthonormalize_L_80064B44
    frsqrte f1, f4
    lfd f3, lbl_806D2B90(r2)
    lfd f2, lbl_806D2B98(r2)
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f0, f1, f0
    fmul f0, f4, f0
    frsp f0, f0
    stfs f0, 0xc(r1)
    lfs f4, 0xc(r1)
    Mtx34_Orthonormalize_L_80064B44:
    lfs f0, lbl_806D2B74(r2)
    fcmpo cr0, f4, f0
    cror eq, lt, eq
    bne Mtx34_Orthonormalize_L_80064B64
    stfs f0, 0x28(r1)
    stfs f0, 0x24(r1)
    stfs f0, 0x20(r1)
    b Mtx34_Orthonormalize_L_80064B90
    Mtx34_Orthonormalize_L_80064B64:
    lfs f0, lbl_806D2B6C(r2)
    lfs f2, 0x20(r1)
    fdivs f3, f0, f4
    lfs f1, 0x24(r1)
    lfs f0, 0x28(r1)
    fmuls f2, f2, f3
    fmuls f1, f1, f3
    fmuls f0, f0, f3
    stfs f2, 0x20(r1)
    stfs f1, 0x24(r1)
    stfs f0, 0x28(r1)
    Mtx34_Orthonormalize_L_80064B90:
    lfs f1, 0x14(r1)
    lfs f0, 0x18(r1)
    fmuls f2, f1, f1
    lfs f3, 0x1c(r1)
    fmuls f1, f0, f0
    lfs f0, lbl_806D2B74(r2)
    fmuls f3, f3, f3
    fadds f1, f2, f1
    fadds f4, f3, f1
    fcmpo cr0, f4, f0
    ble Mtx34_Orthonormalize_L_80064C08
    frsqrte f1, f4
    lfd f3, lbl_806D2B90(r2)
    lfd f2, lbl_806D2B98(r2)
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f0, f1, f0
    fmul f0, f4, f0
    frsp f0, f0
    stfs f0, 0x8(r1)
    lfs f4, 0x8(r1)
    Mtx34_Orthonormalize_L_80064C08:
    lfs f0, lbl_806D2B74(r2)
    fcmpo cr0, f4, f0
    cror eq, lt, eq
    bne Mtx34_Orthonormalize_L_80064C28
    stfs f0, 0x1c(r1)
    stfs f0, 0x18(r1)
    stfs f0, 0x14(r1)
    b Mtx34_Orthonormalize_L_80064C54
    Mtx34_Orthonormalize_L_80064C28:
    lfs f0, lbl_806D2B6C(r2)
    lfs f2, 0x14(r1)
    fdivs f3, f0, f4
    lfs f1, 0x18(r1)
    lfs f0, 0x1c(r1)
    fmuls f2, f2, f3
    fmuls f1, f1, f3
    fmuls f0, f0, f3
    stfs f2, 0x14(r1)
    stfs f1, 0x18(r1)
    stfs f0, 0x1c(r1)
    Mtx34_Orthonormalize_L_80064C54:
    lfs f0, 0x2c(r1)
    lfs f1, 0x30(r1)
    stfs f0, 0x0(r3)
    lfs f0, 0x34(r1)
    stfs f1, 0x4(r3)
    lfs f1, 0x20(r1)
    stfs f0, 0x8(r3)
    lfs f0, 0x24(r1)
    stfs f1, 0x10(r3)
    lfs f1, 0x28(r1)
    stfs f0, 0x14(r3)
    lfs f0, 0x14(r1)
    stfs f1, 0x18(r3)
    lfs f1, 0x18(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x1c(r1)
    stfs f1, 0x24(r3)
    stfs f0, 0x28(r3)
    psq_l f31, 0x98(r1), 0, 0
    lfd f31, 0x90(r1)
    psq_l f30, 0x88(r1), 0, 0
    lfd f30, 0x80(r1)
    psq_l f29, 0x78(r1), 0, 0
    lfd f29, 0x70(r1)
    psq_l f28, 0x68(r1), 0, 0
    lfd f28, 0x60(r1)
    psq_l f27, 0x58(r1), 0, 0
    lfd f27, 0x50(r1)
    psq_l f26, 0x48(r1), 0, 0
    lfd f26, 0x40(r1)
    addi r1, r1, 0xa0
    blr
}

