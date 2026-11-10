#ifndef GAME_TYPES_BANANAFIELD_H
#define GAME_TYPES_BANANAFIELD_H

struct Banana;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct BananaField BananaField;
struct BananaField {
    /* 0x000 */ unsigned int active;  /* also: obj */
    /* 0x004 */ struct Banana *items;
    /* 0x008 */ int count;
    /* 0x00C */ unsigned char hit;
    /* 0x00D */ unsigned char pad_00D[0x3];
};

#endif /* GAME_TYPES_BANANAFIELD_H */
