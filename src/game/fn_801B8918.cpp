struct SpriteObj {
    char pad0[0xC];
    float x;
    float y;
    char pad14[0x30 - 0x14];

    SpriteObj(int anim, int loop, int arg);
};

extern "C" {
extern SpriteObj *lbl_806D1800;
extern int lbl_806D1804;
extern int lbl_806D1808;
extern unsigned char lbl_806D17F3;
extern const float lbl_806D98F8;
extern const float lbl_806D98FC;
void Sprite_SetAnimParam(void *sprite, int id, short value);
void fn_801A0550(void *sprite);
void Sprite_Destroy(void *sprite, int arg);
}

static inline void SpriteObj_SetPos(SpriteObj *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}

extern "C" int fn_801B8918(int value) {
    if (!lbl_806D17F3) {
        return 0;
    }
    Sprite_Destroy(lbl_806D1800, 1);
    lbl_806D1804 = value;
    lbl_806D1800 = new SpriteObj(0xC8, 0, 0);
    Sprite_SetAnimParam(lbl_806D1800, 0x1AD4, value);
    fn_801A0550(lbl_806D1800);
    SpriteObj_SetPos(lbl_806D1800, lbl_806D98F8, lbl_806D98FC);
    lbl_806D1808 = 0;
    return 1;
}
