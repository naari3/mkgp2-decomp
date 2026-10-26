/* Bind a VFX slot to a model resource like VfxSlot_BindResource; an unlit
 * slot (lit == 0) also gets render flag 0x800. */
typedef struct VfxSlot {
    unsigned char active;       /* 0x00 */
    unsigned char kind;         /* 0x01 */
    unsigned char pad02[0x2];
    void *slot;                 /* 0x04 */
    unsigned char resource;     /* 0x08 */
    unsigned char pad09;
    unsigned char animDone;     /* 0x0A */
    unsigned char pad0b;
    float animFrame;            /* 0x0C */
    float scale;                /* 0x10 */
    unsigned char visible;      /* 0x14 */
    unsigned char pad15[0x3];
    float alpha;                /* 0x18 */
    float pos[3];               /* 0x1C */
    unsigned char pad28[0x3c];
    void (*draw)(struct VfxSlot *self); /* 0x64 */
} VfxSlot;

extern void *lbl_806D14A8;
extern const float lbl_806D4FF8;
extern const float lbl_806D5008;
extern void *cLNormal3DWrap_Mgr_AcquireSlot(void *mgr, unsigned char resource, int flag);
extern void cLNormal3DWrap_Slot_SetAnimSpeed(void *slot, float speed);
extern void cLNormal3DWrap_Slot_SetRenderFlags(void *slot, int flags);
extern void GetSpawnPosition(float *out, float x, float y, float z);
extern void VfxSlot_RegisterDraw(VfxSlot *self);

void VfxSlot_BindResourceEx(VfxSlot *self, int resource, int lit)
{
    void *slot;

    self->active = 0;
    if (lit == 0) {
        self->kind = 0x10;
    } else {
        self->kind = 0x11;
    }
    self->resource = resource;
    self->slot = cLNormal3DWrap_Mgr_AcquireSlot(lbl_806D14A8, resource, 1);
    slot = self->slot;
    if (lit == 0) {
        cLNormal3DWrap_Slot_SetRenderFlags(slot, 0x800);
    }
    cLNormal3DWrap_Slot_SetAnimSpeed(slot, lbl_806D4FF8);
    self->scale = lbl_806D5008;
    self->visible = 1;
    self->alpha = lbl_806D5008;
    GetSpawnPosition(self->pos, lbl_806D5008, lbl_806D5008, lbl_806D5008);
    if (self->slot != 0) {
        self->animDone = 0;
        self->animFrame = lbl_806D4FF8;
    }
    self->draw = VfxSlot_RegisterDraw;
}
