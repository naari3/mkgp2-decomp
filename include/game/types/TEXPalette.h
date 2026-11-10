#ifndef GAME_TYPES_TEXPALETTE_H
#define GAME_TYPES_TEXPALETTE_H

struct TEXPaletteEntry;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TEXPalette TEXPalette;
struct TEXPalette {
    /* 0x000 */ void *data;
    /* 0x004 */ unsigned int numDescriptors;
    /* 0x008 */ struct TEXPaletteEntry *entries;
};

#endif /* GAME_TYPES_TEXPALETTE_H */
