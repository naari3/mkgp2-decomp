#ifndef CARD_SETUP_FLOW_VIEW_H
#define CARD_SETUP_FLOW_VIEW_H
#include "CardPrintFlowView.h"
struct SetupName { char pad[0x134]; int phase; unsigned char Done() { return phase == 5 ? true : false; } };
struct SetupReceipt { int phase; char pad[0x1C]; unsigned char accepted; char tail[15]; SetupReceipt(int); unsigned char Done() { return phase == 5 ? true : false; } };
/* Layout follows the seven setup-flow target functions, not CardPrintOwner. */
struct CardSetupFlow {
    virtual void SetupKey();
    unsigned char done;
    char pad[3];
    FlowSceneList *list;
    FlowFaderI *fader;
    int state;
    int selection;
    SetupName *name;
    PrintKart *kart;
    SetupReceipt *receipt;
};
typedef char SetupOwnerSize[sizeof(CardSetupFlow) == 0x24 ? 1 : -1];
struct SetupDialog : FlowTask { char pad[0x48]; SetupDialog(int, int); };
struct SetupChoiceView { char pad[0x20]; int result; int selection; };
extern "C" {
extern char lbl_806D0920[8], lbl_806D0900[8], lbl_806D08F8[8], lbl_806D0910[8], lbl_806D0908[8];
void *fn_80271340(void *, int, const void *, const void *, int);
void fn_801FEF18(void *, int);
void fn_80201148(void *);
void fn_801FFFF4(void *);
void fn_802043B8(FlowSceneList *, int);
void PlayStats_AccumulatePlayTime(int);
void *ItemDisplay_GetOrCreate();
void ItemDisplay_Start(void *, int);
void fn_8020AAD4(void *);
void fn_801BDB60(SetupName *);
void fn_801BE170(SetupName *);
void fn_801D9A2C(PrintKart *);
void HSD_StateInvalidate(int);
void fn_8020F3F0();
void fn_8020F38C(int);
void fn_8020F35C();
void card_force_backup_now();
void PreloadResource(int);
}
struct SetupPrintPanel {
    int busy, layout;
    char pad[0x18];
    unsigned char visible, active;
    char tail[0x46];
    SetupPrintPanel();
};
extern "C" void fn_801D9F88(SetupPrintPanel *, short);
struct SetupPanelHolder {
    SetupPrintPanel *p;
    SetupPanelHolder(SetupPrintPanel *q) : p(q) {}
    ~SetupPanelHolder() throw() { fn_801D9F88(p, 1); }
};
struct SetupPrintTask : FlowTask {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    SetupPanelHolder panel;
    int phase, error;
    virtual void Key();
    SetupPrintTask() : FlowTask(3), list(new SceneListImpl), fader(new FlowFaderI), panel(new SetupPrintPanel), phase(0) {
        PreloadResource(0x1ECD);
        PreloadResource(0x72F);
        PreloadResource(0x734);
        fader.p->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
        panel.p->visible = 1;
        panel.p->active = 0;
        if (fn_8020F280() == 1) clFlowKart_SetupTextLayout((PrintKart *)panel.p, 2);
        else clFlowKart_SetupTextLayout((PrintKart *)panel.p, 5);
        fn_8020F3F0();
        fn_8020F38C(1);
        fn_8020F35C();
    }
};
typedef char SetupTaskSize[sizeof(SetupPrintTask) == 0x24 ? 1 : -1];
typedef char SetupPanelSize[sizeof(SetupPrintPanel) == 0x68 ? 1 : -1];
#endif
