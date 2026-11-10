#include "game/types/SpriteAnimData.h"

#include "game/types/SpriteAnim.h"

extern int fn_8019F5BC(SpriteAnim *s, void *frames, int a, int b, int c, int d, void *out, void *arg,
                       float f0, float f1, float f2, float f3, float f4, float f5);

int fn_8019FF8C(SpriteAnim *s, void *out, void *arg) {
    if (s->data == 0) {
        return 0;
    }
    if (arg == 0) {
        return 0;
    }
    return fn_8019F5BC(s, s->data->frames, 0, 0, 0, 0, out, arg, s->c[0], s->c[1], s->c[2], s->c[3], s->c[4], s->c[5]);
}
