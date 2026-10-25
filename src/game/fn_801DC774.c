typedef struct PathSlot {
    float v[4];
    int unk10;
    int ids[3];
} PathSlot;

extern int g_tableVariant;
extern PathSlot lbl_806792D8[8];
extern const float lbl_806DA298;

void fn_801DC774(void) {
}

void fn_801DC778(void) {
    int i;

    for (i = 0; i < 8; i++) {
        lbl_806792D8[i].v[0] = lbl_806DA298;
        lbl_806792D8[i].v[1] = lbl_806DA298;
        lbl_806792D8[i].v[2] = lbl_806DA298;
        lbl_806792D8[i].v[3] = lbl_806DA298;
        lbl_806792D8[i].ids[0] = -1;
        lbl_806792D8[i].ids[1] = -1;
        lbl_806792D8[i].ids[2] = -1;
    }
}

int fn_801DC868(void) {
    return g_tableVariant;
}

void fn_801DC870(int variant) {
    g_tableVariant = variant;
    if (variant == 2) {
        g_tableVariant = 0;
    }
}
