/*
 * LapDisp_SetTotalLaps @ 0x8023FAA0 (size 0x4C).
 *
 * Clamp `totalLaps` to [1, 9] and store it into `self->totalLaps` (offset
 * 0x2C). Then push the resulting sprite resource id (`totalLaps + 0xB44`)
 * into the SpriteLayer slot held at `self->totalLapsLayer` (offset 0x14)
 * via SpriteLayer_SetResource.
 *
 * The two compares (`> 9` and `< 1`) both operate on the original input
 * `totalLaps` (not on the running clamp result), matching the target
 * codegen `cmpwi r4,0x9 ; ... ; cmpwi r4,0x1 ; ...`. This is the same
 * clamp idiom seen in game/Clamp.c (Clamp_Int) but inlined here.
 *
 * extab/extabindex entries are present in the target (Large Frame: Yes
 * flag, 0x8/0xC bytes). Emitted via #pragma exceptions on/reset so CW
 * auto-generates them -- same pattern as game/ItemDisplay_Stop.c.
 *
 * LapDisp struct fields probed from this function and LapDisp_SetCurrentLap
 * (0x8023FAEC):
 *   0x10  SpriteLayer *currentLapLayer  (used by SetCurrentLap, resId base 0xB3B)
 *   0x14  SpriteLayer *totalLapsLayer   (used here, resId base 0xB44)
 *   0x28  int currentLap
 *   0x2C  int totalLaps                  (clamp [1,9])
 *   0x30  int currentLapFloor            (lower clamp for currentLap)
 */

typedef struct LapDisp {
    char pad_00[0x10];
    int currentLapLayer;   // SpriteLayer slot id used by SetCurrentLap
    int totalLapsLayer;    // SpriteLayer slot id used here
    char pad_18[0x10];
    int currentLap;
    int totalLaps;
    int currentLapFloor;
} LapDisp;

extern void SpriteLayer_SetResource(int layerId, unsigned int resourceId);

#pragma exceptions on
void LapDisp_SetTotalLaps(LapDisp *self, int totalLaps) {
    int clamped = totalLaps;
    if (totalLaps > 9) {
        clamped = 9;
    }
    if (totalLaps < 1) {
        clamped = 1;
    }
    self->totalLaps = clamped;
    SpriteLayer_SetResource(self->totalLapsLayer, self->totalLaps + 0xB44);
}
#pragma exceptions reset
