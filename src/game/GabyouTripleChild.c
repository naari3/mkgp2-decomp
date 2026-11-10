/*
 * GabyouTripleChild (0x800F3B20..0x800F4914) - unit claim #67.
 *
 * Triple-gabyou (pin) child item: per-frame state machines for the homing
 * phase (TickActive), the post-hit / anchored-follow resolve (TickHitResolve)
 * and the master dispatch (Update).
 *
 * Field offsets recovered from the target asm; no shared header exists yet,
 * so the layout is declared locally.
 */

#include "game/types/Vec3.h"

typedef float Mtx44[4][4];

typedef struct GabyouTripleChildSub {
    /* 0x00 */ unsigned char flag_00;
    /* 0x01 */ char pad_01[3];
    /* 0x04 */ unsigned int timer_04;
    /* 0x08 */ unsigned int timer_08;
    /* 0x0C */ unsigned int timer_0c;
    /* 0x10 */ unsigned int timer_10;
    /* 0x14 */ float f_14;
    /* 0x18 */ float f_18;
    /* 0x1C */ char pad_1c[0x18];
    /* 0x34 */ Vec3 relPos_34;
    /* 0x40 */ Vec3 velCopy_40;
    /* 0x4C */ void *effect_4c;
    /* 0x50 */ char pad_50[0x2C];
    /* 0x7C */ int f_7c;
    /* 0x80 */ char pad_80[0x10];
    /* 0x90 */ unsigned char flag_90;
    /* 0x91 */ char pad_91[7];
    /* 0x98 */ void *f_98;
    /* 0x9C */ void *kart_9c;
} GabyouTripleChildSub;

typedef struct GabyouTripleChild {
    /* 0x00 */ char pad_00[0x08];
    /* 0x08 */ unsigned int field_08;
    /* 0x0C */ char pad_0c[0x04];
    /* 0x10 */ int field_10;
    /* 0x14 */ char slot_14[0x14];
    /* 0x28 */ unsigned char visible_28;
    /* 0x29 */ char pad_29[3];
    /* 0x2C */ float f_2c;
    /* 0x30 */ char pad_30[0x0C];
    /* 0x3C */ unsigned char flag_3c;
    /* 0x3D */ char pad_3d[0x0B];
    /* 0x48 */ float mtx_48[12];
    /* 0x78 */ char pad_78[0x14];
    /* 0x8C */ unsigned char category_8c;
    /* 0x8D */ signed char f_8d;
    /* 0x8E */ signed char f_8e;
    /* 0x8F */ char pad_8f[1];
    /* 0x90 */ Vec3 vel2_90;
    /* 0x9C */ void *owner_9c;
    /* 0xA0 */ Vec3 pos;
    /* 0xAC */ float rotX_ac;
    /* 0xB0 */ float rotY_b0;
    /* 0xB4 */ float rotZ_b4;
    /* 0xB8 */ Vec3 vel_b8;
    /* 0xC4 */ float scale_c4;
    /* 0xC8 */ signed char state_c8;
    /* 0xC9 */ signed char state_c9;
    /* 0xCA */ signed char state_ca;
    /* 0xCB */ signed char state_cb;
    /* 0xCC */ char pad_cc[0x20];
    /* 0xEC */ GabyouTripleChildSub sub;
} GabyouTripleChild;

typedef struct DrawEffectPartial {
    /* 0x00 */ char pad_00[0x8C];
    /* 0x8C */ Vec3 trailEnd_8c;
    /* 0x98 */ char pad_98[0x18];
    /* 0xB0 */ float scale_b0;
} DrawEffectPartial;

extern const float lbl_806D60D0;
extern const float lbl_806D60D4;
extern const float lbl_806D60D8;
extern const float lbl_806D60DC;
extern const float lbl_806D60E0;
extern const float lbl_806D60E4;
extern const float lbl_806D60E8;
extern const float lbl_806D60EC;
extern const float lbl_806D60F0;
extern const float lbl_806D60F4;
extern const float lbl_806D60F8;
extern const float lbl_806D60FC;
extern const float lbl_806D6100;
extern const float lbl_806D6104;
extern const float lbl_806D6108;
extern const float lbl_806D610C;
extern const float lbl_806D6110;
extern const float lbl_806D6114;
extern const float lbl_806D6118;
extern const Vec3 GabyouTripleChild_Update_rodata_8032FA28;

extern signed char ItemObject_GetGroundTypeAt(Vec3 *pos, float *outGroundY, int mode);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *out, const void *mtx);
extern void Vec3_Subtract_DestFirst(Vec3 *dst, const Vec3 *a, const Vec3 *b);
extern void Vec3_Add_DestFirst(Vec3 *dst, const Vec3 *a, const Vec3 *b);
extern void Vec3_Copy(Vec3 *dst, const Vec3 *src);
extern void Vec3_Scale(Vec3 *dst, const Vec3 *src, float scale);
extern float Vec3_ToYaw(const Vec3 *v);
extern void GetSpawnPosition(Vec3 *v, float x, float y, float z);
extern void Item_DecayVelocityScalar(void *item, float scalar);
extern float BuildOrientationFromYaw(float yaw);
extern float FAbs_FloatAsDouble(float x);
extern int FinalLapCoinJump_CheckActiveForObject(void *object);
extern void ItemTracker_AcquireLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int phase);
extern void ItemTracker_ReleaseLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void SpriteSlot_Container_Free(void *self);
extern void ItemHitRegistry_AddEntry(void *self, int phase);
extern unsigned char ItemHitRegistry_RemoveEntry(void *self, int entryId, int mode);
extern void Item_HomingScanAndSteer(void *self, float *yaw, int mode);
extern int ItemCollision_Check(void *self);
extern short ItemAlias_HitRemapLookup(unsigned int itemId);
extern void fn_801B1D5C(void *a, void *kart, int remapId, int flag);
extern void Item_ComputeYawRelativeApproach(Vec3 *vel, void *kart, Vec3 *pos, Vec3 *prevVel);
extern void ItemHit_Dispatch(void *self, int a, Vec3 *pos, int b);
extern int Item_CheckWallCollision(void *self, Vec3 *outNormal, int mode);
extern void Item_BounceOffWall(void *self, Vec3 *normal, int a, int b, float f1, float f2);
extern float Item_ProbeForwardGroundPitch(Vec3 *pos, float yaw, float a, float b);
extern float Item_ProbeLateralGroundPitch(Vec3 *pos, float yaw, float a, float b);
extern float AngleStepForward_OrSnap(float current, float target, float step);
/* The definition takes three floats. Declaring `target` as double is what
 * makes MWCC pass the double pitch values below without rounding them first; on
 * PowerPC both travel in the same register, elsewhere they do not. */
#ifdef __MWERKS__
extern float AngleStepTowards_Shortest(float current, double target, float step);
#else
extern float AngleStepTowards_Shortest(float current, float target, float step);
#endif
extern double atan(double x);
extern double sin(double x);
extern void DrawEffect_ItemHitOriented_Spawn(Vec3 *pos, Vec3 *vel, int mode);
extern void *DrawEffect_SpawnDirect(void *factory);
extern void DrawEffect_Free(void *effect);
extern void EffectVfx7F_PulseFan_Tick(void);
extern void ItemObject_DecrementCategoryBudget(void *self);
extern int Item_AdvanceTetherToJoint13(void *self, float *time, float scale, float a, float b);
#ifdef __MWERKS__
extern int Item_OrbitAnchorKart(void *self, Vec3 *anchor, float a, float b, int timer);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern int Item_OrbitAnchorKart(void *, Vec3 *, int, float, float);
static inline int Item_OrbitAnchorKart_Reordered(void *self, Vec3 *anchor, float a, float b, int timer) { return Item_OrbitAnchorKart(self, anchor, timer, a, b); }
#define Item_OrbitAnchorKart Item_OrbitAnchorKart_Reordered
#endif
extern void Matrix4_Identity(Mtx44 m);
extern void Mtx44_Scale_Uniform(Mtx44 dst, const Mtx44 src, float scale);
extern void Matrix4_PreMultiplyRotZ(Mtx44 dst, const Mtx44 src, float angle);
extern void Matrix4_PreMultiplyRotX(Mtx44 dst, const Mtx44 src, float angle);
extern void Matrix4_PreMultiplyRotY(Mtx44 dst, const Mtx44 src, float angle);
extern void Mtx44_Translate(Mtx44 dst, const Mtx44 src, const Vec3 *offset);
extern void DbgScene_CopyMatrix3x4Transpose(float *dst, const Mtx44 src);
extern void Mtx_TransposeToMtx44(Mtx44 dst, const float *src);
#ifdef __MWERKS__
extern void Mtx44_TransformVec3(Vec3 *out, const Mtx44 m, Vec3 in);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(Vec3 *, const Mtx44, Vec3 *);
static inline void Mtx44_TransformVec3_ByValue(Vec3 *out, const Mtx44 m, Vec3 in) { Mtx44_TransformVec3(out, m, &in); }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif

/* Manual exception metadata for Update (compiled with exceptions off).
 * postprocess_extab_user.py renames .extab_user/.extabindex_user sections
 * and symbols after compilation. Emit order (extab_order.json):
 * TickHitResolve (CW auto) -> TickActive (CW auto) -> Update (manual). */
void GabyouTripleChild_TickActive(GabyouTripleChild *self, GabyouTripleChildSub *sub);
void GabyouTripleChild_Update(GabyouTripleChild *self);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GabyouTripleChild_Update[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_GabyouTripleChild_Update = {
    (void *)&GabyouTripleChild_Update, 0x000003D4, (void *)extab_GabyouTripleChild_Update
};

void GabyouTripleChild_TickHitResolve(GabyouTripleChild *self, GabyouTripleChildSub *sub)
{
    Vec3 kartPos;
    Vec3 kartPos2;
    Vec3 pos;
    Vec3 pos2;
    float groundY;

    switch (self->state_c9) {
    case 0:
        pos = self->pos;
        ItemObject_GetGroundTypeAt(&pos, &sub->f_14, 0);
        if (self->state_cb != 5) {
            sub->timer_04 = 10;
        } else {
            sub->timer_04 = 0;
        }
        if (sub->kart_9c != 0) {
            Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(sub->kart_9c));
            Vec3_Subtract_DestFirst(&sub->relPos_34, &self->pos, &kartPos);
            Vec3_Copy(&sub->velCopy_40, &self->vel_b8);
            GetSpawnPosition(&self->vel_b8, lbl_806D60D0, lbl_806D60D0, lbl_806D60D0);
        }
        self->state_c9 = self->state_c9 + 1;
        break;
    case 1:
        break;
    }
    if (sub->timer_04 == 0) {
        self->f_2c = self->f_2c - lbl_806D60E0;
        if (self->f_2c < lbl_806D60D0) {
            self->visible_28 = 0;
            self->state_c8 = 3;
            self->state_c9 = 0;
            return;
        }
    }
    Item_DecayVelocityScalar(self, lbl_806D60D4);
    switch (self->state_cb) {
    case 0:
        self->rotX_ac = BuildOrientationFromYaw(self->rotX_ac - lbl_806D60DC);
        break;
    case 4:
        self->rotX_ac = BuildOrientationFromYaw(self->rotX_ac - lbl_806D60DC);
        break;
    case 5:
        break;
    case 9:
        self->rotX_ac = BuildOrientationFromYaw(lbl_806D60DC + self->rotX_ac);
        break;
    }
    if ((unsigned char)FinalLapCoinJump_CheckActiveForObject(sub->kart_9c) != 0) {
        self->visible_28 = 0;
    } else {
        self->visible_28 = 1;
    }
    if (sub->kart_9c == 0) {
        if (self->state_cb != 5) {
            self->vel_b8.y = self->vel_b8.y + lbl_806D60E4;
        }
        pos2 = self->pos;
        if (ItemObject_GetGroundTypeAt(&pos2, &groundY, 0) != 0) {
            self->pos.y = self->pos.y + (groundY - sub->f_14);
            sub->f_14 = groundY;
        }
    } else {
        sub->velCopy_40.y = sub->velCopy_40.y + lbl_806D60E4;
        Vec3_Add_DestFirst(&sub->relPos_34, &sub->relPos_34, &sub->velCopy_40);
        Mtx44_GetTranslation_RowMajor(&kartPos2, KartDriver_GetKartRootMtx(sub->kart_9c));
        Vec3_Add_DestFirst(&self->pos, &kartPos2, &sub->relPos_34);
    }
}

/*
 * The empty `case 2: break;` in the state_ca switch gives the target's
 * second (dead) `b` after the compare tree. The hit callback is one call
 * with the args evaluated right to left (flag, remap, kart), which gives
 * hit/remap their target registers; `!!` makes the bool flag.
 */
void GabyouTripleChild_TickActive(GabyouTripleChild *self, GabyouTripleChildSub *sub)
{
    int hit;
    float groundY;
    double dpitch;
    double dpitchL;
    Vec3 wallNormal;
    Vec3 sum;
    Vec3 posCopy4;
    Vec3 velCopy;
    Vec3 bounce;
    Vec3 probe;
    Vec3 fxPos;
    Vec3 fxVel;
    Vec3 posCopy;
    Vec3 posCopy2;
    Vec3 posCopy3;
    float peak;
    float angle;
    float rise;
    float pitch;

    switch (self->state_c9) {
    case 0:
        self->visible_28 = 1;
        self->f_2c = lbl_806D60E8;
        self->state_c9 = self->state_c9 + 1;
        self->state_ca = 0;
        /* fall through */
    case 1:
    switch (self->state_ca) {
    case 0:
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        self->f_8d = 1;
        self->flag_3c = 1;
        SpriteSlot_SetAnimFrameAndApplyScale(self->slot_14, 0, lbl_806D60D0);
        SpriteSlot_SetScale(self->slot_14, lbl_806D60E8);
        sub->timer_04 = 0x384;
        sub->timer_08 = 0;
        sub->timer_0c = 0;
        ItemHitRegistry_AddEntry(self, (unsigned char)self->state_ca++);
        /* fall through */
    case 1:
        self->vel_b8.y = self->vel_b8.y + lbl_806D60E4;
        Item_HomingScanAndSteer(self, &self->rotY_b0, 1);
        break;
    case 2:
        break;
    }
    Item_DecayVelocityScalar(self, lbl_806D60D4);
    hit = ItemCollision_Check(self);
    switch (hit) {
    case 1:
        fn_801B1D5C(sub->f_98, ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(self->field_08),
                    !!(self->state_ca == 3 ? 1 : 0));
        /* fall through */
    case 2:
    case 3:
        if (self->state_ca != 3 && hit == 3) {
            sub->f_7c = 0;
            velCopy = self->vel_b8;
            posCopy4 = self->pos;
            Item_ComputeYawRelativeApproach(&self->vel_b8, ItemTracker_GetTargetKart(self),
                                            &posCopy4, &velCopy);
            self->rotY_b0 = Vec3_ToYaw(&self->vel_b8);
            ItemTracker_SetTrackPhase(self, 0);
            sub->timer_0c = 5;
            break;
        }
        if (hit == 1) {
            ItemHit_Dispatch(self, 0, &self->pos, 0);
        }
        sub->kart_9c = ItemTracker_GetTargetKart(self);
        ItemTracker_ReleaseLock(self);
        self->f_8d = 0;
        self->vel_b8.y = lbl_806D60EC;
        DrawEffect_Free(sub->effect_4c);
        sub->effect_4c = 0;
        self->state_c8 = 2;
        self->state_c9 = 0;
        self->state_cb = 0;
        return;
    case 4:
        sub->kart_9c = ItemTracker_GetTargetKart(self);
        ItemTracker_ReleaseLock(self);
        self->f_8d = 0;
        DrawEffect_Free(sub->effect_4c);
        sub->effect_4c = 0;
        self->state_c8 = 2;
        self->state_c9 = 0;
        self->state_cb = 3;
        return;
    case 5:
        ItemTracker_SetTrackPhase(self, 1);
        break;
    }
    if (sub->timer_0c == 0) {
        ItemTracker_SetTrackPhase(self, 1);
    }
    if (self->f_8d == 2) {
        ItemTracker_ReleaseLock(self);
        self->f_8d = 0;
        DrawEffect_Free(sub->effect_4c);
        sub->effect_4c = 0;
        if (self->f_8e == 1) {
            Vec3_Add_DestFirst(&self->vel_b8, &self->vel_b8, &self->vel2_90);
            self->vel_b8.y = lbl_806D60EC;
            self->vel_b8.x = self->vel_b8.x * lbl_806D60F0;
            self->vel_b8.z = self->vel_b8.z * lbl_806D60F0;
            self->state_c8 = 2;
            self->state_c9 = 0;
            self->state_cb = 4;
            return;
        }
        self->state_c8 = 2;
        self->state_c9 = 0;
        self->state_cb = 6;
        return;
    }
    if (self->state_ca != 3) {
        if (Item_CheckWallCollision(self, &wallNormal, 0) != 0) {
            bounce = wallNormal;
            Item_BounceOffWall(self, &bounce, 0, 1, lbl_806D60F0, lbl_806D60D0);
            self->rotY_b0 = Vec3_ToYaw(&self->vel_b8);
        }
    }
    Vec3_Add_DestFirst(&sum, &self->pos, &self->vel_b8);
    probe = sum;
    if (ItemObject_GetGroundTypeAt(&probe, &groundY, 0) != 0) {
        switch (self->state_ca) {
    case 1:
        self->rotX_ac = BuildOrientationFromYaw(lbl_806D60F4 + self->rotX_ac);
        if (sum.y < groundY) {
            self->pos.y = groundY;
            self->vel_b8.y = lbl_806D60D0;
            Vec3_Scale(&self->vel_b8, &self->vel_b8, lbl_806D60F8);
            self->state_ca = self->state_ca + 1;
        }
        break;
    case 2:
        if (sub->timer_08 == 0) {
            fxVel = self->vel_b8;
            fxPos = self->pos;
            DrawEffect_ItemHitOriented_Spawn(&fxPos, &fxVel, 1);
            sub->timer_08 = 3;
        }
        peak = lbl_806D6100 * (float)sin((float)atan(lbl_806D60FC));
        angle = FAbs_FloatAsDouble(BuildOrientationFromYaw(self->rotX_ac));
        if (angle < lbl_806D6104) {
            rise = lbl_806D6100 * angle / lbl_806D6104;
        } else if (angle < lbl_806D6108) {
            rise = lbl_806D6100 + (angle - lbl_806D6104) * (peak - lbl_806D6100) / lbl_806D610C;
        } else {
            rise = peak + (angle - lbl_806D6108) * (lbl_806D6110 - peak) / lbl_806D610C;
        }
        rise = rise * self->scale_c4;
        self->pos.y = groundY + rise;
        posCopy = self->pos;
        pitch = Item_ProbeForwardGroundPitch(&posCopy, self->rotY_b0, lbl_806D6110, rise);
        self->rotX_ac = AngleStepForward_OrSnap(self->rotX_ac, pitch, lbl_806D6114);
        if (FAbs_FloatAsDouble(BuildOrientationFromYaw(self->rotX_ac - pitch)) < lbl_806D6118) {
            GetSpawnPosition(&self->vel_b8, lbl_806D60D0, lbl_806D60D0, lbl_806D60D0);
            sub->effect_4c = DrawEffect_SpawnDirect(EffectVfx7F_PulseFan_Tick);
            self->state_ca = self->state_ca + 1;
        }
        break;
    case 3:
        self->pos.y = groundY;
        posCopy2 = self->pos;
        dpitch = Item_ProbeForwardGroundPitch(&posCopy2, self->rotY_b0, lbl_806D6110, lbl_806D60D0);
        self->rotX_ac = AngleStepTowards_Shortest(self->rotX_ac, dpitch, lbl_806D60DC);
        posCopy3 = self->pos;
        dpitchL = Item_ProbeLateralGroundPitch(&posCopy3, self->rotY_b0, lbl_806D6110, lbl_806D60D0);
        self->rotZ_b4 = AngleStepTowards_Shortest(self->rotZ_b4, dpitchL, lbl_806D60DC);
        break;
        }
    } else {
        ItemTracker_ReleaseLock(self);
        self->f_8d = 0;
        DrawEffect_Free(sub->effect_4c);
        sub->effect_4c = 0;
        self->state_c8 = 2;
        self->state_c9 = 0;
        self->state_cb = 9;
        return;
    }
    if (ItemHitRegistry_RemoveEntry(self, sub->timer_04, 0) != 0) {
        ItemTracker_ReleaseLock(self);
        self->f_8d = 0;
        DrawEffect_Free(sub->effect_4c);
        sub->effect_4c = 0;
        DrawEffect_Free(sub->effect_4c);
        sub->effect_4c = 0;
        if (self->field_10 == 0) {
            ItemObject_DecrementCategoryBudget(self);
        }
        SpriteSlot_Container_Free(self);
    }
    }
}

#pragma exceptions off
void GabyouTripleChild_Update(GabyouTripleChild *self)
{
    GabyouTripleChildSub *sub;
    Mtx44 m44;
    Mtx44 m44b;
    Vec3 trail;
    Vec3 pos;

    sub = &self->sub;
    switch (self->state_c8) {
    case 0:
        sub->flag_90 = 1;
        self->field_08 = 0x46;
        SpriteSlot_InitNonLoop(self->slot_14, 0x49);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self->slot_14, 1);
        sub->flag_00 = 1;
        self->category_8c = 2;
        self->f_8d = 0;
        self->state_c8 = 1;
        self->state_c9 = 0;
        /* fall through */
    case 1:
        GabyouTripleChild_TickActive(self, sub);
        break;
    case 2:
        switch (self->state_cb) {
        case 0:
            GabyouTripleChild_TickHitResolve(self, sub);
            break;
        case 3:
            switch (self->state_c9) {
            case 0:
                GetSpawnPosition(&self->vel_b8, lbl_806D60D0, lbl_806D60D0, lbl_806D60D0);
                self->flag_3c = 0;
                sub->f_14 = lbl_806D60D0;
                sub->f_18 = self->scale_c4;
                self->state_c9 = self->state_c9 + 1;
                break;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, &sub->f_14, sub->f_18, lbl_806D60DC,
                                            lbl_806D60DC) != 0) {
                self->visible_28 = 0;
                self->state_c8 = 3;
                self->state_c9 = 0;
            }
            break;
        case 4:
            GabyouTripleChild_TickHitResolve(self, sub);
            break;
        case 6:
            switch (self->state_c9) {
            case 0:
                GetSpawnPosition(&self->vel_b8, lbl_806D60D0, lbl_806D60D0, lbl_806D60D0);
                self->flag_3c = 0;
                Vec3_Subtract_DestFirst(&sub->relPos_34, &self->pos,
                                        (const Vec3 *)((char *)self->owner_9c + 0xA0));
                sub->timer_04 = 0x1E;
                self->state_c9 = self->state_c9 + 1;
                break;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, lbl_806D60D4);
            if (Item_OrbitAnchorKart(self, &sub->relPos_34, lbl_806D60D8, lbl_806D60D8,
                                     sub->timer_04) != 0) {
                self->visible_28 = 0;
                self->state_c8 = 3;
                self->state_c9 = 0;
            }
            break;
        case 9:
            GabyouTripleChild_TickHitResolve(self, sub);
            break;
        case 5:
            GabyouTripleChild_TickHitResolve(self, sub);
            break;
        }
        break;
    case 3:
        DrawEffect_Free(sub->effect_4c);
        sub->effect_4c = 0;
        if (self->field_10 == 0) {
            ItemObject_DecrementCategoryBudget(self);
        }
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(&self->pos, &self->pos, &self->vel_b8);
    if (sub->flag_00 != 0) {
        Matrix4_Identity(m44);
        Mtx44_Scale_Uniform(m44, m44, self->scale_c4);
        Matrix4_PreMultiplyRotZ(m44, m44, self->rotZ_b4);
        Matrix4_PreMultiplyRotX(m44, m44, self->rotX_ac);
        Matrix4_PreMultiplyRotY(m44, m44, self->rotY_b0);
        pos = self->pos;
        Mtx44_Translate(m44, m44, &pos);
        DbgScene_CopyMatrix3x4Transpose(self->mtx_48, m44);
    }
    if (sub->effect_4c != 0) {
        trail = GabyouTripleChild_Update_rodata_8032FA28;
        Mtx_TransposeToMtx44(m44b, self->mtx_48);
        Mtx44_TransformVec3(&((DrawEffectPartial *)sub->effect_4c)->trailEnd_8c, m44b, trail);
        ((DrawEffectPartial *)sub->effect_4c)->scale_b0 = self->scale_c4;
    }
    if (sub->timer_04 != 0) {
        sub->timer_04 = sub->timer_04 - 1;
    }
    if (sub->timer_08 != 0) {
        sub->timer_08 = sub->timer_08 - 1;
    }
    if (sub->timer_0c != 0) {
        sub->timer_0c = sub->timer_0c - 1;
    }
    if (sub->timer_10 != 0) {
        sub->timer_10 = sub->timer_10 - 1;
    }
}
#pragma exceptions reset
