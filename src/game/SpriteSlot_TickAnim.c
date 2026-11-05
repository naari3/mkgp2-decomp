/* SpriteSlot_TickAnim (0x800D6F64): advance a sprite slot's animation frame
 * through its per-class animation table and push the result to the model.
 * SpriteSlot_SetAnimFrameAndApplyScale (0x800D657C, own TU) is inlined into
 * the "restart" state here, so its body is repeated as a static inline. */

typedef struct SpriteAnimEntry {
    signed char loop; /* 0x0 */
    float start;      /* 0x4 */
    float end;        /* 0x8 */
} SpriteAnimEntry;

typedef struct SpriteClassEntry {
    unsigned char pad0[4];
    SpriteAnimEntry *anims; /* 0x4 */
    unsigned char pad8[0xC];
} SpriteClassEntry;

typedef struct SpriteSlot {
    unsigned char pad0[4];
    void *model;          /* 0x04 */
    unsigned char cls;    /* 0x08 */
    signed char anim;     /* 0x09 */
    signed char state;    /* 0x0A */
    float frame;          /* 0x0C */
    float speed;          /* 0x10 */
    signed char animated; /* 0x14 */
} SpriteSlot;

extern SpriteClassEntry lbl_8041AC24[];

extern void clNormal3D_SetScale(void *m, int anim, float t, float a, float b, float c);
extern void Object_SetField14_IfValid(void *m, float v);
extern void Object_SetField8_10_14(void *m, float a, float b, float c);
extern void clNormal3D_Exec(void *m);
extern void Object_DriveAnimMatrix(void *m);

static inline SpriteAnimEntry *SpriteSlot_GetAnim(SpriteSlot *slot)
{
    return &lbl_8041AC24[slot->cls].anims[slot->anim];
}

static inline float SpriteSlot_GetFrame(SpriteSlot *slot)
{
    SpriteAnimEntry *e = SpriteSlot_GetAnim(slot);
    return e->start + slot->frame;
}

static inline void SpriteSlot_SetAnimFrame(SpriteSlot *slot, signed char anim, float frame)
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

static inline void SpriteSlot_UpdateAnim(SpriteSlot *slot)
{
    SpriteAnimEntry *e;
    float len;

    if (slot->model == 0) {
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
        Object_SetField8_10_14(slot->model, e->start + slot->frame, 0.0f,
                               e->start + slot->frame);
        clNormal3D_Exec(slot->model);
    }
}

void SpriteSlot_TickAnim(SpriteSlot *slot)
{
    if (slot->model == 0) {
        return;
    }
    SpriteSlot_UpdateAnim(slot);
    if (slot->animated) {
        Object_DriveAnimMatrix(slot->model);
    }
}
