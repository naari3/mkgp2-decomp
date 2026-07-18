/*
 * TripleBladeRing_Update (0x800B4094 size:0xD0) - matched 100%
 *
 * Per-frame update. First-frame init: spawns the two child draw-effect
 * actors from factory fn_800AF4F8, binds sub-effect resources 0x90/0x91,
 * clears their +0x28 flags, seeds phase0 and installs
 * TripleBladeRing_DrawCb as the draw callback. On termination flag:
 * frees both children then self.
 *
 * Notes:
 * - initFlag/termFlag are signed char (lbz + extsb. tests).
 * - lbl_806D5034 must stay `extern const float`: the scheduler hoists
 *   the lfs above the two u8 stores only when the load is const
 *   (type-based aliasing blocks the motion otherwise).
 */

#include "game/TripleBladeRing.h"

extern void *DrawEffect_SpawnDirect(void *factory);
extern void DrawEffect_Free(void *p);
extern void VfxSlot_BindResource(void *slot, int id);
extern void fn_800AF4F8(void); /* draw-effect factory descriptor */

extern const float lbl_806D5034;

void TripleBladeRing_Update(TripleBladeRing *self)
{
    if (self->initFlag == 0) {
        self->slotA = DrawEffect_SpawnDirect((void *)fn_800AF4F8);
        self->slotB = DrawEffect_SpawnDirect((void *)fn_800AF4F8);
        VfxSlot_BindResource(self->slotA->bindSlot, 0x90);
        VfxSlot_BindResource(self->slotB->bindSlot, 0x91);
        self->slotA->flag28 = 0;
        self->slotB->flag28 = 0;
        self->phase0 = lbl_806D5034;
        self->drawFn = TripleBladeRing_DrawCb;
        self->drawArg = self;
        self->initFlag = self->initFlag + 1;
    }
    if (self->termFlag != 0) {
        DrawEffect_Free(self->slotA);
        DrawEffect_Free(self->slotB);
        DrawEffect_Free(self);
    }
}
