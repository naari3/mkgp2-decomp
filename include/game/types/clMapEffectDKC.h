#ifndef GAME_TYPES_CLMAPEFFECTDKC_H
#define GAME_TYPES_CLMAPEFFECTDKC_H

#include "game/types/clMapEffect.h"

struct clMapEffectDKC : clMapEffect {
    int wait;
    int volIdx;
    int panIdx;
    unsigned char done;

    virtual ~clMapEffectDKC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectDKC() {
        wait = 0;
        volIdx = 0;
        panIdx = 0;
        done = 0;
        fn_8016B248(0);
        fn_8016B178(2);
        fn_8016B160(0.0f);
        fn_8016B148(10000.0f);
        fn_8016B0F0(0xC0, 0xC0, 0xC0);
    }
};

#endif /* GAME_TYPES_CLMAPEFFECTDKC_H */
