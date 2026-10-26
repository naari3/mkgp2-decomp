/* Rotate a bound VfxSlot's model from a vector. */
typedef struct VfxSlot {
    unsigned char pad00[0x4];
    void *model; /* 0x04 */
} VfxSlot;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void cLNormal3DWrap_Slot_SetRotationXYZ(void *model, float x, float y, float z);

void VfxSlot_SetRotationXYZFromVec(VfxSlot *self, const Vec3 *rot)
{
    void *model = self->model;

    if (model != 0) {
        cLNormal3DWrap_Slot_SetRotationXYZ(model, rot->x, rot->y, rot->z);
    }
}
