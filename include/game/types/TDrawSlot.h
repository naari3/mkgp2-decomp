#ifndef GAME_TYPES_TDRAWSLOT_H
#define GAME_TYPES_TDRAWSLOT_H

struct TDrawEntry;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TDrawSlot TDrawSlot;
struct TDrawSlot {
    /* 0x000 */ int owner;  /* also: id */
    /* 0x004 */ int rank;
    /* 0x008 */ float dist;
    /* 0x00C */ int state;  /* also: prio */
    /* 0x010 */ struct TDrawEntry *entry;
};

#endif /* GAME_TYPES_TDRAWSLOT_H */
