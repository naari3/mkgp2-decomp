/* Game-mode factory: allocates the voice mode and the shared display context. */
struct DisplayContext {
    char pad0[0xD8];
    DisplayContext();
};

struct GameModeBase {
    void *vt;
    GameModeBase();
    ~GameModeBase();
};

extern "C" {
extern void *lbl_8049A214[];
extern DisplayContext *lbl_806D1880;
extern const float lbl_806D986C;
void fn_8002CFB8(int a, int b, int c, int d);
void VoiceSystem_Init(void);
}

struct Mode801B7624 : GameModeBase {
    DisplayContext *display;
    int unk8;
    float unkC;

    Mode801B7624() {
        vt = lbl_8049A214;
        fn_8002CFB8(0, 0, 0, 0);
        VoiceSystem_Init();
        if (lbl_806D1880 == 0) {
            lbl_806D1880 = new DisplayContext;
        }
        display = lbl_806D1880;
        unk8 = 0;
        unkC = lbl_806D986C;
    }
};

extern "C" Mode801B7624 *fn_801B7624(void) {
    return new Mode801B7624;
}
