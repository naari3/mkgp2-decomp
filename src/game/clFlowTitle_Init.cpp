/* Title flow constructor. */
struct SpriteObj {
    char pad0[0x30];

    SpriteObj(int anim, int loop, float x, float y);
    SpriteObj(int anim, int loop, float x, float y, float sx, float sy, float a, float b);
};

struct InputView {
    unsigned char opaque[4];
    unsigned char enabled;
    unsigned char opaque5[0x13];
    int held;
    int edge;
};

struct FlowBase {
    void *vt;
    FlowBase();
    ~FlowBase();
};

struct TitleFlow : FlowBase {
    unsigned char unk4;
    unsigned char unk5;
    unsigned char unk6;
    unsigned char cleaning;
    int peerCount;
    float syncValue;
    int unk10;
    SpriteObj *logo;
    SpriteObj *bg;
    int unk1C;

    TitleFlow();
};

extern "C" {
extern InputView *g_pInputState;
extern void *lbl_8049A878[];
extern int lbl_8049A858[];
extern unsigned char lbl_80598A60[];
extern const float lbl_806D9960;
extern const float lbl_806D9964;
extern const float lbl_806D9970;
extern const float lbl_806D9974;
int CountPeersWithRole(int role);
void InitRumbleController(int arg);
float PcbSyncTable_GetMyValue(void);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
void SetLocalPcbRole(int role);
void SetSyncTarget(int target);
int SetupBgSprites(unsigned char enable);
void Sprite_SetAnimParam(void *sprite, int a, short b);
void card_send_cleaning_cmd_init(void);
void fn_801699D8(int a, int b);
}

static inline InputView *input_state() {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

TitleFlow::TitleFlow() {
    vt = lbl_8049A878;
    SetSyncTarget(7);
    SetLocalPcbRole(1);
    unk4 = 0;
    unk5 = 0;
    unk6 = 0;
    unk1C = 0;
    syncValue = PcbSyncTable_GetMyValue();
    peerCount = CountPeersWithRole(1);
    logo = new SpriteObj(0x1E5, 1, lbl_806D9960, lbl_806D9960);
    bg = new SpriteObj(0x5B, 0, lbl_806D9970, lbl_806D9974, lbl_806D9964, lbl_806D9964, lbl_806D9960, lbl_806D9964);
    unk10 = -1;
    cleaning = 1;
    Sprite_SetAnimParam(logo, 0x1B18, lbl_8049A858[peerCount]);
    if (!ServiceEnable_Get() || ServiceValue_Get()) {
        cleaning = 0;
    } else if (!lbl_80598A60[0x23] || !lbl_80598A60[0x24]) {
        cleaning = 0;
    }
    if (input_state()) {
        InputView *input = input_state();
        input->enabled = 1;
        input->held = 0;
        input->edge = 0;
    }
    SetupBgSprites(1);
    InitRumbleController(1);
    fn_801699D8(0, 1);
    fn_801699D8(1, 1);
    if (cleaning) {
        card_send_cleaning_cmd_init();
    } else {
        Sprite_SetAnimParam(logo, 0x1B21, 0x1B20);
    }
}
