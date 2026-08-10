/* === extracted from auto_HUD_FrameUpdate_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void SoundMgr_PlaySE();
extern void fn_8016C360();
extern void fn_8016C394();
extern void fn_8020EDB4();
extern void fn_80215784();
extern void fn_802512D0();
extern void fn_802518EC();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_countdownPhase;
extern unsigned int g_raceEnded;
extern unsigned int lbl_806DC1BC;
extern unsigned int lbl_806DC1C0;

/* --- function index (1 fns, .text 0x80253658..0x802537E8) ---
 * [  0] 0x80253658 size:0x190   global HUD_FrameUpdate
 */

/* --- forward decls --- */
asm void HUD_FrameUpdate(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_HUD_FrameUpdate[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_HUD_FrameUpdate = {
    (void *)&HUD_FrameUpdate, 0x00000190, (void *)extab_HUD_FrameUpdate
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void HUD_FrameUpdate(void) { /* 0x80253658 size:0x190 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    mr r30, r31
    stw r29, 0x14(r1)
    li r29, 0x0
    HUD_FrameUpdate_L_8025367C:
    lwz r3, 0x10(r30)
    cmplwi r3, 0x0
    beq HUD_FrameUpdate_L_80253698
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    HUD_FrameUpdate_L_80253698:
    addi r29, r29, 0x1
    addi r30, r30, 0x4
    cmpwi r29, 0x17
    blt HUD_FrameUpdate_L_8025367C
    lwz r3, 0x4(r31)
    lwz r0, g_countdownPhase(r13)
    cmpw r3, r0
    bne HUD_FrameUpdate_L_80253710
    cmpwi r0, 0x0
    addi r4, r3, 0x32
    bne HUD_FrameUpdate_L_802536E4
    lwz r30, 0x0(r31)
    li r3, 0x4
    bl fn_802518EC
    mr r4, r3
    mr r3, r30
    li r5, 0x0
    bl fn_8020EDB4
    b HUD_FrameUpdate_L_80253704
    HUD_FrameUpdate_L_802536E4:
    lwz r30, 0x0(r31)
    mr r5, r4
    li r4, 0x4
    bl fn_802512D0
    mr r4, r3
    mr r3, r30
    li r5, 0x0
    bl fn_8020EDB4
    HUD_FrameUpdate_L_80253704:
    lwz r3, 0x4(r31)
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    HUD_FrameUpdate_L_80253710:
    lwz r0, 0x28(r31)
    cmplwi r0, 0x0
    beq HUD_FrameUpdate_L_802537B8
    lwz r3, 0x8(r31)
    lis r0, 0x4330
    stw r0, 0x8(r1)
    addi r0, r3, 0x1
    lfd f2, lbl_806DC1C0(r2)
    xoris r0, r0, 0x8000
    lfs f0, 0x70(r31)
    stw r0, 0xc(r1)
    lfd f1, 0x8(r1)
    fsubs f1, f1, f2
    fcmpo cr0, f0, f1
    cror eq, lt, eq
    bne HUD_FrameUpdate_L_802537B8
    lfs f0, lbl_806DC1BC(r2)
    fcmpo cr0, f1, f0
    ble HUD_FrameUpdate_L_802537B8
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x0
    bne HUD_FrameUpdate_L_80253794
    lwz r30, 0x0(r31)
    addi r5, r3, 0x3c
    li r4, 0x4
    bl fn_80215784
    mr r4, r3
    mr r3, r30
    li r5, 0x0
    bl fn_8020EDB4
    lwz r3, 0x8(r31)
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    HUD_FrameUpdate_L_80253794:
    li r3, 0x3
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne HUD_FrameUpdate_L_802537B0
    li r3, 0x3
    bl fn_8016C394
    HUD_FrameUpdate_L_802537B0:
    li r3, 0x3
    bl SoundMgr_PlaySE
    HUD_FrameUpdate_L_802537B8:
    lwz r3, 0x0(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


