#ifndef GAME_TYPES_PATHENTRY_H
#define GAME_TYPES_PATHENTRY_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct PathEntry PathEntry;
struct PathEntry {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ int node;
    /* 0x008 */ int field8;
    /* 0x00C */ float *px;
    /* 0x010 */ float *py;
    /* 0x014 */ float *pz;
    /* 0x018 */ float hist[10];
    /* 0x040 */ float field40;
    /* 0x044 */ unsigned char field44;
    /* 0x045 */ unsigned char field45;
    /* 0x046 */ unsigned char field46;
    /* 0x047 */ unsigned char pad_047[0x1];
    /* 0x048 */ short field48;
    /* 0x04A */ short total;
    /* 0x04C */ float field4C;
    /* 0x050 */ int field50;
    /* 0x054 */ float dist;
    /* 0x058 */ int field58;
    /* 0x05C */ int field5C;
    /* 0x060 */ int field60;
    /* 0x064 */ unsigned char pad_064[0xC];
    /* 0x070 */ int segment;
    /* 0x074 */ int field74;
    /* 0x078 */ int field78;
    /* 0x07C */ int field7C;
    /* 0x080 */ float pos[3];
    /* 0x08C */ void *field8C;
    /* 0x090 */ void *kart;
    /* 0x094 */ int field94;
};

#endif /* GAME_TYPES_PATHENTRY_H */
