/*
 * 0x8020D1C0..0x8020DAA0: card attract flow. Shows the "insert card / press
 * start" screen, waits for a credit and picks the next sync target.
 */

#include "game/FlowScene.h"
#include "game/os_time.h"

#pragma auto_inline off

struct Sprite {
    char pad[0x30];
    Sprite(int anim, int loop, int arg);
    Sprite(int anim, int loop, float x, float y, float sx, float sy, float a, float b);
};

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual unsigned char Trigger(int mask);
    virtual unsigned int Pressed(int mask);
    virtual unsigned int Held(int mask);
};

/* Flow base (ctor InitializeFrameSelection, dtor dtor_801BA14C). */
struct FlowBase {
    FlowBase();
    virtual ~FlowBase();
    virtual int Update();
    virtual void Draw();
};

extern "C" {
extern unsigned char lbl_806D117C;
extern int lbl_806D11A8;
extern int g_gameMode;
extern const int lbl_804ECA18[5];
extern const float lbl_806DAC58;
extern const float lbl_806DAC5C;
extern const float lbl_806DAC68;
extern const float lbl_806DAC6C;
extern const float lbl_806DAC70;
extern const float lbl_806DAC74;
extern const float lbl_806DAC78;
extern const float lbl_806DAC7C;
extern const float lbl_806DAC80;
extern const float lbl_806DAC84;
extern const float lbl_806DAC88;
extern const float lbl_806DAC8C;
extern const float lbl_806DAC90;
extern const float lbl_806DAC94;
extern const float lbl_806DAC98;
extern const float lbl_806DAC9C;
extern const float lbl_806DACA0;
extern const float lbl_806DACA4;
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void SetRumbleMode(int a, int b, int c);
void RumbleUpdate(void);
void InitRumbleController(int arg);
int PcbSync_CountPeersAtSyncTargetPair_1_or_2(void);
signed char PcbSync_AnyPeerAtState5(void);
int CountPeersInBattleWithRole(int role);
float PcbSyncTable_GetMyValue(void);
void SetSyncTarget(int target);
void SetLocalPcbRole(int role);
void SetTimerModeEnabled(int on);
unsigned char CreditMgr_AcceptorIsAbsent(void);
unsigned char CreditMgr_TryConfirmPlay(int slot);
void PlayStats_IncSinglePlayJoin(void);
void PlayStats_BeginPlaySession(void);
void PlaySoundDSP(int id);
void SetScreenBrightness(float v);
void PreloadResource(int id);
void fn_80120A08(int id);
void fn_801699D8(int a, int b);
void fn_80169C44(void);
void fn_801A0004(Sprite *sprite);
void fn_801A1174(int id, int a, int b, int c, int d);
void fn_801A1128(float x, float y);
void fn_801A0DF0(void);
unsigned char Sprite_AdvanceAnim(Sprite *sprite, float dt);
void Sprite_SetAnimParam(Sprite *sprite, short id, short value);
void Sprite_SetAnimTime(Sprite *sprite, float t);
void Sprite_Destroy(Sprite *sprite, int del);
}

struct CardAttractFlow : FlowBase {
    unsigned char f04;
    signed char peerCount;
    signed char role;
    signed char wait;
    float sync;
    float coins;
    int state;
    int pad14;
    OSTime startTime;
    Sprite *sprites[5];
    CardAttractFlow();
    virtual ~CardAttractFlow();
    virtual int Update();
    virtual void Draw();
    int Step();
    inline void CheckCoins() {
        if (coins != CreditMgr_GetCoinCount(0, -1)) {
            lbl_806D11A8 = 1;
        }
    }
};

int CardAttractFlow::Step() {
    InputPlayer *in;
    unsigned char go;

    if (state != -1) {
        return state;
    }
    in = InputMgr_GetPlayer(GetInputManager(), 0);
    if (in->Trigger(0x400)) {
        SetRumbleMode(1, 1, 1);
    }
    go = 0;
    if (wait != 0) {
        wait--;
    } else if (GetInput()->held == 1) {
        go = 1;
    }
    if (!lbl_806D117C) {
        if (coins != CreditMgr_GetCoinCount(0, -1)) {
            go = 1;
        }
    }
    if (sync <= lbl_806DAC58 || PcbSync_CountPeersAtSyncTargetPair_1_or_2() == 0) {
        state = 2;
        SetSyncTarget(state);
        SetLocalPcbRole(0);
    } else if (go) {
        unsigned char ok = 0;
        if (CreditMgr_AcceptorIsAbsent()) {
            ok = 1;
            PlayStats_IncSinglePlayJoin();
            PlayStats_BeginPlaySession();
        } else if (CreditMgr_TryConfirmPlay(0)) {
            ok = 1;
        }
        if (ok) {
            SetRumbleMode(0, 1, 1);
            if (sync <= lbl_806DAC5C || in->Held(0x400)) {
                SetLocalPcbRole(0);
                g_gameMode = 0;
                SetTimerModeEnabled(0);
                state = 9;
            } else {
                lbl_806D11A8 = 1;
                SetLocalPcbRole(role);
                state = 0x31;
            }
            SetSyncTarget(state);
        } else {
            CheckCoins();
        }
    } else {
        CheckCoins();
    }
    coins = CreditMgr_GetCoinCount(0, -1);
    return state;
}

void CardAttractFlow::Draw() {
    if (sprites[0] != 0) {
        fn_801A0004(sprites[0]);
    }
    if (sprites[3] != 0) {
        fn_801A0004(sprites[3]);
    } else {
        fn_801A1174(0x1E86, 4, 0, 0, 0);
        fn_801A1128(lbl_806DAC68, lbl_806DAC6C);
        fn_801A0DF0();
        fn_801A1174(0x1B4C, 4, 0, 0, 0);
        fn_801A1128(lbl_806DAC68, lbl_806DAC70);
        fn_801A0DF0();
        if (sprites[4] != 0) {
            fn_801A1174(0x1597, 4, 0, 0, 0);
            fn_801A1128(lbl_806DAC74, lbl_806DAC78);
            fn_801A0DF0();
            fn_801A0004(sprites[4]);
        }
    }
    if (sprites[1] != 0) {
        fn_801A0004(sprites[1]);
    }
    if (sync < lbl_806DAC7C && sprites[2] != 0) {
        fn_801A0004(sprites[2]);
    }
}

int CardAttractFlow::Update() {
    OSTime now;
    int n;

    RumbleUpdate();
    now = OSGetTime();
    if (OSTicksToMilliseconds(now - startTime) / lbl_806DAC80 >= lbl_806DAC84) {
        startTime = now;
        PlaySoundDSP(0x271);
    }
    if (sprites[0] != 0) {
        Sprite_AdvanceAnim(sprites[0], lbl_806DAC88);
    }
    if (sprites[3] != 0) {
        if (!Sprite_AdvanceAnim(sprites[3], lbl_806DAC88)) {
            Sprite_Destroy(sprites[3], 1);
            sprites[3] = 0;
        }
    }
    if (sprites[4] != 0) {
        Sprite_AdvanceAnim(sprites[4], lbl_806DAC88);
    }
    n = CountPeersInBattleWithRole(role);
    if (peerCount != n) {
        if (sprites[1] != 0) {
            Sprite_SetAnimParam(sprites[1], lbl_804ECA18[peerCount], lbl_804ECA18[n]);
        }
        peerCount = n;
    }
    sync = PcbSyncTable_GetMyValue();
    SetScreenBrightness(sync);
    {
        float s = sync;
        if (s < lbl_806DAC7C && sprites[2] != 0) {
            Sprite_SetAnimTime(sprites[2], lbl_806DAC7C - s);
        }
    }
    return Step();
}

CardAttractFlow::~CardAttractFlow() {
    if (GetInput()) {
        InputState *in = GetInput();
        in->enabled = 0;
        in->held = 0;
        in->edge = 0;
    }
    fn_801699D8(0, 0);
    fn_801699D8(1, 0);
    fn_80169C44();
    fn_80120A08(0x1B4C);
    fn_80120A08(0x1E86);
    Sprite_SetAnimParam(sprites[1], lbl_804ECA18[peerCount], 0x1B18);
    Sprite_Destroy(sprites[0], 1);
    Sprite_Destroy(sprites[1], 1);
    Sprite_Destroy(sprites[2], 1);
    Sprite_Destroy(sprites[3], 1);
    Sprite_Destroy(sprites[4], 1);
    SetScreenBrightness(lbl_806DAC8C);
}

CardAttractFlow::CardAttractFlow() {
    SetSyncTarget(0x30);
    role = PcbSync_AnyPeerAtState5();
    SetLocalPcbRole(role);
    PreloadResource(0x1B4C);
    PreloadResource(0x1E86);
    sprites[0] = new Sprite(0x1E2, 1, 0);
    sprites[1] = new Sprite(0x1E4, 1, lbl_806DAC90, lbl_806DAC94, lbl_806DAC98, lbl_806DAC98, lbl_806DAC58, lbl_806DAC98);
    sprites[2] = new Sprite(0x5B, 0, lbl_806DAC68, lbl_806DAC9C, lbl_806DAC98, lbl_806DAC98, lbl_806DAC58, lbl_806DAC98);
    sprites[3] = new Sprite(0x10, 0, lbl_806DAC68, lbl_806DAC6C, lbl_806DAC98, lbl_806DAC98, lbl_806DAC58, lbl_806DAC98);
    sprites[4] = new Sprite(0x14, 1, lbl_806DACA0, lbl_806DACA4, lbl_806DAC98, lbl_806DAC98, lbl_806DAC58, lbl_806DAC98);
    state = -1;
    peerCount = CountPeersInBattleWithRole(role);
    sync = PcbSyncTable_GetMyValue();
    coins = CreditMgr_GetCoinCount(0, -1);
    wait = 2;
    InitRumbleController(1);
    fn_801699D8(0, 1);
    fn_801699D8(1, 1);
    Sprite_SetAnimParam(sprites[1], 0x1B18, lbl_804ECA18[peerCount]);
    if (GetInput()) {
        InputState *in = GetInput();
        in->enabled = 1;
        in->held = 0;
        in->edge = 0;
    }
}
