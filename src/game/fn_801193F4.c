/* --- owned .data 0x804220C8..0x80422188 (tools/own_data.py) --- */
#pragma force_active on
char lbl_804220C8[3][64] = { 105, 116, 101, 109, 95, 98, 97, 110, 97, 110, 97, 95, 121, 117, 114, 97, 51, 95, 106, 111, 105, 110, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 105, 116, 101, 109, 95, 98, 97, 110, 97, 110, 97, 95, 121, 117, 114, 97, 50, 95, 106, 111, 105, 110, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 105, 116, 101, 109, 95, 98, 97, 110, 97, 110, 97, 95, 121, 117, 114, 97, 49, 95, 106, 111, 105, 110, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
#pragma force_active reset
#include "game/types/Vec3.h"
extern float lbl_806D6C0C; /* 25.0f, shared .sdata2 pool constant */
typedef float Mtx44[4][4];

extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern short ItemAlias_HitRemapLookup(int id);
extern int ItemCollision_Check(unsigned char *self);
extern void ItemEffectBus_OrMask(void *bus, unsigned long long mask);
extern void ItemHit_Dispatch(void *self, int kind, void *pos, void *kart);
extern unsigned char *ItemObject_AllocFromPool(void *update);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *landed, int flag, float k);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void *KartDriver_GetKartRootMtx(void *kart);
#ifdef __MWERKS__
extern void Mtx44_TransformVec3(Vec3 *out, Mtx44 m, Vec3 v);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(Vec3 *, Mtx44, Vec3 *);
static inline void Mtx44_TransformVec3_ByValue(Vec3 *out, Mtx44 m, Vec3 v) { Mtx44_TransformVec3(out, m, &v); }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif
extern void Mtx_TransposeToMtx44(Mtx44 out, void *src);
#ifdef __MWERKS__
extern void SpriteSlot_SetTransform(void *slot, Vec3 pos, Vec3 rot, float scale);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void SpriteSlot_SetTransform(void *, Vec3 *, Vec3 *, float);
static inline void SpriteSlot_SetTransform_ByValue(void *slot, Vec3 pos, Vec3 rot, float scale) { SpriteSlot_SetTransform(slot, &pos, &rot, scale); }
#define SpriteSlot_SetTransform SpriteSlot_SetTransform_ByValue
#endif
extern void Vec3_Add_DestFirst(void *out, void *a, void *b);
extern void Vec3_Copy(void *dst, void *src);
extern float Vec3_HorizontalYawTo(void *from, void *to);
extern float Vec3_Magnitude_Wrapper(Vec3 *v);
extern void Vec3_Scale(void *out, void *v, float s);
extern void Vec3_Subtract_DestFirst(Vec3 *out, void *a, void *b);
extern void fn_801B158C(void *kart, void *target);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B1D5C(void *kart, void *target, int alias, int flag);
extern unsigned int CourseInteractMover_Update[];
extern unsigned int KartAttachedSpin_Update[];
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int flag, float a, float b, float c);
#ifdef __MWERKS__
extern void Item_BendVelocityByGroundProbe(void *vel, Vec3 pos, float yaw, float a, float b);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Item_BendVelocityByGroundProbe(void *, Vec3 *, float, float, float);
static inline void Item_BendVelocityByGroundProbe_ByValue(void *vel, Vec3 pos, float yaw, float a, float b) { Item_BendVelocityByGroundProbe(vel, &pos, yaw, a, b); }
#define Item_BendVelocityByGroundProbe Item_BendVelocityByGroundProbe_ByValue
#endif
extern void JointByName_GetLocalMatrix4x3(void *out, void *slot, char *name);
extern void Mtx44_GetTranslation_RowMajor(void *out, void *m);
extern float Mtx44_GetYawOfPosZ(Mtx44 m);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, void *names, int count, int visible);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void SpriteSlot_TickAnim(void *slot);
extern float Vec3_ToYaw(void *v);
extern float fn_800D4174(Mtx44 m);
extern unsigned int lbl_803324F0[];
extern unsigned char *ItemObject_SpawnWithAlias(int kind, int alias);
extern void SpriteSlot_Container_Free(void *self);
extern void SpriteSlot_InitNonLoop(void *slot, int id);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);

typedef struct GabyouTripleCtx {
    unsigned char pad0[0x4];
    unsigned int timer4;
    unsigned int timer8;
    unsigned int timerC;
    unsigned int timer10;
    unsigned char pad14[0x5C - 0x14];
    unsigned char *items[3];
    unsigned char pad68[0x94 - 0x68];
    void *owner;
    unsigned char *kart;
    void *hitKart;
    signed char launch;
    unsigned char padA1[3];
    Vec3 launchDir;
} GabyouTripleCtx;

#define ITEM(sub, i) ((sub)->items[i])
#define F32(p, off) (*(float *)((p) + (off)))
#define U32(p, off) (*(unsigned int *)((p) + (off)))
#define PTR(p, off) (*(void **)((p) + (off)))

#pragma use_lmw_stmw on

void fn_801193F4(unsigned char *self, GabyouTripleCtx *sub)
{
    int landed;
    Vec3 tgt;
    Vec3 diff;
    Vec3 save;
    Mtx44 m;
    float dist;
    int i;
    int j;
    int hit;
    unsigned char *n;

    switch ((signed char)self[0xCA]) {
    case 0:
        for (i = 0; i < 3; i++) {
            if (ITEM(sub, i) != 0) {
                ItemTracker_AcquireLock(ITEM(sub, i));
                ItemTracker_SetTrackPhase(ITEM(sub, i), 1);
                ITEM(sub, i)[0x8D] = 1;
                ITEM(sub, i)[0x3C] = 1;
                U32(ITEM(sub, i), 0xF0) = 0;
            }
        }
        sub->timer4 = 600;
        sub->timer8 = 60;
        self[0xCA]++;
    case 1:
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(sub->kart)) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }

    for (i = 0; i < 3; i++) {
        if (ITEM(sub, i) == 0) {
            continue;
        }
        ITEM(sub, i)[0x28] = self[0x28];
        hit = ItemCollision_Check(ITEM(sub, i));
        switch (hit) {
        case 1:
            fn_801B1D5C(sub->kart, ItemTracker_GetTargetKart(self),
                        ItemAlias_HitRemapLookup(*(int *)(self + 0x8)), 0);
        case 2:
            if (hit == 2) {
                fn_801B1660(sub->kart, ItemTracker_GetTargetKart(self));
            }
            sub->hitKart = ItemTracker_GetTargetKart(ITEM(sub, i));
            ItemHit_Dispatch(ITEM(sub, i), 0, 0, 0);
            for (j = 0; j < 3; j++) {
                if (ITEM(sub, j) != 0) {
                    n = ItemObject_AllocFromPool(KartAttachedSpin_Update);
                    if (n != 0) {
                        Vec3_Copy(n + 0xA0, ITEM(sub, j) + 0xA0);
                        Vec3_Copy(n + 0xAC, ITEM(sub, j) + 0xAC);
                        F32(n, 0xC4) = F32(ITEM(sub, j), 0xC4);
                        PTR(n, 0x188) = sub->hitKart;
                    }
                    ItemTracker_ReleaseLock(ITEM(sub, j));
                    ITEM(sub, j)[0x8D] = 0;
                    ITEM(sub, j)[0x28] = 0;
                }
            }
            ItemEffectBus_OrMask(PTR(sub->kart, 0x304), 0x0400000000000000ULL);
            self[0xC8] = 3;
            return;
        case 3:
            fn_801B158C(sub->kart, ItemTracker_GetTargetKart(self));
            ItemTracker_SetTrackPhase(ITEM(sub, i), 0);
            U32(ITEM(sub, i), 0xF0) = 5;
            break;
        case 5:
            ItemTracker_SetTrackPhase(ITEM(sub, i), 1);
            break;
        }

        if (U32(ITEM(sub, i), 0xF0) == 0) {
            ItemTracker_SetTrackPhase(ITEM(sub, i), 1);
        }
        if (U32(ITEM(sub, i), 0xF0) != 0) {
            U32(ITEM(sub, i), 0xF0)--;
        }

        if (*(signed char *)(ITEM(sub, i) + 0x8D) == 2) {
            for (j = 0; j < 3; j++) {
                if (ITEM(sub, j) != 0) {
                    if (*(signed char *)(ITEM(sub, i) + 0x8E) == 1) {
                        n = ItemObject_AllocFromPool(KartAttachedSpin_Update);
                        if (n != 0) {
                            Vec3_Copy(n + 0xA0, ITEM(sub, j) + 0xA0);
                            Vec3_Copy(n + 0xAC, ITEM(sub, j) + 0xAC);
                            F32(n, 0xC4) = F32(ITEM(sub, j), 0xC4);
                        }
                    } else {
                        n = ItemObject_AllocFromPool(CourseInteractMover_Update);
                        if (n != 0) {
                            Vec3_Copy(n + 0xA0, ITEM(sub, j) + 0xA0);
                            Vec3_Copy(n + 0xAC, ITEM(sub, j) + 0xAC);
                            F32(n, 0xC4) = F32(ITEM(sub, j), 0xC4);
                            PTR(n, 0x9C) = PTR(ITEM(sub, i), 0x9C);
                        }
                    }
                    ItemTracker_ReleaseLock(ITEM(sub, j));
                    ITEM(sub, j)[0x8D] = 0;
                    ITEM(sub, j)[0x28] = 0;
                }
            }
            ItemEffectBus_OrMask(PTR(sub->kart, 0x304), 0x0400000000000000ULL);
            self[0xC8] = 3;
            return;
        }

        Item_DecayVelocityScalar(ITEM(sub, i), 2.5f);
        F32(ITEM(sub, i), 0xB8) *= 0.95f;
        F32(ITEM(sub, i), 0xC0) *= 0.95f;
        F32(ITEM(sub, i), 0xBC) += -0.1f;
        if (Item_AdvanceFallingDrop(ITEM(sub, i), &landed, 0, 0.0f) && landed) {
            F32(ITEM(sub, i), 0xBC) = 0.0f;
        }
        Vec3_Add_DestFirst(ITEM(sub, i) + 0xA0, ITEM(sub, i) + 0xA0, ITEM(sub, i) + 0xB8);

        if (i != 0 && ITEM(sub, i - 1) != 0) {
            Vec3_Copy(&tgt, ITEM(sub, i - 1) + 0xA0);
        } else {
            Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(sub->kart));
            GetSpawnPosition(&tgt, 0.0f, 0.0f, -3.0f);
            Mtx44_TransformVec3(&tgt, m, tgt);
        }

        Vec3_Subtract_DestFirst(&diff, ITEM(sub, i) + 0xA0, &tgt);
        dist = Vec3_Magnitude_Wrapper(&diff);
        if (lbl_806D6C0C < dist) {
            Vec3_Copy(&save, ITEM(sub, i) + 0xA0);

            Vec3_Scale(ITEM(sub, i) + 0xA0, &diff, (1.0f / dist) * lbl_806D6C0C);
            Vec3_Add_DestFirst(ITEM(sub, i) + 0xA0, ITEM(sub, i) + 0xA0, &tgt);
            if (26.0f < dist) {
                F32(ITEM(sub, i), 0xB0) = Vec3_HorizontalYawTo(&save, ITEM(sub, i) + 0xA0);
            }
            F32(ITEM(sub, i), 0xBC) *= 0.8f;
        }

        SpriteSlot_SetTransform(ITEM(sub, i) + 0x14, *(Vec3 *)(ITEM(sub, i) + 0xA0),
                                *(Vec3 *)(ITEM(sub, i) + 0xAC), F32(ITEM(sub, i), 0xC4));
    }

    if (sub->timer8 == 0 &&
        (*(unsigned long long *)((unsigned char *)PTR(sub->kart, 0x304) + 0x10) &
         0x0000200000000000ULL) == 0) {
        sub->timer4 = 0;
    }

    if (sub->timer4 == 0) {
        for (j = 0; j < 3; j++) {
            if (ITEM(sub, j) != 0) {
                if (!FinalLapCoinJump_CheckActiveForObject(sub->kart)) {
                    n = ItemObject_AllocFromPool(KartAttachedSpin_Update);
                    if (n != 0) {
                        Vec3_Copy(n + 0xA0, ITEM(sub, j) + 0xA0);
                        Vec3_Copy(n + 0xAC, ITEM(sub, j) + 0xAC);
                        F32(n, 0xC4) = F32(ITEM(sub, j), 0xC4);
                        PTR(n, 0x188) = sub->kart;
                    }
                }
                ItemTracker_ReleaseLock(ITEM(sub, j));
                ITEM(sub, j)[0x8D] = 0;
                ITEM(sub, j)[0x28] = 0;
            }
        }
        self[0xC8] = 3;
    }
}

void fn_80119AB4(unsigned char *self, GabyouTripleCtx *sub)
{
    Mtx44 m;
    int i;

    switch ((signed char)self[0xCA]) {
    case 0:
        F32(self, 0x2C) = 0.0f;
        for (i = 0; i < 3; i++) {
            if (ITEM(sub, i) != 0) {
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(ITEM(sub, i) + 0x14, 1);
                if (i != 0) {
                    SpriteSlot_SetJointVisibilityByName(ITEM(sub, i) + 0x14, lbl_803324F0, 0x10, 1);
                }
            }
        }
        self[0xCA]++;
    case 1:
        GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 0.0f, 2.9670591f, 1.0f);
        self[0x28] = 1;
        SpriteSlot_TickAnim(self + 0x14);
        self[0x28] = 0;
        if (FinalLapCoinJump_CheckActiveForObject(sub->kart)) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
        for (i = 0; i < 3; i++) {
            if (ITEM(sub, i) != 0) {
                JointByName_GetLocalMatrix4x3(ITEM(sub, i) + 0x48, self + 0x14, lbl_804220C8[i]);
                Mtx44_GetTranslation_RowMajor(ITEM(sub, i) + 0xA0, ITEM(sub, i) + 0x48);
                F32(ITEM(sub, i), 0x2C) = F32(self, 0x2C);
                ITEM(sub, i)[0x28] = self[0x28];
            }
        }
        switch (sub->launch) {
        case 1:
            sub->launch = 0;
            F32(self, 0xB0) = Vec3_ToYaw(&sub->launchDir);
            for (i = 0; i < 3; i++) {
                if (ITEM(sub, i) != 0) {
                    SpriteSlot_SetMatrixSourceEnabled_WithReseed(ITEM(sub, i) + 0x14, 0);
                    SpriteSlot_SetJointVisibilityByName(ITEM(sub, i) + 0x14, lbl_803324F0, 0x10, 0);
                    F32(ITEM(sub, i), 0x2C) = 1.0f;
                    Mtx_TransposeToMtx44(m, ITEM(sub, i) + 0x48);
                    F32(ITEM(sub, i), 0xB0) = Mtx44_GetYawOfPosZ(m);
                    F32(ITEM(sub, i), 0xC4) = fn_800D4174(m);
                    Item_BendVelocityByGroundProbe(ITEM(sub, i) + 0xB8, *(Vec3 *)(ITEM(sub, i) + 0xA0),
                                                   F32(self, 0xB0), 5.0f, -0.5235987f);
                }
            }
            self[0xC9]++;
            self[0xCA] = 0;
            break;
        case 2:
            sub->launch = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        }
        break;
    }
}

#pragma use_lmw_stmw reset

void fn_80119D44(unsigned char *self)
{
    GabyouTripleCtx *sub = (GabyouTripleCtx *)(self + 0xEC);
    int i;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x95);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
        self[0x14] = 4;
        self[0x28] = 0;
        for (i = 0; i < 3; i++) {
            ITEM(sub, i) = ItemObject_SpawnWithAlias(0x9C, 0xFF);
            if (ITEM(sub, i) != 0) {
                PTR(ITEM(sub, i), 0x180) = sub->owner;
                PTR(ITEM(sub, i), 0x184) = sub->kart;
                PTR(ITEM(sub, i), 0xE4) = self;
                SpriteSlot_InitNonLoop(ITEM(sub, i) + 0x14, 0x96);
                ITEM(sub, i)[0x14] = 4;
                ITEM(sub, i)[0x8C] = 3;
                ITEM(sub, i)[0x8D] = 0;
            }
        }
        self[0xC8] = 1;
        self[0xC9] = 0;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xC9]) {
        case 0:
            fn_80119AB4(self, sub);
            break;
        case 1:
            fn_801193F4(self, sub);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        for (i = 0; i < 3; i++) {
            if (ITEM(sub, i) != 0) {
                SpriteSlot_Container_Free(ITEM(sub, i));
            }
            ITEM(sub, i) = 0;
        }
        SpriteSlot_Container_Free(self);
        return;
    }

    for (i = 0; i < 3; i++) {
        if (ITEM(sub, i) != 0) {
            SpriteSlot_TickAnim(ITEM(sub, i) + 0x14);
        }
    }
    if (sub->timer4 != 0) {
        sub->timer4--;
    }
    if (sub->timer8 != 0) {
        sub->timer8--;
    }
    if (sub->timerC != 0) {
        sub->timerC--;
    }
    if (sub->timer10 != 0) {
        sub->timer10--;
    }
}
