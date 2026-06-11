/* mr-SR-init probe TU #3: split the front end's local-EBB constant tracking
 * between `i = 0` and `off = i` without changing the final CFG. */

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

#define LOOP()                                                                  \
    for (; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {          \
        if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < F_ONE) { \
            keySpeed = mv->table[mv->tableIdx].pairs[i].value;                  \
            break;                                                              \
        }                                                                       \
    }

/* v20 unused label between the two inits */
float v20_label(Self *self) {
    Mv *mv; int i; int off; Entry *e; float keySpeed;
    mv = self->movement;
    keySpeed = F_ZERO;
    i = 0;
once:
    off = i;
    LOOP();
    TAIL();
}

/* v21 unused label before both inits (control) */
float v21_labelctl(Self *self) {
    Mv *mv; int i; int off; Entry *e; float keySpeed;
    mv = self->movement;
    keySpeed = F_ZERO;
once:
    i = 0;
    off = i;
    LOOP();
    TAIL();
}

/* v22 do-while(0) wrapper around off = i */
float v22_dowhile0(Self *self) {
    Mv *mv; int i; int off; Entry *e; float keySpeed;
    mv = self->movement;
    keySpeed = F_ZERO;
    i = 0;
    do { off = i; } while (0);
    LOOP();
    TAIL();
}

/* v23 label between, but inits in for-init order via comma kept in loop */
float v23_labelfor(Self *self) {
    Mv *mv; int i; int off; Entry *e; float keySpeed;
    mv = self->movement;
    keySpeed = F_ZERO;
    i = 0;
once:
    for (off = i; i < (e = &mv->table[mv->tableIdx])->count; off += 8, i++) {
        if ((float)__fabs(*(const float *)((const char *)e->pairs + off) - e->refSpeed) < F_ONE) {
            keySpeed = mv->table[mv->tableIdx].pairs[i].value;
            break;
        }
    }
    TAIL();
}
