#ifndef GAME_TYPES_SPRITEANIMDATA_H
#define GAME_TYPES_SPRITEANIMDATA_H

typedef struct SpriteAnimData {
    unsigned char pad[0x14];
    float length;
    void *frames;
    short *params;
} SpriteAnimData;

#endif /* GAME_TYPES_SPRITEANIMDATA_H */
