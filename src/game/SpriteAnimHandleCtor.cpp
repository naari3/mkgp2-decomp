#define SPRITE_HANDLE_OUTLINE
#include "game/SpriteAnimHandle_private.h"
SpriteAnimHandle::SpriteAnimHandle(int resource) : sprite(0) {
        sprite = new AnimSprite(resource, 1, 0);
        short *src = ((HandleSpriteView *)sprite)->res->params;
        for (int i = 0; i < 50; ++i) {
            keys[i] = src[i];
            params[i] = src[i];
            if (src[i] == -1) break;
        }
    }
