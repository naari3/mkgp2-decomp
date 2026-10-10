/* Drift puff family: local views contain only target-observed fields. */
struct Vec3 { float x, y, z; };
struct KartState { unsigned char pad00[0x10]; unsigned long long flags; };
struct Kart { unsigned char pad00[0x304]; KartState *state; };
struct Effect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float lifetime;
    unsigned char pad30[0x18];
    float matrix[12];
    unsigned char pad78[0x14];
    Vec3 position;
    unsigned char pad98[8];
    float rotation;
    unsigned char pada4[12];
    float scale;
    signed char state;
    unsigned char padb5[0x14];
    signed char expired;
    unsigned char padca[0x52];
    Kart *kart;
    Vec3 offset;
    unsigned char pad12c[0x24];
    float size, growth;
    unsigned char pad158[0x28];
    unsigned int delay, timer1, timer2, timer3;
    signed char active;
};
struct Camera { float matrix[16]; unsigned char pad40[0x40]; Vec3 position; };
extern "C" {
extern Camera lbl_805DF3D0;
extern const float lbl_806D51C0, lbl_806D51C4, lbl_806D51CC, lbl_806D51DC;
extern const float lbl_806D51E8, lbl_806D5200, lbl_806D5218, lbl_806D521C;
extern const float lbl_806D5220, lbl_806D5224, lbl_806D5280, lbl_806D5304, lbl_806D5308;
void VfxSlot_BindResourceEx(void *, int, int);
void VfxSlot_BindResource(void *, int);
void VfxSlot_SetMatrixSourceEnabled(void *, int);
void VfxSlot_SetAnimSpeed(void *, float);
void VfxSlot_SetRotationZ(void *, float);
void VfxSlot_SetScaleUniform(void *, float);
void VfxSlot_SetPositionFromVec(void *, Vec3);
float Rand_RangeFloat(float, float);
int Rand_RangeInt(int, int);
void GetSpawnPosition(Vec3 *, float, float, float);
void Vec2_RotateY(Vec3 *, const Vec3 *, float);
const float *KartDriver_GetKartRootMtx(Kart *);
void Mtx44_GetTranslation_RowMajor(Vec3 *, const float *);
void Vec3_Add_DestFirst(Vec3 *, const Vec3 *, const Vec3 *);
unsigned char FinalLapCoinJump_CheckActiveForObject(Kart *);
void DrawEffect_Free(Effect *);
Effect *DrawEffect_SpawnDirect(void (*)(Effect *));
void Mtx_TransposeToMtx44(float *, const float *);
void Matrix4_Identity(float *);
void Matrix4_PreMultiplyTranslation(float *, const float *, float, float, float);
void Matrix4_Multiply(float *, const float *, const float *);
void Mtx44_Inverse_GaussJordan(float *, const float *);
Vec3 Mtx44_TransformVec3(const float *, Vec3);
void Mtx44_Scale_Uniform(float *, const float *, float);
double Atan2(double, double);
float BuildOrientationFromYaw(float);
void Matrix4_PreMultiplyRotY(float *, const float *, float);
void DbgScene_CopyMatrix3x4Transpose(float *, const float *);
static inline void Timers(Effect *effect) {
    if (effect->delay != 0) --effect->delay;
    if (effect->timer1 != 0) --effect->timer1;
    if (effect->timer2 != 0) --effect->timer2;
    if (effect->timer3 != 0) --effect->timer3;
}
static inline unsigned char DriftFlag(KartState *state) {
    unsigned char result;
    if ((state->flags & 0x20000ULL) == 0) result = 0;
    else result = 1;
    return result;
}
void KartFx_DriftPuffParticleTick(Effect *);
}

