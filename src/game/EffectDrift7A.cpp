/* Target-observed local views; live Ghidra type lookup was unavailable. */
struct DriftVec { float x, y, z; };
struct DriftMtx { float m[16]; };
struct DriftEffect {
    char pad00[0x14]; char slot[0x14];
    char pad28[4]; float alpha;
    char pad30[0x18]; float matrix[12];
    char pad78[0x14]; DriftVec position, rotation;
    char padA4[0xC]; float scale; signed char state;
    char padB5[0x9B]; float growth;
    char pad154[0x2C]; unsigned int timers[4]; signed char joint;
};
extern "C" {
extern const float lbl_806D555C, lbl_806D556C, lbl_806D5584;
extern const float lbl_806D55A8, lbl_806D55AC, lbl_806D55B0, lbl_806D55B4, lbl_806D55B8;
extern void *Effect_DriftExplosion_Res7A_JointChain_Update_data_8041A494[15];
void VfxSlot_BindResource(void *, int);
void VfxSlot_SetMatrixSourceEnabled(void *, int);
#ifdef __MWERKS__
signed char ItemObject_GetGroundTypeAt(DriftVec, float *, int);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern signed char ItemObject_GetGroundTypeAt(DriftVec *, float *, int);
static inline signed char ItemObject_GetGroundTypeAt_ByValue(DriftVec a0, float *a1, int a2) { return ItemObject_GetGroundTypeAt(&a0, a1, a2); }
#define ItemObject_GetGroundTypeAt ItemObject_GetGroundTypeAt_ByValue
#endif
#ifdef __MWERKS__
float Item_ProbeForwardGroundPitch(DriftVec, float, float, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeForwardGroundPitch(DriftVec *, float, float, float);
static inline float Item_ProbeForwardGroundPitch_ByValue(DriftVec a0, float a1, float a2, float a3) { return Item_ProbeForwardGroundPitch(&a0, a1, a2, a3); }
#define Item_ProbeForwardGroundPitch Item_ProbeForwardGroundPitch_ByValue
#endif
#ifdef __MWERKS__
float Item_ProbeLateralGroundPitch(DriftVec, float, float, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeLateralGroundPitch(DriftVec *, float, float, float);
static inline float Item_ProbeLateralGroundPitch_ByValue(DriftVec a0, float a1, float a2, float a3) { return Item_ProbeLateralGroundPitch(&a0, a1, a2, a3); }
#define Item_ProbeLateralGroundPitch Item_ProbeLateralGroundPitch_ByValue
#endif
void Matrix4_Identity(DriftMtx *);
void Mtx44_Scale_Uniform(DriftMtx *, const DriftMtx *, float);
void Matrix4_PreMultiplyRotZ(DriftMtx *, const DriftMtx *, float);
void Matrix4_PreMultiplyRotX(DriftMtx *, const DriftMtx *, float);
#ifdef __MWERKS__
void Mtx44_Translate(DriftMtx *, const DriftMtx *, DriftVec);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_Translate(DriftMtx *, const DriftMtx *, DriftVec *);
static inline void Mtx44_Translate_ByValue(DriftMtx *a0, const DriftMtx *a1, DriftVec a2) { Mtx44_Translate(a0, a1, &a2); }
#define Mtx44_Translate Mtx44_Translate_ByValue
#endif
void DbgScene_CopyMatrix3x4Transpose(float *, const DriftMtx *);
void DrawEffect_Free(DriftEffect *);
void VfxSlot_ResolveJoint(void *, void *);
void Effect_DriftExplosion_Res7A_JointChain_Update(DriftEffect *effect) {
    switch (effect->state) {
    case 0: {
        DriftMtx matrix;
        VfxSlot_BindResource(effect->slot, 0x7A);
        VfxSlot_SetMatrixSourceEnabled(effect->slot, 1);
        ItemObject_GetGroundTypeAt(effect->position, &effect->position.y, 0);
        effect->rotation.x = Item_ProbeForwardGroundPitch(effect->position, lbl_806D555C, lbl_806D55A8, lbl_806D555C);
        effect->rotation.z = Item_ProbeLateralGroundPitch(effect->position, lbl_806D555C, lbl_806D55A8, lbl_806D555C);
        effect->position.y += lbl_806D55AC;
        effect->scale = lbl_806D556C * effect->scale;
        Matrix4_Identity(&matrix);
        Mtx44_Scale_Uniform(&matrix, &matrix, effect->scale);
        Matrix4_PreMultiplyRotZ(&matrix, &matrix, effect->rotation.z);
        Matrix4_PreMultiplyRotX(&matrix, &matrix, effect->rotation.x);
        Mtx44_Translate(&matrix, &matrix, effect->position);
        DbgScene_CopyMatrix3x4Transpose(effect->matrix, &matrix);
        effect->growth = lbl_806D555C;
        effect->joint = -1;
        ++effect->state;
        break;
    }
    case 1: break;
    }
    float maximum = 1.0f;
    effect->growth += lbl_806D55B0;
    if (maximum <= effect->growth) {
        effect->growth = maximum;
        effect->alpha -= lbl_806D55B4;
        if (effect->alpha <= lbl_806D555C) {
            DrawEffect_Free(effect);
            return;
        }
    }
    signed char oldJoint = effect->joint;
    effect->joint = (signed char)(lbl_806D55B8 * effect->growth);
    if ((unsigned int)effect->joint >= 15U) effect->joint = 14;
    if (oldJoint != effect->joint) VfxSlot_ResolveJoint(effect->slot, Effect_DriftExplosion_Res7A_JointChain_Update_data_8041A494[effect->joint]);
    if (effect->timers[0]) --effect->timers[0];
    if (effect->timers[1]) --effect->timers[1];
    if (effect->timers[2]) --effect->timers[2];
    if (effect->timers[3]) --effect->timers[3];
}
}
