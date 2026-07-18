typedef struct SpriteSlot {
    unsigned char pad0[4];
    void *object;
    unsigned char pad8[8];
    float scale;
} SpriteSlot;

void SpriteSlot_SetScale(SpriteSlot *slot, float scale)
{
    if (slot->object == 0) {
        return;
    }
    slot->scale = scale;
}
