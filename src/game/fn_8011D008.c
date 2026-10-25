extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern unsigned char *ItemObject_SpawnWithAlias(int kind, int alias);
extern void SpriteSlot_Container_Free(void *self);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern float lbl_806D6D28;
extern float lbl_806D6D3C;
extern float lbl_806D6D4C;

void fn_8011D008(unsigned char *self)
{
    int i;
    unsigned char *o;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x84);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        *(float *)(self + 0x2C) = lbl_806D6D28;
        self[0xC8] = 1;
    case 1:
        break;
    }
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(self + 0x184))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    if (*(signed char *)(self + 0x18C)) {
        if (*(signed char *)(self + 0x18C) == 1) {
            for (i = 0; i < 3; i++) {
                o = ItemObject_SpawnWithAlias(0x8D, 0xFF);
                if (o) {
                    *(int *)(o + 0x10) = i;
                    *(int *)(o + 0x180) = *(int *)(self + 0x180);
                    *(int *)(o + 0x184) = *(int *)(self + 0x184);
                }
            }
        }
        SpriteSlot_Container_Free(self);
    } else {
        GabyouItem_BuildLocalTransformFromHandJoint(self, 1, lbl_806D6D3C, lbl_806D6D28, lbl_806D6D4C);
    }
}
