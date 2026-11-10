#ifndef GAME_TYPES_EFFECTSLOT_H
#define GAME_TYPES_EFFECTSLOT_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct EffectSlot EffectSlot;
struct EffectSlot {
    /* 0x000 */ unsigned char pad_000[0x2C];
    /* 0x02C */ int mode;
    /* 0x030 */ unsigned char pad_030[0x64];
};

#endif /* GAME_TYPES_EFFECTSLOT_H */
