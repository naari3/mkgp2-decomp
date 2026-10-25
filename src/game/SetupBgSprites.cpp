struct SpriteObj {
    char pad0[0x30];

    SpriteObj(int anim, int loop, int arg);
};

extern "C" {
extern int g_gameMode;
extern int lbl_806CFD60;
extern SpriteObj *lbl_806D17F8;
extern SpriteObj *lbl_806D17FC;
void Sprite_Destroy(void *sprite, int arg);
}

extern "C" int SetupBgSprites(unsigned char enable) {
    if (lbl_806CFD60 >= 0 && enable == 1) {
        return 0;
    }
    if (lbl_806CFD60 == -1 && enable == 0) {
        return 0;
    }
    if (enable) {
        lbl_806CFD60 = 0;
        switch (g_gameMode) {
        case 1:
            lbl_806D17F8 = new SpriteObj(0x199, 1, 0);
            break;
        case 2:
            lbl_806D17F8 = new SpriteObj(0x198, 1, 0);
            break;
        case 0:
        default:
            lbl_806D17F8 = new SpriteObj(0x197, 1, 0);
            break;
        }
        lbl_806D17FC = new SpriteObj(0x4B, 1, 0);
    } else {
        Sprite_Destroy(lbl_806D17F8, 1);
        Sprite_Destroy(lbl_806D17FC, 1);
        lbl_806CFD60 = -1;
        lbl_806D17F8 = 0;
        lbl_806D17FC = 0;
    }
    return 1;
}
