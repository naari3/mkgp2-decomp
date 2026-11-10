#ifndef GAME_TYPES_TEXDESCRIPTOR_H
#define GAME_TYPES_TEXDESCRIPTOR_H

#include "game/types/TEXHeader.h"

typedef struct TEXDescriptor {
    TEXHeader *tex;
    void *clut;
} TEXDescriptor;

#endif /* GAME_TYPES_TEXDESCRIPTOR_H */
