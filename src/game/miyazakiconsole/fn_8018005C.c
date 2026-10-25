extern char *lbl_806D1650;
extern unsigned int lbl_806CFB98;
extern unsigned int lbl_806CFB9C;
extern char *strncat(char *, const char *, unsigned long);
extern void OverlayText(int, int, int, const char *, ...);

void fn_8018005C(void) {
    unsigned int x;
    unsigned int y;
    char line[256];
    if (lbl_806D1650 == 0) {
        return;
    }
    for (y = 0; y < lbl_806CFB9C; y++) {
        line[0] = 0;
        for (x = 0; x < lbl_806CFB98; x++) {
            strncat(line, &lbl_806D1650[y * lbl_806CFB98 + x], 1);
        }
        OverlayText(1, 0, y, line);
    }
}
