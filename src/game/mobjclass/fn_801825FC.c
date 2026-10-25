extern void *lbl_806D167C;
extern unsigned char lbl_80495B58[];
extern void *HSD_MObjGetDefaultClass(void);
extern void HSD_MObjSetDefaultClass(void *info);

int fn_801825FC(void) {
    if (lbl_806D167C != 0) {
        return 0;
    }
    lbl_806D167C = HSD_MObjGetDefaultClass();
    HSD_MObjSetDefaultClass(lbl_80495B58);
    return 1;
}
