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

extern const float lbl_806DA714;

void fn_801F6F7C(ScrollState *s, const Vec2f *base, float speed) {
    float x = base->x;
    float y = base->y;

    s->x = x + lbl_806DA714 * s->velX;
    s->y = y + lbl_806DA714 * s->velY;
    s->speed = speed;
    Wrap(s);
}
