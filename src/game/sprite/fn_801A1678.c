extern int g_spriteSystemInited;
extern short lbl_80678D2C[];
extern void fn_80120A08(short id);

int fn_801A1678(void) {
    int i;
    if (g_spriteSystemInited == -1) {
        return 0;
    }
    for (i = 0; i < g_spriteSystemInited; i++) {
        fn_80120A08(lbl_80678D2C[i]);
    }
    g_spriteSystemInited = -1;
    return 1;
}
