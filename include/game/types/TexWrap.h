#ifndef GAME_TYPES_TEXWRAP_H
#define GAME_TYPES_TEXWRAP_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TexWrap TexWrap;
struct TexWrap {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ unsigned char s;
    /* 0x005 */ unsigned char t;
    /* 0x006 */ unsigned char pad_006[0xA];
};

#endif /* GAME_TYPES_TEXWRAP_H */
