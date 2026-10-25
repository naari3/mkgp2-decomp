/*
 * clItemBox step table and its static initializer, 0x8005F53C..0x8005F5CC.
 * NonMatching: the target addresses all three tables from one section
 * base (they were file-local in the original TU), but other TUs here
 * still reference lbl_803F9C6C / lbl_803F9CA8 by name, so they stay global
 * and each gets its own lis/addi. The __sinit is renamed to
 * clItemBoxManager_InitStateTable.
 */

struct ItemBoxStepFn {
    int thisDelta;
    int vtblOffset;
    void (*fn)(void *self);
};

extern "C" {
void clItemBox_StepFn_PopOut(void *self);
void clItemBox_StepFn_Bobbing(void *self);
void fn_8005E7E4(void *self);
void fn_8005E794(void *self);

ItemBoxStepFn lbl_803F9C60 = { 0, -1, clItemBox_StepFn_PopOut };
ItemBoxStepFn lbl_803F9C6C[5] = {
    { 0, -1, clItemBox_StepFn_PopOut },
    { 0, -1, clItemBox_StepFn_PopOut },
    { 0, -1, clItemBox_StepFn_Bobbing },
    { 0, -1, fn_8005E7E4 },
    { 0, -1, fn_8005E794 },
};
ItemBoxStepFn lbl_803F9CA8[4] = {
    lbl_803F9C6C[1],
    lbl_803F9C6C[2],
    lbl_803F9C6C[3],
    lbl_803F9C6C[4],
};
}
