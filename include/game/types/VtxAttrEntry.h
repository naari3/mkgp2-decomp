#ifndef GAME_TYPES_VTXATTRENTRY_H
#define GAME_TYPES_VTXATTRENTRY_H

#include "game/types/VtxDesc.h"

typedef struct VtxAttrEntry {
    VtxDesc *desc;
    unsigned int offset;
} VtxAttrEntry;

#endif /* GAME_TYPES_VTXATTRENTRY_H */
