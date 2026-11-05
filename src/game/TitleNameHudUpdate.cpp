/*
 * Player title name HUD part: Update, Draw and SetDelay @ 0x802529C8..0x80252D48.
 */

#include "game/TitleNameHud.h"

static inline void UpdateSprites(TitleNameHud *hud) {
    if (hud->title >= 0) {
        float off, x, y, s;
        off = fn_8020A6CC(hud->slide.p);
        y = lbl_806DC140.y;
        x = lbl_806DC140.x - off;
        s = fn_8020A6CC(hud->scale.p);
        fn_8011F744(hud->sprites[0], s, s);
        fn_8011F804(hud->sprites[0], x, y);
        SpriteHandle_SetActiveFlag(hud->sprites[0], 1);
        {
            s *= lbl_806DC148[isJapanese()];
            for (int i = 1; i < hud->count; i++) {
                x = hud->xs[i - 1] - off;
                fn_8011F744(hud->sprites[i], s, s);
                fn_8011F804(hud->sprites[i], x, lbl_806DC140.y);
                SpriteHandle_SetActiveFlag(hud->sprites[i], 1);
            }
        }
    }

}

void TitleNameHud::SetDelay(int n) {
    if (state < 4) {
        delay = n + 1;
    }
}

void TitleNameHud::Draw() {
}

void TitleNameHud::Update() {
    if (title < 0) {
        return;
    }
    switch (state) {
    case -1:
        if (g_countdownPhase <= 3) {
            state = 0;
        }
        return;
    case 0:
        slide.p->Step();
        if (slide.p->Done()) {
            state = 1;
        }
        break;
    case 1:
        if (g_countdownPhase <= 2) {
            fn_8020A734(scale.p, 4, lbl_806DC158, lbl_806DC15C);
            state = 2;
        }
        break;
    case 2:
        if (scale.p->Done()) {
            if (lbl_806DC158 == fn_8020A6CC(scale.p)) {
                state = 3;
            }
        }
        break;
    case 3:
        break;
    case 4:
        slide.p->Step();
        if (slide.p->Done()) {
            state = 5;
            return;
        }
        break;
    case 5:
        return;
    default:
        return;
    }
    if (delay > 0) {
        delay--;
        if (delay <= 0) {
            delay = 0;
            state = 4;
            fn_8020A734(slide.p, 7, lbl_806DC160, lbl_806DC164);
        }
    }
    UpdateSprites(this);
    for (int j = 0; j < count; j++) {
        SpriteHandle_RecomputeCull(sprites[j]);
    }
    scale.p->Step();
    if (scale.p->Done()) {
        float v = fn_8020A6CC(scale.p);
        if (lbl_806DC15C == v) {
            fn_8020A734(scale.p, 4, lbl_806DC15C, lbl_806DC158);
        } else if (lbl_806DC158 == v) {
            fn_8020A734(scale.p, 1, lbl_806DC158, lbl_806DC158);
        }
    }
}
