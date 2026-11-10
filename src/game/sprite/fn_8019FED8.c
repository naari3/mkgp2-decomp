#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

extern const float lbl_806D97D8;

float fn_8019FED8(SpriteAnim *s) {
    if (s->data == 0) {
        return lbl_806D97D8;
    }
    return s->time;
}
