extern "C" {
extern char lbl_803BD0A8[];
void DebugPrintf(const char *fmt, ...);
}

struct AISingleton {
    unsigned char dummy;

    AISingleton() {
        DebugPrintf(lbl_803BD0A8);
    }
};

extern "C" AISingleton *lbl_806D18B4;

extern "C" AISingleton *fn_801DE1B0(void) {
    if (lbl_806D18B4 == 0) {
        lbl_806D18B4 = new AISingleton;
    }
    return lbl_806D18B4;
}
