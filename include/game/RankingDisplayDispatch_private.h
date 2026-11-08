#ifndef GAME_RANKING_DISPLAY_DISPATCH_PRIVATE_H
#define GAME_RANKING_DISPLAY_DISPATCH_PRIVATE_H
struct RankingBaseRecord {
    const void *type;
    int offset;
    const void *next;
};
struct RankingDispatch {
    const void *type;
    int offset;
    void *(*destroy)(void *, short);
    int (*update)(void *);
    void (*draw)(void *);
};
#endif
