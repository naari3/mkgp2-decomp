#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

short *fn_801A0310(SpriteAnim *s, short key) {
    int i;
    SpriteAnimData *d = s->data;
    if (d == 0) {
        return 0;
    }
    for (i = 0; d->params[i] != -1; i++) {
        if (key == d->params[i]) {
            return &d->params[i];
        }
    }
    return 0;
}
