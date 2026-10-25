extern "C" {
extern char lbl_8039FD04[];
void DebugPrintf(const char *fmt, ...);
}

struct PcbLink {
    unsigned char f0;
    int f4;
    int f8;
    int fC;
    unsigned char f10;
    unsigned char f11;
    unsigned char f12;

    PcbLink() {
        f0 = 0;
        f4 = 0;
        f8 = 0;
        fC = 0;
        f10 = 0;
        f11 = 0;
        f12 = 0;
        DebugPrintf(lbl_8039FD04);
    }
};

extern "C" PcbLink *lbl_806D1878;

extern "C" PcbLink *fn_801DAEC0(void) {
    if (lbl_806D1878 == 0) {
        lbl_806D1878 = new PcbLink;
    }
    return lbl_806D1878;
}
