typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct RaceContextSlot {
    unsigned int kind;           /* 0x00 */
    unsigned char pad04[0xB4 - 0x04];
    void *driver;                /* 0xB4 */
} RaceContextSlot;

extern void *GetRaceContextPtr(void);
extern RaceContextSlot *RaceContextSlot_GetIfAlive(void *ctx, int idx);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *out, void *mtx);
extern float Vec3_HorizontalYawTo(const Vec3 *from, const Vec3 *to);
extern float BuildOrientationFromYaw(float yaw);
extern float FAbs_FloatAsDouble(float x);
extern float Vec3_HorizontalDistance(const Vec3 *a, const Vec3 *b);

void *FindNearestDriverWithinConeAndRadius(const Vec3 *pos, void *exclude, int byDistance,
                                           float yaw, float cone, float radius)
{
    void *best = 0;
    float bestAngle;
    float bestDist;
    Vec3 p;
    int i;

    for (i = 0; i < 0x80; i++) {
        RaceContextSlot *slot = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), i);
        if (slot != 0 && (slot->kind <= 3 || (int)slot->kind == 6)) {
            void *driver = slot->driver;
            float angle;
            float dist;

            if (exclude != 0 && exclude == driver) {
                continue;
            }
            Mtx44_GetTranslation_RowMajor(&p, KartDriver_GetKartRootMtx(driver));
            angle = FAbs_FloatAsDouble(BuildOrientationFromYaw(Vec3_HorizontalYawTo(pos, &p) - yaw));
            dist = Vec3_HorizontalDistance(pos, &p);
            if (angle < cone && dist < radius) {
                if (best == 0 || (byDistance == 0 && angle < bestAngle) ||
                    (byDistance != 0 && dist < bestDist)) {
                    bestAngle = angle;
                    best = driver;
                    bestDist = dist;
                }
            }
        }
    }
    return best;
}
