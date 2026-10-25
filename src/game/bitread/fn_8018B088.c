extern unsigned char lbl_806D1698;
extern const unsigned char lbl_80377BE0[];
extern const unsigned char lbl_80377C00[];
extern unsigned char lbl_80677EE8[];

static inline unsigned char ReadBits(int start, int n) {
    unsigned char result = 0;
    int i;
    for (i = 0; i < n && i + start < 125; i++) {
        result |= ((lbl_80677EE8[(start + i) / 5] >> (4 - (start + i) % 5)) & 1) << (n - (i + 1));
    }
    return result;
}

int fn_8018B088(void) {
    if (lbl_806D1698) {
        return ReadBits(lbl_80377C00[5], lbl_80377BE0[5]);
    }
    return -1;
}
