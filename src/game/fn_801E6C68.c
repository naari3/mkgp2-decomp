extern void fn_801EC810(void *phys, int v);

void fn_801E6C68(char *self, int v) {
    void *phys = *(void **)(self + 0x20);
    if (phys != 0) {
        fn_801EC810(phys, v);
    }
}
