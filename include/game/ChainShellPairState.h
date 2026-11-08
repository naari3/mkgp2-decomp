#ifndef GAME_CHAIN_SHELL_PAIR_STATE_H
#define GAME_CHAIN_SHELL_PAIR_STATE_H

typedef struct ChainShellPairState {
    unsigned char phase;
    unsigned char flags;
    unsigned char reserved02[2];
    unsigned int timers[4];
    float groundY;
    float tetherScale;
    unsigned char reserved1C[0x34 - 0x1C];
    float anchorOffset[3];
    unsigned char reserved40[0x4C - 0x40];
    unsigned char *smoke;
    unsigned char reserved50[0x5C - 0x50];
    unsigned char *children[2];
    unsigned char reserved64[0x98 - 0x64];
    void *owner;
    void *target;
    signed char action;
} ChainShellPairState;

#endif
