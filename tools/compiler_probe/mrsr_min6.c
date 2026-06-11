/* mr-SR-init probe TU #6: inlined-helper wrapper spellings hunting exact
 * register assignment (target: i=r4 mv=r5 off=r6 e=r7; tail f1/f2/f0). */

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

static float CalcMaxA(Mv *mv) {
    int i;
    int off;
    Entry *e;
    float keySpeed;

    keySpeed = F_ZERO;
    for (i = 0, off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

/* helper with chained result local */
static float CalcMaxB(Mv *mv) {
    int i;
    int off;
    Entry *e;
    float keySpeed;

    keySpeed = F_ZERO;
    for (i = 0, off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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
    keySpeed = F_MUL * keySpeed;
    return keySpeed;
}

float x1_exprwrap(Self *self) {
    Mv *mv = self->movement;
    return CalcMaxA(mv) * (F_ONE + mv->coinBonus);
}

float x2_localwrap(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxA(mv);
    return max * (F_ONE + mv->coinBonus);
}

float x3_chain(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxA(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float x4_helperB(Self *self) {
    Mv *mv = self->movement;
    return CalcMaxB(mv) * (F_ONE + mv->coinBonus);
}

float x5_noMvLocal(Self *self) {
    return CalcMaxA(self->movement) * (F_ONE + self->movement->coinBonus);
}
