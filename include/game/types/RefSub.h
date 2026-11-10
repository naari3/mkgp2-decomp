#ifndef GAME_TYPES_REFSUB_H
#define GAME_TYPES_REFSUB_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct RefSub RefSub;
struct RefSub {
    /* 0x000 */ unsigned char on;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ float sx;
    /* 0x008 */ float sy;
    /* 0x00C */ float rot;
    /* 0x010 */ float color[4];
};

#endif /* GAME_TYPES_REFSUB_H */
