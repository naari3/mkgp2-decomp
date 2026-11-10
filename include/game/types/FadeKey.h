#ifndef GAME_TYPES_FADEKEY_H
#define GAME_TYPES_FADEKEY_H

#include "game/types/FadeKeyBase.h"

/* Declare before including (each user already does): VHolder */

struct FadeKey : FadeKeyBase {
    float from;
    float to;
    VHolder<FadeKey> next;
    FadeKey(int d, float f, float t) : FadeKeyBase(d), from(f), to(t) {}
    ~FadeKey();
    void Append(int dur, float to);
};

#endif /* GAME_TYPES_FADEKEY_H */
