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

static float CalcMax_off_mv_i_e(Mv *arg) {
    int off;
    Mv *mv;
    int i;
    Entry *e;
    float keySpeed;

    mv = arg;
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

float x_off_mv_i_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_mv_i_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_mv_e_i(Mv *arg) {
    int off;
    Mv *mv;
    Entry *e;
    int i;
    float keySpeed;

    mv = arg;
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

float x_off_mv_e_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_mv_e_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_i_mv_e(Mv *arg) {
    int off;
    int i;
    Mv *mv;
    Entry *e;
    float keySpeed;

    mv = arg;
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

float x_off_i_mv_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_i_mv_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_i_e_mv(Mv *arg) {
    int off;
    int i;
    Entry *e;
    Mv *mv;
    float keySpeed;

    mv = arg;
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

float x_off_i_e_mv(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_i_e_mv(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_e_mv_i(Mv *arg) {
    int off;
    Entry *e;
    Mv *mv;
    int i;
    float keySpeed;

    mv = arg;
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

float x_off_e_mv_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_e_mv_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_off_e_i_mv(Mv *arg) {
    int off;
    Entry *e;
    int i;
    Mv *mv;
    float keySpeed;

    mv = arg;
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

float x_off_e_i_mv(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_off_e_i_mv(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_mv_off_i_e(Mv *arg) {
    Mv *mv;
    int off;
    int i;
    Entry *e;
    float keySpeed;

    mv = arg;
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

float x_mv_off_i_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_mv_off_i_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_mv_off_e_i(Mv *arg) {
    Mv *mv;
    int off;
    Entry *e;
    int i;
    float keySpeed;

    mv = arg;
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

float x_mv_off_e_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_mv_off_e_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_mv_i_off_e(Mv *arg) {
    Mv *mv;
    int i;
    int off;
    Entry *e;
    float keySpeed;

    mv = arg;
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

float x_mv_i_off_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_mv_i_off_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_mv_i_e_off(Mv *arg) {
    Mv *mv;
    int i;
    Entry *e;
    int off;
    float keySpeed;

    mv = arg;
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

float x_mv_i_e_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_mv_i_e_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_mv_e_off_i(Mv *arg) {
    Mv *mv;
    Entry *e;
    int off;
    int i;
    float keySpeed;

    mv = arg;
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

float x_mv_e_off_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_mv_e_off_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_mv_e_i_off(Mv *arg) {
    Mv *mv;
    Entry *e;
    int i;
    int off;
    float keySpeed;

    mv = arg;
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

float x_mv_e_i_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_mv_e_i_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_off_mv_e(Mv *arg) {
    int i;
    int off;
    Mv *mv;
    Entry *e;
    float keySpeed;

    mv = arg;
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

float x_i_off_mv_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_off_mv_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_off_e_mv(Mv *arg) {
    int i;
    int off;
    Entry *e;
    Mv *mv;
    float keySpeed;

    mv = arg;
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

float x_i_off_e_mv(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_off_e_mv(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_mv_off_e(Mv *arg) {
    int i;
    Mv *mv;
    int off;
    Entry *e;
    float keySpeed;

    mv = arg;
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

float x_i_mv_off_e(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_mv_off_e(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_mv_e_off(Mv *arg) {
    int i;
    Mv *mv;
    Entry *e;
    int off;
    float keySpeed;

    mv = arg;
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

float x_i_mv_e_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_mv_e_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_e_off_mv(Mv *arg) {
    int i;
    Entry *e;
    int off;
    Mv *mv;
    float keySpeed;

    mv = arg;
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

float x_i_e_off_mv(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_e_off_mv(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_i_e_mv_off(Mv *arg) {
    int i;
    Entry *e;
    Mv *mv;
    int off;
    float keySpeed;

    mv = arg;
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

float x_i_e_mv_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_i_e_mv_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_off_mv_i(Mv *arg) {
    Entry *e;
    int off;
    Mv *mv;
    int i;
    float keySpeed;

    mv = arg;
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

float x_e_off_mv_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_off_mv_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_off_i_mv(Mv *arg) {
    Entry *e;
    int off;
    int i;
    Mv *mv;
    float keySpeed;

    mv = arg;
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

float x_e_off_i_mv(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_off_i_mv(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_mv_off_i(Mv *arg) {
    Entry *e;
    Mv *mv;
    int off;
    int i;
    float keySpeed;

    mv = arg;
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

float x_e_mv_off_i(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_mv_off_i(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_mv_i_off(Mv *arg) {
    Entry *e;
    Mv *mv;
    int i;
    int off;
    float keySpeed;

    mv = arg;
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

float x_e_mv_i_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_mv_i_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_i_off_mv(Mv *arg) {
    Entry *e;
    int i;
    int off;
    Mv *mv;
    float keySpeed;

    mv = arg;
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

float x_e_i_off_mv(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_i_off_mv(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CalcMax_e_i_mv_off(Mv *arg) {
    Entry *e;
    int i;
    Mv *mv;
    int off;
    float keySpeed;

    mv = arg;
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

float x_e_i_mv_off(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMax_e_i_mv_off(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
