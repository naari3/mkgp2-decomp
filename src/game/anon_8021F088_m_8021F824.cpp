#include "game/anon_8021F088_private.h"

#pragma auto_inline off
void clCSSceneCoinMilage::StateSum() {
    bool pressed = GetInput()->held == 1;
    switch (sub) {
    case 0:
        sum = new clGetCoinSum;
        nodes.push_back((FadeObj *&)sum);
        timer = 0;
        sub++;
        break;
    case 1:
        if (timer >= 120 || pressed == 1) {
            sub++;
            timer = 0;
            wait = 11;
            tick = 0;
        }
        break;
    case 2:
        if (pressed) {
            timer = 0;
            counter = milage;
            sum->Flash();
            sub++;
        } else {
            if (++tick % 50 == 0) {
                if (wait > 4) {
                    wait--;
                }
            }
            if (timer >= wait) {
                timer = 0;
                SoundMgr_Play(0x19);
                if (++counter >= milage) {
                    counter = milage;
                    sum->Flash();
                    sub++;
                }
            }
        }
        break;
    case 3:
        if (sum->done == 1) {
            timer = 0;
            sub = 0;
            wait = 0;
            state = 4;
        }
        break;
    }
    sum->value = counter;
}
#pragma auto_inline reset

clGetCoinSum::clGetCoinSum() : value(0), spr(new Sprite(0x13F, 1, 0)) {
    flash = 0;
    done = 0;
    timer = 0;
    spr.p->layer = 1;
    tracks[4].Set(lbl_806DB1DC, lbl_806DB1DC, lbl_806DB1E0);
    tracks[3].Set(lbl_806DB1E4, lbl_806DB1E8, lbl_806DB1EC);
    r[0].resId = 0x16D6;
    if (isJapanese() == 0) {
        r[1].resId = 0x16D8;
    } else {
        r[1].resId = 0x1924;
        r[1].scaleX = lbl_806DB1F0;
        r[1].scaleY = lbl_806DB1F0;
    }
    TexMgr_SetTexture(&text, lbl_803C6CBC);
    text.visible = 1;
    text.spacing = lbl_806DB1F4;
    fn_801F93D0(&text, lbl_806DB1F0, lbl_806DB1F0);
    glow[0].resId = 0x1ECD;
    glow[1].resId = 0x1ECD;
    glow[2].resId = 0x1ECD;
    glow[3].resId = 0x1ECD;
    glow[4].resId = 0x1ECD;
}

