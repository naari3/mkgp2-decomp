/* === extracted from auto_ItemObjectManager_Ti_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemHitRegistry_PruneStale();
extern void ItemObject_CheckKartCollision();
extern void ItemObject_CheckPairCollision();
extern void JointByName_GetWorldPosition();
extern void SpriteSlot_TickAnim();
extern void Vec3_Copy();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5A8C;
extern unsigned int lbl_806D5A90;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8041AC24[];

/* --- function index (1 fns, .text 0x800D85B8..0x800D8840) ---
 * [  0] 0x800D85B8 size:0x288   global ItemObjectManager_TickActiveItems
 */

/* --- forward decls --- */
asm void ItemObjectManager_TickActiveItems(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemObjectManager_TickActiveItems[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemObjectManager_TickActiveItems = {
    (void *)&ItemObjectManager_TickActiveItems, 0x00000288, (void *)extab_ItemObjectManager_TickActiveItems
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemObjectManager_TickActiveItems(void) { /* 0x800D85B8 size:0x288 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr r28, r3
    li r27, 0x0
    mr r29, r28
    ItemObjectManager_TickActiveItems_L_800D85D4:
    lbz r0, 0x0(r29)
    extsb. r0, r0
    beq ItemObjectManager_TickActiveItems_L_800D8624
    lwz r12, 0x4(r29)
    cmplwi r12, 0x0
    beq ItemObjectManager_TickActiveItems_L_800D85F8
    mr r3, r29
    mtctr r12
    bctrl
    ItemObjectManager_TickActiveItems_L_800D85F8:
    lbz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 29, 29
    bne ItemObjectManager_TickActiveItems_L_800D860C
    addi r3, r29, 0x14
    bl SpriteSlot_TickAnim
    ItemObjectManager_TickActiveItems_L_800D860C:
    lwz r12, 0xe0(r29)
    cmplwi r12, 0x0
    beq ItemObjectManager_TickActiveItems_L_800D8624
    mr r3, r29
    mtctr r12
    bctrl
    ItemObjectManager_TickActiveItems_L_800D8624:
    addi r27, r27, 0x1
    addi r29, r29, 0x1ec
    cmpwi r27, 0x100
    blt ItemObjectManager_TickActiveItems_L_800D85D4
    li r27, 0x0
    mr r29, r28
    ItemObjectManager_TickActiveItems_L_800D863C:
    lbz r0, 0x0(r29)
    extsb. r0, r0
    beq ItemObjectManager_TickActiveItems_L_800D86D8
    lbz r4, 0x1c(r29)
    lis r3, lbl_8041AC24@ha
    addi r0, r3, lbl_8041AC24@l
    mulli r3, r4, 0x14
    add r3, r0, r3
    lbz r0, 0xc(r3)
    extsb. r0, r0
    beq ItemObjectManager_TickActiveItems_L_800D8690
    lwz r5, 0x10(r3)
    addi r3, r29, 0xcc
    addi r4, r29, 0x14
    bl JointByName_GetWorldPosition
    cmpwi r3, 0x0
    bne ItemObjectManager_TickActiveItems_L_800D869C
    addi r3, r29, 0xcc
    addi r4, r29, 0xa0
    bl Vec3_Copy
    b ItemObjectManager_TickActiveItems_L_800D869C
    ItemObjectManager_TickActiveItems_L_800D8690:
    addi r3, r29, 0xcc
    addi r4, r29, 0xa0
    bl Vec3_Copy
    ItemObjectManager_TickActiveItems_L_800D869C:
    lbz r4, 0x1c(r29)
    lis r3, lbl_8041AC24@ha
    addi r0, r3, lbl_8041AC24@l
    lfs f2, 0xc4(r29)
    mulli r3, r4, 0x14
    lfs f0, lbl_806D5A8C(r2)
    add r3, r0, r3
    lfs f1, 0x8(r3)
    fmuls f1, f2, f1
    stfs f1, 0xd8(r29)
    lfs f1, 0xd8(r29)
    fcmpo cr0, f1, f0
    bge ItemObjectManager_TickActiveItems_L_800D86D8
    lfs f0, lbl_806D5A90(r2)
    stfs f0, 0xd8(r29)
    ItemObjectManager_TickActiveItems_L_800D86D8:
    addi r27, r27, 0x1
    addi r29, r29, 0x1ec
    cmpwi r27, 0x100
    blt ItemObjectManager_TickActiveItems_L_800D863C
    li r30, 0x0
    mr r31, r28
    ItemObjectManager_TickActiveItems_L_800D86F0:
    lbz r0, 0x0(r31)
    extsb. r0, r0
    beq ItemObjectManager_TickActiveItems_L_800D8808
    lbz r0, 0x8c(r31)
    extsb. r0, r0
    beq ItemObjectManager_TickActiveItems_L_800D8808
    lbz r0, 0x8d(r31)
    extsb. r0, r0
    beq ItemObjectManager_TickActiveItems_L_800D8808
    addi r29, r30, 0x1
    mulli r0, r29, 0x1ec
    add r27, r28, r0
    b ItemObjectManager_TickActiveItems_L_800D8800
    ItemObjectManager_TickActiveItems_L_800D8724:
    lbz r0, 0x0(r27)
    extsb. r0, r0
    beq ItemObjectManager_TickActiveItems_L_800D87F8
    lbz r4, 0x8c(r27)
    extsb. r0, r4
    beq ItemObjectManager_TickActiveItems_L_800D87F8
    lbz r0, 0x8d(r27)
    extsb. r0, r0
    beq ItemObjectManager_TickActiveItems_L_800D87F8
    lwz r0, 0xe4(r31)
    cmplw r0, r27
    beq ItemObjectManager_TickActiveItems_L_800D87F8
    lwz r3, 0xe4(r27)
    cmplw r3, r31
    beq ItemObjectManager_TickActiveItems_L_800D87F8
    cmplwi r0, 0x0
    beq ItemObjectManager_TickActiveItems_L_800D8770
    cmplw r0, r3
    beq ItemObjectManager_TickActiveItems_L_800D87F8
    ItemObjectManager_TickActiveItems_L_800D8770:
    lbz r5, 0x8c(r31)
    cmpwi r5, 0x5
    bne ItemObjectManager_TickActiveItems_L_800D8788
    extsb r0, r4
    cmpwi r0, 0x5
    beq ItemObjectManager_TickActiveItems_L_800D87F8
    ItemObjectManager_TickActiveItems_L_800D8788:
    lwz r3, 0x8(r31)
    cmpwi r3, 0x69
    bne ItemObjectManager_TickActiveItems_L_800D87A0
    lwz r0, 0x8(r27)
    cmpwi r0, 0x69
    beq ItemObjectManager_TickActiveItems_L_800D87F8
    ItemObjectManager_TickActiveItems_L_800D87A0:
    cmpwi r3, 0x46
    bne ItemObjectManager_TickActiveItems_L_800D87B4
    lwz r0, 0x8(r27)
    cmpwi r0, 0x46
    beq ItemObjectManager_TickActiveItems_L_800D87F8
    ItemObjectManager_TickActiveItems_L_800D87B4:
    extsb r0, r5
    cmpwi r0, 0x5
    bne ItemObjectManager_TickActiveItems_L_800D87D0
    mr r3, r31
    mr r4, r27
    bl ItemObject_CheckKartCollision
    b ItemObjectManager_TickActiveItems_L_800D87F8
    ItemObjectManager_TickActiveItems_L_800D87D0:
    extsb r0, r4
    cmpwi r0, 0x5
    bne ItemObjectManager_TickActiveItems_L_800D87EC
    mr r3, r27
    mr r4, r31
    bl ItemObject_CheckKartCollision
    b ItemObjectManager_TickActiveItems_L_800D87F8
    ItemObjectManager_TickActiveItems_L_800D87EC:
    mr r3, r31
    mr r4, r27
    bl ItemObject_CheckPairCollision
    ItemObjectManager_TickActiveItems_L_800D87F8:
    addi r27, r27, 0x1ec
    addi r29, r29, 0x1
    ItemObjectManager_TickActiveItems_L_800D8800:
    cmpwi r29, 0x100
    blt ItemObjectManager_TickActiveItems_L_800D8724
    ItemObjectManager_TickActiveItems_L_800D8808:
    addi r30, r30, 0x1
    addi r31, r31, 0x1ec
    cmpwi r30, 0xff
    blt ItemObjectManager_TickActiveItems_L_800D86F0
    addis r4, r28, 0x2
    lwz r3, -0x13fc(r4)
    addi r0, r3, 0x1
    stw r0, -0x13fc(r4)
    bl ItemHitRegistry_PruneStale
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
