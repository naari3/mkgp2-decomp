/* Native draft for 0x800426C8..0x80044498 (7632 bytes).
 * Primary text: 99.971176%; retained as NonMatching.
 * Nine FP scratch-register operands remain in the overlay projection.
 * Owned EH bytes are exact; compiler weak-dtor entries are additional.
 */
#include "game/RenderObj_ItemStateMachinePrivate.h"

extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int, float);
void C_MTXTrans(Mtx, float, float, float);
void C_MTXConcat(const Mtx, const Mtx, Mtx);
void PSMTXCopy(const Mtx, Mtx);
void Object_DriveAnimMatrix(void *);
void Object_DriveAnimAndSkin(void *, float, float, void *);
HSD_JObj *Archive_GetRootJObj(void *);
void ObjectTree_BlendOrCopy_Timed(void *, HSD_JObj *, HSD_JObj *, HSD_JObj *, float);
void *GetCharacterDataEntry(int);
void clNormal3D_Exec(void *);
void Object_SetAnimBinding(void *, const Mtx, int);
void Object_BindMatrixSource(void *, const Mtx, int);
void HSD_JObjSetupMatrixSub(HSD_JObj *);
void HSD_JObjSetMtxDirtySub(HSD_JObj *);
void __assert(const char *, int, const char *);
void JObj_Hide(void *, HSD_JObj *, int);
void JObj_Show(void *, HSD_JObj *, int);
float LUT_Sin12Bit(float);
void KartTireFX_AddSpinBoth(void *, float);
void KartDriver_SetEulerY_4Joints_LastMirrored(RenderItemState *, float);
void *GetItemDataEntry(int);
void ItemEffectMgr_TickPickLowestTimer(void *);
int *ItemEffectMgr_GetPickedSlot(void *);
void fn_80173B68(void *, int);
void fn_80173C34(void *);
void fn_80173BE8(void *);
void RenderObj_CleanupItem(RenderItemState *, int);
void ItemHandler_Star(RenderItemState *, int);
void ItemHandler_Shell(RenderItemState *);
void KartItem_TickTrailingFx(RenderItemState *);
void KartItem_TickStunStateMachine(RenderItemState *);
void KartItem_TickEffectStage_a(RenderItemState *);
void KartItem_TickEffectStage_b(RenderItemState *);
unsigned char ISESlot_IsActive(void *);
void ISESlot_FrameUpdate(void *);
float Object_GetField8(void *);
float Vec3_Magnitude(const Vec3f *);
void Object_SetField8_10_14(void *, float, float, float);
void AnimState_UpdateEquipped(RenderItemState *);
void fn_80231D50(void *);
float (*Object_GetJObjLocalMatrix(void *))[4];
void *GetCourseScene3D(void);
float (*CObj_GetViewMatrix_Cached(void *))[4];
void Vec3_Normalize(Vec3f *, Vec3f *);
float Vec3_Dot(const Vec3f *, const Vec3f *);
void fn_80245704(void *);
void fn_8024F618(void *);
void fn_80250984(void *);
extern unsigned char g_finalLapCoinJumpEnabled;
extern const char lbl_806D2548[8], lbl_806D2550[5], KartDriver_InitFull_rodata_802EADBC[];
extern float lbl_806CF018;
extern const float lbl_806D2540, lbl_806D256C, lbl_806D2570;
extern const float lbl_806D2574, lbl_806D257C, lbl_806D2590;
extern const float lbl_806D25B8, lbl_806D25CC, lbl_806D25E0;
extern const float lbl_806D25F0, lbl_806D25F4, lbl_806D25F8, lbl_806D25FC;
extern const float lbl_806D2600, lbl_806D2604, lbl_806D2608, lbl_806D260C;
extern const float lbl_806D2610, lbl_806D2614, lbl_806D2618;
extern const double lbl_806D2620;
extern const float lbl_806D2628, lbl_806D262C, lbl_806D2630;
extern const float lbl_806D2634, lbl_806D2638;
}

#include "game/types/ScopedTimer.h"

static inline unsigned char MatrixDirty(HSD_JObj *joint) {
    unsigned int flags;
    unsigned char dirty;
    if (!joint) __assert(lbl_806D2548, 0x25D, lbl_806D2550);
    flags = joint->flags;
    dirty = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) dirty = 1;
    return dirty;
}
static inline float (*JointMatrix(HSD_JObj *joint))[4] {
    if (!joint) __assert(lbl_806D2548, 0x47C, lbl_806D2550);
    if (joint && MatrixDirty(joint)) HSD_JObjSetupMatrixSub(joint);
    return (float (*)[4])((char *)joint + 0x44);
}
static inline void SetJointY(HSD_JObj *joint, float value) {
    if (!joint) __assert(lbl_806D2548, 0x3C6, lbl_806D2550);
    *(float *)((char *)joint + 0x3C) = value;
    if (!(joint->flags & 0x02000000) && joint && !MatrixDirty(joint))
        HSD_JObjSetMtxDirtySub(joint);
}

/* Keep the root lookups sequenced: each lookup can update the archive. */
#define COPY_PRIMARY(source) { \
    ObjectTree_BlendOrCopy_Timed(obj->output, Archive_GetRootJObj(source), \
        Archive_GetRootJObj(obj->output), 0, lbl_806D2540); \
}
#define BLEND_SECONDARY(weight) { \
    ObjectTree_BlendOrCopy_Timed(obj->output, Archive_GetRootJObj(obj->secondary), \
        Archive_GetRootJObj(obj->primary), Archive_GetRootJObj(obj->output), weight); \
}
#define BLEND_OR_COPY(index, weight) \
    if (obj->hasSecondary) { \
        Object_DriveAnimAndSkin(obj->secondary, lbl_806D256C, lbl_806D2540, obj->animations[index]); \
        BLEND_SECONDARY(weight); \
    } else { COPY_PRIMARY(obj->primary); }

extern "C" int RenderObj_ItemStateMachine(RenderItemState *obj, int arg, float steering, float spin) {
    float neutralFrame;
    if (!obj->root || !obj->output) return 0;
    if (obj->active == 0) return 0;
    if (obj->active > 0) --obj->active;
    if (obj->field2b2 == 1) {
        obj->field2b2 = 0;
        obj->field2b1 = 0;
    }
    RenderVisibility *visibility = obj->visibility;
    visibility->a = 0;
    visibility->b = 0;
    C_MTXTrans(obj->matrix, lbl_806D2540, lbl_806D2540, lbl_806D2540);
    C_MTXConcat(obj->worldMatrix, obj->matrix, obj->matrix);
    Object_DriveAnimMatrix(obj->root);
    if (obj->steering > steering) {
        if ((obj->steering -= lbl_806CF018) < steering) obj->steering = steering;
    } else {
        if ((obj->steering += lbl_806CF018) > steering) obj->steering = steering;
    }
    obj->steering = steering;
    if (obj->smoothSteering > steering) {
        if ((obj->smoothSteering -= lbl_806CF018) < steering) obj->smoothSteering = steering;
    } else {
        if ((obj->smoothSteering += lbl_806CF018) > steering) obj->smoothSteering = steering;
    }
    if (lbl_806D25F0 < obj->smoothSteering && obj->smoothSteering < lbl_806D25F4) {
        if (obj->turnBlend < lbl_806D2540) {
            if ((obj->turnBlend += lbl_806D25F8) > lbl_806D2540) obj->turnBlend = lbl_806D2540;
        } else if (obj->turnBlend > lbl_806D2540) {
            if ((obj->turnBlend -= lbl_806D25F8) < lbl_806D2540) obj->turnBlend = lbl_806D2540;
        }
    } else if (obj->smoothSteering < lbl_806D2540) {
        float limit = -1.0f;
        float value = obj->turnBlend - lbl_806D25F8;
        obj->turnBlend = value;
        if (value < limit) obj->turnBlend = -1.0f;
    } else {
        float limit = 1.0f;
        float value = obj->turnBlend + lbl_806D25F8;
        obj->turnBlend = value;
        if (value > limit) obj->turnBlend = 1.0f;
    }
    neutralFrame = lbl_806D2574 * (lbl_806D257C - (lbl_806D2570 + obj->turnBlend));
    if (!obj->freezeAnim) {
        if (obj->state == 42 || obj->state == 43) {
            void *anim = obj->animations[obj->state];
            ScopedTimer timer(24);
            Object_DriveAnimAndSkin(obj->primary, obj->frame, lbl_806D2540, anim);
            COPY_PRIMARY(obj->primary);
            float end;
            if (obj->state == 42) end = *(float *)((char *)GetCharacterDataEntry(obj->character) + 0x1C);
            else end = *(float *)((char *)GetCharacterDataEntry(obj->character) + 0x24);
            if ((obj->frame += obj->frameStep) >= end) obj->frame = lbl_806D2540;
        } else if (obj->state == 1) {
            ScopedTimer timer(24);
            Object_DriveAnimAndSkin(obj->primary, neutralFrame, lbl_806D2540, obj->animations[obj->animIndex]);
            BLEND_OR_COPY(0, obj->returnBlend);
            if ((obj->returnBlend += obj->returnBlendStep) >= lbl_806D2570) { obj->state = 0; obj->stateDone = 1; }
        } else if (obj->state != 0) {
            if (obj->state != -1 && obj->frame < obj->frameEnd) {
                ScopedTimer timer(24);
                Object_DriveAnimAndSkin(obj->primary, obj->frame, lbl_806D2540, obj->animations[obj->state]);
                obj->frame += obj->frameStep;
                if (obj->stateBlend < lbl_806D2570) {
                    ScopedTimer blendTimer(24);
                    BLEND_OR_COPY(obj->previousState, obj->stateBlend);
                    obj->stateBlend += obj->blendStep;
                } else {
                    ScopedTimer copyTimer(24);
                    clNormal3D_Exec(obj->animations[obj->state]);
                    Object_DriveAnimAndSkin(obj->secondary, obj->frame, lbl_806D2540, obj->animations[obj->state]);
                    COPY_PRIMARY(obj->secondary);
                }
            } else {
                ScopedTimer timer(24);
                Object_DriveAnimAndSkin(obj->primary, neutralFrame, lbl_806D2540, obj->animations[obj->turnBank + obj->animIndex]);
                BLEND_OR_COPY(obj->state, obj->returnBlend);
                obj->returnBlend += obj->returnBlendStep;
                if (obj->returnBlend >= lbl_806D2570) { obj->state = 0; obj->stateDone = 1; }
            }
        } else {
            /* Separate lexical scopes preserve each bank's automatic timers. */
            if (-0.26f < obj->turnBlend && obj->turnBlend < 0.26f && -0.26f < steering && steering < 0.26f) {
                obj->turnBank = 5;
                if ((obj->frame += obj->idleFrameStep) > lbl_806D25CC) obj->frame = lbl_806D2540;
                ScopedTimer timer(24);
                Object_DriveAnimAndSkin(obj->primary, obj->frame, lbl_806D2540, obj->animations[5 + obj->animIndex]);
                if (obj->turnTransition < lbl_806D2570) {
                    ScopedTimer blendTimer(24);
                    BLEND_OR_COPY(obj->animIndex, obj->turnTransition);
                    float limit = 1.0f;
                    float value = obj->turnTransition + lbl_806D25B8;
                    obj->turnTransition = value;
                    if (value >= limit) obj->turnTransition = 1.0f;
                } else {
                    ScopedTimer copyTimer(24);
                    COPY_PRIMARY(obj->primary);
                }
            }
            else if (lbl_806D25FC < obj->turnBlend) {
                obj->turnBank = 10;
                if ((obj->frame += obj->idleFrameStep) > lbl_806D25CC) obj->frame = lbl_806D2540;
                ScopedTimer timer(24);
                Object_DriveAnimAndSkin(obj->primary, obj->frame, lbl_806D2540, obj->animations[10 + obj->animIndex]);
                if (obj->turnTransition < lbl_806D2570) {
                    ScopedTimer blendTimer(24);
                    BLEND_OR_COPY(obj->animIndex, obj->turnTransition);
                    float limit = 1.0f;
                    float value = obj->turnTransition + lbl_806D25B8;
                    obj->turnTransition = value;
                    if (value >= limit) obj->turnTransition = 1.0f;
                } else {
                    ScopedTimer copyTimer(24);
                    COPY_PRIMARY(obj->primary);
                }
            }
            else if (obj->turnBlend < lbl_806D2600) {
                obj->turnBank = 15;
                if ((obj->frame += obj->idleFrameStep) > lbl_806D25CC) obj->frame = lbl_806D2540;
                ScopedTimer timer(24);
                Object_DriveAnimAndSkin(obj->primary, obj->frame, lbl_806D2540, obj->animations[15 + obj->animIndex]);
                if (obj->turnTransition < lbl_806D2570) {
                    ScopedTimer blendTimer(24);
                    BLEND_OR_COPY(obj->animIndex, obj->turnTransition);
                    float limit = 1.0f;
                    float value = obj->turnTransition + lbl_806D25B8;
                    obj->turnTransition = value;
                    if (value >= limit) obj->turnTransition = 1.0f;
                } else {
                    ScopedTimer copyTimer(24);
                    COPY_PRIMARY(obj->primary);
                }
            }
            else {
                ScopedTimer timer(24);
                Object_DriveAnimAndSkin(obj->primary, neutralFrame, lbl_806D2540, obj->animations[obj->animIndex]);
                if (obj->turnTransition > lbl_806D2540) {
                    ScopedTimer blendTimer(24);
                    BLEND_OR_COPY(obj->turnBank + obj->animIndex, lbl_806D2570 - obj->turnTransition);
                    float limit = 0.0f;
                    float value = obj->turnTransition - lbl_806D25B8;
                    obj->turnTransition = value;
                    if (value <= limit) {
                        obj->turnTransition = 0.0f;
                        obj->turnBank = 0;
                    }
                } else {
                    ScopedTimer copyTimer(24);
                    COPY_PRIMARY(obj->primary);
                }
            }
        }
    }
    if (obj->bindingJoint) {
        const float (*matrix)[4];
        if (!obj->bindingJoint) matrix = 0;
        else matrix = JointMatrix(obj->bindingJoint);
        Object_SetAnimBinding(obj->output, matrix, 0);
    }
    Object_DriveAnimMatrix(obj->output);
    if (obj->lastFace != obj->face) {
        if (obj->face == 2) {
            if (obj->face0) JObj_Hide(obj->output, obj->face0, 16);
            if (obj->face1) JObj_Hide(obj->output, obj->face1, 16);
            if (obj->face2) JObj_Show(obj->output, obj->face2, 16);
        }
        else if (obj->face == 1) {
            if (obj->face0) JObj_Hide(obj->output, obj->face0, 16);
            if (obj->face1) JObj_Show(obj->output, obj->face1, 16);
            if (obj->face2) JObj_Hide(obj->output, obj->face2, 16);
        }
        else {
            if (obj->face0) JObj_Show(obj->output, obj->face0, 16);
            if (obj->face1) JObj_Hide(obj->output, obj->face1, 16);
            if (obj->face2) JObj_Hide(obj->output, obj->face2, 16);
        }
        obj->lastFace = obj->face;
    }
    if (obj->state != 42 && obj->state != 43 && obj->animIndex == 0) obj->face = 0;
    obj->swayPhase += lbl_806D2604;
    float swayY = obj->sway * LUT_Sin12Bit(obj->swayPhase);
    swayY = lbl_806D2608 * swayY;
    steering = swayY + obj->leftY;
    SetJointY(obj->leftJoint, steering);
    swayY = obj->sway * LUT_Sin12Bit(obj->swayPhase);
    swayY = lbl_806D260C * swayY;
    steering = swayY + obj->rightY;
    SetJointY(obj->rightJoint, steering);
    if (obj->root && obj->output && obj->tireFx) KartTireFX_AddSpinBoth(obj->tireFx, spin);
    KartDriver_SetEulerY_4Joints_LastMirrored(obj, lbl_806D2610 * obj->steering);
    void *itemData;
    if (obj->item >= 0x115) itemData = 0;
    else itemData = GetItemDataEntry(obj->item);
    signed char itemType = *((signed char *)itemData + 8);
    if (obj->item == 0x6C) itemType = 6;
    else if (obj->item == 0x6D) itemType = 6;
    else if (obj->item == 0x6E) itemType = 6;
    if (obj->itemEffects) ItemEffectMgr_TickPickLowestTimer(obj->itemEffects);
    if (obj->item >= 0 && itemType == 6 && obj->itemEffects) {
        if (!ItemEffectMgr_GetPickedSlot(obj->itemEffects)) {
            fn_80173B68(obj->itemDisplay, 0);
            fn_80173C34(obj->itemDisplay);
        } else if (ItemEffectMgr_GetPickedSlot(obj->itemEffects)[3] <= 1) {
            int id = ItemEffectMgr_GetPickedSlot(obj->itemEffects)[0];
            if ((unsigned int)id == 0xFFFFFFFFU) {
                fn_80173B68(obj->itemDisplay, 0);
                fn_80173BE8(obj->itemDisplay);
            } else {
                fn_80173B68(obj->itemDisplay, id);
                fn_80173C34(obj->itemDisplay);
            }
        }
    }
    if (obj->cleanup == 1) RenderObj_CleanupItem(obj, 6);
    else if (obj->item == 0x2C) ItemHandler_Star(obj, arg);
    else if (obj->state == 0x2D && obj->item == 0xB) ItemHandler_Shell(obj);
    else if (obj->state == 0x2E && obj->item == 0xD) RenderObj_CleanupItem(obj, 5);
    else if (obj->state == 0x2F && obj->item == 0x51) RenderObj_CleanupItem(obj, 5);
    else if (obj->state == 0x2D && obj->item == 0x15) RenderObj_CleanupItem(obj, 5);
    else if (obj->state == 0x2D && obj->item == 0x14) RenderObj_CleanupItem(obj, 5);
    else if (obj->state == 0x2F && obj->item == 0x12) KartItem_TickTrailingFx(obj);
    else if (obj->state == 0x2D && obj->item == 0x37) RenderObj_CleanupItem(obj, 5);
    else if (obj->state == 0x2F && obj->item == 0x13) RenderObj_CleanupItem(obj, 5);
    else if (obj->state == 0x30 && obj->item == 0x2A) KartItem_TickStunStateMachine(obj);
    else if (obj->state == 0x2D && obj->item == 0xF) RenderObj_CleanupItem(obj, 5);
    else if (obj->state == 0x2D && obj->item == 0x7A) KartItem_TickEffectStage_a(obj);
    else if (obj->state == 0x17) RenderObj_CleanupItem(obj, 5);
    else if (obj->state == 0x1C) RenderObj_CleanupItem(obj, 6);
    else if (obj->state == 0x26) RenderObj_CleanupItem(obj, 3);
    else if (obj->state == 0x1D) RenderObj_CleanupItem(obj, 5);
    else if (obj->state == 0x28) KartItem_TickEffectStage_b(obj);
    for (int i = 0; i < 10; ++i) {
        if (ISESlot_IsActive(obj->slots[i]) == 1) ISESlot_FrameUpdate(obj->slots[i]);
    }
    if (obj->accessory) {
        if (!(obj->flags->bits & 0x8000000000ULL) &&
            (!obj->hasSecondary || !g_finalLapCoinJumpEnabled)) {
            Object_BindMatrixSource(obj->accessory, obj->worldMatrix, 0);
        } else {
            Mtx matrix;
            PSMTXCopy(obj->worldMatrix, matrix);
            matrix[1][3] += lbl_806D2614;
            Object_SetAnimBinding(obj->accessory, matrix, 0);
        }
        Object_DriveAnimMatrix(obj->accessory);
    }
    if (obj->bounceJoint) {
        obj->bouncePhase += lbl_806D2590;
        double bounce = __fabs(lbl_806D2618 * LUT_Sin12Bit(obj->bouncePhase));
        steering = (float)bounce;
        HSD_JObj *joint = obj->bounceJoint;
        if (!joint) __assert(lbl_806D2548, 0x2A4, lbl_806D2550);
        if (joint->flags & 0x20000) __assert(lbl_806D2548, 0x2A5, KartDriver_InitFull_rodata_802EADBC);
        *(float *)((char *)joint + 0x1C) = (float)(lbl_806D2620 * steering);
        if (!(joint->flags & 0x02000000) && joint && !MatrixDirty(joint)) HSD_JObjSetMtxDirtySub(joint);
    }
    if (obj->field168) obj->field170 += lbl_806D25B8;
    if (obj->effectJoint && obj->effect) {
        if ((int)Object_GetField8(obj->effect) % 30 == 0) {
            int frame = 0;
            float speed = Vec3_Magnitude(&obj->velocity);
            if (speed > lbl_806D2610) frame = 90;
            else if (speed > lbl_806D2628) frame = 60;
            else if (speed > lbl_806D2608) frame = 30;
            Object_SetField8_10_14(obj->effect, (float)frame, lbl_806D2570, (float)(frame + 30));
        }
        Object_SetAnimBinding(obj->effect, JointMatrix(obj->effectJoint), 0);
        clNormal3D_Exec(obj->effect);
        Object_DriveAnimMatrix(obj->effect);
    }
    AnimState_UpdateEquipped(obj);
    if (obj->countdown != 0) --obj->countdown;
    if (obj->field35c) fn_80231D50(obj->field35c);
    if (obj->overlay) {
        if (obj->overlay->active == 1) {
            float (*matrix)[4];
            if (!obj->root || !obj->output) matrix = 0;
            else matrix = Object_GetJObjLocalMatrix(obj->root);
            Vec3f forward;
            forward.x = matrix[0][0];
            forward.y = lbl_806D2540;
            forward.z = matrix[2][0];
            float (*view)[4] = CObj_GetViewMatrix_Cached(GetCourseScene3D());
            Vec3_Normalize(&forward, &forward);
            Vec3f camera;
            camera.x = view[0][2];
            camera.y = lbl_806D2540;
            camera.z = -view[2][2];
            Vec3_Normalize(&camera, &camera);
            float dot = Vec3_Dot(&camera, &forward);
            if (dot > lbl_806D262C) dot = lbl_806D262C;
            if (dot < lbl_806D2630) dot = lbl_806D2630;
            RenderOverlay *overlay = obj->overlay;
            overlay->x = (float)((int)(lbl_806D2634 * dot) + 310);
            overlay->y = (float)((int)(lbl_806D2638 * (float)__fabs(dot)) + 180);
        }
        fn_80245704(obj->overlay);
    }
    if (obj->field374 != -1) fn_8024F618(obj->field378);
    if (obj->field380) fn_80250984(obj->field380);
    return 1;
}
