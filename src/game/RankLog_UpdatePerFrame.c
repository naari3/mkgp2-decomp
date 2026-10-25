/* RankLog_UpdatePerFrame (0x800A59F0): per-frame bookkeeping for the
 * player's race stats: frames since the drift/air state last toggled,
 * longest standstill streak, title-grade reset on a new lap section, and
 * which hazard / shortcut zones the kart has passed. */

typedef struct Vec { float x, y, z; } Vec;

typedef struct RenderObj {
    unsigned char pad0[0x23C];
    int airState;
    unsigned char pad240[0x2CC - 0x240];
    int section;
} RenderObj;

extern const float lbl_806D4DC8; /* 0.0 */
extern const float lbl_806D4DCC; /* 0.5 */
extern Vec lbl_80326B24;
extern unsigned char g_raceEnded;
extern int lbl_806CF1F4;  /* previous air state */
extern int lbl_806CF1F8;  /* frames since air-state change, -1 = unset */
extern int lbl_806CF20C;  /* current standstill frames */
extern int g_maxCoins;    /* longest standstill frames */
extern int lbl_806D13F0;  /* previous section */
extern int g_technicalTitleGrade;
extern unsigned int lbl_806D1450; /* hazard zones touched */
extern int lbl_806CF21C;  /* previous hazard zone */
extern int g_hazardPassCount;
extern unsigned char lbl_806D1420;
extern unsigned int lbl_806D1428;
extern int lbl_806D1424;
extern void *GetPlayerCarObject(void);
extern unsigned char IsRaceStarted(void);
extern RenderObj *CarObject_GetRenderObj(void *car);
extern float *KartDriver_GetKartRootMtx(void *driver);
extern float KartItem_GetCurrentSpeedWithBonus(void *car);
extern float KartItem_GetMaxSpeedWithBonus(void *car);
extern float KartMovement_GetVelocityMagnitude(RenderObj *obj);
extern void *fn_80190658(void);
extern int fn_8019032C(void *zones, Vec *pos);
extern void *fn_8016CB44(void);
extern int fn_8016C850(void *zones, Vec *pos);

void RankLog_UpdatePerFrame(void)
{
    int section;
    int air;
    void *car;
    Vec pos;
    float speed;
    float maxSpeed;
    void *zones;

    car = GetPlayerCarObject();
    if (car == 0) {
        return;
    }
    if (IsRaceStarted() != 1) {
        return;
    }
    if (g_raceEnded != 0) {
        return;
    }
    air = CarObject_GetRenderObj(car)->airState;
    section = CarObject_GetRenderObj(car)->section;
    {
        float *m = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(car));
        pos = lbl_80326B24;
        pos.x = m[3];
        pos.y = m[7];
        pos.z = m[11];
    }
    speed = KartItem_GetCurrentSpeedWithBonus(car);
    maxSpeed = KartItem_GetMaxSpeedWithBonus(car);
    if (lbl_806CF1F8 == -1) {
        lbl_806CF1F4 = air;
        lbl_806CF1F8 = 0;
        return;
    }
    if (lbl_806CF1F4 != air) {
        if ((lbl_806CF1F4 != 0 && air == 0) || (lbl_806CF1F4 == 0 && air != 0)) {
            lbl_806CF1F8 = 0;
        }
    }
    if (lbl_806D4DC8 == KartMovement_GetVelocityMagnitude(CarObject_GetRenderObj(car)) && air == 0) {
        lbl_806CF20C++;
        if (lbl_806CF20C > g_maxCoins) {
            g_maxCoins = lbl_806CF20C;
        }
    } else {
        lbl_806CF20C = 0;
    }
    lbl_806CF1F4 = air;
    if (lbl_806CF1F8 < 60) {
        lbl_806CF1F8++;
    }
    if (lbl_806D13F0 != section) {
        if (g_technicalTitleGrade == 2) {
            g_technicalTitleGrade = -1;
        }
        lbl_806D13F0 = section;
    }
    zones = fn_80190658();
    if (zones != 0) {
        int idx = fn_8019032C(zones, &pos);
        if (idx >= 0) {
            if (speed < lbl_806D4DCC * maxSpeed) {
                lbl_806D1450 |= 1 << idx;
            }
        } else if (lbl_806CF21C >= 0 && !(lbl_806D1450 & (1 << lbl_806CF21C))) {
            lbl_806D1450 |= 1 << lbl_806CF21C;
            g_hazardPassCount++;
        }
        lbl_806CF21C = idx;
    }
    zones = fn_8016CB44();
    if (zones != 0 && lbl_806D1420 != 0) {
        int idx = fn_8016C850(zones, &pos);
        if (idx >= 0 && !(lbl_806D1428 & (1 << idx))) {
            lbl_806D1428 |= 1 << idx;
            lbl_806D1424++;
        }
        lbl_806D1420 = 0;
    }
}
