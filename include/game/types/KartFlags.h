#ifndef GAME_TYPES_KARTFLAGS_H
#define GAME_TYPES_KARTFLAGS_H

typedef struct KartFlags {
    char pad[0x10];
    unsigned long long bits;
} KartFlags;

#endif /* GAME_TYPES_KARTFLAGS_H */
