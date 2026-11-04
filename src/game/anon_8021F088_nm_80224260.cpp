#include "game/anon_8021F088_private.h"

void clGetCoinLine::Update() {
        rot += lbl_806DB2DC;
        if (rot >= lbl_806DB270) {
            rot -= lbl_806DB270;
        }
        Sprite_AdvanceAnim(spr.p, lbl_806DB280);
        if (timer < 80) {
            timer++;
        }
        if (timer == 70) {
            SoundMgr_Play(0x1B);
        }
        if (flash) {
            flashTimer++;
        }
    }
