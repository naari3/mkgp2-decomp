#ifndef GAME_TYPES_VTXATTRENTRY_H
#define GAME_TYPES_VTXATTRENTRY_H

struct VtxDesc;

/* Merged from 6 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct VtxAttrEntry VtxAttrEntry;
struct VtxAttrEntry {
    /* 0x000 */ struct VtxDesc *desc;
    /* 0x004 */ unsigned int offset;
};

#endif /* GAME_TYPES_VTXATTRENTRY_H */
