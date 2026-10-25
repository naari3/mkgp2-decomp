extern unsigned char lbl_806CFCA0;
extern const char lbl_8037D038[];
extern void DebugPrintf(const char *fmt, ...);

void fn_801934A0(unsigned char v) {
    if (v > 0x80) {
        v = 0x80;
    }
    if (lbl_806CFCA0 != v) {
        lbl_806CFCA0 = v;
    }
    DebugPrintf(lbl_8037D038, lbl_806CFCA0);
}
