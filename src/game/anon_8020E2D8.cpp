/*
 * 0x8020E2D8..0x8020E388: clTimeupDisp draw / update / finish.
 */

#include "game/types/clTimeup.h"
#include "game/FadeLogo.h"

void clTimeupDisp::Draw() {
    list.p->Draw();
}

void clTimeupDisp::Update() {
    if (list.p->entries.count <= 0) {
        field0C = 1;
    }
    list.p->Update();
}

void clTimeupDisp::Finish() {
    delete this;
}
