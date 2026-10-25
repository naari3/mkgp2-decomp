/* Per-course voice/param lookup, with per-kart overrides in comm mode. */
typedef struct CourseParamTables {
    short base2[14];
    short base1[14];
    short base0[14];
    short perKart2[4][13];
    short perKart1[4][13];
    short perKart0[4][13];
} CourseParamTables;

extern CourseParamTables lbl_80496C38;
extern int g_gameMode;

short fn_801B0CE4(int course, int kart, short variant) {
    CourseParamTables *t = &lbl_80496C38;
    short *base;
    short *perKart;
    short result = 0x43;

    if (variant == 0) {
        base = t->base0;
        perKart = t->perKart0[0];
    } else if (variant == 1) {
        base = t->base1;
        perKart = t->perKart1[0];
    } else {
        base = t->base2;
        perKart = t->perKart2[0];
    }
    if (course > -1 && course < 13) {
        if (g_gameMode == 2) {
            if (kart >= 0 && kart <= 3) {
                result = perKart[kart * 13 + course];
            } else {
                result = base[course];
            }
        } else {
            result = base[course];
        }
    }
    return result;
}
