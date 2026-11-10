#ifndef GAME_TYPES_JOINTTABLE_H
#define GAME_TYPES_JOINTTABLE_H

#include "game/types/JointEntry.h"

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct JointTable JointTable;
struct JointTable {
    /* 0x000 */ JointEntry e[0x22];
};

#endif /* GAME_TYPES_JOINTTABLE_H */
