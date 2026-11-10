#ifndef GAME_TYPES_SNDSLOT_H
#define GAME_TYPES_SNDSLOT_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SndSlot SndSlot;
struct SndSlot {
    /* 0x000 */ unsigned int flags;
    /* 0x004 */ unsigned int id;
    /* 0x008 */ unsigned char group;
    /* 0x009 */ unsigned char pad_009[0xF];
    /* 0x018 */ unsigned char x18;
    /* 0x019 */ unsigned char pad_019[0x3];
};

#endif /* GAME_TYPES_SNDSLOT_H */
