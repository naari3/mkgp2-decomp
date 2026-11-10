#ifndef GAME_TYPES_PATHCURSOR_H
#define GAME_TYPES_PATHCURSOR_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct PathCursor PathCursor;
struct PathCursor {
    /* 0x000 */ void *path;
    /* 0x004 */ int segment;
    /* 0x008 */ int progress;
    /* 0x00C */ void *key;
    /* 0x010 */ unsigned char pad_010[0x4];
    /* 0x014 */ int node;
    /* 0x018 */ unsigned char pad_018[0x80];
};

#endif /* GAME_TYPES_PATHCURSOR_H */
