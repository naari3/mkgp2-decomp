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

static float CalcMax_i_off_e_k(Mv *mv) {
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

float x_i_off_e_k(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_off_e_k(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_off_k_e(Mv *mv) {
    int i;
    int off;
    float keySpeed;
    Entry *e;

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

float x_i_off_k_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_off_k_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_e_off_k(Mv *mv) {
    int i;
    Entry *e;
    int off;
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

float x_i_e_off_k(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_e_off_k(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_e_k_off(Mv *mv) {
    int i;
    Entry *e;
    float keySpeed;
    int off;

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

float x_i_e_k_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_e_k_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_k_off_e(Mv *mv) {
    int i;
    float keySpeed;
    int off;
    Entry *e;

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

float x_i_k_off_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_k_off_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_k_e_off(Mv *mv) {
    int i;
    float keySpeed;
    Entry *e;
    int off;

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

float x_i_k_e_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_k_e_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_i_e_k(Mv *mv) {
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
    return F_MUL * keySpeed;
}

float x_off_i_e_k(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_i_e_k(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_i_k_e(Mv *mv) {
    int off;
    int i;
    float keySpeed;
    Entry *e;

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

float x_off_i_k_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_i_k_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_e_i_k(Mv *mv) {
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

float x_off_e_i_k(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_e_i_k(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_e_k_i(Mv *mv) {
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

float x_off_e_k_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_e_k_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_k_i_e(Mv *mv) {
    int off;
    float keySpeed;
    int i;
    Entry *e;

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

float x_off_k_i_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_k_i_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_k_e_i(Mv *mv) {
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

float x_off_k_e_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_k_e_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_i_off_k(Mv *mv) {
    Entry *e;
    int i;
    int off;
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

float x_e_i_off_k(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_i_off_k(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_i_k_off(Mv *mv) {
    Entry *e;
    int i;
    float keySpeed;
    int off;

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

float x_e_i_k_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_i_k_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_off_i_k(Mv *mv) {
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
    return F_MUL * keySpeed;
}

float x_e_off_i_k(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_off_i_k(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_off_k_i(Mv *mv) {
    Entry *e;
    int off;
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

float x_e_off_k_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_off_k_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_k_i_off(Mv *mv) {
    Entry *e;
    float keySpeed;
    int i;
    int off;

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

float x_e_k_i_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_k_i_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_k_off_i(Mv *mv) {
    Entry *e;
    float keySpeed;
    int off;
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

float x_e_k_off_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_k_off_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_k_i_off_e(Mv *mv) {
    float keySpeed;
    int i;
    int off;
    Entry *e;

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

float x_k_i_off_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_k_i_off_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_k_i_e_off(Mv *mv) {
    float keySpeed;
    int i;
    Entry *e;
    int off;

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

float x_k_i_e_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_k_i_e_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_k_off_i_e(Mv *mv) {
    float keySpeed;
    int off;
    int i;
    Entry *e;

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

float x_k_off_i_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_k_off_i_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_k_off_e_i(Mv *mv) {
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

float x_k_off_e_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_k_off_e_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_k_e_i_off(Mv *mv) {
    float keySpeed;
    Entry *e;
    int i;
    int off;

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

float x_k_e_i_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_k_e_i_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_k_e_off_i(Mv *mv) {
    float keySpeed;
    Entry *e;
    int off;
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

float x_k_e_off_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_k_e_off_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
