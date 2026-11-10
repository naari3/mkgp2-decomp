#ifndef GAME_TYPES_TPLPALETTE_H
#define GAME_TYPES_TPLPALETTE_H

struct TPLDescriptor;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TPLPalette TPLPalette;
struct TPLPalette {
    /* 0x000 */ unsigned long version;
    /* 0x004 */ unsigned long count;
    /* 0x008 */ struct TPLDescriptor *descriptors;
};

#endif /* GAME_TYPES_TPLPALETTE_H */
