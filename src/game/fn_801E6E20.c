extern void fn_801EC9AC(void *phys);

void fn_801E6E20(char *self) {
    void *phys = *(void **)(self + 0x20);
    if (phys != 0) {
        fn_801EC9AC(phys);
    }
}
