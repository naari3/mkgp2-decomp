#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

int Sprite_AdvanceAnim(SpriteAnim *s, float dt) {
    if (s->data == 0) {
        return 0;
    }
    if (s->flag == 0) {
        if (s->time >= s->data->length) {
            s->time = s->data->length;
            return 0;
        }
        s->time += dt;
    } else {
        s->time += dt;
        if (s->time >= s->data->length) {
            s->time -= s->data->length;
        }
    }
    return 1;
}
