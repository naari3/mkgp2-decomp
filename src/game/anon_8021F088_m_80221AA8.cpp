#include "game/anon_8021F088_private.h"


void ItemWnd::Update() {
    switch (state) {
    case 0:
        return;
    case 1:
        Open();
        break;
    case 2:
        switch (entry->type) {
        case 1:
            ShowItem();
            break;
        case 0:
            ShowTicket();
            break;
        case 3:
        case 4:
            ShowOther();
            break;
        case 2:
            ShowKart();
            break;
        }
        break;
    case 3:
        switch (sub) {
        case 0:
            sub++;
            timer = 0;
            if (spr[2] != 0) {
                delete spr[2];
                spr[2] = 0;
            }
            break;
        case 1: {
            float f = lbl_806DB194 - timer / lbl_806DB288;
            float a = lbl_806DB284 * (f * f);
            fade.SetColor((unsigned char)(int)a);
            spr[0]->alpha = f;
            float c = lbl_806DB194 - (float)cos(lbl_806DB1D8 * (lbl_806DB28C * f));
            c = c * c;
            spr[0]->sx = c;
            spr[0]->sy = c;
            if (timer >= 20) {
                sub = 0;
                timer = 0;
                state = 0;
            }
            break;
        }
        }
        break;
    }
    timer++;
    for (int i = 0; i < 3; i++) {
        if (spr[i] != 0) {
            Sprite_AdvanceAnim(spr[i], lbl_806DB280);
        }
    }
}
