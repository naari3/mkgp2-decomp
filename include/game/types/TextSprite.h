#ifndef GAME_TYPES_TEXTSPRITE_H
#define GAME_TYPES_TEXTSPRITE_H

struct TextSprite {
    char pad000[0x8];
    float width;
    char pad00C[0x18 - 0xC];
    int visible;
    char pad01C[0x20 - 0x1C];
    unsigned int color;
    char pad024[0x22C - 0x24];
    float spacing;
    TextSprite();
};

#endif /* GAME_TYPES_TEXTSPRITE_H */
