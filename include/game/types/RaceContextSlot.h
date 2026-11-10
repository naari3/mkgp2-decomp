#ifndef GAME_TYPES_RACECONTEXTSLOT_H
#define GAME_TYPES_RACECONTEXTSLOT_H

/* Merged from 6 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct RaceContextSlot RaceContextSlot;
struct RaceContextSlot {
    /* 0x000 */ int type;  /* also: kind */
    /* 0x004 */ int id;
    /* 0x008 */ unsigned int word08;
    /* 0x00C */ unsigned int word0C;
    /* 0x010 */ unsigned char pad_010[0x60];
    /* 0x070 */ void *driver;  /* also: object70 */
    /* 0x074 */ unsigned char pad_074[0xC];
    /* 0x080 */ void *position;
    /* 0x084 */ int index84;
    /* 0x088 */ unsigned int word88;
    /* 0x08C */ unsigned int word8C;
    /* 0x090 */ int index90;
    /* 0x094 */ int index94;
    /* 0x098 */ unsigned char pad_098[0x4];
    /* 0x09C */ unsigned int word9C;
    /* 0x0A0 */ unsigned char pad_0A0[0x4];
    /* 0x0A4 */ float scale;
    /* 0x0A8 */ void *item;
    /* 0x0AC */ int indexAC;
    /* 0x0B0 */ int state;
    /* 0x0B4 */ unsigned int payloadB4;  /* also: driver */
    /* 0x0B8 */ unsigned int wordB8;
};

#endif /* GAME_TYPES_RACECONTEXTSLOT_H */
