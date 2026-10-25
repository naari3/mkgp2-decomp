#ifndef _MUSYX_LIBC_MATH_H
#define _MUSYX_LIBC_MATH_H

// Minimal math.h for MusyX: plain prototypes only. include/libc/math.h defines
// inline sqrtf/sqrt with local statics that would land in every unit's .sdata2.

#ifdef __cplusplus
extern "C" {
#endif

double fabs(double x);
double sin(double x);
double cos(double x);
double sqrt(double x);
double floor(double x);
double fmod(double x, double y);
double pow(double x, double y);

float sqrtf(float x);

extern inline float fmodf(float x, float y) { return (float)fmod(x, y); }
extern inline float floorf(float x) { return (float)floor(x); }
extern inline float powf(float x, float y) { return (float)pow(x, y); }

#ifdef __cplusplus
}
#endif

#endif
