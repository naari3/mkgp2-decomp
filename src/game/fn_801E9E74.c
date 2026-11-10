#include "game/types/reg_args.h"
/* Native reconstruction of the assigned single-function TU. */
#include "game/AISpeedPrivate.h"
#include "game/KartMovement.h"
extern void *GetPlayerCarObject(void);
extern float *KartDriver_GetKartRootMtx(void *);
extern Vec3 lbl_803BD8A8;
extern const float lbl_806DA3E8, lbl_806DA3EC, lbl_806DA3F0, lbl_806DA3F4;
extern void *g_pathSystem;
extern int Waypoint_FindNearest(void *, int, float, float, float, float);
extern float PSVECSquareDistance(const Vec3 *, const Vec3 *);
extern int fn_801DCCE4(void);
extern float fn_801DCCBC(REG_ARGS1(int idx));
extern int fn_801DCC94(int);
extern float fn_801DCC6C(int);
static inline void UpdateRecord(AIPairRecord *record, AIPairRecord *base, Vec3 *player, float pz) {
    if (record && record->driver) {
        float *m = KartDriver_GetKartRootMtx(record->driver);
        float z, y, x;
        AIPairRecord *other;
        int i;
        Vec3 from;
        x = m[3]; y = m[7]; z = m[11];
        record->waypoint = Waypoint_FindNearest(g_pathSystem, 0, x, y, z, lbl_806DA3E8);
        record->nearestKart = -1;
        record->nearestDriver = 0;
        record->distanceSquared = lbl_806DA3EC;
        record->distanceSquared *= record->distanceSquared;
        record->distanceSquared *= lbl_806DA3F0;
        from.x = x; from.y = y; from.z = z;
        for (i = 0, other = base; i < 8; ++i, ++other) {
            if (record != other && other->driver) {
                float *n = KartDriver_GetKartRootMtx(other->driver);
                Vec3 to;
                float distance;
                float ny = n[7];
                float nz = n[11];
                float nx = n[3];
                to.x = nx; to.y = ny; to.z = nz;
                distance = PSVECSquareDistance(&to, &from);
                if (distance < record->distanceSquared) {
                    record->distanceSquared = distance;
                    record->nearestKart = i;
                    record->nearestDriver = other->driver;
                }
            }
        }
        {
            float dz = z - pz;
            float dx = x - player->x;
            *(float *)&record->field2C = dx * dx + dz * dz;
        }
    }
}
static inline void ClassifyRecord(AIPairRecord *record, float range, int *count, int *result) {
    *result = 0;
    if (record && record->driver) {
        unsigned char active = *(unsigned char *)&record->field30;
        float previous = record->speedBonus;
        record->speedBonus = lbl_806DA3F4;
        *(unsigned char *)&record->field30 = 0;
        if (*(float *)&record->field2C < range) {
            ++*count;
            if (!active) *result = 2;
            else *result = 1;
            if (lbl_806DA3F4 != previous) *result = 2;
            *(unsigned char *)&record->field30 = 1;
        }
    }
}
static inline void ResetRecord(AIPairRecord *record) {
    if (record) {
        record->speedBonus = lbl_806DA3F4;
        *(unsigned char *)&record->field30 = 0;
    }
}
static inline float GetRangeSq(REG_ARGS1(int idx)) { float range = fn_801DCCBC(REG_ARGS1(idx)); range *= range; return range; }
void fn_801E9E74(AISpeedOwner *self) {
    AISpeedRender *player;
    Vec3 position;
    AIPairRecord *base;
    AIPairRecord *record;
    int i;
    float zero;
    float pz;
    /* fakematch (hand): natural code is `int limit = lbl_806D1920;`. base must be the
     * second lifetime range of a variable so the table address lands in its
     * register (regalloc_patterns 57, same as fn_801E96BC). */
    base = (AIPairRecord *)lbl_806D1920;
    ++self->frame;
    if ((int)base < self->frame) self->frame = (int)base;
    if (GetPlayerCarObject()) player = CarObject_GetRenderObj(GetPlayerCarObject());
    else player = 0;
    position = lbl_803BD8A8;
    if (player) {
        position.x = KartDriver_GetKartRootMtx(player)[3];
        position.z = KartDriver_GetKartRootMtx(player)[11];
        position.y = lbl_806DA3F4;
    }
    base = lbl_806793D8;
    pz = position.z;
    zero = lbl_806DA3F4;
    for (i = 0; i < 8; ++i) {
        record = &base[i];
        record->speedBonus = zero;
        UpdateRecord(record, base, &position, pz);
    }
    {
        int setting = fn_801DCCE4();
        if (setting >= 0) {
            int states[8];
            int count = 0;
            float range = GetRangeSq(REG_ARGS1(setting)); /* r3 still holds setting */
            for (i = 0; i < 8; ++i) {
                record = &base[i];
                ClassifyRecord(record, range, &count, &states[i]);
            }
            if (count > fn_801DCC94(setting)) {
                float bonus = fn_801DCC6C(setting);
                for (i = 0; i < 8; ++base, ++i) {
                    if (base && states[i] == 2) base->speedBonus = bonus;
                }
            }
        } else {
            for (i = 0, record = base; i < 8; ++i, ++record) ResetRecord(record);
        }
    }
}
