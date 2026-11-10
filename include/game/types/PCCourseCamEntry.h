#ifndef GAME_TYPES_PCCOURSECAMENTRY_H
#define GAME_TYPES_PCCOURSECAMENTRY_H

#include "game/types/PCPathSeg.h"

typedef struct PCCourseCamEntry {
    int gameMode;
    int cupId;
    int ccClass;
    int roundType;
    PCPathSeg seg[3]; /* 0x10 */
} PCCourseCamEntry;

#endif /* GAME_TYPES_PCCOURSECAMENTRY_H */
