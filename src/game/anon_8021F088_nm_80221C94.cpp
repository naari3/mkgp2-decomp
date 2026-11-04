#include "game/anon_8021F088_private.h"


void ItemWnd::ShowKart() {
    InputState *in = GetInput();
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
        if (timer >= 200 || in->held == 1) {
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

void ItemWnd::ShowOther() {
    InputState *in = GetInput();
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
        if (timer >= 200 || in->held == 1) {
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

void ItemWnd::ShowTicket() {
    InputState *in = GetInput();
    switch (sub) {
    case 0: {
        if (spr[1] != 0) {
            delete spr[1];
            spr[1] = 0;
        }
        spr[1] = new Sprite(0x1B3, 1, 0);
        spr[1]->SetPos(lbl_806DB1E8, lbl_806DB1A4);
        spr[1]->SetAnimParam(0xC3F, fn_80216908(fn_80216974(entry->id)));
        spr[1]->layer = 5;
        spr[1]->alpha = lbl_806DB190;
        const char *name = fn_8021691C(entry->id);
        TexMgr_SetTexture(&texts[0], GetTextureByIdAndLang(0x5F, -1), name);
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
        if (timer >= 200 || in->held == 1) {
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

void ItemWnd::ShowItem() {
    InputState *in = GetInput();
    float f = lbl_806DB190;
    switch (sub) {
    case 0: {
        int a = Item_GetDescriptorField8(itemId);
        int b = Item_GetDescriptorFieldC(itemId);
        short ra = -1;
        if (a >= 0) {
            ra = a + 0x17A3;
        }
        short rb = -1;
        if (b >= 0) {
            rb = b + 0x1E1D;
        }
        fn_8013BEC8(a);
        if (spr[1] != 0) {
            delete spr[1];
            spr[1] = 0;
        }
        spr[1] = new Sprite(0x19F, 1, 0);
        spr[1]->SetPos(lbl_806DB298, lbl_806DB29C);
        spr[1]->SetAnimParam(0x1E1D, rb);
        spr[1]->SetAnimParam(0x17A4, ra);
        spr[1]->SetAnimParam(0x13B9, Item_GetDescriptorField0(itemId, 0));
        spr[1]->layer = 5;
        spr[1]->alpha = lbl_806DB190;
        float pos[2];
        fn_8019FF8C(spr[1], 0x1ECD, pos);
        fn_801F93EC(&texts[3], pos[0], pos[1]);
        fn_8019FF8C(spr[1], 0x1ECF, pos);
        fn_801F93EC(&texts[4], pos[0], pos[1]);
        fn_8019FF8C(spr[1], 0x1ED1, pos);
        fn_801F93EC(&texts[5], pos[0], pos[1]);
        fn_8019FF8C(spr[1], 0x1ED3, pos);
        fn_801F93EC(&texts[6], pos[0], pos[1]);
        TexMgr_SetTexture(&texts[3], fn_8023DAA8(itemId));
        TexMgr_SetTexture(&texts[4], fn_8023D938(itemId, 0));
        TexMgr_SetTexture(&texts[5], fn_8023D938(itemId, 1));
        TexMgr_SetTexture(&texts[6], fn_8023D938(itemId, 2));
        char buf[0x40];
        *(struct Buf40 { char c[0x40]; } *)buf = *(const struct Buf40 *)lbl_803C6B84;
        int kind = fn_8023D710(itemId);
        switch (kind) {
        case -1:
            break;
        case 0:
        case 1: {
            const char *b2 = fn_8013C26C(1, -1);
            sprintf(buf, lbl_806DB2A0, fn_8013C26C(0, -1), b2);
            break;
        }
        case 8:
        case 9: {
            const char *b2 = fn_8013C26C(9, -1);
            sprintf(buf, lbl_806DB2A0, fn_8013C26C(8, -1), b2);
            texts[1].spacing = lbl_806DB1F4;
            break;
        }
        default:
            strcpy(buf, fn_8013C26C(kind, -1));
            break;
        }
        if (kind == -1) {
            TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x5E, -1));
        } else {
            TexMgr_SetTexture(&texts[1], GetTextureByIdAndLang(0x5D, -1), buf);
        }
        fn_801F8E90(&texts[1]);
        spr[1]->SetAnimParam(0x1ECF, 0x1ECD);
        spr[1]->SetAnimParam(0x1ED1, 0x1ECD);
        spr[1]->SetAnimParam(0x1ED3, 0x1ECD);
        *(unsigned int *)((char *)&texts[3] + 0x20) = 0xE0202000;
        *(unsigned int *)((char *)&texts[4] + 0x20) = 0xFFFFFF00;
        *(unsigned int *)((char *)&texts[5] + 0x20) = 0xFFFFFF00;
        *(unsigned int *)((char *)&texts[6] + 0x20) = 0xFFFFFF00;
        fn_80121E10(&label);
        label.resId = 0x1D5E;
        label.Show(lbl_806DB1CC, lbl_806DB290, lbl_806DB194);
        label.SetColor(0xFFFFFF00);
        labelLayer = 5;
        sub++;
        timer = 0;
        break;
    }
    case 1: {
        f = timer / lbl_806DB294;
        spr[1]->alpha = f;
        spr[2]->alpha = f;
        int a = (int)(lbl_806DB24C * f);
        *(unsigned int *)((char *)&texts[3] + 0x20) = PackColor(0xE0, 0x20, 0x20, a);
        unsigned int c = PackColor(0xFF, 0xFF, 0xFF, a);
        *(unsigned int *)((char *)&texts[4] + 0x20) = c;
        *(unsigned int *)((char *)&texts[5] + 0x20) = c;
        *(unsigned int *)((char *)&texts[6] + 0x20) = c;
        label.SetColor(c);
        SetTextAlpha(c);
        if (timer >= 15) {
            spr[2]->alpha = lbl_806DB194;
            spr[1]->alpha = lbl_806DB194;
            timer = 0;
            sub++;
        }
        break;
    }
    case 2:
        f = lbl_806DB194;
        if (timer >= 200 || in->held == 1) {
            sub++;
            timer = 0;
        }
        break;
    case 3: {
        f = lbl_806DB194 - timer / lbl_806DB250;
        spr[1]->alpha = f;
        spr[2]->alpha = f;
        int a = (int)(lbl_806DB24C * f);
        *(unsigned int *)((char *)&texts[3] + 0x20) = PackColor(0xE0, 0x20, 0x20, a);
        unsigned int c = PackColor(0xFF, 0xFF, 0xFF, a);
        *(unsigned int *)((char *)&texts[4] + 0x20) = c;
        *(unsigned int *)((char *)&texts[5] + 0x20) = c;
        *(unsigned int *)((char *)&texts[6] + 0x20) = c;
        label.SetColor(c);
        SetTextAlpha(c);
        if (timer >= 10) {
            label.resId = -1;
            sub = 0;
            timer = 0;
            state = 3;
            if (spr[1] != 0) {
                delete spr[1];
                spr[1] = 0;
            }
            TexMgr_SetTexture(&texts[0], lbl_806DB220);
            TexMgr_SetTexture(&texts[1], lbl_806DB220);
            TexMgr_SetTexture(&texts[2], lbl_806DB220);
            texts[1].spacing = lbl_806DB2A8;
        }
        break;
    }
    }
    if (kart != 0) {
        fn_8013D4B0(kart, f);
        fn_8013DAC8(kart, 5);
    }
}

void ItemWnd::Open() {
    switch (sub) {
    case 0: {
        int a = (int)(lbl_806DB284 * (timer / lbl_806DB250));
        fade.SetColor((unsigned char)a);
        if (timer >= 10) {
            sub++;
            timer = 0;
            spr[0]->alpha = lbl_806DB194;
            spr[0]->sx = lbl_806DB190;
            spr[0]->sy = lbl_806DB190;
        }
        return;
    }
    case 1: {
        float f = timer / lbl_806DB294;
        float c = lbl_806DB194 - (float)cos(lbl_806DB1D8 * (lbl_806DB28C * f));
        c = c * c;
        spr[0]->sx = c;
        spr[0]->sy = c;
        spr[0]->alpha = f * f;
        if (timer >= 15) {
            sub = 0;
            timer = 0;
            state = 2;
            if (spr[2] != 0) {
                delete spr[2];
                spr[2] = 0;
            }
            spr[2] = new Sprite(0x14A, 1, 0);
            spr[2]->SetPos(lbl_806DB1E8, lbl_806DB2AC);
            spr[2]->layer = 5;
            spr[2]->alpha = lbl_806DB190;
            spr[2]->SetAnimParam(0x1931, 0x1ECD);
            spr[2]->SetAnimParam(0x1932, 0x1ECD);
            spr[2]->SetAnimParam(0x1933, 0x1ECD);
            spr[2]->SetAnimParam(0x1934, 0x1ECD);
            int d[4] = {0, 0, 0, 0};
            d[3] = coins / 1000 % 10;
            d[0] = coins % 10;
            d[1] = coins / 10 % 10;
            d[2] = coins / 100 % 10;
            if (d[3] == 0) {
                d[3] = -1;
            }
            if (d[2] == 0 && d[3] < 0) {
                d[2] = -1;
            }
            int row = 0;
            if (isJapanese() == 1) {
                if (d[3] < 0) {
                    row = 1;
                } else {
                    row = 2;
                }
            }
            const float *xs = lbl_803C6BD4[row];
            for (int i = 0; i < 4; i++) {
                fn_80121E10(&digits[i]);
                if (d[i] < 0) {
                    digits[i].resId = 0x1ECD;
                } else {
                    digits[i].resId = (short)(d[i] + 0x1931);
                }
                digits[i].Show(xs[i], lbl_806DB2B0, lbl_806DB194);
                digits[i].SetColor(0xFFFFFF00);
            }
        }
        break;
    }
    }
}
