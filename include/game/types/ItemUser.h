#ifndef GAME_TYPES_ITEMUSER_H
#define GAME_TYPES_ITEMUSER_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemUser ItemUser;
struct ItemUser {
    /* 0x000 */ unsigned char pad_000[0x18];
    /* 0x018 */ int unk18;
    /* 0x01C */ int unk1C;
    /* 0x020 */ int unk20;
    /* 0x024 */ int unk24;
};

#endif /* GAME_TYPES_ITEMUSER_H */
