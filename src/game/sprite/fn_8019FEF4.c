#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

int fn_8019FEF4(SpriteAnim *s) {
    if (s->data == 0) {
        return 0;
    }
    s->time = s->data->length;
    return 1;
}
