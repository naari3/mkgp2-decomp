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

static float CalcMax_oeik(Mv *mv) {
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
    return F_MUL * keySpeed;
}
float xoeik_wA(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_oeik(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
float xoeik_wB(Self *self) {
    Mv *mv = self->movement;
    return CalcMax_oeik(mv) * (F_ONE + mv->coinBonus);
}
float xoeik_wC(Self *self) {
    Mv *mv = self->movement;
    float max;
    max = CalcMax_oeik(mv) * (F_ONE + mv->coinBonus);
    return max;
}
float xoeik_wD(Self *self) {
    Mv *mv;
    float max;
    mv = self->movement;
    max = CalcMax_oeik(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_koei(Mv *mv) {
    float keySpeed;
    int off;
    Entry *e;
    int i;

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
float xkoei_wA(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_koei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
float xkoei_wB(Self *self) {
    Mv *mv = self->movement;
    return CalcMax_koei(mv) * (F_ONE + mv->coinBonus);
}
float xkoei_wC(Self *self) {
    Mv *mv = self->movement;
    float max;
    max = CalcMax_koei(mv) * (F_ONE + mv->coinBonus);
    return max;
}
float xkoei_wD(Self *self) {
    Mv *mv;
    float max;
    mv = self->movement;
    max = CalcMax_koei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_okei(Mv *mv) {
    int off;
    float keySpeed;
    Entry *e;
    int i;

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
float xokei_wA(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_okei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
float xokei_wB(Self *self) {
    Mv *mv = self->movement;
    return CalcMax_okei(mv) * (F_ONE + mv->coinBonus);
}
float xokei_wC(Self *self) {
    Mv *mv = self->movement;
    float max;
    max = CalcMax_okei(mv) * (F_ONE + mv->coinBonus);
    return max;
}
float xokei_wD(Self *self) {
    Mv *mv;
    float max;
    mv = self->movement;
    max = CalcMax_okei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_oeki(Mv *mv) {
    int off;
    Entry *e;
    float keySpeed;
    int i;

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
float xoeki_wA(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_oeki(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
float xoeki_wB(Self *self) {
    Mv *mv = self->movement;
    return CalcMax_oeki(mv) * (F_ONE + mv->coinBonus);
}
float xoeki_wC(Self *self) {
    Mv *mv = self->movement;
    float max;
    max = CalcMax_oeki(mv) * (F_ONE + mv->coinBonus);
    return max;
}
float xoeki_wD(Self *self) {
    Mv *mv;
    float max;
    mv = self->movement;
    max = CalcMax_oeki(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
