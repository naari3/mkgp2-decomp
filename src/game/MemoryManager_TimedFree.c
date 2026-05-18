/* === extracted from MemoryManager_TimedFree === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf();
extern void OSFreeToHeap();
extern void OSGetTick();
extern void Profiler_RecordFrame();
extern void fn_8027248C();
extern void fn_80276D30();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806CF010;
extern unsigned int lbl_806D0FA1;
extern unsigned int lbl_806D24D8;
extern unsigned int lbl_806D24E0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802E9DB0[];
extern unsigned int lbl_802E9DD0[];

/* --- forward decls --- */
asm void MemoryManager_TimedFree(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void dtor_8002CCD8();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; void *f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; } extab_MemoryManager_TimedFree = { 0x101A0000, 0x00000028, 0x00000040, 0x00000050, 0x00070038, 0x0000007C, 0x00150040, 0x000000E0, 0x00000038, 0x000000E4, 0x00150040, 0x00000144, 0x0000004C, 0x00000000, 0x02000008, (void *)&dtor_8002CCD8, 0x8F000000, 0x0000013C, 0x00000010, 0x8D000010 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_MemoryManager_TimedFree = {
    (void *)&MemoryManager_TimedFree, 0x00000168, (void *)&extab_MemoryManager_TimedFree
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void MemoryManager_TimedFree(void) {
    nofralloc
    stwu r1, -0x240(r1)
    mflr r0
    stw r0, 0x244(r1)
    li r0, 0x13
    stw r31, 0x23c(r1)
    mr r31, r1
    stw r30, 0x238(r1)
    mr r30, r3
    stw r0, 0xc(r1)
    bl OSGetTick
    lbz r0, lbl_806D0FA1(r13)
    stw r3, 0x8(r31)
    cmplwi r0, 0x0
    bne MemoryManager_TimedFree_L_8003B028
    lis r4, lbl_802E9DD0@ha
    addi r3, r31, 0x28
    addi r5, r4, lbl_802E9DD0@l
    li r4, 0x200
    crxor 6, 6, 6
    bl fn_80276D30
    addi r3, r31, 0x28
    crxor 6, 6, 6
    bl DebugPrintf
    lis r3, lbl_802E9DB0@ha
    addi r3, r3, lbl_802E9DB0@l
    crxor 6, 6, 6
    bl DebugPrintf
    MemoryManager_TimedFree_L_8003B024:
    b MemoryManager_TimedFree_L_8003B024
    MemoryManager_TimedFree_L_8003B028:
    cmplwi r30, 0x0
    bne MemoryManager_TimedFree_L_8003B08C
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x8(r31)
    srwi r4, r5, 2
    stw r0, 0x228(r31)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D24E0(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D24D8(r2)
    lwz r3, 0xc(r31)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x22c(r31)
    lfd f1, 0x228(r31)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    b MemoryManager_TimedFree_L_8003B100
    MemoryManager_TimedFree_L_8003B08C:
    lwz r3, lbl_806CF010(r13)
    mr r4, r30
    bl OSFreeToHeap
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x8(r31)
    srwi r4, r5, 2
    stw r0, 0x228(r31)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D24E0(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D24D8(r2)
    lwz r3, 0xc(r31)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x22c(r31)
    lfd f1, 0x228(r31)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    b MemoryManager_TimedFree_L_8003B100
    addi r3, r31, 0x10
    bl fn_8027248C
    MemoryManager_TimedFree_L_8003B0FC:
    b MemoryManager_TimedFree_L_8003B0FC
    MemoryManager_TimedFree_L_8003B100:
    mr r10, r31
    lwz r31, 0x23c(r31)
    lwz r30, 0x238(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
}

