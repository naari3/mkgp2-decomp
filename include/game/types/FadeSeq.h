#ifndef GAME_TYPES_FADESEQ_H
#define GAME_TYPES_FADESEQ_H

#include "game/types/FadeKey.h"
#include "game/types/FadeSeqBase.h"

/* Declare before including (each user already does): Tween */

struct FadeSeq : FadeSeqBase {
    FadeKey *head;
    FadeKey *cur;
    Tween *tween;
    FadeSeq(FadeKey *h, bool l);
    ~FadeSeq();
    void Update();
    bool Done();
    void Load() {
        float t = cur->to;
        tween->Set(cur->from, t, cur->dur);
        cur = cur->next.p;
    }
};

#endif /* GAME_TYPES_FADESEQ_H */
