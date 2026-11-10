#ifndef GAME_TYPES_RESULTPANEL_H
#define GAME_TYPES_RESULTPANEL_H

struct ObjPair;
struct ObjTrio;
struct ResultFader;
struct VObj;
struct VObj14;
struct VObj14F;
struct VObjCF;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ResultPanel ResultPanel;
struct ResultPanel {
    /* 0x000 */ void *vt;
    /* 0x004 */ unsigned char done;
    /* 0x005 */ unsigned char pad_005[0x3];
    /* 0x008 */ struct VObj14 *f8;
    /* 0x00C */ struct VObj14 *fC;
    /* 0x010 */ struct VObj14 *f10;
    /* 0x014 */ void *f14;
    /* 0x018 */ void *f18;
    /* 0x01C */ unsigned char pad_01C[0x4];
    /* 0x020 */ unsigned char f20;
    /* 0x021 */ unsigned char f21;
    /* 0x022 */ unsigned char pad_022[0x2];
    /* 0x024 */ int state;
    /* 0x028 */ float t;
    /* 0x02C */ unsigned char pad_02C[0x8];
    /* 0x034 */ unsigned char f34;
    /* 0x035 */ unsigned char pad_035[0x3];
    /* 0x038 */ int item;
    /* 0x03C */ struct VObj *f3C;
    /* 0x040 */ unsigned char f40;
    /* 0x041 */ unsigned char pad_041[0x3];
    /* 0x044 */ struct VObj14F *f44;
    /* 0x048 */ unsigned char pad_048[0x4];
    /* 0x04C */ unsigned char f4C;
    /* 0x04D */ unsigned char pad_04D[0x3];
    /* 0x050 */ struct VObj14 *f50;
    /* 0x054 */ struct VObjCF *f54;
    /* 0x058 */ unsigned char f58;
    /* 0x059 */ unsigned char pad_059[0x3];
    /* 0x05C */ float f5C;
    /* 0x060 */ unsigned char pad_060[0x4];
    /* 0x064 */ struct ResultFader *f64;
    /* 0x068 */ struct ObjTrio *f68;
    /* 0x06C */ struct ObjPair *f6C;
    /* 0x070 */ unsigned char f70;
    /* 0x071 */ unsigned char pad_071[0x3];
};

#endif /* GAME_TYPES_RESULTPANEL_H */
