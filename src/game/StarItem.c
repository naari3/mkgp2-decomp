#include "game/objview/item_state_private.h"
#include "game/StarItemPrivate.h"
/* === extracted from auto_StarItem_BoundToVict_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern float BuildOrientationFromYaw();
float FAbs_FloatAsDouble(float);
extern unsigned char FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern void Item_DecayVelocityScalar(Item *, float);
extern void Item_SpawnHitBurstParticles();
extern void JointByName_GetMatrix4x4Transposed();
void *KartDriver_GetJointByIdx();
extern void * KartDriver_GetKartRootMtx();
float KartFxParam_GetConst1p5();
float Mtx44_GetPitchOfPosZ();
extern void Mtx44_GetTranslation_ColMajor();
extern void Mtx44_GetTranslation_RowMajor();
float Mtx44_GetYawOfPosZ();
extern void Mtx44_Inverse_GaussJordan();
extern void Mtx44_TransformVec3();
extern void Mtx_TransposeToMtx44();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetScale();
extern void Vec2_RotateY();
extern void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
extern void Vec3_Copy(Vec3 *, const Vec3 *);
extern void Vec3_Lerp();
extern void Vec3_Subtract_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
float Vec3_ToYaw();

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D63F8;
extern const float lbl_806D63FC;
extern const float lbl_806D6430;
extern const float lbl_806D6440;
extern const float lbl_806D6444;
extern const float lbl_806D6448;
extern const float lbl_806D644C;
extern const float lbl_806D6450;
extern const float lbl_806D6454;
extern const float lbl_806D6458;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern Vec3 lbl_80330374;
extern char lbl_80330380[];

/* --- function index (1 fns, .text 0x800FD948..0x800FDF24) ---
 * [  0] 0x800FD948 size:0x5DC   global StarItem_BoundToVictimTick
 */

/* --- forward decls --- */
void StarItem_BoundToVictimTick(Item *, StarWork *);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"


/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"


/* --- asm function bodies (.text order = fn address order) --- */
typedef struct StarDriverFlags {
    unsigned char pad0[0x10];
    unsigned long long bits;
} StarDriverFlags;
typedef struct StarDriver {
    unsigned char pad0[0x304];
    StarDriverFlags *flags;
} StarDriver;

#pragma exceptions on
void StarItem_BoundToVictimTick(Item *item, StarWork *work)
{
    float joint[4][4], inverse[4][4], orientation[4][4], spriteMtx[4][4];
    Vec3 endpoint, root, fallingRoot, initialPosition, rotatedEndpoint, rotatedPosition, localPosition;
    float yaw;
    switch (item->subphase) {
    case 0:
        item->x3c = 0;
        item->subphase++;
        item->step = 0;
    case 1:
        Mtx_TransposeToMtx44(joint, KartDriver_GetJointByIdx(work->target, 15));
        endpoint = lbl_80330374;
        switch (item->step) {
        case 0:
            GetSpawnPosition(&item->velocity, lbl_806D63F8, lbl_806D63F8, lbl_806D63F8);
            Mtx44_Inverse_GaussJordan(inverse, joint);
            initialPosition = item->pos;
            Mtx44_TransformVec3(&work->delta, inverse, &initialPosition);
            Vec3_Copy(&work->velocity, &work->delta);
            work->height = lbl_806D63F8;
            work->lift = 1.0f / (FAbs_FloatAsDouble(Vec3_ToYaw(&work->delta)) / 0.17453289f);
            if (0.03f < work->lift) work->lift = 0.03f;
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 3, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D6448 / (lbl_806D6430 / work->lift));
            work->timer2 = 0;
            work->timer3 = 10;
            item->step++;
        case 1:
            yaw = Vec3_ToYaw(&work->delta);
            Vec2_RotateY(&work->delta, &work->delta, -yaw);
            rotatedPosition = work->delta;
            rotatedEndpoint = endpoint;
            Vec3_Lerp(&work->delta, &rotatedEndpoint, &rotatedPosition, work->height);
            Vec2_RotateY(&work->delta, &work->delta, yaw * (lbl_806D6430 - work->height) + lbl_806D63F8 * work->height);
            work->height += work->lift;
            if (lbl_806D6430 < work->height) {
                Vec3_Copy(&work->delta, &endpoint);
                Vec2_RotateY(&work->delta, &work->delta, lbl_806D63F8);
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 4, lbl_806D63F8);
                SpriteSlot_SetScale(item->sprite, lbl_806D6430);
                item->step++;
            }
            break;
        case 2:
            if ((signed char)item->sprite[10] == 1) {
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 5, lbl_806D63F8);
                SpriteSlot_SetScale(item->sprite, lbl_806D6430);
                item->step++;
            }
            break;
        case 3:
            if ((signed char)item->sprite[10] == 1) {
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 6, lbl_806D63F8);
                SpriteSlot_SetScale(item->sprite, lbl_806D6430);
                work->timer = 20;
                item->step++;
            }
            break;
        case 4:
            if (work->timer == 0) {
                item->scale -= lbl_806D644C;
                if (item->scale < lbl_806D63F8) {
                    item->visible = 0; item->phase = 3; item->subphase = 0;
                    return;
                }
            }
            break;
        }
        localPosition = work->delta;
        Mtx44_TransformVec3(&item->pos, joint, &localPosition);
        Mtx_TransposeToMtx44(orientation, KartDriver_GetJointByIdx(work->target, 15));
        item->rotation.x = Mtx44_GetPitchOfPosZ(orientation);
        item->rotation.y = BuildOrientationFromYaw(lbl_806D63F8 + (lbl_806D6450 + Mtx44_GetYawOfPosZ(orientation)));
        Item_DecayVelocityScalar(item, lbl_806D63FC * KartFxParam_GetConst1p5(work->target));
        if (item->step == 3 && work->timer2 == 0) {
            Item_SpawnHitBurstParticles(item, work, 3, lbl_806D63F8);
            work->timer2 = 10;
        }
        if (work->timer3 == 0 && (((StarDriver *)work->target)->flags->bits & 0x10000ULL)) {
            if (work->target != 0) Mtx44_GetTranslation_RowMajor(&work->delta, KartDriver_GetKartRootMtx(work->target));
            JointByName_GetMatrix4x4Transposed(spriteMtx, item->sprite, lbl_80330380);
            Mtx44_GetTranslation_ColMajor(&item->pos, spriteMtx);
            item->rotation.x = Mtx44_GetPitchOfPosZ(spriteMtx);
            item->rotation.y = Mtx44_GetYawOfPosZ(spriteMtx);
            item->rotation.z = lbl_806D63F8;
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D63F8);
            Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(work->target));
            Vec3_Subtract_DestFirst(&work->delta, &item->pos, &root);
            GetSpawnPosition(&work->velocity, lbl_806D63F8, lbl_806D6454, lbl_806D63F8);
            item->subphase = 2; item->step = 0;
            return;
        }
        break;
    case 2:
        item->scale -= lbl_806D644C;
        if (item->scale < lbl_806D63F8) {
            item->visible = 0; item->phase = 3; item->subphase = 0;
            return;
        }
        work->velocity.y += lbl_806D6458;
        Vec3_Add_DestFirst(&work->delta, &work->delta, &work->velocity);
        Mtx44_GetTranslation_RowMajor(&fallingRoot, KartDriver_GetKartRootMtx(work->target));
        Vec3_Add_DestFirst(&item->pos, &fallingRoot, &work->delta);
        item->rotation.x = BuildOrientationFromYaw(item->rotation.x - lbl_806D6440);
        break;
    }
    if (FinalLapCoinJump_CheckActiveForObject(work->target)) item->visible = 0;
    else item->visible = 1;
}
#pragma exceptions reset

/* === extracted from auto_StarItem_FallRecover_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern float BuildOrientationFromYaw();
extern unsigned char FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern signed char ItemObject_GetGroundTypeAt();
extern void Item_DecayVelocityScalar(Item *, float);
extern void * KartDriver_GetKartRootMtx();
extern void Mtx44_GetTranslation_RowMajor();
extern void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
extern void Vec3_Copy(Vec3 *, const Vec3 *);
extern void Vec3_Subtract_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
extern float Vec3_ToPitch();

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D63F8;
extern const float lbl_806D6430;
extern const float lbl_806D6440;
extern const float lbl_806D644C;
extern const float lbl_806D6458;

/* --- function index (1 fns, .text 0x800FDF24..0x800FE1EC) ---
 * [  0] 0x800FDF24 size:0x2C8   global StarItem_FallRecoveryTick
 */

/* --- forward decls --- */
void StarItem_FallRecoveryTick(Item *, StarWork *);

#pragma exceptions on
void StarItem_FallRecoveryTick(Item *item, StarWork *work)
{
    Vec3 initialRoot, followingRoot, initialPosition, groundPosition;
    float ground;
    switch (item->subphase) {
    case 0: {
        initialPosition = item->pos;
        ItemObject_GetGroundTypeAt(&initialPosition, &work->height, 0);
        if (item->reason != 5) work->timer = 10;
        else work->timer = 0;
        if (item->reason == 5) item->velocity.y = 0.0f;
        if (work->target != 0) {
            Mtx44_GetTranslation_RowMajor(&initialRoot, KartDriver_GetKartRootMtx(work->target));
            Vec3_Subtract_DestFirst(&work->delta, &item->pos, &initialRoot);
            Vec3_Copy(&work->velocity, &item->velocity);
            GetSpawnPosition(&item->velocity, 0.0f, 0.0f, 0.0f);
        }
        item->subphase++;
        break;
    }
    case 1: break;
    }
    if (work->timer == 0) {
        item->scale -= 0.05f;
        if (item->scale < 0.0f) {
            item->visible = 0;
            item->phase = 3;
            item->subphase = 0;
            return;
        }
    }
    if (work->target == 0) {
        if (item->reason != 5) item->velocity.y += -0.1f;
        groundPosition = item->pos;
        if (ItemObject_GetGroundTypeAt(&groundPosition, &ground, 0)) {
            item->pos.y += ground - work->height;
            work->height = ground;
        }
    } else {
        work->velocity.y += -0.1f;
        Vec3_Add_DestFirst(&work->delta, &work->delta, &work->velocity);
        Mtx44_GetTranslation_RowMajor(&followingRoot, KartDriver_GetKartRootMtx(work->target));
        Vec3_Add_DestFirst(&item->pos, &followingRoot, &work->delta);
    }
    switch (item->reason) {
    case 1: item->rotation.x = BuildOrientationFromYaw(item->rotation.x - 0.17453289f); break;
    case 4: item->rotation.x = BuildOrientationFromYaw(item->rotation.x - 0.17453289f); break;
    case 9: item->rotation.x = BuildOrientationFromYaw(0.17453289f + item->rotation.x); break;
    case 5: item->rotation.x = Vec3_ToPitch(&item->velocity); break;
    }
    Item_DecayVelocityScalar(item, 1.0f);
    if (FinalLapCoinJump_CheckActiveForObject(work->target)) item->visible = 0;
    else item->visible = 1;
}
#pragma exceptions reset

/* === extracted from auto_StarItem_FlightAndLo_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
unsigned char *DrawEffect_SpawnDirect();
extern unsigned char FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition(Vec3 *, float, float, float);
int ItemAlias_HitRemapLookup();
int ItemCollision_Check();
extern void ItemHit_Dispatch();
extern signed char ItemObject_GetGroundTypeAt();
extern void ItemTracker_AcquireLock();
void *ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AccelClampVelocity();
int Item_AdvanceProjectileSimple();
int Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar(Item *, float);
extern void Item_HomingScanAndSteer();
extern void Item_InitLaunchFromKart();
extern void Item_RenderCharacterScaledFromJoint12();
extern void Item_SpawnHitBurstParticles();
extern void JointByName_GetWorldPosition();
void *KartDriver_GetJointByIdx();
extern void Mtx44_GetTranslation_RowMajor();
extern void SoundMgr_PlaySE_Positional();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void SpriteSlot_SetScale();
extern void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
extern void Vec3_Copy(Vec3 *, const Vec3 *);
float Vec3_HorizontalMagnitude();
extern void Vec3_Scale();
extern void Vec3_Subtract_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
extern float Vec3_ToPitch();
float Vec3_ToYaw();
extern void fn_801B129C();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern int g_ccClass;
extern const float lbl_806D63F8;
extern const float lbl_806D6424;
extern const float lbl_806D6430;
extern const float lbl_806D6450;
extern const float lbl_806D6454;
extern const float lbl_806D645C;
extern const float lbl_806D6460;
extern const float lbl_806D6464;
extern const float lbl_806D6468;
extern const float lbl_806D646C;
extern const float lbl_806D6470;
extern const float lbl_806D6474;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int EffectVfx82_FieldItemDropPuff_Tick[];

/* --- function index (1 fns, .text 0x800FE1EC..0x800FEA94) ---
 * [  0] 0x800FE1EC size:0x8A8   global StarItem_FlightAndLockOnTick
 */

/* --- forward decls --- */
void StarItem_FlightAndLockOnTick(Item *, StarWork *);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"


/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"


/* --- asm function bodies (.text order = fn address order) --- */
typedef struct StarFlightConstants {
    unsigned char pad0[0x3FC];
    Vec3 first, second;
    unsigned char pad414[0xC];
    char jointName[1];
} StarFlightConstants;
extern StarFlightConstants lbl_8032FF60;

#pragma exceptions on
void StarItem_FlightAndLockOnTick(Item *item, StarWork *work)
{
    Vec3 joint, wallNormal, wallPoint, correction, renderPos, renderRot, groundPos, hitPos, approachPos, approachVelocity, burstPos;
    StarFlightConstants *constants = &lbl_8032FF60;
    switch (item->subphase) {
    case 0:
        item->subphase++;
        item->step = 0;
    case 1:
        switch (item->step) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 1);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D6454);
            item->visible = 1;
            item->scale = lbl_806D63F8;
            item->param = lbl_806D645C;
            item->step++;
        case 1:
            renderRot = constants->second;
            renderPos = constants->first;
            Item_RenderCharacterScaledFromJoint12(item, &renderPos, &renderRot, 1, lbl_806D6430);
            if (FinalLapCoinJump_CheckActiveForObject(work->owner)) item->visible = 0;
            else item->visible = 1;
            switch (work->action) {
            case 1:
                item->visible = 1;
                work->action = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 0);
                Item_InitLaunchFromKart(item, &work->delta, lbl_806D6460, lbl_806D63F8);
                item->subphase++;
                item->step = 0;
                return;
            case 2:
                work->action = 0;
                item->visible = 0; item->phase = 3; item->subphase = 0;
                return;
            }
            Mtx44_GetTranslation_RowMajor(&work->delta, KartDriver_GetJointByIdx(work->owner, 12));
            break;
        }
        break;
    case 2:
        switch (item->step) {
        case 0:
            ItemTracker_AcquireLock(item);
            ItemTracker_SetTrackPhase(item, 1);
            item->tracking = 1;
            item->x3c = 1;
            groundPos = item->pos;
            ItemObject_GetGroundTypeAt(&groundPos, &work->height, 0);
            work->height = item->pos.y - work->height;
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 1, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D6454);
            work->timer = 300;
            work->timer2 = 0;
            item->step++;
        case 1:
            if ((signed char)item->sprite[10] == 1) {
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 2, lbl_806D63F8);
                SpriteSlot_SetScale(item->sprite, lbl_806D6454);
                item->step++;
            }
            break;
        case 2:
            Item_AccelClampVelocity(item, g_ccClass == 0 ? lbl_806D6464 : lbl_806D6468, g_ccClass == 0 ? lbl_806D6430 : lbl_806D6454);
            fn_801B129C(&item->pos);
            break;
        }
        JointByName_GetWorldPosition(&joint, item->sprite, constants->jointName);
        Item_HomingScanAndSteer(item, &item->rotation.y, 0);
        item->rotation.x = Vec3_ToPitch(&item->velocity);
        Item_DecayVelocityScalar(item, lbl_806D6430);
        switch (ItemCollision_Check(item)) {
        case 1: {
            short alias = ItemAlias_HitRemapLookup(item->id);
            fn_801B1D5C(work->owner, ItemTracker_GetTargetKart(item), alias, 0);
            work->target = ItemTracker_GetTargetKart(item);
            ItemHit_Dispatch(item, 0, 0, 0);
            ItemTracker_ReleaseLock(item);
            item->tracking = 0; item->phase = 2; item->subphase = 0; item->reason = 0;
            return;
        }
        case 2:
            fn_801B1660(work->owner, ItemTracker_GetTargetKart(item));
            work->target = ItemTracker_GetTargetKart(item);
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            item->velocity.y = lbl_806D6454;
            item->velocity.x *= lbl_806D6424;
            item->velocity.z *= lbl_806D6424;
            Vec3_Copy(&item->pos, &joint);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D63F8);
            hitPos = item->pos;
            SoundMgr_PlaySE_Positional(0x84, &hitPos, 0);
            item->phase = 2; item->subphase = 0; item->reason = 1;
            return;
        case 3:
            fn_801B158C(work->owner, ItemTracker_GetTargetKart(item));
            work->contact = 0;
            approachVelocity = item->velocity;
            approachPos = item->pos;
            Item_ComputeYawRelativeApproach(&item->velocity, ItemTracker_GetTargetKart(item), &approachPos, &approachVelocity);
            item->rotation.y = Vec3_ToYaw(&item->velocity);
            ItemTracker_SetTrackPhase(item, 0);
            work->timer2 = 5;
            break;
        case 4:
            fn_801B14B8(work->owner, ItemTracker_GetTargetKart(item));
            work->target = ItemTracker_GetTargetKart(item);
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            Vec3_Copy(&item->pos, &joint);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D63F8);
            item->phase = 2; item->subphase = 0; item->reason = 3;
            return;
        case 5: ItemTracker_SetTrackPhase(item, 1); break;
        }
        if (work->timer2 == 0) ItemTracker_SetTrackPhase(item, 1);
        if (item->tracking == 2) {
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            Vec3_Copy(&item->pos, &joint);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D63F8);
            if (item->hit == 1) {
                Vec3_Add_DestFirst(&item->velocity, &item->velocity, &item->impulse);
                item->velocity.y = lbl_806D6454;
                item->velocity.x *= lbl_806D646C;
                item->velocity.z *= lbl_806D646C;
                Item_SpawnHitBurstParticles(item, work, 0, lbl_806D63F8);
                burstPos = item->pos;
                SoundMgr_PlaySE_Positional(0x84, &burstPos, 0);
                item->phase = 2; item->subphase = 0; item->reason = 4;
                return;
            }
            Item_SpawnHitBurstParticles(item, work, 2, lbl_806D63F8);
            item->phase = 2; item->subphase = 0; item->reason = 6;
            return;
        }
        if (Item_CheckWallCollision(item, &wallNormal, &wallPoint)) {
            unsigned char *effect;
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            Vec3_Subtract_DestFirst(&correction, &wallPoint, &item->pos);
            Vec3_Scale(&correction, &item->velocity, (lbl_806D6430 / Vec3_HorizontalMagnitude(&item->velocity)) * (Vec3_HorizontalMagnitude(&correction) - lbl_806D6470));
            Vec3_Add_DestFirst(&item->pos, &joint, &correction);
            GetSpawnPosition(&item->velocity, lbl_806D63F8, lbl_806D63F8, lbl_806D63F8);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D63F8);
            SpriteSlot_SetScale(item->sprite, lbl_806D63F8);
            work->height = Vec3_ToYaw(&wallNormal);
            Item_SpawnHitBurstParticles(item, work, 1, work->height);
            effect = DrawEffect_SpawnDirect(EffectVfx82_FieldItemDropPuff_Tick);
            if (effect != 0) {
                Vec3_Copy((Vec3 *)(effect + 0x8C), &item->pos);
                GetSpawnPosition((Vec3 *)(effect + 0x98), lbl_806D63F8, lbl_806D6450 + work->height, lbl_806D63F8);
            }
            item->phase = 2; item->subphase = 0; item->reason = 7;
            return;
        }
        if (!Item_AdvanceProjectileSimple(item, &work->height, lbl_806D6474, lbl_806D6474) && item->step == 2) {
            ItemTracker_ReleaseLock(item);
            item->tracking = 0; item->phase = 2; item->subphase = 0; item->reason = 9;
            return;
        }
        if (work->timer == 0 && item->step == 2) {
            ItemTracker_ReleaseLock(item);
            item->tracking = 0; item->phase = 2; item->subphase = 0; item->reason = 5;
        }
        break;
    }
}
#pragma exceptions reset

/* === extracted from auto_StarItem_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AngleStepTowards_Shortest();
extern float BuildOrientationFromYaw();
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern void ItemObject_DecrementCategoryBudget();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar(Item *, float);
extern void Item_OrbitAnchorKart();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetTransform();
extern void StarItem_BoundToVictimTick();
extern void StarItem_FallRecoveryTick();
extern void StarItem_FlightAndLockOnTick();
extern void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
extern void Vec3_Subtract_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D63F8;
extern const float lbl_806D6420;
extern const float lbl_806D6424;
extern const float lbl_806D6428;
extern const float lbl_806D642C;
extern const float lbl_806D6430;
extern const float lbl_806D6434;
extern const float lbl_806D6438;
extern const float lbl_806D643C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_80421840[];

/* --- function index (1 fns, .text 0x800FEA94..0x800FEE8C) ---
 * [  0] 0x800FEA94 size:0x3F8   global StarItem_Tick
 */

/* --- forward decls --- */
asm void StarItem_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_StarItem_Tick[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_StarItem_Tick = {
    (void *)&StarItem_Tick, 0x000003F8, (void *)extab_StarItem_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void StarItem_Tick(void) { /* 0x800FEA94 size:0x3F8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    mr r30, r3
    addi r31, r30, 0xec
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq StarItem_Tick_L_800FEB18
    bge StarItem_Tick_L_800FEAD4
    cmpwi r0, 0x0
    beq StarItem_Tick_L_800FEAE0
    bge StarItem_Tick_L_800FEB08
    b StarItem_Tick_L_800FEDD0
    StarItem_Tick_L_800FEAD4:
    cmpwi r0, 0x4
    bge StarItem_Tick_L_800FEDD0
    b StarItem_Tick_L_800FEDC0
    StarItem_Tick_L_800FEAE0:
    addi r3, r30, 0x14
    li r4, 0x54
    bl SpriteSlot_InitNonLoop
    li r0, 0x2
    li r3, 0x0
    stb r0, 0x8c(r30)
    li r0, 0x1
    stb r3, 0x8d(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    StarItem_Tick_L_800FEB08:
    mr r3, r30
    mr r4, r31
    bl StarItem_FlightAndLockOnTick
    b StarItem_Tick_L_800FEDD0
    StarItem_Tick_L_800FEB18:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmplwi r0, 0x9
    bgt StarItem_Tick_L_800FEDD0
    lis r4, jumptable_80421840@ha
    slwi r0, r0, 2
    addi r4, r4, jumptable_80421840@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    mr r4, r31
    bl StarItem_BoundToVictimTick
    b StarItem_Tick_L_800FEDD0
    mr r4, r31
    bl StarItem_FallRecoveryTick
    b StarItem_Tick_L_800FEDD0
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq StarItem_Tick_L_800FEBB0
    bge StarItem_Tick_L_800FEBB0
    cmpwi r0, 0x0
    bge StarItem_Tick_L_800FEB78
    b StarItem_Tick_L_800FEBB0
    StarItem_Tick_L_800FEB78:
    lfs f1, lbl_806D63F8(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f0, lbl_806D63F8(r2)
    stb r0, 0x3c(r30)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    StarItem_Tick_L_800FEBB0:
    lfs f2, lbl_806D643C(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq StarItem_Tick_L_800FEDD0
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b StarItem_Tick_L_800FEDD0
    mr r4, r31
    bl StarItem_FallRecoveryTick
    b StarItem_Tick_L_800FEDD0
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq StarItem_Tick_L_800FEC58
    bge StarItem_Tick_L_800FEC58
    cmpwi r0, 0x0
    bge StarItem_Tick_L_800FEC14
    b StarItem_Tick_L_800FEC58
    StarItem_Tick_L_800FEC14:
    lfs f1, lbl_806D63F8(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    addi r3, r31, 0x34
    stb r0, 0x3c(r30)
    addi r4, r30, 0xa0
    lwz r5, 0x9c(r30)
    addi r5, r5, 0xa0
    bl Vec3_Subtract_DestFirst
    li r0, 0x1e
    stw r0, 0x4(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    StarItem_Tick_L_800FEC58:
    lfs f1, lbl_806D6430(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lwz r5, 0x4(r31)
    mr r3, r30
    lfs f1, lbl_806D6434(r2)
    addi r4, r31, 0x34
    lfs f2, lbl_806D6438(r2)
    bl Item_OrbitAnchorKart
    cmpwi r3, 0x0
    beq StarItem_Tick_L_800FEDD0
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b StarItem_Tick_L_800FEDD0
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq StarItem_Tick_L_800FECE4
    bge StarItem_Tick_L_800FECBC
    cmpwi r0, 0x0
    bge StarItem_Tick_L_800FECC8
    b StarItem_Tick_L_800FED5C
    StarItem_Tick_L_800FECBC:
    cmpwi r0, 0x3
    bge StarItem_Tick_L_800FED5C
    b StarItem_Tick_L_800FED08
    StarItem_Tick_L_800FECC8:
    li r0, 0xa
    lfs f0, lbl_806D63F8(r2)
    stw r0, 0x4(r31)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    StarItem_Tick_L_800FECE4:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne StarItem_Tick_L_800FED5C
    li r0, 0x14
    stw r0, 0x4(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    b StarItem_Tick_L_800FED5C
    StarItem_Tick_L_800FED08:
    lfs f1, 0x18(r31)
    lfs f0, lbl_806D6420(r2)
    fsubs f0, f1, f0
    stfs f0, 0x18(r31)
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne StarItem_Tick_L_800FED5C
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D6424(r2)
    lfs f0, lbl_806D63F8(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge StarItem_Tick_L_800FED5C
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b StarItem_Tick_L_800FEDD0
    StarItem_Tick_L_800FED5C:
    lfs f1, 0xb0(r30)
    lfs f2, 0x14(r31)
    lfs f3, lbl_806D6428(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xb0(r30)
    lfs f1, 0xac(r30)
    lfs f0, 0x18(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    lfs f0, lbl_806D642C(r2)
    lfs f1, 0xac(r30)
    fcmpo cr0, f1, f0
    bge StarItem_Tick_L_800FED98
    stfs f0, 0xac(r30)
    StarItem_Tick_L_800FED98:
    lfs f1, lbl_806D6430(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b StarItem_Tick_L_800FEDD0
    mr r4, r31
    bl StarItem_FallRecoveryTick
    b StarItem_Tick_L_800FEDD0
    mr r4, r31
    bl StarItem_FallRecoveryTick
    b StarItem_Tick_L_800FEDD0
    StarItem_Tick_L_800FEDC0:
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    b StarItem_Tick_L_800FEE74
    StarItem_Tick_L_800FEDD0:
    addi r3, r30, 0xa0
    addi r5, r30, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lwz r6, 0xac(r30)
    addi r3, r30, 0x14
    lwz r0, 0xb0(r30)
    addi r4, r1, 0x14
    addi r5, r1, 0x8
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xb4(r30)
    stw r0, 0x10(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x1c(r1)
    lfs f1, 0xc4(r30)
    bl SpriteSlot_SetTransform
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq StarItem_Tick_L_800FEE38
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    StarItem_Tick_L_800FEE38:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq StarItem_Tick_L_800FEE4C
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    StarItem_Tick_L_800FEE4C:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq StarItem_Tick_L_800FEE60
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    StarItem_Tick_L_800FEE60:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq StarItem_Tick_L_800FEE74
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    StarItem_Tick_L_800FEE74:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

