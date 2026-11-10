#ifndef GAME_TYPES_ITEMEFFECTSTATE_H
#define GAME_TYPES_ITEMEFFECTSTATE_H

#include "game/types/ItemEffectCallback.h"

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemEffectState ItemEffectState;
struct ItemEffectState {
    /* 0x000 */ int type;  /* also: slot */
    /* 0x004 */ int target;
    /* 0x008 */ int owner;
    /* 0x00C */ ItemEffectCallback cb;
    /* 0x018 */ int picked;  /* also: timer */
    /* 0x01C */ float scale;
    /* 0x020 */ int index;
    /* 0x024 */ int flags;
};

#endif /* GAME_TYPES_ITEMEFFECTSTATE_H */
