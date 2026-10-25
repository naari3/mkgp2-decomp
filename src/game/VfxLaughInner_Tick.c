typedef struct VfxLaughInner {
    unsigned char pad000[0x14];
    unsigned char slot[0x14];
    unsigned char visible;       /* 0x028 */
    unsigned char pad029[0xB4 - 0x29];
    signed char state;           /* 0x0B4 */
    unsigned char pad0b5[0x190 - 0xB5];
    unsigned char field190;      /* 0x190 */
} VfxLaughInner;

extern void VfxSlot_BindResourceEx(void *slot, int res, int flags);

void VfxLaughInner_Tick(VfxLaughInner *self)
{
    switch (self->state) {
    case 0:
        VfxSlot_BindResourceEx(self->slot, 0x56, 0);
        self->visible = 1;
        self->field190 = 0;
        self->state++;
        break;
    case 1:
        break;
    }
}
