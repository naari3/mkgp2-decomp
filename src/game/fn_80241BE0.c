typedef struct Obj {
    unsigned char pad_0[0x4];
    int f_4;
} Obj;

extern void HSD_JObjAnim(int);

void fn_80241BE0(void *p0) {
    HSD_JObjAnim(((Obj *)p0)->f_4);
}
