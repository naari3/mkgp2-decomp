typedef struct UVScrollEffect {
    unsigned char pad000[0x14];
    unsigned char slot[0x14];
    unsigned char visible;       /* 0x028 */
    unsigned char pad029[0xB4 - 0x29];
    signed char state;           /* 0x0B4 */
    unsigned char pad0b5[0x150 - 0xB5];
    float field150;              /* 0x150 */
    unsigned char pad154[0x180 - 0x154];
    unsigned int timers[4];      /* 0x180 */
} UVScrollEffect;

extern void VfxSlot_BindResourceEx(void *slot, int res, int flags);
extern void VfxSlot_SetUVScroll(void *slot, float u, float v);

void DrawEffect_Cb_UVScroll_Tick(UVScrollEffect *self)
{
    switch (self->state) {
    case 0:
        VfxSlot_BindResourceEx(self->slot, 0x3E, 0);
        VfxSlot_SetUVScroll(self->slot, 0.0f, 0.033333335f);
        self->visible = 0;
        self->field150 = 0.0f;
        self->timers[0] = 0;
        self->state++;
        break;
    case 1:
        break;
    }
    if (self->timers[0] != 0) {
        self->timers[0]--;
    }
    if (self->timers[1] != 0) {
        self->timers[1]--;
    }
    if (self->timers[2] != 0) {
        self->timers[2]--;
    }
    if (self->timers[3] != 0) {
        self->timers[3]--;
    }
}
