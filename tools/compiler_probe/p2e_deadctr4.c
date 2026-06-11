/* Phase 2e probe #4: invisible-use hypotheses for the loop-1 dead counter
 * of CarObject_HandleItemEffect (exceptions ON: no pragma, TU flag applies).
 * h3 = counter passed as extra (ignored) arg to the post-loop call: the use
 * is real for liveness but emits ZERO instructions if i coalesces to r4.
 */
extern int tblA[];
extern int IsActive();          /* K&R empty-paren, mirrors auto-TU externs */
typedef struct SelfH { void *owner; int itemId; float blend; } SelfH;
typedef struct OwnerH { char pad[0x40]; void *stateBlock; } OwnerH;

/* h1: direct + call after loop, exceptions on */
int h1_call_excon(SelfH *self, int itemId) {
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
    if (IsActive(((OwnerH *)self->owner)->stateBlock) == 1) {
        return 1;
    }
    return 2;
}

/* h3: counter as ignored 2nd arg of the call (invisible-use-by-coalescing) */
int h3_argi(SelfH *self, int itemId) {
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
    if (IsActive(((OwnerH *)self->owner)->stateBlock, i) == 1) {
        return 1;
    }
    return 2;
}
