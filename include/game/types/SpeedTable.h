#ifndef GAME_TYPES_SPEEDTABLE_H
#define GAME_TYPES_SPEEDTABLE_H

struct SpeedPt;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SpeedTable SpeedTable;
struct SpeedTable {
    /* 0x000 */ struct SpeedPt *pts;
    /* 0x004 */ int count;
    /* 0x008 */ float maxProgress;  /* also: ref */
    /* 0x00C */ unsigned char pad_00C[0xC];
};

#endif /* GAME_TYPES_SPEEDTABLE_H */
