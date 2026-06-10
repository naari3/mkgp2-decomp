/* Minimal repro for class-1 branch-over-branch bool materialization.
 * Target (non-invert) shape:
 *   or.  r0, rA, r0
 *   bne  L1
 *   b    L2
 * L1:
 *   li   rD, 0x1
 * L2:
 *   clrlwi r0, rD, 24
 * All known CW forms emit the 1-insn-shorter invert:
 *   beq L2 ; li rD,1 ; L2:
 */
typedef unsigned long long u64;
typedef unsigned char u8;

typedef struct Driver {
    char pad[0x10];
    u64 flags; /* hi @0x10, lo @0x14 */
} Driver;

extern void sink(int);

/* form A: if/else assign */
u8 probeA(Driver *d) {
    u8 b;
    if (d->flags & 0x80ULL) {
        b = 1;
    } else {
        b = 0;
    }
    if (b == 1) {
        return 0;
    }
    sink(1);
    return 5;
}

/* form B: ternary */
u8 probeB(Driver *d) {
    u8 b = (d->flags & 0x80ULL) ? 1 : 0;
    if (b == 1) {
        return 0;
    }
    sink(2);
    return 5;
}

/* form C: explicit goto pair mirroring target CFG exactly */
u8 probeC(Driver *d) {
    u8 b = 0;
    if (d->flags & 0x80ULL) goto set1;
    goto done1;
set1:
    b = 1;
done1:
    if (b == 1) {
        return 0;
    }
    sink(3);
    return 5;
}

/* form D: != 0 into u8 (value context, may go branchless) */
u8 probeD(Driver *d) {
    u8 b = (d->flags & 0x80ULL) != 0;
    if (b == 1) {
        return 0;
    }
    sink(4);
    return 5;
}

/* form E: arms swapped, ==0 then-arm assigns 0 (fallthrough), else 1 */
u8 probeE(Driver *d) {
    u8 b;
    if ((d->flags & 0x80ULL) == 0) {
        b = 0;
    } else {
        b = 1;
    }
    if (b == 1) {
        return 0;
    }
    sink(5);
    return 5;
}

/* form F: logical-not condition, arms swapped */
u8 probeF(Driver *d) {
    u8 b;
    if (!(d->flags & 0x80ULL)) {
        b = 0;
    } else {
        b = 1;
    }
    if (b == 1) {
        return 0;
    }
    sink(6);
    return 5;
}

/* form G: pre-set 1, conditional clear */
u8 probeG(Driver *d) {
    u8 b = 1;
    if ((d->flags & 0x80ULL) == 0) {
        b = 0;
    }
    if (b == 1) {
        return 0;
    }
    sink(7);
    return 5;
}

/* form H: ternary with swapped arms via ==0 */
u8 probeH(Driver *d) {
    u8 b = ((d->flags & 0x80ULL) == 0) ? 0 : 1;
    if (b == 1) {
        return 0;
    }
    sink(8);
    return 5;
}
