#ifndef SPRITE_COLOR_CONTEXT_PRIVATE_H
#define SPRITE_COLOR_CONTEXT_PRIVATE_H

typedef struct SpriteColorContext {
    float transform[6];
    unsigned char unknown[4];
    float red, green, blue, alpha;
    short redOffset, greenOffset, blueOffset, alphaOffset;
} SpriteColorContext;

#endif
