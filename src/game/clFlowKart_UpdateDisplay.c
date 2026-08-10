/* === extracted from auto_clFlowKart_UpdateDis_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void GetCoinMilage();
extern void IsCardValid();
extern void Sprite_Destroy();
extern void Sprite_SetAnimParam();
extern void fn_801A08B8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806DA120;
extern unsigned int lbl_806DA124;
extern unsigned int lbl_806DA128;
extern unsigned int lbl_806DA12C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];
extern unsigned int lbl_8039E508[];
extern unsigned int lbl_8049BB30[];

/* --- function index (1 fns, .text 0x801D7920..0x801D7B50) ---
 * [  0] 0x801D7920 size:0x230   global clFlowKart_UpdateDisplay
 */

/* --- forward decls --- */
asm void clFlowKart_UpdateDisplay(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; void *f11; unsigned int f12; void *f13; } extab_clFlowKart_UpdateDisplay = { 0x300A0000, 0x000000CC, 0x00000020, 0x000000F4, 0x00000028, 0x0000011C, 0x00000030, 0x00000000, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowKart_UpdateDisplay = {
    (void *)&clFlowKart_UpdateDisplay, 0x00000230, (void *)&extab_clFlowKart_UpdateDisplay
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowKart_UpdateDisplay(void) { /* 0x801D7920 size:0x230 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stmw r26, 0x28(r1)
    mr r27, r3
    lis r3, lbl_8039E508@ha
    mr r28, r4
    addi r31, r3, lbl_8039E508@l
    li r29, 0x0
    lwz r0, 0x4(r27)
    cmpwi r0, 0x1
    blt clFlowKart_UpdateDisplay_L_801D79A4
    lis r3, g_playerData@ha
    addi r3, r3, g_playerData@l
    bl GetCoinMilage
    slwi r30, r28, 2
    addi r4, r31, 0x3fc
    lwzx r0, r4, r30
    cmpw r3, r0
    blt clFlowKart_UpdateDisplay_L_801D7974
    li r29, 0x1
    clFlowKart_UpdateDisplay_L_801D7974:
    lis r3, g_playerData@ha
    addi r3, r3, g_playerData@l
    bl GetCoinMilage
    addi r4, r31, 0x430
    lwzx r0, r4, r30
    cmpw r3, r0
    blt clFlowKart_UpdateDisplay_L_801D7994
    li r29, 0x2
    clFlowKart_UpdateDisplay_L_801D7994:
    bl IsCardValid
    clrlwi. r0, r3, 24
    bne clFlowKart_UpdateDisplay_L_801D79A4
    li r29, 0x1
    clFlowKart_UpdateDisplay_L_801D79A4:
    lwz r3, 0x74(r27)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x78(r27)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x7c(r27)
    li r4, 0x1
    bl Sprite_Destroy
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowKart_UpdateDisplay_L_801D79EC
    lfs f1, lbl_806DA120(r2)
    li r4, 0x16b
    lfs f2, lbl_806DA124(r2)
    li r5, 0x1
    bl fn_801A08B8
    clFlowKart_UpdateDisplay_L_801D79EC:
    stw r26, 0x74(r27)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowKart_UpdateDisplay_L_801D7A14
    lfs f1, lbl_806DA120(r2)
    li r4, 0x16b
    lfs f2, lbl_806DA128(r2)
    li r5, 0x1
    bl fn_801A08B8
    clFlowKart_UpdateDisplay_L_801D7A14:
    stw r26, 0x78(r27)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowKart_UpdateDisplay_L_801D7A3C
    lfs f1, lbl_806DA120(r2)
    li r4, 0x16b
    lfs f2, lbl_806DA12C(r2)
    li r5, 0x1
    bl fn_801A08B8
    clFlowKart_UpdateDisplay_L_801D7A3C:
    stw r26, 0x7c(r27)
    lis r3, lbl_8049BB30@ha
    mulli r4, r29, 0x27
    addi r29, r1, 0x8
    lwz r8, 0x4b0(r31)
    addi r3, r3, lbl_8049BB30@l
    lwz r7, 0x4b4(r31)
    mr r30, r29
    lwz r6, 0x4b8(r31)
    mulli r0, r28, 0x3
    lwz r5, 0x4bc(r31)
    add r3, r3, r4
    lwz r4, 0x4c0(r31)
    li r28, 0x0
    stw r8, 0x8(r1)
    add r31, r3, r0
    stw r7, 0xc(r1)
    stw r6, 0x10(r1)
    stw r5, 0x14(r1)
    stw r4, 0x18(r1)
    b clFlowKart_UpdateDisplay_L_801D7AAC
    clFlowKart_UpdateDisplay_L_801D7A90:
    lwz r0, 0x0(r30)
    li r5, -0x1
    lwz r3, 0x74(r27)
    extsh r4, r0
    bl Sprite_SetAnimParam
    addi r30, r30, 0x4
    addi r28, r28, 0x1
    clFlowKart_UpdateDisplay_L_801D7AAC:
    lbz r0, 0x0(r31)
    extsb r0, r0
    subfic r0, r0, 0x5
    cmpw r28, r0
    blt clFlowKart_UpdateDisplay_L_801D7A90
    mr r28, r29
    addi r30, r31, 0x1
    li r26, 0x0
    b clFlowKart_UpdateDisplay_L_801D7AEC
    clFlowKart_UpdateDisplay_L_801D7AD0:
    lwz r0, 0x0(r28)
    li r5, -0x1
    lwz r3, 0x78(r27)
    extsh r4, r0
    bl Sprite_SetAnimParam
    addi r28, r28, 0x4
    addi r26, r26, 0x1
    clFlowKart_UpdateDisplay_L_801D7AEC:
    lbz r0, 0x0(r30)
    extsb r0, r0
    subfic r0, r0, 0x5
    cmpw r26, r0
    blt clFlowKart_UpdateDisplay_L_801D7AD0
    addi r28, r31, 0x2
    li r26, 0x0
    b clFlowKart_UpdateDisplay_L_801D7B28
    clFlowKart_UpdateDisplay_L_801D7B0C:
    lwz r0, 0x0(r29)
    li r5, -0x1
    lwz r3, 0x7c(r27)
    extsh r4, r0
    bl Sprite_SetAnimParam
    addi r29, r29, 0x4
    addi r26, r26, 0x1
    clFlowKart_UpdateDisplay_L_801D7B28:
    lbz r0, 0x0(r28)
    extsb r0, r0
    subfic r0, r0, 0x5
    cmpw r26, r0
    blt clFlowKart_UpdateDisplay_L_801D7B0C
    lmw r26, 0x28(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}


