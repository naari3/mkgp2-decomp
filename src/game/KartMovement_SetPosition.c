/*
 * KartMovement_SetPosition @ 0x8019A4A0 (size 0x40).
 *
 * Teleports a kart to (pos.x, pos.y, pos.z).
 *
 *   orientMatTrans <- pos   (always)
 *   posXYZ         <- pos   (always)
 *   prevPos        <- pos   (only when flag == 1, to suppress
 *                            interpolation glitch on teleport)
 *
 * flag is the low byte of r5 (`clrlwi r0, r5, 24; cmplwi r0, 0x1`),
 * so the C parameter is u8.
 *
 * Field offsets are documented in include/game/KartMovement.h
 * (posXYZ at 0x40, prevPos at 0x4C, orientMatTrans at 0x88).
 *
 * No try/catch in the body and no auto extab entry in the dtk-generated
 * asm for this group; #pragma exceptions is not needed.
 *
 * Matching trick:
 *   - The temp variables are declared in REVERSE order
 *     (`float z, y, x;`) because CW's float register allocator
 *     assigns f0/f1/f2 to declarators in declaration order.
 *     The target uses f2 for x, f1 for y, f0 for z, so x must be
 *     the LAST declarator.
 *   - The first store (`self->orientMatTrans.x = x;`) is interleaved
 *     between `y = pos->y;` and `z = pos->z;` so that CW emits
 *     `lfs x; clrlwi; lfs y; cmplwi; stfs x; lfs z; ...` which is the
 *     target schedule. Loading all three before any store produces
 *     a different (matching-failing) interleave.
 */

#include "game/KartMovement.h"

typedef unsigned char u8;

void KartMovement_SetPosition(KartMovement *self, Vec3 *pos, u8 flag) {
    float z, y, x;

    x = pos->x;
    y = pos->y;
    self->orientMatTrans.x = x;
    z = pos->z;
    self->orientMatTrans.y = y;
    self->orientMatTrans.z = z;

    self->posXYZ.x = x;
    self->posXYZ.y = y;
    self->posXYZ.z = z;

    if (flag == 1) {
        self->prevPos.x = x;
        self->prevPos.y = y;
        self->prevPos.z = z;
    }
}
