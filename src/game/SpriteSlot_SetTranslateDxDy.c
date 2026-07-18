typedef struct SpriteSlot {
    unsigned char pad0[0x2C];
    float translate_dx;
    float translate_dy;
} SpriteSlot;

void SpriteSlot_SetTranslateDxDy(SpriteSlot *slot, float dx, float dy)
{
    if (slot == 0) {
        return;
    }
    slot->translate_dx = dx;
    slot->translate_dy = dy;
}
