#include "game/SpritePairOwner.h"
void SpritePairOwner::Tick() {
    alpha += speed;
    if (alpha > 1.0f) { alpha=1.0f; speed=0.0f; }
    if (alpha < 0.0f) { alpha=0.0f; speed=0.0f; }
    for (int i=0; i<2; ++i) {
        if (sprites[i]) {
            sprites[i]->alpha=alpha;
            Sprite_AdvanceAnim(sprites[i],0.0165f);
        }
    }
    for (int i=0; i<2; ++i) {
        if (handles[i] >= 0) {
            SpriteHandle_SetCornerAlpha(handles[i],(int)(255.0f*alpha));
            SpriteHandle_RecomputeCull(handles[i]);
        }
    }
}
void SpritePairOwner::Reset() {
    alpha=0.0f; speed=0.0f;
    Tick();
}
