#ifndef GAME_TYPES_FLOWPANEL_H
#define GAME_TYPES_FLOWPANEL_H

struct ResCtrl;
struct Sprite;
struct TexMgr;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct FlowPanel FlowPanel;
struct FlowPanel {
    /* 0x000 */ int state;
    /* 0x004 */ int field4;
    /* 0x008 */ int field8;
    /* 0x00C */ int fieldC;
    /* 0x010 */ int alpha;
    /* 0x014 */ int layer;
    /* 0x018 */ unsigned char pad_018[0x8];
    /* 0x020 */ unsigned char showBg;
    /* 0x021 */ unsigned char pad_021[0x27];
    /* 0x048 */ void *labelB;
    /* 0x04C */ struct Sprite *labelA;
    /* 0x050 */ struct ResCtrl *icons[3];
    /* 0x05C */ struct TexMgr *texts[3];
};

#endif /* GAME_TYPES_FLOWPANEL_H */
