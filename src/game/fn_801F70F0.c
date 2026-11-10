/* Sets a scroll offset and wraps it into the texture extent. */
#include "game/types/ScrollState.h"

#include "game/types/Vec2f.h"

void fn_801F6574(float *w, float *h);

static inline void Wrap(ScrollState *s) {
    float w;
    float h;

    fn_801F6574(&w, &h);
    if (s->x >= w) {
        s->x -= w;
    } else if (s->x < -w) {
        s->x += w;
    }
    if (s->y >= h) {
        s->y -= h;
    } else if (s->y < -h) {
        s->y += h;
    }
}

void fn_801F70F0(ScrollState *s, float x, float y, float speed) {
    s->x = x;
    s->y = y;
    s->speed = speed;
    Wrap(s);
}
