#ifndef GAME_TYPES_EFFECTSTATE_H
#define GAME_TYPES_EFFECTSTATE_H

struct EffectResource;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct EffectState EffectState;
struct EffectState {
    /* 0x000 */ unsigned char pad_000[0x1C];
    /* 0x01C */ int content;  /* also: handle */
    /* 0x020 */ struct EffectResource *resource;
};

#endif /* GAME_TYPES_EFFECTSTATE_H */
