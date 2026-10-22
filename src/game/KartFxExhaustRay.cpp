/* Boost exhaust ray. Local views describe target-observed fields only.
 * Aggregate arguments preserve caller-owned copies and native C++ EH.
 * Ground and pitch-probe ABIs were checked against their actual callees.
 * Complete NonMatching candidate: text 98.907524%, native extab 100%.
 * Residuals: scale-table addressing, one multiplication operand order,
 * opacity FP allocation, and source-base folding in the static color copy.
 */
struct RayVec3 { float x, y, z; };
struct RayMtx { float m[16]; };
struct RayKart { unsigned char pad00[0x1F4]; int player, character; };
struct RayColors { RayVec3 entries[2]; };
struct RayResources {
    unsigned char pad00[0x4B0]; float scales[15];
    unsigned char pad4EC[0x48]; RayColors colors;
    unsigned char pad54C[0xB8]; RayVec3 offset;
};
struct RayEffect {
    unsigned char pad00[0x10]; int index;
    unsigned char slot[0x14], visible, pad29[3]; float opacity;
    RayVec3 color; unsigned char pad3C[0xC]; float matrix[12];
    unsigned char pad78[0x14]; RayVec3 position, rotation;
    unsigned char padA4[0xC]; float scale; signed char state;
    unsigned char padB5[0x67]; RayKart *kart; RayVec3 anchor;
    unsigned char pad12C[0x24]; float intensity, growth, size;
    unsigned char pad15C[0x24]; unsigned int timer0, timer1, timer2, timer3;
    signed char special;
};
extern "C" {
extern RayResources lbl_80329E20;
extern RayColors lbl_8041A280[2];
extern signed char lbl_806D14B8;
extern int g_gameMode, g_kartVariant, g_cupId;
extern const float lbl_806D51BC, lbl_806D51C0, lbl_806D51C4, lbl_806D51CC;
extern const float lbl_806D51D4, lbl_806D51E8, lbl_806D5214, lbl_806D52B8, lbl_806D5348;
unsigned char *PcbSlot_GetByIndex(int);
void *KartDriver_GetJointByIdx(RayKart *, int);
void *KartDriver_GetKartRootMtx(RayKart *);
void Mtx44_GetTranslation_RowMajor(RayVec3 *, const void *);
void Mtx44_GetTranslation_ColMajor(RayVec3 *, const RayMtx *);
void Mtx_TransposeToMtx44(RayMtx *, const void *);
void Mtx44_TransformVec3(RayVec3 *, const RayMtx *, RayVec3);
float Mtx44_GetPitchOfPosZ(const RayMtx *);
float Mtx44_GetYawOfPosZ(const RayMtx *);
float Mtx44_GetPitchOfNegX_Lean(const RayMtx *);
void Vec3_Lerp(RayVec3 *, RayVec3, RayVec3, float);
void Vec3_Copy(RayVec3 *, const RayVec3 *);
void Vec3_Subtract_DestFirst(RayVec3 *, const RayVec3 *, const RayVec3 *);
void Vec3_Add_DestFirst(RayVec3 *, const RayVec3 *, const RayVec3 *);
void Vec3_Scale(RayVec3 *, const RayVec3 *, float);
float Vec3_Magnitude_Wrapper(const RayVec3 *);
void VfxSlot_BindResource(void *, int);
void VfxSlot_SetMatrixSourceEnabled(void *, int);
signed char ItemObject_GetGroundTypeAt(RayVec3, float *, int);
float Item_ProbeForwardGroundPitch(RayVec3, float, float, float);
float Item_ProbeLateralGroundPitch(RayVec3, float, float, float);
unsigned char FinalLapCoinJump_CheckActiveForObject(RayKart *);
void DrawEffect_Free(RayEffect *);
void Matrix4_Identity(RayMtx *);
void Mtx44_Scale_PerAxis(RayMtx *, const RayMtx *, float, float, float);
void Matrix4_PreMultiplyRotX(RayMtx *, const RayMtx *, float);
void Matrix4_PreMultiplyRotY(RayMtx *, const RayMtx *, float);
void Matrix4_PreMultiplyRotZ(RayMtx *, const RayMtx *, float);
void Mtx44_Translate(RayMtx *, const RayMtx *, RayVec3);
void DbgScene_CopyMatrix3x4Transpose(float *, const RayMtx *);

static inline int CharacterIndex(RayKart *kart) {
    if (!kart) return -1;
    if (kart->player < 0 || kart->player > 3) return -1;
    if (g_gameMode == 2) {
        if ((((unsigned int)PcbSlot_GetByIndex(kart->player)[6] >> 1) & 3U) < 2U) return -1;
    } else {
        if (g_kartVariant < 2) return -1;
        if (g_cupId >= 9) return -1;
    }
    int index = kart->character;
    if (index < 0 || index >= 15) return -1;
    return index;
}

void KartFx_BoostExhaustRayTick(RayEffect *effect) {
    RayResources *resources = &lbl_80329E20;
    RayMtx offsetMatrix, root, matrix;
    RayVec3 second, first, center, translation;
    float ground;
    if (effect->index == 0) {
        Mtx44_GetTranslation_RowMajor(&first, KartDriver_GetJointByIdx(effect->kart, 0));
        Mtx44_GetTranslation_RowMajor(&second, KartDriver_GetJointByIdx(effect->kart, 1));
    } else {
        Mtx44_GetTranslation_RowMajor(&first, KartDriver_GetJointByIdx(effect->kart, 2));
        Mtx44_GetTranslation_RowMajor(&second, KartDriver_GetJointByIdx(effect->kart, 3));
    }
    Vec3_Lerp(&center, first, second, lbl_806D51E8);
    center.y -= lbl_806D51BC;
    if (effect->index != 0) {
        Mtx_TransposeToMtx44(&offsetMatrix, KartDriver_GetKartRootMtx(effect->kart));
        Mtx44_GetTranslation_ColMajor(&translation, &offsetMatrix);
        RayVec3 offset = resources->offset;
        Mtx44_TransformVec3(&offset, &offsetMatrix, offset);
        Vec3_Subtract_DestFirst(&offset, &offset, &translation);
        Vec3_Add_DestFirst(&center, &center, &offset);
    }
    if (effect->state == 0) {
        Mtx_TransposeToMtx44(&root, KartDriver_GetKartRootMtx(effect->kart));
        effect->rotation.x = Mtx44_GetPitchOfPosZ(&root);
        effect->rotation.y = Mtx44_GetYawOfPosZ(&root);
        effect->rotation.z = Mtx44_GetPitchOfNegX_Lean(&root);
    }
    switch (effect->state) {
    case 0: {
        VfxSlot_BindResource(effect->slot, 11);
        VfxSlot_SetMatrixSourceEnabled(effect->slot, 1);
        Vec3_Copy(&effect->position, &center);
        effect->growth = lbl_806D51C0;
        int character = CharacterIndex(effect->kart);
        effect->size = character < 0 ? lbl_806D51C4 : *(float *)((unsigned char *)resources->scales + character * sizeof(float));
        Vec3_Copy(&effect->anchor, &center);
        if (CharacterIndex(effect->kart) >= 0) effect->special = 1;
        else effect->special = 0;
        ++effect->state;
        break;
    }
    case 1: break;
    }
    float speed;
    if (effect->index != 0) speed = lbl_806D51CC * (lbl_806D5214 * effect->growth);
    else speed = lbl_806D51CC * (lbl_806D5214 * effect->growth);
    RayVec3 delta;
    Vec3_Subtract_DestFirst(&delta, &effect->anchor, &center);
    float distance = Vec3_Magnitude_Wrapper(&delta);
    if (speed < distance) {
        Vec3_Scale(&delta, &delta, speed * (lbl_806D51C4 / distance));
        Vec3_Add_DestFirst(&effect->anchor, &center, &delta);
    }
    if (ItemObject_GetGroundTypeAt(effect->anchor, &ground, 0) != 0) {
        ground += lbl_806D51C4;
        if (effect->anchor.y < ground) {
            effect->anchor.y = ground;
            effect->rotation.x = Item_ProbeForwardGroundPitch(effect->anchor, effect->rotation.y, lbl_806D51CC, lbl_806D51C4);
            effect->rotation.z = Item_ProbeLateralGroundPitch(effect->anchor, effect->rotation.y, lbl_806D51CC, lbl_806D51C4);
        }
    }
    Vec3_Copy(&effect->position, &effect->anchor);
    effect->scale = effect->size;
    float maximum = lbl_806D51C4;
    float factor = lbl_806D51BC;
    float opacity = maximum - effect->growth;
    opacity = factor * opacity;
    if (maximum < opacity) opacity = maximum;
    if (effect->index == 0) effect->opacity = opacity;
    else effect->opacity = opacity;
    effect->opacity *= effect->intensity;
    if (!lbl_806D14B8) {
        lbl_8041A280[1] = resources->colors;
        lbl_806D14B8 = 1;
    }
    RayColors *colors = &lbl_8041A280[effect->special];
    Vec3_Lerp(&effect->color, colors->entries[1], colors->entries[0], effect->growth);
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
    if (effect->index == 0) effect->growth += lbl_806D51D4;
    else effect->growth += lbl_806D51D4;
    if (lbl_806D51C4 < effect->growth) { DrawEffect_Free(effect); return; }
    Matrix4_Identity(&matrix);
    Mtx44_Scale_PerAxis(&matrix, &matrix, lbl_806D51BC * effect->scale, lbl_806D51BC * effect->scale, effect->scale);
    Matrix4_PreMultiplyRotY(&matrix, &matrix, lbl_806D5348);
    Matrix4_PreMultiplyRotX(&matrix, &matrix, lbl_806D52B8);
    Matrix4_PreMultiplyRotX(&matrix, &matrix, effect->rotation.x);
    Matrix4_PreMultiplyRotZ(&matrix, &matrix, effect->rotation.z);
    Matrix4_PreMultiplyRotY(&matrix, &matrix, effect->rotation.y);
    Mtx44_Translate(&matrix, &matrix, effect->position);
    DbgScene_CopyMatrix3x4Transpose(effect->matrix, &matrix);
    if (effect->timer0) --effect->timer0;
    if (effect->timer1) --effect->timer1;
    if (effect->timer2) --effect->timer2;
    if (effect->timer3) --effect->timer3;
}
}
