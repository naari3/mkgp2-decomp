#ifndef GAME_TYPES_SPRITE_H
#define GAME_TYPES_SPRITE_H

struct Sprite {
    int field00;
    int style;
    int field08;
    float x;
    float y;
    char pad14[0x30 - 0x14];
    Sprite(int anim, int loop, int arg);
};

#endif /* GAME_TYPES_SPRITE_H */
