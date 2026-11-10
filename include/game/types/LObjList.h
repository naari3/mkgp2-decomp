#ifndef GAME_TYPES_LOBJLIST_H
#define GAME_TYPES_LOBJLIST_H

struct LObjScene;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct LObjList LObjList;
struct LObjList {
    /* 0x000 */ void *archive;
    /* 0x004 */ struct LObjScene *scene;
    /* 0x008 */ void *lights[8];
};

#endif /* GAME_TYPES_LOBJLIST_H */
