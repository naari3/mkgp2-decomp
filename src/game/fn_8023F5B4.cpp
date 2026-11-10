#include "game/SpritePairOwner.h"

#include "game/types/SpriteResourceId.h"

static inline void SetPosition(Sprite *self, float x, float y) {
    self->x = x;
    self->y = y;
}

extern "C" void fn_8023F5B4(Sprite **self, const SpriteResourceId *resource,
                            int enabled, float x, float y) {
    if (!*self) {
        *self = new Sprite(resource->id, 1, 0);
        SetPosition(*self, x, y);
        fn_8019FF6C(*self, enabled);
    }
}
