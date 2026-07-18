/*
 * ItemTracker slot lock helpers (GitHub claim issue #4)
 *
 * ItemTracker_GetTargetKart @ 0x800DD5FC (size 0x6C)
 * ItemTracker_SetTrackPhase @ 0x800DD668 (size 0xC0)
 * ItemTracker_ReleaseLock   @ 0x800DD728 (size 0x68)
 * ItemTracker_AcquireLock   @ 0x800DD790 (size 0xB0)
 *
 * Four adjacent single-fn reversed-extab groups merged into one TU
 * (extab 0x8000B47C..0x8000B49C, extabindex 0x80023BD0..0x80023C00,
 * .text 0x800DD5FC..0x800DD840). Built with CW 1.3.2 +
 * `-Cpp_exceptions on` so all four extab/extabindex pairs are
 * auto-emitted in fn definition order.
 *
 * ItemTracker (partial view, base object shared with ItemObject family):
 *   +0x008 : s32  kind (0x2B selects alloc kind 0xE, else 0xD)
 *   +0x170 : s32  slot index into race context (-1 = none)
 *   +0x174 : s8   active flag (0 = idle, 1 = locked, -1 = releasing)
 *   +0x178 : s32  timer (set to 300 when phase tracking enabled)
 *   +0x180 : s32  alloc param a (forwarded to RaceContextSlot_AllocItem)
 *   +0x184 : s32  alloc param b (forwarded to RaceContextSlot_AllocItem)
 *
 * RaceContextSlot (partial view):
 *   +0x008 : s32  phase (0 = tracking, 3 = idle)
 *   +0x0B8 : void* kart
 */

typedef struct ItemTracker {
    unsigned char pad00[0x8];   /* +0x000 */
    int kind;                   /* +0x008 */
    unsigned char pad0C[0x164]; /* +0x00C */
    int slot;                   /* +0x170 */
    signed char active;         /* +0x174 */
    unsigned char pad175[3];    /* +0x175 */
    int timer;                  /* +0x178 */
    unsigned char pad17C[4];    /* +0x17C */
    int allocParamA;            /* +0x180 */
    int allocParamB;            /* +0x184 */
} ItemTracker;

typedef struct ItemTrackerRaceSlot {
    unsigned char pad00[0x8];  /* +0x000 */
    int phase;                 /* +0x008 */
    unsigned char pad0C[0xAC]; /* +0x00C */
    void *kart;                /* +0x0B8 */
} ItemTrackerRaceSlot;

extern void *GetRaceContextPtr(void);
extern ItemTrackerRaceSlot *RaceContextSlot_GetIfAlive(void *ctx, int idx);
extern void RaceContextSlot_Free(void *ctx, int idx);
extern int RaceContextSlot_AllocItem(void *ctx, int kind, void *owner, int a, int b);

#pragma exceptions on

void *ItemTracker_GetTargetKart(ItemTracker *self) {
    int slot;

    if (self == 0) {
        return 0;
    }
    if (self->active == 0) {
        return 0;
    }
    slot = self->slot;
    if (slot == -1) {
        return 0;
    }
    return RaceContextSlot_GetIfAlive(GetRaceContextPtr(), slot)->kart;
}

void ItemTracker_SetTrackPhase(ItemTracker *self, int enable) {
    int slot;
    int phase;

    if (self == 0) {
        return;
    }
    if (self->active == 0) {
        return;
    }
    slot = self->slot;
    if (slot == -1) {
        return;
    }
    if (enable != 0) {
        phase = 0;
        RaceContextSlot_GetIfAlive(GetRaceContextPtr(), slot)->phase = phase;
    } else {
        phase = 3;
        RaceContextSlot_GetIfAlive(GetRaceContextPtr(), slot)->phase = phase;
    }
    if (enable != 0) {
        self->active = 1;
    } else {
        self->active = -1;
    }
    if (enable != 0) {
        self->timer = 300;
    }
}

void ItemTracker_ReleaseLock(ItemTracker *self) {
    int slot;

    if (self == 0) {
        return;
    }
    if (self->active == 0) {
        return;
    }
    slot = self->slot;
    if (slot != -1) {
        RaceContextSlot_Free(GetRaceContextPtr(), slot);
    }
    self->slot = -1;
    self->active = 0;
}

void ItemTracker_AcquireLock(ItemTracker *self) {
    int slot;
    int phase;

    if (self == 0) {
        return;
    }
    switch (self->kind) {
    case 0x2B:
        self->slot = RaceContextSlot_AllocItem(GetRaceContextPtr(), 0xE, self,
                                               self->allocParamA, self->allocParamB);
        break;
    default:
        self->slot = RaceContextSlot_AllocItem(GetRaceContextPtr(), 0xD, self,
                                               self->allocParamA, self->allocParamB);
        break;
    }
    slot = self->slot;
    if (slot != -1) {
        phase = 0;
        RaceContextSlot_GetIfAlive(GetRaceContextPtr(), slot)->phase = phase;
    }
    self->active = 1;
}

#pragma exceptions reset
