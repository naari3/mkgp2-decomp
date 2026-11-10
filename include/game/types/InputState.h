#ifndef GAME_TYPES_INPUTSTATE_H
#define GAME_TYPES_INPUTSTATE_H

typedef struct InputState {
    char pad00[4];
    unsigned char enabled;
    char pad05[0xF];
    int dir;
    int held;
    int edge;
} InputState;

#endif /* GAME_TYPES_INPUTSTATE_H */
