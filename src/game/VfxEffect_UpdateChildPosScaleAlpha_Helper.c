/* Per-frame update of a VFX effect child: restart its animation when
 * asked, hide it once it is dying, and move/scale/fade its slot. */
typedef struct Vec {
    float x, y, z;
} Vec;

typedef struct VfxEffectChild {
    unsigned char pad000[0x14];
    unsigned char slot[0xa];  /* 0x14: VfxSlot */
    char kind;                /* 0x1E */
    unsigned char pad01f[0x9];
    unsigned char visible;    /* 0x28 */
    unsigned char pad029[0x3];
    float alpha;              /* 0x2C */
    unsigned char pad030[0x5c];
    Vec pos;                  /* 0x8C */
    unsigned char pad098[0x18];
    float scale;              /* 0xB0 */
    unsigned char pad0b4[0x9c];
    float fade;               /* 0x150 */
    unsigned char pad154[0x3c];
    signed char dying;        /* 0x190 */
    signed char restart;      /* 0x191 */
} VfxEffectChild;

extern void Vec3_Copy(Vec *dst, const Vec *src);
extern void VfxSlot_SetPositionFromVec(void *slot, const Vec *pos);
extern void VfxSlot_SetAnimFrame(void *slot, float frame);
extern void VfxSlot_SetScaleUniform(void *slot, float scale);
extern const float lbl_806D555C;
extern const float lbl_806D55DC;

void VfxEffect_UpdateChildPosScaleAlpha_Helper(VfxEffectChild *self, float scale, float alpha, const Vec *pos)
{
    if (self != 0) {
        if (self->restart && !self->dying) {
            VfxSlot_SetAnimFrame(self->slot, lbl_806D555C);
            self->visible = 1;
            self->restart = 0;
        }
        if (self->kind == 1) {
            self->visible = 0;
        }
        if (self->dying) {
            self->visible = 0;
        }
        Vec3_Copy(&self->pos, pos);
        {
            Vec p = self->pos;
            VfxSlot_SetPositionFromVec(self->slot, &p);
        }
        self->scale = lbl_806D55DC * scale;
        VfxSlot_SetScaleUniform(self->slot, self->scale);
        self->alpha = alpha;
    }
}
