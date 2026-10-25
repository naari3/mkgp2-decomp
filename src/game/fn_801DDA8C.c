typedef struct Entry_804E21C4 {
    char pad0[0x14];
    int f14;
    int f18;
    float f1C;
} Entry_804E21C4;

extern Entry_804E21C4 lbl_804E21C4[];
extern const float FLOAT_defaultBonus;

float fn_801DDA8C(int idx) {
    if (idx < 0) {
        return FLOAT_defaultBonus;
    }
    return lbl_804E21C4[idx].f1C;
}

int fn_801DDAB4(int idx) {
    if (idx < 0) {
        return 0;
    }
    return lbl_804E21C4[idx].f18;
}

int fn_801DDADC(int idx) {
    if (idx < 0) {
        return -1;
    }
    return lbl_804E21C4[idx].f14;
}
