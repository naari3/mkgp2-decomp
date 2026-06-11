/* mr-SR-init probe TU (batch_research_mrsrinit_phase2c).
 *
 * Target shape (KartItem_GetMaxSpeedWithBonus 0x8004F040 preheader):
 *   li   r4, 0x0          ; i
 *   lwz  r5, 0x28(r3)     ; mv
 *   lfs  f3, F_ZERO(r2)
 *   mr   r6, r4           ; off  <-- the copy that escaped const-prop
 *   lfs  f0, F_ONE(r2)
 *   b    Lcond
 * Every plain C spelling of `off = i` (i==0) const-propagates to `li r6, 0`.
 * Variants below try to make CW 1.3.2 keep the register copy.
 */

#pragma exceptions off

typedef struct Pair {
    float key;   /* 0x0 */
    float value; /* 0x4 */
} Pair;

typedef struct Entry {
    Pair *pairs;    /* 0x0 */
    int count;      /* 0x4 */
    float refSpeed; /* 0x8 */
    char pad[0xc];  /* stride 0x18 */
} Entry;

typedef struct Mv {
    char pad0[0x8];
    int tableIdx;          /* 0x8 */
    char padC[0x16];
    unsigned char capFlag; /* 0x22 */
    char pad23[0x1];
    Entry *table;          /* 0x24 */
    char pad28[0x2e0 - 0x28];
    float coinBonus;       /* 0x2e0 */
} Mv;

typedef struct Self {
    char pad0[0x28];
    Mv *movement; /* 0x28 */
} Self;

extern const float F_ZERO; /* lbl_806D26EC */
extern const float F_ONE;  /* lbl_806D26FC */
extern const float F_CAP;  /* lbl_806D276C */
extern const float F_MUL;  /* lbl_806D2770 */

#define TAIL()                                              \
    if (mv->capFlag == 1) {                                 \
        if (keySpeed >= F_CAP) {                            \
            keySpeed = F_CAP;                               \
        }                                                   \
    }                                                       \
    return F_MUL * keySpeed * (F_ONE + mv->coinBonus)

#define KEYREAD(E, OFF) (*(const float *)((const char *)(E)->pairs + (OFF)))
#define HIT() keySpeed = mv->table[mv->tableIdx].pairs[i].value

/* v01 baseline (known negative): for-init off = i -> li,li */
float v01_baseline(Self *self) {
    Mv *mv;
    int i;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0, off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v02 plain struct indexing, no off var: let CW strength-reduce i*8 itself */
float v02_plainidx(Self *self) {
    Mv *mv;
    int i;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0; i < (e = &mv->table[mv->tableIdx])->count; i++) {
        if ((float)__fabs(e->pairs[i].key - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v03 byte-offset expression with explicit 8*i (no off var): SR candidate */
float v03_byteexpr(Self *self) {
    Mv *mv;
    int i;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0; i < (e = &mv->table[mv->tableIdx])->count; i++) {
        if ((float)__fabs(*(const float *)((const char *)e->pairs + 8 * i) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v04 init by statements before the for */
float v04_initstmt(Self *self) {
    Mv *mv;
    int i;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    i = 0;
    off = i;
    for (; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v05 address-taken i, init through pointer */
float v05_addrstore(Self *self) {
    Mv *mv;
    int i;
    int *pi;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    pi = &i;
    *pi = 0;
    for (off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v06 address-taken i, off reads through pointer */
float v06_addrread(Self *self) {
    Mv *mv;
    int i;
    int *pi;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    pi = &i;
    i = 0;
    for (off = *pi; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v07 swap: off gets the li, i copies off */
float v07_swapinit(Self *self) {
    Mv *mv;
    int i;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    for (off = 0, i = off; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v08 chained assignment */
float v08_chain(Self *self) {
    Mv *mv;
    int i;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = off = 0; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v09 off = i * 8 in for-init */
float v09_mulinit(Self *self) {
    Mv *mv;
    int i;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0, off = i * 8; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v10 register storage class */
float v10_register(Self *self) {
    Mv *mv;
    register int i;
    register int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0, off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v11 off unsigned */
float v11_unsignedoff(Self *self) {
    Mv *mv;
    int i;
    unsigned int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0, off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v12 identity expressions that need late simplification */
float v12_oride(Self *self) {
    Mv *mv;
    int i;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0, off = i | 0; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v13 volatile read of i for the off init */
float v13_volread(Self *self) {
    Mv *mv;
    int i;
    int off;
    Entry *e;
    float keySpeed;

    mv = self->movement;
    keySpeed = F_ZERO;
    i = 0;
    for (off = *(volatile int *)&i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(KEYREAD(e, off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}
