#ifndef GAME_TYPES_HSDREFOBJ_H
#define GAME_TYPES_HSDREFOBJ_H

struct HsdClass;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct HsdRefObj HsdRefObj;
struct HsdRefObj {
    /* 0x000 */ struct HsdClass *klass;
    /* 0x004 */ unsigned short ref;
    /* 0x006 */ unsigned char pad_006[0x2];
};

#endif /* GAME_TYPES_HSDREFOBJ_H */
