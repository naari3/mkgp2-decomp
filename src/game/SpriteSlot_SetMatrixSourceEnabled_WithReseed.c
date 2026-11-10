/* Reseed through the same animation setter used by SpriteSlot_TickAnim. */
#include "game/SpriteSlot_WithReseed_private.h"
extern SpriteClassEntry g_itemDescriptorTable[];

extern void clNormal3D_SetScale(void *m, int anim, float t, float a, float b, float c);
extern void Object_SetField14_IfValid(void *m, float v);

static inline SpriteAnimEntry *SpriteSlot_GetAnim(SpriteSlot *slot)
{
    return &g_itemDescriptorTable[slot->cls].anims[slot->anim];
}

static inline float SpriteSlot_GetFrame(SpriteSlot *slot)
{
    SpriteAnimEntry *e = SpriteSlot_GetAnim(slot);
    return e->start + slot->frame;
}

static inline void SpriteSlot_SetAnimFrameAndApplyScale(SpriteSlot *slot, signed char anim, float frame)
{
    float t;

    if (slot->model == 0) {
        return;
    }
    slot->anim = anim;
    t = frame + g_itemDescriptorTable[slot->cls].anims[slot->anim].start;
    if (g_itemDescriptorTable[slot->cls].anims[slot->anim].end < t) {
        t = g_itemDescriptorTable[slot->cls].anims[slot->anim].end;
    }
    slot->state = 0;
    slot->frame = t - g_itemDescriptorTable[slot->cls].anims[slot->anim].start;
    clNormal3D_SetScale(slot->model, 0, SpriteSlot_GetFrame(slot), 1.0f, 0.0f,
                        0.0f);
    Object_SetField14_IfValid(slot->model, 0.0f);
}

extern void Object_BindMatrixSource(void *, void *, int);
extern void Object_ClearAnimBinding(void *);
#pragma exceptions on
void SpriteSlot_SetMatrixSourceEnabled_WithReseed(SpriteSlot *slot, signed char enabled)
{
    if (enabled) Object_BindMatrixSource(slot->model, slot->matrix, 0);
    else Object_ClearAnimBinding(slot->model);
    SpriteSlot_SetAnimFrameAndApplyScale(slot, slot->anim, slot->frame);
}
#pragma exceptions reset
