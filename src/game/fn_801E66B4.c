struct AICollisionDriver;
typedef struct AICollisionStatus {
    char pad[8];
    struct AICollisionDriver *target;
    char padC[4];
    unsigned long long flags;
} AICollisionStatus;
typedef struct AICollisionDriver {
    char pad[0x304];
    AICollisionStatus *status;
} AICollisionDriver;
typedef struct AICollisionController {
    char pad[0x10];
    AICollisionDriver *driver;
    char pad14[0x14];
    void *effect;
    char pad2C[4];
    float x, y, z;
} AICollisionController;
extern float *KartDriver_GetKartRootMtx(AICollisionDriver *);
extern void fn_801DF24C(void *, int);
extern const float lbl_806DA388, lbl_806DA38C, lbl_806DA3B0, lbl_806DA3B4;
extern const double lbl_806DA3A0, lbl_806DA3A8;
static inline unsigned char HasFlag(unsigned long long flags, unsigned long long mask) {
    if ((flags & mask) == 0) return 0;
    return 1;
}
static inline float Length(float value) {
    volatile float result;
    if (value > lbl_806DA388) {
        double estimate = __frsqrte(value);
        estimate = lbl_806DA3A0 * estimate * (lbl_806DA3A8 - value * (estimate * estimate));
        estimate = lbl_806DA3A0 * estimate * (lbl_806DA3A8 - value * (estimate * estimate));
        estimate = lbl_806DA3A0 * estimate * (lbl_806DA3A8 - value * (estimate * estimate));
        result = value * estimate;
        return result;
    }
    return value;
}
/* Matches with common-subexpression elimination off: the driver pointer is
 * kept in a local while its status pointer is re-read for the store. */
#pragma opt_common_subs off
int fn_801E66B4(AICollisionController *self, AICollisionDriver *other) {
    AICollisionStatus *status;
    float *m;
    float dx, dy, dz;
    float distance, strength;
    AICollisionDriver *drv;
    if (!other) return 0;
    status = other->status;
    drv = self->driver;
    if (HasFlag(drv->status->flags, 0x80) == 1) return 0;
    if (HasFlag(status->flags, 0x80) == 1) return 0;
    drv->status->target = other;
    m = KartDriver_GetKartRootMtx(other);
    dx = m[3] - self->x;
    dy = m[7] - self->y;
    dz = m[11] - self->z;
    distance = Length(dx * dx + dy * dy + dz * dz);
    dx /= distance; dy /= distance; dz /= distance;
    dx *= lbl_806DA3B0; dy *= lbl_806DA3B0; dz *= lbl_806DA3B0;
    strength = lbl_806DA38C * (lbl_806DA3B4 - distance);
    dx *= strength; dy *= strength; dz *= strength;
    self->x += dx; self->y += dy; self->z += dz;
    if (((status->flags & 0x20000000) != 0)) fn_801DF24C(self->effect, 2);
    return 1;
}
#pragma opt_common_subs reset
