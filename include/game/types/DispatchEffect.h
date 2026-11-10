#ifndef GAME_TYPES_DISPATCHEFFECT_H
#define GAME_TYPES_DISPATCHEFFECT_H

struct DispatchKart;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DispatchEffect DispatchEffect;
struct DispatchEffect {
    /* 0x000 */ unsigned char pad_000[0x10];
    /* 0x010 */ unsigned int index;  /* also: side */
    /* 0x014 */ unsigned char pad_014[0x108];
    /* 0x11C */ struct DispatchKart *kart;
    /* 0x120 */ unsigned char pad_120[0x70];
    /* 0x190 */ unsigned char variant;
    /* 0x191 */ unsigned char pad_191[0x3];
};

#endif /* GAME_TYPES_DISPATCHEFFECT_H */
