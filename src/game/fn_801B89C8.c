extern void *lbl_806D17F8;
extern void *lbl_806D17FC;
extern int g_gameMode;
extern void Sprite_SetupAnim(void *sprite, int anim, int loop, int arg);

int fn_801B89C8(unsigned char flag) {
    void *sprite = lbl_806D17FC;
    if (sprite == 0) {
        return 0;
    }
    if (flag) {
        Sprite_SetupAnim(sprite, 0x1E2, 1, 0);
    } else {
        switch (g_gameMode) {
        case 1:
            Sprite_SetupAnim(lbl_806D17F8, 0x199, 1, 0);
            break;
        case 2:
            Sprite_SetupAnim(lbl_806D17F8, 0x198, 1, 0);
            break;
        case 0:
        default:
            Sprite_SetupAnim(lbl_806D17F8, 0x197, 1, 0);
            break;
        }
    }
    return 1;
}
