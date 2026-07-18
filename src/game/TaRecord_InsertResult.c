/* === extracted from auto_TaRecord_InsertResul_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_cupId;
extern unsigned int g_longRoundFlag;
extern unsigned int g_reverseRoundFlag;
extern unsigned int lbl_806D112C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80598A60[];

/* --- function index (1 fns, .text 0x80074C30..0x80074FA4) ---
 * [  0] 0x80074C30 size:0x374   global TaRecord_InsertResult
 */

/* --- forward decls --- */
asm void TaRecord_InsertResult(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TaRecord_InsertResult[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TaRecord_InsertResult = {
    (void *)&TaRecord_InsertResult, 0x00000374, (void *)extab_TaRecord_InsertResult
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TaRecord_InsertResult(void) { /* 0x80074C30 size:0x374 */
    nofralloc
    stwu r1, -0x20(r1)
    li r0, -0x1
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    lwz r8, g_ccClass(r13)
    stw r0, lbl_806D112C(r13)
    cmpwi r8, 0x0
    lwz r30, g_cupId(r13)
    lwz r31, g_longRoundFlag(r13)
    subi r10, r8, 0x1
    lwz r29, g_reverseRoundFlag(r13)
    bne TaRecord_InsertResult_L_80074C6C
    li r3, -0x1
    b TaRecord_InsertResult_L_80074F90
    TaRecord_InsertResult_L_80074C6C:
    cmpwi r10, 0x0
    blt TaRecord_InsertResult_L_80074C7C
    cmpwi r10, 0x2
    blt TaRecord_InsertResult_L_80074C84
    TaRecord_InsertResult_L_80074C7C:
    li r3, -0x1
    b TaRecord_InsertResult_L_80074F90
    TaRecord_InsertResult_L_80074C84:
    cmpwi r30, 0x0
    blt TaRecord_InsertResult_L_80074C94
    cmpwi r30, 0x9
    blt TaRecord_InsertResult_L_80074C9C
    TaRecord_InsertResult_L_80074C94:
    li r3, -0x1
    b TaRecord_InsertResult_L_80074F90
    TaRecord_InsertResult_L_80074C9C:
    cmpwi r31, 0x0
    blt TaRecord_InsertResult_L_80074CAC
    cmpwi r31, 0x2
    blt TaRecord_InsertResult_L_80074CB4
    TaRecord_InsertResult_L_80074CAC:
    li r3, -0x1
    b TaRecord_InsertResult_L_80074F90
    TaRecord_InsertResult_L_80074CB4:
    cmpwi r29, 0x0
    blt TaRecord_InsertResult_L_80074CC4
    cmpwi r29, 0x2
    blt TaRecord_InsertResult_L_80074CCC
    TaRecord_InsertResult_L_80074CC4:
    li r3, -0x1
    b TaRecord_InsertResult_L_80074F90
    TaRecord_InsertResult_L_80074CCC:
    mulli r9, r10, 0x1c20
    lis r8, lbl_80598A60@ha
    li r0, 0x5
    addi r11, r8, lbl_80598A60@l
    mulli r12, r10, 0x1680
    li r8, 0x0
    add r10, r11, r9
    mulli r9, r30, 0x320
    add r12, r11, r12
    mulli r11, r30, 0x280
    add r10, r10, r9
    mulli r9, r31, 0x190
    add r12, r12, r11
    mulli r11, r31, 0x140
    add r10, r10, r9
    mulli r9, r29, 0xc8
    add r12, r12, r11
    mulli r11, r29, 0xa0
    add r9, r10, r9
    add r10, r12, r11
    addi r12, r9, 0x31e0
    mr r11, r12
    addi r9, r10, 0x4e0
    mtctr r0
    TaRecord_InsertResult_L_80074D2C:
    lfs f0, 0x0(r11)
    fcmpo cr0, f1, f0
    bge TaRecord_InsertResult_L_80074D40
    stw r8, lbl_806D112C(r13)
    b TaRecord_InsertResult_L_80074E24
    TaRecord_InsertResult_L_80074D40:
    lfsu f0, 0x4(r11)
    addi r8, r8, 0x1
    fcmpo cr0, f1, f0
    bge TaRecord_InsertResult_L_80074D58
    stw r8, lbl_806D112C(r13)
    b TaRecord_InsertResult_L_80074E24
    TaRecord_InsertResult_L_80074D58:
    lfsu f0, 0x4(r11)
    addi r8, r8, 0x1
    fcmpo cr0, f1, f0
    bge TaRecord_InsertResult_L_80074D70
    stw r8, lbl_806D112C(r13)
    b TaRecord_InsertResult_L_80074E24
    TaRecord_InsertResult_L_80074D70:
    lfsu f0, 0x4(r11)
    addi r8, r8, 0x1
    fcmpo cr0, f1, f0
    bge TaRecord_InsertResult_L_80074D88
    stw r8, lbl_806D112C(r13)
    b TaRecord_InsertResult_L_80074E24
    TaRecord_InsertResult_L_80074D88:
    lfsu f0, 0x4(r11)
    addi r8, r8, 0x1
    fcmpo cr0, f1, f0
    bge TaRecord_InsertResult_L_80074DA0
    stw r8, lbl_806D112C(r13)
    b TaRecord_InsertResult_L_80074E24
    TaRecord_InsertResult_L_80074DA0:
    lfsu f0, 0x4(r11)
    addi r8, r8, 0x1
    fcmpo cr0, f1, f0
    bge TaRecord_InsertResult_L_80074DB8
    stw r8, lbl_806D112C(r13)
    b TaRecord_InsertResult_L_80074E24
    TaRecord_InsertResult_L_80074DB8:
    lfsu f0, 0x4(r11)
    addi r8, r8, 0x1
    fcmpo cr0, f1, f0
    bge TaRecord_InsertResult_L_80074DD0
    stw r8, lbl_806D112C(r13)
    b TaRecord_InsertResult_L_80074E24
    TaRecord_InsertResult_L_80074DD0:
    lfsu f0, 0x4(r11)
    addi r8, r8, 0x1
    fcmpo cr0, f1, f0
    bge TaRecord_InsertResult_L_80074DE8
    stw r8, lbl_806D112C(r13)
    b TaRecord_InsertResult_L_80074E24
    TaRecord_InsertResult_L_80074DE8:
    lfsu f0, 0x4(r11)
    addi r8, r8, 0x1
    fcmpo cr0, f1, f0
    bge TaRecord_InsertResult_L_80074E00
    stw r8, lbl_806D112C(r13)
    b TaRecord_InsertResult_L_80074E24
    TaRecord_InsertResult_L_80074E00:
    lfsu f0, 0x4(r11)
    addi r8, r8, 0x1
    fcmpo cr0, f1, f0
    bge TaRecord_InsertResult_L_80074E18
    stw r8, lbl_806D112C(r13)
    b TaRecord_InsertResult_L_80074E24
    TaRecord_InsertResult_L_80074E18:
    addi r11, r11, 0x4
    addi r8, r8, 0x1
    bdnz TaRecord_InsertResult_L_80074D2C
    TaRecord_InsertResult_L_80074E24:
    lwz r10, lbl_806D112C(r13)
    cmpwi r10, 0x0
    blt TaRecord_InsertResult_L_80074F8C
    cmpwi r10, 0x31
    addi r11, r12, 0xc4
    subfic r8, r10, 0x31
    bge TaRecord_InsertResult_L_80074EB0
    srwi. r0, r8, 3
    mtctr r0
    beq TaRecord_InsertResult_L_80074E9C
    TaRecord_InsertResult_L_80074E4C:
    lfs f0, -0x4(r11)
    stfs f0, 0x0(r11)
    lfs f0, -0x8(r11)
    stfs f0, -0x4(r11)
    lfs f0, -0xc(r11)
    stfs f0, -0x8(r11)
    lfs f0, -0x10(r11)
    stfs f0, -0xc(r11)
    lfs f0, -0x14(r11)
    stfs f0, -0x10(r11)
    lfs f0, -0x18(r11)
    stfs f0, -0x14(r11)
    lfs f0, -0x1c(r11)
    stfs f0, -0x18(r11)
    lfs f0, -0x20(r11)
    stfs f0, -0x1c(r11)
    subi r11, r11, 0x20
    bdnz TaRecord_InsertResult_L_80074E4C
    andi. r8, r8, 0x7
    beq TaRecord_InsertResult_L_80074EB0
    TaRecord_InsertResult_L_80074E9C:
    mtctr r8
    TaRecord_InsertResult_L_80074EA0:
    lfs f0, -0x4(r11)
    stfs f0, 0x0(r11)
    subi r11, r11, 0x4
    bdnz TaRecord_InsertResult_L_80074EA0
    TaRecord_InsertResult_L_80074EB0:
    slwi r0, r10, 2
    cmpwi r10, 0xa
    stfsx f1, r12, r0
    bge TaRecord_InsertResult_L_80074F8C
    lwz r10, lbl_806D112C(r13)
    addi r8, r9, 0x90
    subfic r0, r10, 0x9
    mtctr r0
    cmpwi r10, 0x9
    bge TaRecord_InsertResult_L_80074F30
    TaRecord_InsertResult_L_80074ED8:
    lhz r0, -0x10(r8)
    sth r0, 0x0(r8)
    lhz r0, -0xe(r8)
    sth r0, 0x2(r8)
    lhz r0, -0xc(r8)
    sth r0, 0x4(r8)
    lhz r0, -0xa(r8)
    sth r0, 0x6(r8)
    lhz r0, -0x8(r8)
    sth r0, 0x8(r8)
    lhz r0, -0x6(r8)
    sth r0, 0xa(r8)
    lbz r0, -0x4(r8)
    stb r0, 0xc(r8)
    lbz r0, -0x3(r8)
    stb r0, 0xd(r8)
    lbz r0, -0x2(r8)
    stb r0, 0xe(r8)
    lbz r0, -0x1(r8)
    stb r0, 0xf(r8)
    subi r8, r8, 0x10
    bdnz TaRecord_InsertResult_L_80074ED8
    TaRecord_InsertResult_L_80074F30:
    lhz r0, 0x0(r3)
    slwi r8, r10, 4
    addi r31, r8, 0x2
    sthx r0, r9, r8
    addi r12, r8, 0x4
    addi r11, r8, 0x6
    addi r10, r8, 0x8
    lhz r30, 0x2(r3)
    addi r0, r8, 0xa
    add r8, r9, r8
    sthx r30, r9, r31
    lhz r31, 0x4(r3)
    sthx r31, r9, r12
    lhz r12, 0x6(r3)
    sthx r12, r9, r11
    lhz r11, 0x8(r3)
    sthx r11, r9, r10
    lhz r3, 0xa(r3)
    sthx r3, r9, r0
    stb r7, 0xc(r8)
    stb r4, 0xd(r8)
    stb r5, 0xe(r8)
    stb r6, 0xf(r8)
    TaRecord_InsertResult_L_80074F8C:
    lwz r3, lbl_806D112C(r13)
    TaRecord_InsertResult_L_80074F90:
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    addi r1, r1, 0x20
    blr
}

