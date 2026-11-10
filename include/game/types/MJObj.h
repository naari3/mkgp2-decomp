#ifndef GAME_TYPES_MJOBJ_H
#define GAME_TYPES_MJOBJ_H

typedef struct MJObj {
    unsigned char pad00[0x88];
    unsigned char rgba[4];
} MJObj;

#endif /* GAME_TYPES_MJOBJ_H */
