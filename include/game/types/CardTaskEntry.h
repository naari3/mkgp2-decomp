#ifndef GAME_TYPES_CARDTASKENTRY_H
#define GAME_TYPES_CARDTASKENTRY_H

struct CardTask;

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CardTaskEntry CardTaskEntry;
struct CardTaskEntry {
    /* 0x000 */ struct CardTask *task;
    /* 0x004 */ int desc;  /* also: kind */
};

#endif /* GAME_TYPES_CARDTASKENTRY_H */
