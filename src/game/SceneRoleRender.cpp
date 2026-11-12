#include "game/FlowScene.h"
#include "game/singleton.h"
#include "game/types/clSceneInterface.h"
#include "game/types/reg_args.h"

struct clRsContinue00 : clSceneInterface {
    virtual ~clRsContinue00();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    VHolder<FlowSceneList> list;
    int result;
    unsigned char missing;
    unsigned char align11[3];
    clRsContinue00();
};

struct SceneRoleResult { unsigned char pad00[0x24]; int value; };
struct ItemDisplay;
struct RankLog;
extern "C" {
extern unsigned char lbl_806D0988[8], lbl_806D0980[8];
extern RankLog *lbl_806D10A0;
extern unsigned char lbl_806D17F0;
SceneRoleResult *fn_80271340(void *, int, void *, void *, int);
ItemDisplay *ItemDisplay_GetOrCreate();
void fn_8020AAD4(ItemDisplay *);
void TitleStats_ResetRaceStagingState(RankLog *);
void RankLog_Reset(RankLog *);
void HSD_StateInvalidate(unsigned int);
void ItemDisplay_Start(ItemDisplay *, int);
void fn_8020F3F0();
void fn_8020F38C(int);
extern int g_gameMode;
void SetSyncTarget(int);
void PcbRole_PromoteToClientConfirmed(REG_ARGS1(int arg));
void PCBComm_PromoteToClientConfirmed();
FlowTask *fn_8024EDC4(int);
FlowTask *fn_8024DD04(int);
}
static inline RankLog *RoleRankLog() { return SINGLETON_INSTANCE(lbl_806D10A0); }

/* Deferred generation: reverse target address order. */
clRsContinue00::clRsContinue00() : list(new SceneListImpl), result(0), missing(0)
{
    ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1ADC);
    InputState *in = GetInput();
    in->enabled = 1;
    in->held = 0;
    in->edge = 0;
    fn_8020F3F0();
    fn_8020F38C(0);
    if (g_gameMode == 2) {
        SetSyncTarget(0x31);
        PcbRole_PromoteToClientConfirmed(REG_ARGS1(0)); /* the callee only returns its argument, and the result is dropped */
        PCBComm_PromoteToClientConfirmed();
        FlowSceneList *target = list.p;
        fn_801F4DF0(target, fn_8024EDC4(0), 0x28);
    } else {
        FlowSceneList *target = list.p;
        fn_801F4DF0(target, fn_8024DD04(0), 0x28);
    }
}

clRsContinue00::~clRsContinue00() {
    fn_801F4D3C(list.p);
    fn_8020AAD4(ItemDisplay_GetOrCreate());
}
extern "C" clRsContinue00 *fn_8024D140() { return new clRsContinue00; }
void clRsContinue00::Destroy() { delete this; }
void clRsContinue00::Update() {
    if (!done) {
        FlowTask *task = fn_801F4DC0(list.p, 0);
        if (task) {
            result = fn_80271340(task, 0, lbl_806D0988, lbl_806D0980, 0)->value;
        } else {
            fn_8020AAD4(ItemDisplay_GetOrCreate());
            missing = 1;
        }
        if (list.p->entries.count <= 0) {
            done = 1;
            fn_8020AAD4(ItemDisplay_GetOrCreate());
            RankLog *log = RoleRankLog();
            if (log) {
                if (lbl_806D17F0 == 1) {
                    TitleStats_ResetRaceStagingState(log);
                } else {
                    RankLog_Reset(log);
                }
            }
        }
        list.p->Update();
    }
}

void clRsContinue00::Draw() {
    if (!done) {
        list.p->Draw();
        HSD_StateInvalidate(~0U);
    }
}
