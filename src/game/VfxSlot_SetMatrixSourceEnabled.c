/* Attach or detach the VfxSlot's own matrix as its model's matrix source. */
typedef struct VfxSlot {
    unsigned char pad00[0x4];
    void *model;           /* 0x04 */
    unsigned char pad08[0x2c];
    float mtx[3][4];       /* 0x34 */
} VfxSlot;

extern void cLNormal3DWrap_Slot_SetMatrixSource(void *model, float (*mtx)[4]);
extern void cLNormal3DWrap_Slot_ClearMatrixSource(void *model);

void VfxSlot_SetMatrixSourceEnabled(VfxSlot *self, signed char enable)
{
    void *model = self->model;

    if (model != 0) {
        if (enable) {
            cLNormal3DWrap_Slot_SetMatrixSource(model, self->mtx);
        } else {
            cLNormal3DWrap_Slot_ClearMatrixSource(model);
        }
    }
}
