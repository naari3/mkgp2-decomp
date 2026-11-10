/* SpriteSlot_SetAnimFrameAndApplyScale (0x800D657C): select an animation of
 * a sprite slot, clamp the requested frame to the animation's end, and push
 * the resulting frame to the model. The same body is inlined into
 * SpriteSlot_TickAnim (see SpriteSlot_TickAnim.c). */

#include "game/types/SpriteAnimEntry.h"

typedef struct SpriteClassEntry {
    unsigned char pad0[4];
    SpriteAnimEntry *anims; /* 0x4 */
    unsigned char pad8[0xC];
} SpriteClassEntry;

typedef struct SpriteSlot {
    unsigned char pad0[4];
    void *model;       /* 0x04 */
    unsigned char cls; /* 0x08 */
    signed char anim;  /* 0x09 */
    signed char state; /* 0x0A */
    float frame;       /* 0x0C */
} SpriteSlot;

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

    if (slot->model == 0) {
        return;
    }
    slot->anim = anim;
    t = frame + lbl_8041AC24[slot->cls].anims[slot->anim].start;
    if (lbl_8041AC24[slot->cls].anims[slot->anim].end < t) {
        t = lbl_8041AC24[slot->cls].anims[slot->anim].end;
    }
    slot->state = 0;
    slot->frame = t - lbl_8041AC24[slot->cls].anims[slot->anim].start;
    clNormal3D_SetScale(slot->model, 0, SpriteSlot_GetFrame(slot), 1.0f, 0.0f,
                        0.0f);
    Object_SetField14_IfValid(slot->model, 0.0f);
}
