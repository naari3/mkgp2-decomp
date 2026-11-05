#include "game/HudSprite2454Private.h"
struct HudSpriteOwner2454 {
    virtual void key();
    int layer;
    float x,y,scale;
    VHolder<HudTween> size, rotation;
    VHolder<HudByteTween> color;
    ~HudSpriteOwner2454();
};
HudSpriteOwner2454::~HudSpriteOwner2454() {}
