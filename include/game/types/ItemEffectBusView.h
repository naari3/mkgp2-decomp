#ifndef GAME_TYPES_ITEMEFFECTBUSVIEW_H
#define GAME_TYPES_ITEMEFFECTBUSVIEW_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemEffectBusView ItemEffectBusView;
struct ItemEffectBusView {
    /* 0x000 */ unsigned char pad_000[0x10];
    /* 0x010 */ unsigned long long flags;
};

#endif /* GAME_TYPES_ITEMEFFECTBUSVIEW_H */
