typedef signed char s8;
typedef int s32;
typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK KartItem_CancelAndQueueDefault(s32);
M2C_UNK KartItem_CancelIfNotForced(s32);

void fn_801E9094(void *arg0) {
    if ((s32) M2C_FIELD(arg0, s32 *, 0x20) == 1) {
        KartItem_CancelIfNotForced(M2C_FIELD(arg0, s32 *, 4));
        KartItem_CancelAndQueueDefault(M2C_FIELD(arg0, s32 *, 4));
        M2C_FIELD(arg0, s32 *, 0x20) = 0;
    }
}
