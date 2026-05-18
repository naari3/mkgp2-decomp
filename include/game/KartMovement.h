/*
 * KartMovement struct (game/KartMovement.c family).
 *
 * Total size 0x324 (804 B). Most fields are still unidentified;
 * this header only names the offsets that current matching TUs touch
 * and keeps the rest as `_padXX` byte gaps so the overall layout
 * stays size-accurate.
 *
 * Field offsets verified against KartMovement_SetPosition @ 0x8019A4A0
 * store sequence (stfs 0x40, 0x44, 0x48 -> posXYZ;
 * stfs 0x4C, 0x50, 0x54 -> prevPos; stfs 0x88, 0x8C, 0x90 ->
 * orientMatTrans). Plate comment from Ghidra (see decompile output)
 * names the same offsets.
 *
 * +0x40  Vec3  posXYZ           (current position)
 * +0x4C  Vec3  prevPos          (previous position; used for
 *                                interpolation glitch suppression)
 * +0x88  Vec3  orientMatTrans   (orientation matrix translation copy)
 *
 * Other names referenced from existing TUs (kept as comments only,
 * not added to the struct yet because their semantics are still
 * being audited):
 *   +0x240 remainingLaps (KartMovement_SetRemainingLaps)
 *   +0x338 velocity Vec3 (KartMovement_GetVelocityMagnitude)
 */

#ifndef GAME_KARTMOVEMENT_H
#define GAME_KARTMOVEMENT_H

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct KartMovement {
    /* +0x000 */ unsigned char _pad00[0x40];
    /* +0x040 */ Vec3 posXYZ;
    /* +0x04C */ Vec3 prevPos;
    /* +0x058 */ unsigned char _pad58[0x88 - 0x58];
    /* +0x088 */ Vec3 orientMatTrans;
    /* +0x094 */ unsigned char _pad94[0x324 - 0x94];
} KartMovement;

#endif /* GAME_KARTMOVEMENT_H */
