#ifndef GAME_TYPES_SUSPPARAM_H
#define GAME_TYPES_SUSPPARAM_H

typedef struct SuspParam {
    float pad0;
    float target;
    float rateUp;
    float rateDown;
    unsigned char pad10[8];
} SuspParam;

#endif /* GAME_TYPES_SUSPPARAM_H */
