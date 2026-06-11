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

static float CalcMaxS_moie(Self *self) {
    Mv *mv;
    int off;
    int i;
    Entry *e;
    float keySpeed;

    mv = self->movement;
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

float ymoie_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_moie(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float ymoie_b(Self *self) {
    float max = CalcMaxS_moie(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_moei(Self *self) {
    Mv *mv;
    int off;
    Entry *e;
    int i;
    float keySpeed;

    mv = self->movement;
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

float ymoei_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_moei(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float ymoei_b(Self *self) {
    float max = CalcMaxS_moei(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_mioe(Self *self) {
    Mv *mv;
    int i;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
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

float ymioe_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_mioe(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float ymioe_b(Self *self) {
    float max = CalcMaxS_mioe(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_mieo(Self *self) {
    Mv *mv;
    int i;
    Entry *e;
    int off;
    float keySpeed;

    mv = self->movement;
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

float ymieo_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_mieo(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float ymieo_b(Self *self) {
    float max = CalcMaxS_mieo(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_meoi(Self *self) {
    Mv *mv;
    Entry *e;
    int off;
    int i;
    float keySpeed;

    mv = self->movement;
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

float ymeoi_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_meoi(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float ymeoi_b(Self *self) {
    float max = CalcMaxS_meoi(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_meio(Self *self) {
    Mv *mv;
    Entry *e;
    int i;
    int off;
    float keySpeed;

    mv = self->movement;
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

float ymeio_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_meio(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float ymeio_b(Self *self) {
    float max = CalcMaxS_meio(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_omie(Self *self) {
    int off;
    Mv *mv;
    int i;
    Entry *e;
    float keySpeed;

    mv = self->movement;
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

float yomie_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_omie(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yomie_b(Self *self) {
    float max = CalcMaxS_omie(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_omei(Self *self) {
    int off;
    Mv *mv;
    Entry *e;
    int i;
    float keySpeed;

    mv = self->movement;
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

float yomei_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_omei(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yomei_b(Self *self) {
    float max = CalcMaxS_omei(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_oime(Self *self) {
    int off;
    int i;
    Mv *mv;
    Entry *e;
    float keySpeed;

    mv = self->movement;
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

float yoime_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_oime(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yoime_b(Self *self) {
    float max = CalcMaxS_oime(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_oiem(Self *self) {
    int off;
    int i;
    Entry *e;
    Mv *mv;
    float keySpeed;

    mv = self->movement;
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

float yoiem_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_oiem(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yoiem_b(Self *self) {
    float max = CalcMaxS_oiem(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_oemi(Self *self) {
    int off;
    Entry *e;
    Mv *mv;
    int i;
    float keySpeed;

    mv = self->movement;
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

float yoemi_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_oemi(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yoemi_b(Self *self) {
    float max = CalcMaxS_oemi(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_oeim(Self *self) {
    int off;
    Entry *e;
    int i;
    Mv *mv;
    float keySpeed;

    mv = self->movement;
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

float yoeim_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_oeim(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yoeim_b(Self *self) {
    float max = CalcMaxS_oeim(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_imoe(Self *self) {
    int i;
    Mv *mv;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
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

float yimoe_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_imoe(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yimoe_b(Self *self) {
    float max = CalcMaxS_imoe(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_imeo(Self *self) {
    int i;
    Mv *mv;
    Entry *e;
    int off;
    float keySpeed;

    mv = self->movement;
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

float yimeo_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_imeo(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yimeo_b(Self *self) {
    float max = CalcMaxS_imeo(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_iome(Self *self) {
    int i;
    int off;
    Mv *mv;
    Entry *e;
    float keySpeed;

    mv = self->movement;
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

float yiome_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_iome(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yiome_b(Self *self) {
    float max = CalcMaxS_iome(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_ioem(Self *self) {
    int i;
    int off;
    Entry *e;
    Mv *mv;
    float keySpeed;

    mv = self->movement;
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

float yioem_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_ioem(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yioem_b(Self *self) {
    float max = CalcMaxS_ioem(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_iemo(Self *self) {
    int i;
    Entry *e;
    Mv *mv;
    int off;
    float keySpeed;

    mv = self->movement;
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

float yiemo_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_iemo(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yiemo_b(Self *self) {
    float max = CalcMaxS_iemo(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_ieom(Self *self) {
    int i;
    Entry *e;
    int off;
    Mv *mv;
    float keySpeed;

    mv = self->movement;
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

float yieom_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_ieom(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yieom_b(Self *self) {
    float max = CalcMaxS_ieom(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_emoi(Self *self) {
    Entry *e;
    Mv *mv;
    int off;
    int i;
    float keySpeed;

    mv = self->movement;
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

float yemoi_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_emoi(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yemoi_b(Self *self) {
    float max = CalcMaxS_emoi(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_emio(Self *self) {
    Entry *e;
    Mv *mv;
    int i;
    int off;
    float keySpeed;

    mv = self->movement;
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

float yemio_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_emio(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yemio_b(Self *self) {
    float max = CalcMaxS_emio(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_eomi(Self *self) {
    Entry *e;
    int off;
    Mv *mv;
    int i;
    float keySpeed;

    mv = self->movement;
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

float yeomi_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_eomi(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yeomi_b(Self *self) {
    float max = CalcMaxS_eomi(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_eoim(Self *self) {
    Entry *e;
    int off;
    int i;
    Mv *mv;
    float keySpeed;

    mv = self->movement;
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

float yeoim_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_eoim(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yeoim_b(Self *self) {
    float max = CalcMaxS_eoim(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_eimo(Self *self) {
    Entry *e;
    int i;
    Mv *mv;
    int off;
    float keySpeed;

    mv = self->movement;
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

float yeimo_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_eimo(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yeimo_b(Self *self) {
    float max = CalcMaxS_eimo(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
static float CalcMaxS_eiom(Self *self) {
    Entry *e;
    int i;
    int off;
    Mv *mv;
    float keySpeed;

    mv = self->movement;
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

float yeiom_a(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxS_eiom(self);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}

float yeiom_b(Self *self) {
    float max = CalcMaxS_eiom(self);
    max = max * (F_ONE + self->movement->coinBonus);
    return max;
}
