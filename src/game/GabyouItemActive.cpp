/* Active held/flight/ground state, 0x800F2D60..0x800F33DC.
 * Reconstructed from the complete target and actual callee disassembly.
 * Ghidra was unavailable. Views are local and describe observed fields only.
 */
struct Vec3 { float x, y, z; };
struct GabyouActiveView {
    unsigned char pad00[8];
    int alias;
    unsigned char pad0C[8];
    unsigned char sprite[0x14];
    unsigned char active;
    unsigned char pad29[3];
    float lifetime;
    unsigned char pad30[0xC];
    unsigned char collisionEnabled;
    unsigned char pad3D[0x4F];
    unsigned char renderMode, renderFlags;
    unsigned char pad8E[2];
    Vec3 collisionImpulse;
    unsigned char pad9C[4];
    Vec3 position, rotation, velocity;
    float scale;
    unsigned char state;
    signed char phase, flightPhase;
    unsigned char recoveryKind;
};
struct GabyouActiveContext {
    unsigned char launched;
    unsigned char pad01[3];
    unsigned int timer, pauseTimer;
    unsigned char pad0C[0x70];
    unsigned int approachCounter;
    unsigned char pad80[0x18];
    void *ownerKart;
    void *hitKart;
    signed char request;
};
extern "C" {
extern float lbl_806D6088, lbl_806D608C, lbl_806D6094, lbl_806D6098;
extern float lbl_806D609C, lbl_806D60A0, lbl_806D60A4, lbl_806D60A8, lbl_806D60AC;
extern const char lbl_8032F994[], lbl_8032F9AC[];
void GabyouItem_BuildLocalTransformFromHandJoint(GabyouActiveView *, int, float, float, float);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
void Item_InitLaunchFromKart(GabyouActiveView *, const Vec3 *, float, float);
void ItemTracker_AcquireLock(GabyouActiveView *);
void ItemTracker_SetTrackPhase(GabyouActiveView *, int);
void ItemTracker_ReleaseLock(GabyouActiveView *);
void *ItemTracker_GetTargetKart(GabyouActiveView *);
int ItemHitRegistry_AddEntry(GabyouActiveView *);
unsigned char ItemHitRegistry_RemoveEntry(GabyouActiveView *, unsigned int, int *);
void Item_HomingScanAndSteer(GabyouActiveView *, float *, int);
int JointByName_GetWorldPosition(Vec3 *, void *, const char *);
void Item_DecayVelocityScalar(GabyouActiveView *, float);
int ItemCollision_Check(GabyouActiveView *);
short ItemAlias_HitRemapLookup(int);
void fn_801B1D5C(void *, void *, int, int);
void fn_801B1660(void *, void *);
void fn_801B158C(void *, void *);
void fn_801B14B8(void *, void *);
void Item_ComputeYawRelativeApproach(Vec3 *, void *, Vec3, Vec3);
float Vec3_ToYaw(const Vec3 *);
void ItemHit_Dispatch(GabyouActiveView *, void *, int, int);
void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
int Item_CheckWallCollision(GabyouActiveView *, Vec3 *, Vec3 *);
void Item_BounceOffWall(GabyouActiveView *, Vec3, unsigned int, signed char, float, float);
int Item_AdvanceFallingDrop(GabyouActiveView *, int *, float *, float);
void DrawEffect_ItemHitBurst_Spawn(Vec3, Vec3, signed char);
void SoundMgr_PlaySE_Positional(unsigned int, Vec3, int);
void GetSpawnPosition(Vec3 *, float, float, float);
float Item_ProbeForwardGroundPitch(Vec3, float, float, float);
float Item_ProbeLateralGroundPitch(Vec3, float, float, float);
float AngleStepTowards_Shortest(float, float, float);
void ItemObject_DecrementCategoryBudget(GabyouActiveView *);
void SpriteSlot_Container_Free(GabyouActiveView *);

void GabyouItem_TickActive(GabyouActiveView *item, GabyouActiveContext *context)
{
    Vec3 jointPosition;
    Vec3 wallNormal;
    int landed;
    float groundHeight;
    int collision;
    float groundPitch;
    float lateralPitch;
    switch (item->phase) {
    case 0:
        ++item->phase;
        item->flightPhase = 0;
        /* Initialization continues through the holding state. */
    case 1:
        switch (item->flightPhase) {
        case 0:
            context->launched = 0;
            item->active = 1;
            item->lifetime = 0.0f;
            ++item->flightPhase;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(item, 1,
                lbl_806D6088, lbl_806D609C, lbl_806D60A0);
            if (FinalLapCoinJump_CheckActiveForObject(context->ownerKart))
                item->active = 0;
            else
                item->active = 1;
            switch (context->request) {
            case 1:
                item->active = 1;
                context->request = 0;
                context->launched = 1;
                Item_InitLaunchFromKart(item, 0, 1.0f, 0.0f);
                ++item->phase;
                item->flightPhase = 0;
                break;
            case 2:
                context->request = 0;
                item->active = 0;
                item->state = 3;
                item->phase = 0;
                break;
            }
            break;
        }
        break;
    case 2:
        switch (item->flightPhase) {
        case 0:
            ItemTracker_AcquireLock(item);
            ItemTracker_SetTrackPhase(item, 1);
            item->renderFlags = 1;
            item->collisionEnabled = 1;
            context->timer = 900;
            context->pauseTimer = 0;
            ++item->flightPhase;
            ItemHitRegistry_AddEntry(item);
        case 1:
            Item_HomingScanAndSteer(item, &item->rotation.y, 1);
            break;
        case 2:
            break;
        default:
            break;
        }
        if (item->alias == 0x43)
            JointByName_GetWorldPosition(&jointPosition, item->sprite, lbl_8032F994);
        else
            JointByName_GetWorldPosition(&jointPosition, item->sprite, lbl_8032F9AC);
        item->velocity.y += lbl_806D6098;
        Item_DecayVelocityScalar(item, 3.0f);
        collision = ItemCollision_Check(item);
        switch (collision) {
        case 1: {
            int hitAlias = ItemAlias_HitRemapLookup(item->alias);
            fn_801B1D5C(context->ownerKart, ItemTracker_GetTargetKart(item), hitAlias, 0);
        }
        case 2:
            if (collision == 2)
                fn_801B1660(context->ownerKart, ItemTracker_GetTargetKart(item));
        case 3:
            if (collision == 3)
                fn_801B158C(context->ownerKart, ItemTracker_GetTargetKart(item));
            if ((int)(unsigned char)item->flightPhase == 1 && collision == 3) {
                context->approachCounter = 0;
                Item_ComputeYawRelativeApproach(&item->velocity,
                    ItemTracker_GetTargetKart(item), item->position, item->velocity);
                item->rotation.y = Vec3_ToYaw(&item->velocity);
                ItemTracker_SetTrackPhase(item, 0);
                context->pauseTimer = 5;
                break;
            } else {
                if (collision == 1)
                    ItemHit_Dispatch(item, 0, 0, 0);
                context->hitKart = ItemTracker_GetTargetKart(item);
                ItemTracker_ReleaseLock(item);
                item->renderFlags = 0;
                item->state = 2;
                item->phase = 0;
                item->recoveryKind = 0;
                return;
            }
        case 4:
            fn_801B14B8(context->ownerKart, ItemTracker_GetTargetKart(item));
            context->hitKart = ItemTracker_GetTargetKart(item);
            ItemTracker_ReleaseLock(item);
            item->renderFlags = 0;
            item->state = 2;
            item->phase = 0;
            item->recoveryKind = 3;
            return;
        case 5:
            ItemTracker_SetTrackPhase(item, 1);
            break;
        }
        if (context->pauseTimer == 0)
            ItemTracker_SetTrackPhase(item, 1);
        if ((int)item->renderFlags == 2) {
            ItemTracker_ReleaseLock(item);
            item->renderFlags = 0;
            Vec3_Add_DestFirst(&item->velocity, &item->velocity, &item->collisionImpulse);
            item->velocity.y = 2.0f;
            item->velocity.x *= 0.2f;
            item->velocity.z *= 0.2f;
            item->state = 2;
            item->phase = 0;
            item->recoveryKind = 4;
            return;
        }
        if (Item_CheckWallCollision(item, &wallNormal, 0))
            Item_BounceOffWall(item, wallNormal, 0xAA, 3, lbl_806D60A8, lbl_806D6088);
        if (Item_AdvanceFallingDrop(item, &landed, &groundHeight, lbl_806D6088)) {
            if (landed) {
                if ((int)(unsigned char)item->flightPhase == 1) {
                    DrawEffect_ItemHitBurst_Spawn(item->position, item->velocity, 3);
                    SoundMgr_PlaySE_Positional(0xAA, item->position, 0);
                    item->flightPhase = 2;
                }
                GetSpawnPosition(&item->velocity, lbl_806D6088, lbl_806D6088, lbl_806D6088);
                groundPitch = Item_ProbeForwardGroundPitch(item->position, item->rotation.y, lbl_806D60AC, lbl_806D6088);
                item->rotation.x = AngleStepTowards_Shortest(item->rotation.x, groundPitch, lbl_806D608C);
                lateralPitch = Item_ProbeLateralGroundPitch(item->position, item->rotation.y, 5.0f, lbl_806D6088);
                item->rotation.z = AngleStepTowards_Shortest(item->rotation.z, lateralPitch, lbl_806D608C);
            }
        } else {
            ItemTracker_ReleaseLock(item);
            item->renderFlags = 0;
            item->state = 2;
            item->phase = 0;
            item->recoveryKind = 9;
            return;
        }
        if (ItemHitRegistry_RemoveEntry(item, context->timer, 0)) {
            ItemTracker_ReleaseLock(item);
            item->renderFlags = 0;
            ItemObject_DecrementCategoryBudget(item);
            SpriteSlot_Container_Free(item);
        }
        break;
    }
}
}
