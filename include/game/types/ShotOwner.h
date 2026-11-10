#ifndef GAME_TYPES_SHOTOWNER_H
#define GAME_TYPES_SHOTOWNER_H

typedef struct ShotOwner {
    char pad0[4];
    void *model;
    void *trailModel;
    int sinIdx;
    int cosIdx;
    char pad14[0x89c - 0x14];
    int trailCount;
} ShotOwner;

#endif /* GAME_TYPES_SHOTOWNER_H */
