typedef struct Obj {
    unsigned char pad_0[0xC];
    int f_C;
} Obj;

extern void PathCursor_SetIndex(int);

void fn_801DBA60(void *p0) {
    PathCursor_SetIndex(((Obj *)p0)->f_C);
}
