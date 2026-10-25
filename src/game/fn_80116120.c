typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern signed char ItemObject_GetGroundTypeAt(Vec3 *pos, float *outY, int a);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void Matrix4_Identity(float *m);
extern void Mtx44_Scale_PerAxis(float *m, float *src, float x, float y, float z);
extern void Matrix4_PreMultiplyRotX(float *m, float *src, float a);
extern void Matrix4_PreMultiplyRotY(float *m, float *src, float a);
extern void Mtx44_Translate(float *m, float *src, Vec3 *v);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float *src);

void fn_80116120(unsigned char *self, unsigned char *ctx)
{
    float m[16];
    Vec3 pos;
    Vec3 tpos;
    float groundY;

    switch ((signed char)self[0xC9]) {
    case 0:
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        *(float *)(ctx + 0x14) = 0.0f;
        self[0xC9]++;
    case 1:
        *(float *)(self + 0xBC) += -0.10000000149011612f;
        *(float *)(self + 0xAC) += 0.034906577318906784f;
        if (1.570796012878418f < *(float *)(self + 0xAC)) {
            *(float *)(self + 0xAC) = 1.570796012878418f;
        }
        pos = *(Vec3 *)(self + 0xA0);
        if (ItemObject_GetGroundTypeAt(&pos, &groundY, 0)) {
            if (*(float *)(self + 0xA4) < groundY) {
                *(float *)(self + 0xAC) = 1.570796012878418f;
                *(float *)(self + 0xA4) = 1.0f + groundY;
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0xC9]++;
            }
        } else {
            self[0xC9] = 3;
        }
        break;
    case 2:
        *(float *)(ctx + 0x14) += 0.30000001192092896f;
        if (0.9900000095367432f < *(float *)(ctx + 0x14)) {
            *(float *)(ctx + 0x14) = 0.9900000095367432f;
        }
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.05000000074505806f;
        if (*(float *)(self + 0x2C) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
        break;
    case 3:
        *(float *)(self + 0xBC) += -0.10000000149011612f;
        *(float *)(self + 0xAC) += 0.034906577318906784f;
        if (1.570796012878418f < *(float *)(self + 0xAC)) {
            *(float *)(self + 0xAC) = 1.570796012878418f;
        }
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.10000000149011612f;
        if (*(float *)(self + 0x2C) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
        break;
    }
    Item_DecayVelocityScalar(self, 2.0f);
    Matrix4_Identity(m);
    Mtx44_Scale_PerAxis(m, m, *(float *)(self + 0xC4), *(float *)(self + 0xC4), *(float *)(self + 0xC4));
    Matrix4_PreMultiplyRotX(m, m, *(float *)(self + 0xAC));
    Mtx44_Scale_PerAxis(m, m, 1.0f + *(float *)(ctx + 0x14), 1.0f - *(float *)(ctx + 0x14), 1.0f + *(float *)(ctx + 0x14));
    Matrix4_PreMultiplyRotY(m, m, *(float *)(self + 0xB0));
    tpos = *(Vec3 *)(self + 0xA0);
    Mtx44_Translate(m, m, &tpos);
    DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
}
