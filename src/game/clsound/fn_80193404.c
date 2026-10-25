extern unsigned char lbl_806CFCA2;
extern const char lbl_8037D014[];
extern void fn_801951FC(unsigned char v);
extern void DebugPrintf(const char *fmt, ...);

void fn_80193404(unsigned char v) {
    if (v > 0x80) {
        v = 0x80;
    }
    if (lbl_806CFCA2 != v) {
        lbl_806CFCA2 = v;
        fn_801951FC(v);
    }
    DebugPrintf(lbl_8037D014, lbl_806CFCA2);
}
