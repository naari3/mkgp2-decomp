/* Decl-order lever test (mirrors CarObject_Init ch/blk/sub/mgr). Four callee
 * pointer-ish locals, each derived from a distinct source so they are separate
 * webs all live across the sink call. Two functions differ ONLY in declaration
 * order of the four. If `key` (and thus the home reg) tracks declaration order,
 * the two functions' key->slot mapping should INVERT. */
extern int src(void);
extern void use4(int, int, int, int);
extern void keep(int);

/* order: ch, blk, sub, mgr */
int f_abcd(void) {
    int ch  = src();
    int blk = src();
    int sub = src();
    int mgr = src();
    use4(ch, blk, sub, mgr);
    keep(ch); keep(blk); keep(sub); keep(mgr);
    return 0;
}

/* order: mgr, sub, blk, ch (reversed) */
int f_dcba(void) {
    int mgr = src();
    int sub = src();
    int blk = src();
    int ch  = src();
    use4(ch, blk, sub, mgr);
    keep(ch); keep(blk); keep(sub); keep(mgr);
    return 0;
}
