/* SpriteSlot_TickAnim (0x800D6F64): advance a sprite slot's animation frame
 * through its per-class animation table and push the result to the model.
 * SpriteSlot_SetAnimFrameAndApplyScale (0x800D657C, own TU) is inlined into
 * the "restart" state here, so its body is repeated as a static inline. */

#include "game/types/SpriteAnimEntry.h"

#include "game/types/SpriteClassEntry.h"

#include "game/types/SpriteSlot.h"

extern SpriteClassEntry g_itemDescriptorTable[];

extern void clNormal3D_SetScale(void *m, int anim, float t, float a, float b, float c);
extern void Object_SetField14_IfValid(void *m, float v);
extern void Object_SetField8_10_14(void *m, float a, float b, float c);
extern void clNormal3D_Exec(void *m);
extern void Object_DriveAnimMatrix(void *m);

static inline SpriteAnimEntry *SpriteSlot_GetAnim(SpriteSlot *slot)
{
    return &g_itemDescriptorTable[slot->cls].anims[slot->anim];
}

static inline float SpriteSlot_GetFrame(SpriteSlot *slot)
{
    SpriteAnimEntry *e = SpriteSlot_GetAnim(slot);
    return e->start + slot->frame;
}

static inline void SpriteSlot_SetAnimFrame(SpriteSlot *slot, signed char anim, float frame)
{
    float t;

    if (slot->object == 0) {
        return;
    }
    slot->anim = anim;
    t = frame + g_itemDescriptorTable[slot->cls].anims[slot->anim].start;
    if (g_itemDescriptorTable[slot->cls].anims[slot->anim].end < t) {
        t = g_itemDescriptorTable[slot->cls].anims[slot->anim].end;
    }
    slot->state = 0;
    slot->frame = t - g_itemDescriptorTable[slot->cls].anims[slot->anim].start;
    clNormal3D_SetScale(slot->object, 0, SpriteSlot_GetFrame(slot), 1.0f, 0.0f,
                        0.0f);
    Object_SetField14_IfValid(slot->object, 0.0f);
}

static inline void SpriteSlot_UpdateAnim(SpriteSlot *slot)
{
    SpriteAnimEntry *e;
    float len;

    if (slot->object == 0) {
        return;
    }
    e = SpriteSlot_GetAnim(slot);
    switch (slot->state) {
    case 0:
        slot->frame += slot->speed;
        len = e->end - e->start;
        if (slot->frame < 0.0f) {
            if (e->loop == 0) {
                slot->frame += len;
            } else {
                slot->frame = 0.0f;
            }
        }
        if (len <= slot->frame) {
            slot->frame = len;
            if (e->loop == 0) {
                slot->state = 2;
            } else {
                slot->state = 1;
            }
        }
        break;
    case 2:
        SpriteSlot_SetAnimFrame(slot, slot->anim, 0.0f);
        break;
    }
    if (slot->animated) {
        Object_SetField8_10_14(slot->object, e->start + slot->frame, 0.0f,
                               e->start + slot->frame);
        clNormal3D_Exec(slot->object);
    }
}

void SpriteSlot_TickAnim(SpriteSlot *slot)
{
    if (slot->object == 0) {
        return;
    }
    SpriteSlot_UpdateAnim(slot);
    if (slot->animated) {
        Object_DriveAnimMatrix(slot->object);
    }
}
