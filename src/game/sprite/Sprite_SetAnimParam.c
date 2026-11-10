#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

int Sprite_SetAnimParam(SpriteAnim *s, short key, short val) {
    int i;
    SpriteAnimData *d = s->data;
    if (d == 0) {
        return 0;
    }
    for (i = 0; d->params[i] != -1; i++) {
        if (key == d->params[i]) {
            d->params[i] = val;
            return 1;
        }
    }
    return 0;
}
