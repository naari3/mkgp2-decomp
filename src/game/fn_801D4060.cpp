/* Game-mode factory: allocates and constructs a mode object. */
struct SpriteObj {
    char pad0[0xC];
    float x;
    float y;
    char pad14[0x1C];

    SpriteObj(int anim, int loop, short *arg);
};

struct GameModeBase {
    void *vt;
    GameModeBase();
    ~GameModeBase();
};

extern "C" {
extern void *lbl_8049B5F4[];
extern short lbl_806CFEA8;
extern const float lbl_806DA07C;
void fn_8002CFB8(int a, int b, int c, int d);
void fn_8019FF6C(SpriteObj *sprite, int arg);
}

static inline void SpriteObj_SetPos(SpriteObj *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}

struct Mode801D4060 : GameModeBase {
    int unk4;
    SpriteObj *sprite;
    int unkC;

    Mode801D4060() {
        vt = lbl_8049B5F4;
        fn_8002CFB8(0x20, 0x60, 0x60, 0);
        unk4 = 0;
        unkC = 0;
        lbl_806CFEA8 = unk4;
        sprite = new SpriteObj(0x1EB, 1, &lbl_806CFEA8);
        SpriteObj_SetPos(sprite, lbl_806DA07C, lbl_806DA07C);
        fn_8019FF6C(sprite, 1);
    }
};

extern "C" Mode801D4060 *fn_801D4060(void) {
    return new Mode801D4060;
}
