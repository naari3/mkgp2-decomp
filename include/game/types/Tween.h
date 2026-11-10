#ifndef GAME_TYPES_TWEEN_H
#define GAME_TYPES_TWEEN_H

/* Declare before including (each user already does): FlowFader */

struct Tween : FlowFader {
    float from;
    float to;
    float rate;
    Tween(float v) : from(v), to(v), rate(v) {}
    virtual void _key2();
    float Value();
    void Set(float f, float t, short d);
};

#endif /* GAME_TYPES_TWEEN_H */
