extern float fn_801EC74C(void *phys);
extern const float lbl_806DA388;

float fn_801E6CC8(char *self) {
    void *phys = *(void **)(self + 0x20);
    if (phys != 0) {
        return fn_801EC74C(phys);
    }
    return lbl_806DA388;
}
