/* BombExplosion_UpdateShockwaveVfx (0x800FBD88): places the bomb blast.
 * The blast hits drivers in two growing radii around the explosion matrix,
 * then four effects are laid out along the blast's reach: the flash at the
 * centre, a wall splash where a wall cuts the reach short, and two ground
 * shockwave rings, each tilted to the ground and faded with the distance. */
typedef struct Vec { float x, y, z; } Vec;

extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern float Mtx44_GetYawOfPosZ(float m[4][4]);
extern float Mtx44_GetPitchOfPosZ(float m[4][4]);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Mtx44_TransformVec3(void *out, float m[4][4], Vec v);
extern float KartFxParam_GetConst1p5(void *driver);
extern void Item_PropagateHitToDriversInRadius(unsigned char *self, void *kart);
extern void Mtx_Copy(void *dst, const void *src);
extern void Mtx44_GetTranslation_RowMajor(void *out, void *mtx);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void VfxSlot_TickAnim(void *slot, int step);
extern float Vec3_HorizontalDistance(const Vec *a, const void *b);
extern void Vec3_Copy(void *dst, const void *src);
extern unsigned char ItemObject_RaycastWallStub(Vec from, Vec to, Vec *hit, Vec *normal);
extern void Vec3_Subtract_DestFirst(void *dst, const void *a, const void *b);
extern void Vec3_Scale(Vec *out, const Vec *in, float s);
extern void Vec3_ScaleXZ(Vec *out, const Vec *in, float s);
extern void Vec3_Add_DestFirst(void *dst, const void *a, const void *b);
extern float Vec3_ToYaw(const Vec *v);
extern void Vec2_RotateY(Vec *out, const Vec *in, float a);
extern float BuildOrientationFromYaw(float yaw);
extern float FAbs_FloatAsDouble(float x);
extern double atan2(double y, double x);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_PerAxis(float dst[4][4], float src[4][4], float x, float y, float z);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float a);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec t);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern signed char ItemObject_GetGroundTypeAt(Vec pos, float *outGroundY, int mode);
extern float Item_ProbeForwardGroundPitch(Vec pos, float yaw, float a, float b);
extern float Item_ProbeLateralGroundPitch(Vec pos, float yaw, float a, float b);

#define F(o) (*(float *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))
#define EF(o) (*(float *)(e + (o)))

static inline float Bomb_Scale(unsigned char *self)
{
    return 1.5f * KartFxParam_GetConst1p5(P(0x184));
}

void BombExplosion_UpdateShockwaveVfx(unsigned char *self, void *mtx)
{
    float m[4][4];
    float m2[4][4];
    float m3[4][4];
    float m4[4][4];
    Vec ctr;
    Vec hit;
    Vec nrm;
    Vec d;
    Vec rel;
    Vec p;
    Vec dd;
    unsigned char *e;
    int blocked;
    float dist;
    float reach;
    float sx;
    float t;
    float lim;
    float h;
    float r;
    float sy;
    float gy;
    float gy2;

    if (self == 0) {
        return;
    }
    Mtx_TransposeToMtx44(m, mtx);
    Mtx44_GetTranslation_ColMajor(&ctr, m);
    F(0xB0) = Mtx44_GetYawOfPosZ(m);
    F(0xAC) = Mtx44_GetPitchOfPosZ(m);
    GetSpawnPosition(self + 0xA0, 0.0f, 0.0f, 25.0f);
    Mtx44_TransformVec3(self + 0xA0, m, *(Vec *)(self + 0xA0));
    F(0xC4) = 10.0f * Bomb_Scale(self);
    Item_PropagateHitToDriversInRadius(self, P(0x184));
    GetSpawnPosition(self + 0xA0, 0.0f, 0.0f, 50.0f);
    Mtx44_TransformVec3(self + 0xA0, m, *(Vec *)(self + 0xA0));
    F(0xC4) = 15.0f * Bomb_Scale(self);
    Item_PropagateHitToDriversInRadius(self, P(0x184));

    e = P(0x138);
    if (e != 0) {
        Mtx_Copy(e + 0x48, mtx);
        Mtx44_GetTranslation_RowMajor(e + 0x8C, e + 0x48);
        EF(0xB0) = Bomb_Scale(self);
        e[0x28] = 1;
        if (FinalLapCoinJump_CheckActiveForObject(P(0x184))) {
            e[0x28] = 0;
        } else {
            e[0x28] = 1;
        }
        VfxSlot_TickAnim(e + 0x14, 1);
    }

    dist = Vec3_HorizontalDistance(&ctr, self + 0xA0);
    reach = dist;
    Vec3_Copy(&hit, self + 0xA0);
    blocked = ItemObject_RaycastWallStub(ctr, *(Vec *)(self + 0xA0), &hit, &nrm);
    if (blocked) {
        Vec3_Subtract_DestFirst(&d, self + 0xA0, &ctr);
        Vec3_Scale(&d, &d, (1.0f / dist) * Vec3_HorizontalDistance(&ctr, &hit));
        Vec3_Add_DestFirst(&hit, &ctr, &d);
        GetSpawnPosition(&d, 0.0f, 0.0f, -1.0f);
        Vec2_RotateY(&d, &d, Vec3_ToYaw(&nrm));
        Vec3_Add_DestFirst(&hit, &hit, &d);
        reach = Vec3_HorizontalDistance(&ctr, &hit);
    }

    e = P(0x13C);
    if (e != 0) {
        if (blocked) {
            Vec3_Copy(e + 0x8C, &hit);
            EF(0x9C) = BuildOrientationFromYaw(3.141592f + Vec3_ToYaw(&nrm));
            EF(0xB0) = reach / dist;
            if (EF(0xB0) < 0.2f) {
                EF(0xB0) = 0.2f;
            }
            if (1.0f < EF(0xB0)) {
                EF(0xB0) = 1.0f;
            }
            EF(0xB0) *= 0.2f * F(0xC4);
            EF(0x2C) = (dist - reach) / dist;
            if (1.0f < EF(0x2C)) {
                EF(0x2C) = 1.0f;
            }
            sx = 3.0f * (FAbs_FloatAsDouble(BuildOrientationFromYaw(F(0xB0) - Vec3_ToYaw(&nrm))) / 1.570796f) + 1.0f;
            Vec3_Subtract_DestFirst(&rel, &ctr, e + 0x8C);
            Vec2_RotateY(&rel, &rel, -EF(0x9C));
            EF(0xA0) = atan2(rel.y, rel.x);
            Matrix4_Identity(m2);
            Mtx44_Scale_PerAxis(m2, m2, EF(0xB0) * sx, EF(0xB0), EF(0xB0));
            Matrix4_PreMultiplyRotZ(m2, m2, EF(0xA0));
            Matrix4_PreMultiplyRotY(m2, m2, EF(0x9C));
            Mtx44_Translate(m2, m2, *(Vec *)(e + 0x8C));
            DbgScene_CopyMatrix3x4Transpose(e + 0x48, m2);
            VfxSlot_TickAnim(e + 0x14, 1);
            e[0x28] = 1;
        } else {
            e[0x28] = 0;
        }
    }

    e = P(0x140);
    if (e != 0) {
        if (ItemObject_GetGroundTypeAt(hit, &gy, 0)) {
            t = reach / dist;
            lim = 5.0f * t;
            h = hit.y - gy;
            if (h < lim) {
                Vec3_Copy(e + 0x8C, &hit);
                EF(0x90) = gy;
                EF(0x9C) = F(0xB0);
                EF(0x98) = Item_ProbeForwardGroundPitch(*(Vec *)(e + 0x8C), EF(0x9C), 5.0f, 0.0f);
                EF(0xA0) = Item_ProbeLateralGroundPitch(*(Vec *)(e + 0x8C), EF(0x9C), 5.0f, 0.0f);
                EF(0x90) += 2.0f;
                EF(0xB0) = t * (lim - h) / lim;
                if (EF(0xB0) < 0.2f) {
                    EF(0xB0) = 0.2f;
                }
                if (1.0f < EF(0xB0)) {
                    EF(0xB0) = 1.0f;
                }
                EF(0xB0) *= 0.2f * F(0xC4);
                EF(0x2C) = (dist - reach) / dist;
                if (1.0f < EF(0x2C)) {
                    EF(0x2C) = 1.0f;
                }
                sy = 3.0 * ((0.2617993298918009 - FAbs_FloatAsDouble(BuildOrientationFromYaw(F(0xAC) - EF(0x98)))) / 0.26179933547973633) + 1.0;
                if (4.0f < sy) {
                    sy = 4.0f;
                }
                Matrix4_Identity(m3);
                Matrix4_PreMultiplyRotX(m3, m3, -1.570796f);
                Mtx44_Scale_PerAxis(m3, m3, EF(0xB0), EF(0xB0), EF(0xB0) * sy);
                Matrix4_PreMultiplyRotZ(m3, m3, EF(0xA0));
                Matrix4_PreMultiplyRotX(m3, m3, EF(0x98));
                Matrix4_PreMultiplyRotY(m3, m3, EF(0x9C));
                Mtx44_Translate(m3, m3, *(Vec *)(e + 0x8C));
                DbgScene_CopyMatrix3x4Transpose(e + 0x48, m3);
                e[0x28] = 1;
            } else {
                e[0x28] = 0;
            }
        } else {
            e[0x28] = 0;
        }
    }

    e = P(0x144);
    if (e != 0) {
        r = reach - 5.0f;
        if (0.0f < r) {
            Vec3_Subtract_DestFirst(&dd, &hit, &ctr);
            Vec3_ScaleXZ(&dd, &dd, (1.0f / reach) * r);
            Vec3_Add_DestFirst(&p, &ctr, &dd);
            if (ItemObject_GetGroundTypeAt(p, &gy2, 0)) {
                t = r / dist;
                lim = 5.0f * t;
                h = p.y - gy2;
                if (h < lim) {
                    Vec3_Copy(e + 0x8C, &p);
                    EF(0x90) = gy2;
                    EF(0x9C) = F(0xB0);
                    EF(0x98) = Item_ProbeForwardGroundPitch(*(Vec *)(e + 0x8C), EF(0x9C), 5.0f, 0.0f);
                    EF(0xA0) = Item_ProbeLateralGroundPitch(*(Vec *)(e + 0x8C), EF(0x9C), 5.0f, 0.0f);
                    EF(0x90) += 2.0f;
                    EF(0xB0) = t;
                    if (EF(0xB0) < 0.2f) {
                        EF(0xB0) = 0.2f;
                    }
                    EF(0xB0) *= 0.1f * F(0xC4);
                    EF(0x2C) = (lim - h) / lim;
                    if (1.0f < EF(0x2C)) {
                        EF(0x2C) = 1.0f;
                    }
                    sy = 3.0 * ((0.2617993298918009 - FAbs_FloatAsDouble(BuildOrientationFromYaw(F(0xAC) - EF(0x98)))) / 0.26179933547973633) + 1.0;
                    if (4.0f < sy) {
                        sy = 4.0f;
                    }
                    Matrix4_Identity(m4);
                    Matrix4_PreMultiplyRotX(m4, m4, -1.570796f);
                    Mtx44_Scale_PerAxis(m4, m4, EF(0xB0), EF(0xB0), EF(0xB0) * sy);
                    Matrix4_PreMultiplyRotZ(m4, m4, EF(0xA0));
                    Matrix4_PreMultiplyRotX(m4, m4, EF(0x98));
                    Matrix4_PreMultiplyRotY(m4, m4, EF(0x9C));
                    Mtx44_Translate(m4, m4, *(Vec *)(e + 0x8C));
                    DbgScene_CopyMatrix3x4Transpose(e + 0x48, m4);
                    e[0x28] = 1;
                } else {
                    e[0x28] = 0;
                }
            } else {
                e[0x28] = 0;
            }
        }
    }
}
