#ifndef GAME_TYPES_KARTITEM_H
#define GAME_TYPES_KARTITEM_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartItem KartItem;
struct KartItem {
    /* 0x000 */ unsigned char pad_000[0x1F0];
    /* 0x1F0 */ long currentState;
    /* 0x1F4 */ unsigned char pad_1F4[0x10];
    /* 0x204 */ unsigned char flag204;
    /* 0x205 */ unsigned char pad_205[0x43];
    /* 0x248 */ int slot;
    /* 0x24C */ unsigned char pad_24C[0x50];
    /* 0x29C */ void *driver;
    /* 0x2A0 */ unsigned char pad_2A0[0x20];
    /* 0x2C0 */ long currentItemId;
    /* 0x2C4 */ unsigned char pad_2C4[0x74];
    /* 0x338 */ float velocity[3];
};

#endif /* GAME_TYPES_KARTITEM_H */
