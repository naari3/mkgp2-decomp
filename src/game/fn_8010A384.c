typedef struct Vec3 { float x, y, z; } Vec3;
typedef float Mtx44[4][4];

extern void GetSpawnPosition(void *out, float x, float y, float z);
extern unsigned char *DrawEffect_SpawnDirect(void *fn);
extern void Effect_SeC2_PositionalUpdate(void);
extern void Vec3_Copy(void *dst, void *src);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void Vec3_Lerp(void *dst, Vec3 *a, Vec3 *b, float t);
extern float AngleStepTowards_Shortest(float cur, float target, float step);
extern float Vec3_HorizontalYawTo(void *from, void *to);
extern float KartFxParam_GetConst1p5(void *kart);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern float BuildOrientationFromYaw(float yaw);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Matrix4_Identity(Mtx44 m);
extern void Matrix4_PreMultiplyRotX(Mtx44 dst, Mtx44 src, float a);
extern void Matrix4_PreMultiplyRotY(Mtx44 dst, Mtx44 src, float a);
extern void Matrix4_PreMultiplyRotZ(Mtx44 dst, Mtx44 src, float a);
extern void Matrix4_PreMultiplyTranslation(Mtx44 dst, Mtx44 src, float x, float y, float z);
extern void Mtx44_Scale_Uniform(Mtx44 dst, Mtx44 src, float s);
extern void Mtx44_Translate(Mtx44 dst, Mtx44 src, Vec3 *v);
extern void Effect_BindRes5Aor5B_AnimSpeed(void *e, Mtx44 m, float speed);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);

extern unsigned char lbl_805DF3D0[];

#define KART_FLAGS(k) (*(unsigned long long *)(*(unsigned char **)((unsigned char *)(k) + 0x304) + 0x10))

static inline unsigned char Kart_IsFlag200(void *kart)
{
    unsigned char result;
    if ((KART_FLAGS(kart) & 0x20000000000ULL) == 0) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

void fn_8010A384(unsigned char *self, unsigned char *sub)
{
    Mtx44 m;
    Vec3 t;
    Vec3 t2;
    Vec3 t3;
    Vec3 t4;
    Vec3 b;
    Vec3 a;
    Vec3 p;
    float w;

    switch ((signed char)self[0xC9]) {
    case 0:
        *(unsigned int *)(sub + 0x8) = 10;
        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
        self[0x3C] = 0;
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xCA]) {
        case 0:
            *(float *)(sub + 0x14) = 0.0f;
            *(unsigned char **)(sub + 0x4C) = DrawEffect_SpawnDirect(Effect_SeC2_PositionalUpdate);
            *(float *)(sub + 0x18) = 0.0f;
            Vec3_Copy(sub + 0x34, self + 0xA0);
            Mtx44_GetTranslation_RowMajor(&t, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9C)));
            t.y += 25.0f;
            Vec3_Copy(sub + 0x34, &t);
            self[0xCA]++;
        case 1:
            *(float *)(sub + 0x14) += 0.05f;
            if (1.0f < *(float *)(sub + 0x14)) {
                *(float *)(sub + 0x14) = 1.0f;
            }
            if (1.0f == *(float *)(sub + 0x14) && Kart_IsFlag200(*(void **)(sub + 0x9C)) == 1) {
                self[0xCA]++;
            }
            if (!(KART_FLAGS(*(void **)(sub + 0x9C)) & 0x400000000ULL)) {
                self[0xCA] = 3;
            }
            break;
        case 2:
            *(float *)(sub + 0x18) += 0.016666668f;
            if (1.0f < *(float *)(sub + 0x18)) {
                *(float *)(sub + 0x18) = 1.0f;
            }
            if (!(KART_FLAGS(*(void **)(sub + 0x9C)) & 0x20000000000ULL)) {
                *(float *)(sub + 0x14) = 0.0f;
                self[0xCA]++;
            }
            break;
        case 3:
            *(float *)(sub + 0x14) += 0.05f;
            if (1.0f < *(float *)(sub + 0x14)) {
                *(float *)(sub + 0x14) = 1.0f;
            }
            *(float *)(sub + 0x18) = *(float *)(sub + 0x18) - 0.016666668f;
            if (*(float *)(sub + 0x18) < 0.0f) {
                *(float *)(sub + 0x18) = 0.0f;
                *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.05f;
                if (*(float *)(self + 0x2C) < 0.0f) {
                    if (*(unsigned char **)(sub + 0x4C)) {
                        (*(unsigned char **)(sub + 0x4C))[0xC9] = 1;
                    }
                    *(unsigned char **)(sub + 0x4C) = 0;
                    self[0x28] = 0;
                    self[0xC8] = 3;
                    self[0xC9] = 0;
                    return;
                }
            }
            break;
        }
        if (!Kart_IsFlag200(*(void **)(sub + 0x9C))) {
            Mtx44_GetTranslation_RowMajor(&t2, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9C)));
            t2.y += 25.0f;
            Vec3_Copy(sub + 0x34, &t2);
        }
        if (1.0f != *(float *)(sub + 0x14) || !(KART_FLAGS(*(void **)(sub + 0x9C)) & 0x20000000000ULL)) {
            a = *(Vec3 *)(self + 0xA0);
            b = *(Vec3 *)(sub + 0x34);
            Vec3_Lerp(self + 0xA0, &b, &a, *(float *)(sub + 0x14));
        }
        *(float *)(self + 0xAC) = AngleStepTowards_Shortest(*(float *)(self + 0xAC), 1.570796f, 0.17453289f);
        w = *(float *)(sub + 0x14);
        *(float *)(self + 0xB0) =
            *(float *)(self + 0xB0) * (1.0f - w) + w * Vec3_HorizontalYawTo(self + 0xA0, lbl_805DF3D0 + 0x80);
        Item_DecayVelocityScalar(self, KartFxParam_GetConst1p5(*(void **)(sub + 0x9C)));
        if (*(unsigned char **)(sub + 0x9C) && *(unsigned int *)(sub + 0x8) == 0) {
            unsigned char *fl = *(unsigned char **)(*(unsigned char **)(sub + 0x9C) + 0x304);
            if (!(*(unsigned long long *)(fl + 0x10) & 0x400000000ULL)) {
                *(unsigned int *)(sub + 0x4) = 0;
            }
            if (*(unsigned long long *)(fl + 0x10) & 0x10000ULL) {
                if (*(unsigned char **)(sub + 0x4C)) {
                    (*(unsigned char **)(sub + 0x4C))[0xC9] = 1;
                }
                *(unsigned char **)(sub + 0x4C) = 0;
                Mtx44_GetTranslation_RowMajor(&t3, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9C)));
                Vec3_Subtract_DestFirst(sub + 0x34, self + 0xA0, &t3);
                GetSpawnPosition(sub + 0x40, 0.0f, 1.0f, 1.0f);
                Vec2_RotateY(sub + 0x40, sub + 0x40, BuildOrientationFromYaw(3.141592f + *(float *)(self + 0xB0)));
                self[0xC9] = 2;
                self[0xCA] = 0;
                return;
            }
        }
        if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x9C))) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
        if (*(unsigned char **)(sub + 0x4C)) {
            Matrix4_Identity(m);
            Matrix4_PreMultiplyRotX(m, m, -1.570796f);
            Matrix4_PreMultiplyTranslation(m, m, 0.0f, 0.0f, 1.0f);
            Mtx44_Scale_Uniform(m, m, 1.8f * *(float *)(self + 0xC4));
            Matrix4_PreMultiplyRotZ(m, m, *(float *)(self + 0xB4));
            Matrix4_PreMultiplyRotX(m, m, *(float *)(self + 0xAC));
            Matrix4_PreMultiplyRotY(m, m, *(float *)(self + 0xB0));
            p = *(Vec3 *)(self + 0xA0);
            Mtx44_Translate(m, m, &p);
            if (*(signed char *)(self + 0x28) != 0) {
                Effect_BindRes5Aor5B_AnimSpeed(*(void **)(sub + 0x4C), m, *(float *)(sub + 0x18));
            } else {
                Effect_BindRes5Aor5B_AnimSpeed(*(void **)(sub + 0x4C), m, 0.0f);
            }
        }
        break;
    case 2:
        self[0x28] = 1;
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.05f;
        if (*(float *)(self + 0x2C) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        }
        *(float *)(sub + 0x44) += -0.1f;
        Vec3_Add_DestFirst(sub + 0x34, sub + 0x34, sub + 0x40);
        Mtx44_GetTranslation_RowMajor(&t4, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9C)));
        Vec3_Add_DestFirst(self + 0xA0, &t4, sub + 0x34);
        *(float *)(self + 0xAC) = BuildOrientationFromYaw(*(float *)(self + 0xAC) - 0.17453289f);
        break;
    }
}
