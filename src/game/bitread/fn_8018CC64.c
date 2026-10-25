extern unsigned char lbl_80677EE8[];
extern unsigned char lbl_80677F04[];
extern unsigned char lbl_806D1698;
static inline void Fill(unsigned char *p, unsigned char v, int n) {
    int i;
    for (i = 0; i < n; i++) {
        p[i] = v;
    }
}
void fn_8018CC64(void) {
    lbl_806D1698 = 0;
    Fill(lbl_80677EE8, 0, 25);
    Fill(lbl_80677F04, 0, 0x1a);
}
