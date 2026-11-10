#ifndef GAME_TYPES_DISPATCHKART_H
#define GAME_TYPES_DISPATCHKART_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DispatchKart DispatchKart;
struct DispatchKart {
    /* 0x000 */ unsigned char pad_000[0x238];
    /* 0x238 */ int wingEnabled;
    /* 0x23C */ unsigned char pad_23C[0x94];
    /* 0x2D0 */ unsigned char mode2Enabled;
    /* 0x2D1 */ unsigned char pad_2D1[0x3];
};

#endif /* GAME_TYPES_DISPATCHKART_H */
