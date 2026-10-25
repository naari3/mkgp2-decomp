extern unsigned char lbl_806D16E0;
extern int lbl_806D16E4;

int fn_801A0BB4(void) {
    if (lbl_806D16E0) {
        return 1;
    }
    lbl_806D16E0 = 1;
    lbl_806D16E4 = 0;
    return 1;
}
