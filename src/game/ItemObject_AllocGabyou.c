typedef struct GabyouSprite {
    unsigned char pad000[0x10];
    int variant;                 /* 0x010 */
    unsigned char slotMode;      /* 0x014 = SpriteSlot */
    unsigned char slot[0x13];
    unsigned char visible;       /* 0x028 */
    unsigned char pad029[0xC8 - 0x29];
    unsigned char state;         /* 0x0C8 */
    unsigned char pad0c9[0x100 - 0xC9];
    float field100;              /* 0x100 */
} GabyouSprite;

extern GabyouSprite *ItemObject_AllocFromPool(void (*update)(void));
extern void fn_800D748C(void);
extern void SpriteSlot_InitNonLoop(void *slot, int model);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float t);
extern void SpriteSlot_SetScale(void *slot, float scale);

GabyouSprite *ItemObject_AllocGabyou(void)
{
    GabyouSprite *e = ItemObject_AllocFromPool(fn_800D748C);
    if (e != 0) {
        SpriteSlot_InitNonLoop(&e->slotMode, 0x9C);
        e->slotMode = 4;
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(&e->slotMode, 1);
        if (e->variant == 0) {
            SpriteSlot_SetAnimFrameAndApplyScale(&e->slotMode, 1, 0.0f);
        } else {
            SpriteSlot_SetAnimFrameAndApplyScale(&e->slotMode, 0, 0.0f);
        }
        SpriteSlot_SetScale(&e->slotMode, 1.3f);
        e->visible = 0;
        e->field100 = 0.0f;
        e->state = 1;
    }
    return e;
}
