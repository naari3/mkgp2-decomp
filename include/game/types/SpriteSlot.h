#ifndef GAME_TYPES_SPRITESLOT_H
#define GAME_TYPES_SPRITESLOT_H

typedef struct SpriteSlot {
    unsigned char pad00[0x4];
    void *object;
} SpriteSlot;

#endif /* GAME_TYPES_SPRITESLOT_H */
