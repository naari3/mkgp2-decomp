#ifndef GAME_TYPES_CLSTREAM_H
#define GAME_TYPES_CLSTREAM_H

#include "game/types/DVDFileInfo.h"

struct StreamInfo;

/* Merged from 10 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ClStream ClStream;
struct ClStream {
    /* 0x000 */ unsigned char state;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ struct ClStream *pair;
    /* 0x008 */ struct ClStream *pair2;
    /* 0x00C */ unsigned int handle;
    /* 0x010 */ unsigned int flags;
    /* 0x014 */ unsigned char rate;
    /* 0x015 */ unsigned char volume;
    /* 0x016 */ unsigned char pan;
    /* 0x017 */ unsigned char bus;
    /* 0x018 */ DVDFileInfo file;
    /* 0x054 */ struct StreamInfo *info;
    /* 0x058 */ unsigned int size;
    /* 0x05C */ unsigned char *base;
    /* 0x060 */ unsigned char head;
    /* 0x061 */ unsigned char pad_061[0x3];
    /* 0x064 */ unsigned int mask;
    /* 0x068 */ unsigned char x68;
    /* 0x069 */ unsigned char pad_069[0x3];
    /* 0x06C */ unsigned int pos;
    /* 0x070 */ unsigned int fill;
    /* 0x074 */ unsigned char pad_074[0x4];
};

#endif /* GAME_TYPES_CLSTREAM_H */
