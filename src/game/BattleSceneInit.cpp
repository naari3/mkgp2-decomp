#include "game/types/reg_args.h"
#include "game/SceneRoleVariantCPrivate.h"
extern "C" {
void ItemDisplay_Start(void *, int);
void fn_8020F3F0();
void fn_8020F38C(int);
extern int g_gameMode;
void SetSyncTarget(int);
void PcbRole_PromoteToClientConfirmed(REG_ARGS1(int arg));
void PCBComm_PromoteToClientConfirmed();
FlowTask *fn_8024EDC4(int);
FlowTask *fn_8024DD04(int);
}
struct BattleSceneBoot : SceneRoleVariantCRoot {
    VHolder<FlowSceneList> list;
    int value;
    unsigned char flag;
    virtual void ExternalKey();
    BattleSceneBoot();
};
BattleSceneBoot::BattleSceneBoot() : list(new SceneListImpl), value(0), flag(0)
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
