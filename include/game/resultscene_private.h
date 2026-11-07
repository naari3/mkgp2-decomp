#ifndef GAME_RESULTSCENE_PRIVATE_H
#define GAME_RESULTSCENE_PRIVATE_H

/* Private ABI views for resultscene.cpp constructor-owned objects. */
struct ResultPopupSprite {
    int field0, layer, field8;
    float x, y, sx, sy, angle, alpha;
    char pad24[0x30 - 0x24];
    ResultPopupSprite(int resource, int mode, int flags);
};
struct ResultPopupText {
    float x, y, cursorX, scaleX, scaleY, angle;
    int font;
    int field1c;
    unsigned int color;
    unsigned short glyphs[256];
    float z;
    int mode;
    float advance;
    ResultPopupText();
};

struct ResultInner;

struct PopupInputState {
    char pad[4];
    unsigned char active;
    char pad5[0x14 - 5];
    int x14;
    int x18;
    int x1c;
};

struct PopupCursorSprite {
    char pad[0x1c];
    float y;
};

struct ResultPartBUpdate {
    void *vt;
    int unused4;
    int sound;
    unsigned char soundStarted;
    char pad0d[3];
    int stage;
    float timer;
    unsigned char on;
    char pad19[3];
    void *p1c;
    ResultInner *inner;
    void *sprite;
    char pad28[0x5c - 0x28];
    unsigned int innerCol[4];
    char pad6c[0xb4 - 0x6c];
    unsigned int fadeCol[4];
};

/* 24-byte staff-roll records: text, cached length, scroll y, colour and
 * a "large font" flag. The table ends with a null text. */
struct ResultMessageRecord {
    const char *text;
    unsigned int length;
    float y;
    int padc;
    int color;
    unsigned char big;
    char pad15[3];
};

#endif
