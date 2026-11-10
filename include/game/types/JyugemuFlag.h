#ifndef GAME_TYPES_JYUGEMUFLAG_H
#define GAME_TYPES_JYUGEMUFLAG_H

/* Merged from 4 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct JyugemuFlag JyugemuFlag;
struct JyugemuFlag {
    /* 0x000 */ void *model;
    /* 0x004 */ unsigned char pad_004[0x4];
    /* 0x008 */ void *kart_driver;  /* also: visible */
};

#endif /* GAME_TYPES_JYUGEMUFLAG_H */
