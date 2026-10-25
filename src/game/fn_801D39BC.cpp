/* Game-mode factory: allocates and constructs a mode object. */
struct SpriteObj {
    char pad0[0xC];
    float x;
    float y;
    char pad14[0x1C];

    SpriteObj(int anim, int loop, int arg);
};

struct GameModeBase {
    void *vt;
    GameModeBase();
    ~GameModeBase();
};

extern "C" {
extern void *lbl_8049B5D4[];
extern const float lbl_806DA034;
extern const float lbl_806DA038;
void fn_8002CFB8(int a, int b, int c, int d);
void fn_8019FF6C(SpriteObj *sprite, int arg);
}

static inline void SpriteObj_SetPos(SpriteObj *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}

struct Mode801D39BC : GameModeBase {
    int unk4;
    int unk8;
    int unkC;
    SpriteObj *sprite;

    Mode801D39BC() {
        vt = lbl_8049B5D4;
        fn_8002CFB8(0, 0x8F, 0, 0);
        unk4 = 0;
        unk8 = 0;
        sprite = new SpriteObj(0, 1, 0);
        fn_8019FF6C(sprite, 1);
        SpriteObj_SetPos(sprite, lbl_806DA034, lbl_806DA038);
    }
};

extern "C" Mode801D39BC *fn_801D39BC(void) {
    return new Mode801D39BC;
}
