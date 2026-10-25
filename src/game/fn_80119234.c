typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void TripleBladeRing_Update(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern float Vec3_PitchTo(void *a, void *b);
extern float Vec3_HorizontalYawTo(void *a, void *b);
extern void Matrix4_Identity(float *m);
extern void Mtx44_Scale_Uniform(float *m, float *src, float s);
extern void Matrix4_PreMultiplyRotX(float *m, float *src, float a);
extern void Matrix4_PreMultiplyRotY(float *m, float *src, float a);
extern void Mtx44_Translate(float *m, float *src, Vec3 *v);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float *src);
extern void TripleBladeRing_SetWorldYaw(unsigned char *e, void *mtx, float yaw);
extern void SpriteSlot_Container_Free(void *self);
extern unsigned char lbl_805DF3D0[];
extern float lbl_806D6BF0;
extern float lbl_806D6BF4;

void fn_80119234(unsigned char *self)
{
    Vec3 pos;
    float m[16];
    unsigned char *cam;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x94);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        self[0x28] = 1;
        *(float *)(self + 0x2C) = lbl_806D6BF0;
        *(unsigned char **)(self + 0x138) = DrawEffect_SpawnDirect(TripleBladeRing_Update);
        self[0xC8] = 1;
    case 1:
        GabyouItem_BuildLocalTransformFromHandJoint(self, 1, lbl_806D6BF4, lbl_806D6BF0, lbl_806D6BF4);
        cam = lbl_805DF3D0 + 0x80;
        *(float *)(self + 0xAC) = Vec3_PitchTo(cam, self + 0xA0);
        *(float *)(self + 0xB0) = Vec3_HorizontalYawTo(cam, self + 0xA0);
        Matrix4_Identity(m);
        Mtx44_Scale_Uniform(m, m, *(float *)(self + 0xC4));
        Matrix4_PreMultiplyRotX(m, m, *(float *)(self + 0xAC));
        Matrix4_PreMultiplyRotY(m, m, *(float *)(self + 0xB0));
        pos = *(Vec3 *)(self + 0xA0);
        Mtx44_Translate(m, m, &pos);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
        if (FinalLapCoinJump_CheckActiveForObject(*(void **)(self + 0x184))) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
        if (*(unsigned char **)(self + 0x138)) {
            if (*(signed char *)(self + 0x28)) {
                TripleBladeRing_SetWorldYaw(*(unsigned char **)(self + 0x138), self + 0x48, *(float *)(self + 0x2C));
            } else {
                TripleBladeRing_SetWorldYaw(*(unsigned char **)(self + 0x138), self + 0x48, lbl_806D6BF0);
            }
        }
        if (*(signed char *)(self + 0x18C)) {
            if (*(unsigned char **)(self + 0x138)) {
                (*(unsigned char **)(self + 0x138))[0xC9] = 1;
            }
            SpriteSlot_Container_Free(self);
        }
        break;
    }
}
