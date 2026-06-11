/* mr-SR-init probe TU #2: byte offset computed INSIDE the loop body so that
 * SR/LICM motion creates the preheader init (hypothesis: moved zero inits do
 * an availability check and emit mr from an existing zero web). */

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

#define TAIL()                                              \
    if (mv->capFlag == 1) {                                 \
        if (keySpeed >= F_CAP) { keySpeed = F_CAP; }        \
    }                                                       \
    return F_MUL * keySpeed * (F_ONE + mv->coinBonus)

#define HIT() keySpeed = mv->table[mv->tableIdx].pairs[i].value

/* v14 while-loop, off = i * 8 inside body */
float v14_whilebody(Self *self) {
    Mv *mv; int i; int off; Entry *e; float keySpeed;
    mv = self->movement;
    keySpeed = F_ZERO;
    i = 0;
    while (i < (e = &mv->table[mv->tableIdx])->count) {
        off = i * 8;
        if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
        i++;
    }
    TAIL();
}

/* v15 for-loop, off = i * 8 first body stmt */
float v15_forbody(Self *self) {
    Mv *mv; int i; int off; Entry *e; float keySpeed;
    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0; i < (e = &mv->table[mv->tableIdx])->count; i++) {
        off = i * 8;
        if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v16 for-loop, off = i << 3 in body */
float v16_shiftbody(Self *self) {
    Mv *mv; int i; int off; Entry *e; float keySpeed;
    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0; i < (e = &mv->table[mv->tableIdx])->count; i++) {
        off = i << 3;
        if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v17 explicit off IV but with a dead in-loop zero use that LICM can hoist:
 * decoy: store-value temp? not applicable; instead read key via off and ALSO
 * recompute hit via i (baseline) but init off inside an if(i==0) guard --
 * structurally different, skip. Instead: off IV with init moved by making the
 * for-init contain a loop-invariant expr of a variable: off = i + 0 in body */
float v17_addzero(Self *self) {
    Mv *mv; int i; int off; Entry *e; float keySpeed;
    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0; i < (e = &mv->table[mv->tableIdx])->count; i++) {
        off = (i + 0) * 8;
        if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}

/* v18 pointer form in body: p = (char*)e->pairs + 8*i */
float v18_ptrbody(Self *self) {
    Mv *mv; int i; const char *p; Entry *e; float keySpeed;
    mv = self->movement;
    keySpeed = F_ZERO;
    for (i = 0; i < (e = &mv->table[mv->tableIdx])->count; i++) {
        p = (const char *)e->pairs + 8 * i;
        if ((float)__fabs(*(const float *)p - e->refSpeed) < F_ONE) {
            HIT();
            break;
        }
    }
    TAIL();
}
