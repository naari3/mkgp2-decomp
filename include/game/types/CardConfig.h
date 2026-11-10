#ifndef GAME_TYPES_CARDCONFIG_H
#define GAME_TYPES_CARDCONFIG_H

typedef struct CardConfig {
    char pad00[2];
    unsigned char f02;
    char pad03[0xE - 3];
    unsigned char f0E;
    unsigned char f0F;
} CardConfig;

#endif /* GAME_TYPES_CARDCONFIG_H */
