typedef struct CharEntry {
    unsigned short card;
    unsigned short code;
    int width;
    int height;
    int advance;
} CharEntry;

extern CharEntry lbl_804E5590[];
extern CharEntry lbl_804E83C0[];

unsigned short fn_801F8D58(unsigned short c) {
    unsigned short ret = 0x8140;
    int i;
    for (i = 0; i < 0x32F; i++) {
        if (c == lbl_804E83C0[i].card) {
            ret = lbl_804E83C0[i].code;
            break;
        }
    }
    return ret;
}

unsigned short fn_801F8DB0(unsigned short c) {
    unsigned short ret = 0x8140;
    int i;
    for (i = 0; i < 0x2E3; i++) {
        if (c == lbl_804E5590[i].card) {
            ret = lbl_804E5590[i].code;
            break;
        }
    }
    return ret;
}
