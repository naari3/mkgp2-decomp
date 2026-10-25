extern char *lbl_806D1650;
extern void HSD_Free(void *);

void fn_8018013C(void) {
    if (lbl_806D1650 != 0) {
        HSD_Free(lbl_806D1650);
        lbl_806D1650 = 0;
    }
}
