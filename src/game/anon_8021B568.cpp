#include "game/anon_8021B568_private.h"

int TeamIconRow::CountFlagged() {
    int n = 0;
    for (int i = 0; i < 4; i++) {
        if (team[i] == 1 || team[i] == 3) {
            n++;
        }
    }
    return n;
}

void TeamIconRow::Close() {
    if (closing != 1) {
        closing = 1;
        state = 2;
    }
}

void TeamIconRow::SetLayer(int layer) {
    icons[0]->anim->obj->layer = layer;
    icons[1]->anim->obj->layer = layer;
    icons[2]->anim->obj->layer = layer;
    icons[3]->anim->obj->layer = layer;
}

void TeamIconRow::Draw() {
    for (int i = 0; i < 4; i++) {
        fn_801A0004(icons[i]->anim->obj);
    }
}
