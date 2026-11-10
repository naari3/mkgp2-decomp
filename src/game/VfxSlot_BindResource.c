/* Bind a VFX slot to a model resource: acquire a cLNormal3DWrap slot,
 * reset its animation and register the slot's draw callback. */
#include "game/types/VfxSlot.h"

extern void *lbl_806D14A8;
extern const float lbl_806D4FF8;
extern const float lbl_806D5008;
extern void *cLNormal3DWrap_Mgr_AcquireSlot(void *mgr, unsigned char resource, int flag);
extern void cLNormal3DWrap_Slot_SetAnimSpeed(void *slot, float speed);
extern void GetSpawnPosition(float *out, float x, float y, float z);
extern void VfxSlot_RegisterDraw(VfxSlot *self);

#pragma exceptions on
void VfxSlot_BindResource(VfxSlot *self, int resource)
{
    self->active = 0;
    self->kind = 0x11;
    self->resource = resource;
    self->slot = cLNormal3DWrap_Mgr_AcquireSlot(lbl_806D14A8, resource, 1);
    cLNormal3DWrap_Slot_SetAnimSpeed(self->slot, lbl_806D4FF8);
    self->scale = lbl_806D5008;
    self->visible = 1;
    self->alpha = lbl_806D5008;
    GetSpawnPosition(self->pos, lbl_806D5008, lbl_806D5008, lbl_806D5008);
    if (self->slot != 0) {
        self->animDone = 0;
        self->animFrame = lbl_806D4FF8;
    }
    self->draw = VfxSlot_RegisterDraw;
}
#pragma exceptions reset
