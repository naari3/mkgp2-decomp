#ifndef GAME_TYPES_KARTDRIVER_H
#define GAME_TYPES_KARTDRIVER_H

typedef struct KartDriver {
    void *model;
    unsigned char pad004[0x8];
    void *loaded;
    unsigned char pad010[0x2fc];
    void *tireFX;
} KartDriver;

#endif /* GAME_TYPES_KARTDRIVER_H */
