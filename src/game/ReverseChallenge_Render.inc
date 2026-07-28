/* === extracted from auto_ReverseChallenge_Ren_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BananaField_Render();
extern void CObj_DebugVizPathFlush();
extern void CourseEnvironment_RenderObjects_Timed();
extern void DrawEffect_TickAndCull();
extern void ItemObjectManager_Render();
extern void KartItem_RenderPipelinedWithEffects();
extern void Object_RenderJObjIfWithinRange();
extern void Subsystem36c_DispatchPass2_Timed();
extern void Subsystem36c_DispatchPass4_Timed();
extern void TransitionEffect_RenderPass();
extern void TransparentDraw_SortAndDispatch();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void fn_8016B0C4();
extern void fn_80253448();
extern void fn_802535D4();
extern void fn_802C14B8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806DC190;
extern unsigned int lbl_806DC1B0;
extern unsigned int lbl_806DC1B8;

/* --- function index (1 fns, .text 0x800ACFC0..0x800AD134) ---
 * [  0] 0x800ACFC0 size:0x174   global ReverseChallenge_Render
 */

/* --- forward decls --- */
asm void ReverseChallenge_Render(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ReverseChallenge_Render[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ReverseChallenge_Render = {
    (void *)&ReverseChallenge_Render, 0x00000174, (void *)extab_ReverseChallenge_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ReverseChallenge_Render(void) { /* 0x800ACFC0 size:0x174 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lbz r0, 0x40(r3)
    cmplwi r0, 0x0
    beq ReverseChallenge_Render_L_800AD120
    lwz r3, 0x1c(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne ReverseChallenge_Render_L_800AD0EC
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne ReverseChallenge_Render_L_800AD010
    li r3, 0x0
    ReverseChallenge_Render_L_800AD010:
    bl clDrawMan_Buckets_Reset
    bl TransparentDraw_SortAndDispatch
    lwz r3, 0x1c(r31)
    bl CObj_DebugVizPathFlush
    bl fn_8016B0C4
    lwz r3, 0x14(r31)
    li r4, 0x0
    bl KartItem_RenderPipelinedWithEffects
    lwz r3, 0x18(r31)
    bl Object_RenderJObjIfWithinRange
    lwz r3, 0x8(r31)
    bl CourseEnvironment_RenderObjects_Timed
    lwz r3, 0x8(r31)
    bl Subsystem36c_DispatchPass2_Timed
    bl ItemObjectManager_Render
    lwz r3, 0x30(r31)
    bl BananaField_Render
    lwz r3, 0x24(r31)
    lwz r4, lbl_806DC190(r2)
    bl fn_80253448
    bl DrawEffect_TickAndCull
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne ReverseChallenge_Render_L_800AD074
    li r3, 0x0
    ReverseChallenge_Render_L_800AD074:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne ReverseChallenge_Render_L_800AD088
    li r3, 0x0
    ReverseChallenge_Render_L_800AD088:
    bl clDrawMan_Buckets_Dispatch
    lwz r3, 0x8(r31)
    bl Subsystem36c_DispatchPass4_Timed
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne ReverseChallenge_Render_L_800AD0A4
    li r3, 0x0
    ReverseChallenge_Render_L_800AD0A4:
    li r4, 0x2
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne ReverseChallenge_Render_L_800AD0BC
    li r3, 0x0
    ReverseChallenge_Render_L_800AD0BC:
    li r4, 0x4
    bl TransitionEffect_RenderPass
    lwz r4, lbl_806DC1B0(r2)
    lwz r0, lbl_806DC190(r2)
    lwz r3, 0x24(r31)
    or r4, r4, r0
    bl fn_80253448
    lwz r3, 0x1c(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    ReverseChallenge_Render_L_800AD0EC:
    lwz r3, 0x24(r31)
    lwz r4, lbl_806DC1B8(r2)
    bl fn_80253448
    lwz r3, 0x24(r31)
    bl fn_802535D4
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne ReverseChallenge_Render_L_800AD110
    li r3, 0x0
    ReverseChallenge_Render_L_800AD110:
    li r4, 0x1
    bl TransitionEffect_RenderPass
    li r3, 0x7f
    bl fn_802C14B8
    ReverseChallenge_Render_L_800AD120:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

