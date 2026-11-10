#ifndef GAME_TYPES_BITPACK_H
#define GAME_TYPES_BITPACK_H

struct BitpackEntry;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct Bitpack Bitpack;
struct Bitpack {
    /* 0x000 */ struct BitpackEntry *schema;
    /* 0x004 */ int count;
    /* 0x008 */ unsigned char *dest;
    /* 0x00C */ unsigned char options;
    /* 0x00D */ unsigned char pad_00D[0x3];
    /* 0x010 */ int total_bits;
    /* 0x014 */ int total_bytes;
};

#endif /* GAME_TYPES_BITPACK_H */
