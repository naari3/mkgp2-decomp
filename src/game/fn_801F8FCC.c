typedef signed char s8;
typedef int s32;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void fn_801F8FCC(void *arg0, s32 arg1) {
    if ((arg1 < 1) || (arg1 > 2)) {
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x1C) = arg1;
}

void fn_801F8FF0(void *arg0, s32 arg1) {
    if ((arg1 != 0) && (arg1 != 1)) {
        M2C_FIELD(arg0, s32 *, 0x228) = 0;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x228) = arg1;
}
