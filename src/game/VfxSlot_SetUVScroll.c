extern void SpriteSlot_SetTranslateDxDy(void* slot, float dx, float dy);

void VfxSlot_SetUVScroll(void* slot, float dx, float dy)
{
    SpriteSlot_SetTranslateDxDy(slot, dx, dy);
}
