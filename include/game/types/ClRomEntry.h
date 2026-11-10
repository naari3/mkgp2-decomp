#ifndef GAME_TYPES_CLROMENTRY_H
#define GAME_TYPES_CLROMENTRY_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ClRomEntry ClRomEntry;
struct ClRomEntry {
    /* 0x000 */ void *rom;
    /* 0x004 */ const char *path;
};

#endif /* GAME_TYPES_CLROMENTRY_H */
