/* ItemObject_TryAcquireTarget (0x800A4F64): homing lock-on test. The target
 * must be free, within maxDist and inside +-halfAngle degrees of the item's
 * heading. Karts of kinds 0..3 owned by `owner` win outright; otherwise the
 * nearest candidate wins. */
#include "game/MathInline.h"

typedef struct LockTarget {
    int kind;
    unsigned char pad04[4];
    int busy;
    unsigned char pad0C[0x68];
    Vec3f pos;
    unsigned char pad80[0x14];
    int owner;
    int lockCount;
    unsigned char pad9C[0x18];
    int team;
} LockTarget;

typedef struct LockSeeker {
    unsigned char pad00[0x10];
    float mtx[3][4];
    unsigned char pad40[0x34];
    Vec3f pos;
    unsigned char pad80[0x10];
    int targetId;
    unsigned char pad94[0x8];
    LockTarget *target;
    float targetDist;
    unsigned char padA4[0x14];
    int targetTeam;
} LockSeeker;

extern const float lbl_806D4868; /* 0.0 */
extern const float lbl_806D489C; /* 180.0 */
extern const float lbl_806D48A0; /* 3.1415 */
extern const float lbl_806D48A4; /* -1.0 */
extern const float lbl_806D48A8; /* 90.0 */
extern const float lbl_806D48AC; /* -90.0 */
extern void PSMTXMultVec(float mtx[3][4], const Vec3f *in, Vec3f *out);
extern double atan2(double y, double x);

int ItemObject_TryAcquireTarget(LockSeeker *self, float maxDist, float halfAngle, int owner, int id,
                                LockTarget *target)
{
    Vec3f d;
    Vec3f local;
    float dist;
    float angle;

    d.x = target->pos.x - self->pos.x;
    d.y = target->pos.y - self->pos.y;
    d.z = target->pos.z - self->pos.z;
    dist = MathInline_sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
    PSMTXMultVec(self->mtx, &d, &local);
    angle = lbl_806D489C * (float)atan2(local.z, local.x) / lbl_806D48A0;
    if (angle < lbl_806D48AC) {
        angle *= lbl_806D48A4;
    } else {
        angle -= lbl_806D48A8;
    }

    if (target->busy != 0) {
        return 0;
    }
    if (maxDist < dist) {
        return 0;
    }
    if (angle < -halfAngle || halfAngle < angle) {
        return 0;
    }
    if (target->kind >= 0 && target->kind <= 3 && target->owner == owner) {
        self->targetId = id;
        self->targetDist = lbl_806D4868;
        target->lockCount++;
    } else {
        if (self->targetDist < dist) {
            return 0;
        }
        self->targetId = id;
        self->targetDist = dist;
        target->lockCount++;
    }
    self->target = target;
    self->targetTeam = target->team;
    return 1;
}
