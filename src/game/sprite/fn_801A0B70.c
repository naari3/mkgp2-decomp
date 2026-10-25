extern unsigned char lbl_806D16E0;
extern int lbl_806D16E4;

int fn_801A0B70(unsigned char force) {
    if (!lbl_806D16E0) {
        return 1;
    }
    if (!force && lbl_806D16E4 != 0) {
        return 0;
    }
    lbl_806D16E0 = 0;
    lbl_806D16E4 = 0;
    return 1;
}
