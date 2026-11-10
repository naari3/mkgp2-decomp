/* DrawEffect_ItemHitBurst_Spawn (0x800CBBD4): debris burst when an item
 * hits the ground near the camera. Ground types 1..3 throw explosion
 * pieces tinted per ground type; types 4..5 throw spark tiers, and type 4
 * also leaves a timed smoke ring. `strength` (1..3) sets the piece count
 * and the angular spread. Pieces fan out on the local ground slope. */
#include "game/DrawEffectAccess.h"

extern unsigned char lbl_805DF3D0[];
Vec DrawEffect_KartDustRing_Update_data_8041A4D0 = { 1.0f, 1.0f, 1.0f };
Vec DrawEffect_ItemHitOriented_Spawn_data_8041A4DC = { 1.0f, 1.0f, 0.9f };
Vec DrawEffect_ItemHitOriented_Spawn_data_8041A4E8 = { 0.65f, 0.55f, 0.25f };
extern float fn_800D3184(const Vec *a, const Vec *b);
extern signed char ItemObject_GetGroundTypeAt(Vec *pos, float *outGroundY, int mode);
extern float Item_ProbeForwardGroundPitch(Vec *pos, float a, float b, float c);
extern float Item_ProbeLateralGroundPitch(Vec *pos, float a, float b, float c);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float angle);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float angle);
extern float FAbs_FloatAsDouble(float x);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void Effect_ExplosionPiece_Update(unsigned char *self);
extern void DrawEffect_KartSparkTier_Update(unsigned char *self);
extern void DrawEffect_SmokeRingTimed_Update(unsigned char *self);

static inline void SpawnGroundBurst(Vec *pos, float m[4][4], signed char strength,
                                    signed char ground, float speed)
{
    unsigned char *self;
    Vec local;
    int count;
    int i;
    float yaw;
    float spread;
    switch (strength) {
    case 1:
        count = 2;
        break;
    case 2:
        count = 4;
        break;
    case 3:
        count = 8;
        break;
    }
    yaw = 0.017453289f * Rand_RangeFloat(-1.8e+02f, 1.8e+02f);
    spread = 0.5f * speed;
    for (i = 0; i < count; i++) {
        self = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
        if (self != 0) {
            Vec3_Copy(V(0x8C), pos);
            F(0x90) += 1.5f;
            GetSpawnPosition(V(0xA4), 0.0f, 0.0f,
                             spread * Rand_RangeFloat(0.8f, 1.2f));
            Vec2_RotateY(V(0xA4), V(0xA4),
                         BuildOrientationFromYaw(0.017453289f * Rand_RangeFloat(-15.0f, 15.0f) + yaw));
            local = *V(0xA4);
            Mtx44_TransformVec3(V(0xA4), m, &local);
            switch (strength) {
            case 1:
                S8(0x191) = 1;
                break;
            case 2:
                S8(0x191) = 1;
                break;
            case 3:
                S8(0x191) = 2;
                break;
            }
            S8(0x193) = 2;
            switch (ground) {
            case 1:
                Vec3_Copy(V(0x120), &DrawEffect_KartDustRing_Update_data_8041A4D0);
                break;
            case 2:
                Vec3_Copy(V(0x120), &DrawEffect_ItemHitOriented_Spawn_data_8041A4DC);
                break;
            case 3:
                Vec3_Copy(V(0x120), &DrawEffect_ItemHitOriented_Spawn_data_8041A4E8);
                break;
            }
        }
        switch (strength) {
        case 1:
            yaw = BuildOrientationFromYaw(3.141592f + yaw);
            break;
        case 2:
            yaw = BuildOrientationFromYaw(1.570796f + yaw);
            break;
        case 3:
            yaw = BuildOrientationFromYaw(0.785398f + yaw);
            break;
        }
    }
}

static inline void SpawnGroundSparks(Vec *pos, float m[4][4], signed char strength,
                                     signed char ground, float speed)
{
    unsigned char *self;
    Vec local2;
    int count;
    int i;
    float yaw;
    float spread;
    switch (strength) {
    case 1:
        count = 4;
        break;
    case 2:
        count = 8;
        break;
    case 3:
        count = 8;
        break;
    }
    yaw = 0.017453289f * Rand_RangeFloat(-1.8e+02f, 1.8e+02f);
    spread = 0.5f * speed;
    for (i = 0; i < count; i++) {
        self = DrawEffect_SpawnDirect(DrawEffect_KartSparkTier_Update);
        if (self != 0) {
            Vec3_Copy(V(0x8C), pos);
            GetSpawnPosition(V(0xA4), 0.0f, 0.0f,
                             spread * Rand_RangeFloat(0.8f, 1.2f));
            Vec2_RotateX(V(0xA4), V(0xA4), -0.785398f);
            Vec2_RotateY(V(0xA4), V(0xA4),
                         BuildOrientationFromYaw(0.017453289f * Rand_RangeFloat(-15.0f, 15.0f) + yaw));
            local2 = *V(0xA4);
            Mtx44_TransformVec3(V(0xA4), m, &local2);
            S8(0x190) = strength;
            S8(0x191) = ground;
        }
        switch (strength) {
        case 1:
            yaw = BuildOrientationFromYaw(1.570796f + yaw);
            break;
        case 2:
            yaw = BuildOrientationFromYaw(0.785398f + yaw);
            break;
        case 3:
            yaw = BuildOrientationFromYaw(0.785398f + yaw);
            break;
        }
    }
    if (ground == 4) {
        self = DrawEffect_SpawnDirect(DrawEffect_SmokeRingTimed_Update);
        if (self != 0) {
            Vec3_Copy(V(0x8C), pos);
            F(0x90) += 1.0f;
            S8(0x190) = strength;
        }
    }
}

void DrawEffect_ItemHitBurst_Spawn(Vec *pos, Vec *vel, signed char strength)
{
    float m[4][4];
    Vec p;
    Vec q;
    Vec a;
    Vec b;
    signed char ground;
    float roll;
    float pitch;
    float speed;

    if (5e+02f < fn_800D3184((Vec *)(lbl_805DF3D0 + 0x80), pos)) {
        return;
    }
    Vec3_Copy(&p, pos);
    q = p;
    ground = ItemObject_GetGroundTypeAt(&q, &p.y, 0);
    if (ground == 0) {
        return;
    }
    a = p;
    pitch = Item_ProbeForwardGroundPitch(&a, 0.0f, 1e+01f, 0.0f);
    b = p;
    roll = Item_ProbeLateralGroundPitch(&b, 0.0f, 1e+01f, 0.0f);
    Matrix4_Identity(m);
    Matrix4_PreMultiplyRotX(m, m, pitch);
    Matrix4_PreMultiplyRotZ(m, m, roll);
    speed = FAbs_FloatAsDouble(vel->y);
    if (speed < 3.0f) {
        speed = 3.0f;
    }
    if (5.0f < speed) {
        speed = 5.0f;
    }
    switch (ground) {
    case 1:
    case 2:
    case 3: {
        SpawnGroundBurst(&p, m, strength, ground, speed);
        break;
    }
    case 4:
    case 5: {
        SpawnGroundSparks(&p, m, strength, ground, speed);
        break;
    }
    }
}
