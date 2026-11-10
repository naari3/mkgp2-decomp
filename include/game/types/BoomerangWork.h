#ifndef GAME_TYPES_BOOMERANGWORK_H
#define GAME_TYPES_BOOMERANGWORK_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct BoomerangWork BoomerangWork;
struct BoomerangWork {
    /* 0x000 */ unsigned char thrown;
    /* 0x001 */ unsigned char hits;
    /* 0x002 */ unsigned char pad_002[0x2];
    /* 0x004 */ unsigned int timers[4];
    /* 0x014 */ float pace;
    /* 0x018 */ float tether;
    /* 0x01C */ float tetherScale;
    /* 0x020 */ unsigned char pad_020[0x3C];
    /* 0x05C */ unsigned char *sub;
    /* 0x060 */ unsigned char pad_060[0x30];
    /* 0x090 */ unsigned char spawned;
    /* 0x091 */ unsigned char pad_091[0x3];
    /* 0x094 */ void *owner;
    /* 0x098 */ void *driver;
    /* 0x09C */ void *target;
    /* 0x0A0 */ signed char launch;
    /* 0x0A1 */ unsigned char pad_0A1[0x4F];
    /* 0x0F0 */ unsigned char shellColor;
    /* 0x0F1 */ unsigned char pad_0F1[0x3];
};

#endif /* GAME_TYPES_BOOMERANGWORK_H */
