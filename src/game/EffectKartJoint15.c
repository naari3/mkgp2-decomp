/* Target-observed local views; live Ghidra type lookup was unavailable. */
typedef struct JointVec { float x, y, z; } JointVec;
typedef struct JointEffect {
    char pad00[0x14];
    char slot[0x14];
    unsigned char visible;
    char pad29[3];
    float alpha;
    char pad30[0x5C];
    JointVec position;
    JointVec rotation;
    char padA4[0xC];
    float scale;
    signed char state;
    char padB5[0x67];
    void *kart;
    JointVec offset;
    char pad12C[0x24];
    float growth;
    char pad154[0x2C];
    unsigned int timers[4];
} JointEffect;
extern const float lbl_806D5550, lbl_806D5554, lbl_806D5558;
extern const float lbl_806D555C, lbl_806D5560, lbl_806D5564;
extern void *KartDriver_GetKartRootMtx(void *);
extern void *KartDriver_GetJointByIdx(void *, int);
extern void Mtx44_GetTranslation_RowMajor(JointVec *, const void *);
extern void VfxSlot_BindResource(void *, int);
extern void VfxSlot_SetAnimSpeed(void *, float);
extern float KartFxParam_GetConst1p5(void *);
extern void Vec3_Subtract_DestFirst(JointVec *, const JointVec *, const JointVec *);
extern void Vec3_Add_DestFirst(JointVec *, const JointVec *, const JointVec *);
extern void DrawEffect_Free(JointEffect *);
extern void VfxSlot_SetPositionFromVec(void *, JointVec);
extern void VfxSlot_SetRotationXYZFromVec(void *, JointVec);
extern void VfxSlot_SetScaleVec3(void *, float, float, float);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *);

void Effect_KartJoint15_Res7B_Update(JointEffect *effect) {
    JointVec root;
    Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(effect->kart));
    switch (effect->state) {
    case 0: {
        JointVec joint;
        VfxSlot_BindResource(effect->slot, 0x7B);
        VfxSlot_SetAnimSpeed(effect->slot, lbl_806D5550);
        effect->rotation.x = lbl_806D5554;
        effect->scale *= lbl_806D5558;
        effect->growth = lbl_806D555C;
        Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(effect->kart, 15));
        effect->position.y = lbl_806D5550 * KartFxParam_GetConst1p5(effect->kart) + joint.y;
        Vec3_Subtract_DestFirst(&effect->offset, &effect->position, &root);
        effect->timers[0] = 5;
        ++effect->state;
        break;
    }
    case 1: break;
    }
    if (!effect->timers[0]) {
        effect->alpha -= lbl_806D5560;
        if (effect->alpha < lbl_806D555C) {
            DrawEffect_Free(effect);
            return;
        }
    }
    effect->growth += lbl_806D5564;
    Vec3_Add_DestFirst(&effect->position, &root, &effect->offset);
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetRotationXYZFromVec(effect->slot, effect->rotation);
    VfxSlot_SetScaleVec3(effect->slot, effect->scale, effect->scale * effect->growth, effect->scale);
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
    if (effect->timers[0]) --effect->timers[0];
    if (effect->timers[1]) --effect->timers[1];
    if (effect->timers[2]) --effect->timers[2];
    if (effect->timers[3]) --effect->timers[3];
}
