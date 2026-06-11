/* Phase 2e probe #3: does a KNOWN late-splice helper (the phase-2c
 * CalcMaxSpeed body, whose `off = i` copy survives as mr) also preserve a
 * dead up-counter web added to its loop? Distinguishes:
 *   - FE-only DCE (callee dead webs die pre-splice, spliced-dead webs live)
 *   - global DCE (all dead webs die regardless of splice timing)
 */

#pragma exceptions off

typedef struct Pair { float key; float value; } Pair;
typedef struct Entry { Pair *pairs; int count; float refSpeed; char pad[0xc]; } Entry;
typedef struct Mv {
    char pad0[0x8]; int tableIdx; char padC[0x16];
    unsigned char capFlag; char pad23[0x1];
    Entry *table; char pad28[0x2e0 - 0x28]; float coinBonus;
} Mv;
typedef struct Self { char pad0[0x28]; Mv *movement; } Self;

extern const float F_ZERO, F_ONE, F_CAP, F_MUL;

/* g1: CalcMaxSpeed body + dead counter j in the loop (dead IN the callee) */
static float CalcMaxJ(Mv *mv) {
    int i;
    int off;
    int j;
    Entry *e;
    float keySpeed;

    keySpeed = F_ZERO;
    j = 0;
    for (i = 0, off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        ++j;
        if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < F_ONE) {
            keySpeed = mv->table[mv->tableIdx].pairs[i].value;
            break;
        }
    }
    if (mv->capFlag == 1) {
        if (keySpeed >= F_CAP) {
            keySpeed = F_CAP;
        }
    }
    return F_MUL * keySpeed;
}

float g1_wrapper(Self *self) {
    Mv *mv = self->movement;
    return CalcMaxJ(mv) * (F_ONE + mv->coinBonus);
}

/* g2: counter LIVE in callee (returned via out-param-free trick: multiply
 * into result in a way the callee cannot fold), dead-ish at site */
static float CalcMaxK(Mv *mv, int *jout) {
    int i;
    int off;
    int j;
    Entry *e;
    float keySpeed;

    keySpeed = F_ZERO;
    j = 0;
    for (i = 0, off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        ++j;
        if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < F_ONE) {
            keySpeed = mv->table[mv->tableIdx].pairs[i].value;
            break;
        }
    }
    *jout = j;
    if (mv->capFlag == 1) {
        if (keySpeed >= F_CAP) {
            keySpeed = F_CAP;
        }
    }
    return F_MUL * keySpeed;
}

float g2_wrapper(Self *self) {
    Mv *mv = self->movement;
    int jdead;
    return CalcMaxK(mv, &jdead) * (F_ONE + mv->coinBonus);
}
