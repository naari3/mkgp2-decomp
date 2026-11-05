#include "game/SpriteAnimHandle_private.h"
extern "C" void SpriteGroup_CreateOrInit(SpriteAnimHandle **out, int *resource, int mode, float x, float y) {
    if (*out == 0) {
        *out = new SpriteAnimHandle(resource);
        (*out)->sprite->SetPos(x, y);
        fn_8019FF6C((*out)->sprite, mode);
    }
}
