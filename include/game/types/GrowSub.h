#ifndef GAME_TYPES_GROWSUB_H
#define GAME_TYPES_GROWSUB_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct GrowSub GrowSub;
struct GrowSub {
    /* 0x000 */ unsigned char pad_000[0x10];
    /* 0x010 */ unsigned char started;
    /* 0x011 */ unsigned char done;
};

#endif /* GAME_TYPES_GROWSUB_H */
