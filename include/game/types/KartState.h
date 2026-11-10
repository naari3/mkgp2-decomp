#ifndef GAME_TYPES_KARTSTATE_H
#define GAME_TYPES_KARTSTATE_H

typedef struct KartState {
    unsigned char pad00[0x10];
    unsigned long long flags;
} KartState;

#endif /* GAME_TYPES_KARTSTATE_H */
