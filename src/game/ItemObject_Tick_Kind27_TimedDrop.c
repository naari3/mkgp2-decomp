/* ItemObject_Tick_Kind27_TimedDrop (0x800E0DE4): item that circles the
 * kart for two turns, spiralling outward and then back in, with a bob
 * that dips lower on the last turn. It spawns an orbit spark at the start,
 * then fades out. */
typedef struct Vec { float x, y, z; } Vec;

extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern float Vec3_HorizontalMagnitude(const Vec *v);
extern void Vec3_ScaleXZ(Vec *out, const Vec *in, float s);
extern void Vec2_RotateY(Vec *out, const Vec *in, float angle);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern float BuildOrientationFromYaw(float yaw);
extern float FAbs_FloatAsDouble(float x);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern float Mtx44_GetYawOfPosZ(float m[4][4]);
extern float AngleStepTowards_Shortest(float current, float target, float step);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_KartOrbitSpark_Update(unsigned char *self);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define SF(o) (*(float *)(sub + (o)))
#define SU32(o) (*(unsigned int *)(sub + (o)))
#define SP(o) (*(unsigned char **)(sub + (o)))
#define SV(o) ((Vec *)(sub + (o)))

void ItemObject_Tick_Kind27_TimedDrop(unsigned char *self, unsigned char *sub)
{
    float root[4][4];
    Vec v;
    Vec local;
    float h;
    unsigned char *e;

    switch (S8(0xC9)) {
    case 0:
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
        SF(0x14) = 0.0f;
        SU32(0x4) = 0;
        S8(0xC9)++;
    case 1:
        if (6.283184f < SF(0x14)) {
            SF(0x14) -= 6.283184f;
            S8(0xC9)++;
        }
        break;
    case 2:
        if (6.283184f < SF(0x14)) {
            S8(0xC9)++;
        }
        break;
    case 3:
        F(0x2C) -= 0.1f;
        if (F(0x2C) < 0.0f) {
            self[0x28] = 0;
            S8(0xC8) = 3;
            S8(0xC9) = 0;
            return;
        }
        break;
    }

    SF(0x38) += 0.15f;
    h = Vec3_HorizontalMagnitude(SV(0x34));
    Vec3_ScaleXZ(SV(0x34), SV(0x34), 1.0f / h);
    {
        Vec *p;
        if ((int)self[0xC9] == 1) {
            h += 0.15f;
        } else {
            h -= 0.1f;
        }
        p = SV(0x34);
        Vec3_ScaleXZ(p, p, h);
    }
    Vec2_RotateY(SV(0x34), SV(0x34), 0.17453289f);
    SF(0x14) += 0.17453289f;
    if (SP(0x98) != 0) {
        Vec3_Copy(&v, SV(0x34));
        if ((int)self[0xC9] != 3) {
            v.y = -10.0f * (FAbs_FloatAsDouble(BuildOrientationFromYaw(SF(0x14))) / 3.141592f) + v.y;
        } else {
            v.y = 5.0f * (FAbs_FloatAsDouble(BuildOrientationFromYaw(SF(0x14))) / 3.141592f) + v.y;
        }
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(SP(0x98)));
        local = v;
        Mtx44_TransformVec3((Vec *)(self + 0xA0), root, &local);
    }
    if (SP(0x98) != 0) {
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(SP(0x98)));
        F(0xB0) = AngleStepTowards_Shortest(F(0xB0), BuildOrientationFromYaw(1.570796f + (SF(0x14) + Mtx44_GetYawOfPosZ(root))), 1.570796f);
    }
    if (SU32(0x4) == 0) {
        e = DrawEffect_SpawnDirect(Effect_KartOrbitSpark_Update);
        if (e != 0) {
            Vec3_Copy((Vec *)(e + 0x8C), (Vec *)(self + 0xA0));
            *(void **)(e + 0x11C) = SP(0x98);
        }
        SU32(0x4) = 2;
    }
    if (FinalLapCoinJump_CheckActiveForObject(SP(0x98))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
}
