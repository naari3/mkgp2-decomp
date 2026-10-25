typedef struct DrawEffectFreeView {
    unsigned char active;
    unsigned char pad01[0x13];
    unsigned char slot[1];
} DrawEffectFreeView;

extern void VfxSlot_Release(void *);

void DrawEffect_Free(DrawEffectFreeView *self)
{
    if (self != 0) {
        VfxSlot_Release(self->slot);
        self->active = 0;
    }
}
