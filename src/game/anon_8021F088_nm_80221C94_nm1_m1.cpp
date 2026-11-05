#include "game/anon_8021F088_private.h"

static inline void SetTicketText(ItemWnd *w, const char *name) {
    TexMgr_SetTexture(&w->texts[0], GetTextureByIdAndLang(0x5F, -1), name);
}

void ItemWnd::ShowTicket() {
    bool pressed = GetInput()->held == 1;
    switch (sub) {
    case 0: {
        if (spr[1] != 0) {
            delete spr[1];
            spr[1] = 0;
        }
        spr[1] = new Sprite(0x1B3, 1, 0);
        spr[1]->SetPos(lbl_806DB1E8, lbl_806DB1A4);
        spr[1]->SetAnimParam(0xC3F, (short)fn_80216908(fn_80216974(entry->id)));
        spr[1]->layer = 5;
        spr[1]->alpha = lbl_806DB190;
        SetTicketText(this, fn_8021691C(entry->id));
        fn_801F8E90(&texts[0]);
        TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x60, -1));
        fn_801F8E90(&texts[1]);
        sub++;
        timer = 0;
        break;
    }
    case 1: {
        float f = timer / lbl_806DB294;
        spr[1]->alpha = f;
        spr[2]->alpha = f;
        SetTextAlpha(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
        if (timer >= 15) {
            spr[2]->alpha = lbl_806DB194;
            spr[1]->alpha = lbl_806DB194;
            SetTextAlpha(0xFFFFFFFF);
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
        spr[1]->alpha = f;
        spr[2]->alpha = f;
        SetTextAlpha(PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806DB24C * f)));
        if (timer >= 10) {
            state = 3;
            sub = 0;
            timer = 0;
            if (spr[1] != 0) {
                delete spr[1];
                spr[1] = 0;
            }
            SetTextAlpha(0xFFFFFF00);
            TexMgr_SetTexture(&texts[0], lbl_806DB220);
            TexMgr_SetTexture(&texts[1], lbl_806DB220);
            TexMgr_SetTexture(&texts[2], lbl_806DB220);
        }
        break;
    }
    }
}

