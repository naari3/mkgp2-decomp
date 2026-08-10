/* === extracted from auto_BtMode_RenderFrame_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_DebugVizPathFlush();
extern void CarObject_GetRenderObj();
extern void CourseEnvironment_RenderObjects_Timed();
extern void DrawEffect_TickAndCull();
extern void GetKartSlotKartVariant();
extern void IsRaceStarted();
extern void IsTimerModeEnabled();
extern void ItemObjectManager_Render();
extern void Jyugemu_Flag_Render();
extern void Jyugemu_ReverseFlag_Render();
extern void KartItem_GetCurrentISESlot();
extern void KartItem_IsAtStartSlot();
extern void KartItem_RenderPipelinedWithEffects();
extern void KartItem_TriggerStateAction();
extern void LapBannerScene_RenderIfActive();
extern void NoopRenderHook_Pending_80064d28();
extern void Object_RenderJObjIfWithinRange();
extern void Stub_NoOp_80030aec();
extern void Subsystem36c_DispatchPass2_Timed();
extern void Subsystem36c_DispatchPass4_Timed();
extern void TransitionEffect_RenderPass();
extern void TransparentDraw_SortAndDispatch();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void clItemBoxManager_Draw();
extern void fn_80139810();
extern void fn_8016B0C4();
extern void fn_8023E2F8();
extern void fn_80253448();
extern void fn_802535D4();
extern void fn_802C14B8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_cupId;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D10D0;
extern unsigned int lbl_806D1398;
extern unsigned int lbl_806D13A1;
extern unsigned int lbl_806D13B4;
extern unsigned int lbl_806DC17C;
extern unsigned int lbl_806DC180;
extern unsigned int lbl_806DC184;
extern unsigned int lbl_806DC188;
extern unsigned int lbl_806DC18C;
extern unsigned int lbl_806DC190;
extern unsigned int lbl_806DC194;
extern unsigned int lbl_806DC198;
extern unsigned int lbl_806DC19C;
extern unsigned int lbl_806DC1A0;
extern unsigned int lbl_806DC1A4;
extern unsigned int lbl_806DC1AC;
extern unsigned int lbl_806DC1B0;
extern unsigned int lbl_806DC1B4;
extern unsigned int lbl_806DC1B8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_carObjects[];

/* --- function index (1 fns, .text 0x800A28D4..0x800A2B90) ---
 * [  0] 0x800A28D4 size:0x2BC   global BtMode_RenderFrame
 */

/* --- forward decls --- */
asm void BtMode_RenderFrame(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BtMode_RenderFrame[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BtMode_RenderFrame = {
    (void *)&BtMode_RenderFrame, 0x000002BC, (void *)extab_BtMode_RenderFrame
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BtMode_RenderFrame(void) { /* 0x800A28D4 size:0x2BC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    lbz r0, lbl_806D13A1(r13)
    cmplwi r0, 0x1
    bne BtMode_RenderFrame_L_800A2B74
    lwz r3, 0x1c(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne BtMode_RenderFrame_L_800A2B64
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne BtMode_RenderFrame_L_800A292C
    li r3, 0x0
    BtMode_RenderFrame_L_800A292C:
    bl clDrawMan_Buckets_Reset
    bl TransparentDraw_SortAndDispatch
    lwz r3, 0x1c(r31)
    bl CObj_DebugVizPathFlush
    bl fn_8016B0C4
    lwz r0, g_cupId(r13)
    cmpwi r0, 0x0
    bne BtMode_RenderFrame_L_800A2950
    bl IsTimerModeEnabled
    BtMode_RenderFrame_L_800A2950:
    lis r3, g_carObjects@ha
    li r4, 0x0
    addi r3, r3, g_carObjects@l
    lwz r3, 0x0(r3)
    bl KartItem_RenderPipelinedWithEffects
    lwz r0, lbl_806D1398(r13)
    cmplwi r0, 0x0
    beq BtMode_RenderFrame_L_800A29A8
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    bne BtMode_RenderFrame_L_800A299C
    lwz r3, lbl_806D1398(r13)
    bl CarObject_GetRenderObj
    bl KartItem_GetCurrentISESlot
    lwz r3, 0x18(r3)
    cmplwi r3, 0x0
    beq BtMode_RenderFrame_L_800A299C
    li r0, 0x0
    stb r0, 0x28(r3)
    BtMode_RenderFrame_L_800A299C:
    lwz r3, lbl_806D1398(r13)
    li r4, 0x0
    bl KartItem_RenderPipelinedWithEffects
    BtMode_RenderFrame_L_800A29A8:
    lwz r3, 0x1c(r31)
    bl Stub_NoOp_80030aec
    lwz r3, 0x4(r31)
    bl Object_RenderJObjIfWithinRange
    lwz r3, 0x8(r31)
    bl Jyugemu_Flag_Render
    lwz r3, 0xc(r31)
    bl Jyugemu_ReverseFlag_Render
    lwz r3, 0x10(r31)
    bl LapBannerScene_RenderIfActive
    lwz r3, 0x14(r31)
    bl CourseEnvironment_RenderObjects_Timed
    lwz r3, 0x14(r31)
    bl Subsystem36c_DispatchPass2_Timed
    bl NoopRenderHook_Pending_80064d28
    bl ItemObjectManager_Render
    bl DrawEffect_TickAndCull
    bl fn_80139810
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    bne BtMode_RenderFrame_L_800A2A00
    li r3, 0x0
    BtMode_RenderFrame_L_800A2A00:
    bl clItemBoxManager_Draw
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne BtMode_RenderFrame_L_800A2A14
    li r3, 0x0
    BtMode_RenderFrame_L_800A2A14:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne BtMode_RenderFrame_L_800A2A28
    li r3, 0x0
    BtMode_RenderFrame_L_800A2A28:
    bl clDrawMan_Buckets_Dispatch
    lwz r3, 0x14(r31)
    bl Subsystem36c_DispatchPass4_Timed
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne BtMode_RenderFrame_L_800A2A44
    li r3, 0x0
    BtMode_RenderFrame_L_800A2A44:
    li r4, 0x5
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806DC190(r2)
    lwz r0, lbl_806DC188(r2)
    lwz r4, lbl_806DC18C(r2)
    or r0, r3, r0
    lwz r3, lbl_806DC184(r2)
    or r0, r4, r0
    lwz r4, lbl_806DC198(r2)
    or r0, r3, r0
    lwz r5, lbl_806DC19C(r2)
    or r0, r4, r0
    lwz r3, 0x2c(r31)
    or r4, r5, r0
    bl fn_80253448
    lwz r3, lbl_806D13B4(r13)
    cmplwi r3, 0x0
    beq BtMode_RenderFrame_L_800A2A90
    bl fn_8023E2F8
    BtMode_RenderFrame_L_800A2A90:
    lwz r3, lbl_806DC180(r2)
    lwz r0, lbl_806DC17C(r2)
    lwz r4, lbl_806DC1A0(r2)
    or r0, r3, r0
    lwz r3, lbl_806DC1A4(r2)
    or r0, r4, r0
    lwz r4, lbl_806DC1AC(r2)
    or r0, r3, r0
    lwz r3, lbl_806DC194(r2)
    or r0, r4, r0
    lwz r4, lbl_806DC1B0(r2)
    or r0, r3, r0
    lwz r3, lbl_806DC1B4(r2)
    or r0, r4, r0
    lwz r4, lbl_806DC1B8(r2)
    or r0, r3, r0
    lwz r3, 0x2c(r31)
    or r4, r4, r0
    bl fn_80253448
    li r30, 0x0
    BtMode_RenderFrame_L_800A2AE0:
    mr r3, r30
    bl GetKartSlotKartVariant
    mr. r29, r3
    beq BtMode_RenderFrame_L_800A2AFC
    bl KartItem_TriggerStateAction
    mr r3, r29
    bl KartItem_IsAtStartSlot
    BtMode_RenderFrame_L_800A2AFC:
    addi r30, r30, 0x1
    cmpwi r30, 0x8
    blt BtMode_RenderFrame_L_800A2AE0
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne BtMode_RenderFrame_L_800A2B18
    li r3, 0x0
    BtMode_RenderFrame_L_800A2B18:
    li r4, 0x2
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne BtMode_RenderFrame_L_800A2B30
    li r3, 0x0
    BtMode_RenderFrame_L_800A2B30:
    li r4, 0x4
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne BtMode_RenderFrame_L_800A2B48
    li r3, 0x0
    BtMode_RenderFrame_L_800A2B48:
    li r4, 0x6
    bl TransitionEffect_RenderPass
    lwz r3, 0x1c(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    BtMode_RenderFrame_L_800A2B64:
    lwz r3, 0x2c(r31)
    bl fn_802535D4
    li r3, 0x7f
    bl fn_802C14B8
    BtMode_RenderFrame_L_800A2B74:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

