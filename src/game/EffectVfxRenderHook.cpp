#include "EffectVfxView.h"
static inline void *PresentOrNull(void *p) { if(!p) return 0; return p; }
extern "C" {
extern const float lbl_806D51C0;
extern void *lbl_806D10AC;
void cLNormal3DWrap_Slot_GetOrLoadJointTransform(void *, EffectVfxVec *);
void cLNormal3DWrap_Slot_SetRotationQuat(void *, float,float,float,float);
void cLNormal3DWrap_Slot_Render(void *);
void EffectVfx_KartChild_SetRotQuatAndRender(EffectVfxView *);
void clDrawMan_AddSorted_DepthRange(void *, void (*)(EffectVfxView *), EffectVfxView *, float,float,float,float);
static inline void RenderIfUnmasked(EffectVfxView *effect) {
    if (effect->flags & 2) return;
    if (effect->alpha <= lbl_806D51C0) return;
    EffectVfxVec position;
    cLNormal3DWrap_Slot_GetOrLoadJointTransform(effect->slot, &position);
    void *manager=PresentOrNull(lbl_806D10AC);
    clDrawMan_AddSorted_DepthRange(manager,EffectVfx_KartChild_SetRotQuatAndRender,effect,position.x,position.y,position.z,lbl_806D51C0);
}
void EffectVfx_KartChildAttached_RenderHook(EffectVfxView *effect) {
    if (!effect->slot) return;
    if (!effect->active) return;
    RenderIfUnmasked(effect);
}
}
