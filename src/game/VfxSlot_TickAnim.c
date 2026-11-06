#include "game/VfxSlot_TickAnim_private.h"

extern void cLNormal3DWrap_Slot_AdvanceAnimFrame(void *);
extern void cLNormal3DWrap_Slot_SetAnimFrame(void *, float);
extern void cLNormal3DWrap_Slot_SetAnimSpeed(void *, float);
extern VfxAnimResource lbl_8041BC00[];

/* Same guarded operation as VfxSlot_SetAnimFrame. */
static inline void SetAnimFrame(VfxSlotAnim *self, float frame)
{
    if (self->effect != 0) {
        self->state = 0;
        self->frame = frame;
    }
}

#pragma exceptions on
void VfxSlot_TickAnim(VfxSlotAnim *self, int update)
{
    if (self->effect != 0) {
        switch (lbl_8041BC00[self->resource].mode) {
        case 0:
            if (update && self->enabled)
                cLNormal3DWrap_Slot_AdvanceAnimFrame(self->effect);
            break;
        case 1:
            switch (self->state) {
            case 0:
                self->frame += self->speed;
                if (lbl_8041BC00[self->resource].lastFrame <= self->frame) {
                    self->frame = lbl_8041BC00[self->resource].lastFrame;
                    if (lbl_8041BC00[self->resource].loop)
                        self->state = 2;
                    else
                        self->state = 1;
                }
                break;
            case 2:
                SetAnimFrame(self, 0.0f);
                break;
            case 1:
            default:
                break;
            }
            if (update && self->enabled) {
                void *effect = self->effect;
                cLNormal3DWrap_Slot_SetAnimFrame(effect, self->frame);
                cLNormal3DWrap_Slot_SetAnimSpeed(effect, 0.0f);
                cLNormal3DWrap_Slot_AdvanceAnimFrame(effect);
            }
            break;
        }
    }
}
#pragma exceptions reset
