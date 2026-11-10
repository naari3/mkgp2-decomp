#ifndef GAME_TYPES_GRIDINITSTATE_H
#define GAME_TYPES_GRIDINITSTATE_H

struct TextManager;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct GridInitState GridInitState;
struct GridInitState {
    /* 0x000 */ void *groups[7];
    /* 0x01C */ int handle;
    /* 0x020 */ struct TextManager *texts[3][4];
    /* 0x050 */ int selected;
    /* 0x054 */ int timer;
    /* 0x058 */ int phase;
    /* 0x05C */ unsigned char done;
    /* 0x05D */ unsigned char automatic;
    /* 0x05E */ unsigned char pad_05E[0x2];
    /* 0x060 */ int itemIndices[3];
    /* 0x06C */ int resources[3];
};

#endif /* GAME_TYPES_GRIDINITSTATE_H */
