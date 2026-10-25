typedef int s32;
typedef s32 M2C_UNK;
#define NULL 0

extern M2C_UNK *lbl_806D1980;
extern M2C_UNK lbl_806D19A0;

M2C_UNK *fn_801F98CC(void) {
    if ((M2C_UNK *) lbl_806D1980 == NULL) {
        lbl_806D1980 = &lbl_806D19A0;
    }
    return lbl_806D1980;
}
