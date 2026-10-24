extern float fn_801EC754(void *phys);
extern const float lbl_806DA388;

float fn_801E6CFC(char *self) {
    void *phys = *(void **)(self + 0x20);
    if (phys != 0) {
        return fn_801EC754(phys);
    }
    return lbl_806DA388;
}
