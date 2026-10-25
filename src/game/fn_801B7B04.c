extern unsigned char lbl_806D184F;
extern unsigned char lbl_806D1850;
extern float lbl_806D1854;
extern unsigned char lbl_806D1858;

void fn_801B7B04(unsigned char reset) {
    if (reset) {
        lbl_806D184F = 0;
        lbl_806D1850 = 0;
        lbl_806D1858 = 0;
        return;
    }
    if (lbl_806D184F == 1) {
        lbl_806D184F = 0;
        lbl_806D1850 = 1;
    }
}

void StartScreenFade(float duration) {
    if (lbl_806D184F == 0) {
        lbl_806D184F = 1;
        lbl_806D1850 = 0;
        lbl_806D1854 = duration;
    }
}
