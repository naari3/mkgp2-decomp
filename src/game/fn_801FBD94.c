typedef signed char s8;
typedef short s16;
typedef int s32;
typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK fn_801618CC(s32, M2C_UNK, M2C_UNK);

void fn_801FBD94(void *arg0) {
    s16 temp_r3;
    void *temp_r4;
    void *temp_r4_2;

    fn_801618CC(M2C_FIELD(arg0, s32 *, 0x48), 0, 0);
    temp_r4 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_r4, s16 *, 6) = (s16) (M2C_FIELD(temp_r4, s16 *, 6) + 1);
    temp_r3 = M2C_FIELD(temp_r4, s16 *, 4);
    if ((s16) M2C_FIELD(temp_r4, s16 *, 6) >= temp_r3) {
        M2C_FIELD(temp_r4, s16 *, 6) = temp_r3;
    }
    temp_r4_2 = M2C_FIELD(arg0, void **, 0x14);
    if ((s16) M2C_FIELD(temp_r4_2, s16 *, 6) >= (s16) M2C_FIELD(temp_r4_2, s16 *, 4)) {
        M2C_FIELD(arg0, s32 *, 0x24) = 0;
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    }
}
