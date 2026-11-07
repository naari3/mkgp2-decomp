#ifndef GAME_SPRITE_VOICE_COUNTDOWN_TICK_PRIVATE_H
#define GAME_SPRITE_VOICE_COUNTDOWN_TICK_PRIVATE_H

#include "game/SpriteVoiceCountdownPrivate.h"

/* Item-pointer column of each 0x68-byte race entry. */
typedef struct CountdownRaceItemEntry {
    unsigned char beforeItem[0x40];
    void *item;
    unsigned char afterItem[0x24];
} CountdownRaceItemEntry;

#endif
