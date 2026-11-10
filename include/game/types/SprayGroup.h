#ifndef GAME_TYPES_SPRAYGROUP_H
#define GAME_TYPES_SPRAYGROUP_H

struct SprayEffect;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SprayGroup SprayGroup;
struct SprayGroup {
    /* 0x000 */ unsigned char pad_000[0x10];
    /* 0x010 */ struct SprayEffect *children[8];
    /* 0x030 */ unsigned char pad_030[0x84];
    /* 0x0B4 */ unsigned int timers[4];
    /* 0x0C4 */ signed char variant;
    /* 0x0C5 */ unsigned char pad_0C5[0x3];
};

#endif /* GAME_TYPES_SPRAYGROUP_H */
