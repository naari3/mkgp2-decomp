extern unsigned char lbl_80677F20[0x1a];
extern unsigned char lbl_806D1699;

static inline void Clear(unsigned char *p, int n) {
    int i;
    for (i = 0; i < n; i++) {
        p[i] = 0;
    }
}

void fn_8018B248(void) {
    Clear(lbl_80677F20, 0x1a);
    lbl_806D1699 = 0;
}
