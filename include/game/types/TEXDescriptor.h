#ifndef GAME_TYPES_TEXDESCRIPTOR_H
#define GAME_TYPES_TEXDESCRIPTOR_H

struct CLUTHeader;
struct TEXHeader;

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TEXDescriptor TEXDescriptor;
struct TEXDescriptor {
    /* 0x000 */ struct TEXHeader *tex;
    /* 0x004 */ struct CLUTHeader *clut;
};

#endif /* GAME_TYPES_TEXDESCRIPTOR_H */
