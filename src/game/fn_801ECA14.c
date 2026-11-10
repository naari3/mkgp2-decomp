/* fn_801ECA14: renew the enemy-run path line from the current position and
 * dump it. The original TU owned the .rodata block 0x803BD920..0x803BDED4
 * (float tables, class names and these format strings); the format strings
 * are addressed off its pooled section base, so the block is defined here
 * in target order. */
extern const float lbl_806DA468;
extern int fn_801DB99C(void *, float, float, float, float);
extern void fn_801DBA60(void *, int);
extern int fn_801DBA34(void *);
extern char *fn_801DB9C4(void *, int);
extern void DebugPrintf(const char *, ...);

/* element type read off the values (all floats), not from code */
const float lbl_803BD920[258] = {
    1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f,
    0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f,
    83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f,
    83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 9.6f,
    9.6f, 12.0f
};
const unsigned int lbl_803BDD28[12] = {
    0x40E66667, 0x00000000, 0x4119999A, 0xC0E66667, 0x00000000, 0x4119999A,
    0x40E66667, 0x00000000, 0xC119999A, 0xC0E66667, 0x00000000, 0xC119999A,
};
/* element type read off the values (all small integers), not from code */
const int EnemyRun_BaseInit_rodata_803BDD58[51] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0
};
const unsigned int lbl_803BDE24[9] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000,
};
const char lbl_803BDE48[0x10] = "clEnemyRunType2";
const char lbl_803BDE58[0x14] = "clEnemyRunInterface";
const char lbl_803BDE6C[0x28] = "*************************************\n";
const char lbl_803BDE94[0x14] = "renewal line %d\n";
const char lbl_803BDEA8[0xC] = "%f %f %f\n";
const char lbl_803BDEB4[0x10] = "%d %f %f %f\n";
const char lbl_803BDEC4[0x10] = "clEnemyRunType1";

void fn_801ECA14(char *self) {
    void *path = *(void **)(self + 4);
    char *point;
    fn_801DBA60(path, fn_801DB99C(path, *(float *)(self + 0x4C), *(float *)(self + 0x50), *(float *)(self + 0x54), lbl_806DA468) + 2);
    DebugPrintf(lbl_803BDE6C);
    DebugPrintf(lbl_803BDE94, fn_801DBA34(*(void **)(self + 4)));
    DebugPrintf(lbl_803BDEA8, *(float *)(self + 0x4C), *(float *)(self + 0x50), *(float *)(self + 0x54));
    path = *(void **)(self + 4);
    point = fn_801DB9C4(path, fn_801DBA34(path));
    DebugPrintf(lbl_803BDEB4, fn_801DBA34(*(void **)(self + 4)), *(float *)(point + 4), *(float *)(point + 8), *(float *)(point + 12));
}
