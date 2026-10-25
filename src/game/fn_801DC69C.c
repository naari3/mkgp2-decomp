typedef struct Entry_806792D8 {
    char pad0[0x14];
    int f14;
    int f18;
    int f1C;
} Entry_806792D8;

extern Entry_806792D8 lbl_806792D8[];

int fn_801DC69C(int idx) { return lbl_806792D8[idx].f1C; }
void fn_801DC6B4(int idx, int v) { lbl_806792D8[idx].f1C = v; }
int fn_801DC6CC(int idx) { return lbl_806792D8[idx].f18; }
void fn_801DC6E4(int idx, int v) { lbl_806792D8[idx].f18 = v; }
int fn_801DC6FC(int idx) { return lbl_806792D8[idx].f14; }
void fn_801DC714(int idx, int v) { lbl_806792D8[idx].f14 = v; }
Entry_806792D8 *fn_801DC72C(int idx) { return &lbl_806792D8[idx]; }
