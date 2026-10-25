/*
 * 0x8020DAA0..0x8020E2D8: card cleaning flow. Waits for the peers, then lets
 * the operator open the cleaning dialog and runs the card cleaning command.
 */

#include "game/FlowScene.h"
#include "game/os_time.h"

#pragma auto_inline off

struct Sprite {
    char pad[0x30];
    Sprite(int anim, int loop, float x, float y);
    Sprite(int anim, int loop, float x, float y, float sx, float sy, float a, float b);
};

/* Yes / no dialog (0x8C bytes, ctor fn_80161914). */
struct Dialog {
    char pad00[0x10];
    int phase;
    int pad14;
    int result;
    char pad1C[0x39 - 0x1C];
    unsigned char f39;
    char pad3A[0x8C - 0x3A];
    Dialog(int a, int b, int c);
    int Result() { return phase < 2 ? 2 : result; }
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

struct ServiceInfo {
    char pad00[0x23];
    unsigned char f23;
    unsigned char f24;
};

extern "C" {
extern int g_localPcbRole;
extern int g_gameMode;
extern ServiceInfo lbl_80598A60;
extern const int lbl_804ECA50[5];
extern const float lbl_806DACA8;
extern const float lbl_806DACAC;
extern const float lbl_806DACB0;
extern const float lbl_806DACB4;
extern const float lbl_806DACB8;
extern const float lbl_806DACBC;
extern const float lbl_806DACC0;
extern const float lbl_806DACC4;
extern const float lbl_806DACC8;
extern const float lbl_806DACCC;
extern const float lbl_806DACD0;
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void SetRumbleMode(int a, int b, int c);
void RumbleUpdate(void);
void InitRumbleController(int arg);
int PcbSync_CountPeersAtSyncTargetPair_0_or_1(void);
unsigned char PCBComm_ConfirmHostBattle(void);
int CountPeersInBattleWithRole(int role);
float PcbSyncTable_GetMyValue(void);
void SetSyncTarget(int target);
void SetLocalPcbRole(int role);
void SetTimerModeEnabled(int on);
void SetPcbScratchFlag_806d11a4(void);
void SetScreenBrightness(float v);
void SetupBgSprites(int arg);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
void card_cleaning_state_machine(void);
void card_send_cleaning_cmd_init(void);
void fn_801699D8(int a, int b);
void fn_80169C44(void);
void fn_801A0004(Sprite *sprite);
unsigned char Sprite_AdvanceAnim(Sprite *sprite, float dt);
void Sprite_SetAnimParam(Sprite *sprite, short id, short value);
void Sprite_SetAnimTime(Sprite *sprite, float t);
void Sprite_Destroy(Sprite *sprite, int del);
void fn_80161F28(Dialog *dlg, int del);
void fn_801618CC(Dialog *dlg, int a, int b);
void fn_80161888(Dialog *dlg);
void fn_80160588(Dialog *dlg, int dir, unsigned char edge);
void fn_8016039C(Dialog *dlg);
}

struct CardCleanFlow : FlowBase {
    int peerCount;
    unsigned char waiting;
    unsigned char active;
    unsigned char finished;
    unsigned char cleaning;
    float sync;
    OSTime startTime;
    int state;
    Sprite *icon;
    Sprite *fade;
    Dialog *dialog;
    CardCleanFlow();
    virtual ~CardCleanFlow();
    virtual int Update();
    virtual void Draw();
    int Step();
};

int CardCleanFlow::Step() {
    SetSyncTarget(0x32);
    if (waiting) {
        if (PcbSync_CountPeersAtSyncTargetPair_0_or_1() == 0) {
            fn_80161F28(dialog, 1);
            waiting = 0;
            startTime = OSGetTime();
            active = 0;
            finished = 0;
            dialog = 0;
        }
    } else {
        OSTime now = OSGetTime();
        if (OSTicksToMilliseconds(now - startTime) / lbl_806DACA8 >= lbl_806DACAC && PCBComm_ConfirmHostBattle()) {
            if (g_localPcbRole != 0) {
                g_gameMode = 2;
                SetTimerModeEnabled(1);
            } else {
                g_gameMode = 0;
                SetTimerModeEnabled(0);
            }
            state = 9;
        }
    }
    return state;
}

void CardCleanFlow::Draw() {
    if (icon != 0) {
        fn_801A0004(icon);
    }
    if (sync < lbl_806DACB0 && fade != 0) {
        fn_801A0004(fade);
    }
    if (dialog != 0) {
        fn_8016039C(dialog);
    }
}

int CardCleanFlow::Update() {
    InputPlayer *in;
    int n;

    RumbleUpdate();
    if (cleaning) {
        card_cleaning_state_machine();
    }
    n = CountPeersInBattleWithRole(g_localPcbRole);
    if (peerCount != n) {
        if (icon != 0) {
            Sprite_SetAnimParam(icon, lbl_804ECA50[peerCount], lbl_804ECA50[n]);
        }
        peerCount = n;
    }
    sync = PcbSyncTable_GetMyValue();
    SetScreenBrightness(sync);
    {
        float s = sync;
        if (s < lbl_806DACB0 && fade != 0) {
            Sprite_SetAnimTime(fade, lbl_806DACB0 - s);
        }
    }
    if (icon != 0) {
        Sprite_AdvanceAnim(icon, lbl_806DACC0);
    }
    if (state == -1) {
        Step();
        if (state != -1) {
            return state;
        }
    }
    in = InputMgr_GetPlayer(GetInputManager(), 0);
    if (waiting) {
        int st = state;
        if (st == -1) {
            if (active) {
                int dir = 0;
                unsigned char edge = 0;
                if (finished) {
                    if (dialog != 0 && dialog->phase == 6) {
                        fn_80161F28(dialog, 1);
                        dialog = 0;
                        active = 0;
                    }
                } else if (sync < lbl_806DACC4) {
                    if (dialog != 0) {
                        fn_801618CC(dialog, 1, 0);
                        fn_80161888(dialog);
                    }
                    finished = 1;
                } else {
                    InputState *ip = GetInput();
                    if (ip != 0) {
                        unsigned char e = ip->held == 1;
                        dir = ip->dir;
                        edge = e;
                        if (e) {
                            SetRumbleMode(0, 1, 1);
                        }
                    }
                }
                if (dialog != 0) {
                    fn_80160588(dialog, dir, edge);
                    if (!finished) {
                        if (dialog->Result() == 1) {
                            fn_80161888(dialog);
                            finished = 1;
                        } else if (dialog->Result() == 0) {
                            fn_80161888(dialog);
                            finished = 1;
                            g_gameMode = 0;
                            SetTimerModeEnabled(0);
                            SetLocalPcbRole(0);
                            state = 9;
                        }
                    }
                }
            } else if (sync > lbl_806DACC8 && in->Pressed(0x400)) {
                SetRumbleMode(1, 1, 1);
                active = 1;
                finished = 0;
                dialog = new Dialog(1, 0, 9);
                dialog->f39 = 1;
            }
        } else if (dialog != 0) {
            if (dialog->phase == 6) {
                return st;
            }
            fn_80160588(dialog, 0, 0);
        } else {
            return st;
        }
    }
    if (sync > lbl_806DACCC && in->Pressed(0x2000)) {
        SetRumbleMode(0, 1, 1);
        SetPcbScratchFlag_806d11a4();
    }
    return -1;
}

CardCleanFlow::~CardCleanFlow() {
    fn_801699D8(0, 0);
    fn_801699D8(1, 0);
    fn_80169C44();
    if (GetInput()) {
        InputState *in = GetInput();
        in->enabled = 0;
        in->held = 0;
        in->edge = 0;
    }
    if (icon != 0) {
        Sprite_SetAnimParam(icon, lbl_804ECA50[peerCount], 0x1B18);
    }
    fn_80161F28(dialog, 1);
    Sprite_Destroy(icon, 1);
    Sprite_Destroy(fade, 1);
    SetScreenBrightness(lbl_806DACD0);
}

CardCleanFlow::CardCleanFlow() {
    SetSyncTarget(0x32);
    SetLocalPcbRole(5);
    waiting = 1;
    startTime = OSGetTime();
    active = 0;
    finished = 0;
    dialog = 0;
    sync = PcbSyncTable_GetMyValue();
    peerCount = CountPeersInBattleWithRole(g_localPcbRole);
    icon = new Sprite(0x1E5, 1, lbl_806DACCC, lbl_806DACCC);
    fade = new Sprite(0x5B, 0, lbl_806DACB4, lbl_806DACB8, lbl_806DACBC, lbl_806DACBC, lbl_806DACCC, lbl_806DACBC);
    state = -1;
    cleaning = 1;
    Sprite_SetAnimParam(icon, 0x1B18, lbl_804ECA50[peerCount]);
    if (!ServiceEnable_Get() || ServiceValue_Get()) {
        cleaning = 0;
    } else if (!lbl_80598A60.f23 || !lbl_80598A60.f24) {
        cleaning = 0;
    }
    if (GetInput()) {
        InputState *in = GetInput();
        in->enabled = 1;
        in->held = 0;
        in->edge = 0;
    }
    SetupBgSprites(1);
    InitRumbleController(1);
    fn_801699D8(0, 1);
    fn_801699D8(1, 1);
    if (cleaning) {
        card_send_cleaning_cmd_init();
    } else {
        Sprite_SetAnimParam(icon, 0x1B21, 0x1B20);
    }
}
