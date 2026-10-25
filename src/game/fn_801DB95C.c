extern void *Alloc(int size);
extern void *lbl_806D1890;

void *fn_801DB95C(void) {
    if (lbl_806D1890 == 0) {
        lbl_806D1890 = Alloc(1);
    }
    return lbl_806D1890;
}
