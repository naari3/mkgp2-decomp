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

float fn_8018A8D4(void) {
    if (lbl_806D1698) {
        float value = 0.0f;
        value += 60.0f * (float)ReadBits(lbl_80377C00[12], lbl_80377BE0[12]);
        value += 10.0f * (float)ReadBits(lbl_80377C00[13], lbl_80377BE0[13]);
        value += (float)ReadBits(lbl_80377C00[14], lbl_80377BE0[14]);
        value += (float)ReadBits(lbl_80377C00[15], lbl_80377BE0[15]) / 10.0f;
        value += (float)ReadBits(lbl_80377C00[16], lbl_80377BE0[16]) / 100.0f;
        value += (float)ReadBits(lbl_80377C00[17], lbl_80377BE0[17]) / 1000.0f;
        return value;
    }
    return 0.0f;
}
