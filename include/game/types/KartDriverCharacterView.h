#ifndef GAME_TYPES_KARTDRIVERCHARACTERVIEW_H
#define GAME_TYPES_KARTDRIVERCHARACTERVIEW_H

typedef struct KartDriverCharacterView {
    char pad0[0x1F8];
    unsigned int characterId;
} KartDriverCharacterView;

#endif /* GAME_TYPES_KARTDRIVERCHARACTERVIEW_H */
