/* mr-SR-init probe TU #5: the two target fns are wrappers around an inlined
 * KartMovement_CalcMaxSpeed (standalone clone at 0x801999E0 lives in another
 * TU -> header inline). Does inlining the loop produce the mr init? */

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

static float CalcMaxSpeed_inl(Mv *mv) {
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

/* w1: GetMaxSpeedWithBonus wrapper shape */
float w1_wrapper(Self *self) {
    Mv *mv = self->movement;
    return CalcMaxSpeed_inl(mv) * (F_ONE + mv->coinBonus);
}

/* w2: same but helper result in a local */
float w2_local(Self *self) {
    Mv *mv = self->movement;
    float max = CalcMaxSpeed_inl(mv);
    return max * (F_ONE + mv->coinBonus);
}
