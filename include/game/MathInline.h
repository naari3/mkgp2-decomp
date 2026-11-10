#ifndef GAME_MATHINLINE_H
#define GAME_MATHINLINE_H

#include "game/types/Vec3f.h"

/* MSL sqrtf: three Newton refinements and a single-precision spill. */
static inline float MathInline_sqrtf(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

#endif
