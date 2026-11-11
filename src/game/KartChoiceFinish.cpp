#include "game/singleton.h"
#include "game/SpritePairOwner.h"
#include "game/types/clGameOver.h"
struct FinishInput {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual float Axis();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual unsigned int Pressed(int);
};
struct FinishStatus { int a, b, active, mode; void SetActive(int v) { active = v; } void SetMode(int v) { mode = v; } };
extern "C" {
extern const float lbl_806DB9A8, lbl_806DB9AC, lbl_806DB9B0, lbl_806DB9B4;
extern const float lbl_806DB9C0, lbl_806DB9C4, lbl_806DB9C8, lbl_806DB9CC, lbl_806DB9D0, lbl_806DB9D4;
extern int g_gameMode, lbl_806D09C8, lbl_806D1ACC;
extern unsigned char lbl_806D12E2;
extern void *lbl_806D10A0;
void *GetInputManager();
FinishInput *InputMgr_GetPlayer(void *, int);
void fn_8011FAB8();
unsigned char fn_8019FE78(Sprite *);
FinishStatus *fn_801DAEC0();
void SetKartVariant(int);
void fn_8020F220();
void RankLog_Reset(void *);
void fn_80121210();
void fn_8012094C();
void clRom_PurgeAll();
void fn_801A0B70(int);
void *StrPcb_GetInstance();
void StrPcb_WaitForState1(void *);
void SetSyncTarget(int);
void ProcessSystemTick(int);
void PlayStats_EndPlaySession();
signed char GetDisplayBufferIndex();
void *GetDisplayContext(int);
void *memset(void *, int, unsigned long);
}
void clGameOver::Destroy() { delete this; }

clGameOver::clGameOver() : state(0), sprite(0), handle(-1), timer(0) {
    SetSyncTarget(0x34);
    lbl_806D12E2 = 1;
    ProcessSystemTick(0);
    PlayStats_EndPlaySession();
    ProcessSystemTick(0);
    fn_801DAEC0()->SetActive(1);
    fn_801DAEC0()->SetMode(0);
    if (GetInput()) {
        InputState *input = GetInput();
        input->enabled = 0;
        input->held = 0;
        input->edge = 0;
    }
    sprite = new Sprite(0x147, 1, 0);
    Sprite *positioned = sprite;
    positioned->x = lbl_806DB9C0;
    positioned->y = lbl_806DB9C0;
    ResCtrl res;
    res.mode = 2;
    res.width = lbl_806DB9C4;
    res.height = lbl_806DB9C8;
    res.flag = 1;
    res.x = lbl_806DB9CC;
    res.y = lbl_806DB9D0;
    res.z = lbl_806DB9D4;
    res.colors[0] = 0;
    res.colors[1] = 0;
    res.colors[2] = 0;
    res.colors[3] = 0;
    handle = SpriteHandle_CreateDefault(&res, 5);
    SpriteHandle_SetActiveFlag(handle, 0);
    SpriteHandle_RecomputeCull(handle);
    int buffer;
    int i;
    for (i = 0; i <= 3; ++i) {
        buffer = GetDisplayBufferIndex();
        memset(GetDisplayContext(i), buffer, 0x8000);
    }
    ProcessSystemTick(0);
}

clGameOver::~clGameOver() {
    if (sprite) delete sprite;
    SetKartVariant(0);
    g_gameMode = 0;
    fn_8020F220();
    if (SINGLETON_INSTANCE(lbl_806D10A0))
        RankLog_Reset(SINGLETON_INSTANCE(lbl_806D10A0));
    lbl_806D09C8 = -1;
    lbl_806D1ACC = 0;
    SpriteHandle_Destroy(handle);
    fn_80121210();
    fn_8012094C();
    clRom_PurgeAll();
    fn_801A0B70(0);
    StrPcb_WaitForState1(StrPcb_GetInstance());
    fn_801DAEC0()->SetActive(0);
}

void clGameOver::Update() {
    if (done == 1) return;
    unsigned char pressed;
    FinishInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    pressed = 1;
    if (!input->Pressed(0x2000) && !(input->Axis() >= lbl_806DB9A8)) pressed = 0;
    switch (state) {
    case 0:
        if (!fn_8019FE78(sprite)) { state = 1; timer = 0; }
        if (pressed) {
            state = 2;
            timer = 0;
            SpriteHandle_SetActiveFlag(handle, 1);
        }
        break;
    case 1:
        if (timer >= 40 || pressed) {
            timer = 0;
            state = 2;
            SpriteHandle_SetActiveFlag(handle, 1);
            fn_801DAEC0()->SetActive(0);
        }
        break;
    case 2:
        SpriteHandle_SetCornerAlpha(handle, lbl_806DB9AC * (timer / lbl_806DB9B0));
        if (timer >= 30) state = 3;
        break;
    case 3:
        done = 1;
        state = -1;
        break;
    }
    ++timer;
    Sprite_AdvanceAnim(sprite, lbl_806DB9B4);
    SpriteHandle_RecomputeCull(handle);
}

void clGameOver::Draw() {
    if (done != 1) { fn_801A0004(sprite); fn_8011FAB8(); }
}
