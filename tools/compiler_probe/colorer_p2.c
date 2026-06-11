/* Single-fn colorer probe: decl order reversed (e first, a last).
 * If `key` field tracks declaration/web-birth order, then e gets the highest
 * key and should be colored r31; a (last decl) lowest of the clique.
 * Expected homes (alloc_run.py p2_defrev): e=r31 d=r30 c=r29 b=r28 a=volatile. */
extern int src(void);
extern void sink5(int, int, int, int, int);

int p2_defrev(void) {
    int e = src();
    int d = src();
    int c = src();
    int b = src();
    int a = src();
    sink5(a, b, c, d, e);
    return 0;
}
