#ifndef _MSL_SQRT_INLINE_H
#define _MSL_SQRT_INLINE_H

#include <cmath>

/* Inline double sqrt used by this game's MSL math (4 Newton steps on frsqrte). */
extern inline double sqrt(double x) {
    if (x > 0.0) {
        double guess = __frsqrte(x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x == 0) {
        return 0;
    } else if (x) {
        return NAN;
    }
    return HUGE_VALF;
}

#endif
