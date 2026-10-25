/* KartBurstShard_SpawnSet (0x800B1FBC): one-shot DrawEffect callback that
 * spawns a KartFadeInEffect at the parent's translation plus 6 burst shards
 * fanned around Z by the angle table, then frees itself. */
#include "game/DrawEffectAccess.h"

typedef struct ShardAngles { float a[6]; } ShardAngles;

extern const ShardAngles lbl_80329474;
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec in);
extern void KartFadeInEffect_Update(unsigned char *self);
extern void KartBurstShard_Update(unsigned char *self);

void KartBurstShard_SpawnSet(unsigned char *self)
{
    float m[4][4];
    ShardAngles angles;
    Vec pos;
    Vec dir;
    unsigned char *child;
    float *angle;
    int i;

    angles = lbl_80329474;
    Mtx_TransposeToMtx44(m, self + 0x48);
    Mtx44_GetTranslation_ColMajor(&pos, m);
    Matrix4_PreMultiplyTranslation(m, m, -pos.x, -pos.y, -pos.z);

    child = DrawEffect_SpawnDirect(KartFadeInEffect_Update);
    Vec3_Copy(V_(child, 0x8C), &pos);
    *(int *)(child + 0x11C) = I(0x11C);

    angle = angles.a;
    for (i = 0; i < 6; i++) {
        child = DrawEffect_SpawnDirect(KartBurstShard_Update);
        Vec3_Copy(V_(child, 0x8C), &pos);
        GetSpawnPosition(V_(child, 0xA4), 0.0f, Rand_RangeFloat(0.4f, 0.6f), 0.0f);
        Vec2_RotateX(V_(child, 0xA4), V_(child, 0xA4), 0.785398f);
        Vec2_RotateZ(V_(child, 0xA4), V_(child, 0xA4),
                     0.017453289f * (*angle + Rand_RangeFloat(-18.0f, 18.0f)));
        Vec2_RotateY(V_(child, 0xA4), V_(child, 0xA4), -1.570796f);
        dir = *V_(child, 0xA4);
        Mtx44_TransformVec3(V_(child, 0xA4), m, dir);
        *(int *)(child + 0x11C) = I(0x11C);
        angle++;
    }
    DrawEffect_Free(self);
}
