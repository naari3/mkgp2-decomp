/* SpriteSlot_SetAnimFrameAndApplyScale (0x800D657C): select an animation of
 * a sprite slot, clamp the requested frame to the animation's end, and push
 * the resulting frame to the model. The same body is inlined into
 * SpriteSlot_TickAnim (see SpriteSlot_TickAnim.c). */

#include "game/types/SpriteAnimEntry.h"

#include "game/types/SpriteClassEntry.h"

#include "game/types/SpriteSlot.h"

extern SpriteClassEntry lbl_8041AC24[];

extern void clNormal3D_SetScale(void *m, int anim, float t, float a, float b, float c);
extern void Object_SetField14_IfValid(void *m, float v);

static inline SpriteAnimEntry *SpriteSlot_GetAnim(SpriteSlot *slot)
{
    return &lbl_8041AC24[slot->cls].anims[slot->anim];
}

static inline float SpriteSlot_GetFrame(SpriteSlot *slot)
{
    SpriteAnimEntry *e = SpriteSlot_GetAnim(slot);
    return e->start + slot->frame;
}

void SpriteSlot_SetAnimFrameAndApplyScale(SpriteSlot *slot, signed char anim, float frame)
{
    float t;

    if (slot->object == 0) {
        return;
    }
    slot->anim = anim;
    t = frame + lbl_8041AC24[slot->cls].anims[slot->anim].start;
    if (lbl_8041AC24[slot->cls].anims[slot->anim].end < t) {
        t = lbl_8041AC24[slot->cls].anims[slot->anim].end;
    }
    slot->state = 0;
    slot->frame = t - lbl_8041AC24[slot->cls].anims[slot->anim].start;
    clNormal3D_SetScale(slot->object, 0, SpriteSlot_GetFrame(slot), 1.0f, 0.0f,
                        0.0f);
    Object_SetField14_IfValid(slot->object, 0.0f);
}
