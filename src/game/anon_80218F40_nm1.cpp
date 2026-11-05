#include "game/anon_80218F40_private.h"

void MinimapHud::Update() {
    int res;
    switch (state) {
    case -1:
        if (g_countdownPhase < 4) {
            state = 0;
            slide.p->Set(lbl_806DAF40, lbl_806DAF44, 7);
        }
        break;
    case 0:
        slideX = slide.p->Value();
        slide.p->Step();
        if (slide.p->Done()) {
            state = 1;
            slideX = lbl_806DAF44;
        }
        break;
    case 1:
        if (g_countdownPhase <= 2) {
            zoom.p->Set(lbl_806DAF48, lbl_806DAF4C, 4);
            state = 2;
        }
        break;
    case 2:
        if (zoom.p->Done() && lbl_806DAF48 == zoom.p->Value()) {
            state = 3;
        }
        break;
    case 3:
        break;
    case 4:
        slideX = slide.p->Value();
        slide.p->Step();
        if (slide.p->Done()) {
            state = 5;
            for (int i = 0; i < 11; i++) {
                SpriteHandle_SetActiveFlag(sprites[i], 0);
                SpriteHandle_RecomputeCull(sprites[i]);
            }
        }
        break;
    case 5:
        fn_80120A08(resId);
        switch (CupIndex()) {
        case 4:
            fn_80120A08(0xC14);
            break;
        case 6:
            fn_80120A08(0xC16);
            break;
        }
        return;
    default:
        return;
    }
    if (delay > 0) {
        delay--;
        if (delay <= 0) {
            delay = 0;
            state = 4;
            slide.p->Set(lbl_806DAF44, lbl_806DAF40, 7);
        }
    }
    if (self != 0) {
        int cup = CupIndex();
        int longRound = g_longRoundFlag;
        if (cup == 4) {
            if (longRound == 1) {
                if (self->team == 0) {
                    variant = 1;
                    resId = 0xC12;
                } else {
                    variant = 2;
                    resId = 0xC14;
                }
            }
        } else if (cup == 6) {
            if (self->team == 0) {
                variant = 0;
                resId = 0xC16;
            } else if (longRound == 0) {
                variant = 1;
                resId = 0xC18;
            } else {
                variant = 2;
                resId = 0xC1A;
            }
        }
    }
    if (path != 0) {
        int cup = CupIndex();
        int longRound = g_longRoundFlag;
        res = resId;
        if (cup == 4) {
            if (longRound == 1) {
                Layout();
            }
        } else if (cup == 6) {
            Layout();
        }
        fn_8011F804(sprites[0], x - slideX, y);
        fn_8011F7AC(sprites[0], scale);
        SpriteLayer_SetResource(sprites[0], res);
        SpriteHandle_SetActiveFlag(sprites[0], 1);
        UpdateMarkers();
    }
    blink.p->Step();
    if (blink.p->Done()) {
        if (blink.p->Value() == 0x7F) {
            blink.p->Set(0x7F, 0xFF, 30);
        } else {
            blink.p->Set(0xFF, 0x7F, 30);
        }
    }
    zoom.p->Step();
    if (zoom.p->Done()) {
        float v = zoom.p->Value();
        if (lbl_806DAF4C == v) {
            zoom.p->Set(lbl_806DAF4C, lbl_806DAF48, 4);
        } else if (lbl_806DAF48 == v) {
            zoom.p->Set(lbl_806DAF48, lbl_806DAF48, 1);
        }
    }
    float z = zoom.p->Value();
    for (int i = 0; i < 3; i++) {
        fn_8011F744(sprites[i], z, z);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    float k = lbl_806DAF50;
    for (int i = 3; i < 11; i++) {
        float s;
        if (others[i - 3] == 1) {
            s = k * zoom.p->Value();
        } else {
            s = zoom.p->Value();
        }
        fn_8011F744(sprites[i], s, s);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}
