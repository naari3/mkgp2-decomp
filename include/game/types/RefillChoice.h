#ifndef GAME_TYPES_REFILLCHOICE_H
#define GAME_TYPES_REFILLCHOICE_H

struct RefillGroup;
struct TextManager;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct RefillChoice RefillChoice;
struct RefillChoice {
    /* 0x000 */ struct RefillGroup *groups[4];
    /* 0x010 */ struct TextManager *text[4];
    /* 0x020 */ int phase;
    /* 0x024 */ int timer;
    /* 0x028 */ int row;
    /* 0x02C */ int column;
    /* 0x030 */ unsigned char active;
    /* 0x031 */ unsigned char selected;
    /* 0x032 */ unsigned char done;
    /* 0x033 */ unsigned char pad_033[0x1];
    /* 0x034 */ int resource;
    /* 0x038 */ int count;
    /* 0x03C */ int slots[3][2];
};

#endif /* GAME_TYPES_REFILLCHOICE_H */
