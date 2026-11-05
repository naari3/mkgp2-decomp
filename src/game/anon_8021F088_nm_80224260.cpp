#include "game/anon_8021F088_private.h"

void clGetCoinLine::Update() {
        rot += 3.0f;
        if (rot >= 360.0f) {
            rot -= 360.0f;
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
