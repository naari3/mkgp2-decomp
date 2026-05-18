/* === extracted from auto_FlowDispatcher_Creat_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void DebugLog_LvIdMsg();
extern void DebugPrintf();
extern void HeapStats_DumpForTag();
extern void MemoryManager_TimedFree();
extern void OSGetTick();
extern void Profiler_RecordFrame();
extern void SeqMenuScene_Init();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D0F80;
extern unsigned int lbl_806D2268;
extern unsigned int lbl_806D2280;
extern unsigned int lbl_806D2288;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802E8DBC[];

/* --- forward decls --- */
asm void FlowDispatcher_Create(void);
asm void __dt__11ScopedTimerFv(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab___dt__11ScopedTimerFv[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; void *f11; } extab_FlowDispatcher_Create = { 0x180A0000, 0x00000054, 0x00050028, 0x00000078, 0x00000020, 0x000000A8, 0x00230028, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001F, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_FlowDispatcher_Create = {
    (void *)&FlowDispatcher_Create, 0x00000158, (void *)&extab_FlowDispatcher_Create
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex___dt__11ScopedTimerFv = {
    (void *)&__dt__11ScopedTimerFv, 0x000000A4, (void *)extab___dt__11ScopedTimerFv
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void FlowDispatcher_Create(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr r29, r3
    lwz r0, lbl_806D0F80(r13)
    cmplwi r0, 0x0
    bne FlowDispatcher_Create_L_8002CCB8
    li r3, 0x38
    bl Alloc
    mr. r31, r3
    beq FlowDispatcher_Create_L_8002CCB4
    stw r29, 0x0(r31)
    lis r3, lbl_802E8DBC@ha
    addi r3, r3, lbl_802E8DBC@l
    stw r30, 0x4(r31)
    crxor 6, 6, 6
    bl DebugPrintf
    addi r3, r2, -0x7FFC  /* lbl_806D2264 */
    li r4, 0x0
    bl HeapStats_DumpForTag
    li r3, 0x14
    bl Alloc
    mr. r29, r3
    beq FlowDispatcher_Create_L_8002CBF8
    lwz r4, 0x0(r31)
    bl SeqMenuScene_Init
    FlowDispatcher_Create_L_8002CBF8:
    cmpwi r30, -0x4
    stw r29, 0x10(r31)
    bne FlowDispatcher_Create_L_8002CC10
    lwz r0, 0x10(r31)
    stw r0, 0x8(r31)
    b FlowDispatcher_Create_L_8002CC2C
    FlowDispatcher_Create_L_8002CC10:
    lwz r0, 0x4(r31)
    lwz r3, 0x0(r31)
    mulli r0, r0, 0xc
    lwzx r12, r3, r0
    mtctr r12
    bctrl
    stw r3, 0x8(r31)
    FlowDispatcher_Create_L_8002CC2C:
    li r0, 0x0
    stw r0, 0xc(r31)
    b FlowDispatcher_Create_L_8002CC44
    FlowDispatcher_Create_L_8002CC38:
    lwz r3, 0xc(r31)
    addi r0, r3, 0x1
    stw r0, 0xc(r31)
    FlowDispatcher_Create_L_8002CC44:
    lwz r0, 0xc(r31)
    lwz r3, 0x0(r31)
    mulli r0, r0, 0xc
    lwzx r0, r3, r0
    cmplwi r0, 0x0
    bne FlowDispatcher_Create_L_8002CC38
    li r0, 0x0
    lfs f0, lbl_806D2268(r2)
    stw r0, 0x14(r31)
    addi r3, r2, -0x7FFC  /* lbl_806D2264 */
    li r4, 0x0
    stfs f0, 0x24(r31)
    stfs f0, 0x28(r31)
    stfs f0, 0x2c(r31)
    stfs f0, 0x18(r31)
    stfs f0, 0x1c(r31)
    stfs f0, 0x20(r31)
    stw r0, 0x30(r31)
    stw r0, 0x34(r31)
    bl HeapStats_DumpForTag
    lis r3, lbl_802E8DBC@ha
    addi r3, r3, lbl_802E8DBC@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0x0
    li r4, 0x0
    addi r5, r2, -0x7FFC  /* lbl_806D2264 */
    bl DebugLog_LvIdMsg
    FlowDispatcher_Create_L_8002CCB4:
    stw r31, lbl_806D0F80(r13)
    FlowDispatcher_Create_L_8002CCB8:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r3, lbl_806D0F80(r13)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

asm void __dt__11ScopedTimerFv(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r4
    stw r30, 0x18(r1)
    mr. r30, r3
    beq __dt__11ScopedTimerFv_L_8002CD60
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x0(r30)
    srwi r4, r5, 2
    stw r0, 0x8(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D2288(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D2280(r2)
    lwz r3, 0x4(r30)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0xc(r1)
    lfd f1, 0x8(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    extsh. r0, r31
    ble __dt__11ScopedTimerFv_L_8002CD60
    mr r3, r30
    bl MemoryManager_TimedFree
    __dt__11ScopedTimerFv_L_8002CD60:
    lwz r0, 0x24(r1)
    mr r3, r30
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

