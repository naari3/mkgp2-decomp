/* === extracted from auto_CardRW_ErrorDisplay_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawText();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8030E598[];

/* --- function index (1 fns, .text 0x80066350..0x800668FC) ---
 * [  0] 0x80066350 size:0x5AC   global CardRW_ErrorDisplay
 */

/* --- forward decls --- */
asm void CardRW_ErrorDisplay(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardRW_ErrorDisplay[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardRW_ErrorDisplay = {
    (void *)&CardRW_ErrorDisplay, 0x000005AC, (void *)extab_CardRW_ErrorDisplay
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardRW_ErrorDisplay(void) { /* 0x80066350 size:0x5AC */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lis r3, lbl_8030E598@ha
    lwz r7, 0x284(r30)
    addi r31, r3, lbl_8030E598@l
    cmpwi r7, 0x1
    bne CardRW_ErrorDisplay_L_80066384
    li r3, 0x0
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_80066384:
    lwz r3, 0x270(r30)
    cmplwi r3, 0x0
    bne CardRW_ErrorDisplay_L_80066398
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_80066398:
    cmpwi r7, 0x65
    bne CardRW_ErrorDisplay_L_80066418
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_80066410
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    addi r7, r2, -0x7518  /* lbl_806D2D48 */
    creqv 6, 6, 6
    bl DrawText
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b6c
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_80066410
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b80
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_80066410:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_80066418:
    cmpwi r7, 0x66
    bne CardRW_ErrorDisplay_L_80066498
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_80066490
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    addi r7, r2, -0x7514  /* lbl_806D2D4C */
    creqv 6, 6, 6
    bl DrawText
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b9c
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_80066490
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b80
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_80066490:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_80066498:
    cmpwi r7, 0x68
    beq CardRW_ErrorDisplay_L_800664A8
    cmpwi r7, 0x64
    bne CardRW_ErrorDisplay_L_80066520
    CardRW_ErrorDisplay_L_800664A8:
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_80066518
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    addi r7, r2, -0x7510  /* lbl_806D2D50 */
    creqv 6, 6, 6
    bl DrawText
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1bb8
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_80066518
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b80
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_80066518:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_80066520:
    cmpwi r7, 0x69
    bne CardRW_ErrorDisplay_L_800665A0
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_80066598
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    addi r7, r2, -0x750C  /* lbl_806D2D54 */
    creqv 6, 6, 6
    bl DrawText
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1bd0
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_80066598
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b80
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_80066598:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_800665A0:
    cmpwi r7, 0x6a
    bne CardRW_ErrorDisplay_L_80066620
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_80066618
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xc0
    li r6, 0x7
    addi r7, r2, -0x7508  /* lbl_806D2D58 */
    creqv 6, 6, 6
    bl DrawText
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1be8
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_80066618
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b80
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_80066618:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_80066620:
    cmpwi r7, 0x2
    bne CardRW_ErrorDisplay_L_80066680
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_80066678
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x1c00
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_80066678
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b80
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_80066678:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_80066680:
    cmpwi r7, 0x6
    bne CardRW_ErrorDisplay_L_800666E0
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_800666D8
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x1c14
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_800666D8
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b80
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_800666D8:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_800666E0:
    cmpwi r7, 0x7
    bne CardRW_ErrorDisplay_L_80066740
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_80066738
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x1c24
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_80066738
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b80
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_80066738:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_80066740:
    clrlwi. r0, r5, 24
    beq CardRW_ErrorDisplay_L_800667A8
    cmpwi r7, 0x67
    bne CardRW_ErrorDisplay_L_800667A8
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_800667A0
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x1c34
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_800667A0
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1c58
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_800667A0:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_800667A8:
    clrlwi. r0, r5, 24
    beq CardRW_ErrorDisplay_L_80066810
    cmpwi r7, 0x5
    bne CardRW_ErrorDisplay_L_80066810
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_80066808
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x1c34
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_80066808
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1c58
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_80066808:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_80066810:
    clrlwi. r0, r5, 24
    beq CardRW_ErrorDisplay_L_80066880
    clrlwi. r0, r6, 24
    beq CardRW_ErrorDisplay_L_80066880
    cmpwi r7, 0x4
    bne CardRW_ErrorDisplay_L_80066880
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_80066878
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x1c34
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_80066878
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1c58
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_80066878:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_80066880:
    cmpwi r7, 0xff
    bne CardRW_ErrorDisplay_L_800668E0
    clrlwi. r0, r4, 24
    beq CardRW_ErrorDisplay_L_800668D8
    lfs f1, lbl_806D2D44(r2)
    addi r7, r31, 0x1c6c
    li r4, 0x54
    li r5, 0xd8
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt CardRW_ErrorDisplay_L_800668D8
    lwz r3, 0x270(r30)
    addi r7, r31, 0x1b80
    lfs f1, lbl_806D2D44(r2)
    li r4, 0x54
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    CardRW_ErrorDisplay_L_800668D8:
    li r3, 0x1
    b CardRW_ErrorDisplay_L_800668E4
    CardRW_ErrorDisplay_L_800668E0:
    li r3, 0x0
    CardRW_ErrorDisplay_L_800668E4:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

