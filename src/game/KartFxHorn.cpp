/* Horn effect callback. Local views describe only target-observed fields.
 * Positional sound arguments are by-value Vec3 caller copies; EH is native.
 */
struct HornVec3 { float x, y, z; };
struct HornMotion { unsigned char pad00[0x28]; float yawStep; };
struct HornKart { unsigned char pad00[0x304]; HornMotion *motion; };
struct HornEffect {
    unsigned char pad00[0x14], slot[0x14];
    unsigned char visible, pad29[3];
    float opacity;
    unsigned char pad30[0x18];
    float matrix[12];
    unsigned char pad78[0x14];
    HornVec3 position;
    unsigned char pad98[4];
    float yaw;
    unsigned char pada0[0x10];
    float scale;
    signed char state;
    unsigned char padb5[0x14];
    signed char expired;
    unsigned char padca[0x52];
    HornKart *kart;
    unsigned char pad120[0x30];
    float motion, lastMotion;
    unsigned char pad158[0x28];
    unsigned int delay, timer1, timer2, timer3;
    signed char channel;
};
extern "C" {
extern const float lbl_806D51C0, lbl_806D51C4, lbl_806D51C8, lbl_806D51D4, lbl_806D530C;
void VfxSlot_BindResource(void *, int);
void VfxSlot_SetMatrixSourceEnabled(void *, int);
void SoundMgr_StopSE_OrSpecial(int, int);
int SoundMgr_CountActiveSEInstances(int);
void SoundMgr_PlaySE_Positional(int, HornVec3, int);
void SoundMgr_PlaySE_WithChannel(int, HornVec3, int);
void DrawEffect_Free(HornEffect *);
double FAbs_FloatAsDouble(float);
float BuildOrientationFromYaw(float);
const float *KartDriver_GetKartRootMtx(HornKart *);
void Mtx_TransposeToMtx44(float *, const float *);
void Matrix4_Identity(float *);
void Matrix4_PreMultiplyRotY(float *, const float *, float);
void Matrix4_Multiply(float *, const float *, const float *);
void DbgScene_CopyMatrix3x4Transpose(float *, const float *);
void Mtx44_GetTranslation_RowMajor(HornVec3 *, const float *);
unsigned char FinalLapCoinJump_CheckActiveForObject(HornKart *);

void KartFx_HornBlastTick(HornEffect *effect) {
    float base[16], rotation[16];
    switch (effect->state) {
    case 0:
        VfxSlot_BindResource(effect->slot, 0x7C);
        VfxSlot_SetMatrixSourceEnabled(effect->slot, 1);
        effect->visible = 1;
        effect->opacity = lbl_806D51C0;
        effect->scale = 1.0f;
        effect->lastMotion = lbl_806D51C0;
        effect->delay = 0;
        effect->channel = -1;
        ++effect->state;
        break;
    case 1: break;
    }
    if (effect->expired) {
        if (effect->channel >= 0) {
            SoundMgr_StopSE_OrSpecial(0x61, effect->channel);
            effect->channel = -1;
        }
        DrawEffect_Free(effect);
        return;
    }
    effect->motion = effect->kart->motion->yawStep;
    if (lbl_806D530C < FAbs_FloatAsDouble(effect->motion)) {
        effect->opacity += lbl_806D51D4;
        if (1.0f < effect->opacity) effect->opacity = 1.0f;
        effect->lastMotion = effect->motion;
        if (effect->channel < 0) {
            effect->channel = SoundMgr_CountActiveSEInstances(0x61);
            if (effect->channel >= 0) SoundMgr_PlaySE_Positional(0x61, effect->position, effect->channel);
        }
        effect->delay = 10;
    } else {
        if (effect->delay == 0) {
            effect->opacity -= lbl_806D51C8;
            if (effect->opacity < 0.0f) {
                effect->opacity = 0.0f;
                if (effect->channel >= 0) {
                    SoundMgr_StopSE_OrSpecial(0x61, effect->channel);
                    effect->channel = -1;
                }
            }
        }
        effect->yaw = BuildOrientationFromYaw(effect->yaw + effect->lastMotion);
    }
    Mtx_TransposeToMtx44(base, KartDriver_GetKartRootMtx(effect->kart));
    Matrix4_Identity(rotation);
    Matrix4_PreMultiplyRotY(rotation, rotation, effect->yaw);
    Matrix4_Multiply(base, rotation, base);
    DbgScene_CopyMatrix3x4Transpose(effect->matrix, base);
    Mtx44_GetTranslation_RowMajor(&effect->position, effect->matrix);
    if (effect->channel >= 0) SoundMgr_PlaySE_WithChannel(0x61, effect->position, effect->channel);
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
    if (effect->delay) --effect->delay;
    if (effect->timer1) --effect->timer1;
    if (effect->timer2) --effect->timer2;
    if (effect->timer3) --effect->timer3;
}
}
