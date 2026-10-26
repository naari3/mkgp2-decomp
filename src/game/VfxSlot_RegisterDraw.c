/* Queue a visible VFX slot for sorted drawing at its joint (or fixed)
 * position. Flag bits: 1 = no depth bias, 2 = hidden, 8 = fixed position. */
typedef struct Vec {
    float x, y, z;
} Vec;

typedef struct VfxSlot {
    signed char flags;          /* 0x00 */
    unsigned char pad01[0x3];
    void *slot;                 /* 0x04 */
    unsigned char pad08[0xc];
    signed char visible;        /* 0x14 */
    unsigned char pad15[0x3];
    float alpha;                /* 0x18 */
    unsigned char pad1c[0x50];
    Vec fixedPos;               /* 0x6C */
} VfxSlot;

extern void *lbl_806D10AC;
extern const float lbl_806D4FF8;
extern void VfxSlot_Render(void *self);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern void cLNormal3DWrap_Slot_GetOrLoadJointTransform(void *slot, Vec *out);
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

void VfxSlot_RegisterDraw(VfxSlot *self)
{
    Vec pos;
    int flags;

    if (self->slot == 0 || !self->visible || ((flags = self->flags) & 2)) {
        return;
    }
    if (self->alpha <= lbl_806D4FF8) {
        return;
    }
    if (!(flags & 8)) {
        cLNormal3DWrap_Slot_GetOrLoadJointTransform(self->slot, &pos);
    } else {
        Vec3_Copy(&pos, &self->fixedPos);
    }
    if (!(self->flags & 1)) {
        clDrawMan_AddSorted_DepthRange(DrawMan_Get(), VfxSlot_Render, self, pos.x, pos.y, pos.z, lbl_806D4FF8);
    } else {
        clDrawMan_AddSorted_NoDepthBias(DrawMan_Get(), VfxSlot_Render, self, pos.x, pos.y, pos.z, lbl_806D4FF8);
    }
}
