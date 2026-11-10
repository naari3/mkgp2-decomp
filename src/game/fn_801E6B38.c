extern void fn_801EC828(void *phys, float v);

void fn_801E6B38(char *self, float v) {
    void *phys = *(void **)(self + 0x20);
    if (phys != 0) {
        fn_801EC828(phys, v);
    }
}
