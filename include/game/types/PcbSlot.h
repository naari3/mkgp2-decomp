#ifndef GAME_TYPES_PCBSLOT_H
#define GAME_TYPES_PCBSLOT_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct PcbSlot PcbSlot;
struct PcbSlot {
    /* 0x000 */ unsigned char b0;
    /* 0x001 */ unsigned char pad_001[0x2];
    /* 0x003 */ unsigned char b3;
    /* 0x004 */ unsigned char pad_004[0x12];
    /* 0x016 */ unsigned short name[6];
};

#endif /* GAME_TYPES_PCBSLOT_H */
