#ifndef GAME_TYPES_BUF256_H
#define GAME_TYPES_BUF256_H

/* Merged from 13 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct Buf256 Buf256;
struct Buf256 {
    /* 0x000 */ unsigned short c[0x100];
};

#endif /* GAME_TYPES_BUF256_H */
