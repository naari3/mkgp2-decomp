#ifndef GAME_TYPES_SPRITEREF_H
#define GAME_TYPES_SPRITEREF_H

/* Declare before including (each user already does): Sprite */

struct SpriteRef {
    struct Sprite {
        char pad[0x20];
        float t;
    } *spr;
};

#endif /* GAME_TYPES_SPRITEREF_H */
