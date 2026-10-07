/* Tick state dispatch. Local views contain only the observed object fields. */
struct Vec3 { float x, y, z; };
struct GabyouTickContext {
    unsigned char pad00[4];
    unsigned int timer, timer8, timerC, timer10;
    float tetherAngle, tetherStep;
    unsigned char pad1C[0x18];
    Vec3 anchorOffset;
};
struct GabyouTickView {
    unsigned char pad00[0x14];
    unsigned char sprite[0x14];
    unsigned char active;
    unsigned char pad29[3];
    float lifetime;
    unsigned char pad30[0xC];
    unsigned char collisionEnabled;
    unsigned char pad3D[0x4F];
    unsigned char renderMode, renderFlags;
    unsigned char pad8E[0xE];
    GabyouTickView *anchor;
    Vec3 position, rotation, velocity;
    float scale;
    signed char state, phase;
    unsigned char padCA;
    signed char kind;
    unsigned char padCC[0x20];
    GabyouTickContext context;
};
extern "C" {
extern float lbl_806D62C0, lbl_806D62EC, lbl_806D62F0, lbl_806D62F4;
extern float lbl_806D62F8, lbl_806D62FC, lbl_806D6300, lbl_806D6304, lbl_806D6308;
void SpriteSlot_InitNonLoop(void *, int);
void GabyouItem_FlightAndLockOnTick(GabyouTickView *, GabyouTickContext *);
void GabyouItem_ReturnToHandTick(GabyouTickView *, GabyouTickContext *);
void GabyouItem_FallRecoveryTick(GabyouTickView *, GabyouTickContext *);
void GetSpawnPosition(Vec3 *, float, float, float);
void Vec3_Subtract_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
int Item_AdvanceTetherToJoint13(GabyouTickView *, float *, float, float, float);
int Item_OrbitAnchorKart(GabyouTickView *, Vec3 *, unsigned int, float, float);
void Item_DecayVelocityScalar(GabyouTickView *, float);
float AngleStepTowards_Shortest(float, float, float);
void ItemObject_DecrementCategoryBudget(GabyouTickView *);
void SpriteSlot_Container_Free(GabyouTickView *);
void SpriteSlot_SetTransform(void *, Vec3, Vec3, float);

static inline void MarkFinished(GabyouTickView *item) {
    item->active = 0;
    item->state = 3;
    item->phase = 0;
}
static inline bool DecayLifetime(GabyouTickView *item, float decay) {
    float minimum = 0.0f;
    item->lifetime -= decay;
    if (item->lifetime < minimum) return true;
    return false;
}
void GabyouItem_Tick(GabyouTickView *item) {
    GabyouTickContext *context = &item->context;
    switch (item->state) {
    case 0:
        SpriteSlot_InitNonLoop(item->sprite, 0x51);
        item->renderMode = 2;
        item->renderFlags = 0;
        item->state = 1;
        item->phase = 0;
    case 1:
        GabyouItem_FlightAndLockOnTick(item, context);
        break;
    case 2:
        switch (item->kind) {
        case 0: GabyouItem_ReturnToHandTick(item, context); break;
        case 1: GabyouItem_FallRecoveryTick(item, context); break;
        case 3:
            switch (item->phase) {
            case 0:
                GetSpawnPosition(&item->velocity, lbl_806D62C0, lbl_806D62C0, lbl_806D62C0);
                item->collisionEnabled = 0;
                context->tetherAngle = 0.0f;
                context->tetherStep = item->scale;
                ++item->phase;
                break;
            case 1: break;
            }
            if (Item_AdvanceTetherToJoint13(item, &context->tetherAngle, context->tetherStep, lbl_806D6308, lbl_806D6308))
                MarkFinished(item);
            break;
        case 4: GabyouItem_FallRecoveryTick(item, context); break;
        case 6:
            switch (item->phase) {
            case 0:
                GetSpawnPosition(&item->velocity, lbl_806D62C0, lbl_806D62C0, lbl_806D62C0);
                item->collisionEnabled = 0;
                Vec3_Subtract_DestFirst(&context->anchorOffset, &item->position, &item->anchor->position);
                context->timer = 30;
                ++item->phase;
                break;
            case 1: break;
            }
            Item_DecayVelocityScalar(item, lbl_806D6300);
            if (Item_OrbitAnchorKart(item, &context->anchorOffset, context->timer, lbl_806D6304, lbl_806D6304))
                MarkFinished(item);
            break;
        case 7:
            switch (item->phase) {
            case 0:
                context->timer = 10;
                context->tetherStep = 0.34906578f;
                item->collisionEnabled = 0;
                ++item->phase;
                break;
            case 1: break;
            }
            if (context->timer == 0) {
                if (DecayLifetime(item, lbl_806D62F0)) {
                    MarkFinished(item);
                    break;
                }
            }
            context->tetherStep *= lbl_806D62F4;
            item->rotation.x = AngleStepTowards_Shortest(item->rotation.x, 1.570796f, 0.17453289f);
            item->rotation.y = AngleStepTowards_Shortest(item->rotation.y, context->tetherAngle, context->tetherStep);
            Item_DecayVelocityScalar(item, lbl_806D6300);
            break;
        case 8: GabyouItem_FallRecoveryTick(item, context); break;
        case 9: GabyouItem_FallRecoveryTick(item, context); break;
        default: break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(item);
        SpriteSlot_Container_Free(item);
        return;
    }
    Vec3_Add_DestFirst(&item->position, &item->position, &item->velocity);
    SpriteSlot_SetTransform(item->sprite, item->position, item->rotation, item->scale);
    if (context->timer != 0) --context->timer;
    if (context->timer8 != 0) --context->timer8;
    if (context->timerC != 0) --context->timerC;
    if (context->timer10 != 0) --context->timer10;
}
}
