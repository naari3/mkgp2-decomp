/* alloc_gpr2.c - Phase 2f follow-ups: decl-vs-def split, volatile clique,
 * partial interference, param priority. Same driver (alloc_run.py). */

extern int src(void);
extern void sink5(int, int, int, int, int);
extern void sink2(int, int);

/* Q0: declaration order a,b,c but DEFINITION (first store) order c,a,b.
 * If homes follow DECL order: a=r31. If DEF order: c=r31. */
int q0_decl_vs_def(void) {
    int a, b, c;
    c = src();
    a = src();
    b = src();
    sink5(a, b, c, 0, 0);
    return 0;
}

/* Q1: no calls inside the clique -> all webs can live in VOLATILE regs.
 * sink takes them but each is defined by a cheap expression. Reveals the
 * volatile-pool direction/order. */
int q1_volatile(int *p) {
    int a = p[0] + 1;
    int b = p[1] + 2;
    int c = p[2] + 3;
    int d = p[3] + 4;
    int e = p[4] + 5;
    sink5(a, b, c, d, e);
    return 0;
}

/* Q2: partial interference (chain, not clique): a used early then dead,
 * so later webs can REUSE a's register. Reveals whether homes are picked
 * by a graph-simplify stack (degree<k removal) vs straight def order. */
int q2_chain(void) {
    int a, b, c, d;
    a = src();
    b = src();          /* a still live (used at sink_ab) */
    sink2(a, b);        /* a dies here */
    c = src();          /* c can reuse a's reg */
    d = src();
    sink2(c, d);
    return 0;
}

/* Q3: param explicitly compared against a call-defined local for r31.
 * p is live across the whole fn; x is defined by one call. */
int q3_param_priority(int *p) {
    int x = src();
    sink5(p[0], x, p[1], x, p[2]);
    return x;
}

/* Q4: 6 webs but only 5 cross a call. Which web is forced volatile? */
int q4_six(void) {
    int a = src();
    int b = src();
    int c = src();
    int d = src();
    int e = src();
    int f = src();
    sink5(a + f, b, c, d, e);
    return f;
}
