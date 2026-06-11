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
typedef struct KartItemOpsView2 { char pad0[0x28]; Mv *movement; } KartItemOpsView2;
typedef struct Self { char pad0[0x28]; Mv *movement; } Self;

extern const float F_ZERO, F_ONE, F_CAP, F_MUL;

static float CKB_s1(Mv *mv) {
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
float ss1(Self *self) {
    float max;
    Mv *mv = self->movement;
    max = CKB_s1(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CKB_s2(Mv *mv) {
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
float ss2(Self *self) {
    Mv *mv;
    float max;
    max = CKB_s2(mv = self->movement);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
static float CKB_s3(Mv *mv) {
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
float ss3(Self *self) {
    float bonus;
    Mv *mv = self->movement;
    float max = CKB_s3(mv);
    bonus = F_ONE + mv->coinBonus;
    max = max * bonus;
    return max;
}
static float CKB_s4(Mv *mv) {
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
float ss4(KartItemOpsView2 *self) {
    Mv *mv = self->movement;
    float max = CKB_s4(mv);
    max = max * (F_ONE + mv->coinBonus);
    return max;
}
