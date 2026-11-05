#include "game/anon_8021F088_private.h"

void ItemWnd::ShowOther() {
    bool pressed = GetInput()->held == 1;
    switch (sub) {
    case 0: {
        if (spr[1] != 0) {
            delete spr[1];
            spr[1] = 0;
        }
        fn_80121E10(&label);
        const char *name = fn_8013C26C(fn_80216960(entry->id), -1);
        if (entry->type == 3) {
            TexMgr_SetTexture(&texts[0], GetTextureByIdAndLang(0x61, -1), name);
            TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x62, -1));
            label.resId = 0x1ECD;
        } else {
            TexMgr_SetTexture(&texts[0], GetTextureByIdAndLang(0x63, -1), name);
            TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x64, -1));
            label.resId = 0x1D5C;
            if (spr[1] != 0) {
                delete spr[1];
                spr[1] = 0;
            }
            spr[1] = new Sprite(0x21, 1, 0);
            spr[1]->SetPos(lbl_806DB1E8, lbl_806DB290);
            spr[1]->layer = 6;
            spr[1]->alpha = lbl_806DB194;
        }
        if (item != 0) {
            fn_8021A4B8(item, lbl_806DB194, lbl_806DB194, lbl_806DB194, lbl_806DB190);
        }
        fn_801F8E90(&texts[0]);
        fn_801F8E90(&texts[1]);
        label.SetColor(0xFFFFFF00);
        label.Show(lbl_806DB1E8, lbl_806DB290, lbl_806DB194);
        labelLayer = 6;
        sub++;
        timer = 0;
        break;
    }
    case 1: {
        float f = timer / lbl_806DB294;
        spr[2]->alpha = f;
        if (item != 0) {
            fn_8021A430(item, f);
        }
        SetTextAlpha(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
        if (timer >= 15) {
            spr[2]->alpha = lbl_806DB194;
            timer = 0;
            sub++;
            if (item != 0) {
                fn_8021A430(item, lbl_806DB194);
            }
        }
        break;
    }
    case 2: {
        float s = lbl_806DB194;
        float f = timer / lbl_806DB294;
        if (entry->type == 4) {
            s = s - lbl_806DB20C * f;
        }
        if (item != 0) {
            fn_8021A4B8(item, s, s, s, lbl_806DB194);
        }
        label.SetColor(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
        if (timer >= 15) {
            label.SetColor(0xFFFFFFFF);
            timer = 0;
            sub++;
        }
        break;
    }
    case 3:
        if (timer >= 200 || pressed) {
            sub++;
            timer = 0;
        }
        break;
    case 4: {
        float f = lbl_806DB194 - timer / lbl_806DB250;
        spr[2]->alpha = f;
        unsigned int c = PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f));
        label.SetColor(c);
        SetTextAlpha(c);
        if (item != 0) {
            if (entry->type == 4) {
                fn_8021A4B8(item, lbl_806DB204, lbl_806DB204, lbl_806DB204, f);
            } else {
                fn_8021A4B8(item, lbl_806DB194, lbl_806DB194, lbl_806DB194, f);
            }
        }
        if (timer >= 10) {
            state = 3;
            sub = 0;
            label.SetColor(0xFFFFFF00);
            label.resId = 0x1ECD;
            TexMgr_SetTexture(&texts[0], lbl_806DB220);
            TexMgr_SetTexture(&texts[1], lbl_806DB220);
            TexMgr_SetTexture(&texts[2], lbl_806DB220);
            if (spr[1] != 0) {
                delete spr[1];
                spr[1] = 0;
            }
        }
        break;
    }
    }
    if (item != 0) {
        fn_8013DAC8((Model *)item, 5);
    }
}

