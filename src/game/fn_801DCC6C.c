typedef struct Entry_804E3644 {
    char pad0[0x8];
    float f8;
    int fC;
    float f10;
} Entry_804E3644;

extern Entry_804E3644 lbl_804E3644[];
extern const float FLOAT_defaultBonus;

float fn_801DCC6C(int idx) {
    if (idx < 0) {
        return FLOAT_defaultBonus;
    }
    return lbl_804E3644[idx].f10;
}

int fn_801DCC94(int idx) {
    if (idx < 0) {
        return 0;
    }
    return lbl_804E3644[idx].fC;
}

float fn_801DCCBC(int idx) {
    if (idx < 0) {
        return FLOAT_defaultBonus;
    }
    return lbl_804E3644[idx].f8;
}
