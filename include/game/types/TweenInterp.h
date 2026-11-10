#ifndef GAME_TYPES_TWEENINTERP_H
#define GAME_TYPES_TWEENINTERP_H

typedef struct TweenInterp {
    void *vtable;
    short from;
    short to;
    float t;
    float value;
    float speed;
} TweenInterp;

#endif /* GAME_TYPES_TWEENINTERP_H */
