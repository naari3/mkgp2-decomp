extern int fn_801DD934(int);
extern int fn_801DD90C(int);
extern float fn_801DD8E4(int);
extern float lbl_806DA44C;
void fn_801EC9AC(char *self) {
    float value;
    int id = fn_801DD934(*(int *)(self + 0x10));
    if (id != -1) {
        *(int *)(self + 0x158) = fn_801DD90C(id);
        value = fn_801DD8E4(id);
        *(float *)(self + 0x154) = ((value / lbl_806DA44C) / lbl_806DA44C) / lbl_806DA44C;
    }
}
