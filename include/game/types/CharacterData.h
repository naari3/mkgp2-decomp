#ifndef GAME_TYPES_CHARACTERDATA_H
#define GAME_TYPES_CHARACTERDATA_H

/* Merged from 4 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CharacterData CharacterData;
struct CharacterData {
    /* 0x000 */ void *name;
    /* 0x004 */ void *driver_model;
    /* 0x008 */ void *kart_model;
    /* 0x00C */ unsigned char pad_00C[0x10];
    /* 0x01C */ float anim1C;
    /* 0x020 */ unsigned char pad_020[0x4];
    /* 0x024 */ float anim24;
    /* 0x028 */ unsigned char pad_028[0x4];
};

#endif /* GAME_TYPES_CHARACTERDATA_H */
