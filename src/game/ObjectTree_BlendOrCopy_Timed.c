/* === extracted from auto_ObjectTree_BlendOrCo_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void OSGetTick();
extern void ObjectTree_BlendOrCopy();
extern void Profiler_RecordFrame();
extern void __assert();
extern void fn_802D20AC();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2360;
extern unsigned int lbl_806D2368;
extern unsigned char lbl_806D2348[];
extern unsigned char lbl_806D2350[];

/* --- function index (1 fns, .text 0x80032540..0x8003267C) ---
 * [  0] 0x80032540 size:0x13C   global ObjectTree_BlendOrCopy_Timed
 */

/* --- forward decls --- */
asm void ObjectTree_BlendOrCopy_Timed(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void __dt__11ScopedTimerFv();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_ObjectTree_BlendOrCopy_Timed = { 0x204A0000, 0x00000060, 0x00170010, 0x00000000, 0x82000008, (void *)&__dt__11ScopedTimerFv };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ObjectTree_BlendOrCopy_Timed = {
    (void *)&ObjectTree_BlendOrCopy_Timed, 0x0000013C, (void *)&extab_ObjectTree_BlendOrCopy_Timed
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ObjectTree_BlendOrCopy_Timed(void) { /* 0x80032540 size:0x13C */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    stw r28, 0x20(r1)
    li r0, 0x9
    fmr f31, f1
    stw r0, 0xc(r1)
    mr r28, r3
    mr r29, r4
    mr r30, r5
    mr r31, r6
    bl OSGetTick
    fmr f1, f31
    stw r3, 0x8(r1)
    mr r3, r28
    mr r4, r29
    mr r5, r30
    mr r6, r31
    bl ObjectTree_BlendOrCopy
    cmplwi r31, 0x0
    beq ObjectTree_BlendOrCopy_Timed_L_800325FC
    lwz r0, 0x14(r31)
    rlwinm. r0, r0, 0, 6, 6
    bne ObjectTree_BlendOrCopy_Timed_L_800325FC
    cmplwi r31, 0x0
    beq ObjectTree_BlendOrCopy_Timed_L_800325FC
    bne ObjectTree_BlendOrCopy_Timed_L_800325D0
    addi r3, r2, -0x7F18  /* lbl_806D2348 */
    li r4, 0x25d
    addi r5, r2, -0x7F10  /* lbl_806D2350 */
    bl __assert
    ObjectTree_BlendOrCopy_Timed_L_800325D0:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne ObjectTree_BlendOrCopy_Timed_L_800325EC
    rlwinm. r0, r4, 0, 25, 25
    beq ObjectTree_BlendOrCopy_Timed_L_800325EC
    li r3, 0x1
    ObjectTree_BlendOrCopy_Timed_L_800325EC:
    clrlwi. r0, r3, 24
    bne ObjectTree_BlendOrCopy_Timed_L_800325FC
    mr r3, r31
    bl fn_802D20AC
    ObjectTree_BlendOrCopy_Timed_L_800325FC:
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x8(r1)
    srwi r4, r5, 2
    stw r0, 0x10(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D2368(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D2360(r2)
    lwz r3, 0xc(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x14(r1)
    lfd f1, 0x10(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    psq_l f31, 0x38(r1), 0, 0
    lwz r0, 0x44(r1)
    lfd f31, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

