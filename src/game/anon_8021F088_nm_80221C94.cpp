#include "game/anon_8021F088_private.h"


void ItemWnd::ShowKart() {
    bool pressed = GetInput()->held == 1;
    switch (sub) {
    case 0:
        fn_80121E10(&label);
        label.resId = 0x1D5D;
        label.SetColor(0xFFFFFF00);
        label.Show(lbl_806DB1E8, lbl_806DB290, lbl_806DB194);
        labelLayer = 5;
        TexMgr_SetTexture(&texts[0], GetTextureByIdAndLang(0x65, -1));
        fn_801F8E90(&texts[0]);
        TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x66, -1));
        fn_801F8E90(&texts[1]);
        sub++;
        timer = 0;
        break;
    case 1: {
        float f = timer / lbl_806DB294;
        spr[2]->alpha = f;
        unsigned int c = PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f));
        label.SetColor(c);
        SetTextAlpha(c);
        if (timer >= 15) {
            label.SetColor(0xFFFFFFFF);
            spr[2]->alpha = lbl_806DB194;
            timer = 0;
            sub++;
        }
        break;
    }
    case 2:
        if (timer >= 200 || pressed) {
            sub++;
            timer = 0;
        }
        break;
    case 3: {
        float f = lbl_806DB194 - timer / lbl_806DB250;
        spr[2]->alpha = f;
        unsigned int c = PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f));
        label.SetColor(c);
        SetTextAlpha(c);
        if (timer >= 10) {
            state = 3;
            sub = 0;
            TexMgr_SetTexture(&texts[0], lbl_806DB220);
            TexMgr_SetTexture(&texts[1], lbl_806DB220);
            fn_80121E10(&label);
            label.resId = 0x1ECD;
            label.SetColor(0xFFFFFF00);
        }
        break;
    }
    }
}
