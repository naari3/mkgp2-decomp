/* === extracted from EffectSteering === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2978;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_803F99E0[];
extern unsigned int lbl_802EDD98[];

/* --- function index (1 fns, .text 0x8005B288..0x8005B43C) ---
 * [  0] 0x8005B288 size:0x1B4   global EffectSteering_InitForDelay
 */

/* --- forward decls --- */
asm void EffectSteering_InitForDelay(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EffectSteering_InitForDelay[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EffectSteering_InitForDelay = {
    (void *)&EffectSteering_InitForDelay, 0x000001B4, (void *)extab_EffectSteering_InitForDelay
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void EffectSteering_InitForDelay(void) { /* 0x8005B288 size:0x1B4 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    fmr f31, f1
    lwz r0, 0x1c(r3)
    mr r31, r4
    cmpwi r0, 0x0
    beq EffectSteering_InitForDelay_L_8005B2D0
    lwz r3, 0x20(r30)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    EffectSteering_InitForDelay_L_8005B2D0:
    li r0, 0x9
    stw r0, 0x1c(r30)
    lwz r0, 0x14(r30)
    cmpwi r0, 0x0
    ble EffectSteering_InitForDelay_L_8005B2F8
    lwz r3, 0xc(r30)
    lwz r0, 0x8(r30)
    cmpw r3, r0
    bge EffectSteering_InitForDelay_L_8005B308
    b EffectSteering_InitForDelay_L_8005B33C
    EffectSteering_InitForDelay_L_8005B2F8:
    lwz r3, 0xc(r30)
    lwz r0, 0x8(r30)
    cmpw r3, r0
    bgt EffectSteering_InitForDelay_L_8005B33C
    EffectSteering_InitForDelay_L_8005B308:
    lfs f0, lbl_806D2978(r2)
    li r0, 0x0
    stw r0, 0x8(r30)
    li r0, 0x1
    fmuls f0, f0, f31
    lwz r3, 0x8(r30)
    fctiwz f0, f0
    stw r3, 0x10(r30)
    stfd f0, 0x8(r1)
    lwz r3, 0xc(r1)
    stw r3, 0xc(r30)
    stw r0, 0x14(r30)
    stb r0, 0x18(r30)
    EffectSteering_InitForDelay_L_8005B33C:
    lwz r0, 0x1c(r30)
    cmplwi r0, 0x9
    bgt EffectSteering_InitForDelay_L_8005B3C0
    lis r3, jumptable_803F99E0@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_803F99E0@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lwz r0, 0x24(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x28(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x2c(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x30(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x34(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x38(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x3c(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x40(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    EffectSteering_InitForDelay_L_8005B3C0:
    lis r3, lbl_802EDD98@ha
    addi r3, r3, lbl_802EDD98@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r0, 0x0
    b EffectSteering_InitForDelay_L_8005B3DC
    EffectSteering_InitForDelay_L_8005B3D8:
    li r0, 0x1
    EffectSteering_InitForDelay_L_8005B3DC:
    clrlwi. r0, r0, 24
    bne EffectSteering_InitForDelay_L_8005B3EC
    li r3, 0x0
    b EffectSteering_InitForDelay_L_8005B41C
    EffectSteering_InitForDelay_L_8005B3EC:
    lwz r3, 0x40(r30)
    stw r31, 0x1c(r3)
    lwz r0, 0x1c(r3)
    cmpwi r0, 0xd
    blt EffectSteering_InitForDelay_L_8005B408
    li r0, 0xc
    stw r0, 0x1c(r3)
    EffectSteering_InitForDelay_L_8005B408:
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r3, 0x1
    EffectSteering_InitForDelay_L_8005B41C:
    psq_l f31, 0x28(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

