extern int fn_801EC77C(void *phys);

int fn_801E6DDC(char *self) {
    void *phys = *(void **)(self + 0x20);
    if (phys != 0) {
        return fn_801EC77C(phys);
    }
    return 0;
}
