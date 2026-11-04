#include "game/anon_80224ECC_private.h"

void clCSSceneBanner::Draw() {
    if (spr) {
        fn_801A0004(spr);
    }
    obj->Draw();
}

void clCSSceneBanner::Update() {
    if (done == 1) {
        return;
    }
    bool pressed = false;
    if (GetInput()->held == 1) {
        pressed = true;
    }
    switch (state) {
    case 0:
        SpriteHandle_SetCornerAlpha(fade, (int)(lbl_806DB320 * (timer / lbl_806DB324)));
        if (timer >= 30) {
            state = 1;
            timer = 0;
        }
        break;
    case 1:
        spr->alpha = timer / lbl_806DB328;
        if (timer >= 20) {
            state = 2;
            timer = 0;
        }
        break;
    case 2:
        if (timer >= 120 || pressed) {
            state = 3;
            timer = 0;
        }
        break;
    case 3:
        spr->alpha = lbl_806DB32C - timer / lbl_806DB328;
        if (timer >= 20) {
            state = 4;
            timer = 0;
        }
        break;
    case 4:
        SpriteHandle_SetCornerAlpha(fade, (int)lbl_806DB330);
        if (timer >= 30) {
            done = 1;
        }
        break;
    }
    timer++;
    if (spr) {
        Sprite_AdvanceAnim(spr, lbl_806DB334);
    }
    obj->Update();
    SpriteHandle_RecomputeCull(fade);
}
