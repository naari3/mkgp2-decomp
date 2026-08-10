/* === extracted from auto_clItemBoxResponder_S_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void Saturate_Double();
extern void fn_80270D6C();
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
extern unsigned int clItemBoxResponder_DebrisParticle_Dtor[];
extern unsigned int fn_8005E788[];

/* --- function index (1 fns, .text 0x8005E46C..0x8005E788) ---
 * [  0] 0x8005E46C size:0x31C   global clItemBoxResponder_SpawnDebris
 */

/* --- forward decls --- */
asm void clItemBoxResponder_SpawnDebris(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80036E40();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; void *f9; } extab_clItemBoxResponder_SpawnDebris = { 0x248A0000, 0x000000E8, 0x00000018, 0x000001B8, 0x00240020, 0x00000000, 0x8A80001F, (void *)&MemoryManager_TimedFree, 0x82000008, (void *)&dtor_80036E40 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBoxResponder_SpawnDebris = {
    (void *)&clItemBoxResponder_SpawnDebris, 0x0000031C, (void *)&extab_clItemBoxResponder_SpawnDebris
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBoxResponder_SpawnDebris(void) { /* 0x8005E46C size:0x31C */
    nofralloc
    stwu r1, -0x150(r1)
    mflr r0
    stw r0, 0x154(r1)
    stfd f31, 0x140(r1)
    psq_st f31, 0x148(r1), 0, 0
    stfd f30, 0x130(r1)
    psq_st f30, 0x138(r1), 0, 0
    stfd f29, 0x120(r1)
    psq_st f29, 0x128(r1), 0, 0
    stfd f28, 0x110(r1)
    psq_st f28, 0x118(r1), 0, 0
    stfd f27, 0x100(r1)
    psq_st f27, 0x108(r1), 0, 0
    stfd f26, 0xf0(r1)
    psq_st f26, 0xf8(r1), 0, 0
    stfd f25, 0xe0(r1)
    psq_st f25, 0xe8(r1), 0, 0
    stfd f24, 0xd0(r1)
    psq_st f24, 0xd8(r1), 0, 0
    stfd f23, 0xc0(r1)
    psq_st f23, 0xc8(r1), 0, 0
    stfd f22, 0xb0(r1)
    psq_st f22, 0xb8(r1), 0, 0
    stfd f21, 0xa0(r1)
    psq_st f21, 0xa8(r1), 0, 0
    stfd f20, 0x90(r1)
    psq_st f20, 0x98(r1), 0, 0
    stfd f19, 0x80(r1)
    psq_st f19, 0x88(r1), 0, 0
    stfd f18, 0x70(r1)
    psq_st f18, 0x78(r1), 0, 0
    stfd f17, 0x60(r1)
    psq_st f17, 0x68(r1), 0, 0
    stfd f16, 0x50(r1)
    psq_st f16, 0x58(r1), 0, 0
    stfd f15, 0x40(r1)
    psq_st f15, 0x48(r1), 0, 0
    stfd f14, 0x30(r1)
    psq_st f14, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    stw r28, 0x20(r1)
    mr r28, r3
    mr r30, r4
    mr r29, r5
    li r3, 0x298
    bl Alloc
    mr. r31, r3
    beq clItemBoxResponder_SpawnDebris_L_8005E59C
    lis r3, fn_8005E788@ha
    lis r5, clItemBoxResponder_DebrisParticle_Dtor@ha
    addi r4, r3, fn_8005E788@l
    li r6, 0x2c
    addi r3, r31, 0x4
    addi r5, r5, clItemBoxResponder_DebrisParticle_Dtor@l
    li r7, 0xf
    bl fn_80270D6C
    li r0, 0x0
    lfs f0, lbl_806D29A8(r2)
    stb r0, 0x0(r31)
    stfs f0, 0x20(r31)
    stfs f0, 0x4c(r31)
    stfs f0, 0x78(r31)
    stfs f0, 0xa4(r31)
    stfs f0, 0xd0(r31)
    stfs f0, 0xfc(r31)
    stfs f0, 0x128(r31)
    stfs f0, 0x154(r31)
    stfs f0, 0x180(r31)
    stfs f0, 0x1ac(r31)
    stfs f0, 0x1d8(r31)
    stfs f0, 0x204(r31)
    stfs f0, 0x230(r31)
    stfs f0, 0x25c(r31)
    stfs f0, 0x288(r31)
    clItemBoxResponder_SpawnDebris_L_8005E59C:
    stw r31, 0x0(r28)
    li r0, 0x1
    lfs f3, 0x8(r30)
    li r31, 0x0
    lfs f2, 0x4(r30)
    lfs f1, 0x0(r30)
    frsp f24, f3
    lwz r30, 0x0(r28)
    frsp f23, f2
    lfs f19, 0x8(r29)
    frsp f22, f1
    lfs f0, lbl_806D29C4(r2)
    lfs f20, 0x4(r29)
    lfs f21, 0x0(r29)
    fmuls f14, f0, f19
    fmuls f15, f0, f20
    stfs f1, 0x8(r1)
    fmuls f16, f0, f21
    lfs f0, lbl_806D29E4(r2)
    lfs f25, lbl_806D29D0(r2)
    stfs f2, 0xc(r1)
    lfs f26, lbl_806D29CC(r2)
    stfs f3, 0x10(r1)
    lfs f27, lbl_806D29C8(r2)
    stb r0, 0x0(r30)
    lfs f28, lbl_806D29A8(r2)
    lfs f29, lbl_806D29D4(r2)
    lfs f30, lbl_806D29D8(r2)
    lfs f31, lbl_806D29E0(r2)
    stfd f0, 0x18(r1)
    clItemBoxResponder_SpawnDebris_L_8005E614:
    stfs f22, 0x4(r30)
    stfs f23, 0x8(r30)
    stfs f24, 0xc(r30)
    bl fn_802DCA04
    fsubs f0, f1, f25
    fmuls f0, f26, f0
    fmuls f17, f27, f0
    bl fn_802DCA04
    fsubs f0, f1, f25
    fmuls f0, f26, f0
    fmuls f18, f27, f0
    bl fn_802DCA04
    fsubs f1, f1, f25
    fmuls f0, f20, f18
    fmuls f1, f26, f1
    fmadds f0, f21, f17, f0
    fmuls f3, f27, f1
    fmadds f0, f19, f3, f0
    fcmpo cr0, f0, f28
    bge clItemBoxResponder_SpawnDebris_L_8005E670
    fneg f17, f17
    fneg f18, f18
    fneg f3, f3
    clItemBoxResponder_SpawnDebris_L_8005E670:
    fadds f2, f17, f16
    fadds f1, f18, f15
    fadds f0, f3, f14
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
    lfd f0, 0x18(r1)
    stfs f0, 0x20(r30)
    addi r30, r30, 0x2c
    blt clItemBoxResponder_SpawnDebris_L_8005E614
    mr r3, r28
    psq_l f31, 0x148(r1), 0, 0
    lfd f31, 0x140(r1)
    psq_l f30, 0x138(r1), 0, 0
    lfd f30, 0x130(r1)
    psq_l f29, 0x128(r1), 0, 0
    lfd f29, 0x120(r1)
    psq_l f28, 0x118(r1), 0, 0
    lfd f28, 0x110(r1)
    psq_l f27, 0x108(r1), 0, 0
    lfd f27, 0x100(r1)
    psq_l f26, 0xf8(r1), 0, 0
    lfd f26, 0xf0(r1)
    psq_l f25, 0xe8(r1), 0, 0
    lfd f25, 0xe0(r1)
    psq_l f24, 0xd8(r1), 0, 0
    lfd f24, 0xd0(r1)
    psq_l f23, 0xc8(r1), 0, 0
    lfd f23, 0xc0(r1)
    psq_l f22, 0xb8(r1), 0, 0
    lfd f22, 0xb0(r1)
    psq_l f21, 0xa8(r1), 0, 0
    lfd f21, 0xa0(r1)
    psq_l f20, 0x98(r1), 0, 0
    lfd f20, 0x90(r1)
    psq_l f19, 0x88(r1), 0, 0
    lfd f19, 0x80(r1)
    psq_l f18, 0x78(r1), 0, 0
    lfd f18, 0x70(r1)
    psq_l f17, 0x68(r1), 0, 0
    lfd f17, 0x60(r1)
    psq_l f16, 0x58(r1), 0, 0
    lfd f16, 0x50(r1)
    psq_l f15, 0x48(r1), 0, 0
    lfd f15, 0x40(r1)
    psq_l f14, 0x38(r1), 0, 0
    lfd f14, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r0, 0x154(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x150
    blr
}
