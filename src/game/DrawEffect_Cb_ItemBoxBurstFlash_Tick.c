typedef struct FlashVec3 {
    float x, y, z;
} FlashVec3;

typedef struct ItemBoxBurstFlash {
    unsigned char pad000[0x14];
    unsigned char slot[0xA];
    unsigned char animDone;      /* 0x01E */
    unsigned char pad01f[0x8C - 0x1F];
    FlashVec3 pos;               /* 0x08C */
    unsigned char pad098[0xB0 - 0x98];
    float scale;                 /* 0x0B0 */
    signed char state;           /* 0x0B4 */
} ItemBoxBurstFlash;

extern void VfxSlot_BindResource(void *slot, int res);
extern void VfxSlot_SetAnimSpeed(void *slot, float speed);
extern void VfxSlot_SetPositionFromVec(void *slot, const FlashVec3 *pos);
extern void VfxSlot_SetScaleUniform(void *slot, float scale);
extern void DrawEffect_Free(void *);

static inline int Flash_AnimDone(ItemBoxBurstFlash *self)
{
    return self->animDone;
}

void DrawEffect_Cb_ItemBoxBurstFlash_Tick(ItemBoxBurstFlash *self)
{
    FlashVec3 pos;

    switch (self->state) {
    case 0:
        VfxSlot_BindResource(self->slot, 0x8D);
        VfxSlot_SetAnimSpeed(self->slot, 1.0f);
        self->scale = 2.0f;
        pos = self->pos;
        VfxSlot_SetPositionFromVec(self->slot, &pos);
        VfxSlot_SetScaleUniform(self->slot, self->scale);
        self->state++;
        break;
    case 1:
        break;
    }
    if (Flash_AnimDone(self) == 1) {
        DrawEffect_Free(self);
    }
}
