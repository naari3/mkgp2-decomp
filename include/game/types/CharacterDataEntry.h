#ifndef GAME_TYPES_CHARACTERDATAENTRY_H
#define GAME_TYPES_CHARACTERDATAENTRY_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CharacterDataEntry CharacterDataEntry;
struct CharacterDataEntry {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ void *body;
    /* 0x008 */ void *hand;
    /* 0x00C */ void *effect;
    /* 0x010 */ unsigned char pad_010[0x8];
    /* 0x018 */ void **parts;
    /* 0x01C */ unsigned char pad_01C[0xC];
    /* 0x028 */ unsigned char pose;
};

#endif /* GAME_TYPES_CHARACTERDATAENTRY_H */
