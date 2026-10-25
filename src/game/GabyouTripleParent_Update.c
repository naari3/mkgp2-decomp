/* GabyouTripleParent_Update (0x800F4914): triple-gabyou (thumbtack) item
 * held over the kart. It shows three sprite children around a carried
 * gabyou. When released (sub flag at +0xA0 == 1) it launches three
 * GabyouTripleChild objects in a spread and frees itself. */
typedef struct { float v[3]; } FloatTriple;

extern const FloatTriple lbl_8032FA1C;
extern const FloatTriple lbl_8032FA10;
extern const float lbl_806D611C;
extern const float lbl_806D60D0;
extern const float lbl_806D6120;
extern const float lbl_806D60E8;
extern unsigned char *ItemObject_AllocFromPool(void (*fn)(void));
extern void *ItemObject_AllocGabyou(void);
extern void fn_800D748C(void);
extern void GabyouTripleChild_Update(void);
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_TickAnim(void *slot);
extern void SpriteSlot_Container_Free(void *self);
extern void Item_RenderFlyingFromKart(unsigned char *self, void *obj, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void Mtx_Copy(void *dst, void *src);
extern void Vec3_Copy(void *dst, void *src);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *src);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void Vec2_RotateY(void *dst, void *src, float a);

#define CHILD(i) (*(unsigned char **)(sub + 0x5C + (i) * 4))
#define HELD (*(unsigned char **)(sub + 0x68))
#define DRIVER (*(void **)(sub + 0x98))

void GabyouTripleParent_Update(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    unsigned char *c;
    int i;

    switch (*(signed char *)(self + 0xC8)) {
    case 0:
        *(float *)(self + 0xC4) = lbl_806D611C;
        *(float *)(self + 0x2C) = lbl_806D60D0;
        for (i = 0; i < 3; i++) {
            CHILD(i) = ItemObject_AllocFromPool(fn_800D748C);
            if (CHILD(i) != 0) {
                SpriteSlot_InitNonLoop(CHILD(i) + 0x14, 0x49);
                CHILD(i)[0x14] = 4;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(CHILD(i) + 0x14, 1);
                SpriteSlot_SetScale(CHILD(i) + 0x14, lbl_806D60D0);
                *(float *)(CHILD(i) + 0xC4) = *(float *)(self + 0xC4);
            }
        }
        HELD = ItemObject_AllocGabyou();
        if (HELD != 0) {
            *(int *)(HELD + 0x10) = 1;
        }
        self[0xC8]++;
    case 1:
        Item_RenderFlyingFromKart(self, HELD, 1, lbl_806D6120, lbl_806D60D0, lbl_806D611C);
        if (HELD != 0) {
            *(float *)(self + 0x20) = *(float *)(HELD + 0x20);
        }
        if (FinalLapCoinJump_CheckActiveForObject(DRIVER)) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
        for (i = 0; i < 3; i++) {
            if (CHILD(i) != 0) {
                CHILD(i)[0x28] = self[0x28];
                *(float *)(CHILD(i) + 0x2C) = *(float *)(self + 0x2C);
                Mtx_Copy(CHILD(i) + 0x48, self + 0x48);
                Vec3_Copy(CHILD(i) + 0xA0, self + 0xA0);
                SpriteSlot_SetAnimFrameAndApplyScale(CHILD(i) + 0x14, (signed char)(i + 1), *(float *)(self + 0x20));
                SpriteSlot_TickAnim(CHILD(i) + 0x14);
            }
        }
        if (*(signed char *)(sub + 0xA0)) {
            if (*(signed char *)(sub + 0xA0) == 1) {
                for (i = 0; i < 3; i++) {
                    c = ItemObject_AllocFromPool(GabyouTripleChild_Update);
                    if (c != 0) {
                        FloatTriple angles;
                        FloatTriple speeds;
                        *(int *)(c + 0x10) = i;
                        c[0x1DC] = sub[0xF0];
                        *(int *)(c + 0x1E0) = *(int *)(sub + 0xF4);
                        Mtx44_GetTranslation_RowMajor(c + 0xA0, KartDriver_GetJointByIdx(DRIVER, 0xC));
                        Vec3_Copy(c + 0x190, sub + 0xA4);
                        *(int *)(c + 0x180) = *(int *)(sub + 0x94);
                        *(void **)(c + 0x184) = DRIVER;
                        angles = lbl_8032FA10;
                        speeds = lbl_8032FA1C;
                        Item_InitLaunchFromKart(c, 0, lbl_806D60E8, speeds.v[*(int *)(self + 0x10)]);
                        Vec2_RotateY(c + 0xB8, c + 0xB8, angles.v[*(int *)(c + 0x10)]);
                    }
                }
            }
            for (i = 0; i < 3; i++) {
                SpriteSlot_Container_Free(CHILD(i));
                CHILD(i) = 0;
            }
            SpriteSlot_Container_Free(HELD);
            HELD = 0;
            SpriteSlot_Container_Free(self);
        }
        break;
    }
}
