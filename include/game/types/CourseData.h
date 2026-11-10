#ifndef GAME_TYPES_COURSEDATA_H
#define GAME_TYPES_COURSEDATA_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CourseData CourseData;
struct CourseData {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ void *jointNames[4];
    /* 0x014 */ void *collisionBin[4];
    /* 0x024 */ unsigned char dir[224];
    /* 0x104 */ void *variantTable[4];
    /* 0x114 */ unsigned char pad_114[0x94];
    /* 0x1A8 */ short mapIds[9][2];
    /* 0x1CC */ unsigned char pad_1CC[0x8];
    /* 0x1D4 */ int vtable[5];
};

#endif /* GAME_TYPES_COURSEDATA_H */
