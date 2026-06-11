/* Two-regime probe (HandleItemEffect shape). A fn-scope web `obj` is live across
 * the whole body; an inline helper splices its own locals into the body. Observe
 * whether the spliced helper locals get HIGHER keys (born first -> colored first
 * -> high regs) than the fn-scope `obj`, i.e. whether inline splicing reorders
 * web birth such that `obj` lands at a low key (colored last). */
extern int src(void);
extern void use2(int, int);
extern void sink3(int, int, int);

static int site(int seed) {
    int x = src();
    int y = src();
    use2(x, y);
    return x + y + seed;
}

int regime_B(void) {
    int obj = src();            /* fn-scope web, defined FIRST */
    int handled = site(obj);    /* spliced inline -> site webs born during opt */
    sink3(obj, handled, src());
    return obj + handled;
}
