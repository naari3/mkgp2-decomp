#ifndef GAME_TYPES_KARTITEMAUDIO_H
#define GAME_TYPES_KARTITEMAUDIO_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartItemAudio KartItemAudio;
struct KartItemAudio {
    /* 0x000 */ int charId;
    /* 0x004 */ unsigned char playerType;
    /* 0x005 */ unsigned char pad_005[0x1];
    /* 0x006 */ unsigned char voiceOn;
    /* 0x007 */ unsigned char pad_007[0x1];
    /* 0x008 */ unsigned int channel;
    /* 0x00C */ float *mtx;
    /* 0x010 */ unsigned char pad_010[0x18];
    /* 0x028 */ int voiceHandle;
};

#endif /* GAME_TYPES_KARTITEMAUDIO_H */
