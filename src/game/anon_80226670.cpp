#include "game/types/size_t.h"
#include "game/singleton.h"
/*
 * 0x80226670..0x80226954: single-play join message scene (vtable
 * clCSSceneNextRaceGP_vtable_804EDF64, base clSceneInterface lbl_803FE0C8). Shows one FlowPanel
 * message and counts the join. RTTI names: clCSSceneNextRaceGP : clSceneInterface.
 * The TU owns the vtable and RTTI (0x804EDF58..0x804EDF80, .sdata 0x806D0530).
 */

void *operator new(size_t size);
void operator delete(void *p) throw();

#include "game/types/InputState.h"

struct FlowPanel {
    int state;
    char pad04[0x64];
    FlowPanel();
};

struct RankLog;

extern "C" {
extern InputState *g_pInputState;
extern RankLog *lbl_806D10A0;
extern int lbl_806D12C0;
extern int lbl_806D1ACC;
extern int g_ccClass;
extern const float lbl_806DB3D0;
extern const float lbl_806DB3D4;
extern const float lbl_806DB3D8;
void fn_801D9B70(FlowPanel *self, int pressed);
void fn_801D9F88(FlowPanel *self, short flag);
void clFlowKart_SetupTextLayout(FlowPanel *self, int layout);
void RankLog_OnRoundComplete(RankLog *log);
void TitleStats_ResetRaceStagingState(RankLog *log);
void PlayStats_IncSinglePlayJoin(void);
void fn_801D9A2C(FlowPanel *panel);
}

static inline InputState *GetInput() {
    return SINGLETON_INSTANCE(g_pInputState);
}

static inline RankLog *GetRankLog() {
    return SINGLETON_INSTANCE(lbl_806D10A0);
}

#include "game/types/clSceneInterface.h"

struct clCSSceneNextRaceGP : clSceneInterface {
    int state;
    float time;
    FlowPanel *panel;
    clCSSceneNextRaceGP();
    ~clCSSceneNextRaceGP();
    void Destroy();
    void Update();
    void Draw();
};

void clCSSceneNextRaceGP::Draw() {
    fn_801D9A2C(panel);
}

void clCSSceneNextRaceGP::Update() {
    int pressed = GetInput()->held == 1 ? 1 : 0;
    if (done == 1) {
        return;
    }
    if (state == 3) {
        done = 1;
        return;
    }
    switch (state) {
    case 0:
        if (time >= lbl_806DB3D4) {
            time = lbl_806DB3D8;
            state = 1;
            clFlowKart_SetupTextLayout(panel, 0xD);
        }
        break;
    case 1:
        if (panel->state == 0) {
            time = lbl_806DB3D8;
            state = 2;
        }
        break;
    case 2:
        if (time >= lbl_806DB3D4) {
            time = lbl_806DB3D8;
            state = 3;
        }
        break;
    }
    time += lbl_806DB3D0;
    fn_801D9B70(panel, pressed);
}

clCSSceneNextRaceGP::~clCSSceneNextRaceGP() {
    if (panel) {
        fn_801D9F88(panel, 1);
        panel = 0;
    }
}

void clCSSceneNextRaceGP::Destroy() {
    delete this;
}

inline clCSSceneNextRaceGP::clCSSceneNextRaceGP() {
    state = 0;
    time = lbl_806DB3D8;
    panel = 0;
    panel = new FlowPanel;
    lbl_806D12C0++;
    if (g_ccClass == 2) {
        lbl_806D1ACC++;
    }
    if (GetRankLog()) {
        RankLog_OnRoundComplete(GetRankLog());
        TitleStats_ResetRaceStagingState(GetRankLog());
    }
    PlayStats_IncSinglePlayJoin();
}

extern "C" clCSSceneNextRaceGP *fn_80226860(void) {
    return new clCSSceneNextRaceGP;
}
