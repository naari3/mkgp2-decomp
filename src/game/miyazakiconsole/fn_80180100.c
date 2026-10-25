extern char *lbl_806D1650;
extern unsigned int lbl_806CFB98;
extern unsigned int lbl_806CFB9C;
extern void *memset(void *, int, unsigned long);

void fn_80180100(void) {
    if (lbl_806D1650 != 0) {
        memset(lbl_806D1650, ' ', lbl_806CFB98 * lbl_806CFB9C);
    }
}
