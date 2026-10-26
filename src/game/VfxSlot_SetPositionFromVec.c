/* Position a bound VfxSlot's model from a vector. */
typedef struct VfxSlot {
    unsigned char pad00[0x4];
    void *model; /* 0x04 */
} VfxSlot;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void cLNormal3DWrap_Slot_SetPositionXYZ(void *model, float x, float y, float z);

void VfxSlot_SetPositionFromVec(VfxSlot *self, const Vec3 *pos)
{
    void *model = self->model;

    if (model != 0) {
        cLNormal3DWrap_Slot_SetPositionXYZ(model, pos->x, pos->y, pos->z);
    }
}
