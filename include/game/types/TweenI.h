#ifndef GAME_TYPES_TWEENI_H
#define GAME_TYPES_TWEENI_H

/* Declare before including (each user already does): FlowFader */

struct TweenI : FlowFader {
    int from;
    int to;
    int rate;
    virtual void _key2();
    int Value();
    void Set(int f, int t, short d);
};

#endif /* GAME_TYPES_TWEENI_H */
