#ifndef GAME_TEXTURE_RECT_801F_PRIVATE_H
#define GAME_TEXTURE_RECT_801F_PRIVATE_H
#include "game/DrawQuad801F.h"
typedef float Mtx[3][4];
extern "C" void PSMTXScale(Mtx, float, float, float);
extern "C" void PSMTXTransApply(const Mtx, Mtx, float, float, float);
struct TextureSprite801F {
    DrawDesc801F desc;
    char reserved54[0x10];
    Mtx textureMatrix;
};
struct TextureRect801F { float reserved[2]; float x, y, width, height; };
#endif
