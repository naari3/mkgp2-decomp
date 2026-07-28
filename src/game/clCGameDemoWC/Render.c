/* === extracted from auto_clCGameDemoWC_Render_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_DebugVizPathFlush();
extern void DrawEffect_TickAndCull();
extern void ItemObjectManager_Render();
extern void KartDriver_RenderTimed();
extern void Object_RenderJObjTree();
extern void TransparentDraw_SortAndDispatch();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void fn_8016B0C4();
extern void fn_80181790();
extern void fn_802C14B8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D4F90;
extern unsigned int lbl_806D4F94;
extern unsigned int lbl_806D4F98;
extern unsigned int lbl_806D4F9C;
extern unsigned int lbl_806D4FA0;
extern unsigned int lbl_806D4FA4;

/* --- function index (1 fns, .text 0x800ADF58..0x800AE108) ---
 * [  0] 0x800ADF58 size:0x1B0   global clCGameDemoWC_Render
 */

/* --- forward decls --- */
asm void clCGameDemoWC_Render(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clCGameDemoWC_Render[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clCGameDemoWC_Render = {
    (void *)&clCGameDemoWC_Render, 0x000001B0, (void *)extab_clCGameDemoWC_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clCGameDemoWC_Render(void) { /* 0x800ADF58 size:0x1B0 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    lwz r3, 0xc(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clCGameDemoWC_Render_L_800AE0F4
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne clCGameDemoWC_Render_L_800ADF9C
    li r3, 0x0
    clCGameDemoWC_Render_L_800ADF9C:
    bl clDrawMan_Buckets_Reset
    bl TransparentDraw_SortAndDispatch
    lwz r3, 0xc(r31)
    bl CObj_DebugVizPathFlush
    bl fn_8016B0C4
    lwz r3, 0x14(r31)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0x18(r31)
    li r4, 0x0
    li r5, 0x1
    bl KartDriver_RenderTimed
    lwz r3, 0x58(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    bl ItemObjectManager_Render
    bl DrawEffect_TickAndCull
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne clCGameDemoWC_Render_L_800ADFF8
    li r3, 0x0
    clCGameDemoWC_Render_L_800ADFF8:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne clCGameDemoWC_Render_L_800AE00C
    li r3, 0x0
    clCGameDemoWC_Render_L_800AE00C:
    bl clDrawMan_Buckets_Dispatch
    lfs f2, 0x8(r31)
    li r7, 0x0
    lfs f0, lbl_806D4F90(r2)
    fcmpo cr0, f2, f0
    bge clCGameDemoWC_Render_L_800AE060
    fdivs f0, f2, f0
    lfs f1, lbl_806D4F94(r2)
    fcmpo cr0, f0, f1
    bge clCGameDemoWC_Render_L_800AE038
    b clCGameDemoWC_Render_L_800AE04C
    clCGameDemoWC_Render_L_800AE038:
    lfs f1, lbl_806D4F98(r2)
    fcmpo cr0, f0, f1
    ble clCGameDemoWC_Render_L_800AE048
    b clCGameDemoWC_Render_L_800AE04C
    clCGameDemoWC_Render_L_800AE048:
    fmr f1, f0
    clCGameDemoWC_Render_L_800AE04C:
    lfs f0, lbl_806D4F9C(r2)
    fnmsubs f0, f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r7, 0xc(r1)
    clCGameDemoWC_Render_L_800AE060:
    lfs f0, lbl_806D4FA0(r2)
    fcmpo cr0, f2, f0
    ble clCGameDemoWC_Render_L_800AE0B4
    lfs f1, lbl_806D4FA4(r2)
    lfs f0, lbl_806D4F90(r2)
    fsubs f1, f1, f2
    lfs f2, lbl_806D4F94(r2)
    fdivs f0, f1, f0
    fcmpo cr0, f0, f2
    bge clCGameDemoWC_Render_L_800AE08C
    b clCGameDemoWC_Render_L_800AE0A0
    clCGameDemoWC_Render_L_800AE08C:
    lfs f2, lbl_806D4F98(r2)
    fcmpo cr0, f0, f2
    ble clCGameDemoWC_Render_L_800AE09C
    b clCGameDemoWC_Render_L_800AE0A0
    clCGameDemoWC_Render_L_800AE09C:
    fmr f2, f0
    clCGameDemoWC_Render_L_800AE0A0:
    lfs f0, lbl_806D4F9C(r2)
    fnmsubs f0, f0, f2, f0
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r7, 0xc(r1)
    clCGameDemoWC_Render_L_800AE0B4:
    clrlwi. r0, r7, 24
    beq clCGameDemoWC_Render_L_800AE0D8
    lwz r3, 0xc(r31)
    li r4, 0x0
    lfs f1, lbl_806D4F98(r2)
    li r5, 0x0
    li r6, 0x0
    li r8, 0x0
    bl fn_80181790
    clCGameDemoWC_Render_L_800AE0D8:
    lwz r3, 0xc(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    li r3, 0x7f
    bl fn_802C14B8
    clCGameDemoWC_Render_L_800AE0F4:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

