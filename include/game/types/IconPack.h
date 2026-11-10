#ifndef GAME_TYPES_ICONPACK_H
#define GAME_TYPES_ICONPACK_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct IconPack IconPack;
struct IconPack {
    /* 0x000 */ void *handles[4];
    /* 0x010 */ void *vals[4];
    /* 0x020 */ unsigned char pad_020[0x18];
    /* 0x038 */ int mode;
};

#endif /* GAME_TYPES_ICONPACK_H */
