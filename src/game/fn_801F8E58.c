typedef int s32;
typedef unsigned int u32;
typedef s32 M2C_UNK;

u32 Alloc(M2C_UNK);
extern u32 lbl_806D1978;

u32 fn_801F8E58(void) {
    if ((u32) lbl_806D1978 == 0U) {
        lbl_806D1978 = Alloc(1);
    }
    return lbl_806D1978;
}
