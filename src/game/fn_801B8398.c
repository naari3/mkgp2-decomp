extern void *lbl_806D180C;
extern signed char lbl_806D1818;
extern unsigned char lbl_806D1819;
extern void Sprite_SetupAnim(void *sprite, int anim, int loop, int arg);
extern void Sprite_SetAnimParam(void *sprite, int id, int value);
extern void fn_801A0550(void *sprite);
extern void fn_8019FF6C(void *sprite, int arg);

int fn_801B8398(int value) {
    void *sprite = lbl_806D180C;
    if (sprite == 0) {
        return 0;
    }
    if (lbl_806D1818 <= 1) {
        Sprite_SetupAnim(sprite, 0x1B, 0, 0);
        Sprite_SetAnimParam(lbl_806D180C, 0x1D3E, value);
        fn_801A0550(lbl_806D180C);
    } else {
        Sprite_SetupAnim(sprite, 0x13, 1, 0);
    }
    lbl_806D1818 = 4;
    return 1;
}
