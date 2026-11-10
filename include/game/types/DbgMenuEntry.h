#ifndef GAME_TYPES_DBGMENUENTRY_H
#define GAME_TYPES_DBGMENUENTRY_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DbgMenuEntry DbgMenuEntry;
struct DbgMenuEntry {
    /* 0x000 */ void *ctor;
    /* 0x004 */ char *name;
};

#endif /* GAME_TYPES_DBGMENUENTRY_H */
