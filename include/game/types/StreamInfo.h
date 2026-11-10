#ifndef GAME_TYPES_STREAMINFO_H
#define GAME_TYPES_STREAMINFO_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct StreamInfo StreamInfo;
struct StreamInfo {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ unsigned int byteLength;
    /* 0x008 */ unsigned int frequency;
    /* 0x00C */ unsigned short loop;
    /* 0x00E */ unsigned char pad_00E[0x2];
    /* 0x010 */ unsigned int loopStart;
    /* 0x014 */ unsigned int loopEnd;
    /* 0x018 */ unsigned char pad_018[0x4];
    /* 0x01C */ unsigned char adpcm[0x44];
};

#endif /* GAME_TYPES_STREAMINFO_H */
