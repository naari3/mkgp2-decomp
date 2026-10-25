extern const float lbl_806D89F0;
extern const float lbl_806D89F4;
extern const float lbl_806D89F8;
extern const float lbl_806D89FC;
extern const float lbl_806D8A00;

int fn_80167744(unsigned int digit, float t) {
    switch (digit) {
    case 0: return (int)(lbl_806D89F0 * t) % 10;
    case 1: return (int)(lbl_806D89F4 * t) % 10;
    case 2: return (int)(lbl_806D89F8 * t) % 10;
    case 4: return (int)t % 10;
    case 5: return (int)(t / lbl_806D89F8) % 6;
    case 7: return (int)(t / lbl_806D89FC) % 10;
    case 8: return (int)(t / lbl_806D8A00) % 6;
    case 3: return 0xb;
    case 6: return 0xa;
    }
    return 0;
}
