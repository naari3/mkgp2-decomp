extern void *lbl_806D167C;
extern void HSD_MObjSetDefaultClass(void *info);

void fn_801825C8(void) {
    if (lbl_806D167C != 0) {
        HSD_MObjSetDefaultClass(lbl_806D167C);
        lbl_806D167C = 0;
    }
}
