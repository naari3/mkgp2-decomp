#ifndef GAME_TYPES_DISPLAYSTATE_H
#define GAME_TYPES_DISPLAYSTATE_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DisplayState DisplayState;
struct DisplayState {
    /* 0x000 */ unsigned char pad_000[0x20];
    /* 0x020 */ signed char mode;
    /* 0x021 */ signed char bufferIndex;
    /* 0x022 */ unsigned char pad_022[0x2];
    /* 0x024 */ unsigned char flag24;
};

#endif /* GAME_TYPES_DISPLAYSTATE_H */
