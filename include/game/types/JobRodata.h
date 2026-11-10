#ifndef GAME_TYPES_JOBRODATA_H
#define GAME_TYPES_JOBRODATA_H

#include "game/types/JobEntry.h"

typedef struct JobRodata {
    char pad000[0x4E0];
    JobEntry entries[14];
    char pad550[0x568 - 0x550];
    char selectFmt[0x14];
    char runFmt[0x14];
    char drawFmt[0x14];
} JobRodata;

#endif /* GAME_TYPES_JOBRODATA_H */
