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

static float CM_z1doei(Mv *mv) {
    int off;
    Entry *e;
    int i;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (i = 0, off = 0; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz1doei(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z1doei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z1dioe(Mv *mv) {
    int i;
    int off;
    Entry *e;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (i = 0, off = 0; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz1dioe(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z1dioe(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z1dieo(Mv *mv) {
    int i;
    Entry *e;
    int off;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (i = 0, off = 0; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz1dieo(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z1dieo(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z1deio(Mv *mv) {
    Entry *e;
    int i;
    int off;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (i = 0, off = 0; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz1deio(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z1deio(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z2doei(Mv *mv) {
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

float zz2doei(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z2doei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z2dioe(Mv *mv) {
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

float zz2dioe(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z2dioe(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z2dieo(Mv *mv) {
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

float zz2dieo(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z2dieo(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z2deio(Mv *mv) {
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

float zz2deio(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z2deio(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z3doei(Mv *mv) {
    int off;
    Entry *e;
    int i;
    float keySpeed;

    keySpeed = F_ZERO;
    i = 0;
    off = i;
    for (; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz3doei(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z3doei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z3dioe(Mv *mv) {
    int i;
    int off;
    Entry *e;
    float keySpeed;

    keySpeed = F_ZERO;
    i = 0;
    off = i;
    for (; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz3dioe(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z3dioe(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z3dieo(Mv *mv) {
    int i;
    Entry *e;
    int off;
    float keySpeed;

    keySpeed = F_ZERO;
    i = 0;
    off = i;
    for (; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz3dieo(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z3dieo(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z3deio(Mv *mv) {
    Entry *e;
    int i;
    int off;
    float keySpeed;

    keySpeed = F_ZERO;
    i = 0;
    off = i;
    for (; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz3deio(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z3deio(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z4doei(Mv *mv) {
    int off;
    Entry *e;
    int i;
    float keySpeed;

    keySpeed = F_ZERO;
    i = 0;
    off = 0;
    for (; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz4doei(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z4doei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z4dioe(Mv *mv) {
    int i;
    int off;
    Entry *e;
    float keySpeed;

    keySpeed = F_ZERO;
    i = 0;
    off = 0;
    for (; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz4dioe(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z4dioe(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z4dieo(Mv *mv) {
    int i;
    Entry *e;
    int off;
    float keySpeed;

    keySpeed = F_ZERO;
    i = 0;
    off = 0;
    for (; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz4dieo(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z4dieo(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z4deio(Mv *mv) {
    Entry *e;
    int i;
    int off;
    float keySpeed;

    keySpeed = F_ZERO;
    i = 0;
    off = 0;
    for (; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz4deio(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z4deio(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z5doei(Mv *mv) {
    int off;
    Entry *e;
    int i;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (off = 0, i = off; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz5doei(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z5doei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z5dioe(Mv *mv) {
    int i;
    int off;
    Entry *e;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (off = 0, i = off; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz5dioe(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z5dioe(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z5dieo(Mv *mv) {
    int i;
    Entry *e;
    int off;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (off = 0, i = off; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz5dieo(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z5dieo(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z5deio(Mv *mv) {
    Entry *e;
    int i;
    int off;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (off = 0, i = off; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz5deio(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z5deio(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z6doei(Mv *mv) {
    int off;
    Entry *e;
    int i;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (off = 0, i = 0; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz6doei(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z6doei(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z6dioe(Mv *mv) {
    int i;
    int off;
    Entry *e;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (off = 0, i = 0; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz6dioe(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z6dioe(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z6dieo(Mv *mv) {
    int i;
    Entry *e;
    int off;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (off = 0, i = 0; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz6dieo(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z6dieo(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CM_z6deio(Mv *mv) {
    Entry *e;
    int i;
    int off;
    float keySpeed;

    keySpeed = F_ZERO;
    
    for (off = 0, i = 0; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
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

float zz6deio(Self *self) {
    Mv *mv = self->movement;
    float max = CM_z6deio(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
