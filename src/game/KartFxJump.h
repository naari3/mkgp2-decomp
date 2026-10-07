/* Jump effects. These local views name only fields observed in this family. */
struct Vec3 { float x, y, z; };
struct JumpKartView {
    unsigned char pad00[0x238];
    int visible;
};
struct JumpEffectView {
    unsigned char pad00[0x14];
    unsigned char vfx[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float lifetime;
    unsigned char pad30[0x5C];
    Vec3 position;
    unsigned char pad98[0x18];
    float scale;
    signed char state;
    unsigned char phase;
    unsigned char padB6[0x66];
    JumpKartView *kart;
};
extern "C" {
extern const float lbl_806D51C0, lbl_806D51C4, lbl_806D51C8, lbl_806D51D0;
extern const float lbl_806D521C, lbl_806D5230, lbl_806D5250;
extern const float lbl_806D52A0, lbl_806D52A4, lbl_806D52A8, lbl_806D52AC, lbl_806D52B0;
extern float lbl_805DF3D0[16];
void VfxSlot_BindResourceEx(void *, int, int);
void VfxSlot_SetPositionFromVec(void *, Vec3);
void VfxSlot_SetScaleUniform(void *, float);
void VfxSlot_SetRotationZ(void *, float);
Vec3 Mtx44_TransformVec3(const float *, Vec3);
int Rand_RangeIntMax(int);
float Rand_RangeFloat(float, float);
void Vec3_Copy(Vec3 *, const Vec3 *);
void DrawEffect_Free(JumpEffectView *);
JumpEffectView *DrawEffect_SpawnDirect(void (*)(JumpEffectView *));

void KartFx_JumpRingGlowTick(JumpEffectView *);
void KartFx_JumpDustSmokeTick(JumpEffectView *);
}
