#ifndef GAME_TYPES_RACESLOT_H
#define GAME_TYPES_RACESLOT_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct RaceSlot RaceSlot;
struct RaceSlot {
    /* 0x000 */ int type;
    /* 0x004 */ int selection;
    /* 0x008 */ int enabled;
    /* 0x00C */ int pending;
    /* 0x010 */ int count;
    /* 0x014 */ unsigned char item[3];
    /* 0x017 */ unsigned char unused;
    /* 0x018 */ unsigned char pad_018[0x78];
    /* 0x090 */ int targetId;
    /* 0x094 */ int sourceId;
    /* 0x098 */ int hitCount;
    /* 0x09C */ void *target;
    /* 0x0A0 */ float distance;
    /* 0x0A4 */ unsigned char pad_0A4[0x10];
    /* 0x0B4 */ unsigned char *driver;
    /* 0x0B8 */ void *targetDriver;
};

#endif /* GAME_TYPES_RACESLOT_H */
