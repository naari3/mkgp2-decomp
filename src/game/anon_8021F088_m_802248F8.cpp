#include "game/anon_8021F088_private.h"

void clGetCoinSum::Update() {
        float x = tracks[3].value;
        float y = tracks[4].value;
        if (isJapanese() == 0) {
            r[0].Show(x - lbl_806DB304, y - lbl_806DB308, lbl_806DB194);
        } else {
            fn_801F93EC(&text, x - lbl_806DB30C, y - lbl_806DB308);
        }
        r[1].Show(lbl_806DB310 + x, lbl_806DB314 + y, lbl_806DB194);
        Layout();
        spr.p->SetPos(tracks[3].value, tracks[4].value);
        Sprite_AdvanceAnim(spr.p, lbl_806DB280);
        if (timer < 240) {
            timer++;
        }
    }
