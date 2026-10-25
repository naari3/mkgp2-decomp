void fn_801D9180(char *self, int v) {
    char *p;
    *(int *)(self + 0x14) = v;
    p = *(char **)(self + 0x4C);
    if (p != 0) {
        *(int *)(p + 0x4) = *(int *)(self + 0x14);
    }
}
