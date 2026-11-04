#include "game/anon_8021B568_private.h"

void TeamIconRow::Update() {
    switch (state) {
    case 0:
        state = 1;
        break;
    case 1:
        for (int i = 0; i < 4; i++) {
            team[i] = SlotTeam(i);
            TeamIcon *ic = icons[i];
            int t = team[i];
            if (ic->state == t) {
                continue;
            }
            if (t == 0) {
                ic->locked = 0;
            }
            if (ic->locked == 1) {
                continue;
            }
            if (ic->state == 3 && t == 1) {
                ic->state = 2;
                ic->locked = 1;
            } else {
                ic->state = t;
            }
            if (ic->state == 0) {
                SpriteAnimParamBlock_SetKey(ic->anim, 0x1567, 0x156B);
                if (ic->isMe == 0) {
                    SpriteAnimParamBlock_SetKey(ic->anim, 0x156D, ic->slot + 0x1575);
                }
            } else {
                SpriteAnimParamBlock_SetKey(ic->anim, 0x1567, ic->slot + 0x1567);
                if (ic->isMe == 0) {
                    SpriteAnimParamBlock_SetKey(ic->anim, 0x156D, ic->slot + 0x156D);
                } else {
                    SpriteAnimParamBlock_SetKey(ic->anim, 0x156D, ic->slot + 0x1571);
                }
            }
            if (ic->state == 1 || ic->state == 3) {
                SpriteAnimParamBlock_SetKey(ic->anim, 0x156C, 0x156C);
            } else {
                SpriteAnimParamBlock_SetKey(ic->anim, 0x156C, 0x1ECD);
            }
            SpriteAnimParamBlock_SetKey(ic->anim, 0x157A, lbl_803C53C0[ic->state]);
        }
        break;
    case 2:
        timer++;
        if (timer >= 15) {
            state = 3;
        }
        break;
    }
    frame++;
    for (int i = 0; i < 4; i++) {
        Sprite_AdvanceAnim(icons[i]->anim->obj, 0.0165f);
    }
}
