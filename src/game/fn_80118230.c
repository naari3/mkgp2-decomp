extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern double sin(double);
extern void Mtx_TransposeToMtx44(float *dst, void *src);
extern void Matrix4_Identity(float *m);
extern void Matrix4_PreMultiplyRotY(float *m, float *src, float a);
extern void Matrix4_Multiply(float *a, float *b, float *dst);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float *src);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void Item_InitLaunchFromKart(unsigned char *self, int a, float x, float y);

void fn_80118230(unsigned char *self, unsigned char *ctx)
{
    float m1[16];
    float m0[16];

    switch (*(signed char *)(self + 0xCA)) {
    case 0:
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        self[0x28] = 1;
        *(float *)(self + 0x2C) = 0.0f;
        *(float *)(ctx + 0x14) = 0.0f;
        self[0xCA]++;
    case 1:
        GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 7.0f, 2.6179933547973633f, 0.30000001192092896f);
        *(float *)(ctx + 0x14) += 0.004166666883975267f;
        if (1.0f <= *(float *)(ctx + 0x14)) {
            *(float *)(ctx + 0x14) = 0.0f;
        }
        *(float *)(self + 0xB0) = 0.20000000298023224f * (float)sin(0.017453288659453392f * (360.0f * *(float *)(ctx + 0x14))) + *(float *)(self + 0xB0);
        if (*(float *)(self + 0xB0) < 6.283184051513672f) {
            *(float *)(self + 0xB0) += 6.283184051513672f;
        }
        if (6.283184051513672f <= *(float *)(self + 0xB0)) {
            *(float *)(self + 0xB0) -= 6.283184051513672f;
        }
        Mtx_TransposeToMtx44(m1, self + 0x48);
        Matrix4_Identity(m0);
        Matrix4_PreMultiplyRotY(m0, m0, *(float *)(self + 0xB0));
        Matrix4_Multiply(m1, m0, m1);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m1);
        if (FinalLapCoinJump_CheckActiveForObject(*(void **)(ctx + 0x98))) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
        switch (*(signed char *)(ctx + 0xA0)) {
        case 1:
            self[0x28] = 1;
            ctx[0xA0] = 0;
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
            Item_InitLaunchFromKart(self, 0, 1.0f, 0.0f);
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
}
