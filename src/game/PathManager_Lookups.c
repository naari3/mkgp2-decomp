/*
 * PathManager_Lookups @ 0x8003B454 - 0x8003B668 (3 fns, 1 TU bundle).
 *
 *   0x8003B454 Path_LookupCheckpointOffset  (size 0xD0)
 *   0x8003B524 Path_LookupMaxProgressOffset (size 0xD0)
 *   0x8003B5F4 PathManager_GetEntrySubStruct (size 0x74)
 *
 * Each takes a PathManager-like base pointer and a 0..7 slot index.
 * Per-slot stride is 0x98 bytes. The two Lookup* fns wrap a delta walk
 * around Path_GetTotalCount/Path_GetWaypointPtr starting from a per-slot
 * "current" field (offset 0x14 / 0x80). The Get* fn returns a pointer
 * into the per-slot substructure at offset 0x10.
 *
 * All three carry a Large-Frame extab/extabindex entry; we let CW auto-emit
 * them by wrapping each body with #pragma exceptions on/reset, same pattern
 * as PathManager_RefreshFinishPositions / AI_GetYaw / GetCourseSectionType.
 *
 * Matching tricks (CW 1.3.2):
 *  - To get `mulli r0; cmpwi; add r3, base, r0; lwz r0, off(r3); add iv, r0, delta`
 *    (instead of `mulli r3; addi r0, r3, off; lwzx r0, base, r0`), use
 *    explicit pointer arithmetic via a long-lived `PathSlot *slot` that is
 *    INCREMENTED in two steps:
 *       PathSlot *slot = (PathSlot *)self;
 *       slot += kartIndex;
 *       iv = slot->field + offsetDelta;
 *    Splitting the index addition from the cast and into a separate stmt
 *    forces CW to materialize slot in a register before the load. Inline
 *    forms (`((PathSlot*)self)[ki].field`, `((PathSlot*)self + ki)->field`,
 *    or `*(int*)(self + ki*0x98 + off)`) all collapse into addi+lwzx.
 *  - The negative-offset loop uses a `do { if (iv >= 0) goto done; ... } while(1)`
 *    pattern, NOT `while (iv < 0) { ... }`. The latter produces a do/while
 *    backward-test layout (`b test; loop:body; test:cmpwi/blt loop`), but
 *    target wants a top-tested forward-exit layout (`loop:cmpwi/bge exit;
 *    body; b loop`).
 */

extern int PathManager_HasPathLoaded(void *self);
extern int Path_GetTotalCount(void *self);
extern void *Path_GetWaypointPtr(void *self, int waypointIndex);

typedef struct PathSlot {
    char _pad0[0x14];
    int checkpoint;
    char _pad18[0x80 - 0x18];
    int maxProgress;
    char _pad84[0x98 - 0x84];
} PathSlot;

#pragma exceptions on
void *Path_LookupCheckpointOffset(void *self, int kartIndex, int offsetDelta) {
    int iv;
    int total;

    if (PathManager_HasPathLoaded(self) == 0) {
        return 0;
    }
    if (kartIndex < 0) {
        return 0;
    }
    if (kartIndex >= 8) {
        return 0;
    }
    {
        PathSlot *slot = (PathSlot *)self;
        slot += kartIndex;
        iv = slot->checkpoint + offsetDelta;
    }
    if (offsetDelta < 0) goto neg_loop;
    do {
        total = Path_GetTotalCount(self);
        if (iv < total) goto done;
        total = Path_GetTotalCount(self);
        iv -= total;
    } while (1);
neg_loop:
    do {
        if (iv >= 0) goto done;
        total = Path_GetTotalCount(self);
        iv += total;
    } while (1);
done:
    return Path_GetWaypointPtr(self, iv);
}
#pragma exceptions reset

#pragma exceptions on
void *Path_LookupMaxProgressOffset(void *self, int kartIndex, int offsetDelta) {
    int iv;
    int total;

    if (PathManager_HasPathLoaded(self) == 0) {
        return 0;
    }
    if (kartIndex < 0) {
        return 0;
    }
    if (kartIndex >= 8) {
        return 0;
    }
    {
        PathSlot *slot = (PathSlot *)self;
        slot += kartIndex;
        iv = slot->maxProgress + offsetDelta;
    }
    if (offsetDelta < 0) goto neg_loop;
    do {
        total = Path_GetTotalCount(self);
        if (iv < total) goto done;
        total = Path_GetTotalCount(self);
        iv -= total;
    } while (1);
neg_loop:
    do {
        if (iv >= 0) goto done;
        total = Path_GetTotalCount(self);
        iv += total;
    } while (1);
done:
    return Path_GetWaypointPtr(self, iv);
}
#pragma exceptions reset

#pragma exceptions on
void *PathManager_GetEntrySubStruct(void *self, int kartIndex) {
    if (PathManager_HasPathLoaded(self) == 0) {
        return 0;
    }
    if (kartIndex < 0) {
        return 0;
    }
    if (kartIndex >= 8) {
        return 0;
    }
    return (char *)self + kartIndex * 0x98 + 0x10;
}
#pragma exceptions reset
