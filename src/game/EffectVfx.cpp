#include "EffectVfxView.h"
extern "C" {
void cLNormal3DWrap_Slot_SetRotationQuat(void *,float,float,float,float);
void cLNormal3DWrap_Slot_Render(void *);
void EffectVfx_KartChild_SetRotQuatAndRender(EffectVfxView *effect) {
    void *slot=effect->slot;
    cLNormal3DWrap_Slot_SetRotationQuat(slot,effect->x,effect->y,effect->z,effect->alpha);
    cLNormal3DWrap_Slot_Render(slot);
}
}
