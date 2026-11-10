#ifndef GAME_TYPES_KARTOBJ_H
#define GAME_TYPES_KARTOBJ_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartObj KartObj;
struct KartObj {
    /* 0x000 */ unsigned char pad_000[0xF0];
    /* 0x0F0 */ int hitCooldown;
};

#endif /* GAME_TYPES_KARTOBJ_H */
