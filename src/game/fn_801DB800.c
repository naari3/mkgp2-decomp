typedef struct TableEntry_8049BC30 {
    int f0;
    int f4;
    int f8;
    float fC;
    int f10;
    int f14;
    int f18;
    int f1C;
} TableEntry_8049BC30;

extern TableEntry_8049BC30 lbl_8049BC30[];

int fn_801DB800(void *self, int idx) { return lbl_8049BC30[idx].f1C; }
int fn_801DB818(void *self, int idx) { return lbl_8049BC30[idx].f18; }
int fn_801DB830(void *self, int idx) { return lbl_8049BC30[idx].f14; }
int fn_801DB848(void *self, int idx) { return lbl_8049BC30[idx].f10; }
float fn_801DB860(void *self, int idx) { return lbl_8049BC30[idx].fC; }
int fn_801DB878(void *self, int idx) { return lbl_8049BC30[idx].f8; }
int fn_801DB890(void *self, int idx) { return lbl_8049BC30[idx].f0; }
int fn_801DB8A4(void *self, int idx) { return lbl_8049BC30[idx].f4; }
