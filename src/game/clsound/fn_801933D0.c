extern unsigned char lbl_806D16B1;
extern void fn_801951B4(unsigned char v);

void fn_801933D0(unsigned char v) {
    if (lbl_806D16B1 != v) {
        lbl_806D16B1 = v;
        fn_801951B4(v);
    }
}
