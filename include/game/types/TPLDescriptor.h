#ifndef GAME_TYPES_TPLDESCRIPTOR_H
#define GAME_TYPES_TPLDESCRIPTOR_H

struct TPLClut;
struct TPLImage;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TPLDescriptor TPLDescriptor;
struct TPLDescriptor {
    /* 0x000 */ struct TPLImage *image;
    /* 0x004 */ struct TPLClut *clut;
};

#endif /* GAME_TYPES_TPLDESCRIPTOR_H */
