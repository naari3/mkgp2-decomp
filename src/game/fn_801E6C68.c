extern void fn_801EC810(void *phys);

void fn_801E6C68(char *self) {
    void *phys = *(void **)(self + 0x20);
    if (phys != 0) {
        fn_801EC810(phys);
    }
}
