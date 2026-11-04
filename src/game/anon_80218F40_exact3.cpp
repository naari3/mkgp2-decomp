#include "game/anon_80218F40_private.h"

MinimapHud::MinimapHud(int unused, int layer_)
    : state(-1), layer(layer_), variant(0), resId(0), order(0), path(0), self(0), x(lbl_806DAF44),
      y(lbl_806DAF44), scale(lbl_806DAF44), blink(new FlowFaderI), slide(new FlowFaderF(lbl_806DAF44)),
      zoom(new FlowFaderF(lbl_806DAF44)) {
    zoom.p->Set(lbl_806DAF48, lbl_806DAF48, 1);
    order = new int[8];
    resId = 0xC0C;
    int cup = CupIndex();
    int longRound = g_longRoundFlag;
    switch (cup) {
    case 1:
        resId = longRound == 0 ? 0xC0C : 0xC0E;
        break;
    case 2:
        resId = longRound == 0 ? 0xC04 : 0xC06;
        break;
    case 3:
        resId = longRound == 0 ? 0xC00 : 0xC02;
        break;
    case 4:
        resId = longRound == 0 ? 0xC10 : 0xC12;
        if (resId == 0xC12) {
            PreloadResource(0xC14);
        }
        break;
    case 5:
        resId = longRound == 0 ? 0xC08 : 0xC0A;
        break;
    case 6:
        PreloadResource(0xC16);
        resId = longRound == 0 ? 0xC18 : 0xC1A;
        PreloadResource(resId);
        resId = 0xC16;
        break;
    case 7:
        resId = longRound == 0 ? 0xC20 : 0xC22;
        break;
    case 8:
        resId = longRound == 0 ? 0xC1C : 0xC1E;
        break;
    default:
        resId = longRound == 0 ? 0xC0C : 0xC0E;
        break;
    }
    PreloadResource(resId);
    PreloadResource(0xBCC);
    PreloadResource(0xBD2);
    PreloadResource(0xBD1);
    for (int i = 0; i < 4; i++) {
        PreloadResource(i + 0xBCD);
    }
    if (CupIndex() == 6) {
        variant = 0;
    } else {
        variant = g_longRoundFlag;
    }
    Layout();
    slideX = lbl_806DAF40;
    order[0] = -1;
    order[1] = -1;
    order[2] = -1;
    order[3] = -1;
    order[4] = -1;
    order[5] = -1;
    order[6] = -1;
    order[7] = -1;
    blink.p->Set(0x7F, 0xFF, 30);
    {
    ResCtrl a;
    a.resId = resId;
    sprites[0] = SpriteHandle_CreateDefault(&a, layer);
    }
    {
    ResCtrl b;
    b.resId = 0xBD1;
    for (int i = 3; i < 11; i++) {
        sprites[i] = SpriteHandle_CreateDefault(&b, layer);
    }
    }
    {
    ResCtrl c;
    c.resId = 0xBD2;
    sprites[1] = SpriteHandle_CreateDefault(&c, layer);
    }
    {
    ResCtrl d;
    d.resId = 0xBCC;
    sprites[2] = SpriteHandle_CreateDefault(&d, layer);
    }
    for (int i = 0; i < 11; i++) {
        SpriteHandle_SetActiveFlag(sprites[i], 0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    others[0] = 0;
    others[1] = 0;
    others[2] = 0;
    others[3] = 0;
    others[4] = 0;
    others[5] = 0;
    others[6] = 0;
    others[7] = 0;
}
