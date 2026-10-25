extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float f);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void Matrix4_Identity(float *m);
extern void Matrix4_PreMultiplyRotY(float *m, float *src, float a);
extern void Mtx_TransposeToMtx44(float *dst, void *src);
extern void Matrix4_Multiply(float *a, float *b, float *dst);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float *src);
extern void SpriteSlot_TickAnim(void *slot);
extern void Mtx_Copy(void *dst, void *src);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *src);
extern const float lbl_806D6A20;
extern const float lbl_806D6A18;
extern const float lbl_806D6A60;
extern const float lbl_806CF404;
extern const float lbl_806CF408;
extern const float lbl_806CF40C;

void fn_80115118(unsigned char *self, unsigned char *ctx)
{
    float m0[16];
    float m1[16];
    unsigned char *o;

    switch (*(signed char *)(self + 0xCA)) {
    case 0:
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, lbl_806D6A20);
        *(float *)(self + 0x2C) = lbl_806D6A20;
        self[0xCA]++;
    case 1:
        GabyouItem_BuildLocalTransformFromHandJoint(self, 1, lbl_806CF404, lbl_806CF408, lbl_806CF40C);
        switch (*(signed char *)(ctx + 0xA0)) {
        case 1:
            ctx[0xA0] = 0;
            *(float *)(self + 0x2C) = lbl_806D6A18;
            self[0xC9]++;
            self[0xCA] = 0;
            break;
        case 2:
            ctx[0xA0] = 0;
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        }
        break;
    }
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(ctx + 0x98))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    Matrix4_Identity(m0);
    Matrix4_PreMultiplyRotY(m0, m0, lbl_806D6A60);
    Mtx_TransposeToMtx44(m1, self + 0x48);
    Matrix4_Multiply(m1, m0, m1);
    DbgScene_CopyMatrix3x4Transpose(self + 0x48, m1);
    SpriteSlot_TickAnim(self + 0x14);
    if (*(unsigned char **)(ctx + 0x5C)) {
        Mtx_Copy(*(unsigned char **)(ctx + 0x5C) + 0x48, self + 0x48);
        o = *(unsigned char **)(ctx + 0x5C);
        Mtx44_GetTranslation_RowMajor(o + 0xA0, o + 0x48);
        (*(unsigned char **)(ctx + 0x5C))[0x28] = self[0x28];
        *(float *)(*(unsigned char **)(ctx + 0x5C) + 0x2C) = *(float *)(self + 0x2C);
    }
}
