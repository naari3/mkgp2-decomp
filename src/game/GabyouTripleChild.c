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

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

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
extern const Vec3 lbl_8032FA28;

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
extern float AngleStepTowards_Shortest(float current, double target, float step);
extern double fn_8027E240(double x);
extern double fn_8027E9E8(double x);
extern void DrawEffect_ItemHitOriented_Spawn(Vec3 *pos, Vec3 *vel, int mode);
extern void *DrawEffect_SpawnDirect(void *factory);
extern void DrawEffect_Free(void *effect);
extern void EffectVfx7F_PulseFan_Tick(void);
extern void ItemObject_DecrementCategoryBudget(void *self);
extern int Item_AdvanceTetherToJoint13(void *self, float *time, float scale, float a, float b);
extern int Item_OrbitAnchorKart(void *self, Vec3 *anchor, float a, float b, int timer);
extern void Matrix4_Identity(Mtx44 m);
extern void Mtx44_Scale_Uniform(Mtx44 dst, const Mtx44 src, float scale);
extern void Matrix4_PreMultiplyRotZ(Mtx44 dst, const Mtx44 src, float angle);
extern void Matrix4_PreMultiplyRotX(Mtx44 dst, const Mtx44 src, float angle);
extern void Matrix4_PreMultiplyRotY(Mtx44 dst, const Mtx44 src, float angle);
extern void Mtx44_Translate(Mtx44 dst, const Mtx44 src, const Vec3 *offset);
extern void DbgScene_CopyMatrix3x4Transpose(float *dst, const Mtx44 src);
extern void Mtx_TransposeToMtx44(Mtx44 dst, const float *src);
extern void Mtx44_TransformVec3(Vec3 *out, const Mtx44 m, Vec3 in);

/* Manual exception metadata for the asm_fn / approach-B functions.
 * postprocess_extab_user.py renames .extab_user/.extabindex_user sections
 * and symbols after compilation. Emit order (extab_order.json):
 * TickHitResolve (CW auto) -> TickActive (manual) -> Update (manual). */
asm void GabyouTripleChild_TickActive(GabyouTripleChild *self, GabyouTripleChildSub *sub);
void GabyouTripleChild_Update(GabyouTripleChild *self);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GabyouTripleChild_TickActive[8] = {
    0x28, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_GabyouTripleChild_Update[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_GabyouTripleChild_TickActive = {
    (void *)&GabyouTripleChild_TickActive, 0x0000077C, (void *)extab_GabyouTripleChild_TickActive
};
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

/* --- paste-ready C (99.30% fuzzy, parked: see note below) ---
 * void GabyouTripleChild_TickActive(GabyouTripleChild *self, GabyouTripleChildSub *sub)
 * {
 *     int alias;
 *     int hit;
 *     int eq;
 *     float groundY;
 *     double dpitch;
 *     double dpitchL;
 *     Vec3 wallNormal;
 *     Vec3 sum;
 *     Vec3 posCopy4;
 *     Vec3 velCopy;
 *     Vec3 bounce;
 *     Vec3 probe;
 *     Vec3 fxPos;
 *     Vec3 fxVel;
 *     Vec3 posCopy;
 *     Vec3 posCopy2;
 *     Vec3 posCopy3;
 *     void *kart;
 *     float peak;
 *     float angle;
 *     float rise;
 *     float pitch;
 *
 *     switch (self->state_c9) {
 *     case 0:
 *         self->visible_28 = 1;
 *         self->f_2c = lbl_806D60E8;
 *         self->state_c9 = self->state_c9 + 1;
 *         self->state_ca = 0;
 *         (fall through)
 *     case 1:
 *     switch (self->state_ca) {
 *     case 0:
 *         ItemTracker_AcquireLock(self);
 *         ItemTracker_SetTrackPhase(self, 1);
 *         self->f_8d = 1;
 *         self->flag_3c = 1;
 *         SpriteSlot_SetAnimFrameAndApplyScale(self->slot_14, 0, lbl_806D60D0);
 *         SpriteSlot_SetScale(self->slot_14, lbl_806D60E8);
 *         sub->timer_04 = 0x384;
 *         sub->timer_08 = 0;
 *         sub->timer_0c = 0;
 *         ItemHitRegistry_AddEntry(self, (unsigned char)self->state_ca++);
 *         (fall through)
 *     case 1:
 *         self->vel_b8.y = self->vel_b8.y + lbl_806D60E4;
 *         Item_HomingScanAndSteer(self, &self->rotY_b0, 1);
 *     }
 *     Item_DecayVelocityScalar(self, lbl_806D60D4);
 *     hit = ItemCollision_Check(self);
 *     switch (hit) {
 *     case 1:
 *         eq = self->state_ca == 3;
 *         alias = ItemAlias_HitRemapLookup(self->field_08);
 *         kart = ItemTracker_GetTargetKart(self);
 *         fn_801B1D5C(sub->f_98, kart, alias, eq != 0);
 *         (fall through)
 *     case 2:
 *     case 3:
 *         if (self->state_ca != 3 && hit == 3) {
 *             sub->f_7c = 0;
 *             velCopy = self->vel_b8;
 *             posCopy4 = self->pos;
 *             Item_ComputeYawRelativeApproach(&self->vel_b8, ItemTracker_GetTargetKart(self),
 *                                             &posCopy4, &velCopy);
 *             self->rotY_b0 = Vec3_ToYaw(&self->vel_b8);
 *             ItemTracker_SetTrackPhase(self, 0);
 *             sub->timer_0c = 5;
 *             break;
 *         }
 *         if (hit == 1) {
 *             ItemHit_Dispatch(self, 0, &self->pos, 0);
 *         }
 *         sub->kart_9c = ItemTracker_GetTargetKart(self);
 *         ItemTracker_ReleaseLock(self);
 *         self->f_8d = 0;
 *         self->vel_b8.y = lbl_806D60EC;
 *         DrawEffect_Free(sub->effect_4c);
 *         sub->effect_4c = 0;
 *         self->state_c8 = 2;
 *         self->state_c9 = 0;
 *         self->state_cb = 0;
 *         return;
 *     case 4:
 *         sub->kart_9c = ItemTracker_GetTargetKart(self);
 *         ItemTracker_ReleaseLock(self);
 *         self->f_8d = 0;
 *         DrawEffect_Free(sub->effect_4c);
 *         sub->effect_4c = 0;
 *         self->state_c8 = 2;
 *         self->state_c9 = 0;
 *         self->state_cb = 3;
 *         return;
 *     case 5:
 *         ItemTracker_SetTrackPhase(self, 1);
 *         break;
 *     }
 *     if (sub->timer_0c == 0) {
 *         ItemTracker_SetTrackPhase(self, 1);
 *     }
 *     if (self->f_8d == 2) {
 *         ItemTracker_ReleaseLock(self);
 *         self->f_8d = 0;
 *         DrawEffect_Free(sub->effect_4c);
 *         sub->effect_4c = 0;
 *         if (self->f_8e == 1) {
 *             Vec3_Add_DestFirst(&self->vel_b8, &self->vel_b8, &self->vel2_90);
 *             self->vel_b8.y = lbl_806D60EC;
 *             self->vel_b8.x = self->vel_b8.x * lbl_806D60F0;
 *             self->vel_b8.z = self->vel_b8.z * lbl_806D60F0;
 *             self->state_c8 = 2;
 *             self->state_c9 = 0;
 *             self->state_cb = 4;
 *             return;
 *         }
 *         self->state_c8 = 2;
 *         self->state_c9 = 0;
 *         self->state_cb = 6;
 *         return;
 *     }
 *     if (self->state_ca != 3) {
 *         if (Item_CheckWallCollision(self, &wallNormal, 0) != 0) {
 *             bounce = wallNormal;
 *             Item_BounceOffWall(self, &bounce, 0, 1, lbl_806D60F0, lbl_806D60D0);
 *             self->rotY_b0 = Vec3_ToYaw(&self->vel_b8);
 *         }
 *     }
 *     Vec3_Add_DestFirst(&sum, &self->pos, &self->vel_b8);
 *     probe = sum;
 *     if (ItemObject_GetGroundTypeAt(&probe, &groundY, 0) != 0) {
 *         switch (self->state_ca) {
 *     case 1:
 *         self->rotX_ac = BuildOrientationFromYaw(lbl_806D60F4 + self->rotX_ac);
 *         if (sum.y < groundY) {
 *             self->pos.y = groundY;
 *             self->vel_b8.y = lbl_806D60D0;
 *             Vec3_Scale(&self->vel_b8, &self->vel_b8, lbl_806D60F8);
 *             self->state_ca = self->state_ca + 1;
 *         }
 *         break;
 *     case 2:
 *         if (sub->timer_08 == 0) {
 *             fxVel = self->vel_b8;
 *             fxPos = self->pos;
 *             DrawEffect_ItemHitOriented_Spawn(&fxPos, &fxVel, 1);
 *             sub->timer_08 = 3;
 *         }
 *         peak = lbl_806D6100 * (float)fn_8027E9E8((float)fn_8027E240(lbl_806D60FC));
 *         angle = FAbs_FloatAsDouble(BuildOrientationFromYaw(self->rotX_ac));
 *         if (angle < lbl_806D6104) {
 *             rise = lbl_806D6100 * angle / lbl_806D6104;
 *         } else if (angle < lbl_806D6108) {
 *             rise = lbl_806D6100 + (angle - lbl_806D6104) * (peak - lbl_806D6100) / lbl_806D610C;
 *         } else {
 *             rise = peak + (angle - lbl_806D6108) * (lbl_806D6110 - peak) / lbl_806D610C;
 *         }
 *         rise = rise * self->scale_c4;
 *         self->pos.y = groundY + rise;
 *         posCopy = self->pos;
 *         pitch = Item_ProbeForwardGroundPitch(&posCopy, self->rotY_b0, lbl_806D6110, rise);
 *         self->rotX_ac = AngleStepForward_OrSnap(self->rotX_ac, pitch, lbl_806D6114);
 *         if (FAbs_FloatAsDouble(BuildOrientationFromYaw(self->rotX_ac - pitch)) < lbl_806D6118) {
 *             GetSpawnPosition(&self->vel_b8, lbl_806D60D0, lbl_806D60D0, lbl_806D60D0);
 *             sub->effect_4c = DrawEffect_SpawnDirect(EffectVfx7F_PulseFan_Tick);
 *             self->state_ca = self->state_ca + 1;
 *         }
 *         break;
 *     case 3:
 *         self->pos.y = groundY;
 *         posCopy2 = self->pos;
 *         dpitch = Item_ProbeForwardGroundPitch(&posCopy2, self->rotY_b0, lbl_806D6110, lbl_806D60D0);
 *         self->rotX_ac = AngleStepTowards_Shortest(self->rotX_ac, dpitch, lbl_806D60DC);
 *         posCopy3 = self->pos;
 *         dpitchL = Item_ProbeLateralGroundPitch(&posCopy3, self->rotY_b0, lbl_806D6110, lbl_806D60D0);
 *         self->rotZ_b4 = AngleStepTowards_Shortest(self->rotZ_b4, dpitchL, lbl_806D60DC);
 *         break;
 *         }
 *     } else {
 *         ItemTracker_ReleaseLock(self);
 *         self->f_8d = 0;
 *         DrawEffect_Free(sub->effect_4c);
 *         sub->effect_4c = 0;
 *         self->state_c8 = 2;
 *         self->state_c9 = 0;
 *         self->state_cb = 9;
 *         return;
 *     }
 *     if (ItemHitRegistry_RemoveEntry(self, sub->timer_04, 0) != 0) {
 *         ItemTracker_ReleaseLock(self);
 *         self->f_8d = 0;
 *         DrawEffect_Free(sub->effect_4c);
 *         sub->effect_4c = 0;
 *         DrawEffect_Free(sub->effect_4c);
 *         sub->effect_4c = 0;
 *         if (self->field_10 == 0) {
 *             ItemObject_DecrementCategoryBudget(self);
 *         }
 *         SpriteSlot_Container_Free(self);
 *     }
 *     }
 * }
 *
 * Parked residual (2026-08-09, ~15 edit/build cycles):
 *  - one duplicate unconditional branch appended after the state_ca sparse
 *    switch decision tree (target emits two `b .L_800F3ED0`, CW 1.3.2 emits
 *    one; 6 source-shape variants tried: explicit/implicit/default-first
 *    default, no-break case fallthrough, outer-switch wrap).
 *  - hit/alias callee-saved web color swap (target hit=r28/alias=r29, CW
 *    gives hit=r29/alias=r28; mwcc_dump --colorer shows web-birth-key
 *    pinned visit order, phase2f closed class).
 * Everything else (instruction selection, block order, stack map, extab)
 * matches. Retry hint: the duplicate switch-exit branch is the same
 * emitter artifact family as the outer state_c9 switch, which DID match
 * once the whole function tail was wrapped in `case 1:` of the outer
 * switch - the inner switch may need a different enclosing structure.
 */

asm void GabyouTripleChild_TickActive(GabyouTripleChild *self, GabyouTripleChildSub *sub) { /* 0x800F3DC4 size:0x77C */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stmw r27, 0x9c(r1)
    mr r30, r3
    mr r31, r4
    lbz r0, 0xc9(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq GabyouTripleChild_TickActive_L_800F3E28
    bge GabyouTripleChild_TickActive_L_800F4524
    cmpwi r0, 0x0
    bge GabyouTripleChild_TickActive_L_800F3E04
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F3E04:
    li r0, 0x1
    lfs f0, lbl_806D60E8(r2)
    stb r0, 0x28(r30)
    li r0, 0x0
    stfs f0, 0x2c(r30)
    lbz r3, 0xc9(r30)
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    GabyouTripleChild_TickActive_L_800F3E28:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq GabyouTripleChild_TickActive_L_800F3EB0
    bge GabyouTripleChild_TickActive_L_800F3ED0
    cmpwi r0, 0x0
    bge GabyouTripleChild_TickActive_L_800F3E4C
    b GabyouTripleChild_TickActive_L_800F3ED0
    b GabyouTripleChild_TickActive_L_800F3ED0
    GabyouTripleChild_TickActive_L_800F3E4C:
    mr r3, r30
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r0, 0x1
    lfs f1, lbl_806D60D0(r2)
    stb r0, 0x8d(r30)
    addi r3, r30, 0x14
    li r4, 0x0
    stb r0, 0x3c(r30)
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D60E8(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    li r3, 0x384
    li r0, 0x0
    stw r3, 0x4(r31)
    mr r3, r30
    stw r0, 0x8(r31)
    stw r0, 0xc(r31)
    lbz r4, 0xca(r30)
    addi r0, r4, 0x1
    stb r0, 0xca(r30)
    bl ItemHitRegistry_AddEntry
    GabyouTripleChild_TickActive_L_800F3EB0:
    lfs f1, 0xbc(r30)
    mr r3, r30
    lfs f0, lbl_806D60E4(r2)
    addi r4, r30, 0xb0
    li r5, 0x1
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    bl Item_HomingScanAndSteer
    GabyouTripleChild_TickActive_L_800F3ED0:
    lfs f1, lbl_806D60D4(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    mr r3, r30
    bl ItemCollision_Check
    mr r28, r3
    cmpwi r28, 0x4
    beq GabyouTripleChild_TickActive_L_800F4044
    bge GabyouTripleChild_TickActive_L_800F3F04
    cmpwi r28, 0x1
    beq GabyouTripleChild_TickActive_L_800F3F10
    bge GabyouTripleChild_TickActive_L_800F3F54
    b GabyouTripleChild_TickActive_L_800F4094
    GabyouTripleChild_TickActive_L_800F3F04:
    cmpwi r28, 0x6
    bge GabyouTripleChild_TickActive_L_800F4094
    b GabyouTripleChild_TickActive_L_800F4088
    GabyouTripleChild_TickActive_L_800F3F10:
    lbz r0, 0xca(r30)
    lwz r3, 0x8(r30)
    extsb r0, r0
    subfic r0, r0, 0x3
    cntlzw r0, r0
    srwi r27, r0, 5
    bl ItemAlias_HitRemapLookup
    extsh r29, r3
    mr r3, r30
    bl ItemTracker_GetTargetKart
    neg r0, r27
    mr r4, r3
    or r0, r0, r27
    lwz r3, 0x98(r31)
    srwi r6, r0, 31
    mr r5, r29
    bl fn_801B1D5C
    GabyouTripleChild_TickActive_L_800F3F54:
    lbz r0, 0xca(r30)
    cmpwi r0, 0x3
    beq GabyouTripleChild_TickActive_L_800F3FE0
    cmpwi r28, 0x3
    bne GabyouTripleChild_TickActive_L_800F3FE0
    li r0, 0x0
    mr r3, r30
    stw r0, 0x7c(r31)
    lwz r4, 0xb8(r30)
    lwz r0, 0xbc(r30)
    stw r4, 0x60(r1)
    stw r0, 0x64(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x68(r1)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x6c(r1)
    stw r0, 0x70(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x74(r1)
    bl ItemTracker_GetTargetKart
    mr r4, r3
    addi r3, r30, 0xb8
    addi r5, r1, 0x6c
    addi r6, r1, 0x60
    bl Item_ComputeYawRelativeApproach
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    mr r3, r30
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0xc(r31)
    b GabyouTripleChild_TickActive_L_800F4094
    GabyouTripleChild_TickActive_L_800F3FE0:
    cmpwi r28, 0x1
    bne GabyouTripleChild_TickActive_L_800F3FFC
    mr r3, r30
    addi r5, r30, 0xa0
    li r4, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    GabyouTripleChild_TickActive_L_800F3FFC:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    lfs f0, lbl_806D60EC(r2)
    stb r0, 0x8d(r30)
    stfs f0, 0xbc(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r3, 0x0
    li r0, 0x2
    stw r3, 0x4c(r31)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r3, 0xcb(r30)
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F4044:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r4, 0x0
    li r3, 0x2
    stw r4, 0x4c(r31)
    li r0, 0x3
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F4088:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    GabyouTripleChild_TickActive_L_800F4094:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne GabyouTripleChild_TickActive_L_800F40AC
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    GabyouTripleChild_TickActive_L_800F40AC:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne GabyouTripleChild_TickActive_L_800F414C
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r4, 0x0
    stw r4, 0x4c(r31)
    lbz r0, 0x8e(r30)
    cmpwi r0, 0x1
    bne GabyouTripleChild_TickActive_L_800F4134
    addi r3, r30, 0xb8
    addi r5, r30, 0x90
    mr r4, r3
    bl Vec3_Add_DestFirst
    lfs f0, lbl_806D60EC(r2)
    li r4, 0x2
    lfs f1, lbl_806D60F0(r2)
    li r3, 0x0
    stfs f0, 0xbc(r30)
    li r0, 0x4
    lfs f0, 0xb8(r30)
    fmuls f0, f0, f1
    stfs f0, 0xb8(r30)
    lfs f0, 0xc0(r30)
    fmuls f0, f0, f1
    stfs f0, 0xc0(r30)
    stb r4, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F4134:
    li r3, 0x2
    li r0, 0x6
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F414C:
    lbz r0, 0xca(r30)
    cmpwi r0, 0x3
    beq GabyouTripleChild_TickActive_L_800F41B0
    mr r3, r30
    addi r4, r1, 0x84
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq GabyouTripleChild_TickActive_L_800F41B0
    lwz r6, 0x84(r1)
    mr r3, r30
    lwz r7, 0x88(r1)
    addi r4, r1, 0x54
    lwz r0, 0x8c(r1)
    li r5, 0x0
    stw r6, 0x54(r1)
    li r6, 0x1
    lfs f1, lbl_806D60F0(r2)
    stw r7, 0x58(r1)
    lfs f2, lbl_806D60D0(r2)
    stw r0, 0x5c(r1)
    bl Item_BounceOffWall
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    GabyouTripleChild_TickActive_L_800F41B0:
    addi r3, r1, 0x78
    addi r4, r30, 0xa0
    addi r5, r30, 0xb8
    bl Vec3_Add_DestFirst
    lwz r7, 0x78(r1)
    addi r3, r1, 0x48
    lwz r6, 0x7c(r1)
    addi r4, r1, 0x8
    lwz r0, 0x80(r1)
    li r5, 0x0
    stw r7, 0x48(r1)
    stw r6, 0x4c(r1)
    stw r0, 0x50(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq GabyouTripleChild_TickActive_L_800F4488
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x2
    beq GabyouTripleChild_TickActive_L_800F426C
    bge GabyouTripleChild_TickActive_L_800F4210
    cmpwi r0, 0x1
    bge GabyouTripleChild_TickActive_L_800F421C
    b GabyouTripleChild_TickActive_L_800F44C0
    GabyouTripleChild_TickActive_L_800F4210:
    cmpwi r0, 0x4
    bge GabyouTripleChild_TickActive_L_800F44C0
    b GabyouTripleChild_TickActive_L_800F43F4
    GabyouTripleChild_TickActive_L_800F421C:
    lfs f1, lbl_806D60F4(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    lfs f0, 0x7c(r1)
    lfs f1, 0x8(r1)
    fcmpo cr0, f0, f1
    bge GabyouTripleChild_TickActive_L_800F44C0
    stfs f1, 0xa4(r30)
    addi r3, r30, 0xb8
    lfs f0, lbl_806D60D0(r2)
    mr r4, r3
    lfs f1, lbl_806D60F8(r2)
    stfs f0, 0xbc(r30)
    bl Vec3_Scale
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b GabyouTripleChild_TickActive_L_800F44C0
    GabyouTripleChild_TickActive_L_800F426C:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne GabyouTripleChild_TickActive_L_800F42C0
    lwz r6, 0xb8(r30)
    addi r3, r1, 0x3c
    lwz r0, 0xbc(r30)
    addi r4, r1, 0x30
    li r5, 0x1
    stw r6, 0x30(r1)
    stw r0, 0x34(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x38(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x3c(r1)
    stw r0, 0x40(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x44(r1)
    bl DrawEffect_ItemHitOriented_Spawn
    li r0, 0x3
    stw r0, 0x8(r31)
    GabyouTripleChild_TickActive_L_800F42C0:
    lfs f1, lbl_806D60FC(r2)
    bl fn_8027E240
    frsp f1, f1
    bl fn_8027E9E8
    frsp f2, f1
    lfs f0, lbl_806D6100(r2)
    lfs f1, 0xac(r30)
    fmuls f31, f0, f2
    bl BuildOrientationFromYaw
    bl FAbs_FloatAsDouble
    lfs f2, lbl_806D6104(r2)
    fcmpo cr0, f1, f2
    bge GabyouTripleChild_TickActive_L_800F4304
    lfs f0, lbl_806D6100(r2)
    fmuls f0, f0, f1
    fdivs f3, f0, f2
    b GabyouTripleChild_TickActive_L_800F434C
    GabyouTripleChild_TickActive_L_800F4304:
    lfs f0, lbl_806D6108(r2)
    fcmpo cr0, f1, f0
    bge GabyouTripleChild_TickActive_L_800F4330
    lfs f3, lbl_806D6100(r2)
    fsubs f2, f1, f2
    lfs f0, lbl_806D610C(r2)
    fsubs f1, f31, f3
    fmuls f1, f2, f1
    fdivs f0, f1, f0
    fadds f3, f3, f0
    b GabyouTripleChild_TickActive_L_800F434C
    GabyouTripleChild_TickActive_L_800F4330:
    lfs f2, lbl_806D6110(r2)
    fsubs f3, f1, f0
    lfs f0, lbl_806D610C(r2)
    fsubs f1, f2, f31
    fmuls f1, f3, f1
    fdivs f0, f1, f0
    fadds f3, f31, f0
    GabyouTripleChild_TickActive_L_800F434C:
    lfs f1, 0xc4(r30)
    addi r3, r1, 0x24
    lfs f0, 0x8(r1)
    fmuls f3, f3, f1
    lfs f2, lbl_806D6110(r2)
    fadds f0, f0, f3
    stfs f0, 0xa4(r30)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x24(r1)
    stw r0, 0x28(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x2c(r1)
    lfs f1, 0xb0(r30)
    bl Item_ProbeForwardGroundPitch
    fmr f0, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D6114(r2)
    fmr f31, f0
    fmr f2, f31
    bl AngleStepForward_OrSnap
    stfs f1, 0xac(r30)
    lfs f0, 0xac(r30)
    fsubs f1, f0, f31
    bl BuildOrientationFromYaw
    bl FAbs_FloatAsDouble
    lfs f0, lbl_806D6118(r2)
    fcmpo cr0, f1, f0
    bge GabyouTripleChild_TickActive_L_800F44C0
    lfs f1, lbl_806D60D0(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lis r3, EffectVfx7F_PulseFan_Tick@ha
    addi r3, r3, EffectVfx7F_PulseFan_Tick@l
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b GabyouTripleChild_TickActive_L_800F44C0
    GabyouTripleChild_TickActive_L_800F43F4:
    lfs f0, 0x8(r1)
    addi r3, r1, 0x18
    lfs f2, lbl_806D6110(r2)
    stfs f0, 0xa4(r30)
    lfs f3, lbl_806D60D0(r2)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x18(r1)
    stw r0, 0x1c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x20(r1)
    lfs f1, 0xb0(r30)
    bl Item_ProbeForwardGroundPitch
    fmr f0, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D60DC(r2)
    fmr f2, f0
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    addi r3, r1, 0xc
    lfs f2, lbl_806D6110(r2)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    lfs f3, lbl_806D60D0(r2)
    stw r4, 0xc(r1)
    stw r0, 0x10(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x14(r1)
    lfs f1, 0xb0(r30)
    bl Item_ProbeLateralGroundPitch
    fmr f0, f1
    lfs f1, 0xb4(r30)
    lfs f3, lbl_806D60DC(r2)
    fmr f2, f0
    bl AngleStepTowards_Shortest
    stfs f1, 0xb4(r30)
    b GabyouTripleChild_TickActive_L_800F44C0
    GabyouTripleChild_TickActive_L_800F4488:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r4, 0x0
    li r3, 0x2
    stw r4, 0x4c(r31)
    li r0, 0x9
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F44C0:
    lwz r4, 0x4(r31)
    mr r3, r30
    li r5, 0x0
    bl ItemHitRegistry_RemoveEntry
    clrlwi. r0, r3, 24
    beq GabyouTripleChild_TickActive_L_800F4524
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r0, 0x0
    stw r0, 0x4c(r31)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r0, 0x0
    stw r0, 0x4c(r31)
    lwz r0, 0x10(r30)
    cmpwi r0, 0x0
    bne GabyouTripleChild_TickActive_L_800F451C
    mr r3, r30
    bl ItemObject_DecrementCategoryBudget
    GabyouTripleChild_TickActive_L_800F451C:
    mr r3, r30
    bl SpriteSlot_Container_Free
    GabyouTripleChild_TickActive_L_800F4524:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    lmw r27, 0x9c(r1)
    lwz r0, 0xc4(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
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
        trail = lbl_8032FA28;
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
