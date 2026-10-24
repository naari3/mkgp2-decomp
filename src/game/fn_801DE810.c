extern void *Alloc(int size);
extern void *lbl_806D18C0;

void *fn_801DE810(void) {
    if (lbl_806D18C0 == 0) {
        lbl_806D18C0 = Alloc(1);
    }
    return lbl_806D18C0;
}
