#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

int Sprite_SetAnimTime(SpriteAnim *s, float t) {
    if (s->data == 0) {
        return 0;
    }
    if (t >= s->data->length) {
        return 0;
    }
    s->time = t;
    return 1;
}
