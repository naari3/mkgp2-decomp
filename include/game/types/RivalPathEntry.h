#ifndef GAME_TYPES_RIVALPATHENTRY_H
#define GAME_TYPES_RIVALPATHENTRY_H

typedef struct RivalPathEntry {
    int unknown;
    int valid;
    int reserved8;
    float *x;
    float *y;
    float *z;
} RivalPathEntry;

#endif /* GAME_TYPES_RIVALPATHENTRY_H */
