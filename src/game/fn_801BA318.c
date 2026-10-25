extern void fn_801A0004(void *sprite);
extern void fn_8016039C(void *obj);

void fn_801BA318(char *self) {
    if (*(void **)(self + 0x14) != 0) {
        fn_801A0004(*(void **)(self + 0x14));
    }
    if (*(float *)(self + 0xC) < 6.0f && *(void **)(self + 0x18) != 0) {
        fn_801A0004(*(void **)(self + 0x18));
    }
    if (*(void **)(self + 0x1C) != 0) {
        fn_8016039C(*(void **)(self + 0x1C));
    }
}
