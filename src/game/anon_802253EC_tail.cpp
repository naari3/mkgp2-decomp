#include "game/NetJoin_private.h"

void clCSSceneNextRaceBT::Destroy() {
    delete this;
}

extern "C" clCSSceneNextRaceBT *fn_80225F6C(void) {
    return new clCSSceneNextRaceBT;
}

void NetJoinPopup::Draw() {
    if (spr) {
        fn_801A0004(spr);
    }
    if (popup) {
        fn_8016039C(popup);
    }
}

void NetJoinPopup::Update() {
    InputState *in = GetInput();
    bool pressed = in->held == 1;
    switch (state) {
    case 0:
        if (timer <= 10) {
            boxes[2]->SetAlpha((int)(lbl_806DB3B0 * (timer / lbl_806DB3B4)));
        }
        if (!fn_8019FE78(spr)) {
            boxes[0]->SetActive(1);
            boxes[1]->SetActive(1);
            spr->alpha = lbl_806DB35C;
            popup = new CoinPopupDetail(0, 1, 9);
            state = 1;
            timer = 0;
        }
        break;
    case 1:
        ok = popup->Mode() == 0;
        if (popup->Mode() != 2) {
            state = 2;
            timer = 0;
        }
        break;
    case 2:
        if (popup->Closed() == 1) {
            Sprite_SetupAnim(spr, 0x11, 1, 0);
            boxes[0]->SetActive(0);
            boxes[1]->SetActive(0);
            state = 3;
            timer = 0;
        }
        break;
    case 3:
        if (timer <= 10) {
            boxes[2]->SetAlpha((int)(lbl_806DB3B0 * (lbl_806DB37C - timer / lbl_806DB3B4)));
        }
        if (timer >= 10 && !fn_8019FE78(spr)) {
            state = 4;
            timer = 0;
        }
        break;
    }
    timer++;
    if (popup) {
        fn_80160588(popup, in->dir, pressed);
    }
    if (spr) {
        Sprite_AdvanceAnim(spr, lbl_806DB3B8);
    }
    for (int i = 0; i < 3; i++) {
        if (boxes[i]) {
            boxes[i]->Cull();
        }
    }
}

NetJoinPopup::~NetJoinPopup() {
    if (popup) {
        fn_80161F28(popup, 1);
        popup = 0;
    }
    if (spr) {
        delete spr;
        spr = 0;
    }
    for (int i = 0; i < 3; i++) {
        if (boxes[i]) {
            delete boxes[i];
            boxes[i] = 0;
        }
    }
}

NetJoinPopup::NetJoinPopup() {
    state = 0;
    timer = 0;
    ok = 1;
    popup = 0;
    spr = 0;
    spr = new Sprite(0x12, 1, 0);
    spr->SetPos(lbl_806DB374, lbl_806DB3C8);
    spr->layer = 2;
    ResCtrl rc;
    rc.mode = 2;
    rc.SetSize(lbl_806DB380, lbl_806DB3A4);
    rc.Show(lbl_806DB374, lbl_806DB3A8, lbl_806DB37C);
    rc.SetColor(0);
    boxes[2] = new SpriteBox(&rc, 2);
    fn_80121E10(&rc);
    rc.resId = 0x1E88;
    rc.Show(lbl_806DB374, lbl_806DB3C8, lbl_806DB37C);
    boxes[0] = new SpriteBox(&rc, 2);
    boxes[0]->SetActive(0);
    fn_80121E10(&rc);
    rc.resId = 0x1AEA;
    rc.Show(lbl_806DB374, lbl_806DB3AC, lbl_806DB37C);
    boxes[1] = new SpriteBox(&rc, 2);
    boxes[1]->SetActive(0);
    for (int i = 0; i < 3; i++) {
        boxes[i]->Cull();
    }
    if (GetRankLog()) {
        TitleStats_ResetRaceStagingState(GetRankLog());
    }
    SetPcbSub(0);
}
