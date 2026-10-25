/* Boomerang_ReturnAndAcquireTargetTick (0x800FEE8C): boomerang homing
 * state machine. State 1 picks the nearest racer within 300 units, state 2
 * turns toward it (5 deg/frame) until within 100 units or 30 frames, then
 * swings back (10 deg/frame) until the tracker reports the return. */
#include "game/DrawEffectAccess.h"

typedef struct RaceSlot {
    int type;
    unsigned char pad4[0xB4 - 4];
    unsigned char *kart;
} RaceSlot;

extern const float lbl_806D6478; /* 0.0 */
extern const float lbl_806D647C; /* 300.0 */
extern const float lbl_806D6480; /* 5 deg */
extern const float lbl_806D6484; /* 100.0 */
extern const float lbl_806D6488; /* 10 deg */
extern void *GetRaceContextPtr(void);
extern RaceSlot *RaceContextSlot_GetIfAlive(void *ctx, int idx);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern float Mtx44_GetYawOfPosZ(float m[4][4]);
extern float Vec3_HorizontalYawTo(const Vec *from, const Vec *to);
extern float Vec3_HorizontalDistance(const Vec *a, const Vec *b);
extern float AngleStepTowards_Shortest(float cur, float target, float step);
extern void ItemTracker_SetTrackPhase(unsigned char *item, int phase);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);

void Boomerang_ReturnAndAcquireTargetTick(unsigned char *kart, unsigned char *item)
{
    unsigned char *self = *(unsigned char **)(item + 0x5C);
    float bestDist;

    if (self == 0) {
        return;
    }
    switch (U8(0xEC)) {
    case 0:
        SpriteSlot_SetAnimFrameAndApplyScale(SLOT(self), 1, lbl_806D6478);
        U8(0xEC)++;
        U8(0xED) = 0;
    case 1: {
        int i;

        switch (U8(0xED)) {
        case 0:
            P(0x188) = 0;
            U8(0xED)++;
        case 1:
            for (i = 0; i < 0x80; i++) {
                RaceSlot *slot = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), i);
                if (slot != 0 && (slot->type == 0 || (unsigned int)(slot->type - 1) <= 2 || slot->type == 6)) {
                    float m[4][4];
                    Vec pos;
                    float yaw;
                    float dist;

                    kart = slot->kart;
                    Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(kart));
                    Mtx44_GetTranslation_ColMajor(&pos, m);
                    yaw = Mtx44_GetYawOfPosZ(m);
                    BuildOrientationFromYaw(Vec3_HorizontalYawTo(&pos, V(0xA0)) - yaw);
                    dist = Vec3_HorizontalDistance(V(0xA0), &pos);
                    if (dist < lbl_806D647C && (P(0x188) == 0 || dist < bestDist)) {
                        P(0x188) = kart;
                        bestDist = dist;
                    }
                }
            }
            if (P(0x188) != 0) {
                U8(0xEC)++;
                U8(0xED) = 0;
            }
            break;
        }
        break;
    }
    case 2: {
        Vec target;
        float dist;
        float yaw;

        Mtx44_GetTranslation_RowMajor(&target, KartDriver_GetKartRootMtx(P(0x188)));
        dist = Vec3_HorizontalDistance(V(0xA0), &target);
        yaw = Vec3_HorizontalYawTo(V(0xA0), &target);
        switch (U8(0xED)) {
        case 0:
            U32(0xF0) = 30;
            U8(0xED)++;
        case 1:
            F(0xB0) = AngleStepTowards_Shortest(F(0xB0), yaw, lbl_806D6480);
            if (dist < lbl_806D6484) {
                SpriteSlot_SetAnimFrameAndApplyScale(SLOT(self), 2, lbl_806D6478);
                ItemTracker_SetTrackPhase(self, 1);
                SoundMgr_PlaySE_Positional(0xAF, *V_(kart, 0xA0), 0);
                U8(0xED)++;
            } else if (lbl_806D647C < dist || U32(0xF0) == 0) {
                U8(0xEC) = 1;
                U8(0xED) = 0;
            }
            break;
        case 2:
            F(0xB0) = AngleStepTowards_Shortest(F(0xB0), yaw, lbl_806D6488);
            if ((int)U8(0x1E) == 1) {
                ItemTracker_SetTrackPhase(self, 0);
                U8(0xEC) = 0;
            }
            break;
        }
        break;
    }
    }
}
