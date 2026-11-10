#ifndef GAME_TYPES_FADESEQBASE_H
#define GAME_TYPES_FADESEQBASE_H

struct FadeSeqBase {
    virtual ~FadeSeqBase();
    bool loop;
    FadeSeqBase(bool l) : loop(l) {}
};

#endif /* GAME_TYPES_FADESEQBASE_H */
