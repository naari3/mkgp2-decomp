typedef signed char s8;
typedef float f32;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void fn_801F93C8(void *arg0, f32 farg0) {
    M2C_FIELD(arg0, f32 *, 0x14) = farg0;
}

void fn_801F93D0(void *arg0, f32 farg0, f32 farg1) {
    M2C_FIELD(arg0, f32 *, 0xC) = farg0;
    M2C_FIELD(arg0, f32 *, 0x10) = farg1;
}

void fn_801F93DC(void *arg0, f32 farg0, f32 farg1, f32 farg2) {
    M2C_FIELD(arg0, f32 *, 0) = farg0;
    M2C_FIELD(arg0, f32 *, 4) = farg1;
    M2C_FIELD(arg0, f32 *, 0x224) = farg2;
}

void fn_801F93EC(void *arg0, f32 farg0, f32 farg1) {
    M2C_FIELD(arg0, f32 *, 0) = farg0;
    M2C_FIELD(arg0, f32 *, 4) = farg1;
}
