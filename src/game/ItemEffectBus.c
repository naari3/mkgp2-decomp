/* ItemEffectBus reversed extab-group bundle: asm_fn fallback. */

/* === extracted from auto_ItemEffectBus_Commit_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void KartDriver_TickAction_78778();
extern void KartDriver_TickAction_78a3c();
extern void KartDriver_TickAction_78d00();

/* --- function index (1 fns, .text 0x8009107C..0x80091284) ---
 * [  0] 0x8009107C size:0x208   global ItemEffectBus_Commit
 */

/* --- forward decls --- */
asm void ItemEffectBus_Commit(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_Commit[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_Commit = {
    (void *)&ItemEffectBus_Commit, 0x00000208, (void *)extab_ItemEffectBus_Commit
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_Commit(void) { /* 0x8009107C size:0x208 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    li r0, 0x0
    stw r31, 0x1c(r1)
    mr r31, r5
    and r5, r31, r0
    stw r30, 0x18(r1)
    mr r30, r6
    lis r6, 0x4
    and r4, r30, r6
    stw r29, 0x14(r1)
    mr r29, r3
    xor r3, r5, r0
    xor r4, r4, r0
    or. r3, r4, r3
    beq ItemEffectBus_Commit_L_800910F0
    lwz r3, 0x10(r29)
    lwz r5, 0x14(r29)
    and r4, r3, r0
    and r3, r5, r6
    xor r3, r3, r0
    xor r0, r4, r0
    or. r0, r3, r0
    bne ItemEffectBus_Commit_L_80091260
    lwz r3, 0x0(r29)
    li r4, 0x2
    bl KartDriver_TickAction_78d00
    b ItemEffectBus_Commit_L_80091260
    ItemEffectBus_Commit_L_800910F0:
    li r6, 0x20
    xor r3, r5, r0
    and r4, r30, r6
    xor r4, r4, r0
    or. r3, r4, r3
    beq ItemEffectBus_Commit_L_80091154
    lwz r3, 0x10(r29)
    lwz r5, 0x14(r29)
    and r4, r3, r0
    and r3, r5, r6
    xor r3, r3, r0
    xor r0, r4, r0
    or. r0, r3, r0
    bne ItemEffectBus_Commit_L_80091260
    lwz r0, 0x2c(r29)
    cmpwi r0, 0x1
    bne ItemEffectBus_Commit_L_80091144
    lwz r3, 0x0(r29)
    li r4, 0x3
    bl KartDriver_TickAction_78a3c
    b ItemEffectBus_Commit_L_80091260
    ItemEffectBus_Commit_L_80091144:
    lwz r3, 0x0(r29)
    li r4, 0x3
    bl KartDriver_TickAction_78778
    b ItemEffectBus_Commit_L_80091260
    ItemEffectBus_Commit_L_80091154:
    li r6, 0x8
    xor r3, r5, r0
    and r4, r30, r6
    xor r4, r4, r0
    or. r3, r4, r3
    beq ItemEffectBus_Commit_L_8009119C
    lwz r3, 0x10(r29)
    lwz r5, 0x14(r29)
    and r4, r3, r0
    and r3, r5, r6
    xor r3, r3, r0
    xor r0, r4, r0
    or. r0, r3, r0
    bne ItemEffectBus_Commit_L_80091260
    lwz r3, 0x0(r29)
    li r4, 0x0
    bl KartDriver_TickAction_78d00
    b ItemEffectBus_Commit_L_80091260
    ItemEffectBus_Commit_L_8009119C:
    li r6, 0x10
    xor r3, r5, r0
    and r4, r30, r6
    xor r4, r4, r0
    or. r3, r4, r3
    beq ItemEffectBus_Commit_L_800911E4
    lwz r3, 0x10(r29)
    lwz r5, 0x14(r29)
    and r4, r3, r0
    and r3, r5, r6
    xor r3, r3, r0
    xor r0, r4, r0
    or. r0, r3, r0
    bne ItemEffectBus_Commit_L_80091260
    lwz r3, 0x0(r29)
    li r4, 0x1
    bl KartDriver_TickAction_78d00
    b ItemEffectBus_Commit_L_80091260
    ItemEffectBus_Commit_L_800911E4:
    lis r6, 0x40
    xor r3, r5, r0
    and r4, r30, r6
    xor r4, r4, r0
    or. r3, r4, r3
    beq ItemEffectBus_Commit_L_8009122C
    lwz r3, 0x10(r29)
    lwz r5, 0x14(r29)
    and r4, r3, r0
    and r3, r5, r6
    xor r3, r3, r0
    xor r0, r4, r0
    or. r0, r3, r0
    bne ItemEffectBus_Commit_L_80091260
    lwz r3, 0x0(r29)
    li r4, 0x4
    bl KartDriver_TickAction_78d00
    b ItemEffectBus_Commit_L_80091260
    ItemEffectBus_Commit_L_8009122C:
    lwz r4, 0x10(r29)
    lis r3, 0x44
    lwz r5, 0x14(r29)
    addi r3, r3, 0x38
    and r4, r4, r0
    and r3, r5, r3
    xor r3, r3, r0
    xor r0, r4, r0
    or. r0, r3, r0
    beq ItemEffectBus_Commit_L_80091260
    lwz r3, 0x0(r29)
    li r4, 0x0
    bl KartDriver_TickAction_78d00
    ItemEffectBus_Commit_L_80091260:
    stw r30, 0x14(r29)
    stw r31, 0x10(r29)
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

/* Contiguous incumbent dtor at 0x80091284; folded into this TU so the
 * promoted split remains a single uninterrupted .text range. */
extern void MemoryManager_TimedFree(void *this);
asm void dtor_80091284(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_dtor_80091284[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_dtor_80091284 = {
    (void *)&dtor_80091284, 0x0000003C, (void *)extab_dtor_80091284
};

asm void dtor_80091284(void) { /* 0x80091284 size:0x3C */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr. r31, r3
    beq dtor_80091284_L_800912A8
    extsh. r0, r4
    ble dtor_80091284_L_800912A8
    bl MemoryManager_TimedFree
    dtor_80091284_L_800912A8:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_03_800912C0_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D34B0;

/* --- function index (1 fns, .text 0x800912C0..0x80091300) ---
 * [  0] 0x800912C0 size:0x40    global ItemEffectBus_Init
 */

/* --- forward decls --- */
asm void ItemEffectBus_Init(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_Init(void) { /* 0x800912C0 size:0x40 */
    nofralloc
    stw r4, 0x0(r3)
    li r0, 0x0
    lfs f0, lbl_806D34B0(r2)
    stb r0, 0x4(r3)
    stw r0, 0x8(r3)
    stw r0, 0x14(r3)
    stw r0, 0x10(r3)
    stw r0, 0x1c(r3)
    stw r0, 0x18(r3)
    stb r0, 0x20(r3)
    stfs f0, 0x24(r3)
    stfs f0, 0x28(r3)
    stfs f0, 0x48(r3)
    stw r0, 0x4c(r3)
    stw r0, 0x50(r3)
    blr
}

/* === extracted from auto_ItemEffectBus_ClearB_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D34B8;
extern unsigned int lbl_806D34BC;
extern unsigned int lbl_806D34C0;
extern unsigned int lbl_806D34C4;
extern unsigned int lbl_806D34C8;
extern unsigned int lbl_806D34CC;
extern unsigned int lbl_806D34D0;
extern unsigned int lbl_806D34D4;
extern unsigned int lbl_806D34D8;
extern unsigned int lbl_806D34DC;
extern unsigned int lbl_806D34E0;
extern unsigned int lbl_806D34E4;
extern unsigned int lbl_806D34E8;
extern unsigned int lbl_806D34EC;
extern unsigned int lbl_806D34F0;
extern unsigned int lbl_806D34F4;

/* --- function index (1 fns, .text 0x80091300..0x800913F8) ---
 * [  0] 0x80091300 size:0xF8    global ItemEffectBus_ClearByTable8
 */

/* --- forward decls --- */
asm void ItemEffectBus_ClearByTable8(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_ClearByTable8[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_ClearByTable8 = {
    (void *)&ItemEffectBus_ClearByTable8, 0x000000F8, (void *)extab_ItemEffectBus_ClearByTable8
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_ClearByTable8(void) { /* 0x80091300 size:0xF8 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r7, 0x0
    li r6, 0x0
    stw r0, 0x14(r1)
    clrlwi. r0, r4, 31
    beq ItemEffectBus_ClearByTable8_L_80091324
    lwz r6, lbl_806D34B8(r2)
    lwz r7, lbl_806D34BC(r2)
    ItemEffectBus_ClearByTable8_L_80091324:
    rlwinm. r0, r4, 0, 30, 30
    beq ItemEffectBus_ClearByTable8_L_8009133C
    lwz r0, lbl_806D34C0(r2)
    lwz r5, lbl_806D34C4(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_8009133C:
    rlwinm. r0, r4, 0, 29, 29
    beq ItemEffectBus_ClearByTable8_L_80091354
    lwz r0, lbl_806D34C8(r2)
    lwz r5, lbl_806D34CC(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_80091354:
    rlwinm. r0, r4, 0, 28, 28
    beq ItemEffectBus_ClearByTable8_L_8009136C
    lwz r0, lbl_806D34D0(r2)
    lwz r5, lbl_806D34D4(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_8009136C:
    rlwinm. r0, r4, 0, 27, 27
    beq ItemEffectBus_ClearByTable8_L_80091384
    lwz r0, lbl_806D34D8(r2)
    lwz r5, lbl_806D34DC(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_80091384:
    rlwinm. r0, r4, 0, 26, 26
    beq ItemEffectBus_ClearByTable8_L_8009139C
    lwz r0, lbl_806D34E0(r2)
    lwz r5, lbl_806D34E4(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_8009139C:
    rlwinm. r0, r4, 0, 25, 25
    beq ItemEffectBus_ClearByTable8_L_800913B4
    lwz r0, lbl_806D34E8(r2)
    lwz r5, lbl_806D34EC(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_800913B4:
    rlwinm. r0, r4, 0, 24, 24
    beq ItemEffectBus_ClearByTable8_L_800913CC
    lwz r0, lbl_806D34F0(r2)
    lwz r4, lbl_806D34F4(r2)
    or r6, r6, r0
    or r7, r7, r4
    ItemEffectBus_ClearByTable8_L_800913CC:
    nor r0, r6, r6
    lwz r5, 0x10(r3)
    lwz r6, 0x14(r3)
    nor r4, r7, r7
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_Regist_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- function index (1 fns, .text 0x800913F8..0x80091438) ---
 * [  0] 0x800913F8 size:0x40    global ItemEffectBus_RegisterBonkPosition
 */

/* --- forward decls --- */
asm void ItemEffectBus_RegisterBonkPosition(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_RegisterBonkPosition[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_RegisterBonkPosition = {
    (void *)&ItemEffectBus_RegisterBonkPosition, 0x00000040, (void *)extab_ItemEffectBus_RegisterBonkPosition
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_RegisterBonkPosition(void) { /* 0x800913F8 size:0x40 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    li r0, 0x1
    stfs f1, 0x3c(r3)
    stfs f2, 0x40(r3)
    stfs f3, 0x44(r3)
    stb r0, 0x4(r3)
    lwz r0, 0x10(r3)
    lwz r6, 0x14(r3)
    ori r5, r0, 0x1
    bl ItemEffectBus_Commit
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_ApplyI_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D34B0;
extern unsigned int lbl_806D34B8;
extern unsigned int lbl_806D34BC;
extern unsigned int lbl_806D34C0;
extern unsigned int lbl_806D34C4;
extern unsigned int lbl_806D34C8;
extern unsigned int lbl_806D34CC;
extern unsigned int lbl_806D34D0;
extern unsigned int lbl_806D34D4;
extern unsigned int lbl_806D34D8;
extern unsigned int lbl_806D34DC;
extern unsigned int lbl_806D34E0;
extern unsigned int lbl_806D34E4;
extern unsigned int lbl_806D34E8;
extern unsigned int lbl_806D34EC;
extern unsigned int lbl_806D34F0;
extern unsigned int lbl_806D34F4;
extern unsigned int lbl_806D34F8;
extern unsigned int lbl_806D34FC;
extern unsigned int lbl_806D3500;
extern unsigned int lbl_806D3504;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_803FF4E0[];

/* --- function index (1 fns, .text 0x80091438..0x8009185C) ---
 * [  0] 0x80091438 size:0x424   global ItemEffectBus_ApplyItemEventClear
 */

/* --- forward decls --- */
asm void ItemEffectBus_ApplyItemEventClear(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_ApplyItemEventClear[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_ApplyItemEventClear = {
    (void *)&ItemEffectBus_ApplyItemEventClear, 0x00000424, (void *)extab_ItemEffectBus_ApplyItemEventClear
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_ApplyItemEventClear(void) { /* 0x80091438 size:0x424 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f0, lbl_806D34B0(r2)
    cmplwi r4, 0x121
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    li r31, 0x0
    stw r30, 0x8(r1)
    mr r30, r3
    stfs f0, 0x28(r3)
    bgt ItemEffectBus_ApplyItemEventClear_L_80091844
    lis r5, jumptable_803FF4E0@ha
    slwi r0, r4, 2
    addi r4, r5, jumptable_803FF4E0@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    lwz r31, lbl_806D34F8(r2)
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r31, lbl_806D34FC(r2)
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r31, lbl_806D3500(r2)
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r3, 0x0(r30)
    li r4, 0x0
    lwz r31, lbl_806D3500(r2)
    stb r4, 0x2b1(r3)
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lfs f0, lbl_806D34B0(r2)
    lwz r31, lbl_806D3504(r2)
    stfs f0, 0x28(r30)
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xff80
    lwz r5, 0x10(r30)
    li r0, -0x1
    lwz r6, 0x14(r30)
    subi r4, r4, 0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r4, 0x10(r30)
    li r0, -0x1
    lwz r6, 0x14(r30)
    and r5, r4, r0
    and r6, r6, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xc000
    lwz r5, 0x10(r30)
    li r0, -0x1
    lwz r6, 0x14(r30)
    subi r4, r4, 0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x11
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x9
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x9
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x21
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x1001
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xfffe
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xfffc
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xfff8
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xfff0
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xffe0
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x41
    lwz r6, 0x14(r30)
    li r4, -0x1
    mr r3, r30
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xffff
    lwz r5, 0x10(r30)
    addi r0, r4, 0x7fff
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x4001
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xffff
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xfc00
    lwz r5, 0x10(r30)
    subi r0, r4, 0x2001
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x401
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x801
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    b ItemEffectBus_ApplyItemEventClear_L_80091844
    ItemEffectBus_ApplyItemEventClear_L_80091764:
    clrlwi. r3, r31, 31
    li r0, 0x0
    mr r6, r0
    beq ItemEffectBus_ApplyItemEventClear_L_8009177C
    lwz r6, lbl_806D34B8(r2)
    lwz r0, lbl_806D34BC(r2)
    ItemEffectBus_ApplyItemEventClear_L_8009177C:
    rlwinm. r3, r31, 0, 30, 30
    beq ItemEffectBus_ApplyItemEventClear_L_80091794
    lwz r3, lbl_806D34C0(r2)
    lwz r4, lbl_806D34C4(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_80091794:
    rlwinm. r3, r31, 0, 29, 29
    beq ItemEffectBus_ApplyItemEventClear_L_800917AC
    lwz r3, lbl_806D34C8(r2)
    lwz r4, lbl_806D34CC(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_800917AC:
    rlwinm. r3, r31, 0, 28, 28
    beq ItemEffectBus_ApplyItemEventClear_L_800917C4
    lwz r3, lbl_806D34D0(r2)
    lwz r4, lbl_806D34D4(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_800917C4:
    rlwinm. r3, r31, 0, 27, 27
    beq ItemEffectBus_ApplyItemEventClear_L_800917DC
    lwz r3, lbl_806D34D8(r2)
    lwz r4, lbl_806D34DC(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_800917DC:
    rlwinm. r3, r31, 0, 26, 26
    beq ItemEffectBus_ApplyItemEventClear_L_800917F4
    lwz r3, lbl_806D34E0(r2)
    lwz r4, lbl_806D34E4(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_800917F4:
    rlwinm. r3, r31, 0, 25, 25
    beq ItemEffectBus_ApplyItemEventClear_L_8009180C
    lwz r3, lbl_806D34E8(r2)
    lwz r4, lbl_806D34EC(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_8009180C:
    rlwinm. r3, r31, 0, 24, 24
    beq ItemEffectBus_ApplyItemEventClear_L_80091824
    lwz r3, lbl_806D34F0(r2)
    lwz r4, lbl_806D34F4(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_80091824:
    lwz r5, 0x10(r30)
    nor r4, r6, r6
    lwz r6, 0x14(r30)
    nor r0, r0, r0
    mr r3, r30
    and r5, r5, r4
    and r6, r6, r0
    bl ItemEffectBus_Commit
    ItemEffectBus_ApplyItemEventClear_L_80091844:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_ApplyI_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_803FF968[];

/* --- function index (1 fns, .text 0x8009185C..0x80091AC4) ---
 * [  0] 0x8009185C size:0x268   global ItemEffectBus_ApplyItemEventSet
 */

/* --- forward decls --- */
asm void ItemEffectBus_ApplyItemEventSet(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_ApplyItemEventSet[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_ApplyItemEventSet = {
    (void *)&ItemEffectBus_ApplyItemEventSet, 0x00000268, (void *)extab_ItemEffectBus_ApplyItemEventSet
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_ApplyItemEventSet(void) { /* 0x8009185C size:0x268 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r6, 0x9000
    stw r0, 0x24(r1)
    subi r0, r6, 0x1
    li r6, -0x1
    stw r31, 0x1c(r1)
    li r31, 0x0
    stw r30, 0x18(r1)
    li r30, 0x0
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr r28, r3
    stw r5, 0x2c(r3)
    lwz r4, 0x10(r3)
    lwz r7, 0x14(r3)
    and r5, r4, r0
    and r6, r7, r6
    bl ItemEffectBus_Commit
    cmplwi r29, 0x121
    bgt ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r3, jumptable_803FF968@ha
    slwi r0, r29, 2
    addi r3, r3, jumptable_803FF968@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    li r30, 0x0
    li r31, 0x20
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    lis r31, 0x4
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    lis r31, 0x8
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    lis r31, 0x10
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    lis r31, 0x20
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r30, 0x8
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    lis r31, 0x200
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    li r31, 0x10
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    li r31, 0x8
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    li r31, 0x8
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x2
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x20
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x20
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x20
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x8
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x10
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x200
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x800
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x800
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r30, 0x4
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r30, 0x20
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r30, 0x40
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r30, 0x10
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r30, 0x800
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    li r31, 0x40
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    li r31, 0x2
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    li r31, 0x4
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r30, 0x80
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    li r31, 0x1000
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r30, 0x2
    lis r31, 0x100
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    lis r31, 0x100
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    li r31, 0x800
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r30, 0x4000
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x0
    lis r31, 0x2
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    li r30, 0x2000
    li r31, 0x0
    b ItemEffectBus_ApplyItemEventSet_L_80091A84
    lis r30, 0x200
    li r31, 0x0
    ItemEffectBus_ApplyItemEventSet_L_80091A84:
    lwz r0, 0x10(r28)
    mr r3, r28
    lwz r4, 0x14(r28)
    or r31, r31, r0
    or r30, r30, r4
    mr r6, r30
    mr r5, r31
    bl ItemEffectBus_Commit
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

/* === extracted from auto_ItemEffectBus_ArmTor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- function index (1 fns, .text 0x80091AC4..0x80091B9C) ---
 * [  0] 0x80091AC4 size:0xD8    global ItemEffectBus_ArmTornadoAndQuery
 */

/* --- forward decls --- */
asm void ItemEffectBus_ArmTornadoAndQuery(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_ArmTornadoAndQuery[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_ArmTornadoAndQuery = {
    (void *)&ItemEffectBus_ArmTornadoAndQuery, 0x000000D8, (void *)extab_ItemEffectBus_ArmTornadoAndQuery
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_ArmTornadoAndQuery(void) { /* 0x80091AC4 size:0xD8 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, 0x1
    stw r0, 0x14(r1)
    li r0, 0x1
    stw r31, 0xc(r1)
    mr r31, r3
    stw r0, 0x50(r3)
    addi r0, r4, 0x1
    lwz r4, 0x14(r3)
    lwz r5, 0x10(r3)
    or r6, r4, r0
    bl ItemEffectBus_Commit
    lwz r6, 0x10(r31)
    li r5, 0x0
    lwz r7, 0x14(r31)
    li r0, 0x40
    and r4, r6, r5
    and r0, r7, r0
    xor r3, r0, r5
    xor r0, r4, r5
    or. r0, r3, r0
    beq ItemEffectBus_ArmTornadoAndQuery_L_80091B28
    li r3, 0x0
    b ItemEffectBus_ArmTornadoAndQuery_L_80091B88
    ItemEffectBus_ArmTornadoAndQuery_L_80091B28:
    li r3, 0x400
    xor r0, r4, r5
    and r3, r7, r3
    xor r3, r3, r5
    or. r0, r3, r0
    beq ItemEffectBus_ArmTornadoAndQuery_L_80091B48
    li r3, 0x0
    b ItemEffectBus_ArmTornadoAndQuery_L_80091B88
    ItemEffectBus_ArmTornadoAndQuery_L_80091B48:
    li r3, 0x80
    xor r0, r4, r5
    and r3, r7, r3
    xor r3, r3, r5
    or. r0, r3, r0
    beq ItemEffectBus_ArmTornadoAndQuery_L_80091B68
    li r3, 0x0
    b ItemEffectBus_ArmTornadoAndQuery_L_80091B88
    ItemEffectBus_ArmTornadoAndQuery_L_80091B68:
    lis r3, 0x100
    and r0, r7, r5
    and r3, r6, r3
    xor r0, r0, r5
    xor r3, r3, r5
    or r3, r0, r3
    cntlzw r3, r3
    srwi r3, r3, 5
    ItemEffectBus_ArmTornadoAndQuery_L_80091B88:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_ApplyI_text_2 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D3508;
extern unsigned int lbl_806D350C;
extern unsigned int lbl_806D3510;
extern unsigned int lbl_806D3514;
extern unsigned int lbl_806D3518;
extern unsigned int lbl_806D351C;
extern unsigned int lbl_806D3520;
extern unsigned int lbl_806D3524;
extern unsigned int lbl_806D3528;
extern unsigned int lbl_806D352C;
extern unsigned int lbl_806D3530;
extern unsigned int lbl_806D3534;
extern unsigned int lbl_806D3538;
extern unsigned int lbl_806D353C;
extern unsigned int lbl_806D3540;
extern unsigned int lbl_806D3544;
extern unsigned int lbl_806D3548;
extern unsigned int lbl_806D354C;
extern unsigned int lbl_806D3550;
extern unsigned int lbl_806D3554;
extern unsigned int lbl_806D3558;
extern unsigned int lbl_806D355C;
extern unsigned int lbl_806D3560;
extern unsigned int lbl_806D3564;
extern unsigned int lbl_806D3568;
extern unsigned int lbl_806D356C;

/* --- function index (1 fns, .text 0x80091B9C..0x80091E40) ---
 * [  0] 0x80091B9C size:0x2A4   global ItemEffectBus_ApplyItemConfirm
 */

/* --- forward decls --- */
asm void ItemEffectBus_ApplyItemConfirm(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_ApplyItemConfirm[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_ApplyItemConfirm = {
    (void *)&ItemEffectBus_ApplyItemConfirm, 0x000002A4, (void *)extab_ItemEffectBus_ApplyItemConfirm
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_ApplyItemConfirm(void) { /* 0x80091B9C size:0x2A4 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r4, 0x28
    stw r0, 0x14(r1)
    lwz r5, 0x10(r3)
    lwz r6, 0x14(r3)
    beq ItemEffectBus_ApplyItemConfirm_L_80091DAC
    bge ItemEffectBus_ApplyItemConfirm_L_80091C60
    cmpwi r4, 0x19
    beq ItemEffectBus_ApplyItemConfirm_L_80091E2C
    bge ItemEffectBus_ApplyItemConfirm_L_80091C18
    cmpwi r4, 0x11
    beq ItemEffectBus_ApplyItemConfirm_L_80091DD8
    bge ItemEffectBus_ApplyItemConfirm_L_80091BF8
    cmpwi r4, 0xe
    beq ItemEffectBus_ApplyItemConfirm_L_80091DAC
    bge ItemEffectBus_ApplyItemConfirm_L_80091BEC
    cmpwi r4, 0xc
    bge ItemEffectBus_ApplyItemConfirm_L_80091DD8
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091BEC:
    cmpwi r4, 0x10
    bge ItemEffectBus_ApplyItemConfirm_L_80091DAC
    b ItemEffectBus_ApplyItemConfirm_L_80091DD8
    ItemEffectBus_ApplyItemConfirm_L_80091BF8:
    cmpwi r4, 0x17
    beq ItemEffectBus_ApplyItemConfirm_L_80091E2C
    bge ItemEffectBus_ApplyItemConfirm_L_80091DD8
    cmpwi r4, 0x15
    bge ItemEffectBus_ApplyItemConfirm_L_80091DAC
    cmpwi r4, 0x13
    bge ItemEffectBus_ApplyItemConfirm_L_80091DD8
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091C18:
    cmpwi r4, 0x21
    beq ItemEffectBus_ApplyItemConfirm_L_80091DC0
    bge ItemEffectBus_ApplyItemConfirm_L_80091C48
    cmpwi r4, 0x1c
    beq ItemEffectBus_ApplyItemConfirm_L_80091DCC
    bge ItemEffectBus_ApplyItemConfirm_L_80091C3C
    cmpwi r4, 0x1b
    bge ItemEffectBus_ApplyItemConfirm_L_80091D0C
    b ItemEffectBus_ApplyItemConfirm_L_80091D84
    ItemEffectBus_ApplyItemConfirm_L_80091C3C:
    cmpwi r4, 0x1e
    bge ItemEffectBus_ApplyItemConfirm_L_80091DAC
    b ItemEffectBus_ApplyItemConfirm_L_80091D70
    ItemEffectBus_ApplyItemConfirm_L_80091C48:
    cmpwi r4, 0x24
    beq ItemEffectBus_ApplyItemConfirm_L_80091DAC
    bge ItemEffectBus_ApplyItemConfirm_L_80091DD8
    cmpwi r4, 0x23
    bge ItemEffectBus_ApplyItemConfirm_L_80091D48
    b ItemEffectBus_ApplyItemConfirm_L_80091CF8
    ItemEffectBus_ApplyItemConfirm_L_80091C60:
    cmpwi r4, 0x91
    beq ItemEffectBus_ApplyItemConfirm_L_80091DD8
    bge ItemEffectBus_ApplyItemConfirm_L_80091CA8
    cmpwi r4, 0x52
    beq ItemEffectBus_ApplyItemConfirm_L_80091D5C
    bge ItemEffectBus_ApplyItemConfirm_L_80091C90
    cmpwi r4, 0x3c
    beq ItemEffectBus_ApplyItemConfirm_L_80091D34
    bge ItemEffectBus_ApplyItemConfirm_L_80091E2C
    cmpwi r4, 0x2c
    beq ItemEffectBus_ApplyItemConfirm_L_80091D20
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091C90:
    cmpwi r4, 0x8c
    beq ItemEffectBus_ApplyItemConfirm_L_80091E08
    bge ItemEffectBus_ApplyItemConfirm_L_80091E2C
    cmpwi r4, 0x8b
    bge ItemEffectBus_ApplyItemConfirm_L_80091DD8
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091CA8:
    cmpwi r4, 0x9c
    beq ItemEffectBus_ApplyItemConfirm_L_80091E2C
    bge ItemEffectBus_ApplyItemConfirm_L_80091CCC
    cmpwi r4, 0x9a
    beq ItemEffectBus_ApplyItemConfirm_L_80091DF4
    bge ItemEffectBus_ApplyItemConfirm_L_80091D98
    cmpwi r4, 0x99
    bge ItemEffectBus_ApplyItemConfirm_L_80091DE0
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091CCC:
    cmpwi r4, 0x142
    beq ItemEffectBus_ApplyItemConfirm_L_80091CE4
    bge ItemEffectBus_ApplyItemConfirm_L_80091E2C
    cmpwi r4, 0x9e
    bge ItemEffectBus_ApplyItemConfirm_L_80091E2C
    b ItemEffectBus_ApplyItemConfirm_L_80091E1C
    ItemEffectBus_ApplyItemConfirm_L_80091CE4:
    lwz r0, lbl_806D3508(r2)
    lwz r4, lbl_806D350C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091CF8:
    lwz r0, lbl_806D3510(r2)
    lwz r4, lbl_806D3514(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D0C:
    lwz r0, lbl_806D3518(r2)
    lwz r4, lbl_806D351C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D20:
    lwz r0, lbl_806D3520(r2)
    lwz r4, lbl_806D3524(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D34:
    lwz r0, lbl_806D3528(r2)
    lwz r4, lbl_806D352C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D48:
    lwz r0, lbl_806D3530(r2)
    lwz r4, lbl_806D3534(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D5C:
    lwz r0, lbl_806D3538(r2)
    lwz r4, lbl_806D353C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D70:
    lwz r0, lbl_806D3540(r2)
    lwz r4, lbl_806D3544(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D84:
    lwz r0, lbl_806D3508(r2)
    lwz r4, lbl_806D350C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D98:
    lwz r0, lbl_806D3548(r2)
    lwz r4, lbl_806D354C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DAC:
    lis r4, 0x2000
    ori r5, r5, 0x100
    addi r0, r4, 0x40
    or r6, r6, r0
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DC0:
    li r6, 0x80
    li r5, 0x80
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DCC:
    li r6, 0x0
    li r5, 0x80
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DD8:
    ori r6, r6, 0x140
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DE0:
    lwz r0, lbl_806D3550(r2)
    lwz r4, lbl_806D3554(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DF4:
    lwz r0, lbl_806D3558(r2)
    lwz r4, lbl_806D355C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091E08:
    lwz r0, lbl_806D3560(r2)
    lwz r4, lbl_806D3564(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091E1C:
    lwz r0, lbl_806D3568(r2)
    lwz r4, lbl_806D356C(r2)
    or r5, r5, r0
    or r6, r6, r4
    ItemEffectBus_ApplyItemConfirm_L_80091E2C:
    bl ItemEffectBus_Commit
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_ClearM_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- function index (1 fns, .text 0x80091E40..0x80091E78) ---
 * [  0] 0x80091E40 size:0x38    global ItemEffectBus_ClearMask
 */

/* --- forward decls --- */
asm void ItemEffectBus_ClearMask(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_ClearMask[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_ClearMask = {
    (void *)&ItemEffectBus_ClearMask, 0x00000038, (void *)extab_ItemEffectBus_ClearMask
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_ClearMask(void) { /* 0x80091E40 size:0x38 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    nor r4, r6, r6
    stw r0, 0x14(r1)
    nor r0, r5, r5
    lwz r7, 0x10(r3)
    lwz r8, 0x14(r3)
    and r5, r7, r0
    and r6, r8, r4
    bl ItemEffectBus_Commit
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_OrMask_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- function index (1 fns, .text 0x80091E78..0x80091EA8) ---
 * [  0] 0x80091E78 size:0x30    global ItemEffectBus_OrMask
 */

/* --- forward decls --- */
asm void ItemEffectBus_OrMask(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_OrMask[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_OrMask = {
    (void *)&ItemEffectBus_OrMask, 0x00000030, (void *)extab_ItemEffectBus_OrMask
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_OrMask(void) { /* 0x80091E78 size:0x30 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r0, 0x10(r3)
    lwz r4, 0x14(r3)
    or r5, r5, r0
    or r6, r6, r4
    bl ItemEffectBus_Commit
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_TickTo_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D3570;
extern unsigned int lbl_806D3574;

/* --- function index (1 fns, .text 0x80091EA8..0x80091F0C) ---
 * [  0] 0x80091EA8 size:0x64    global ItemEffectBus_TickTornadoCooldown
 */

/* --- forward decls --- */
asm void ItemEffectBus_TickTornadoCooldown(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_TickTornadoCooldown[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_TickTornadoCooldown = {
    (void *)&ItemEffectBus_TickTornadoCooldown, 0x00000064, (void *)extab_ItemEffectBus_TickTornadoCooldown
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_TickTornadoCooldown(void) { /* 0x80091EA8 size:0x64 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r7, 0x0
    lis r6, 0xc000
    stw r0, 0x14(r1)
    lwz r4, 0x50(r3)
    cmpwi r4, 0x0
    ble ItemEffectBus_TickTornadoCooldown_L_80091ED4
    subi r0, r4, 0x1
    stw r0, 0x50(r3)
    b ItemEffectBus_TickTornadoCooldown_L_80091EE0
    ItemEffectBus_TickTornadoCooldown_L_80091ED4:
    lwz r0, lbl_806D3570(r2)
    lwz r7, lbl_806D3574(r2)
    or r6, r6, r0
    ItemEffectBus_TickTornadoCooldown_L_80091EE0:
    nor r0, r6, r6
    lwz r5, 0x10(r3)
    lwz r6, 0x14(r3)
    nor r4, r7, r7
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_Snapsh_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- function index (1 fns, .text 0x80091F0C..0x80091F58) ---
 * [  0] 0x80091F0C size:0x4C    global ItemEffectBus_SnapshotAndClearSpawnFlags
 */

/* --- forward decls --- */
asm void ItemEffectBus_SnapshotAndClearSpawnFlags(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_SnapshotAndClearSpawnFlags[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_SnapshotAndClearSpawnFlags = {
    (void *)&ItemEffectBus_SnapshotAndClearSpawnFlags, 0x0000004C, (void *)extab_ItemEffectBus_SnapshotAndClearSpawnFlags
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_SnapshotAndClearSpawnFlags(void) { /* 0x80091F0C size:0x4C */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, 0xffff
    stw r0, 0x14(r1)
    addi r4, r4, 0x3eff
    li r0, -0x1
    lwz r5, 0x10(r3)
    lwz r6, 0x14(r3)
    stw r6, 0x1c(r3)
    stw r5, 0x18(r3)
    lwz r5, 0x10(r3)
    lwz r6, 0x14(r3)
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_Snapsh_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemEffectBus_Commit();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D34B0;

/* --- function index (1 fns, .text 0x80091F58..0x80091FD4) ---
 * [  0] 0x80091F58 size:0x7C    global ItemEffectBus_SnapshotAndFullReset
 */

/* --- forward decls --- */
asm void ItemEffectBus_SnapshotAndFullReset(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_SnapshotAndFullReset[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_SnapshotAndFullReset = {
    (void *)&ItemEffectBus_SnapshotAndFullReset, 0x0000007C, (void *)extab_ItemEffectBus_SnapshotAndFullReset
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_SnapshotAndFullReset(void) { /* 0x80091F58 size:0x7C */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, 0x77ff
    lis r4, 0xfd80
    stw r0, 0x14(r1)
    subi r0, r4, 0x24
    addi r6, r5, 0x14fe
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r7, 0x10(r3)
    lwz r8, 0x14(r3)
    stw r8, 0x1c(r3)
    stw r7, 0x18(r3)
    lwz r4, 0x10(r3)
    lwz r7, 0x14(r3)
    and r5, r4, r0
    and r6, r7, r6
    bl ItemEffectBus_Commit
    li r0, 0x0
    lfs f0, lbl_806D34B0(r2)
    stw r0, 0x8(r31)
    stb r0, 0x4(r31)
    stb r0, 0x20(r31)
    stfs f0, 0x30(r31)
    stfs f0, 0x34(r31)
    stfs f0, 0x38(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

