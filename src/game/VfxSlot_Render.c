/* Push the slot's rotation and UV scroll to its model, then render it. */
typedef struct VfxSlot {
    unsigned char pad00[0x4];
    void *model;      /* 0x04 */
    unsigned char pad08[0x10];
    float quat[4];    /* 0x18: w, x, y, z */
    unsigned char pad28[0x4];
    float uvScroll[2]; /* 0x2C */
} VfxSlot;

extern void cLNormal3DWrap_Slot_SetRotationQuat(void *model, float x, float y, float z, float w);
extern void cLNormal3DWrap_Slot_AdvanceUVScrollWrapped(void *model, float u, float v);
extern void cLNormal3DWrap_Slot_Render(void *model);

void VfxSlot_Render(VfxSlot *self)
{
    void *model = self->model;

    cLNormal3DWrap_Slot_SetRotationQuat(model, self->quat[1], self->quat[2], self->quat[3],
                                        self->quat[0]);
    cLNormal3DWrap_Slot_AdvanceUVScrollWrapped(model, self->uvScroll[0], self->uvScroll[1]);
    cLNormal3DWrap_Slot_Render(model);
}
