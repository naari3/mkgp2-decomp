#ifndef GAME_TYPES_VIEWERENTRY_H
#define GAME_TYPES_VIEWERENTRY_H

#include "game/types/ShowXform.h"

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ViewerEntry ViewerEntry;
struct ViewerEntry {
    /* 0x000 */ const char *file;
    /* 0x004 */ ShowXform xf;
};

#endif /* GAME_TYPES_VIEWERENTRY_H */
