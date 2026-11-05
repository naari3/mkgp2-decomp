#include "DriveBehavior_private.h"

extern const float lbl_806DA2D0, lbl_806DA2DC;

void fn_801DEC74(DriveBehavior *self) {
    self->matrix[0] = lbl_806DA2D0;
    self->matrix[1] = lbl_806DA2D0;
    self->matrix[2] = lbl_806DA2D0;
    self->matrix[3] = lbl_806DA2D0;
    self->matrix[4] = lbl_806DA2D0;
    self->matrix[5] = lbl_806DA2D0;
    self->matrix[6] = lbl_806DA2D0;
    self->matrix[7] = lbl_806DA2D0;
    self->matrix[8] = lbl_806DA2D0;
    self->matrix[9] = lbl_806DA2D0;
    self->matrix[10] = lbl_806DA2D0;
    self->matrix[11] = lbl_806DA2D0;
    self->matrix[12] = lbl_806DA2D0;
    self->matrix[13] = lbl_806DA2D0;
    self->matrix[14] = lbl_806DA2D0;
    self->matrix[15] = lbl_806DA2D0;
    self->matrix[15] = lbl_806DA2DC;
    self->matrix[10] = lbl_806DA2DC;
    self->matrix[5] = lbl_806DA2DC;
    self->matrix[0] = lbl_806DA2DC;
    DriveBehavior_HandleWpType(self, self->waypoint);
    if (self->remaining > 0) {
        --self->remaining;
        if (self->remaining <= 0) {
            fn_801E2F28(&self->queue);
            if (self->queue.count == 0) {
                self->remaining = 0;
                self->waypoint = 0;
            } else {
                DriveRing *ring = &self->queue.blocks;
                DrivePair **slot;
                slot = fn_801E40C0(ring,
                    self->queue.first / self->queue.blockSize);
                self->remaining = ((int *)*slot)[
                    (self->queue.first % self->queue.blockSize) * 2 + 1];
                slot = fn_801E40C0(ring,
                    self->queue.first / self->queue.blockSize);
                self->waypoint = ((int *)*slot)[
                    (self->queue.first % self->queue.blockSize) * 2];
                switch (fn_801DB830(fn_801DB8F0(), self->waypoint)) {
                case 3:
                case 4:
                    self->direction = 1;
                    self->speedScale = lbl_806DA2D0;
                    self->acceleration = lbl_806D18FC;
                    break;
                case 5: self->speedScale = lbl_806D18F4; break;
                case 6: self->speedScale = lbl_806D18F8; break;
                case 10: break;
                case 11: self->phase = lbl_806DA2D0; break;
                }
            }
        }
    }
}
