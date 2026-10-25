typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float angle);
extern void Vec2_RotateX(Vec3 *out, const Vec3 *in, float angle);
extern signed char ItemObject_GetGroundTypeAt(Vec3 pos, float *outGroundY, int mode);
extern void Vec3_Add_DestFirst(Vec3 *dst, const Vec3 *a, const Vec3 *b);
extern void Vec3_Subtract_DestFirst(Vec3 *dst, const Vec3 *a, const Vec3 *b);
extern float Vec3_Magnitude_Wrapper(const Vec3 *v);
extern void Vec3_Scale(Vec3 *dst, const Vec3 *src, float scale);
extern double Vec3_ToYaw(const Vec3 *v);

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
    {
        double d = Vec3_ToYaw(vel);
        groundY = d;
        Vec2_RotateY(vel, vel, -(float)d);
    }
    Vec2_RotateX(vel, vel, pitch);
    Vec2_RotateY(vel, vel, groundY);
}
