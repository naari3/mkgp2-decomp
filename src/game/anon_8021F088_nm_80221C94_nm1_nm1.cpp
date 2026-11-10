#include "game/anon_8021F088_private.h"
#include "game/singleton.h"

static inline void FormatItemNames(char *buf, int first, int second) {
    sprintf(buf, lbl_806DB2A0, fn_8013C26C(first, -1), fn_8013C26C(second, -1));
}

static inline void SetItemLabels(ItemWnd *w, unsigned int color) {
    w->label.SetColor(color);
    w->SetTextAlpha(color);
}

static inline void SetItemSprites(ItemWnd *w, float alpha) {
    w->spr[1]->alpha = alpha;
    w->spr[2]->alpha = alpha;
}

void ItemWnd::ShowItem() {
    float f = lbl_806DB190;
    bool pressed = SINGLETON_INSTANCE(g_pInputState)->held == 1;
    switch (sub) {
    case 0: {
        int a = Item_GetDescriptorField8(itemId);
        int b = Item_GetDescriptorFieldC(itemId);
        short ra = a >= 0 ? a + 0x17A3 : -1;
        short rb = b >= 0 ? b + 0x1E1D : -1;
        fn_8013BEC8(a);
        if (spr[1] != 0) {
            delete spr[1];
            spr[1] = 0;
        }
        spr[1] = new Sprite(0x19F, 1, 0);
        spr[1]->SetPos(lbl_806DB298, lbl_806DB29C);
        spr[1]->SetAnimParam(0x1E1D, rb);
        spr[1]->SetAnimParam(0x17A4, ra);
        spr[1]->SetAnimParam(0x13B9, (short)Item_GetDescriptorField0(itemId, 0));
        spr[1]->layer = 5;
        spr[1]->alpha = lbl_806DB190;
        float pos[12];
        char buf[0x40]; // fn_8019FF8C writes a 0x30-byte sprite node record.
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
        struct Buf40 { char c[0x40]; };
        *(struct Buf40 *)buf = *(const struct Buf40 *)lbl_803C6B84;
        int kind = fn_8023D710(itemId);
        switch (kind) {
        case -1:
            break;
        case 0:
        case 1: {
            FormatItemNames(buf, 0, 1);
            break;
        }
        case 8:
        case 9: {
            FormatItemNames(buf, 8, 9);
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
        unsigned int c, d;
        d = c = 0xFFFFFF00;
        float alpha = timer / lbl_806DB294;
        SetItemSprites(this, alpha);
        f = alpha;
        int a = (int)(lbl_806DB24C * f);
        *(unsigned int *)((char *)&texts[3] + 0x20) = PackColor(0xE0, 0x20, 0x20, a);
        d |= a & 0xFF;
        c |= a & 0xFF;
        *(unsigned int *)((char *)&texts[4] + 0x20) = c;
        *(unsigned int *)((char *)&texts[5] + 0x20) = c;
        *(unsigned int *)((char *)&texts[6] + 0x20) = c;
        SetItemLabels(this, d);
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
        if (timer >= 200 || pressed) {
            sub++;
            timer = 0;
        }
        break;
    case 3: {
        unsigned int c, d;
        d = c = 0xFFFFFF00;
        float alpha = lbl_806DB194 - timer / lbl_806DB250;
        SetItemSprites(this, alpha);
        f = alpha;
        int a = (int)(lbl_806DB24C * f);
        *(unsigned int *)((char *)&texts[3] + 0x20) = PackColor(0xE0, 0x20, 0x20, a);
        d |= a & 0xFF;
        c |= a & 0xFF;
        *(unsigned int *)((char *)&texts[4] + 0x20) = c;
        *(unsigned int *)((char *)&texts[5] + 0x20) = c;
        *(unsigned int *)((char *)&texts[6] + 0x20) = c;
        SetItemLabels(this, d);
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

