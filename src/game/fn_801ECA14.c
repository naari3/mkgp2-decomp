/* Native candidate: 73.12069% text. The shared data-pool base is
 * rematerialized at each printf instead of remaining in r30. */
extern const float lbl_806DA468;
extern char lbl_803BD920[];
extern int fn_801DB99C(void *, float, float, float, float);
extern void fn_801DBA60(void *, int);
extern int fn_801DBA34(void *);
extern char *fn_801DB9C4(void *, int);
extern void DebugPrintf(const char *, ...);
void fn_801ECA14(char *self) {
    void *path = *(void **)(self + 4);
    register char *strings = lbl_803BD920;
    char *point;
    fn_801DBA60(path, fn_801DB99C(path, *(float *)(self + 0x4C), *(float *)(self + 0x50), *(float *)(self + 0x54), lbl_806DA468) + 2);
    DebugPrintf(strings + 0x54C);
    DebugPrintf(strings + 0x574, fn_801DBA34(*(void **)(self + 4)));
    DebugPrintf(strings + 0x588, *(float *)(self + 0x4C), *(float *)(self + 0x50), *(float *)(self + 0x54));
    path = *(void **)(self + 4);
    point = fn_801DB9C4(path, fn_801DBA34(path));
    DebugPrintf(strings + 0x594, fn_801DBA34(*(void **)(self + 4)), *(float *)(point + 4), *(float *)(point + 8), *(float *)(point + 12));
}
