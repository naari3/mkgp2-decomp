#ifndef GAME_TYPES_ITEMSTATEGUARD_H
#define GAME_TYPES_ITEMSTATEGUARD_H

struct GuardedItem;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemStateGuard ItemStateGuard;
struct ItemStateGuard {
    /* 0x000 */ unsigned char pad_000[0x18];
    /* 0x018 */ struct GuardedItem *active;  /* also: item */
};

#endif /* GAME_TYPES_ITEMSTATEGUARD_H */
