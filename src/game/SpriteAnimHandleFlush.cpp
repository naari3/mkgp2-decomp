#include "game/SpriteAnimHandle_private.h"
extern "C" void fn_8023F1C8(SpriteAnimHandle *self) {
    if (self->sprite) {
        SpriteAnimHandle *cursor;
        int i;
        for (i = 0, cursor = self; i < 50; ++i, cursor = (SpriteAnimHandle *)((char *)cursor + 2)) {
            if (cursor->keys[0] == -1) break;
            if (cursor->params[0] != cursor->keys[0]) {
                Sprite_SetAnimParam(self->sprite, cursor->params[0], cursor->keys[0]);
                cursor->params[0] = cursor->keys[0];
            }
        }
        fn_801A0500(self->sprite);
    }
}
