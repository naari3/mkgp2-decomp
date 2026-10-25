/* Attract-mode flow constructor. */
#include "game/os_time.h"

struct SpriteObj {
    char pad0[0x30];

    SpriteObj(int anim, int loop, int arg);
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

struct AttractFlow : FlowBase {
    unsigned char unk4;
    signed char peerCount;
    unsigned char phase;
    char pad_7;
    float syncValue;
    float coins;
    int unk10;
    char pad_14[4];
    OSTime startTime;
    SpriteObj *sprites[5];

    AttractFlow();
};

extern "C" {
extern InputView *g_pInputState;
extern void *lbl_8049BC08[];
extern int lbl_8049BBE8[];
extern const float lbl_806DA200;
extern const float lbl_806DA210;
extern const float lbl_806DA214;
extern const float lbl_806DA238;
extern const float lbl_806DA23C;
extern const float lbl_806DA240;
extern const float lbl_806DA244;
extern const float lbl_806DA248;
extern const float lbl_806DA24C;
int CountPeersWithRole(int role);
int CreditMgr_GetCoinCount(int a, int b);
void InitRumbleController(int arg);
float PcbSyncTable_GetMyValue(void);
void PreloadResource(int id);
void SetLocalPcbRole(int role);
void SetSyncTarget(int target);
void Sprite_SetAnimParam(void *sprite, int a, short b);
void fn_801699D8(int a, int b);
}

static inline InputView *input_state() {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

AttractFlow::AttractFlow() {
    vt = lbl_8049BC08;
    SetSyncTarget(6);
    SetLocalPcbRole(0);
    PreloadResource(0x1B4C);
    PreloadResource(0x1E86);
    sprites[0] = new SpriteObj(0x1E2, 1, 0);
    sprites[1] = new SpriteObj(0x1E4, 1, lbl_806DA238, lbl_806DA23C, lbl_806DA240, lbl_806DA240, lbl_806DA200, lbl_806DA240);
    sprites[2] = new SpriteObj(0x5B, 0, lbl_806DA210, lbl_806DA244, lbl_806DA240, lbl_806DA240, lbl_806DA200, lbl_806DA240);
    sprites[3] = new SpriteObj(0x10, 0, lbl_806DA210, lbl_806DA214, lbl_806DA240, lbl_806DA240, lbl_806DA200, lbl_806DA240);
    sprites[4] = new SpriteObj(0x14, 1, lbl_806DA248, lbl_806DA24C, lbl_806DA240, lbl_806DA240, lbl_806DA200, lbl_806DA240);
    peerCount = CountPeersWithRole(1);
    unk10 = -1;
    syncValue = PcbSyncTable_GetMyValue();
    coins = CreditMgr_GetCoinCount(0, -1);
    startTime = OSGetTime();
    phase = 2;
    InitRumbleController(1);
    fn_801699D8(0, 1);
    fn_801699D8(1, 1);
    Sprite_SetAnimParam(sprites[1], 0x1B18, lbl_8049BBE8[peerCount]);
    if (input_state()) {
        InputView *input = input_state();
        input->enabled = 1;
        input->held = 0;
        input->edge = 0;
    }
}
