/* alloc_gpr.c - Phase 2f register-coloring-order probes.
 *
 * Each probe builds a CLIQUE of long-range int webs (each defined by a
 * separate call to src(), all simultaneously live at one sink() call), so the
 * interference graph is complete => every web must get a DISTINCT register.
 * The sink() call passes them in a fixed argument order; the emitted
 * `mr r3,<home(a)> ; mr r4,<home(b)> ...` reveals each web's physical home.
 * By permuting (decl order, definition/first-use order, sink argument order,
 * use count) across probes we read off the colorer's web visit/priority order.
 *
 * Driver: alloc_run.py classifies each fn by reading the mr-to-arg mapping.
 */

extern int src(void);
extern void sink5(int, int, int, int, int);
extern void sink2(int, int);

/* P0: decl order = def order = arg order (a,b,c,d,e). Baseline. */
int p0_baseline(void) {
    int a = src();
    int b = src();
    int c = src();
    int d = src();
    int e = src();
    sink5(a, b, c, d, e);
    return 0;
}

/* P1: def order a..e, but sink argument order reversed (e,d,c,b,a).
 * Isolates: does home follow def order or use(arg) order? */
int p1_argrev(void) {
    int a = src();
    int b = src();
    int c = src();
    int d = src();
    int e = src();
    sink5(e, d, c, b, a);
    return 0;
}

/* P2: def order reversed relative to a..e naming; arg order a..e.
 * (e defined first, a defined last.) Isolates def order vs decl order. */
int p2_defrev(void) {
    int e = src();
    int d = src();
    int c = src();
    int b = src();
    int a = src();
    sink5(a, b, c, d, e);
    return 0;
}

/* P3: extra uses on 'c' (used many times after the clique) to raise its
 * use-count / lower its spill priority. Tests degree/priority weighting. */
int p3_usecount(int *q) {
    int a = src();
    int b = src();
    int c = src();
    int d = src();
    int e = src();
    sink5(a, b, c, d, e);
    q[0] = c; q[1] = c; q[2] = c; q[3] = c; q[4] = c;
    return 0;
}

/* P4: only 2 webs in the clique. Minimal: which of the two gets the
 * higher/lower reg, by def order. */
int p4_two(void) {
    int a = src();
    int b = src();
    sink2(a, b);
    return 0;
}

/* P5: 2 webs, arg order swapped (b,a). */
int p5_two_swap(void) {
    int a = src();
    int b = src();
    sink2(b, a);
    return 0;
}
