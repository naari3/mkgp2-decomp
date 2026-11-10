#ifndef GAME_TYPES_SAVEDGXSTATE_H
#define GAME_TYPES_SAVEDGXSTATE_H

typedef struct SavedGXState {
    int cullMode;
    float proj[7];
    float viewport[6];
    unsigned int scissor[4];
} SavedGXState;

#endif /* GAME_TYPES_SAVEDGXSTATE_H */
