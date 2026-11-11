extern "C" { int lbl_8049BBE8[5] = {6936, 6937, 6938, 6939, 7874}; }
/* Attract-mode flow constructor. */
#include "game/os_time.h"

struct SpriteObj {
    char pad0[0x30];

    SpriteObj(int anim, int loop, int arg);
    SpriteObj(int anim, int loop, float x, float y, float sx, float sy, float a, float b);
};

#include "game/types/InputView.h"

#include "game/types/clFlowProcess.h"
#include "game/singleton.h"

struct clFlowFigure : clFlowProcess {
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

    clFlowFigure();
    virtual ~clFlowFigure();
    virtual int Update();
    virtual void Draw();
};

extern "C" {
extern InputView *g_pInputState;
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
void Sprite_SetAnimParam(void *sprite, short a, short b);
void fn_801699D8(int a, int b);
}

extern "C" {
extern void fn_801A0004(void *obj);
extern void fn_801A1174(int id, int a, int b, int c, int d);
extern void fn_801A1128(float x, float y);
extern void fn_801A0DF0(void);

extern const float lbl_806DA210;
extern const float lbl_806DA214;
extern const float lbl_806DA218;
extern const float lbl_806DA21C;
extern const float lbl_806DA220;
extern const float lbl_806DA224;

extern void RumbleUpdate(void);
extern void PlaySoundDSP(int id);
extern unsigned char Sprite_AdvanceAnim(void *spr, float dt);
extern void Sprite_Destroy(void *spr, int flag);

extern void Sprite_SetAnimTime(void *spr, float time);
extern int CountPeersWithRole(int role);
extern float PcbSyncTable_GetMyValue(void);
extern void SetScreenBrightness(float brightness);
extern int fn_801DA1C4(void *self);
extern int lbl_8049BBE8[];

extern const float lbl_806DA234;
extern void MemoryManager_TimedFree(void *p);
extern void SetScreenBrightness(float level);
extern void Sprite_Destroy(void *sprite, int flag);

extern void dtor_801BA14C(void *self, int flag);
extern void fn_80120A08(int id);
extern void fn_801699D8(int a, int b);
extern void fn_80169C44(void);

}

static inline InputView *input_state() { return SINGLETON_INSTANCE(g_pInputState); }

clFlowFigure::clFlowFigure() {
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

clFlowFigure::~clFlowFigure() {
        if (input_state()) {
            InputView *input = input_state();
            input->enabled = 0;
            input->held = 0;
            input->edge = 0;
        }
        fn_801699D8(0, 0);
        fn_801699D8(1, 0);
        fn_80169C44();
        fn_80120A08(0x1B4C);
        fn_80120A08(0x1E86);
        Sprite_SetAnimParam(sprites[1], lbl_8049BBE8[peerCount], 0x1B18);
        Sprite_Destroy(sprites[0], 1);
        Sprite_Destroy(sprites[1], 1);
        Sprite_Destroy(sprites[2], 1);
        Sprite_Destroy(sprites[3], 1);
        Sprite_Destroy(sprites[4], 1);
        SetScreenBrightness(lbl_806DA234);
}

int clFlowFigure::Update() {
    OSTime now;
    int peers;

    RumbleUpdate();
    now = OSGetTime();
    if ((float)OSTicksToMilliseconds(now - startTime) / 1000.0f >= 4.0f) {
        startTime = now;
        PlaySoundDSP(0x271);
    }
    if (sprites[0] != 0) {
        Sprite_AdvanceAnim(sprites[0], 0.0165f);
    }
    if (sprites[3] != 0 && Sprite_AdvanceAnim(sprites[3], 0.0165f) == 0) {
        Sprite_Destroy(sprites[3], 1);
        sprites[3] = 0;
    }
    if (sprites[4] != 0) {
        Sprite_AdvanceAnim(sprites[4], 0.0165f);
    }
    peers = CountPeersWithRole(1);
    if (peerCount != peers) {
        if (sprites[1] != 0) {
            Sprite_SetAnimParam(sprites[1], lbl_8049BBE8[peerCount], lbl_8049BBE8[peers]);
        }
        peerCount = peers;
    }
    syncValue = PcbSyncTable_GetMyValue();
    SetScreenBrightness(syncValue);
    if (syncValue < 6.0f && sprites[2] != 0) {
        Sprite_SetAnimTime(sprites[2], 6.0f - syncValue);
    }
    return fn_801DA1C4(this);
}

void clFlowFigure::Draw() {
    if (sprites[0] != 0) {
        fn_801A0004(sprites[0]);
    }
    if (sprites[3] != 0) {
        fn_801A0004(sprites[3]);
    } else {
        fn_801A1174(0x1E86, 4, 0, 0, 0);
        fn_801A1128(lbl_806DA210, lbl_806DA214);
        fn_801A0DF0();
        fn_801A1174(0x1B4C, 4, 0, 0, 0);
        fn_801A1128(lbl_806DA210, lbl_806DA218);
        fn_801A0DF0();
        if (sprites[4] != 0) {
            fn_801A1174(0x1597, 4, 0, 0, 0);
        fn_801A1128(lbl_806DA21C, lbl_806DA220);
        fn_801A0DF0();
            fn_801A0004(sprites[4]);
        }
    }
    if (sprites[1] != 0) {
        fn_801A0004(sprites[1]);
    }
    if (syncValue < lbl_806DA224 && sprites[2] != 0) {
        fn_801A0004(sprites[2]);
    }
}
