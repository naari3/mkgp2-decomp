/* Held/launch/homing/attached-effect phases, reconstructed from the target
 * 800E6F78..800E7EC4. These local views describe only observed fields. */
struct Vec3 { float x, y, z; };
struct HeldKart;
struct HeldEffectBus {
    unsigned char pad00[8];
    HeldKart *nextTarget;
    unsigned char pad0C[0x40];
    int itemType;
};
struct HeldKart {
    unsigned char pad00[0x304];
    HeldEffectBus *effects;
};
struct HeldEffect {
    unsigned char pad00[0x190];
    unsigned char held;
};
struct HeldSprite {
    unsigned char pad00[9];
    unsigned char advancing, completed;
    unsigned char pad0B[9];
};
struct HeldItem {
    unsigned char pad00[8];
    int type;
    unsigned char pad0C[8];
    HeldSprite sprite;
    unsigned char active;
    unsigned char pad29[3];
    float lifetime;
    Vec3 displayScale;
    unsigned char collisionEnabled;
    unsigned char pad3D[0x50];
    unsigned char trackPhase, surface;
    unsigned char pad8F[0x11];
    Vec3 position, rotation, velocity;
    float scale;
    signed char state, phase, subphase, kind;
};
struct HeldContext {
    unsigned char attached;
    unsigned char pad01[3];
    unsigned int timer, timer8, timerC;
    unsigned char pad10[4];
    float progress;
    unsigned char pad18[0x1C];
    Vec3 offset;
    unsigned char pad40[0xC];
    HeldEffect *effect;
    unsigned char pad50[0x2C];
    unsigned int field7C;
    unsigned char pad80[0x18];
    HeldKart *owner, *target;
    signed char command;
};
struct HeldRadii { Vec3 entry[11]; };
extern "C" {
extern const HeldRadii lbl_8032EEAC;
extern int g_ccClass;
extern float lbl_806D5D20, lbl_806D5D24, lbl_806D5D2C, lbl_806D5D30;
extern float lbl_806D5D34, lbl_806D5D4C, lbl_806D5D50, lbl_806D5D64;
extern float lbl_806D5D68, lbl_806D5D6C, lbl_806D5D70, lbl_806D5D74;
extern float lbl_806D5D78, lbl_806D5D7C, lbl_806D5D80, lbl_806D5D84, lbl_806D5D88;
void SpriteSlot_SetMatrixSourceEnabled_WithReseed(HeldSprite *, int);
void SpriteSlot_SetAnimFrameAndApplyScale(HeldSprite *, int, float);
void SpriteSlot_SetScale(HeldSprite *, float);
void GabyouItem_BuildLocalTransformFromHandJoint(HeldItem *, int, float, float, float);
unsigned char FinalLapCoinJump_CheckActiveForObject(HeldKart *);
void Item_InitLaunchFromKart(HeldItem *, const Vec3 *, float, float);
void *KartDriver_GetJointByIdx(HeldKart *, int);
void *KartDriver_GetKartRootMtx(HeldKart *);
void Mtx44_GetTranslation_RowMajor(Vec3 *, const void *);
float Mtx44_GetYawOfPosZ_Padded(const void *);
void ItemTracker_AcquireLock(HeldItem *);
void ItemTracker_SetTrackPhase(HeldItem *, int);
void ItemTracker_ReleaseLock(HeldItem *);
HeldKart *ItemTracker_GetTargetKart(HeldItem *);
signed char ItemObject_GetGroundTypeAt(Vec3, float *, int);
void Item_AccelClampVelocity(HeldItem *, float, float);
void fn_801B129C(const Vec3 *);
void Item_HomingScanAndSteer(HeldItem *, float *, int);
void Item_DecayVelocityScalar(HeldItem *, float);
int ItemCollision_Check(HeldItem *);
int ItemAlias_HitRemapLookup(int);
int fn_801B1D5C(HeldKart *, HeldKart *, short, int);
void fn_801B1660(HeldKart *, HeldKart *);
void fn_801B14B8(HeldKart *, HeldKart *);
void fn_801B158C(HeldKart *, HeldKart *);
void Item_ComputeYawRelativeApproach(Vec3 *, HeldKart *, Vec3, Vec3);
float Vec3_ToYaw(const Vec3 *);
void GetSpawnPosition(Vec3 *, float, float, float);
int Item_CheckWallCollision(HeldItem *, void *, void *);
int Item_AdvanceProjectileSimple(HeldItem *, float *, float, float);
int KartCharacterParam_GetIdentityIndex(HeldKart *);
float KartFxParam_GetConst1p5(HeldKart *);
void Vec3_Subtract_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
void Vec3_Scale(Vec3 *, const Vec3 *, float);
float Vec3_HorizontalYawTo(const Vec3 *, const Vec3 *);
float BuildOrientationFromYaw(float);
float AngleStepTowards_Shortest(float, float, float);
void Effect_TwoChild_Res8F_Update(void *);
HeldEffect *DrawEffect_SpawnDirect(void (*)(void *));
void SoundMgr_PlaySE_Positional(unsigned int, Vec3, int);
void ItemObject_TargetFirstHomingMatch(HeldItem *, HeldKart *);
void ItemEffectBus_ClearMask(HeldEffectBus *, unsigned long long);
void ItemEffectBus_OrMask(HeldEffectBus *, unsigned long long);
int KartItem_QueryEffectStateFromIse(HeldKart *);
int fn_801B13B0(HeldKart *, unsigned int, unsigned char);
void ItemHit_Dispatch(HeldItem *, HeldItem *, const Vec3 *, HeldKart *);

static inline void Recover(HeldItem *item, int kind)
{
    item->state = 2;
    item->phase = 0;
    item->kind = kind;
}

void GabyouItem_Tick_HeldAndHoming_2Eto31(HeldItem *item, HeldContext *context)
{
    int collision;
    short hit;
    switch (item->phase) {
    case 0:
        ++item->phase;
        item->subphase = 0;
    case 1:
        switch (item->subphase) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(&item->sprite, 1);
            SpriteSlot_SetAnimFrameAndApplyScale(&item->sprite, 0, lbl_806D5D20);
            SpriteSlot_SetScale(&item->sprite, lbl_806D5D24);
            item->lifetime = lbl_806D5D20;
            item->active = 1;
            if (item->type == 0x31 && context->effect) context->effect->held = 1;
            context->timer = 0;
            ++item->subphase;
        case 1:
            switch (item->type) {
            case 0x2E:
                GabyouItem_BuildLocalTransformFromHandJoint(item, 1, lbl_806D5D20, lbl_806D5D64, lbl_806D5D24); break;
            case 0x2F:
                GabyouItem_BuildLocalTransformFromHandJoint(item, 1, lbl_806D5D20, lbl_806D5D64, lbl_806D5D24); break;
            case 0x30:
                GabyouItem_BuildLocalTransformFromHandJoint(item, 1, lbl_806D5D20, lbl_806D5D68, lbl_806D5D2C); break;
            case 0x31:
                GabyouItem_BuildLocalTransformFromHandJoint(item, 1, lbl_806D5D20, lbl_806D5D68, lbl_806D5D2C); break;
            }
            if (FinalLapCoinJump_CheckActiveForObject(context->owner)) item->active = 0;
            else item->active = 1;
            switch (context->command) {
            case 1:
                item->active = 1;
                context->command = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(&item->sprite, 0);
                item->lifetime = lbl_806D5D24;
                if (item->type == 0x31 && context->effect) context->effect->held = 0;
                Item_InitLaunchFromKart(item, &context->offset, lbl_806D5D6C, lbl_806D5D20);
                ++item->phase;
                item->subphase = 0;
                break;
            case 2:
                context->command = 0;
                item->active = 0;
                item->state = 3;
                return;
            }
            Mtx44_GetTranslation_RowMajor(&context->offset, KartDriver_GetJointByIdx(context->owner, 12));
            break;
        }
        break;
    case 2: {
        switch (item->subphase) {
        case 0:
            ItemTracker_AcquireLock(item);
            ItemTracker_SetTrackPhase(item, 1);
            item->trackPhase = 1;
            item->collisionEnabled = 1;
            SpriteSlot_SetAnimFrameAndApplyScale(&item->sprite, 5, lbl_806D5D20);
            SpriteSlot_SetScale(&item->sprite, lbl_806D5D24);
            ItemObject_GetGroundTypeAt(item->position, &context->progress, 0);
            context->progress = item->position.y - context->progress;
            context->timer = 0;
            context->timer8 = 300;
            context->timerC = 0;
            ++item->subphase;
            break;
        case 1: break;
        }
        Item_AccelClampVelocity(item, g_ccClass == 0 ? lbl_806D5D70 : lbl_806D5D74,
            g_ccClass == 0 ? lbl_806D5D24 : lbl_806D5D50);
        fn_801B129C(&item->position);
        Item_HomingScanAndSteer(item, &item->rotation.y, 0);
        Item_DecayVelocityScalar(item, lbl_806D5D24);
        switch (item->type) {
        case 0x2E: Item_DecayVelocityScalar(item, lbl_806D5D24); break;
        case 0x2F: Item_DecayVelocityScalar(item, lbl_806D5D24); break;
        case 0x30: Item_DecayVelocityScalar(item, lbl_806D5D2C); break;
        case 0x31: Item_DecayVelocityScalar(item, lbl_806D5D2C); break;
        }
        collision = ItemCollision_Check(item);
        switch (collision) {
        case 1: {
            hit = (short)ItemAlias_HitRemapLookup(item->type);
            fn_801B1D5C(context->owner, ItemTracker_GetTargetKart(item), hit, 0);
        }
        case 2:
            if (collision == 2) fn_801B1660(context->owner, ItemTracker_GetTargetKart(item));
        case 4:
            if (collision == 4) fn_801B14B8(context->owner, ItemTracker_GetTargetKart(item));
            context->target = ItemTracker_GetTargetKart(item);
            ItemTracker_ReleaseLock(item);
            item->trackPhase = 0;
            if (collision == 1) { item->phase = 3; item->subphase = 0; return; }
            if (collision == 2) { Recover(item, 1); return; }
            Recover(item, 3);
            return;
        case 3: {
            fn_801B158C(context->owner, ItemTracker_GetTargetKart(item));
            context->field7C = 0;
            Item_ComputeYawRelativeApproach(&item->velocity, ItemTracker_GetTargetKart(item), item->position, item->velocity);
            item->rotation.y = Vec3_ToYaw(&item->velocity);
            ItemTracker_SetTrackPhase(item, 0);
            context->timerC = 5;
            break;
        }
        case 5: ItemTracker_SetTrackPhase(item, 1); break;
        }
        if (context->timerC == 0) ItemTracker_SetTrackPhase(item, 1);
        if ((int)item->trackPhase == 2) {
            ItemTracker_ReleaseLock(item);
            item->trackPhase = 0;
            if ((int)item->surface == 1) {
                GetSpawnPosition(&item->velocity, lbl_806D5D20, lbl_806D5D20, lbl_806D5D20);
                Recover(item, 4);
                return;
            }
            Recover(item, 6);
            return;
        }
        if (Item_CheckWallCollision(item, 0, 0)) {
            ItemTracker_ReleaseLock(item);
            item->trackPhase = 0;
            GetSpawnPosition(&item->velocity, lbl_806D5D20, lbl_806D5D20, lbl_806D5D20);
            Recover(item, 7);
            return;
        }
        if (!Item_AdvanceProjectileSimple(item, &context->progress, lbl_806D5D78, lbl_806D5D78)) {
            ItemTracker_ReleaseLock(item);
            item->trackPhase = 0;
            Recover(item, 9);
            return;
        }
        if (context->timer8 == 0) {
            ItemTracker_ReleaseLock(item);
            item->trackPhase = 0;
            Recover(item, 5);
        }
        break;
    }
    case 3: {
        /* The target performs a 132-byte aggregate copy before subphase dispatch.
         * Its table remains externally owned; no surrounding rodata is claimed. */
        HeldRadii radii = lbl_8032EEAC;
        switch (item->subphase) {
        case 0: {
            GetSpawnPosition(&item->velocity, lbl_806D5D20, lbl_806D5D20, lbl_806D5D20);
            SpriteSlot_SetAnimFrameAndApplyScale(&item->sprite, 1, lbl_806D5D20);
            SpriteSlot_SetScale(&item->sprite, lbl_806D5D24);
            context->progress = lbl_806D5D20;
            context->attached = 0;
            Vec3 initialPosition;
            Mtx44_GetTranslation_RowMajor(&initialPosition, KartDriver_GetJointByIdx(context->target, 15));
            float radius = radii.entry[KartCharacterParam_GetIdentityIndex(context->target)].y;
            float ownerScale = KartFxParam_GetConst1p5(context->owner);
            initialPosition.y = ownerScale * radius + initialPosition.y;
            Vec3_Subtract_DestFirst(&context->offset, &item->position, &initialPosition);
            switch (item->type) {
            case 0x2E: context->timer = 900; break;
            case 0x2F: context->timer = 900; break;
            case 0x30: context->timer = 900; break;
            case 0x31: context->timer = 900; break;
            }
            context->timer8 = 10;
            if (item->type == 0x2E || item->type == 0x2F)
                context->effect = DrawEffect_SpawnDirect(Effect_TwoChild_Res8F_Update);
            SoundMgr_PlaySE_Positional(0x98, item->position, 0);
            ++item->subphase;
            item->kind = 0;
        }
        case 1: {
            switch (item->type) {
            case 0x2E: Item_DecayVelocityScalar(item, lbl_806D5D34 * KartFxParam_GetConst1p5(context->target)); break;
            case 0x2F: Item_DecayVelocityScalar(item, lbl_806D5D34 * KartFxParam_GetConst1p5(context->target)); break;
            case 0x30: Item_DecayVelocityScalar(item, lbl_806D5D4C * KartFxParam_GetConst1p5(context->target)); break;
            case 0x31: Item_DecayVelocityScalar(item, lbl_806D5D4C * KartFxParam_GetConst1p5(context->target)); break;
            }
            if ((int)item->sprite.advancing == 1) context->progress += lbl_806D5D7C;
            else context->progress += lbl_806D5D80;
            if (lbl_806D5D24 < context->progress) context->progress = lbl_806D5D24;
            Vec3 targetPosition;
            Mtx44_GetTranslation_RowMajor(&targetPosition, KartDriver_GetJointByIdx(context->target, 15));
            float radius = radii.entry[KartCharacterParam_GetIdentityIndex(context->target)].y;
            float ownerScale = KartFxParam_GetConst1p5(context->owner);
            targetPosition.y = ownerScale * radius + targetPosition.y;
            Vec3 scaledOffset;
            Vec3_Scale(&scaledOffset, &context->offset, lbl_806D5D24 - context->progress);
            Vec3_Add_DestFirst(&item->position, &targetPosition, &scaledOffset);
            float progress;
            if (lbl_806D5D84 < (progress = context->progress)) {
                float yaw;
                switch (item->type) {
                case 0x2E: yaw = Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(context->target)); break;
                case 0x2F: yaw = Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(context->target)); break;
                case 0x30: yaw = BuildOrientationFromYaw(lbl_806D5D88 + Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(context->target))); break;
                case 0x31: yaw = BuildOrientationFromYaw(lbl_806D5D88 + Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(context->target))); break;
                }
                item->rotation.y = AngleStepTowards_Shortest(item->rotation.y, yaw, lbl_806D5D30);
            } else {
                float yaw = Vec3_HorizontalYawTo(&item->position, &targetPosition);
                float weightedYaw = progress * yaw;
                float remainder = lbl_806D5D24 - progress;
                item->rotation.y = BuildOrientationFromYaw(remainder * item->rotation.y + weightedYaw);
            }
            if (lbl_806D5D24 == context->progress) {
                if (FinalLapCoinJump_CheckActiveForObject(context->target)) item->active = 0;
                else item->active = 1;
            } else item->active = 1;
            if (lbl_806D5D24 == context->progress) {
                if (context->attached == 0) {
                    context->attached = 1;
                    ItemObject_TargetFirstHomingMatch(item, context->target);
                }
                if (context->command != 0) {
                    context->command = 0;
                    HeldEffectBus *bus = context->target->effects;
                    if (item->type == 0x31) ItemEffectBus_ClearMask(bus, 0x1000000000000000ULL);
                    if (item->type == 0x30) ItemEffectBus_ClearMask(bus, 0x2000000000000000ULL);
                    ItemEffectBus_ClearMask(bus, 0x0800000000000000ULL);
                    Recover(item, 0);
                    context->attached = 1;
                    return;
                }
                HeldEffectBus *bus = context->target->effects;
                if (item->type == 0x31) ItemEffectBus_OrMask(bus, 0x1000000000000000ULL);
                if (item->type == 0x30) ItemEffectBus_OrMask(bus, 0x2000000000000000ULL);
                ItemEffectBus_OrMask(bus, 0x0800000000000000ULL);
                bus->itemType = item->type;
                if (item->type == 0x2E || item->type == 0x2F) {
                    if (KartItem_QueryEffectStateFromIse(context->target) == 2)
                        fn_801B13B0(context->target, context->timer, 1);
                    else if (KartItem_QueryEffectStateFromIse(context->target) == 4)
                        fn_801B13B0(context->target, context->timer, 1);
                    else if (KartItem_QueryEffectStateFromIse(context->target) == 3)
                        fn_801B13B0(context->target, context->timer, 1);
                    else fn_801B13B0(context->target, context->timer, 0);
                }
                if (context->timer == 0) {
                    if (item->type == 0x2E || item->type == 0x2F) {
                        int state = KartItem_QueryEffectStateFromIse(context->target);
                        if (state == 1 || state == 2) ItemHit_Dispatch(item, 0, &item->position, context->target);
                    }
                    bus = context->target->effects;
                    if (item->type == 0x31) ItemEffectBus_ClearMask(bus, 0x1000000000000000ULL);
                    if (item->type == 0x30) ItemEffectBus_ClearMask(bus, 0x2000000000000000ULL);
                    ItemEffectBus_ClearMask(bus, 0x0800000000000000ULL);
                    Recover(item, 0);
                    context->attached = 0;
                    return;
                }
                HeldKart *nextTarget;
                HeldEffectBus *previousBus = context->target->effects;
                nextTarget = previousBus->nextTarget;
                if (nextTarget) {
                    if (item->type == 0x31) ItemEffectBus_ClearMask(previousBus, 0x1000000000000000ULL);
                    if (item->type == 0x30) ItemEffectBus_ClearMask(previousBus, 0x2000000000000000ULL);
                    ItemEffectBus_ClearMask(previousBus, 0x0800000000000000ULL);
                    context->target = nextTarget;
                    context->progress = lbl_806D5D20;
                    context->attached = 0;
                    Vec3 newPosition;
                    Mtx44_GetTranslation_RowMajor(&newPosition, KartDriver_GetJointByIdx(context->target, 15));
                    float nextRadius = radii.entry[KartCharacterParam_GetIdentityIndex(context->target)].y;
                    float nextScale = KartFxParam_GetConst1p5(context->owner);
                    newPosition.y = nextScale * nextRadius + newPosition.y;
                    Vec3_Subtract_DestFirst(&context->offset, &item->position, &newPosition);
                    Mtx44_GetTranslation_RowMajor(&newPosition, KartDriver_GetKartRootMtx(context->target));
                    float difference = BuildOrientationFromYaw(Vec3_HorizontalYawTo(&item->position, &newPosition) - item->rotation.y);
                    if (lbl_806D5D20 < difference) {
                        SpriteSlot_SetAnimFrameAndApplyScale(&item->sprite, 3, lbl_806D5D20);
                        SpriteSlot_SetScale(&item->sprite, lbl_806D5D24);
                    } else {
                        SpriteSlot_SetAnimFrameAndApplyScale(&item->sprite, 4, lbl_806D5D20);
                        SpriteSlot_SetScale(&item->sprite, lbl_806D5D24);
                    }
                    SoundMgr_PlaySE_Positional(0x98, item->position, 0);
                }
                if ((int)item->sprite.completed == 1) {
                    SpriteSlot_SetAnimFrameAndApplyScale(&item->sprite, 2, lbl_806D5D20);
                    SpriteSlot_SetScale(&item->sprite, lbl_806D5D24);
                }
            }
            if ((item->type == 0x2E || item->type == 0x2F) && context->timer < 300) {
                unsigned int interval = (context->timer / 60) * 3 + 3;
                if (context->timer % interval < 2)
                    GetSpawnPosition(&item->displayScale, lbl_806D5D50, lbl_806D5D24, lbl_806D5D24);
                else GetSpawnPosition(&item->displayScale, lbl_806D5D24, lbl_806D5D24, lbl_806D5D24);
            }
            break;
        }
        }
        break;
    }
    }
}
}
