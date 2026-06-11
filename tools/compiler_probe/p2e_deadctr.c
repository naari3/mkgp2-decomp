/* Phase 2e probe: dead-counter-in-ctr-loop (CarObject_HandleItemEffect loop 1).
 * Target shape (0x8004F878..):
 *   li r3,0x0   (found)
 *   li r4,0x0   (dead counter i)
 *   mtctr r0    (0x13)
 * L: lwz r0,0(r5); cmpw; bne; li r3,1; b out
 *    lwzu r0,4(r5); cmpw; bne; li r3,1; b out
 *    addi r5,r5,0x4
 *    addi r4,r4,0x1   <- never read (DEAD)
 *    bdnz L
 * Hypothesis: the counter survives only when the loop is spliced by the
 * inliner from a static inline helper (same mechanism as the phase-2c
 * mr-SR-init); direct forms are all DCEd (8 negatives in
 * docs/notes/cw132-dead-counter-ctr-loop-hardblock.md).
 */
extern int tblA[];

/* d1: direct form, dead body counter (known-negative baseline) */
int d1_direct(int itemId) {
    unsigned char found;
    int i;
    const int *p;
    int n;
    found = 0;
    i = 0;
    p = (const int *)tblA;
    for (n = 0; n < 0x13; n++) {
        if (itemId == *p) { found = 1; break; }
        if (itemId == *++p) { found = 1; break; }
        ++p;
        ++i;
    }
    if (found == 0) { return 0; }
    return 2;
}

/* d2: same loop inside a static inline helper, counter dead IN the callee */
static inline unsigned char scan2(int itemId) {
    unsigned char found;
    int i;
    const int *p;
    int n;
    found = 0;
    i = 0;
    p = (const int *)tblA;
    for (n = 0; n < 0x13; n++) {
        if (itemId == *p) { found = 1; break; }
        if (itemId == *++p) { found = 1; break; }
        ++p;
        ++i;
    }
    return found;
}
int d2_inl_dead(int itemId) {
    unsigned char found = scan2(itemId);
    if (found == 0) { return 0; }
    return 2;
}

/* d3: helper where i IS the loop control (ctr conversion must replace it) */
static inline unsigned char scan3(int itemId) {
    unsigned char found;
    int i;
    const int *p;
    found = 0;
    p = (const int *)tblA;
    for (i = 0; i < 0x13; i++) {
        if (itemId == *p) { found = 1; break; }
        if (itemId == *++p) { found = 1; break; }
        ++p;
    }
    return found;
}
int d3_inl_loopctl(int itemId) {
    unsigned char found = scan3(itemId);
    if (found == 0) { return 0; }
    return 2;
}

/* d4: helper returns the counter; call site ignores the return value
 * (counter live-in-callee, dead-at-splice) */
static inline int scan4(int itemId, unsigned char *foundp) {
    unsigned char found;
    int i;
    const int *p;
    int n;
    found = 0;
    i = 0;
    p = (const int *)tblA;
    for (n = 0; n < 0x13; n++) {
        if (itemId == *p) { found = 1; break; }
        if (itemId == *++p) { found = 1; break; }
        ++p;
        ++i;
    }
    *foundp = found;
    return i;
}
int d4_inl_retidx(int itemId) {
    unsigned char found;
    scan4(itemId, &found);
    if (found == 0) { return 0; }
    return 2;
}
