#ifndef GAME_TYPES_POBJVIEW_H
#define GAME_TYPES_POBJVIEW_H

#include "game/types/VtxDesc.h"

typedef struct PObjView {
    unsigned char pad[0x8];
    VtxDesc *verts;
    unsigned char pad2[0x2];
    unsigned short n_display;
    unsigned char *display;
} PObjView;

#endif /* GAME_TYPES_POBJVIEW_H */
