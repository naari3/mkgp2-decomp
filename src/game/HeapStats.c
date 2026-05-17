/*
 * dtk reversed-extab group `auto_fn_8002F640_text` bundle (1 TU, indivisible).
 *
 * Contains 6 functions: fn_8002F640, HeapStats_DumpForTag, isJapanese,
 * fn_8002F8D4, dtor_8002F910, dtor_8002F978.
 *
 * Phase 1 verify of per-fn matching strategy:
 *   isJapanese is inlined as asm_fn (matches the trivial 3-instruction body
 *   verbatim; chosen for asm_fn verify since it requires no sda21 reloc).
 *   The other 5 are written in C.
 *
 * See docs/per_fn_matching_strategy.md.
 */

extern void DebugPrintf(const char *fmt, ...);
extern unsigned int OSGetTick(void);

extern void fn_802554DC(void);
extern unsigned short *fn_80293BBC(void);
extern void fn_801DB68C(int, int);
extern void *dtor_8003AFB8(void *);
extern void MemoryHeap_GetStats(void *heap, unsigned int *total, unsigned int *largest, unsigned int *count);

/* Externs for sdata/sbss objects. Names match symbols.txt verbatim so the
 * sub does not need to add rename entries. Sized so CW emits SDA21-relocs
 * (<= 8 bytes for sbss/sdata, in line with the project's sdata threshold). */
extern void *lbl_806CF010;          /* default heap pointer (.sdata) */
extern unsigned int *lbl_806D0F9C;  /* prev-tick scratch pointer (.sbss) */
extern int lbl_806D0FA4;            /* scratch (.sbss) */
extern signed char lbl_806D0FA8;    /* init guard (.sbss) */
extern unsigned int lbl_806D1880;   /* memory-manager init guard (.sbss) */
extern const float lbl_806D2294;    /* tick-to-sec denom (.sdata2) */
extern const double lbl_806D2298;   /* 4503601774854144.0 (.sdata2) */
extern const float SAFE;            /* timing threshold (.sdata2) */
extern const float lbl_806D22B4;    /* 1/1024 (.sdata2) */
extern const double lbl_806D22B8;   /* 4503601774854144.0 (.sdata2) */
extern unsigned char lbl_80594080[0x60]; /* heap-stats snapshot buffer (.bss) */

/* rodata strings used by DebugPrintf wrappers. lbl_802E8F48 is a base
 * symbol whose +0x6AC..+0x6FC region carries 4 format strings. */
extern const char lbl_802E8F48[];
extern const char lbl_802E9650[];

/* =========================================================================
 * fn_8002F640 — periodic timing probe. After SAFE seconds since prev OSGetTick,
 * calls fn_802554DC, then copies a 0x60 byte structure (returned by
 * fn_80293BBC) to lbl_80594080 field-by-field (mixed h/b/w widths).
 * ========================================================================= */
void fn_8002F640(void) {
    unsigned int now;
    unsigned int delta;
    unsigned int us_per_500k;
    float elapsed;
    union { struct { unsigned int hi, lo; } i; double d; } u;

    if (lbl_806D0FA8 == 0) {
        lbl_806D0FA4 = 0;
        lbl_806D0FA8 = 1;
    }
    now = OSGetTick();
    /* (now - prev) * 8 / (DAT_800000f8 / 500000) — DAT_800000f8 is bus clock
     * speed in Hz at 0x800000F8. */
    delta = (now - *(unsigned int *)lbl_806D0F9C) << 3;
    us_per_500k = *(unsigned int *)0x800000F8 / 500000U;
    u.i.hi = 0x43300000;
    u.i.lo = delta / us_per_500k;
    elapsed = (float)((u.d - lbl_806D2298) / lbl_806D2294);
    if (elapsed < SAFE) {
        return;
    }
    fn_802554DC();
    {
        unsigned short *p = fn_80293BBC();
        unsigned char *q = lbl_80594080;
        q[0] = ((unsigned char *)p)[0];
        q[1] = ((unsigned char *)p)[1];
        *(unsigned short *)(q + 2) = p[1];
        *(unsigned short *)(q + 4) = p[2];
        *(unsigned short *)(q + 6) = p[3];
        *(unsigned int *)(q + 0x08) = ((unsigned int *)p)[2];
        *(unsigned int *)(q + 0x0C) = ((unsigned int *)p)[3];
        q[0x10] = ((unsigned char *)p)[0x10];
        q[0x11] = ((unsigned char *)p)[0x11];
        *(unsigned short *)(q + 0x12) = p[9];
        *(unsigned short *)(q + 0x14) = p[10];
        *(unsigned short *)(q + 0x16) = p[11];
        *(unsigned int *)(q + 0x18) = ((unsigned int *)p)[6];
        *(unsigned int *)(q + 0x1C) = ((unsigned int *)p)[7];
        *(unsigned int *)(q + 0x20) = ((unsigned int *)p)[8];
        *(unsigned int *)(q + 0x24) = ((unsigned int *)p)[9];
        *(unsigned int *)(q + 0x28) = ((unsigned int *)p)[10];
        *(unsigned int *)(q + 0x2C) = ((unsigned int *)p)[11];
        *(unsigned int *)(q + 0x30) = ((unsigned int *)p)[12];
        *(unsigned int *)(q + 0x34) = ((unsigned int *)p)[13];
        *(unsigned int *)(q + 0x38) = ((unsigned int *)p)[14];
        *(unsigned int *)(q + 0x3C) = ((unsigned int *)p)[15];
        *(unsigned int *)(q + 0x40) = ((unsigned int *)p)[16];
        *(unsigned int *)(q + 0x44) = ((unsigned int *)p)[17];
        *(unsigned int *)(q + 0x48) = ((unsigned int *)p)[18];
        *(unsigned int *)(q + 0x4C) = ((unsigned int *)p)[19];
        *(unsigned int *)(q + 0x50) = ((unsigned int *)p)[20];
        *(unsigned int *)(q + 0x54) = ((unsigned int *)p)[21];
        *(unsigned int *)(q + 0x58) = ((unsigned int *)p)[22];
        *(unsigned int *)(q + 0x5C) = ((unsigned int *)p)[23];
    }
    *(unsigned int *)lbl_806D0F9C = OSGetTick();
}

/* =========================================================================
 * HeapStats_DumpForTag — DebugPrintf wrapper that prints heap snapshot.
 * ========================================================================= */
int HeapStats_DumpForTag(const char *tag) {
    int total_bytes;
    int largest_block_bytes;
    int block_count;
    union { struct { unsigned int hi, lo; } i; double d; } u;
    const char *base = lbl_802E8F48;

    DebugPrintf(base + 0x6AC);
    MemoryHeap_GetStats(lbl_806CF010,
                        (unsigned int *)&total_bytes,
                        (unsigned int *)&largest_block_bytes,
                        (unsigned int *)&block_count);
    u.i.hi = 0x43300000;
    total_bytes = total_bytes / 1024;
    u.i.lo = total_bytes ^ 0x80000000U;
    largest_block_bytes = largest_block_bytes / 1024;
    DebugPrintf(base + 0x6D4,
                (double)((float)(u.d - lbl_806D22B8) * lbl_806D22B4),
                total_bytes, tag);
    DebugPrintf(base + 0x6EC, largest_block_bytes);
    DebugPrintf(base + 0x6FC, block_count);
    return 0;
}

/* =========================================================================
 * isJapanese — locale stub. asm_fn (Phase 1 verify case).
 * ========================================================================= */
asm int isJapanese(void) {
    nofralloc
    li r3, 0
    blr
}

/* =========================================================================
 * fn_8002F8D4 — DebugPrintf wrapper with 3 forwarded args.
 * ========================================================================= */
void fn_8002F8D4(int a, int b, int c) {
    DebugPrintf(lbl_802E9650, a, b, c);
}

/* =========================================================================
 * dtor_8002F910 — guarded MemoryManager_TimedFree wrapper.
 * ========================================================================= */
void *dtor_8002F910(void *p, short extend) {
    if (p != 0) {
        /* Re-use the loaded value of lbl_806D1880 as the r3 arg to
         * fn_801DB68C — keeps register allocator from emitting an extra
         * li r3, 0 instruction. */
        unsigned int g = lbl_806D1880;
        if (g == 0) {
            fn_801DB68C((int)g, 1);
            lbl_806D1880 = 0;
        }
        if (extend > 0) {
            dtor_8003AFB8(p);
        }
    }
    return p;
}

/* =========================================================================
 * dtor_8002F978 — unguarded MemoryManager_TimedFree wrapper.
 * ========================================================================= */
void *dtor_8002F978(void *p, short extend) {
    if (p != 0 && extend > 0) {
        dtor_8003AFB8(p);
    }
    return p;
}
