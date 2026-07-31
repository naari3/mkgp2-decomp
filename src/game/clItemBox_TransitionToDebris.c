/* === extracted from auto_clItemBox_Transition_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Saturate_Double();
extern void fn_802DCA04();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D29A8;
extern unsigned int lbl_806D29C4;
extern unsigned int lbl_806D29C8;
extern unsigned int lbl_806D29CC;
extern unsigned int lbl_806D29D0;
extern unsigned int lbl_806D29D4;
extern unsigned int lbl_806D29D8;
extern unsigned int lbl_806D29DC;
extern unsigned int lbl_806D29E0;
extern unsigned int lbl_806D29E4;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803F9CA8[];

/* --- function index (1 fns, .text 0x8005EA94..0x8005ED18) ---
 * [  0] 0x8005EA94 size:0x284   global clItemBox_TransitionToDebris
 */

/* --- forward decls --- */
asm void clItemBox_TransitionToDebris(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBox_TransitionToDebris[8] = {
    0x1C, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBox_TransitionToDebris = {
    (void *)&clItemBox_TransitionToDebris, 0x00000284, (void *)extab_clItemBox_TransitionToDebris
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBox_TransitionToDebris(void) { /* 0x8005EA94 size:0x284 */
    nofralloc
    stwu r1, -0x120(r1)
    mflr r0
    stw r0, 0x124(r1)
    stfd f31, 0x110(r1)
    psq_st f31, 0x118(r1), 0, 0
    stfd f30, 0x100(r1)
    psq_st f30, 0x108(r1), 0, 0
    stfd f29, 0xf0(r1)
    psq_st f29, 0xf8(r1), 0, 0
    stfd f28, 0xe0(r1)
    psq_st f28, 0xe8(r1), 0, 0
    stfd f27, 0xd0(r1)
    psq_st f27, 0xd8(r1), 0, 0
    stfd f26, 0xc0(r1)
    psq_st f26, 0xc8(r1), 0, 0
    stfd f25, 0xb0(r1)
    psq_st f25, 0xb8(r1), 0, 0
    stfd f24, 0xa0(r1)
    psq_st f24, 0xa8(r1), 0, 0
    stfd f23, 0x90(r1)
    psq_st f23, 0x98(r1), 0, 0
    stfd f22, 0x80(r1)
    psq_st f22, 0x88(r1), 0, 0
    stfd f21, 0x70(r1)
    psq_st f21, 0x78(r1), 0, 0
    stfd f20, 0x60(r1)
    psq_st f20, 0x68(r1), 0, 0
    stfd f19, 0x50(r1)
    psq_st f19, 0x58(r1), 0, 0
    stfd f18, 0x40(r1)
    psq_st f18, 0x48(r1), 0, 0
    stfd f17, 0x30(r1)
    psq_st f17, 0x38(r1), 0, 0
    stfd f16, 0x20(r1)
    psq_st f16, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    li r0, 0x2
    mr r29, r3
    stw r0, 0x24(r3)
    lis r3, lbl_803F9CA8@ha
    addi r3, r3, lbl_803F9CA8@l
    lfs f25, lbl_806D29A8(r2)
    lwz r0, 0x24(r29)
    fmr f17, f1
    lfs f0, lbl_806D29C4(r2)
    fmr f18, f2
    mulli r4, r0, 0xc
    fmr f19, f3
    fmuls f22, f0, f17
    fmuls f21, f0, f18
    li r0, 0x1
    add r5, r3, r4
    lwz r4, 0x0(r5)
    fmuls f20, f0, f19
    lwz r3, 0x4(r5)
    lfs f26, lbl_806D29D0(r2)
    li r31, 0x0
    stw r4, 0x18(r29)
    lfs f27, lbl_806D29CC(r2)
    stw r3, 0x1c(r29)
    lfs f28, lbl_806D29C8(r2)
    lwz r3, 0x8(r5)
    lfs f29, lbl_806D29D4(r2)
    stw r3, 0x20(r29)
    lfs f30, lbl_806D29D8(r2)
    stfs f25, 0x2c(r29)
    lfs f31, lbl_806D29E0(r2)
    lwz r30, 0x4(r29)
    lfs f16, lbl_806D29E4(r2)
    stb r0, 0x0(r30)
    clItemBox_TransitionToDebris_L_8005EBB4:
    lfs f0, 0x8(r29)
    stfs f0, 0x4(r30)
    lfs f0, 0xc(r29)
    stfs f0, 0x8(r30)
    lfs f0, 0x10(r29)
    stfs f0, 0xc(r30)
    bl fn_802DCA04
    fsubs f0, f1, f26
    fmuls f0, f27, f0
    fmuls f23, f28, f0
    bl fn_802DCA04
    fsubs f0, f1, f26
    fmuls f0, f27, f0
    fmuls f24, f28, f0
    bl fn_802DCA04
    fsubs f1, f1, f26
    fmuls f0, f18, f24
    fmuls f1, f27, f1
    fmadds f0, f17, f23, f0
    fmuls f3, f28, f1
    fmadds f0, f19, f3, f0
    fcmpo cr0, f0, f25
    bge clItemBox_TransitionToDebris_L_8005EC1C
    fneg f23, f23
    fneg f24, f24
    fneg f3, f3
    clItemBox_TransitionToDebris_L_8005EC1C:
    fadds f2, f23, f22
    fadds f1, f24, f21
    fadds f0, f3, f20
    stfs f2, 0x10(r30)
    stfs f1, 0x14(r30)
    stfs f0, 0x18(r30)
    stfs f29, 0x1c(r30)
    bl fn_802DCA04
    fmuls f1, f30, f1
    lfs f2, lbl_806D29DC(r2)
    fmr f3, f30
    bl Saturate_Double
    stfs f1, 0x24(r30)
    bl fn_802DCA04
    fmuls f0, f31, f1
    stfs f0, 0x28(r30)
    bl fn_802DCA04
    fmuls f0, f31, f1
    addi r31, r31, 0x1
    cmplwi r31, 0xf
    stfs f0, 0x2c(r30)
    stfs f16, 0x20(r30)
    addi r30, r30, 0x2c
    blt clItemBox_TransitionToDebris_L_8005EBB4
    psq_l f31, 0x118(r1), 0, 0
    lfd f31, 0x110(r1)
    psq_l f30, 0x108(r1), 0, 0
    lfd f30, 0x100(r1)
    psq_l f29, 0xf8(r1), 0, 0
    lfd f29, 0xf0(r1)
    psq_l f28, 0xe8(r1), 0, 0
    lfd f28, 0xe0(r1)
    psq_l f27, 0xd8(r1), 0, 0
    lfd f27, 0xd0(r1)
    psq_l f26, 0xc8(r1), 0, 0
    lfd f26, 0xc0(r1)
    psq_l f25, 0xb8(r1), 0, 0
    lfd f25, 0xb0(r1)
    psq_l f24, 0xa8(r1), 0, 0
    lfd f24, 0xa0(r1)
    psq_l f23, 0x98(r1), 0, 0
    lfd f23, 0x90(r1)
    psq_l f22, 0x88(r1), 0, 0
    lfd f22, 0x80(r1)
    psq_l f21, 0x78(r1), 0, 0
    lfd f21, 0x70(r1)
    psq_l f20, 0x68(r1), 0, 0
    lfd f20, 0x60(r1)
    psq_l f19, 0x58(r1), 0, 0
    lfd f19, 0x50(r1)
    psq_l f18, 0x48(r1), 0, 0
    lfd f18, 0x40(r1)
    psq_l f17, 0x38(r1), 0, 0
    lfd f17, 0x30(r1)
    psq_l f16, 0x28(r1), 0, 0
    lfd f16, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r0, 0x124(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x120
    blr
}

