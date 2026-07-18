typedef struct SpriteSlot {
    unsigned char pad0[4];
    void *object;
} SpriteSlot;

extern void Object_SetJObjScaleXYZ(void *object, float x, float y, float z);

void SpriteSlot_SetScaleUniform(SpriteSlot *slot, float scale)
{
    if (slot->object != 0) {
        Object_SetJObjScaleXYZ(slot->object, scale, scale, scale);
    }
}

void SpriteSlot_SetScaleXYZ(SpriteSlot *slot, float x, float y, float z)
{
    if (slot->object != 0) {
        Object_SetJObjScaleXYZ(slot->object, x, y, z);
    }
}
