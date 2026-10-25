extern unsigned char lbl_80495988[];
extern void fn_801826F8(void *jobj, void *src);

static inline void *GetSrc(int mode) {
    switch (mode) {
    case 1:
        return lbl_80495988;
    default:
        return 0;
    }
}

void fn_80182954(void *jobj, int mode) {
    fn_801826F8(jobj, GetSrc(mode));
}
