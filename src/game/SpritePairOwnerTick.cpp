#include "game/SpritePairOwner.h"
void SpritePairOwner::Tick() {
    const float upper=lbl_806DB9D8;
    alpha += speed;
    if (alpha > upper) { alpha=upper; speed=lbl_806DB9DC; }
    if (alpha < lbl_806DB9DC) { alpha=lbl_806DB9DC; speed=lbl_806DB9DC; }
    for (int i=0; i<2; ++i) {
        if (sprites[i]) {
            sprites[i]->alpha=alpha;
            Sprite_AdvanceAnim(sprites[i],lbl_806DB9E0);
        }
    }
    for (int i=0; i<2; ++i) {
        if (handles[i] >= 0) {
            SpriteHandle_SetCornerAlpha(handles[i],(int)(lbl_806DB9E4*alpha));
            SpriteHandle_RecomputeCull(handles[i]);
        }
    }
}
void SpritePairOwner::Reset() {
    alpha=lbl_806DB9DC; speed=lbl_806DB9DC;
    Tick();
}
