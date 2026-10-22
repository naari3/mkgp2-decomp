/* Auxiliary acceleration burst: local ABI views contain only observed fields.
 * The position setter consumes a by-value vector and EH metadata is native.
 */
struct AuxVec3 { float x, y, z; };
struct AuxMotion { unsigned char pad00[0x10]; unsigned long long flags; };
struct AuxKart { unsigned char pad00[0x304]; AuxMotion *motion; };
struct AuxEffect {
    unsigned char pad00[0x14], slot[0x14];
    unsigned char visible, pad29[3];
    float opacity;
    unsigned char pad30[0x5c];
    AuxVec3 position;
    unsigned char pad98[8];
    float rotation;
    AuxVec3 velocity;
    float scale;
    signed char state;
    unsigned char padb5[0x67];
    AuxKart *kart;
    AuxVec3 offset;
    unsigned char pad12c[0x24];
    float size, growth;
    unsigned char pad158[0x28];
    unsigned int delay, timer1, timer2, timer3;
    signed char variant;
};
extern "C" {
extern const float lbl_806D51C0, lbl_806D51C4, lbl_806D51C8, lbl_806D51D0;
extern const float lbl_806D51D4, lbl_806D51D8, lbl_806D51F8, lbl_806D521C;
extern const float lbl_806D5220, lbl_806D5224, lbl_806D5248, lbl_806D525C;
extern const float lbl_806D5260, lbl_806D5268, lbl_806D526C, lbl_806D527C;
extern const float lbl_806D5280, lbl_806D5284, lbl_806D5288;
void VfxSlot_BindResourceEx(void *, unsigned char, int);
int Rand_RangeIntMax(int);
float Rand_RangeFloat(float, float);
void GetSpawnPosition(AuxVec3 *, float, float, float);
void Vec2_RotateX(AuxVec3 *, const AuxVec3 *, float);
void Vec2_RotateY(AuxVec3 *, const AuxVec3 *, float);
void Vec3_Scale(AuxVec3 *, const AuxVec3 *, float);
void Vec3_Add_DestFirst(AuxVec3 *, const AuxVec3 *, const AuxVec3 *);
void Vec3_Subtract_DestFirst(AuxVec3 *, const AuxVec3 *, const AuxVec3 *);
const float *KartDriver_GetKartRootMtx(AuxKart *);
const float *KartDriver_GetJointByIdx(AuxKart *, int);
void Mtx44_GetTranslation_RowMajor(AuxVec3 *, const float *);
void DrawEffect_Free(AuxEffect *);
float BuildOrientationFromYaw(float);
unsigned char FinalLapCoinJump_CheckActiveForObject(AuxKart *);
void VfxSlot_SetPositionFromVec(void *, AuxVec3);
void VfxSlot_SetRotationZ(void *, float);
void VfxSlot_SetScaleUniform(void *, float);

void KartFx_Slot4C_AuxAccelBurstTick(AuxEffect *effect) {
    AuxVec3 root, joint, displacement, currentRoot;
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 2, 0);
        effect->opacity = lbl_806D51F8;
        effect->variant = Rand_RangeIntMax(15) % 2;
        GetSpawnPosition(&effect->velocity, lbl_806D51C0, lbl_806D51C0, lbl_806D51C4);
        Vec2_RotateX(&effect->velocity, &effect->velocity, lbl_806D527C);
        if ((effect->kart->motion->flags & 2) != 0) {
            Vec2_RotateY(&effect->velocity, &effect->velocity,
                lbl_806D521C * Rand_RangeFloat(lbl_806D525C, lbl_806D5260));
            effect->variant = 0;
        } else if (effect->variant == 0) {
            Vec2_RotateY(&effect->velocity, &effect->velocity,
                lbl_806D521C * Rand_RangeFloat(lbl_806D525C, lbl_806D5260));
        } else {
            if (Rand_RangeIntMax(15) % 2 != 0) {
                Vec2_RotateY(&effect->velocity, &effect->velocity,
                    lbl_806D521C * Rand_RangeFloat(lbl_806D5260, lbl_806D5224));
            } else {
                Vec2_RotateY(&effect->velocity, &effect->velocity,
                    lbl_806D521C * Rand_RangeFloat(lbl_806D5220, lbl_806D525C));
            }
        }
        Vec3_Scale(&effect->offset, &effect->velocity, lbl_806D51D0);
        Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(effect->kart));
        Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(effect->kart, 15));
        Vec3_Subtract_DestFirst(&displacement, &joint, &root);
        Vec3_Add_DestFirst(&effect->offset, &effect->offset, &displacement);
        Vec3_Scale(&effect->velocity, &effect->velocity, lbl_806D51D4);
        effect->rotation = lbl_806D521C * Rand_RangeFloat(lbl_806D5220, lbl_806D5224);
        if (effect->variant == 0)
            effect->size = Rand_RangeFloat(lbl_806D51C8, lbl_806D51D4);
        else
            effect->size = Rand_RangeFloat(lbl_806D51D4, lbl_806D5280);
        effect->growth = lbl_806D51D4;
        effect->scale = effect->size * effect->growth;
        effect->delay = 60;
        ++effect->state;
        break;
    case 1: break;
    }
    if (effect->delay == 0) {
        effect->opacity -= lbl_806D51D8;
        if (effect->opacity < 0.0f) {
            effect->visible = 0;
            DrawEffect_Free(effect);
            return;
        }
    } else {
        if (effect->variant == 0) effect->opacity += lbl_806D5284;
        else effect->opacity += lbl_806D51D8;
        if (lbl_806D51C4 < effect->opacity) effect->opacity = lbl_806D51C4;
    }
    effect->rotation = BuildOrientationFromYaw(effect->rotation - lbl_806D5288);
    effect->growth += lbl_806D51D8;
    if (lbl_806D51C4 < effect->growth) effect->growth = lbl_806D51C4;
    Vec3_Scale(&effect->velocity, &effect->velocity, lbl_806D5268);
    effect->velocity.y += lbl_806D526C;
    Vec3_Add_DestFirst(&effect->offset, &effect->offset, &effect->velocity);
    Mtx44_GetTranslation_RowMajor(&currentRoot, KartDriver_GetKartRootMtx(effect->kart));
    Vec3_Add_DestFirst(&effect->position, &currentRoot, &effect->offset);
    effect->scale = lbl_806D5248 * (effect->size * effect->growth);
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
    VfxSlot_SetPositionFromVec(effect->slot, effect->position);
    VfxSlot_SetRotationZ(effect->slot, effect->rotation);
    VfxSlot_SetScaleUniform(effect->slot, effect->scale);
    if (effect->delay) --effect->delay;
    if (effect->timer1) --effect->timer1;
    if (effect->timer2) --effect->timer2;
    if (effect->timer3) --effect->timer3;
}
}
