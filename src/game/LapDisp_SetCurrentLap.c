/*
 * LapDisp_SetCurrentLap @ 0x8023FAEC (size 0x60).
 *
 * Clamp `currentLap` to [self->currentLapFloor (0x30), self->totalLaps (0x2C)]
 * and only commit + refresh the sprite when the clamped value differs from
 * the cached `self->currentLap` (offset 0x28). On change, store the new lap
 * count and push resource id `currentLap + 0xB3B` into the SpriteLayer slot
 * held at `self->currentLapLayer` (offset 0x10) via SpriteLayer_SetResource.
 *
 * Both compares (`> max` and `< min`) operate on the original input
 * `currentLap` rather than the running clamp result, matching the target
 * codegen `mr r5, r4 ; cmpw r4, r0 ; ble ; mr r5, r0 ; cmpw r4, r0 ; bge ;
 * mr r5, r0`. Same clamp idiom as LapDisp_SetTotalLaps.
 *
 * After commit the source reads back `self->currentLap` before adding the
 * resource id base, reproducing the `stw r5, 0x28(r3) ; lwz r4, 0x28(r3) ;
 * addi r4, r4, 0xb3b` sequence (store, reload, add).
 *
 * extab/extabindex entries are present in the target (Large Frame: Yes flag,
 * 0x8/0xC bytes). Emitted via #pragma exceptions on/reset so CW auto-generates
 * them -- same pattern as LapDisp_SetTotalLaps.c.
 */

typedef struct LapDisp {
    char pad_00[0x10];
    int currentLapLayer;   // SpriteLayer slot id used here, resId base 0xB3B
    int totalLapsLayer;    // SpriteLayer slot id used by SetTotalLaps
    char pad_18[0x10];
    int currentLap;
    int totalLaps;
    int currentLapFloor;
} LapDisp;

extern void SpriteLayer_SetResource(int layerId, unsigned int resourceId);

#pragma exceptions on
void LapDisp_SetCurrentLap(LapDisp *self, int currentLap) {
    int clamped = currentLap;
    if (currentLap > self->totalLaps) {
        clamped = self->totalLaps;
    }
    if (currentLap < self->currentLapFloor) {
        clamped = self->currentLapFloor;
    }
    if (clamped != self->currentLap) {
        self->currentLap = clamped;
        SpriteLayer_SetResource(self->currentLapLayer, self->currentLap + 0xB3B);
    }
}
#pragma exceptions reset
