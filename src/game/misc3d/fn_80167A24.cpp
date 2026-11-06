extern "C" {
extern const unsigned char lbl_8036A390[0x200];
void fn_801685A4(void *, const char *, float, float, float, float, float, float, ...);
static inline int GetTimeDigit(unsigned int digit, float t) {
    switch (digit) {
    case 0: return (int)(1000.0f * t) % 10;
    case 1: return (int)(100.0f * t) % 10;
    case 2: return (int)(10.0f * t) % 10;
    case 4: return (int)t % 10;
    case 5: return (int)(t / 10.0f) % 6;
    case 7: return (int)(t / 60.0f) % 10;
    case 8: return (int)(t / 600.0f) % 6;
    case 3: return 11;
    case 6: return 10;
    }
    return 0;
}
void fn_80167A24(void *dst, unsigned int flags, float x, float y, float red, float green, float blue, float alpha, float time) {
    struct Digits { int d[7]; };
    Digits init = *(const Digits *)(lbl_8036A390 + 0x24A8);
    int *digits = init.d;
    digits[0] = GetTimeDigit(0, time);
    digits[1] = GetTimeDigit(1, time);
    digits[2] = GetTimeDigit(2, time);
    digits[3] = GetTimeDigit(4, time);
    digits[4] = GetTimeDigit(5, time);
    digits[5] = GetTimeDigit(7, time);
    digits[6] = GetTimeDigit(8, time);
    if (flags & 1) {
        fn_801685A4(dst, (const char *)lbl_8036A390 + 0x24E0, x,y,red,green,blue,alpha,
          digits[6],digits[5],digits[4],digits[3],digits[2],digits[1],digits[0]);
    } else if (flags & 2) {
        if (digits[6] == 0) {
            fn_801685A4(dst, (const char *)lbl_8036A390 + 0x24F4, x,y,red,green,blue,alpha,
              digits[5],digits[4],digits[3],digits[2],digits[1],digits[0]);
        } else {
            fn_801685A4(dst, (const char *)lbl_8036A390 + 0x24E0, x,y,red,green,blue,alpha,
              digits[6],digits[5],digits[4],digits[3],digits[2],digits[1],digits[0]);
        }
    } else {
        fn_801685A4(dst, (const char *)lbl_8036A390 + 0x2508, x,y,red,green,blue,alpha,
          digits[5],digits[4],digits[3],digits[2],digits[1],digits[0]);
    }
}
}
