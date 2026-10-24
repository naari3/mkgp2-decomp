extern void fn_801EC820(void *phys);

void fn_801E6B0C(char *self) {
    void *phys = *(void **)(self + 0x20);
    if (phys != 0) {
        fn_801EC820(phys);
    }
}
