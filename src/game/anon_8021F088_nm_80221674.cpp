#include "game/anon_8021F088_private.h"


void NextWnd::Update() {
    switch (state) {
    case 0:
        return;
    case 1: {
        int a = (int)(lbl_806DB284 * (timer / lbl_806DB250));
        back.SetColor((unsigned char)a);
        if (timer >= 10) {
            state = 2;
            timer = 0;
            Sprite_SetupAnim(spr[0], 0x12, 1, 0);
            spr[0]->alpha = lbl_806DB194;
        }
        break;
    }
    case 2:
        if (fn_8019FE78(spr[0]) == 0) {
            fn_801A0500(spr[0]);
            state = 3;
            timer = 0;
            Sprite_SetAnimTime(spr[1], lbl_806DB190);
            spr[1]->alpha = lbl_806DB190;
            label.SetColor(0xFFFFFFFF);
        }
        break;
    case 3:
        Count();
        break;
    case 4:
        if (fn_8019FE78(spr[0]) == 0) {
            timer = 0;
            state = 5;
            spr[0]->alpha = lbl_806DB190;
        }
        break;
    case 5: {
        int a = (int)(lbl_806DB284 * (lbl_806DB194 - timer / lbl_806DB250));
        back.SetColor((unsigned char)a);
        if (timer >= 10) {
            state = 0;
            timer = 0;
        }
        break;
    }
    }
    timer++;
    for (int i = 0; i < 2; i++) {
        if (spr[i] != 0) {
            Sprite_AdvanceAnim(spr[i], lbl_806DB280);
        }
    }
}

void NextWnd::Count() {
    bool pressed = GetInput()->held == 1;
    if (timer <= 10) {
        float f = timer / lbl_806DB250;
        spr[1]->alpha = f;
        SetDigitColor(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
    }
    if (timer > 10 && timer < 250 && pressed) {
        timer = 250;
    }
    if (timer >= 250 && timer >= 260) {
        float f = lbl_806DB194 - timer / lbl_806DB250;
        spr[1]->alpha = f;
        SetDigitColor(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
    }
    if (timer >= 260) {
        state = 4;
        timer = 0;
        Sprite_SetupAnim(spr[0], 0x11, 1, 0);
        spr[1]->alpha = lbl_806DB190;
        label.SetColor(0xFFFFFF00);
        SetDigitColor(0xFFFFFF00);
    }
}
