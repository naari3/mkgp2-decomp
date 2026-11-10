#ifndef GAME_TYPES_OPTIONMENU_H
#define GAME_TYPES_OPTIONMENU_H

struct DrawObj;
struct MenuTarget;
struct Widget;

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct OptionMenu OptionMenu;
struct OptionMenu {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ unsigned char done;
    /* 0x005 */ unsigned char pad_005[0x3];
    /* 0x008 */ unsigned char started;
    /* 0x009 */ unsigned char pad_009[0x3];
    /* 0x00C */ int state;
    /* 0x010 */ float timer;
    /* 0x014 */ int page;
    /* 0x018 */ int nextPage;
    /* 0x01C */ unsigned char stickHeld;
    /* 0x01D */ unsigned char toggleEnabled;
    /* 0x01E */ unsigned char pad_01E[0x2];
    /* 0x020 */ struct MenuTarget *target;
    /* 0x024 */ unsigned char pad_024[0x4];
    /* 0x028 */ int timeout;
    /* 0x02C */ struct DrawObj *bg;
    /* 0x030 */ struct DrawObj *frame;
    /* 0x034 */ struct Widget *w34;
    /* 0x038 */ struct Widget *w38;
    /* 0x03C */ struct Widget *w3C;
    /* 0x040 */ struct Widget *w40;
    /* 0x044 */ float blink;
    /* 0x048 */ unsigned char pad_048[0x4];
    /* 0x04C */ bool toggle;
    /* 0x04D */ unsigned char pad_04D[0x3];
    /* 0x050 */ float fade50;
    /* 0x054 */ float fade54;
    /* 0x058 */ unsigned char sel;
    /* 0x059 */ unsigned char pad_059[0x3];
    /* 0x05C */ float blink2;
    /* 0x060 */ int count;
    /* 0x064 */ int value;
    /* 0x068 */ int equipped;
    /* 0x06C */ int rule;
    /* 0x070 */ unsigned char flags[6];
    /* 0x076 */ unsigned char pad_076[0x2];
    /* 0x078 */ unsigned short wins;
    /* 0x07A */ unsigned short losses;
    /* 0x07C */ signed char digitsA[3];
    /* 0x07F */ signed char digitsB[3];
    /* 0x082 */ unsigned char pad_082[0x2];
    /* 0x084 */ int scroll;
    /* 0x088 */ int scrollTimer;
    /* 0x08C */ float time[6];
    /* 0x0A4 */ int course[6];
    /* 0x0BC */ int mode[6];
    /* 0x0D4 */ int isNew[6];
    /* 0x0EC */ int kind[6];
};

#endif /* GAME_TYPES_OPTIONMENU_H */
