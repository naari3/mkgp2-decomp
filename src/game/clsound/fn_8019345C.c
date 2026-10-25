extern unsigned char lbl_806CFCA1;
extern void fn_80195214(unsigned char v);

void fn_8019345C(unsigned char v) {
    if (v > 0x80) {
        v = 0x80;
    }
    if (lbl_806CFCA1 != v) {
        lbl_806CFCA1 = v;
        fn_80195214(v);
    }
}
