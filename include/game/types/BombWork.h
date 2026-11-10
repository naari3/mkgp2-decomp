#ifndef GAME_TYPES_BOMBWORK_H
#define GAME_TYPES_BOMBWORK_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct BombWork BombWork;
struct BombWork {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ unsigned int timers[4];
    /* 0x014 */ unsigned char pad_014[0x38];
    /* 0x04C */ unsigned char *fx[4];
    /* 0x05C */ unsigned char pad_05C[0x20];
    /* 0x07C */ int approach;
    /* 0x080 */ unsigned char pad_080[0x18];
    /* 0x098 */ void *driver;
    /* 0x09C */ void *target;
    /* 0x0A0 */ signed char launch;
    /* 0x0A1 */ unsigned char pad_0A1[0x3];
};

#endif /* GAME_TYPES_BOMBWORK_H */
