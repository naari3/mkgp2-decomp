extern void *Alloc(int size);
extern void *lbl_806D18A8;

void *fn_801DC664(void) {
    if (lbl_806D18A8 == 0) {
        lbl_806D18A8 = Alloc(1);
    }
    return lbl_806D18A8;
}
