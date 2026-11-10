#ifndef GAME_TYPES_PATHSLOT_H
#define GAME_TYPES_PATHSLOT_H

typedef struct PathSlot {
    float v[3];
    float speed;
    float accel;
    int ids[3];
} PathSlot;

#endif /* GAME_TYPES_PATHSLOT_H */
