#ifndef GAME_TYPES_SEQMENUSCENE_H
#define GAME_TYPES_SEQMENUSCENE_H

struct MenuEntry;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SeqMenuScene SeqMenuScene;
struct SeqMenuScene {
    /* 0x000 */ char *vtable;
    /* 0x004 */ struct MenuEntry *entries;
    /* 0x008 */ int count;
    /* 0x00C */ int cursor;
    /* 0x010 */ int blink;
};

#endif /* GAME_TYPES_SEQMENUSCENE_H */
