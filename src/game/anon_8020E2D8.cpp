/*
 * 0x8020E2D8..0x8020E388: FadeLogoScene draw / update / finish.
 */

#include "game/FadeLogo.h"

void FadeLogoScene::Draw() {
    list.p->Draw();
}

void FadeLogoScene::Update() {
    if (list.p->entries.count <= 0) {
        field0C = 1;
    }
    list.p->Update();
}

void FadeLogoScene::Finish() {
    delete this;
}
