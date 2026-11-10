#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

extern int fn_801A13BC(SpriteAnimData *d);

int fn_801A0550(SpriteAnim *s) {
    SpriteAnimData *d = s->data;
    if (d != 0) {
        return 0;
    }
    return fn_801A13BC(d);
}
