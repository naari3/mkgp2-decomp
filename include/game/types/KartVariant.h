#ifndef GAME_TYPES_KARTVARIANT_H
#define GAME_TYPES_KARTVARIANT_H

typedef struct KartVariant {
    char pad0[0x1F4];
    int kind;
    int sub;
} KartVariant;

#endif /* GAME_TYPES_KARTVARIANT_H */
