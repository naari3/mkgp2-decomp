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

static float CK_doei(Mv *mv) {
    int off;
    Entry *e;
    int i;
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
    return keySpeed;
}
float qdoei_a(Self *self) {
    Mv *mv = self->movement;
    float max = F_MUL * CK_doei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
float qdoei_b(Self *self) {
    Mv *mv = self->movement;
    return F_MUL * CK_doei(mv) * (F_ONE + mv->coinBonus);
}
float qdoei_c(Self *self) {
    Mv *mv = self->movement;
    float max = CK_doei(mv);
    max = F_MUL * max;
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CK_dioe(Mv *mv) {
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
    return keySpeed;
}
float qdioe_a(Self *self) {
    Mv *mv = self->movement;
    float max = F_MUL * CK_dioe(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
float qdioe_b(Self *self) {
    Mv *mv = self->movement;
    return F_MUL * CK_dioe(mv) * (F_ONE + mv->coinBonus);
}
float qdioe_c(Self *self) {
    Mv *mv = self->movement;
    float max = CK_dioe(mv);
    max = F_MUL * max;
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CK_doie(Mv *mv) {
    int off;
    int i;
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
    return keySpeed;
}
float qdoie_a(Self *self) {
    Mv *mv = self->movement;
    float max = F_MUL * CK_doie(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
float qdoie_b(Self *self) {
    Mv *mv = self->movement;
    return F_MUL * CK_doie(mv) * (F_ONE + mv->coinBonus);
}
float qdoie_c(Self *self) {
    Mv *mv = self->movement;
    float max = CK_doie(mv);
    max = F_MUL * max;
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CK_deoi(Mv *mv) {
    Entry *e;
    int off;
    int i;
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
    return keySpeed;
}
float qdeoi_a(Self *self) {
    Mv *mv = self->movement;
    float max = F_MUL * CK_deoi(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
float qdeoi_b(Self *self) {
    Mv *mv = self->movement;
    return F_MUL * CK_deoi(mv) * (F_ONE + mv->coinBonus);
}
float qdeoi_c(Self *self) {
    Mv *mv = self->movement;
    float max = CK_deoi(mv);
    max = F_MUL * max;
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
