extern void *lbl_806D180C;
extern int lbl_806D1810;
extern int lbl_806D1814;
extern signed char lbl_806D1818;
extern void Sprite_SetupAnim(void *sprite, int anim, int loop, int arg);
extern void Sprite_SetAnimParam(void *sprite, int id, int value);
extern void fn_801A0550(void *sprite);

int fn_801B8540(int value) {
    void *sprite = lbl_806D180C;
    if (sprite == 0) {
        return 0;
    }
    if (lbl_806D1818 != 1) {
        return 0;
    }
    lbl_806D1810 = 0;
    lbl_806D1818 = 2;
    if (lbl_806D1814 == 0xD) {
        Sprite_SetupAnim(sprite, 0x1A, 0, 0);
        Sprite_SetAnimParam(lbl_806D180C, 0x1D3E, value);
        fn_801A0550(lbl_806D180C);
    }
    return 1;
}
