#include "game/anon_801FC1E0_private.h"

extern "C" CoinFlowScene *fn_801FC1E0(int arg) {
    return new CoinFlowScene(arg);
}

CoinFlowScene::~CoinFlowScene() {
    fn_80232284(ItemMsg_Get(), lbl_806DA800);
    if (detail) {
        fn_80161F28(detail, 1);
    }
    fn_8024E244(counter, 1);
    delete[] texts;
    CreditMgr_SetActiveSlot(0);
    fn_80218D90(0);
    {
        CardMode *mgr = fn_801DAEC0();
        mgr->light = 0;
    }
}

CoinFlowScene::CoinFlowScene(int arg)
    : FlowScene(arg), kind(2), field2C(0), field30(0), coins(CreditMgr_GetCoinCount(0, -1)),
      field3C(0), field40(0), counter(0), window(new CoinWindow),
      prompt(new CoinPrompt(0x74, 0x4A, 0x1874, 0x1875, 4)) {
    InputState *in;
    int jp;
    in = GetInput();
    in->enabled = 1;
    in->held = 0;
    int initialTimer = lbl_803BFF40[1];
    in->edge = 0;
    subState = 1;
    timer = initialTimer + 1;
    cursor = 0;
    state = 0;
    texts = new TextManager[3];
    texts[0].visible = 1;
    texts[1].visible = 1;
    texts[2].visible = 1;
    fn_801F93EC(&texts[0], lbl_806DA820, lbl_806DA824);
    fn_801F93EC(&texts[1], lbl_806DA820, lbl_806DA820);
    fn_801F93EC(&texts[2], lbl_806DA820, lbl_806DA828);
    jp = isJapanese() != 0;
    TexMgr_SetTexture(&texts[0], lbl_804EBF58[jp][0]);
    TexMgr_SetTexture(&texts[1], lbl_804EBF58[jp][1]);
    TexMgr_SetTexture(&texts[2], lbl_804EBF58[jp][2]);
    if (jp == 1) {
        texts[0].scale = lbl_806DA82C;
        texts[1].scale = lbl_806DA82C;
        texts[2].scale = lbl_806DA82C;
    }
    CreditMgr_SetActiveSlot(2);
    fn_80218D90(2);
    counter = new CoinCounter(2);
    fn_8023CEB4(prompt.p);
    fn_8023CD3C(prompt.p, lbl_806DA814, lbl_806DA818);
    fn_8023CCF8(prompt.p, lbl_806DA7EC, lbl_806DA7E8);
    fn_8023CD24(prompt.p, lbl_806DA810, lbl_806DA7E8);
    fn_8023CCCC(prompt.p, lbl_806DA7E4, lbl_806DA7E8);
    fn_8023CDA8(prompt.p);
    fn_8023CFD4(prompt.p);
    *((unsigned char *)window.p + 0x20) = 1;
}
