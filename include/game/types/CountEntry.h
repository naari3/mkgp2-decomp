#ifndef GAME_TYPES_COUNTENTRY_H
#define GAME_TYPES_COUNTENTRY_H

/* Include before this header (each user already does): "game/types/VObjC.h" */

typedef struct CountEntry {
    int count;
    int f4;
    VObjC *obj;
} CountEntry;

#endif /* GAME_TYPES_COUNTENTRY_H */
