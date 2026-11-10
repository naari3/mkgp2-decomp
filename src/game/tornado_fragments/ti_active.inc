/* === extracted from auto_TornadoItem_TickActi_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern float AngleStepTowards_Shortest(float, float, float);
extern float BuildOrientationFromYaw();
extern void DrawEffect_ItemHitBurst_Spawn();
extern unsigned char FinalLapCoinJump_CheckActiveForObject();
extern void GabyouItem_BuildLocalTransformFromHandJoint();
extern short ItemAlias_HitRemapLookup();
extern int ItemCollision_Check();
extern void ItemHit_Dispatch();
extern unsigned char ItemObject_RaycastWallStub();
extern void ItemTracker_AcquireLock();
extern char *ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AccelClampVelocity();
extern int Item_AdvanceFallingDrop();
extern void Item_BendVelocityByGroundProbe();
extern void Item_BounceOffWall();
extern int Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar(void *, float);
extern void Item_HomingScanAndSteer();
extern void Item_InitLaunchFromKart();
extern float *KartDriver_GetJointByIdx();
extern void SoundMgr_PlaySE_Positional();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void SpriteSlot_SetScale();
extern void Vec2_RotateY();
extern float Vec3_HorizontalYawTo();
extern void Vec3_Lerp();
extern float Vec3_Magnitude_Wrapper();
extern float Vec3_ToPitch();
extern float Vec3_ToYaw();
extern void fn_801B129C();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern const float lbl_806D61F0;
extern const float lbl_806D61F4;
extern const float lbl_806D61FC;
extern const float lbl_806D6204;
extern const float lbl_806D6208;
extern const float lbl_806D620C;
extern const float lbl_806D6210;
extern const float lbl_806D6214;
extern const float lbl_806D6218;
extern const float lbl_806D621C;
extern const float lbl_806D6220;
extern const float lbl_806D6224;
extern const float lbl_806D6228;
extern const float lbl_806D622C;
extern const float lbl_806D6230;
extern const float lbl_806D6234;
extern const float lbl_806D6238;
extern const float lbl_806D623C;
extern const float lbl_806D6240;
extern const float lbl_806D6244;
extern const float lbl_806D6248;
extern const float lbl_806D624C;
extern const float lbl_806D6250;
extern const float lbl_806D6254;
extern const float lbl_806D6258;

/* --- function index (1 fns, .text 0x800F7AFC..0x800F869C) ---
 * [  0] 0x800F7AFC size:0xBA0   global TornadoItem_TickActive
 */

/* --- forward decls --- */
void TornadoItem_TickActive(char *self, char *sub);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoItem_TickActive[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoItem_TickActive = {
    (void *)&TornadoItem_TickActive, 0x00000BA0, (void *)extab_TornadoItem_TickActive
};

/* --- asm function bodies (.text order = fn address order) --- */
void TornadoItem_TickActive(char *self, char *sub)
{
    TIVec3 probes[2];
    TIVec3 hitPos;
    TIVec3 hitNormal;
    TIVec3 mid;
    TIVec3 ahead;
    TIVec3 hit2;
    TIVec3 side;
    TIVec3 wallNormal;
    TIVec3 sePos;
    TIVec3 rayFrom;
    TIVec3 rayTo;
    TIVec3 lerpA;
    TIVec3 lerpB;
    TIVec3 rayFrom2;
    TIVec3 rayTo2;
    TIVec3 rayFrom3;
    TIVec3 rayTo3;
    TIVec3 pos;
    TIVec3 vel;
    TIVec3 sePos2;
    TIVec3 bounce;
    TIVec3 sePos3;
    TIVec3 sePos4;
    TIVec3 burstPos;
    TIVec3 burstVel;
    TIVec3 bendPos;
    TIVec3 bendPos2;
    int landed;
    int hit;
    TIVec3 *p;
    int i;
    float ang;
    float mag;

    switch (TI_S8(self, 0xc9)) {
    case 0:
        TI_U8(self, 0xc9) = TI_U8(self, 0xc9) + 1;
        TI_U8(self, 0xca) = 0;
        /* fall through */
    case 1:
        switch (TI_S8(self, 0xca)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, lbl_806D61F0);
            SpriteSlot_SetScale(self + 0x14, lbl_806D6208);
            TI_U8(self, 0x28) = 1;
            TI_F32(self, 0x2c) = lbl_806D61F0;
            TI_S8(self, 0xca) = TI_S8(self, 0xca) + 1;
            /* fall through */
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, lbl_806D620C, lbl_806D6210, lbl_806D6214);
            if (FinalLapCoinJump_CheckActiveForObject(TI_PTR(sub, 0x98)) != 0) {
                TI_U8(self, 0x28) = 0;
            } else {
                TI_U8(self, 0x28) = 1;
            }
            switch (TI_S8(sub, 0xa0)) {
            case 1:
                TI_U8(self, 0x28) = 1;
                TI_U8(sub, 0xa0) = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                Item_InitLaunchFromKart(self, sub + 0x34, lbl_806D6218, lbl_806D61F0);
                TI_U8(self, 0xc9) = TI_U8(self, 0xc9) + 1;
                TI_U8(self, 0xca) = 0;
                break;
            case 2:
                TI_U8(sub, 0xa0) = 0;
                TI_U8(self, 0x28) = 0;
                TI_S8(self, 0xc8) = 3;
                TI_S8(self, 0xc9) = 0;
                break;
            default:
                Mtx44_GetTranslation_RowMajor((float *)(sub + 0x34), KartDriver_GetJointByIdx(TI_PTR(sub, 0x98), 12));
                break;
            }
            break;
        }
        break;
    case 2:
        switch (TI_S8(self, 0xca)) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            TI_S8(self, 0x8d) = 1;
            TI_U8(self, 0x3c) = 1;
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, lbl_806D61F0);
            SpriteSlot_SetScale(self + 0x14, lbl_806D621C);
            TI_U32(sub, 4) = 600;
            TI_U32(sub, 8) = 30;
            TI_U32(sub, 0xc) = 0;
            TI_U32(sub, 0x10) = 0;
            TI_F32(sub, 0x14) = Vec3_ToYaw(self + 0xb8);
            TI_F32(sub, 0x18) = lbl_806D61F0;
            TI_S8(self, 0xca) = TI_S8(self, 0xca) + 1;
            /* fall through */
        case 1:
            if (TI_U32(sub, 4) == 0) {
                TI_U32(sub, 4) = 180;
                TI_S8(self, 0xca) = TI_S8(self, 0xca) + 1;
            }
            break;
        case 2:
            if (TI_U32(sub, 4) == 0) {
                TI_U8(self, 0xca) = TI_U8(self, 0xca) + 1;
            }
            break;
        case 3:
            break;
        }
        TI_F32(self, 0xbc) = TI_F32(self, 0xbc) + lbl_806D61FC;
        Item_AccelClampVelocity(self, (int)g_ccClass == 0 ? lbl_806D6224 : lbl_806D6228,
                                (int)g_ccClass == 0 ? lbl_806D6208 : lbl_806D6220);
        fn_801B129C(self + 0xa0);
        TI_F32(self, 0xb0) = AngleStepTowards_Shortest(TI_F32(self, 0xb0), TI_F32(sub, 0x14), lbl_806D61F4);
        TI_F32(self, 0xac) = AngleStepTowards_Shortest(TI_F32(self, 0xac), Vec3_ToPitch(self + 0xb8), lbl_806D61F4);
        Item_DecayVelocityScalar(self, lbl_806D6204);
        if (TI_S8(self, 0x1d) == 1 && TI_S8(self, 0x1e) == 1) {
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, lbl_806D61F0);
            SpriteSlot_SetScale(self + 0x14, lbl_806D6208);
        }
        if (TI_U32(sub, 0x10) == 0) {
            sePos = *(TIVec3 *)(self + 0xa0);
            SoundMgr_PlaySE_Positional(0xac, &sePos, 0);
            TI_U32(sub, 0x10) = 30;
        }
        if (TI_PTR(sub, 0x7c) != 0) {
            Item_HomingScanAndSteer(self, self + 0xb0, 0);
            TI_F32(sub, 0x14) = TI_F32(self, 0xb0);
        } else if (TI_S8(self, 0xca) == 1) {
            if (TI_U32(sub, 8) == 0) {
                for (i = 0, p = probes; i < 2; i++, p++) {
                    if (i != 0) {
                        ang = BuildOrientationFromYaw(lbl_806D622C + TI_F32(sub, 0x14));
                    } else {
                        ang = BuildOrientationFromYaw(lbl_806D6230 + TI_F32(sub, 0x14));
                    }
                    GetSpawnPosition(p, 0.0f, 0.0f, lbl_806D6234);
                    Vec2_RotateY(p, p, ang);
                    Vec3_Add_DestFirst((float *)p, (float *)p, (float *)(self + 0xa0));
                    rayTo = *p;
                    rayFrom = *(TIVec3 *)(self + 0xa0);
                    if (ItemObject_RaycastWallStub(&rayFrom, &rayTo, &hitPos, &hitNormal) != 0) {
                        p->x = hitPos.x;
                        p->z = hitPos.z;
                    }
                }
                lerpB = probes[1];
                lerpA = probes[0];
                Vec3_Lerp(&mid, &lerpA, &lerpB, lbl_806D621C);
                TI_F32(sub, 0x14) = Vec3_HorizontalYawTo(self + 0xa0, &mid);
                GetSpawnPosition(&ahead, 0.0f, 0.0f, lbl_806D6234);
                Vec2_RotateY(&ahead, &ahead, TI_F32(sub, 0x14));
                Vec3_Add_DestFirst((float *)&ahead, (float *)&ahead, (float *)(self + 0xa0));
                rayTo2 = ahead;
                rayFrom2 = *(TIVec3 *)(self + 0xa0);
                if (ItemObject_RaycastWallStub(&rayFrom2, &rayTo2, &hit2, &hit2) != 0) {
                    for (i = 0; i < 2; i++) {
                        if (i != 0) {
                            ang = BuildOrientationFromYaw(lbl_806D6238 + TI_F32(sub, 0x14));
                        } else {
                            ang = BuildOrientationFromYaw(lbl_806D623C + TI_F32(sub, 0x14));
                        }
                        GetSpawnPosition(&side, 0.0f, 0.0f, lbl_806D6234);
                        Vec2_RotateY(&side, &side, ang);
                        Vec3_Add_DestFirst((float *)&side, (float *)&side, (float *)(self + 0xa0));
                        rayTo3 = side;
                        rayFrom3 = *(TIVec3 *)(self + 0xa0);
                        if (ItemObject_RaycastWallStub(&rayFrom3, &rayTo3, &hit2, &hit2) != 0) {
                            if (i == 0) {
                                Vec2_RotateY(self + 0xb8, self + 0xb8, lbl_806D6240);
                            } else {
                                Vec2_RotateY(self + 0xb8, self + 0xb8, lbl_806D6244);
                            }
                        }
                    }
                }
                TI_F32(sub, 0x18) += lbl_806D6248;
                if (1.0f < TI_F32(sub, 0x18)) {
                    TI_F32(sub, 0x18) = 1.0f;
                }
                Vec2_RotateY(self + 0xb8, self + 0xb8,
                             TI_F32(sub, 0x18) * BuildOrientationFromYaw(TI_F32(sub, 0x14) - Vec3_ToYaw(self + 0xb8)));
            } else {
                TI_F32(sub, 0x18) = lbl_806D61F0;
            }
        }
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(TI_PTR(sub, 0x98), ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(TI_U32(self, 8)), 0);
            /* fall through */
        case 2:
            if (hit == 2) {
                fn_801B1660(TI_PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
            }
            if (hit == 1) {
                ItemHit_Dispatch(self, 0, 0, 0);
            }
            ItemTracker_SetTrackPhase(self, 1);
            if (TI_PTR(sub, 0x7c) == ItemTracker_GetTargetKart(self)) {
                TI_PTR(sub, 0x7c) = 0;
                TI_U32(sub, 8) = 30;
            }
            break;
        case 3:
            fn_801B158C(TI_PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
            TI_PTR(sub, 0x7c) = 0;
            vel = *(TIVec3 *)(self + 0xb8);
            pos = *(TIVec3 *)(self + 0xa0);
            Item_ComputeYawRelativeApproach(self + 0xb8, ItemTracker_GetTargetKart(self), &pos, &vel);
            TI_F32(self, 0xb0) = Vec3_ToYaw(self + 0xb8);
            TI_F32(sub, 0x14) = TI_F32(self, 0xb0);
            TI_U32(sub, 8) = 30;
            ItemTracker_SetTrackPhase(self, 0);
            TI_U32(sub, 0xc) = 5;
            break;
        case 4:
            fn_801B14B8(TI_PTR(sub, 0x98), ItemTracker_GetTargetKart(self));
            TI_PTR(sub, 0x9c) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            TI_S8(self, 0x8d) = 0;
            TI_S8(self, 0xc8) = 2;
            TI_S8(self, 0xc9) = 0;
            TI_S8(self, 0xcb) = 3;
            return;
        case 5:
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (TI_U32(sub, 0xc) == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if (TI_S8(self, 0x8d) == 2) {
            ItemTracker_ReleaseLock(self);
            TI_S8(self, 0x8d) = 0;
            sePos2 = *(TIVec3 *)(self + 0xa0);
            SoundMgr_PlaySE_Positional(0xcb, &sePos2, 0);
            Vec3_Add_DestFirst((float *)(self + 0xb8), (float *)(self + 0xb8), (float *)(self + 0x90));
            TI_F32(self, 0xbc) = lbl_806D6220;
            TI_F32(self, 0xb8) = TI_F32(self, 0xb8) * lbl_806D6214;
            TI_F32(self, 0xc0) = TI_F32(self, 0xc0) * lbl_806D6214;
            TI_F32(self, 0xb0) = BuildOrientationFromYaw(lbl_806D624C + Vec3_ToYaw(self + 0xb8));
            TI_S8(self, 0xc8) = 2;
            TI_S8(self, 0xc9) = 0;
            TI_S8(self, 0xcb) = 4;
            return;
        }
        if (Item_CheckWallCollision(self, &wallNormal, 0) != 0) {
            bounce = wallNormal;
            Item_BounceOffWall(self, &bounce, 0, 3, lbl_806D621C, lbl_806D61F0);
            if (TI_S8(self, 0xca) == 1) {
                TI_F32(self, 0xb0) = Vec3_ToYaw(self + 0xb8);
                TI_F32(sub, 0x14) = TI_F32(self, 0xb0);
                TI_U32(sub, 8) = 0;
                return;
            }
            TI_F32(self, 0xbc) = lbl_806D6220;
            TI_F32(self, 0xb0) = BuildOrientationFromYaw(lbl_806D624C + Vec3_ToYaw(self + 0xb8));
            ItemTracker_ReleaseLock(self);
            TI_S8(self, 0x8d) = 0;
            TI_S8(self, 0xc8) = 2;
            TI_S8(self, 0xc9) = 0;
            TI_S8(self, 0xcb) = 7;
            return;
        }
        if (Item_AdvanceFallingDrop(self, &landed, 0, lbl_806D6250) != 0) {
            if (landed != 0) {
                sePos3 = *(TIVec3 *)(self + 0xa0);
                SoundMgr_PlaySE_Positional(0xad, &sePos3, 0);
                sePos4 = *(TIVec3 *)(self + 0xa0);
                SoundMgr_PlaySE_Positional(0xb5, &sePos4, 0);
                burstVel = *(TIVec3 *)(self + 0xb8);
                burstPos = *(TIVec3 *)(self + 0xa0);
                DrawEffect_ItemHitBurst_Spawn(&burstPos, &burstVel, 3);
                if (TI_S8(self, 0xca) != 3) {
                    bendPos = *(TIVec3 *)(self + 0xa0);
                    Item_BendVelocityByGroundProbe(self + 0xb8, &bendPos, TI_F32(sub, 0x14), Vec3_Magnitude_Wrapper(self + 0xb8), lbl_806D6254);
                    return;
                }
                bendPos2 = *(TIVec3 *)(self + 0xa0);
                Item_BendVelocityByGroundProbe(self + 0xb8, &bendPos2, Vec3_ToYaw(self + 0xb8), Vec3_Magnitude_Wrapper(self + 0xb8), lbl_806D6258);
                ItemTracker_ReleaseLock(self);
                TI_S8(self, 0x8d) = 0;
                TI_S8(self, 0xc8) = 2;
                TI_S8(self, 0xc9) = 0;
                TI_S8(self, 0xcb) = 5;
                return;
            }
        } else {
            ItemTracker_ReleaseLock(self);
            TI_S8(self, 0x8d) = 0;
            TI_S8(self, 0xc8) = 2;
            TI_S8(self, 0xc9) = 0;
            TI_S8(self, 0xcb) = 9;
        }
        break;
    }
}

