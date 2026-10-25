extern int fn_801DD1B0(void *self);

void fn_801E6C10(char *self, int enable) {
    *(int *)(self + 0x9C) = enable;
    if (enable != 0) {
        *(int *)(self + 0x98) = 120;
        *(int *)(self + 0xEC) = fn_801DD1B0(self);
    }
}
