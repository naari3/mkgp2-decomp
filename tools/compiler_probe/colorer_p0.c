/* Single-fn colorer probe: 5-web callee-saved clique, decl order a..e.
 * Expected homes (alloc_run.py): a=r31 b=r30 c=r29 d=r28 e=volatile. */
extern int src(void);
extern void sink5(int, int, int, int, int);

int p0_baseline(void) {
    int a = src();
    int b = src();
    int c = src();
    int d = src();
    int e = src();
    sink5(a, b, c, d, e);
    return 0;
}
