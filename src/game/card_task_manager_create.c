/* === extracted from auto_card_task_manager_cr_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void FUN_8003b120();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803FE7E8[];

/* --- function index (1 fns, .text 0x8008A0A0..0x8008A2A0) ---
 * [  0] 0x8008A0A0 size:0x200   global card_task_manager_create
 */

/* --- forward decls --- */
asm void card_task_manager_create(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_card_task_manager_create[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_card_task_manager_create = {
    (void *)&card_task_manager_create, 0x00000200, (void *)extab_card_task_manager_create
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void card_task_manager_create(void) { /* 0x8008A0A0 size:0x200 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    li r7, 0x0
    stw r0, 0x24(r1)
    li r0, 0x3c
    stw r31, 0x1c(r1)
    mr r31, r6
    stw r30, 0x18(r1)
    mr r30, r5
    stw r29, 0x14(r1)
    mr r29, r3
    stw r28, 0x10(r1)
    mr r28, r4
    stw r7, 0x0(r3)
    stw r7, 0x4(r3)
    li r3, 0x20
    stw r7, 0x8(r29)
    stw r7, 0xc(r29)
    stw r0, 0x10(r29)
    stw r7, 0x4(r29)
    bl FUN_8003b120
    stw r3, 0x0(r29)
    clrlwi r0, r28, 24
    li r4, 0x0
    lwz r3, 0x0(r29)
    cmplwi r0, 0x1
    stw r4, 0x0(r3)
    lwz r3, 0x0(r29)
    stw r4, 0x8(r3)
    lwz r3, 0x0(r29)
    stw r4, 0x10(r3)
    lwz r3, 0x0(r29)
    stw r4, 0x18(r3)
    bne card_task_manager_create_L_8008A16C
    lis r3, lbl_803FE7E8@ha
    lwz r12, lbl_803FE7E8@l(r3)
    mtctr r12
    bctrl
    lwz r0, 0x4(r29)
    li r4, 0x0
    lwz r5, 0x0(r29)
    slwi r0, r0, 3
    stwx r3, r5, r0
    lwz r0, 0x4(r29)
    lwz r3, 0x0(r29)
    slwi r0, r0, 3
    add r3, r3, r0
    stw r4, 0x4(r3)
    lwz r3, 0x4(r29)
    addi r0, r3, 0x1
    stw r0, 0x4(r29)
    card_task_manager_create_L_8008A16C:
    lis r3, lbl_803FE7E8@ha
    addi r3, r3, lbl_803FE7E8@l
    lwz r12, 0x8(r3)
    mtctr r12
    bctrl
    lwz r5, 0x4(r29)
    clrlwi r0, r30, 24
    lwz r6, 0x0(r29)
    li r4, 0x1
    slwi r5, r5, 3
    cmplwi r0, 0x1
    stwx r3, r6, r5
    lwz r0, 0x4(r29)
    lwz r3, 0x0(r29)
    slwi r0, r0, 3
    add r3, r3, r0
    stw r4, 0x4(r3)
    lwz r3, 0x4(r29)
    addi r0, r3, 0x1
    stw r0, 0x4(r29)
    bne card_task_manager_create_L_8008A208
    lis r3, lbl_803FE7E8@ha
    addi r3, r3, lbl_803FE7E8@l
    lwz r12, 0x10(r3)
    mtctr r12
    bctrl
    lwz r0, 0x4(r29)
    li r4, 0x2
    lwz r5, 0x0(r29)
    slwi r0, r0, 3
    stwx r3, r5, r0
    lwz r0, 0x4(r29)
    lwz r3, 0x0(r29)
    slwi r0, r0, 3
    add r3, r3, r0
    stw r4, 0x4(r3)
    lwz r3, 0x4(r29)
    addi r0, r3, 0x1
    stw r0, 0x4(r29)
    card_task_manager_create_L_8008A208:
    clrlwi r0, r31, 24
    cmplwi r0, 0x1
    bne card_task_manager_create_L_8008A25C
    lis r3, lbl_803FE7E8@ha
    addi r3, r3, lbl_803FE7E8@l
    lwz r12, 0x18(r3)
    mtctr r12
    bctrl
    lwz r0, 0x4(r29)
    li r4, 0x3
    lwz r5, 0x0(r29)
    slwi r0, r0, 3
    stwx r3, r5, r0
    lwz r0, 0x4(r29)
    lwz r3, 0x0(r29)
    slwi r0, r0, 3
    add r3, r3, r0
    stw r4, 0x4(r3)
    lwz r3, 0x4(r29)
    addi r0, r3, 0x1
    stw r0, 0x4(r29)
    card_task_manager_create_L_8008A25C:
    lwz r0, 0x8(r29)
    lwz r3, 0x0(r29)
    slwi r0, r0, 3
    lwzx r3, r3, r0
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r0, 0x24(r1)
    mr r3, r29
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
