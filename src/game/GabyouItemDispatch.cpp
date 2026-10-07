/* Local ABI views, recovered from the complete dispatch disassembly. */
struct Vec3 { float x, y, z; };
struct Matrix4 { float m[4][4]; };
struct GabyouDispatchView;
struct GabyouDispatchContext {
    unsigned char impactReady;
    unsigned char pad01[3];
    unsigned int timer, timer8, timerC, timer10;
    float tetherAngle, tetherStep;
    unsigned char pad1C[0x18];
    Vec3 anchorOffset;
    unsigned char pad40[0xC];
    GabyouDispatchView *effect;
    unsigned char pad50[0xC];
    GabyouDispatchView *children[2];
};
struct GabyouDispatchView {
    unsigned char pad00[8];
    int type;
    unsigned char pad0C[8];
    unsigned char sprite[0x14];
    signed char active;
    unsigned char pad29[3];
    float lifetime;
    unsigned char pad30[0xC];
    unsigned char collisionEnabled;
    unsigned char pad3D[0xB];
    float matrix[12];
    unsigned char pad78[0x14];
    unsigned char renderMode, renderFlags;
    unsigned char pad8E[0xE];
    GabyouDispatchView *anchor;
    Vec3 position, rotation, velocity;
    float scale;
    signed char state, phase;
    unsigned char padCA;
    signed char kind;
    unsigned char padCC[0x20];
    GabyouDispatchContext context;
};
extern "C" {
extern char lbl_8032EAB0[];
extern unsigned char lbl_805DF3D0[0x98];
extern float lbl_806D5D20, lbl_806D5D24, lbl_806D5D28, lbl_806D5D2C;
extern float lbl_806D5D30, lbl_806D5D50, lbl_806D5D88, lbl_806D5D8C;
void fn_800D748C(GabyouDispatchView *);
GabyouDispatchView *ItemObject_AllocFromPool(void (*)(GabyouDispatchView *));
GabyouDispatchView *DrawEffect_SpawnDirect(void (*)(GabyouDispatchView *));
void Effect_TwoChild_Res3C_3D_Init(GabyouDispatchView *);
void SpriteSlot_InitNonLoop(void *, int);
void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *, int);
void SpriteSlot_Container_Free(GabyouDispatchView *);
void SpriteSlot_SetTransform(void *, Vec3, Vec3, float);
void SpriteSlot_TickAnim(void *);
void SpriteSlot_SetAnimFrameAndApplyScale(void *, signed char, float);
void GabyouItem_Tick_HeldAndHoming_2Eto31(GabyouDispatchView *, GabyouDispatchContext *);
void GabyouItem_OnHitFlush_2Eto31(GabyouDispatchView *, GabyouDispatchContext *);
void GabyouItem_OnImpactTick_2Eto31(GabyouDispatchView *, GabyouDispatchContext *);
void GetSpawnPosition(Vec3 *, float, float, float);
void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
void Vec3_Subtract_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
void Vec3_Copy(Vec3 *, const Vec3 *);
float Vec3_Magnitude_Wrapper(Vec3 *);
void Vec3_Scale(Vec3 *, const Vec3 *, float);
int Item_AdvanceTetherToJoint13(GabyouDispatchView *, float *, float, float, float);
int Item_OrbitAnchorKart(GabyouDispatchView *, Vec3 *, unsigned int, float, float);
void Item_DecayVelocityScalar(GabyouDispatchView *, float);
void ItemObject_DecrementCategoryBudget(GabyouDispatchView *);
void JointByName_GetMatrix4x4Transposed(Matrix4 *, void *, const char *);
void JointByName_GetLocalMatrix4x3(float *, void *, const char *);
void JointByName_GetWorldPosition(Vec3 *, void *, const char *);
void Matrix4_Identity(Matrix4 *);
void Matrix4_PreMultiplyRotY(Matrix4 *, const Matrix4 *, float);
void Matrix4_Multiply(Matrix4 *, const Matrix4 *, const Matrix4 *);
void DbgScene_CopyMatrix3x4Transpose(float *, const Matrix4 *);
void SoundMgr_PlaySE_Positional(int, Vec3, int);
void VfxEffect_UpdateTwoChildSpinAndSound_Helper(GabyouDispatchView *, Vec3, float, float);
void Effect_TwoChildRotate_FromPhase150(GabyouDispatchView *, Vec3, float, float);

static inline void Finish(GabyouDispatchView *item) {
    item->active = 0;
    item->state = 3;
    item->phase = 0;
}

void GabyouItem_Dispatch_2Eto31(GabyouDispatchView *item)
{
    const char *strings = lbl_8032EAB0;
    unsigned int ones, tens;
    int childIndex;
    GabyouDispatchContext *context = &item->context;
    Matrix4 jointMatrix, rotationMatrix;
    Vec3 effectPosition, cameraEffectPosition, cameraOffset;
    switch (item->state) {
    case 0:
        switch (item->type) {
        case 0x2E: SpriteSlot_InitNonLoop(item->sprite, 0x30); break;
        case 0x2F: SpriteSlot_InitNonLoop(item->sprite, 0x32); break;
        case 0x30: SpriteSlot_InitNonLoop(item->sprite, 0x34); break;
        case 0x31: SpriteSlot_InitNonLoop(item->sprite, 0x36); break;
        }
        item->sprite[0] = 4;
        switch (item->type) {
        case 0x2E:
        case 0x2F:
            for (int i = 0; i < 2; ++i) {
                context->children[i] = ItemObject_AllocFromPool(fn_800D748C);
                if (context->children[i]) {
                    SpriteSlot_InitNonLoop(context->children[i]->sprite, 0x31);
                    SpriteSlot_SetMatrixSourceEnabled_WithReseed(context->children[i]->sprite, 1);
                    context->children[i]->sprite[0] = 4;
                }
            }
            break;
        case 0x30:
            context->children[0] = ItemObject_AllocFromPool(fn_800D748C);
            if (context->children[0]) {
                SpriteSlot_InitNonLoop(context->children[0]->sprite, 0x35);
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(context->children[0]->sprite, 1);
                context->children[0]->sprite[0] = 4;
            }
            break;
        case 0x31:
            context->effect = DrawEffect_SpawnDirect(Effect_TwoChild_Res3C_3D_Init);
            if (context->effect) Effect_TwoChild_Res3C_3D_Init(context->effect);
            break;
        }
        item->renderMode = 3;
        item->renderFlags = 0;
        item->state = 1;
        item->phase = 0;
    case 1:
        GabyouItem_Tick_HeldAndHoming_2Eto31(item, context);
        break;
    case 2:
        switch (item->kind) {
        case 1: GabyouItem_OnHitFlush_2Eto31(item, context); break;
        case 3:
            switch (item->phase) {
            case 0:
                GetSpawnPosition(&item->velocity, lbl_806D5D20, lbl_806D5D20, lbl_806D5D20);
                item->collisionEnabled = 0;
                context->tetherAngle = 0.0f;
                context->tetherStep = item->scale;
                ++item->phase;
                break;
            case 1: break;
            }
            if (Item_AdvanceTetherToJoint13(item, &context->tetherAngle, context->tetherStep, lbl_806D5D30, lbl_806D5D30))
                Finish(item);
            break;
        case 4: GabyouItem_OnHitFlush_2Eto31(item, context); break;
        case 6:
            switch (item->phase) {
            case 0:
                GetSpawnPosition(&item->velocity, lbl_806D5D20, lbl_806D5D20, lbl_806D5D20);
                item->collisionEnabled = 0;
                Vec3_Subtract_DestFirst(&context->anchorOffset, &item->position, &item->anchor->position);
                context->timer = 30;
                ++item->phase;
                break;
            case 1: break;
            }
            Item_DecayVelocityScalar(item, lbl_806D5D24);
            if (Item_OrbitAnchorKart(item, &context->anchorOffset, context->timer, lbl_806D5D28, lbl_806D5D28)) {
                Finish(item);
                break;
            }
            switch (item->type) {
            case 0x2E: Item_DecayVelocityScalar(item, lbl_806D5D24); break;
            case 0x2F: Item_DecayVelocityScalar(item, lbl_806D5D24); break;
            case 0x30: Item_DecayVelocityScalar(item, lbl_806D5D2C); break;
            case 0x31: Item_DecayVelocityScalar(item, lbl_806D5D2C); break;
            }
            break;
        case 7: GabyouItem_OnHitFlush_2Eto31(item, context); break;
        case 9: GabyouItem_OnImpactTick_2Eto31(item, context); break;
        case 5: GabyouItem_OnImpactTick_2Eto31(item, context); break;
        case 0:
            if (!context->impactReady) GabyouItem_OnHitFlush_2Eto31(item, context);
            else if (item->type == 0x2E || item->type == 0x2F)
                GabyouItem_OnImpactTick_2Eto31(item, context);
            else GabyouItem_OnHitFlush_2Eto31(item, context);
            break;
        case 2: break;
        case 8: break;
        }
        break;
    case 3:
        switch (item->type) {
        case 0x2E:
        case 0x2F:
            SpriteSlot_Container_Free(context->children[0]);
            SpriteSlot_Container_Free(context->children[1]);
            context->children[0] = 0;
            context->children[1] = 0;
            if (context->effect) context->effect->phase = 1;
            context->effect = 0;
            break;
        case 0x30:
            SpriteSlot_Container_Free(context->children[0]);
            context->children[0] = 0;
            break;
        case 0x31:
            if (context->effect) context->effect->phase = 1;
            context->effect = 0;
            break;
        }
        ItemObject_DecrementCategoryBudget(item);
        SpriteSlot_Container_Free(item);
        return;
    }
    Vec3_Add_DestFirst(&item->position, &item->position, &item->velocity);
    SpriteSlot_SetTransform(item->sprite, item->position, item->rotation, item->scale);
    SpriteSlot_TickAnim(item->sprite);
    switch (item->type) {
    case 0x2E:
    case 0x2F: {
        unsigned int seconds = context->timer / 60;
        if (context->timer != 0) ++seconds;
        ones = seconds % 10;
        tens = seconds / 10;
        for (childIndex = 0; childIndex < 2; ++childIndex) {
            int i = childIndex;
            if (context->children[i]) {
                if (item->type == 0x2E) {
                    if (i == 0) JointByName_GetMatrix4x4Transposed(&jointMatrix, item->sprite, strings + 0x480);
                    else JointByName_GetMatrix4x4Transposed(&jointMatrix, item->sprite, strings + 0x49C);
                } else {
                    if (i == 0) JointByName_GetMatrix4x4Transposed(&jointMatrix, item->sprite, strings + 0x4B8);
                    else JointByName_GetMatrix4x4Transposed(&jointMatrix, item->sprite, strings + 0x4D0);
                }
                Matrix4_Identity(&rotationMatrix);
                Matrix4_PreMultiplyRotY(&rotationMatrix, &rotationMatrix, lbl_806D5D88);
                Matrix4_Multiply(&jointMatrix, &rotationMatrix, &jointMatrix);
                DbgScene_CopyMatrix3x4Transpose(context->children[i]->matrix, &jointMatrix);
                unsigned int digit = ones;
                if (i != 0) digit = tens;
                if ((unsigned int)(signed char)context->children[i]->sprite[9] != digit) {
                    SpriteSlot_SetAnimFrameAndApplyScale(context->children[i]->sprite, (signed char)digit, lbl_806D5D20);
                    if (i == 0) SoundMgr_PlaySE_Positional(0x97, item->position, 0);
                }
                Vec3_Copy(&context->children[i]->position, &item->position);
                context->children[i]->scale = item->scale;
                context->children[i]->lifetime = item->lifetime;
                context->children[i]->active = item->active;
                SpriteSlot_TickAnim(context->children[i]->sprite);
            }
        }
        if (context->effect) {
            if (item->type == 0x2E) JointByName_GetWorldPosition(&effectPosition, item->sprite, strings + 0x4E8);
            else JointByName_GetWorldPosition(&effectPosition, item->sprite, strings + 0x500);
            if (item->active) VfxEffect_UpdateTwoChildSpinAndSound_Helper(context->effect, effectPosition, item->scale, item->lifetime);
            else VfxEffect_UpdateTwoChildSpinAndSound_Helper(context->effect, effectPosition, item->scale, lbl_806D5D20);
        }
        break;
    }
    case 0x30:
        if (context->children[0]) {
            JointByName_GetLocalMatrix4x3(context->children[0]->matrix, item->sprite, strings + 0x514);
            Vec3_Copy(&context->children[0]->position, &item->position);
            context->children[0]->scale = item->scale;
            context->children[0]->lifetime = item->lifetime;
            context->children[0]->active = item->active;
            SpriteSlot_TickAnim(context->children[0]->sprite);
        }
        break;
    case 0x31:
        if (context->effect) {
            JointByName_GetWorldPosition(&cameraEffectPosition, item->sprite, strings + 0x528);
            Vec3_Subtract_DestFirst(&cameraOffset, &cameraEffectPosition, (Vec3 *)(lbl_805DF3D0 + 0x80));
            float magnitude = Vec3_Magnitude_Wrapper(&cameraOffset);
            magnitude = lbl_806D5D24 / magnitude;
            magnitude = lbl_806D5D50 * magnitude;
            magnitude = item->scale * magnitude;
            Vec3_Scale(&cameraOffset, &cameraOffset, magnitude);
            Vec3_Add_DestFirst(&cameraEffectPosition, &cameraEffectPosition, &cameraOffset);
            if (item->active) Effect_TwoChildRotate_FromPhase150(context->effect, cameraEffectPosition, lbl_806D5D8C * item->scale, item->lifetime);
            else Effect_TwoChildRotate_FromPhase150(context->effect, cameraEffectPosition, lbl_806D5D8C * item->scale, lbl_806D5D20);
        }
        break;
    }
    if (context->timer) --context->timer;
    if (context->timer8) --context->timer8;
    if (context->timerC) --context->timerC;
    if (context->timer10) --context->timer10;
}
}
