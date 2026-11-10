#ifndef GAME_TYPES_CARDTASKMANAGER_H
#define GAME_TYPES_CARDTASKMANAGER_H

struct CardTaskEntry;

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CardTaskManager CardTaskManager;
struct CardTaskManager {
    /* 0x000 */ struct CardTaskEntry *entries;
    /* 0x004 */ int count;
    /* 0x008 */ int current;
    /* 0x00C */ int frame;
    /* 0x010 */ int linger;
};

#endif /* GAME_TYPES_CARDTASKMANAGER_H */
