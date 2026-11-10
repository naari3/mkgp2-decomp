/*
 * PowItem @ 0x800F5B7C..0x800F6F54 (unit-claim #63).
 *
 * POW-family item unit: PowItem_TickHitResolve / PowItem_TickActive /
 * PowItem_Update. ItemObject_Partial layout is accessed by raw offsets
 * (no committed struct header yet); see Ghidra bmp_output plate comments.
 */

#include "game/types/Vec3.h"

/* --- extern decls: callees referenced from C bodies --- */
extern signed char ItemObject_GetGroundTypeAt(float *pos, float *outGroundY, int flag);
extern float *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(float *out, float *mtx);
extern void Vec3_Subtract_DestFirst(float *dst, float *a, float *b);
extern void Vec3_Add_DestFirst(float *dst, float *a, float *b);
extern void Vec3_Copy(float *dst, float *src);
#ifdef __MWERKS__
extern void GetSpawnPosition(float x, float y, float z, float *out);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void GetSpawnPosition(float *, float, float, float);
static inline void GetSpawnPosition_Reordered(float x, float y, float z, float *out) { GetSpawnPosition(out, x, y, z); }
#define GetSpawnPosition GetSpawnPosition_Reordered
#endif
extern float BuildOrientationFromYaw(float yaw);
extern void Item_DecayVelocityScalar(void *item, float scalar);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
#ifdef __MWERKS__
extern int Item_AdvanceTetherToJoint13(float anchor, float k2, float k3, void *self, float *state);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern int Item_AdvanceTetherToJoint13(void *, float *, float, float, float);
static inline int Item_AdvanceTetherToJoint13_Reordered(float anchor, float k2, float k3, void *self, float *state) { return Item_AdvanceTetherToJoint13(self, state, anchor, k2, k3); }
#define Item_AdvanceTetherToJoint13 Item_AdvanceTetherToJoint13_Reordered
#endif
#ifdef __MWERKS__
extern int Item_OrbitAnchorKart(float k1, float k2, void *self, float *offset, int timer);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern int Item_OrbitAnchorKart(void *, float *, int, float, float);
static inline int Item_OrbitAnchorKart_Reordered(float k1, float k2, void *self, float *offset, int timer) { return Item_OrbitAnchorKart(self, offset, timer, k1, k2); }
#define Item_OrbitAnchorKart Item_OrbitAnchorKart_Reordered
#endif
extern void ItemObject_DecrementCategoryBudget(void *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Matrix4_Identity(float *mtx);
#ifdef __MWERKS__
extern void Mtx44_Scale_Uniform(float scale, float *mtx, float *dst);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void Mtx44_Scale_Uniform(float *, float *, float);
static inline void Mtx44_Scale_Uniform_Reordered(float scale, float *mtx, float *dst) { Mtx44_Scale_Uniform(mtx, dst, scale); }
#define Mtx44_Scale_Uniform Mtx44_Scale_Uniform_Reordered
#endif
#ifdef __MWERKS__
extern void Matrix4_PreMultiplyRotZ(float angle, float *mtx, float *dst);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void Matrix4_PreMultiplyRotZ(float *, float *, float);
static inline void Matrix4_PreMultiplyRotZ_Reordered(float angle, float *mtx, float *dst) { Matrix4_PreMultiplyRotZ(mtx, dst, angle); }
#define Matrix4_PreMultiplyRotZ Matrix4_PreMultiplyRotZ_Reordered
#endif
#ifdef __MWERKS__
extern void Matrix4_PreMultiplyRotX(float angle, float *mtx, float *dst);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void Matrix4_PreMultiplyRotX(float *, float *, float);
static inline void Matrix4_PreMultiplyRotX_Reordered(float angle, float *mtx, float *dst) { Matrix4_PreMultiplyRotX(mtx, dst, angle); }
#define Matrix4_PreMultiplyRotX Matrix4_PreMultiplyRotX_Reordered
#endif
#ifdef __MWERKS__
extern void Matrix4_PreMultiplyRotY(float angle, float *mtx, float *dst);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void Matrix4_PreMultiplyRotY(float *, float *, float);
static inline void Matrix4_PreMultiplyRotY_Reordered(float angle, float *mtx, float *dst) { Matrix4_PreMultiplyRotY(mtx, dst, angle); }
#define Matrix4_PreMultiplyRotY Matrix4_PreMultiplyRotY_Reordered
#endif
extern void Mtx44_Translate(float *mtx, float *dst, float *pos);
extern void DbgScene_CopyMatrix3x4Transpose(float *dst, float *src);

/* --- extern decls: callees used only by TickActive --- */
extern float AngleStepForward_OrSnap(float current, float target, float step);
extern void DrawEffect_Free(void *effect);
extern void DrawEffect_ItemHitOriented_Spawn(Vec3 *pos, Vec3 *vel, int mode);
extern char *DrawEffect_SpawnDirect(void *factory);
extern float FAbs_FloatAsDouble(float x);
extern void GabyouItem_BuildLocalTransformFromHandJoint(void *self, int mode, float a, float b, float c);
extern short ItemAlias_HitRemapLookup(unsigned int itemId);
extern int ItemCollision_Check(void *self);
extern void ItemHitRegistry_AddEntry(void *self, int phase);
extern unsigned char ItemHitRegistry_RemoveEntry(void *self, int entryId, int mode);
extern void ItemHit_Dispatch(void *self, int a, void *pos, int b);
extern void ItemTracker_AcquireLock(void *self);
extern char *ItemTracker_GetTargetKart(void *self);
extern void ItemTracker_ReleaseLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int phase);
extern void Item_BounceOffWall(void *self, Vec3 *normal, int a, int b, float f1, float f2);
extern int Item_CheckWallCollision(void *self, Vec3 *outNormal, int mode);
extern void Item_ComputeYawRelativeApproach(float *vel, void *kart, Vec3 *pos, Vec3 *prevVel);
extern void Item_HomingScanAndSteer(void *self, float *yaw, int mode);
extern void Item_InitLaunchFromKart(void *self, int mode, float a, float b);
extern float Item_ProbeForwardGroundPitch(Vec3 *pos, float yaw, float a, float b);
extern float Rand_RangeFloat(float lo, float hi);
#ifndef __MWERKS__ /* this unit passes the position as the address of its own copy (SoundMgr_PlaySE_Positional.c) */
#define SoundMgr_PlaySE_Positional SoundMgr_PlaySE_Positional_ByAddress
#endif
extern void SoundMgr_PlaySE_Positional(int id, Vec3 *pos, int flag);
extern void Vec2_RotateX(float *dst, float *src, float angle);
extern void Vec2_RotateY(float *dst, float *src, float angle);
extern float Vec3_Magnitude_Wrapper(float *v);
extern void Vec3_Scale(float *dst, float *src, float s);
extern void Vec3_ScaleXZ(float *dst, float *src, float s);
extern float Vec3_ToYaw(float *v);
extern void fn_801B14B8(void *a, void *kart);
extern void fn_801B158C(void *a, void *kart);
extern void fn_801B1660(void *a, void *kart);
extern void fn_801B1D5C(void *a, void *kart, int remapId, int flag);

/* --- extern decls: sdata2 float tuning bank --- */
extern const float lbl_806D6178;
extern const float lbl_806D617C;
extern const float lbl_806D6180;
extern const float lbl_806D6184;
extern const float lbl_806D6188;
extern const float lbl_806D618C;
extern const float lbl_806D6190;
extern const float lbl_806D6194;
extern const float lbl_806D6198;
extern const float lbl_806D619C;
extern const float lbl_806D61A0;
extern const float lbl_806D61A4;
extern const float lbl_806D61A8;
extern const float lbl_806D61AC;
extern const float lbl_806D61B0;
extern const float lbl_806D61B4;
extern const float lbl_806D61B8;
extern const float lbl_806D61BC;
extern const float lbl_806D61C0;
extern const float lbl_806D61C4;
extern const float lbl_806D61C8;
extern const float lbl_806D61CC;

/* --- extern decls: large-data refs (@ha/@l pairs, asm_fn body only) --- */
extern void EffectVfx4E_TextSplash_Tick(void);
extern void Effect_HitFlash_Update(void);

void PowItem_TickHitResolve(char *self, char *sub)
{
    float groundY;
    Vec3 kartTrans;
    Vec3 anchorTrans;
    Vec3 posCopy;
    Vec3 probePos;

    switch (*(signed char *)(self + 0xc9)) {
    case 0:
        posCopy = *(Vec3 *)(self + 0xa0);
        ItemObject_GetGroundTypeAt((float *)&posCopy, (float *)(sub + 0x14), 0);
        if ((int)*(unsigned char *)(self + 0xcb) != 5) {
            *(int *)(sub + 4) = 10;
        } else {
            *(int *)(sub + 4) = 0;
        }
        if (*(void **)(sub + 0x9c) != 0) {
            Mtx44_GetTranslation_RowMajor((float *)&kartTrans,
                                          KartDriver_GetKartRootMtx(*(void **)(sub + 0x9c)));
            Vec3_Subtract_DestFirst((float *)(sub + 0x34), (float *)(self + 0xa0), (float *)&kartTrans);
            Vec3_Copy((float *)(sub + 0x40), (float *)(self + 0xb8));
            GetSpawnPosition(lbl_806D6178, lbl_806D6178, lbl_806D6178, (float *)(self + 0xb8));
        }
        *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
        break;
    case 1:
        break;
    }
    if (*(unsigned int *)(sub + 4) == 0) {
        *(float *)(self + 0x2c) = *(float *)(self + 0x2c) - lbl_806D61A4;
        if (*(float *)(self + 0x2c) < lbl_806D6178) {
            self[0x28] = 0;
            self[0xc8] = 3;
            self[0xc9] = 0;
            return;
        }
    }
    Item_DecayVelocityScalar(self, lbl_806D6198);
    switch (*(signed char *)(self + 0xcb)) {
    case 5:
        break;
    case 4:
        *(float *)(self + 0xac) = BuildOrientationFromYaw(*(float *)(self + 0xac) - lbl_806D61A0);
        break;
    case 9:
        *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D61A0 + *(float *)(self + 0xac));
        break;
    case 0:
        *(float *)(self + 0xac) = BuildOrientationFromYaw(*(float *)(self + 0xac) - lbl_806D61A0);
        break;
    }
    if (*(void **)(sub + 0x9c) == 0) {
        if ((int)*(unsigned char *)(self + 0xcb) != 5) {
            *(float *)(self + 0xbc) = *(float *)(self + 0xbc) + lbl_806D61A8;
        }
        probePos = *(Vec3 *)(self + 0xa0);
        if (ItemObject_GetGroundTypeAt((float *)&probePos, &groundY, 0) != 0) {
            *(float *)(self + 0xa4) = *(float *)(self + 0xa4) + (groundY - *(float *)(sub + 0x14));
            *(float *)(sub + 0x14) = groundY;
        }
    } else {
        *(float *)(sub + 0x44) = *(float *)(sub + 0x44) + lbl_806D61A8;
        Vec3_Add_DestFirst((float *)(sub + 0x34), (float *)(sub + 0x34), (float *)(sub + 0x40));
        Mtx44_GetTranslation_RowMajor((float *)&anchorTrans,
                                      KartDriver_GetKartRootMtx(*(void **)(sub + 0x9c)));
        Vec3_Add_DestFirst((float *)(self + 0xa0), (float *)&anchorTrans, (float *)(sub + 0x34));
    }
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x9c)) != 0) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
}

#define S8(p, o) (*(signed char *)((char *)(p) + (o)))
#define U8(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define I32(p, o) (*(int *)((char *)(p) + (o)))
#define U32(p, o) (*(unsigned int *)((char *)(p) + (o)))
#define F32(p, o) (*(float *)((char *)(p) + (o)))
#define PTR(p, o) (*(char **)((char *)(p) + (o)))
#define V3(p, o) (*(Vec3 *)((char *)(p) + (o)))

static inline void PowItem_SpawnHitFlash(Vec3 *pos, void *owner)
{
    int i;
    char *fx;

    for (i = 0; i < 8; i++) {
        fx = DrawEffect_SpawnDirect(Effect_HitFlash_Update);
        if (fx != 0) {
            Vec3_Copy((float *)(fx + 0x8c), (float *)pos);
            GetSpawnPosition(0.0f, 0.0f, Rand_RangeFloat(lbl_806D617C, lbl_806D6180), (float *)(fx + 0xa4));
            Vec2_RotateX((float *)(fx + 0xa4), (float *)(fx + 0xa4), lbl_806D6184 * Rand_RangeFloat(lbl_806D6188, lbl_806D618C));
            Vec2_RotateY((float *)(fx + 0xa4), (float *)(fx + 0xa4), lbl_806D6184 * Rand_RangeFloat(lbl_806D6190, lbl_806D6194));
            I32(fx, 0x10) = 0;
            PTR(fx, 0x11c) = owner;
            I32(fx, 0xcc) = 0;
        }
    }
}

static inline void PowItem_DropChildren(char *sub)
{
    char *fx = PTR(sub, 0x4c);
    if (fx != 0) {
        fx[0xc9] = 1;
    }
    PTR(sub, 0x4c) = 0;
    ItemTracker_ReleaseLock(PTR(sub, 0x5c));
    SpriteSlot_Container_Free(PTR(sub, 0x5c));
    PTR(sub, 0x5c) = 0;
}

#pragma push
#pragma use_lmw_stmw on
void PowItem_TickActive(char *self, char *sub)
{
    int hit;
    int hit2;
    char *fx;
    char *owner;
    int i;
    char *child;
    int j;
    float groundY;
    float pitch;
    float excess;
    Vec3 wallNormal;
    Vec3 sum;
    Vec3 posA;
    Vec3 velA;
    Vec3 posB;
    Vec3 posC;
    Vec3 posD;
    Vec3 posE;
    Vec3 posF;
    Vec3 bounce;
    Vec3 probe;
    Vec3 posG;
    Vec3 fxPos;
    Vec3 fxVel;
    Vec3 posH;
    Vec3 fxPos2;
    Vec3 fxVel2;
    Vec3 posI;

    switch (S8(self, 0xc9)) {
    case 0:
        U8(self, 0xc9) = U8(self, 0xc9) + 1;
        U8(self, 0xca) = 0;
        /* fall through */
    case 1:
        switch (S8(self, 0xca)) {
        case 0:
            sub[0] = 0;
            U8(self, 0x28) = 1;
            F32(self, 0x2c) = lbl_806D6178;
            U8(self, 0xca) = U8(self, 0xca) + 1;
            /* fall through */
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, lbl_806D61AC, lbl_806D61B0, lbl_806D61B4);
            if (FinalLapCoinJump_CheckActiveForObject(PTR(sub, 0x98)) != 0) {
                U8(self, 0x28) = 0;
            } else {
                U8(self, 0x28) = 1;
            }
            switch (S8(sub, 0xa0)) {
            case 1:
                U8(self, 0x28) = 1;
                U8(sub, 0xa0) = 0;
                sub[0] = 1;
                Item_InitLaunchFromKart(self, 0, lbl_806D617C, lbl_806D6178);
                U8(self, 0xc9) = U8(self, 0xc9) + 1;
                U8(self, 0xca) = 0;
                break;
            case 2:
                U8(sub, 0xa0) = 0;
                U8(self, 0x28) = 0;
                S8(self, 0xc8) = 3;
                S8(self, 0xc9) = 0;
                break;
            }
            break;
        }
        break;
    case 2:
        switch (S8(self, 0xca)) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            S8(self, 0x8d) = 1;
            U8(self, 0x3c) = 1;
            U32(sub, 4) = 0x384;
            U32(sub, 8) = 0;
            U32(sub, 0xc) = 0;
            ItemHitRegistry_AddEntry(self, (unsigned char)S8(self, 0xca)++);
            /* fall through */
        case 1:
            F32(self, 0xbc) = F32(self, 0xbc) + lbl_806D61A8;
            F32(self, 0xac) = BuildOrientationFromYaw(lbl_806D61B8 + F32(self, 0xac));
            Item_HomingScanAndSteer(self, (float *)(self + 0xb0), 1);
            break;
        case 2:
            break;
        }
        Item_DecayVelocityScalar(self, lbl_806D6198);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(PTR(sub, 0x98), ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(U32(self, 8)), 0);
            /* fall through */
        case 2:
            if (hit == 2) {
                fn_801B1660(PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
            }
            /* fall through */
        case 3:
            if (hit == 3) {
                fn_801B158C(PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
            }
            if (S8(self, 0xca) != 4 && hit == 3) {
                I32(sub, 0x7c) = 0;
                velA = V3(self, 0xb8);
                posA = V3(self, 0xa0);
                Item_ComputeYawRelativeApproach((float *)(self + 0xb8), ItemTracker_GetTargetKart(self), &posA, &velA);
                F32(self, 0xb0) = Vec3_ToYaw((float *)(self + 0xb8));
                ItemTracker_SetTrackPhase(self, 0);
                U32(sub, 0xc) = 5;
                break;
            }
            if (hit == 1) {
                ItemHit_Dispatch(self, 0, 0, 0);
            }
            PTR(sub, 0x9c) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            S8(self, 0x8d) = 0;
            F32(self, 0xbc) = lbl_806D61B4;
            F32(self, 0xb8) = F32(self, 0xb8) * lbl_806D61BC;
            F32(self, 0xc0) = F32(self, 0xc0) * lbl_806D61BC;
            posB = V3(self, 0xa0);
            SoundMgr_PlaySE_Positional(0x8e, &posB, 0);
            owner = PTR(sub, 0x9c);
            posC = V3(self, 0xa0);
            PowItem_SpawnHitFlash(&posC, owner);
            PowItem_DropChildren(sub);
            S8(self, 0xc8) = 2;
            S8(self, 0xc9) = 0;
            S8(self, 0xcb) = 0;
            return;
        case 4:
            fn_801B14B8(PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
            PTR(sub, 0x9c) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            S8(self, 0x8d) = 0;
            PowItem_DropChildren(sub);
            S8(self, 0xc8) = 2;
            S8(self, 0xc9) = 0;
            S8(self, 0xcb) = 3;
            return;
        case 5:
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (U32(sub, 0xc) == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if (PTR(sub, 0x5c) != 0) {
            hit2 = ItemCollision_Check(PTR(sub, 0x5c));
            switch (hit2) {
            case 1:
                fn_801B1D5C(PTR(sub, 0x98), ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(U32(self, 8)), 1);
                /* fall through */
            case 2:
                if (hit2 == 2) {
                    fn_801B1660(PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
                }
                /* fall through */
            case 3:
                if (hit2 == 3) {
                    fn_801B158C(PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
                }
                /* fall through */
            case 4:
                if (hit2 == 4) {
                    fn_801B14B8(PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
                }
                /* fall through */
            case 5:
                if (hit2 == 1) {
                    ItemHit_Dispatch(PTR(sub, 0x5c), 0, self + 0xa0, 0);
                }
                ItemTracker_SetTrackPhase(PTR(sub, 0x5c), 0);
                U32(PTR(sub, 0x5c), 0xf0) = 5;
                break;
            }
            if (U32(PTR(sub, 0x5c), 0xf0) == 0) {
                ItemTracker_SetTrackPhase(PTR(sub, 0x5c), 1);
            }
        }
        if (S8(self, 0x8d) == 2) {
            ItemTracker_ReleaseLock(self);
            S8(self, 0x8d) = 0;
            fx = PTR(sub, 0x4c);
            if (fx != 0) {
                fx[0xc9] = 1;
            }
            PTR(sub, 0x4c) = 0;
            ItemTracker_ReleaseLock(PTR(sub, 0x5c));
            SpriteSlot_Container_Free(PTR(sub, 0x5c));
            /* fakematch: natural code is `PTR(sub, 0x5c) = 0;` with
             * `for (j = 0; ...)` below; the chained store makes the zero
             * share j's register, as in the target. */
            I32(sub, 0x5c) = j = 0;
            if (S8(self, 0x8e) == 1) {
                Vec3_Add_DestFirst((float *)(self + 0xb8), (float *)(self + 0xb8), (float *)(self + 0x90));
                F32(self, 0xbc) = lbl_806D61B4;
                F32(self, 0xb8) = F32(self, 0xb8) * lbl_806D61C0;
                F32(self, 0xc0) = F32(self, 0xc0) * lbl_806D61C0;
                posD = V3(self, 0xa0);
                SoundMgr_PlaySE_Positional(0x8e, &posD, 0);
                posE = V3(self, 0xa0);
                for (i = 0; i < 8; i++) {
                    fx = DrawEffect_SpawnDirect(Effect_HitFlash_Update);
                    if (fx != 0) {
                        Vec3_Copy((float *)(fx + 0x8c), (float *)&posE);
                        GetSpawnPosition(0.0f, 0.0f, Rand_RangeFloat(lbl_806D617C, lbl_806D6180), (float *)(fx + 0xa4));
                        Vec2_RotateX((float *)(fx + 0xa4), (float *)(fx + 0xa4), lbl_806D6184 * Rand_RangeFloat(lbl_806D6188, lbl_806D618C));
                        Vec2_RotateY((float *)(fx + 0xa4), (float *)(fx + 0xa4), lbl_806D6184 * Rand_RangeFloat(lbl_806D6190, lbl_806D6194));
                        I32(fx, 0x10) = 0;
                        I32(fx, 0x11c) = 0;
                        I32(fx, 0xcc) = 0;
                    }
                }
                S8(self, 0xc8) = 2;
                S8(self, 0xc9) = 0;
                S8(self, 0xcb) = 4;
                return;
            }
            owner = PTR(self, 0x9c);
            posF = V3(self, 0xa0);
            for (; j < 8; j++) {
                fx = DrawEffect_SpawnDirect(Effect_HitFlash_Update);
                if (fx != 0) {
                    Vec3_Copy((float *)(fx + 0x8c), (float *)&posF);
                    if (owner == 0) {
                        GetSpawnPosition(0.0f, 0.0f, Rand_RangeFloat(lbl_806D617C, lbl_806D6180), (float *)(fx + 0xa4));
                        Vec2_RotateX((float *)(fx + 0xa4), (float *)(fx + 0xa4), lbl_806D6184 * Rand_RangeFloat(lbl_806D6188, lbl_806D618C));
                        Vec2_RotateY((float *)(fx + 0xa4), (float *)(fx + 0xa4), lbl_806D6184 * Rand_RangeFloat(lbl_806D6190, lbl_806D6194));
                    }
                    I32(fx, 0x10) = 0;
                    I32(fx, 0x11c) = 0;
                    PTR(fx, 0xcc) = owner;
                }
            }
            S8(self, 0xc8) = 2;
            S8(self, 0xc9) = 0;
            S8(self, 0xcb) = 6;
            return;
        }
        if (S8(self, 0xca) != 4 && Item_CheckWallCollision(self, &wallNormal, 0) != 0) {
            bounce = wallNormal;
            Item_BounceOffWall(self, &bounce, 0x8e, 2, lbl_806D61C0, lbl_806D6178);
            F32(self, 0xb0) = Vec3_ToYaw((float *)(self + 0xb8));
        }
        Vec3_Add_DestFirst((float *)&sum, (float *)(self + 0xa0), (float *)(self + 0xb8));
        probe = sum;
        if (ItemObject_GetGroundTypeAt((float *)&probe, &groundY, 0) != 0) {
        switch (S8(self, 0xca)) {
        case 1:
            if (sum.y < lbl_806D61AC * F32(self, 0xc4) + groundY) {
                posG = V3(self, 0xa0);
                SoundMgr_PlaySE_Positional(0x8e, &posG, 0);
                F32(self, 0xa4) = lbl_806D61AC * F32(self, 0xc4) + groundY;
                Vec3_ScaleXZ((float *)(self + 0xb8), (float *)(self + 0xb8), lbl_806D61BC);
                F32(self, 0xbc) = lbl_806D6178;
                PTR(sub, 0x4c) = DrawEffect_SpawnDirect(EffectVfx4E_TextSplash_Tick);
                if (PTR(sub, 0x4c) != 0) {
                    Vec3_Copy((float *)(PTR(sub, 0x4c) + 0x8c), (float *)(self + 0xa0));
                }
                if (PTR(sub, 0x5c) != 0) {
                    U8(PTR(sub, 0x5c), 0x1dc) = U8(sub, 0xf0);
                    I32(PTR(sub, 0x5c), 8) = 0x4b;
                    U8(PTR(sub, 0x5c), 0x1c) = 0x9b;
                    U8(PTR(sub, 0x5c), 0x17c) = 1;
                    I32(PTR(sub, 0x5c), 0x180) = I32(sub, 0x94);
                    I32(PTR(sub, 0x5c), 0x184) = I32(sub, 0x98);
                    ItemTracker_AcquireLock(PTR(sub, 0x5c));
                    ItemTracker_SetTrackPhase(PTR(sub, 0x5c), 1);
                    F32(PTR(sub, 0x5c), 0xc4) = lbl_806D61C4;
                }
                S8(self, 0xca) = 2;
            }
            break;
        case 2:
            if (U32(sub, 8) == 0) {
                fxVel = V3(self, 0xb8);
                fxPos = V3(self, 0xa0);
                DrawEffect_ItemHitOriented_Spawn(&fxPos, &fxVel, 2);
                U32(sub, 8) = 3;
            }
            F32(self, 0xa4) = lbl_806D61AC * F32(self, 0xc4) + groundY;
            if (PTR(sub, 0x4c) != 0) {
                Vec3_Copy((float *)(PTR(sub, 0x4c) + 0x8c), (float *)(self + 0xa0));
            }
            posH = V3(self, 0xa0);
            pitch = BuildOrientationFromYaw(lbl_806D61C8 + Item_ProbeForwardGroundPitch(&posH, F32(self, 0xb0), lbl_806D61B4, lbl_806D61AC * F32(self, 0xc4)));
            F32(self, 0xac) = AngleStepForward_OrSnap(F32(self, 0xac), pitch, lbl_806D61B8);
            if (FAbs_FloatAsDouble(BuildOrientationFromYaw(F32(self, 0xac) - pitch)) < lbl_806D6184) {
                S8(self, 0xca) = 3;
            }
            break;
        case 3:
            if (U32(sub, 8) == 0) {
                fxVel2 = V3(self, 0xb8);
                fxPos2 = V3(self, 0xa0);
                DrawEffect_ItemHitOriented_Spawn(&fxPos2, &fxVel2, 2);
                U32(sub, 8) = 3;
            }
            F32(self, 0xa4) = lbl_806D61AC * F32(self, 0xc4) + groundY;
            posI = V3(self, 0xa0);
            F32(self, 0xac) = BuildOrientationFromYaw(lbl_806D61C8 + Item_ProbeForwardGroundPitch(&posI, F32(self, 0xb0), lbl_806D61B4, lbl_806D61AC * F32(self, 0xc4)));
            if (PTR(sub, 0x4c) != 0) {
                Vec3_Copy((float *)(PTR(sub, 0x4c) + 0x8c), (float *)(self + 0xa0));
            }
            excess = Vec3_Magnitude_Wrapper((float *)(self + 0xb8)) - lbl_806D61CC;
            if (lbl_806D6178 < excess) {
                Vec3_Scale((float *)(self + 0xb8), (float *)(self + 0xb8), excess * (lbl_806D617C / Vec3_Magnitude_Wrapper((float *)(self + 0xb8))));
            } else {
                GetSpawnPosition(lbl_806D6178, lbl_806D6178, lbl_806D6178, (float *)(self + 0xb8));
                S8(self, 0xca) = 4;
            }
            break;
        }
        } else {
            ItemTracker_ReleaseLock(self);
            S8(self, 0x8d) = 0;
            PowItem_DropChildren(sub);
            S8(self, 0xc8) = 2;
            S8(self, 0xc9) = 0;
            S8(self, 0xcb) = 9;
            return;
        }
        if (ItemHitRegistry_RemoveEntry(self, U32(sub, 4), 0) != 0) {
            ItemTracker_ReleaseLock(self);
            S8(self, 0x8d) = 0;
            if (PTR(sub, 0x4c) != 0) {
                DrawEffect_Free(PTR(sub, 0x4c));
            }
            PTR(sub, 0x4c) = 0;
            ItemTracker_ReleaseLock(PTR(sub, 0x5c));
            SpriteSlot_Container_Free(PTR(sub, 0x5c));
            PTR(sub, 0x5c) = 0;
            ItemObject_DecrementCategoryBudget(self);
            SpriteSlot_Container_Free(self);
            return;
        }
        child = PTR(sub, 0x5c);
        if (child != 0) {
            if (U32(child, 0xf0) != 0) {
                U32(child, 0xf0) = U32(child, 0xf0) - 1;
            }
            Vec3_Copy((float *)(PTR(sub, 0x5c) + 0xa0), (float *)(self + 0xa0));
            F32(PTR(sub, 0x5c), 0xa4) = F32(PTR(sub, 0x5c), 0xa4) - lbl_806D61AC * F32(self, 0xc4);
        }
        break;
    }
}
#pragma pop


void PowItem_Update(char *self)
{
    Vec3 posCopy;
    float mtx[16];
    char *sub = self + 0xec;
    int code;

    switch (*(signed char *)(self + 0xc8)) {
    case 0:
        sub[0x90] = 1;
        SpriteSlot_InitNonLoop(self + 0x14, 0x4c);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        sub[0] = 1;
        self[0x8c] = 3;
        self[0x8d] = 0;
        self[0xc8] = 1;
        self[0xc9] = 0;
        /* fallthrough */
    case 1:
        PowItem_TickActive(self, sub);
        break;
    case 2:
        switch (*(signed char *)(self + 0xcb)) {
        case 0:
            PowItem_TickHitResolve(self, sub);
            break;
        case 3:
            switch (*(signed char *)(self + 0xc9)) {
            case 0:
                GetSpawnPosition(lbl_806D6178, lbl_806D6178, lbl_806D6178, (float *)(self + 0xb8));
                self[0x3c] = 0;
                *(float *)(sub + 0x14) = lbl_806D6178;
                *(float *)(sub + 0x18) = *(float *)(self + 0xc4);
                *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
                break;
            case 1:
                break;
            }
            code = Item_AdvanceTetherToJoint13(*(float *)(sub + 0x18), lbl_806D61A0, lbl_806D61A0,
                                               self, (float *)(sub + 0x14));
            if (code != 0) {
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
            }
            break;
        case 4:
            PowItem_TickHitResolve(self, sub);
            break;
        case 6:
            switch (*(signed char *)(self + 0xc9)) {
            case 0:
                GetSpawnPosition(lbl_806D6178, lbl_806D6178, lbl_806D6178, (float *)(self + 0xb8));
                self[0x3c] = 0;
                Vec3_Subtract_DestFirst((float *)(sub + 0x34), (float *)(self + 0xa0),
                                        (float *)(*(int *)(self + 0x9c) + 0xa0));
                *(int *)(sub + 4) = 0x1e;
                *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
                break;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, lbl_806D6198);
            code = Item_OrbitAnchorKart(lbl_806D619C, lbl_806D619C, self, (float *)(sub + 0x34),
                                        *(int *)(sub + 4));
            if (code != 0) {
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
            }
            break;
        case 9:
            PowItem_TickHitResolve(self, sub);
            break;
        case 5:
            PowItem_TickHitResolve(self, sub);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst((float *)(self + 0xa0), (float *)(self + 0xa0), (float *)(self + 0xb8));
    if (*(unsigned char *)sub != 0) {
        Matrix4_Identity(mtx);
        Mtx44_Scale_Uniform(*(float *)(self + 0xc4), mtx, mtx);
        Matrix4_PreMultiplyRotZ(*(float *)(self + 0xb4), mtx, mtx);
        Matrix4_PreMultiplyRotX(*(float *)(self + 0xac), mtx, mtx);
        Matrix4_PreMultiplyRotY(*(float *)(self + 0xb0), mtx, mtx);
        posCopy = *(Vec3 *)(self + 0xa0);
        Mtx44_Translate(mtx, mtx, (float *)&posCopy);
        DbgScene_CopyMatrix3x4Transpose((float *)(self + 0x48), mtx);
    }
    if (*(unsigned int *)(sub + 4) != 0) {
        *(unsigned int *)(sub + 4) = *(unsigned int *)(sub + 4) - 1;
    }
    if (*(unsigned int *)(sub + 8) != 0) {
        *(unsigned int *)(sub + 8) = *(unsigned int *)(sub + 8) - 1;
    }
    if (*(unsigned int *)(sub + 0xc) != 0) {
        *(unsigned int *)(sub + 0xc) = *(unsigned int *)(sub + 0xc) - 1;
    }
    if (*(unsigned int *)(sub + 0x10) != 0) {
        *(unsigned int *)(sub + 0x10) = *(unsigned int *)(sub + 0x10) - 1;
    }
}
