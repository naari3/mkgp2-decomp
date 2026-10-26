/* Apply a visible sprite slot's colour and UV offset, then queue its
 * object for sorted drawing. Flag bits: 1 = no depth bias, 2 = hidden. */
typedef struct Vec {
    float x, y, z;
} Vec;

typedef struct SpriteSlot {
    unsigned char flags;        /* 0x00 */
    unsigned char pad01[0x3];
    void *object;               /* 0x04 */
    unsigned char pad08[0xc];
    signed char visible;        /* 0x14 */
    unsigned char pad15[0x3];
    float alpha;                /* 0x18 */
    float r, g, b;              /* 0x1C */
    unsigned char pad28[0x4];
    float u, v;                 /* 0x2C */
} SpriteSlot;

extern void *lbl_806D10AC;
extern const float lbl_806D5960;
extern void SpriteSlot_Render(void *object);
extern void Object_SetColorRGBA(void *object, int joint, float r, float g, float b, float a);
extern void JObjTree_TranslateAndMul(void *object, int joint, float u, float v);
extern void Object_GetJObjPositionVec(void *object, Vec *out);
extern void clDrawMan_AddSorted_DepthRange(void *man, void (*draw)(void *), void *obj,
                                           float x, float y, float z, float depth);
extern void clDrawMan_AddSorted_NoDepthBias(void *man, void (*draw)(void *), void *obj,
                                            float x, float y, float z, float depth);

static inline void *DrawMan_Get(void)
{
    void *man = lbl_806D10AC;
    if (man == 0) {
        man = 0;
    }
    return man;
}

void SpriteSlot_RegisterDraw(SpriteSlot *self)
{
    Vec pos;
    void *object;

    if (self->object == 0 || !self->visible || (self->flags & 2)) {
        return;
    }
    if (self->alpha <= lbl_806D5960) {
        return;
    }
    Object_SetColorRGBA(self->object, 0, self->r, self->g, self->b, self->alpha);
    JObjTree_TranslateAndMul(self->object, 0, self->u, self->v);
    object = self->object;
    Object_GetJObjPositionVec(object, &pos);
    if (!(self->flags & 1)) {
        clDrawMan_AddSorted_DepthRange(DrawMan_Get(), SpriteSlot_Render, object, pos.x, pos.y, pos.z, lbl_806D5960);
    } else {
        clDrawMan_AddSorted_NoDepthBias(DrawMan_Get(), SpriteSlot_Render, object, pos.x, pos.y, pos.z, lbl_806D5960);
    }
}
