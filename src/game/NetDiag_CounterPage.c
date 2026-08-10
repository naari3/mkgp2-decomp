/* === extracted from auto_NetDiag_CounterPage_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawText();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void NetDiag_QualityPage();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2D44;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80310484[];
extern unsigned int lbl_803FD71C[];
extern unsigned int lbl_803FD7DC[];

/* --- function index (1 fns, .text 0x80067F74..0x8006830C) ---
 * [  0] 0x80067F74 size:0x398   global NetDiag_CounterPage
 */

/* --- forward decls --- */
asm void NetDiag_CounterPage(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NetDiag_CounterPage[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NetDiag_CounterPage = {
    (void *)&NetDiag_CounterPage, 0x00000398, (void *)extab_NetDiag_CounterPage
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NetDiag_CounterPage(void) { /* 0x80067F74 size:0x398 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r27, 0x1c(r1)
    mr. r28, r4
    mr r30, r3
    bne NetDiag_CounterPage_L_80067F98
    li r0, 0x0
    stw r0, 0x18(r30)
    NetDiag_CounterPage_L_80067F98:
    cmpwi r28, 0x1
    bne NetDiag_CounterPage_L_80068040
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r27, r3
    li r4, 0x800
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq NetDiag_CounterPage_L_80067FF0
    li r0, 0x1f
    stw r0, 0x8(r30)
    lwz r3, 0x18(r30)
    addi r0, r3, 0x1
    cmpwi r0, 0x1
    stw r0, 0x18(r30)
    ble NetDiag_CounterPage_L_80067FF0
    li r0, 0x0
    stw r0, 0x18(r30)
    NetDiag_CounterPage_L_80067FF0:
    mr r3, r27
    li r4, 0x1000
    lwz r12, 0x0(r27)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq NetDiag_CounterPage_L_80068040
    lwz r0, 0x18(r30)
    cmpwi r0, 0x0
    bne NetDiag_CounterPage_L_80068038
    li r0, 0x1f
    mr r3, r30
    stw r0, 0x10(r30)
    li r4, 0x0
    li r5, -0x1
    bl NetDiag_QualityPage
    b NetDiag_CounterPage_L_80068040
    NetDiag_CounterPage_L_80068038:
    li r0, 0x0
    stw r0, 0x10(r30)
    NetDiag_CounterPage_L_80068040:
    cmpwi r28, 0x2
    bne NetDiag_CounterPage_L_800682F4
    lwz r0, 0x34(r30)
    lwz r31, 0x274(r30)
    cmpwi r0, 0x0
    bne NetDiag_CounterPage_L_800680C8
    lwz r4, 0x18(r30)
    lis r3, lbl_803FD71C@ha
    addi r27, r3, lbl_803FD71C@l
    li r29, 0x0
    addi r28, r4, 0xb
    b NetDiag_CounterPage_L_800680B8
    NetDiag_CounterPage_L_80068070:
    cmpw r29, r28
    bne NetDiag_CounterPage_L_80068084
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt NetDiag_CounterPage_L_800680B0
    NetDiag_CounterPage_L_80068084:
    lwz r3, 0x270(r30)
    cmplwi r3, 0x0
    beq NetDiag_CounterPage_L_800680B0
    lwz r4, 0x0(r27)
    li r6, 0x7
    lwz r0, 0x4(r27)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    NetDiag_CounterPage_L_800680B0:
    addi r27, r27, 0xc
    addi r29, r29, 0x1
    NetDiag_CounterPage_L_800680B8:
    lwz r7, 0x8(r27)
    cmplwi r7, 0x0
    bne NetDiag_CounterPage_L_80068070
    b NetDiag_CounterPage_L_80068134
    NetDiag_CounterPage_L_800680C8:
    lwz r4, 0x18(r30)
    lis r3, lbl_803FD7DC@ha
    addi r27, r3, lbl_803FD7DC@l
    li r28, 0x0
    addi r29, r4, 0xb
    b NetDiag_CounterPage_L_80068128
    NetDiag_CounterPage_L_800680E0:
    cmpw r28, r29
    bne NetDiag_CounterPage_L_800680F4
    lwz r0, 0x8(r30)
    cmpwi r0, 0x1e
    bgt NetDiag_CounterPage_L_80068120
    NetDiag_CounterPage_L_800680F4:
    lwz r3, 0x270(r30)
    cmplwi r3, 0x0
    beq NetDiag_CounterPage_L_80068120
    lwz r4, 0x0(r27)
    li r6, 0x7
    lwz r0, 0x4(r27)
    mulli r4, r4, 0xe
    lfs f1, lbl_806D2D44(r2)
    mulli r5, r0, 0x18
    creqv 6, 6, 6
    bl DrawText
    NetDiag_CounterPage_L_80068120:
    addi r27, r27, 0xc
    addi r28, r28, 0x1
    NetDiag_CounterPage_L_80068128:
    lwz r7, 0x8(r27)
    cmplwi r7, 0x0
    bne NetDiag_CounterPage_L_800680E0
    NetDiag_CounterPage_L_80068134:
    lwz r0, 0x454(r31)
    lis r3, lbl_80310484@ha
    addi r7, r3, lbl_80310484@l
    lfs f1, lbl_806D2D44(r2)
    stw r0, 0x8(r1)
    li r4, 0x7e
    li r5, 0x60
    li r6, 0x7
    lwz r3, 0x270(r30)
    lwz r8, 0x43c(r31)
    lwz r9, 0x444(r31)
    lwz r10, 0x44c(r31)
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x394(r31)
    lis r3, lbl_80310484@ha
    addi r7, r3, lbl_80310484@l
    lfs f1, lbl_806D2D44(r2)
    stw r0, 0x8(r1)
    li r4, 0x7e
    li r5, 0x78
    li r6, 0x7
    lwz r3, 0x270(r30)
    lwz r8, 0x37c(r31)
    lwz r9, 0x384(r31)
    lwz r10, 0x38c(r31)
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x474(r31)
    lis r3, lbl_80310484@ha
    addi r7, r3, lbl_80310484@l
    lfs f1, lbl_806D2D44(r2)
    stw r0, 0x8(r1)
    li r4, 0x7e
    li r5, 0x90
    li r6, 0x7
    lwz r3, 0x270(r30)
    lwz r8, 0x45c(r31)
    lwz r9, 0x464(r31)
    lwz r10, 0x46c(r31)
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x3b4(r31)
    lis r3, lbl_80310484@ha
    addi r7, r3, lbl_80310484@l
    lfs f1, lbl_806D2D44(r2)
    stw r0, 0x8(r1)
    li r4, 0x7e
    li r5, 0xa8
    li r6, 0x7
    lwz r3, 0x270(r30)
    lwz r8, 0x39c(r31)
    lwz r9, 0x3a4(r31)
    lwz r10, 0x3ac(r31)
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x3d4(r31)
    lis r3, lbl_80310484@ha
    addi r7, r3, lbl_80310484@l
    lfs f1, lbl_806D2D44(r2)
    stw r0, 0x8(r1)
    li r4, 0x7e
    li r5, 0xc0
    li r6, 0x7
    lwz r3, 0x270(r30)
    lwz r8, 0x3bc(r31)
    lwz r9, 0x3c4(r31)
    lwz r10, 0x3cc(r31)
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x3f4(r31)
    lis r3, lbl_80310484@ha
    addi r7, r3, lbl_80310484@l
    lfs f1, lbl_806D2D44(r2)
    stw r0, 0x8(r1)
    li r4, 0x7e
    li r5, 0xd8
    li r6, 0x7
    lwz r3, 0x270(r30)
    lwz r8, 0x3dc(r31)
    lwz r9, 0x3e4(r31)
    lwz r10, 0x3ec(r31)
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x414(r31)
    lis r3, lbl_80310484@ha
    addi r7, r3, lbl_80310484@l
    lfs f1, lbl_806D2D44(r2)
    stw r0, 0x8(r1)
    li r4, 0x7e
    li r5, 0xf0
    li r6, 0x7
    lwz r3, 0x270(r30)
    lwz r8, 0x3fc(r31)
    lwz r9, 0x404(r31)
    lwz r10, 0x40c(r31)
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x434(r31)
    lis r3, lbl_80310484@ha
    addi r7, r3, lbl_80310484@l
    lfs f1, lbl_806D2D44(r2)
    stw r0, 0x8(r1)
    li r4, 0x7e
    li r5, 0x108
    li r6, 0x7
    lwz r3, 0x270(r30)
    lwz r8, 0x41c(r31)
    lwz r9, 0x424(r31)
    lwz r10, 0x42c(r31)
    creqv 6, 6, 6
    bl DrawText
    NetDiag_CounterPage_L_800682F4:
    lmw r27, 0x1c(r1)
    li r3, 0x1
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

