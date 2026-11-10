#ifndef GAME_TYPES_PATHSLOT_H
#define GAME_TYPES_PATHSLOT_H

/* Merged from 5 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct PathSlot PathSlot;
struct PathSlot {
    /* 0x000 */ float v[3];
    /* 0x00C */ float speed;
    /* 0x010 */ float accel;
    /* 0x014 */ int ids[3];
    /* 0x020 */ unsigned char pad_020[0x60];
    /* 0x080 */ int maxProgress;
    /* 0x084 */ unsigned char pad_084[0x14];
};

#endif /* GAME_TYPES_PATHSLOT_H */
