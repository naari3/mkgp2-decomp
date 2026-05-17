/*
 * dtk reversed-extab group `auto_fn_8002F640_text` bundle (1 TU, indivisible).
 * 6 functions sharing one extab group.
 *
 * Phase 1b probe: all 6 fns held as asm_fn + manually emitted
 * extab/extabindex via __declspec(section ".extab_user"/".extabindex_user").
 * tools/postprocess_extab_user.py renames sections + symbol names to the
 * `extab`/`extabindex` + `@etb_<addr>`/`@eti_<addr>` form dtk expects.
 *
 * Layout: target has the .text section ordered by fn address but the extab
 * section ordered differently (dtors first, then fn_8002F640, etc.). To
 * control both orders independently we keep:
 *   - function definitions in .text order (fn_8002F640 first)
 *   - extab declarations in target extab order (dtor_8002F910 first)
 *   - extabindex declarations in target extabindex order (fn address order)
 *
 * See docs/per_fn_matching_strategy.md section 11 and
 * docs/large_extab_group_strategy.md.
 */

/* externs for callees and data symbols referenced by the asm bodies. */
extern void DebugPrintf(const char *fmt, ...);
extern unsigned int OSGetTick(void);
extern void fn_802554DC(void);
extern unsigned short *fn_80293BBC(void);
extern void fn_801DB68C(int, int);
extern void *dtor_8003AFB8(void *);
extern void MemoryHeap_GetStats(void *heap, unsigned int *total,
                                unsigned int *largest, unsigned int *count);

extern void *lbl_806CF010;
extern unsigned int *lbl_806D0F9C;
extern int lbl_806D0FA4;
extern signed char lbl_806D0FA8;
extern unsigned int lbl_806D1880;
extern const float lbl_806D2294;
extern const double lbl_806D2298;
extern const float SAFE;
extern const float lbl_806D22B4;
extern const double lbl_806D22B8;
extern unsigned char lbl_80594080[0x60];

extern const char lbl_802E8F48[];
extern const char lbl_802E9650[];

/* Forward decls so manual extabindex entries can reference function pointers. */
asm void fn_8002F640(void);
asm int  HeapStats_DumpForTag(const char *tag);
asm int  isJapanese(void);
asm void fn_8002F8D4(int a, int b, int c);
asm void *dtor_8002F910(void *p, short extend);
asm void *dtor_8002F978(void *p, short extend);

/* =========================================================================
 * Manual extab/extabindex emit (5 entries each; isJapanese has no entry).
 *
 * extab section order matches target: dtor_8002F910 first, then dtor_8002F978,
 * fn_8002F640, HeapStats_DumpForTag, fn_8002F8D4.
 * extabindex section order matches target: fn address order.
 *
 * Source names extab_<fn>/extabindex_<fn> are renamed to @etb_<addr>/@eti_<addr>
 * by tools/postprocess_extab_user.py via llvm-objcopy --redefine-sym.
 * ========================================================================= */
#pragma section R ".extab_user"
#pragma section R ".extabindex_user"

__declspec(section ".extab_user") static const unsigned char extab_dtor_8002F910[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
__declspec(section ".extab_user") static const unsigned char extab_dtor_8002F978[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
__declspec(section ".extab_user") static const unsigned char extab_fn_8002F640[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
__declspec(section ".extab_user") static const unsigned char extab_HeapStats_DumpForTag[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
__declspec(section ".extab_user") static const unsigned char extab_fn_8002F8D4[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

struct extabindex_entry {
    void (*fn)(void);
    unsigned int size;
    const void *extab;
};

__declspec(section ".extabindex_user") static const struct extabindex_entry extabindex_fn_8002F640 = {
    fn_8002F640, 0x1BC, extab_fn_8002F640,
};
__declspec(section ".extabindex_user") static const struct extabindex_entry extabindex_HeapStats_DumpForTag = {
    (void (*)(void))HeapStats_DumpForTag, 0xD0, extab_HeapStats_DumpForTag,
};
__declspec(section ".extabindex_user") static const struct extabindex_entry extabindex_fn_8002F8D4 = {
    (void (*)(void))fn_8002F8D4, 0x3C, extab_fn_8002F8D4,
};
__declspec(section ".extabindex_user") static const struct extabindex_entry extabindex_dtor_8002F910 = {
    (void (*)(void))dtor_8002F910, 0x68, extab_dtor_8002F910,
};
__declspec(section ".extabindex_user") static const struct extabindex_entry extabindex_dtor_8002F978 = {
    (void (*)(void))dtor_8002F978, 0x3C, extab_dtor_8002F978,
};

/* =========================================================================
 * Function definitions in target .text order (fn address ascending).
 * All asm_fn; syntax adjustments:
 *   - `lbl@sda21(r0)` -> `lbl(r2)` (mwcc auto-attaches sda21 for sdata syms)
 *   - `crclr cr1eq`/`crset cr1eq` -> `crxor 6,6,6`/`creqv 6,6,6`
 *   - local labels renamed to `_<fn>_LNNN` to avoid TU-wide collisions
 * ========================================================================= */

asm void fn_8002F640(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    lbz r0, lbl_806D0FA8(r2)
    extsb. r0, r0
    bne _fn8002F640_L66C
    li r3, 0x0
    li r0, 0x1
    stw r3, lbl_806D0FA4(r2)
    stb r0, lbl_806D0FA8(r2)
_fn8002F640_L66C:
    lwz r31, lbl_806D0F9C(r2)
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    lwz r7, 0x0(r31)
    subi r6, r4, 0x217d
    srwi r4, r5, 2
    stw r0, 0x8(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f3, lbl_806D2298(r2)
    slwi r3, r3, 3
    lfs f1, lbl_806D2294(r2)
    lfs f0, SAFE(r2)
    srwi r0, r0, 15
    divwu r0, r3, r0
    stw r0, 0xc(r1)
    lfd f2, 0x8(r1)
    fsubs f2, f2, f3
    fdivs f1, f2, f1
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne _fn8002F640_L6D8
    li r0, 0x1
    b _fn8002F640_L6DC
_fn8002F640_L6D8:
    li r0, 0x0
_fn8002F640_L6DC:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne _fn8002F640_L7E8
    bl fn_802554DC
    bl fn_80293BBC
    lhz r0, 0x0(r3)
    lis r4, lbl_80594080@ha
    lwz r31, lbl_806D0F9C(r2)
    sthu r0, lbl_80594080@l(r4)
    lhz r0, 0x2(r3)
    sth r0, 0x2(r4)
    lhz r0, 0x4(r3)
    sth r0, 0x4(r4)
    lhz r0, 0x6(r3)
    sth r0, 0x6(r4)
    lwz r5, 0x8(r3)
    lwz r0, 0xc(r3)
    stw r5, 0x8(r4)
    stw r0, 0xc(r4)
    lbz r0, 0x10(r3)
    stb r0, 0x10(r4)
    lbz r0, 0x11(r3)
    stb r0, 0x11(r4)
    lhz r0, 0x12(r3)
    sth r0, 0x12(r4)
    lhz r0, 0x14(r3)
    sth r0, 0x14(r4)
    lhz r0, 0x16(r3)
    sth r0, 0x16(r4)
    lwz r5, 0x18(r3)
    lwz r0, 0x1c(r3)
    stw r5, 0x18(r4)
    stw r0, 0x1c(r4)
    lwz r5, 0x20(r3)
    lwz r0, 0x24(r3)
    stw r5, 0x20(r4)
    stw r0, 0x24(r4)
    lwz r0, 0x28(r3)
    stw r0, 0x28(r4)
    lwz r5, 0x2c(r3)
    lwz r0, 0x30(r3)
    stw r5, 0x2c(r4)
    stw r0, 0x30(r4)
    lwz r5, 0x34(r3)
    lwz r0, 0x38(r3)
    stw r5, 0x34(r4)
    stw r0, 0x38(r4)
    lwz r0, 0x3c(r3)
    stw r0, 0x3c(r4)
    lwz r5, 0x40(r3)
    lwz r0, 0x44(r3)
    stw r5, 0x40(r4)
    stw r0, 0x44(r4)
    lwz r5, 0x48(r3)
    lwz r0, 0x4c(r3)
    stw r5, 0x48(r4)
    stw r0, 0x4c(r4)
    lwz r5, 0x50(r3)
    lwz r0, 0x54(r3)
    stw r5, 0x50(r4)
    stw r0, 0x54(r4)
    lwz r0, 0x58(r3)
    stw r0, 0x58(r4)
    lwz r0, 0x5c(r3)
    stw r0, 0x5c(r4)
    bl OSGetTick
    stw r3, 0x0(r31)
_fn8002F640_L7E8:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

asm int HeapStats_DumpForTag(const char *tag) {
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r4, lbl_802E8F48@ha
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    addi r31, r4, lbl_802E8F48@l
    stw r30, 0x28(r1)
    mr r30, r3
    addi r3, r31, 0x6ac
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r3, lbl_806CF010(r2)
    addi r4, r1, 0x10
    addi r5, r1, 0xc
    addi r6, r1, 0x8
    bl MemoryHeap_GetStats
    lwz r3, 0x10(r1)
    lis r0, 0x4330
    stw r0, 0x18(r1)
    mr r5, r30
    srawi r0, r3, 10
    lfd f2, lbl_806D22B8(r2)
    addze r4, r0
    lwz r3, 0xc(r1)
    xoris r0, r4, 0x8000
    lfs f0, lbl_806D22B4(r2)
    stw r0, 0x1c(r1)
    srawi r0, r3, 10
    addze r0, r0
    addi r3, r31, 0x6d4
    lfd f1, 0x18(r1)
    stw r4, 0x10(r1)
    fsubs f1, f1, f2
    stw r0, 0xc(r1)
    fmuls f1, f1, f0
    creqv 6, 6, 6
    bl DebugPrintf
    lwz r4, 0xc(r1)
    addi r3, r31, 0x6ec
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r4, 0x8(r1)
    addi r3, r31, 0x6fc
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r0, 0x34(r1)
    li r3, 0x0
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

asm int isJapanese(void) {
    nofralloc
    li r3, 0
    blr
}

asm void fn_8002F8D4(int a, int b, int c) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r6, lbl_802E9650@ha
    stw r0, 0x14(r1)
    mr r0, r4
    mr r4, r3
    addi r3, r6, lbl_802E9650@l
    mr r6, r5
    mr r5, r0
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void *dtor_8002F910(void *p, short extend) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq _dtor8002F910_L95C
    lwz r3, lbl_806D1880(r2)
    cmplwi r3, 0x0
    bne _dtor8002F910_L94C
    li r4, 0x1
    bl fn_801DB68C
    li r0, 0x0
    stw r0, lbl_806D1880(r2)
_dtor8002F910_L94C:
    extsh. r0, r31
    ble _dtor8002F910_L95C
    mr r3, r30
    bl dtor_8003AFB8
_dtor8002F910_L95C:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void *dtor_8002F978(void *p, short extend) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr. r31, r3
    beq _dtor8002F978_L99C
    extsh. r0, r4
    ble _dtor8002F978_L99C
    bl dtor_8003AFB8
_dtor8002F978_L99C:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
