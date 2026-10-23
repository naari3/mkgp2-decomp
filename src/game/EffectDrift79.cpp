/* Narrow target-observed field view; live Ghidra types unavailable. */
struct Drift79Vec { float x, y, z; };
struct Drift79Matrix { float m[16]; };
struct Drift79Effect {
    char pad00[0x14];
    char slot[0x18];
    float alpha;
    char pad30[0x18];
    float matrix[12];
    char pad78[0x14];
    Drift79Vec position, rotation;
    char padA4[0xC];
    float scale;
    signed char state;
    char padB5[0x9B];
    float initialScale, growth;
    char pad158[0x28];
    unsigned int timers[4];
};
extern "C" {
extern const float lbl_806D555C, lbl_806D55A8, lbl_806D55AC;
extern const float lbl_806D55BC, lbl_806D55B4, lbl_806D556C;
void VfxSlot_BindResource(void *, int);
void VfxSlot_SetMatrixSourceEnabled(void *, int);
signed char ItemObject_GetGroundTypeAt(Drift79Vec, float *, int);
float Item_ProbeForwardGroundPitch(Drift79Vec, float, float, float);
float Item_ProbeLateralGroundPitch(Drift79Vec, float, float, float);
void DrawEffect_Free(Drift79Effect *);
void Matrix4_Identity(Drift79Matrix *);
void Mtx44_Scale_Uniform(Drift79Matrix *, const Drift79Matrix *, float);
void Matrix4_PreMultiplyRotZ(Drift79Matrix *, const Drift79Matrix *, float);
void Matrix4_PreMultiplyRotX(Drift79Matrix *, const Drift79Matrix *, float);
void Mtx44_Translate(Drift79Matrix *, const Drift79Matrix *, Drift79Vec);
void DbgScene_CopyMatrix3x4Transpose(float *, const Drift79Matrix *);
void Effect_DriftExplosion_Res79_Update(Drift79Effect *effect) {
    Drift79Matrix matrix;
    switch (effect->state) {
    case 0:
        VfxSlot_BindResource(effect->slot, 0x79);
        VfxSlot_SetMatrixSourceEnabled(effect->slot, 1);
        ItemObject_GetGroundTypeAt(effect->position, &effect->position.y, 0);
        effect->rotation.x = Item_ProbeForwardGroundPitch(effect->position, lbl_806D555C, lbl_806D55A8, lbl_806D555C);
        effect->rotation.z = Item_ProbeLateralGroundPitch(effect->position, lbl_806D555C, lbl_806D55A8, lbl_806D555C);
        effect->position.y += lbl_806D55AC;
        effect->initialScale = effect->scale;
        effect->growth = lbl_806D555C;
        effect->timers[0] = 5;
        ++effect->state;
        break;
    case 1: break;
    }
    if (!effect->timers[0]) {
        effect->alpha -= lbl_806D55BC;
        if (effect->alpha <= lbl_806D555C) {
            DrawEffect_Free(effect);
            return;
        }
    }
    effect->growth += lbl_806D55B4;
    effect->scale = lbl_806D556C * (effect->initialScale * effect->growth);
    Matrix4_Identity(&matrix);
    Mtx44_Scale_Uniform(&matrix, &matrix, effect->scale);
    Matrix4_PreMultiplyRotZ(&matrix, &matrix, effect->rotation.z);
    Matrix4_PreMultiplyRotX(&matrix, &matrix, effect->rotation.x);
    Mtx44_Translate(&matrix, &matrix, effect->position);
    DbgScene_CopyMatrix3x4Transpose(effect->matrix, &matrix);
    if (effect->timers[0]) --effect->timers[0];
    if (effect->timers[1]) --effect->timers[1];
    if (effect->timers[2]) --effect->timers[2];
    if (effect->timers[3]) --effect->timers[3];
}
}
