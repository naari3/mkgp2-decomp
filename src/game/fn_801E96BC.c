#include "game/AIPairPrivate.h"
#include "game/KartMovement.h"
typedef struct AISystemState {
    void *vtable;
    void *car;
    int field08;
    int frame;
} AISystemState;
typedef Vec3 AIVec;
extern AIPairRecord lbl_806793D8[8];
extern int lbl_806D1920;
extern void *g_pathSystem;
extern const float lbl_806DA3E8;
extern const float lbl_806DA3EC;
extern const float lbl_806DA3F0;
extern float *KartDriver_GetKartRootMtx(void *);
extern int Waypoint_FindNearest(void *, int, float, float, float, float);
extern float PSVECSquareDistance(const AIVec *, const AIVec *);

/* Refresh the closest other kart for one tracking record. */
static inline void FindNearestKart(AIPairRecord *record, AIPairRecord *base, const AIVec *pos, AIVec *p) {
    AIPairRecord *other;
    int j;
    float *m;
    j = 0;
    record->nearestKart = -1;
    record->nearestDriver = (void *)j;
    record->distanceSquared = lbl_806DA3EC;
    record->distanceSquared *= record->distanceSquared;
    record->distanceSquared *= lbl_806DA3F0;
    other = base;
    for (; j < 8; ++j, ++other) {
        if (record != other && other->driver) {
            float d;
            float px, py, pz;
            m = KartDriver_GetKartRootMtx(other->driver);
            px = m[3]; py = m[7]; pz = m[11];
            p->x = px; p->y = py; p->z = pz;
            d = PSVECSquareDistance(p, pos);
            if (d < record->distanceSquared) {
                record->distanceSquared = d;
                record->nearestKart = j;
                record->nearestDriver = other->driver;
            }
        }
    }
}

void fn_801E96BC(AISystemState *self) {
    AIPairRecord *record;
    AIPairRecord *base;
    int i;
    AIVec p;
    AIVec pos;
    int cap = lbl_806D1920;
    self->frame++;
    if (cap < self->frame) self->frame = cap;
    base = lbl_806793D8;
    for (i = 0; i < 8; ++i) {
        record = &base[i];
        if (record && record->driver) {
            float *m = KartDriver_GetKartRootMtx(record->driver);
            float x = m[3];
            float y = m[7];
            float z = m[11];
            record->waypoint = Waypoint_FindNearest(g_pathSystem, 0, x, y, z, lbl_806DA3E8);
            pos.x = x; pos.y = y; pos.z = z;
            FindNearestKart(record, base, &pos, &p);
        }
    }
}
