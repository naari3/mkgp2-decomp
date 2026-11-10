#ifndef GAME_TYPES_RIVALAVOIDANCESTATE_H
#define GAME_TYPES_RIVALAVOIDANCESTATE_H

typedef struct RivalAvoidanceState {
    char reserved0[4];
    void *follower;
    char reserved8[8];
    int kartId;
    int pathId;
    char reserved18[0x64];
    float yaw;
    char reserved80[0x1d];
    unsigned char avoiding;
} RivalAvoidanceState;

#endif /* GAME_TYPES_RIVALAVOIDANCESTATE_H */
