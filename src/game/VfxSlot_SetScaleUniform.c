/* Uniform scale on a bound VfxSlot's model. */
typedef struct VfxSlot {
    unsigned char pad00[0x4];
    void *model; /* 0x04 */
} VfxSlot;

extern void cLNormal3DWrap_Slot_SetScaleVec3(void *model, float x, float y, float z);

void VfxSlot_SetScaleUniform(VfxSlot *self, float scale)
{
    void *model = self->model;

    if (model != 0) {
        cLNormal3DWrap_Slot_SetScaleVec3(model, scale, scale, scale);
    }
}
