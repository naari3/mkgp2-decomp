typedef struct HaloVec3 {
    float x, y, z;
} HaloVec3;

typedef struct KartHaloPlate {
    unsigned char pad000[0x10];
    int variant;                 /* 0x010 */
    unsigned char slot[0x78];    /* 0x014 */
    HaloVec3 pos;                /* 0x08C */
    unsigned char pad098[0xB0 - 0x98];
    float scale;                 /* 0x0B0 */
    signed char state;           /* 0x0B4 */
} KartHaloPlate;

extern void VfxSlot_BindResourceEx(void *slot, int res, int flags);
extern void VfxSlot_SetPositionFromVec(void *slot, const HaloVec3 *pos);
extern void VfxSlot_SetScaleUniform(void *slot, float scale);

void DrawEffect_Cb_KartHaloPlate_Init(KartHaloPlate *self)
{
    HaloVec3 pos;

    switch (self->state) {
    case 0:
        VfxSlot_BindResourceEx(self->slot, 0x75, 0);
        switch (self->variant) {
        case 0:
            self->scale = 0.6f;
            break;
        case 1:
            self->scale = 0.3f;
            break;
        case 2:
            self->scale = 0.3f;
            break;
        }
        pos = self->pos;
        VfxSlot_SetPositionFromVec(self->slot, &pos);
        VfxSlot_SetScaleUniform(self->slot, self->scale);
        self->state++;
        break;
    case 1:
        break;
    }
}
