typedef struct VfxSlot {
    void* unk0;
    void* slot;
} VfxSlot;

extern void cLNormal3DWrap_Slot_SetScaleVec3(void* slot, const void* scale);

void VfxSlot_SetScaleVec3(VfxSlot* vfx, const void* scale)
{
    if (vfx->slot != 0) {
        cLNormal3DWrap_Slot_SetScaleVec3(vfx->slot, scale);
    }
}
