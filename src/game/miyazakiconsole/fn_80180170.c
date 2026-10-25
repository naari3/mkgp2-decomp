extern char *lbl_806D1650;
extern unsigned int lbl_806CFB98;
extern unsigned int lbl_806CFB9C;
extern void *memset(void *, int, unsigned long);
extern void *HSD_MemAlloc(unsigned long);

static inline void Clear(void) {
    if (lbl_806D1650 != 0) {
        memset(lbl_806D1650, ' ', lbl_806CFB98 * lbl_806CFB9C);
    }
}

void fn_80180170(void) {
    if (lbl_806D1650 == 0) {
        lbl_806D1650 = HSD_MemAlloc(lbl_806CFB98 * lbl_806CFB9C);
    }
    Clear();
}
