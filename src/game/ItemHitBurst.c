typedef struct BurstVec3 { float x, y, z; } BurstVec3;
typedef struct BurstItem {
    unsigned char pad00[0x9C];
    void *driver;
    BurstVec3 position;
} BurstItem;
typedef struct BurstEffect {
    unsigned char pad00[0x10];
    int state;
    unsigned char pad14[0x78];
    BurstVec3 position;
    unsigned char pad98[0xC];
    BurstVec3 velocity;
    unsigned char padB0[0x1C];
    void *trackedDriver;
    unsigned char padD0[0x4C];
    void *owner;
} BurstEffect;

extern BurstEffect *DrawEffect_SpawnDirect(void (*update)(BurstEffect *));
extern void Effect_DustScatter_Update(BurstEffect *);
extern void Effect_HitFlash_Update(BurstEffect *);
extern void Vec3_Copy(BurstVec3 *, const BurstVec3 *);
extern void GetSpawnPosition(BurstVec3 *, float, float, float);
extern void Vec2_RotateX(BurstVec3 *, const BurstVec3 *, float);
extern void Vec2_RotateY(BurstVec3 *, const BurstVec3 *, float);
extern float BuildOrientationFromYaw(float);
extern float Rand_RangeFloat(float, float);
extern const float lbl_806D63F8, lbl_806D63FC, lbl_806D6400;
extern const float lbl_806D6404, lbl_806D6408, lbl_806D640C;
extern const float lbl_806D6410, lbl_806D6414, lbl_806D6418, lbl_806D641C;

void Item_SpawnHitBurstParticles(BurstItem *item, BurstItem *other, signed char kind, float yaw) {
    BurstEffect *effect;
    int signedKind;
    int count = 1;
    int i;
    BurstVec3 velocity;

    if (kind != 3) count = 5;
    signedKind = kind;
    for (i = 0; i < count; i++) {
        if (signedKind != 2) {
            effect = DrawEffect_SpawnDirect(Effect_DustScatter_Update);
        } else {
            effect = DrawEffect_SpawnDirect(Effect_HitFlash_Update);
        }
        if (effect != 0) {
            float z;
            effect->state = 2;
            Vec3_Copy(&effect->position, &item->position);
            z = Rand_RangeFloat(lbl_806D63FC, lbl_806D6400);
            GetSpawnPosition(&velocity, lbl_806D63F8, lbl_806D63F8, z);
            switch (signedKind) {
            case 0:
            case 3:
                Vec2_RotateX(&velocity, &velocity, lbl_806D6404 * Rand_RangeFloat(lbl_806D6408, lbl_806D640C));
                Vec2_RotateY(&velocity, &velocity, lbl_806D6404 * Rand_RangeFloat(lbl_806D6410, lbl_806D6414));
                break;
            case 1:
                Vec2_RotateX(&velocity, &velocity, lbl_806D6404 * Rand_RangeFloat(lbl_806D6408, lbl_806D640C));
                Vec2_RotateY(&velocity, &velocity, BuildOrientationFromYaw(yaw + lbl_806D6404 * Rand_RangeFloat(lbl_806D6418, lbl_806D641C)));
                break;
            case 2:
                GetSpawnPosition(&velocity, lbl_806D63F8, lbl_806D63F8, lbl_806D63F8);
                break;
            }
            Vec3_Copy(&effect->velocity, &velocity);
            effect->owner = other->driver;
            if (kind == 2) effect->trackedDriver = item->driver;
        }
    }
}
