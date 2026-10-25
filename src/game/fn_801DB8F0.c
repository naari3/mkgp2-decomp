extern void *Alloc(int size);
extern void *lbl_806D1888;

void *fn_801DB8F0(void) {
    if (lbl_806D1888 == 0) {
        lbl_806D1888 = Alloc(1);
    }
    return lbl_806D1888;
}
