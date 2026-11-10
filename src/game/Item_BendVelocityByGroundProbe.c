#include "game/types/Vec3.h"

extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float angle);
extern void Vec2_RotateX(Vec3 *out, const Vec3 *in, float angle);
extern signed char ItemObject_GetGroundTypeAt(Vec3 pos, float *outGroundY, int mode);
extern void Vec3_Add_DestFirst(Vec3 *dst, const Vec3 *a, const Vec3 *b);
extern void Vec3_Subtract_DestFirst(Vec3 *dst, const Vec3 *a, const Vec3 *b);
extern float Vec3_Magnitude_Wrapper(const Vec3 *v);
extern void Vec3_Scale(Vec3 *dst, const Vec3 *src, float scale);
extern float Vec3_ToYaw(const Vec3 *v);

/* Rotate around the velocity's yaw so pitch bends in its local frame. */
static inline void BendInYawFrame(Vec3 *vel, float pitch, float *yaw)
{
    *yaw = Vec3_ToYaw(vel);
    Vec2_RotateY(vel, vel, -*yaw);
    Vec2_RotateX(vel, vel, pitch);
    Vec2_RotateY(vel, vel, *yaw);
}

void Item_BendVelocityByGroundProbe(Vec3 *vel, const Vec3 *pos, float yaw, float speed, float pitch)
{
    Vec3 probe;
    float groundY;
    float probeY;

    GetSpawnPosition(vel, 0.0f, 0.0f, speed);
    Vec2_RotateY(vel, vel, yaw);
    if (ItemObject_GetGroundTypeAt(*pos, &groundY, 0)) {
        GetSpawnPosition(&probe, 0.0f, 0.0f, 20.0f);
        Vec2_RotateY(&probe, &probe, yaw);
        Vec3_Add_DestFirst(&probe, pos, &probe);
        if (ItemObject_GetGroundTypeAt(probe, &probeY, 0)) {
            groundY = pos->y - groundY;
            probe.y = probeY + groundY;
            Vec3_Subtract_DestFirst(vel, &probe, pos);
            Vec3_Scale(vel, vel, speed * (1.0f / Vec3_Magnitude_Wrapper(vel)));
        }
    }
    BendInYawFrame(vel, pitch, &groundY);
}
