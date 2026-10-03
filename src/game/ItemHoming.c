/* Item_HomingScanAndSteer, .text [0x800D9D74, 0x800DA118).
 * Reconstructed from complete target/callee disassembly; Ghidra unavailable.
 * Field 0x168 is a target driver here, not the wall-response mode used by
 * other item helpers. FAbs returns double: retain that precision in the scan.
 * Keep table reads inside each probe iteration and ordered integer Vec3 copies.
 * The complete C draft remains NonMatching: the direct-yaw temporary has one
 * extra fmr, and scan initialization uses li instead of the target's mr.
 */
typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Float3 {
    float value[3];
} Float3;

typedef struct ItemHomingView {
    char pad0[0xA0];
    Vec3 position;
    char padAC[0xC];
    Vec3 velocity;
    char padC4[0xA4];
    void *targetDriver;
    char pad16C[0x18];
    void *ownerDriver;
} ItemHomingView;

typedef struct RaceSlotView {
    int type;
    char pad4[0xB0];
    void *driver;
} RaceSlotView;

extern float Vec3_ToYaw(const Vec3 *v);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *out, const void *matrix);
extern float Vec3_HorizontalYawTo(const Vec3 *from, const Vec3 *to);
extern void GetSpawnPosition(Vec3 *out, float x, float y, float z);
extern void Vec2_RotateY(Vec3 *out, const Vec3 *in, float yaw);
extern void Vec3_Add_DestFirst(Vec3 *out, const Vec3 *a, const Vec3 *b);
extern unsigned char ItemObject_RaycastWallStub(Vec3 *from, Vec3 *to,
                                               Vec3 *hit, Vec3 *normal);
extern float BuildOrientationFromYaw(float yaw);
extern void *GetRaceContextPtr(void);
extern RaceSlotView *RaceContextSlot_GetIfAlive(void *context, int index);
extern double FAbs_FloatAsDouble(float value);
extern float Vec3_HorizontalDistance(const Vec3 *a, const Vec3 *b);
extern Float3 lbl_8032DDC4[];
extern Float3 lbl_8032DDD0[];
extern const float lbl_806D5AC4;
extern float lbl_806D5AC8;
extern const float lbl_806D5B00;
extern const float lbl_806D5B04;
extern const float lbl_806D5B08;
extern const float lbl_806D5B0C;
extern const float lbl_806D5B10;
extern const float lbl_806D5B14;

void Item_HomingScanAndSteer(ItemHomingView *item, float *yaw, int scanEnabled)
{
    Vec3 origin;
    Vec3 avoidTo;
    Vec3 avoidFrom;
    Vec3 scanOrigin;
    Vec3 directTo;
    Vec3 directFrom;
    Float3 turnFactors;
    Float3 probeDistances;
    Vec3 avoidNormal;
    Vec3 avoidHit;
    Vec3 avoidProbe;
    Vec3 directNormal;
    Vec3 directHit;
    Vec3 directProbe;
    Vec3 targetPosition;
    Vec3 candidatePosition;
    float currentYaw;
    float adjustment;

    if (item == 0) {
        return;
    }
    if (yaw != 0) {
        currentYaw = *yaw;
    } else {
        currentYaw = Vec3_ToYaw(&item->velocity);
    }
    origin = item->position;
    if (item->targetDriver != 0) {
        Mtx44_GetTranslation_RowMajor(&targetPosition,
                                     KartDriver_GetKartRootMtx(item->targetDriver));
        {
            float targetYaw = Vec3_HorizontalYawTo(&origin, &targetPosition);
            GetSpawnPosition(&directProbe, lbl_806D5AC8, lbl_806D5AC8, lbl_806D5AC4);
            Vec2_RotateY(&directProbe, &directProbe, targetYaw);
            Vec3_Add_DestFirst(&directProbe, &origin, &directProbe);
            directTo = directProbe;
            directFrom = origin;
            if (ItemObject_RaycastWallStub(&directFrom, &directTo,
                                          &directHit, &directNormal) == 0) {
                adjustment = BuildOrientationFromYaw(targetYaw - currentYaw);
                goto steer;
            }
        }
    } else if (scanEnabled != 0) {
        void *driver;
        int index;
        void *bestDriver;
        void *owner;
        double angle;
        double bestAngle;

        scanOrigin = origin;
        bestDriver = 0;
        index = 0;
        owner = item->ownerDriver;
        for (; index < 128; index++) {
            RaceSlotView *slot = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), index);
            if (slot != 0 && ((unsigned int)slot->type <= 3 || slot->type == 6)) {
                driver = slot->driver;
                if (owner == 0 || owner != driver) {
                    float distance;
                    Mtx44_GetTranslation_RowMajor(&candidatePosition,
                                                 KartDriver_GetKartRootMtx(driver));
                    angle = FAbs_FloatAsDouble(BuildOrientationFromYaw(
                        Vec3_HorizontalYawTo(&scanOrigin, &candidatePosition) - currentYaw));
                    distance = Vec3_HorizontalDistance(&scanOrigin, &candidatePosition);
                    if (angle < lbl_806D5B00 && distance < lbl_806D5B04 &&
                        (bestDriver == 0 || angle < bestAngle)) {
                        bestDriver = driver;
                        bestAngle = angle;
                    }
                }
            }
        }
        item->targetDriver = bestDriver;
    }
    if (item->targetDriver != 0) {
        int index;
        float *probeDistance;
        float *turnFactor;
        probeDistance = probeDistances.value;
        turnFactor = turnFactors.value;
        for (index = 0; index < 3; index++, probeDistance++, turnFactor++) {
            probeDistances = lbl_8032DDC4[0];
            turnFactors = lbl_8032DDD0[0];
            GetSpawnPosition(&avoidProbe, lbl_806D5AC8, lbl_806D5AC8,
                             *probeDistance);
            Vec2_RotateY(&avoidProbe, &avoidProbe, BuildOrientationFromYaw(
                lbl_806D5B08 * (lbl_806D5B0C * *turnFactor) + currentYaw));
            Vec3_Add_DestFirst(&avoidProbe, &origin, &avoidProbe);
            avoidTo = avoidProbe;
            avoidFrom = origin;
            if (ItemObject_RaycastWallStub(&avoidFrom, &avoidTo,
                                          &avoidHit, &avoidNormal) != 0) {
                float relativeYaw;
                currentYaw -= Vec3_ToYaw(&avoidNormal);
                relativeYaw = BuildOrientationFromYaw(currentYaw);
                if (lbl_806D5AC8 < BuildOrientationFromYaw(currentYaw)) {
                    adjustment = BuildOrientationFromYaw(lbl_806D5B10 - relativeYaw);
                } else {
                    adjustment = BuildOrientationFromYaw(lbl_806D5B14 - relativeYaw);
                }
                goto steer;
            }
        }
    }
    adjustment = lbl_806D5AC8;
steer:
    if (adjustment != lbl_806D5AC8) {
        Vec2_RotateY(&item->velocity, &item->velocity, adjustment);
        if (yaw != 0) {
            *yaw = Vec3_ToYaw(&item->velocity);
        }
    }
}
