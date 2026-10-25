typedef struct CharEntry {
    unsigned short card;
    unsigned short code;
    int width;
    int height;
    int advance;
} CharEntry;

typedef struct GlyphPos {
    short x;
    short y;
    short w;
    short h;
} GlyphPos;

extern CharEntry lbl_804E5590[];
extern const GlyphPos lbl_803BF0A0[][8];

int fn_801F9628(unsigned short c) {
    int i;
    if ((c & 0x8000) == 0) {
        for (i = 0x28E; i < 0x28E + 0x55; i++) {
            if (c == lbl_804E5590[i].code) {
                return lbl_804E5590[i].width;
            }
        }
        return 0x1ECD;
    }
    for (i = 0; i < 0x28E; i++) {
        if (c == lbl_804E5590[i].code) {
            return lbl_804E5590[i].width;
        }
    }
    return 0x1ECD;
}

int fn_801F96D0(unsigned short c) {
    int i;
    if ((c & 0x8000) == 0) {
        for (i = 0x28E; i < 0x28E + 0x55; i++) {
            if (c == lbl_804E5590[i].code) {
                return lbl_804E5590[i].height;
            }
        }
        return 0x23E5;
    }
    for (i = 0; i < 0x28E; i++) {
        if (c == lbl_804E5590[i].code) {
            return lbl_804E5590[i].height;
        }
    }
    return 0x23E5;
}

int fn_801F9778(unsigned short c) {
    int i;
    if ((c & 0x8000) == 0) {
        for (i = 0x28E; i < 0x28E + 0x55; i++) {
            if (c == lbl_804E5590[i].code) {
                return lbl_804E5590[i].advance;
            }
        }
        return 0x3F6;
    }
    for (i = 0; i < 0x28E; i++) {
        if (c == lbl_804E5590[i].code) {
            return lbl_804E5590[i].advance;
        }
    }
    return 0x3F6;
}

int fn_801F9820(void *self, int row, int col) {
    row -= 1;
    return lbl_803BF0A0[row][col].w;
}

int fn_801F9844(void *self, int row, int col) {
    row -= 1;
    return lbl_803BF0A0[row][col].y;
}

int fn_801F9868(void *self, int row, int col) {
    row -= 1;
    return lbl_803BF0A0[row][col].x;
}
