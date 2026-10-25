/*
 * Card-flow manager singleton @ 0x801FE3BC..0x801FE4D0
 * (instance lbl_806D19D8, vtable lbl_804EC1AC, base vtable lbl_804EC1B8).
 */

#include "game/FlowScene.h"

extern "C" {
extern const char lbl_803BFF84[];
void DebugPrintf(const char *fmt, ...);
void fn_801F98CC(void);
void fn_80209FE8(void);
}

struct CardFlowMgrBase {
    virtual ~CardFlowMgrBase();
    char pad04[0x164];
    CardFlowMgrBase() { Init(); }
    void Init();
};

struct CardFlowMgr : CardFlowMgrBase {
    int field168;
    int field16C;
    int field170;
    int field174;
    int field178;
    int field17C;
    int field180;
    int pad184;
    int field188;
    int field18C;
    int field190;
    unsigned char flag194;
    unsigned char flag195;
    unsigned char flag196;
    unsigned char flag197;
    CardFlowMgr() : flag194(0), flag195(0), flag196(0), flag197(0) {
        DebugPrintf(lbl_803BFF84);
        fn_801F98CC();
        fn_80209FE8();
        field168 = 0;
        field16C = 0;
        field170 = 0;
        field174 = 1;
        field178 = 0;
        field17C = 0;
        field180 = 0;
        field188 = 0x2B;
        field18C = 0x2D;
        field190 = 0x32;
    }
    virtual ~CardFlowMgr(); /* fn_801FE4D0, defined in dtor_801FE870.cpp */
    virtual void _key();
};

extern "C" CardFlowMgr *lbl_806D19D8;

extern "C" void fn_801FE3BC(void) {
    if (lbl_806D19D8) {
        delete lbl_806D19D8;
        lbl_806D19D8 = 0;
    }
}

extern "C" CardFlowMgr *fn_801FE404(void) {
    if (lbl_806D19D8 == 0) {
        lbl_806D19D8 = new CardFlowMgr;
    }
    return lbl_806D19D8;
}
