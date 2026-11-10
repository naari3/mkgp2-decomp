#ifndef GAME_TYPES_ITEMDATA_H
#define GAME_TYPES_ITEMDATA_H

typedef struct ItemData {
    unsigned char pad0[5];
    unsigned char kind;
    signed char throwable;
    signed char throwType;
    unsigned char effect;
} ItemData;

#endif /* GAME_TYPES_ITEMDATA_H */
