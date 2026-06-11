/* Phase 2e probe #2: dead-counter survival levers beyond naive splice.
 * Axes: exceptions pragma parity, pre-opt helper size (late-splice threshold
 * hypothesis), call-site-constant trip count, call inside helper, volatile
 * counter (not in the original 8-probe ledger).
 */
extern int tblA[];
extern int ExternalCall(int);

#pragma exceptions off

/* e1: direct + volatile counter (ledger gap) */
int e1_volctr(int itemId) {
    unsigned char found;
    volatile int i;
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

/* e2: direct + register volatile counter */
int e2_regvolctr(int itemId) {
    unsigned char found;
    register volatile int i;
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

/* e3: helper, dead counter, exceptions-off parity (d2 rerun under pragma) */
static inline unsigned char scan_e3(int itemId) {
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
int e3_inl_dead(int itemId) {
    unsigned char found = scan_e3(itemId);
    if (found == 0) { return 0; }
    return 2;
}

/* e4: helper with non-constant trip count (constant only at call site) */
static inline unsigned char scan_e4(int itemId, int count) {
    unsigned char found;
    int i;
    const int *p;
    found = 0;
    p = (const int *)tblA;
    for (i = 0; i < count; i++) {
        if (itemId == *p) { found = 1; break; }
        if (itemId == *++p) { found = 1; break; }
        ++p;
    }
    return found;
}
int e4_inl_count(int itemId) {
    unsigned char found = scan_e4(itemId, 0x13);
    if (found == 0) { return 0; }
    return 2;
}

/* e5: big-pre-opt helper - junk that the callee's own optimizer removes;
 * if the inline decision is taken on pre-opt size, this may defer the
 * splice past DCE. */
static inline unsigned char scan_e5(int itemId) {
    unsigned char found;
    int i;
    const int *p;
    int n;
    int j0, j1, j2, j3, j4, j5, j6, j7;
    found = 0;
    i = 0;
    j0 = itemId * 3; j1 = j0 + 5; j2 = j1 * 7; j3 = j2 - j0;
    j4 = j3 * 11; j5 = j4 + j2; j6 = j5 * 13; j7 = j6 - j4;
    j0 = j7 * 3; j1 = j0 + 5; j2 = j1 * 7; j3 = j2 - j0;
    j4 = j3 * 11; j5 = j4 + j2; j6 = j5 * 13; j7 = j6 - j4;
    j0 = j7 * 3; j1 = j0 + 5; j2 = j1 * 7; j3 = j2 - j0;
    j4 = j3 * 11; j5 = j4 + j2; j6 = j5 * 13; j7 = j6 - j4;
    j0 = j7 * 3; j1 = j0 + 5; j2 = j1 * 7; j3 = j2 - j0;
    j4 = j3 * 11; j5 = j4 + j2; j6 = j5 * 13; j7 = j6 - j4;
    p = (const int *)tblA;
    for (n = 0; n < 0x13; n++) {
        if (itemId == *p) { found = 1; break; }
        if (itemId == *++p) { found = 1; break; }
        ++p;
        ++i;
    }
    return found;
}
int e5_inl_bigpreopt(int itemId) {
    unsigned char found = scan_e5(itemId);
    if (found == 0) { return 0; }
    return 2;
}

/* e6: helper containing a call after the loop (non-leaf callee) */
static inline unsigned char scan_e6(int itemId) {
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
    if (found != 0 && ExternalCall(itemId) == 1) {
        return 1;
    }
    return found;
}
int e6_inl_call(int itemId) {
    unsigned char found = scan_e6(itemId);
    if (found == 0) { return 0; }
    return 2;
}

#pragma exceptions reset
