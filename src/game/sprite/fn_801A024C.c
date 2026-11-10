#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

int fn_801A024C(SpriteAnim *s) {
    if (s->data == 0) {
        return 0;
    }
    if (s->flag == 0 && s->time >= s->data->length) {
        return 0;
    }
    return 1;
}
