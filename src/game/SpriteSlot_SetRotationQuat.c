typedef struct SpriteSlot {
    unsigned char pad0[4];
    void *object;
} SpriteSlot;

extern void JObj_SetRotationQuat(void *object, float x, float y, float z);

void SpriteSlot_SetRotationQuat(SpriteSlot *slot, float x, float y, float z)
{
    if (slot->object != 0) {
        JObj_SetRotationQuat(slot->object, x, y, z);
    }
}
