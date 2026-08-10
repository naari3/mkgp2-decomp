/* === extracted from auto_ItemObjectManager_Re_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemObjectManager_RenderImpl();
extern void OSGetTick();
extern void Profiler_RecordFrame();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5A94;
extern unsigned int lbl_806D5A98;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80638300[];

/* --- function index (1 fns, .text 0x800D802C..0x800D80BC) ---
 * [  0] 0x800D802C size:0x90    global ItemObjectManager_Render
 */

/* --- forward decls --- */
asm void ItemObjectManager_Render(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void __dt__11ScopedTimerFv();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_ItemObjectManager_Render = { 0x000A0000, 0x00000028, 0x00000010, 0x00000000, 0x82000008, (void *)&__dt__11ScopedTimerFv };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemObjectManager_Render = {
    (void *)&ItemObjectManager_Render, 0x00000090, (void *)&extab_ItemObjectManager_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemObjectManager_Render(void) { /* 0x800D802C size:0x90 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    li r0, 0x1d
    stw r0, 0xc(r1)
    bl OSGetTick
    lis r4, lbl_80638300@ha
    stw r3, 0x8(r1)
    addi r3, r4, lbl_80638300@l
    bl ItemObjectManager_RenderImpl
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
    lfd f2, lbl_806D5A98(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D5A94(r2)
    lwz r3, 0xc(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x14(r1)
    lfd f1, 0x10(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


/* === extracted from auto_ItemObjectManager_Re_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AnimStatePool_FreeAll();
extern void Object_DtorWithGXSync();
extern void SpriteSlot_Destroy();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80638300[];

/* --- function index (1 fns, .text 0x800D80BC..0x800D8150) ---
 * [  0] 0x800D80BC size:0x94    global ItemObjectManager_Reset
 */

/* --- forward decls --- */
asm void ItemObjectManager_Reset(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemObjectManager_Reset[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemObjectManager_Reset = {
    (void *)&ItemObjectManager_Reset, 0x00000094, (void *)extab_ItemObjectManager_Reset
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemObjectManager_Reset(void) { /* 0x800D80BC size:0x94 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r3, lbl_80638300@ha
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    li r30, 0x0
    mr r31, r30
    stw r29, 0x14(r1)
    addi r29, r3, lbl_80638300@l
    ItemObjectManager_Reset_L_800D80E4:
    cmplwi r29, 0x0
    beq ItemObjectManager_Reset_L_800D80F8
    addi r3, r29, 0x14
    bl SpriteSlot_Destroy
    stb r31, 0x0(r29)
    ItemObjectManager_Reset_L_800D80F8:
    addi r30, r30, 0x1
    addi r29, r29, 0x1ec
    cmpwi r30, 0x100
    blt ItemObjectManager_Reset_L_800D80E4
    lis r3, lbl_80638300@ha
    addi r3, r3, lbl_80638300@l
    addis r29, r3, 0x2
    lwz r3, -0x1400(r29)
    cmplwi r3, 0x0
    beq ItemObjectManager_Reset_L_800D8128
    li r4, 0x1
    bl Object_DtorWithGXSync
    ItemObjectManager_Reset_L_800D8128:
    li r0, 0x0
    stw r0, -0x1400(r29)
    bl AnimStatePool_FreeAll
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


/* === extracted from auto_ItemObjectManager_Up_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemObjectManager_TickActiveItems();
extern void OSGetTick();
extern void Profiler_RecordFrame();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5A94;
extern unsigned int lbl_806D5A98;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80638300[];

/* --- function index (1 fns, .text 0x800D8150..0x800D81E0) ---
 * [  0] 0x800D8150 size:0x90    global ItemObjectManager_Update
 */

/* --- forward decls --- */
asm void ItemObjectManager_Update(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void __dt__11ScopedTimerFv();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_ItemObjectManager_Update = { 0x000A0000, 0x00000028, 0x00000010, 0x00000000, 0x82000008, (void *)&__dt__11ScopedTimerFv };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemObjectManager_Update = {
    (void *)&ItemObjectManager_Update, 0x00000090, (void *)&extab_ItemObjectManager_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemObjectManager_Update(void) { /* 0x800D8150 size:0x90 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    li r0, 0x1c
    stw r0, 0xc(r1)
    bl OSGetTick
    lis r4, lbl_80638300@ha
    stw r3, 0x8(r1)
    addi r3, r4, lbl_80638300@l
    bl ItemObjectManager_TickActiveItems
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
    lfd f2, lbl_806D5A98(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D5A94(r2)
    lwz r3, 0xc(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x14(r1)
    lfd f1, 0x10(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


