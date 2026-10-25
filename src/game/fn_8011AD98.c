typedef struct Vec3 { float x, y, z; } Vec3;

extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_Inverse_GaussJordan(float dst[4][4], float src[4][4]);
extern void Mtx44_TransformVec3(void *out, float m[4][4], Vec3 v);
extern float Vec3_ToYaw(void *v);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec3_Copy(void *dst, void *src);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void ItemHit_Dispatch(void *self, int a, void *pos, void *target);
extern unsigned char *DrawEffect_SpawnDirect(void *fn);
extern void Effect_ExplosionPiece_Update(void);
extern float Rand_RangeFloat(float lo, float hi);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int flag);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void Item_DecayVelocityScalar(void *self, float k);
extern Vec3 lbl_80332508;
extern const double lbl_806D6C88;
extern const double lbl_806D6C90;

static inline float Item_sqrtf(float x)
{
    static const double _half = 0.5;
    static const double _three = 3.0;
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = _half * guess * (_three - x * (guess * guess));
        guess = _half * guess * (_three - x * (guess * guess));
        guess = _half * guess * (_three - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

static inline void PlaySE(unsigned char *self)
{
    Vec3 sePos;
    sePos = *(Vec3 *)(self + 0xA0);
    SoundMgr_PlaySE_Positional(0x87, &sePos, 0);
}

static inline void ApplyKartTransform(unsigned char *self, unsigned char *sub)
{
    float m2[4][4];
    Mtx_TransposeToMtx44(m2, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9C)));
    Mtx44_TransformVec3(self + 0xA0, m2, *(Vec3 *)(sub + 0x34));
}

void fn_8011AD98(unsigned char *self, unsigned char *sub)
{
    Vec3 tgt = lbl_80332508;
    float m[4][4];
    float l1;
    float l2;
    float s;
    float yaw;
    float yaw2;
    int i;
    unsigned char *e;

    switch ((signed char)self[0xC9]) {
    case 0:
        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
        *(float *)(sub + 0x14) = 0.0f;
        Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9C)));
        Mtx44_Inverse_GaussJordan(m, m);
        Mtx44_TransformVec3(sub + 0x34, m, *(Vec3 *)(self + 0xA0));
        self[0xC9]++;
    case 1:
        *(float *)(sub + 0x14) += 0.1f;
        l1 = Item_sqrtf(*(float *)(sub + 0x34) * *(float *)(sub + 0x34) + *(float *)(sub + 0x3C) * *(float *)(sub + 0x3C));
        l2 = Item_sqrtf(tgt.x * tgt.x + tgt.z * tgt.z);
        s = l2 * *(float *)(sub + 0x14) + l1 * (1.0f - *(float *)(sub + 0x14));
        *(float *)(sub + 0x34) = s * (*(float *)(sub + 0x34) / l1);
        *(float *)(sub + 0x3C) = s * (*(float *)(sub + 0x3C) / l1);
        yaw = Vec3_ToYaw(sub + 0x34);
        yaw2 = Vec3_ToYaw(&tgt);
        Vec2_RotateY(sub + 0x34, sub + 0x34,
                     (yaw2 * *(float *)(sub + 0x14) + yaw * (1.0f - *(float *)(sub + 0x14))) - yaw);
        *(float *)(sub + 0x38) = tgt.y * *(float *)(sub + 0x14) + *(float *)(sub + 0x38) * (1.0f - *(float *)(sub + 0x14));
        if (1.0f < *(float *)(sub + 0x14)) {
            *(float *)(sub + 0x14) = 1.0f;
            Vec3_Copy(sub + 0x34, &tgt);
            *(unsigned int *)(sub + 0x4) = 20;
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 9, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 5.0f);
            self[0xC9]++;
        }
        break;
    case 2:
        if (*(unsigned int *)(sub + 0x4) == 0) {
            *(unsigned int *)(sub + 0x4) = 5;
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
            self[0xC9]++;
        }
        break;
    case 3:
        *(float *)(sub + 0x3C) = *(float *)(sub + 0x3C) - 2.0f;
        *(float *)(sub + 0x38) = *(float *)(sub + 0x38) - 1.0f;
        if (*(unsigned int *)(sub + 0x4) == 0) {
            ItemHit_Dispatch(self, 0, self + 0xA0, *(void **)(sub + 0x9C));
            for (i = 0; i < 6; i++) {
                e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
                if (e) {
                    Vec3_Copy(e + 0x8C, self + 0xA0);
                    GetSpawnPosition(e + 0xA4, 0.0f, 0.0f, 0.6f * Rand_RangeFloat(0.7f, 1.3f));
                    Vec2_RotateX(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-1.8e+02f, 1.8e+02f));
                    Vec2_RotateY(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-1.8e+02f, 1.8e+02f));
                    e[0x190] = 1;
                    e[0x191] = 2;
                    e[0x192] = 1;
                    *(int *)(e + 0x11C) = *(int *)(sub + 0x9C);
                    GetSpawnPosition(e + 0x120, 1.0f, 1.0f, 1.0f);
                    e[0x193] = 1;
                }
            }
            PlaySE(self);
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
        break;
    }
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x9C))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    ApplyKartTransform(self, sub);
    Item_DecayVelocityScalar(self, 1.5f);
}
