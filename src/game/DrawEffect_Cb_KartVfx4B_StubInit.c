typedef struct KartVfx4BEffect {
    unsigned char pad000[0x14];
    unsigned char slot[0x14];
    unsigned char visible;       /* 0x028 */
    unsigned char pad029[0xB4 - 0x29];
    signed char state;           /* 0x0B4 */
    unsigned char pad0b5[0x150 - 0xB5];
    float field150;              /* 0x150 */
} KartVfx4BEffect;

extern void VfxSlot_BindResource(void *slot, int res);

void DrawEffect_Cb_KartVfx4B_StubInit(KartVfx4BEffect *self)
{
    switch (self->state) {
    case 0:
        VfxSlot_BindResource(self->slot, 0x4B);
        self->visible = 0;
        self->field150 = 0.0f;
        self->state = 1;
        break;
    case 1:
        break;
    }
}
