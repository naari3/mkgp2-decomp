typedef struct Entry_804E3C5C {
    char pad0[0xC];
    int fC;
    int f10;
} Entry_804E3C5C;

extern Entry_804E3C5C lbl_804E3C5C[];

int fn_801DC9AC(int idx) {
    if (idx < 0) {
        return 0;
    }
    return lbl_804E3C5C[idx].f10;
}

int fn_801DC9D4(int idx) {
    if (idx < 0) {
        return -1;
    }
    return lbl_804E3C5C[idx].fC;
}
