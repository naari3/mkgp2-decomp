#ifndef GAME_DISPLAYCONTEXTFLUSHPRIVATE_H
#define GAME_DISPLAYCONTEXTFLUSHPRIVATE_H

#include <game/DebugTextPrivate.h>

typedef struct DebugVtxDesc {
    int attr, type;
} DebugVtxDesc;

typedef struct DebugVtxFmt {
    int attr, count, type;
    unsigned char frac;
} DebugVtxFmt;

#endif
