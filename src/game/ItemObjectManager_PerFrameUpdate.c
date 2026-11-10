/* ItemObjectManager_PerFrameUpdate (0x800A45B8): per-frame pass over the
 * race-context slot array. The first loop refreshes every live slot's
 * matrices and position from its source (a matrix or a position vector)
 * and clears its target. Once the race has started, the second loop pairs
 * every live slot with every other one: karts (types 0..3) and type-6
 * objects try to acquire each other as targets, and a type-7 slot either
 * counts down its lock on its own target or locks onto a kart/type-6 slot
 * that comes within its hit radius. */
typedef float Mtx[3][4];

#include "game/types/Vec.h"

typedef struct RaceContextSlot {
    int type;               /* 0x00 */
    int id;                 /* 0x04 */
    int mode;               /* 0x08 */
    int modeTimer;          /* 0x0C */
    Mtx mtx;                /* 0x10 */
    Mtx srcCopy;            /* 0x40 */
    Mtx *srcMtx;            /* 0x70 */
    Vec pos;                /* 0x74 */
    Vec *srcPos;            /* 0x80 */
    unsigned char pad84[0x90 - 0x84];
    int target;             /* 0x90 */
    unsigned char pad94[0x98 - 0x94];
    int word98;             /* 0x98 */
    struct RaceContextSlot *targetSlot; /* 0x9C */
    float targetDist;       /* 0xA0 */
    float scale;            /* 0xA4 */
    unsigned char *item;    /* 0xA8 */
    int owner;              /* 0xAC */
    int ownerLock;          /* 0xB0 */
    unsigned int tag;       /* 0xB4 */
    unsigned int targetTag; /* 0xB8 */
} RaceContextSlot;

extern unsigned char IsRaceStarted(void);
extern signed char ItemClass_GetFlagByte1(int itemId);
extern void ItemObject_TryAcquireTarget(RaceContextSlot *self, int selfIndex, int otherIndex,
                                        RaceContextSlot *other, float range, float radius);
extern void PSMTXIdentity(Mtx *m);
extern void PSMTXCopy(Mtx *src, Mtx *dst);
extern void PSMTXTranspose(Mtx *src, Mtx *dst);

static inline float sqrtf(float x)
{
    static const double _half = 0.5;
    static const double _three = 3.0;
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = _half * guess * (_three - x * (guess * guess));
        guess = _half * guess * (_three - x * (guess * guess));
        guess = _half * guess * (_three - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

static inline unsigned int Slot_IsAlive(RaceContextSlot *slot)
{
    return slot->type != -1;
}

static inline float Vec_Distance(Vec *a, Vec *b)
{
    float dy = b->y - a->y;
    float dx = b->x - a->x;
    float dz = b->z - a->z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

static inline void Slot_TryLock(RaceContextSlot *self, int index, RaceContextSlot *other, float radius)
{
    if (self->mode != 3) {
        radius *= self->scale;
        if (!(radius < Vec_Distance(&self->pos, &other->pos))) {
            self->target = index;
            self->targetSlot = other;
            self->targetTag = other->tag;
            self->mode = 3;
            if (self->id == 0xD) {
                other->modeTimer = 480;
                other->mode = 1;
            }
            if (self->id == 0xE) {
                other->modeTimer = 0;
                other->mode = 2;
            }
        }
    }
}

#pragma use_lmw_stmw on

void ItemObjectManager_PerFrameUpdate(RaceContextSlot *slots)
{
    int k;
    int i;
    int j;
    int type;
    int otherType;
    RaceContextSlot *slot;
    RaceContextSlot *other;

    for (k = 0; k < 127; k++) {
        slot = &slots[k];
        if (Slot_IsAlive(slot) == 1) {
            if (slot->srcMtx != 0) {
                PSMTXCopy(slot->srcMtx, &slot->srcCopy);
                slot->srcCopy[0][3] = 0.0f;
                slot->srcCopy[1][3] = 0.0f;
                slot->srcCopy[2][3] = 0.0f;
                PSMTXTranspose(&slot->srcCopy, &slot->mtx);
                slot->pos.x = (*slot->srcMtx)[0][3];
                slot->pos.y = (*slot->srcMtx)[1][3];
                slot->pos.z = (*slot->srcMtx)[2][3];
            }
            if (slot->srcPos != 0) {
                PSMTXIdentity(&slot->mtx);
                PSMTXIdentity(&slot->srcCopy);
                slot->pos.x = slot->srcPos->x;
                slot->pos.y = slot->srcPos->y;
                slot->pos.z = slot->srcPos->z;
            }
            slot->targetDist = 10000.0f;
            slot->target = -1;
            slot->word98 = 0;
        }
    }

    if (!IsRaceStarted()) {
        return;
    }

    for (i = 0; i < 127; i++) {
        slot = &slots[i];
        if (Slot_IsAlive(slot) == 1) {
            for (j = 0; j < 128; j++) {
                other = &slots[j];
                if (i == j || Slot_IsAlive(other) != 1) {
                    continue;
                }
                otherType = other->type;
                type = slot->type;
                if (type >= 0 && type <= 3 && otherType == 6) {
                    ItemObject_TryAcquireTarget(slot, i, j, other, 300.0f, 20.0f);
                }
                if (otherType >= 0 && otherType <= 3 && type == 6) {
                    ItemObject_TryAcquireTarget(slot, i, j, other, 260.0f, 24.0f);
                }
                if (type != 7) {
                    continue;
                }
                if (j == slot->owner) {
                    if (slot->item != 0 && ItemClass_GetFlagByte1(*(int *)(slot->item + 8)) == 1) {
                        continue;
                    }
                    slot->ownerLock--;
                    if (slot->ownerLock <= 0) {
                        slot->owner = -1;
                    }
                    continue;
                }
                if (otherType >= 0 && otherType <= 3) {
                    Slot_TryLock(slot, j, other, 18.0f);
                }
                if (otherType == 6) {
                    Slot_TryLock(slot, j, other, 24.0f);
                }
            }
            if (slot->modeTimer > 0) {
                slot->modeTimer--;
                if (slot->modeTimer <= 0) {
                    slot->mode = 0;
                }
            }
        }
    }
}

#pragma use_lmw_stmw reset
