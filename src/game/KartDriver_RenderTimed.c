/* === extracted from auto_KartDriver_RenderTim_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void KartDriver_Render();
extern void OSGetTick();
extern void Profiler_RecordFrame();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D25E0;
extern unsigned int lbl_806D25E8;

/* --- function index (1 fns, .text 0x80042610..0x800426C8) ---
 * [  0] 0x80042610 size:0xB8    global KartDriver_RenderTimed
 */

/* --- forward decls --- */
asm void KartDriver_RenderTimed(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void __dt__11ScopedTimerFv();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_KartDriver_RenderTimed = { 0x180A0000, 0x00000044, 0x00000010, 0x00000000, 0x82000008, (void *)&__dt__11ScopedTimerFv };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_RenderTimed = {
    (void *)&KartDriver_RenderTimed, 0x000000B8, (void *)&extab_KartDriver_RenderTimed
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_RenderTimed(void) { /* 0x80042610 size:0xB8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    li r0, 0x17
    stw r31, 0x2c(r1)
    mr r31, r5
    stw r30, 0x28(r1)
    mr r30, r4
    stw r29, 0x24(r1)
    mr r29, r3
    stw r0, 0xc(r1)
    bl OSGetTick
    stw r3, 0x8(r1)
    mr r3, r29
    mr r4, r30
    mr r5, r31
    bl KartDriver_Render
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
    lfd f2, lbl_806D25E8(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D25E0(r2)
    lwz r3, 0xc(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x14(r1)
    lfd f1, 0x10(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


