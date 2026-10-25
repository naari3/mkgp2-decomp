typedef struct SpriteObj {
    char pad0[0xC];
    float x;
    float y;
} SpriteObj;

extern SpriteObj *lbl_806D1800;
extern int lbl_806D1804;
extern int lbl_806D1808;
extern unsigned char lbl_806D17F3;
extern void Sprite_SetupAnim(void *sprite, int anim, int loop, int arg);
extern void Sprite_SetAnimParam(void *sprite, int id, int value);
extern void fn_801A0550(void *sprite);
extern void fn_8019FF6C(void *sprite, int arg);
extern void Sprite_Destroy(void *sprite, int arg);
extern void *Alloc(int size);
extern const float lbl_806D98F8;
extern const float lbl_806D98FC;

static inline void SpriteObj_SetPos(SpriteObj *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}
extern void Sprite_InitWithAnim(void *sprite, int anim, int loop, int arg);

int fn_801B87D8(void) {
    SpriteObj *sprite = lbl_806D1800;
    if (sprite == 0) {
        return 0;
    }
    if (lbl_806D1808 != 1) {
        return 0;
    }
    Sprite_SetupAnim(sprite, 0xC7, 0, 0);
    Sprite_SetAnimParam(lbl_806D1800, 0x1AD4, (short)lbl_806D1804);
    fn_801A0550(lbl_806D1800);
    SpriteObj_SetPos(lbl_806D1800, lbl_806D98F8, lbl_806D98FC);
    fn_8019FF6C(lbl_806D1800, 0);
    lbl_806D1808 = 2;
    return 1;
}
