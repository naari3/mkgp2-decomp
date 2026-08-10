/* === extracted from auto_03_8005E330_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D29A8;
extern unsigned int lbl_806D29B0;
extern unsigned int lbl_806D29B4;
extern unsigned int lbl_806D29B8;
extern unsigned int lbl_806D29BC;
extern unsigned int lbl_806D29C0;

/* --- function index (1 fns, .text 0x8005E330..0x8005E46C) ---
 * [  0] 0x8005E330 size:0x13C   global clItemBoxResponder_TickDebris
 */

/* --- forward decls --- */
asm void clItemBoxResponder_TickDebris(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBoxResponder_TickDebris(void) { /* 0x8005E330 size:0x13C */
    nofralloc
    lwz r4, 0x0(r3)
    lbz r0, 0x0(r4)
    cmplwi r0, 0x0
    bne clItemBoxResponder_TickDebris_L_8005E348
    li r0, 0x0
    b clItemBoxResponder_TickDebris_L_8005E45C
    clItemBoxResponder_TickDebris_L_8005E348:
    li r0, 0xf
    mr r5, r4
    lfs f0, lbl_806D29B0(r2)
    li r3, 0x0
    lfs f5, lbl_806D29A8(r2)
    mtctr r0
    clItemBoxResponder_TickDebris_L_8005E360:
    lfs f1, 0x20(r5)
    fsubs f1, f1, f0
    stfs f1, 0x20(r5)
    lfs f1, 0x20(r5)
    fcmpo cr0, f1, f5
    bge clItemBoxResponder_TickDebris_L_8005E380
    li r0, 0x0
    b clItemBoxResponder_TickDebris_L_8005E42C
    clItemBoxResponder_TickDebris_L_8005E380:
    lfs f3, 0x1c(r5)
    lfs f2, lbl_806D29B4(r2)
    lfs f1, lbl_806D29B8(r2)
    fsubs f2, f3, f2
    stfs f2, 0x1c(r5)
    lfs f2, 0x1c(r5)
    fcmpo cr0, f2, f1
    bge clItemBoxResponder_TickDebris_L_8005E3A4
    stfs f1, 0x1c(r5)
    clItemBoxResponder_TickDebris_L_8005E3A4:
    lfs f2, 0x14(r5)
    li r0, 0x1
    lfs f1, 0x1c(r5)
    lfs f3, lbl_806D29BC(r2)
    fadds f1, f2, f1
    lfs f2, lbl_806D29C0(r2)
    stfs f1, 0x14(r5)
    lfs f4, 0x4(r5)
    lfs f1, 0x10(r5)
    fadds f1, f4, f1
    stfs f1, 0x4(r5)
    lfs f4, 0x8(r5)
    lfs f1, 0x14(r5)
    fadds f1, f4, f1
    stfs f1, 0x8(r5)
    lfs f4, 0xc(r5)
    lfs f1, 0x18(r5)
    fadds f1, f4, f1
    stfs f1, 0xc(r5)
    lfs f1, 0x10(r5)
    fmuls f1, f1, f3
    stfs f1, 0x10(r5)
    lfs f1, 0x14(r5)
    fmuls f1, f1, f3
    stfs f1, 0x14(r5)
    lfs f1, 0x18(r5)
    fmuls f1, f1, f3
    stfs f1, 0x18(r5)
    lfs f1, 0x28(r5)
    fadds f1, f1, f2
    stfs f1, 0x28(r5)
    lfs f1, 0x2c(r5)
    fadds f1, f1, f2
    stfs f1, 0x2c(r5)
    clItemBoxResponder_TickDebris_L_8005E42C:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne clItemBoxResponder_TickDebris_L_8005E43C
    addi r3, r3, 0x1
    clItemBoxResponder_TickDebris_L_8005E43C:
    addi r5, r5, 0x2c
    bdnz clItemBoxResponder_TickDebris_L_8005E360
    cmpwi r3, 0x0
    bgt clItemBoxResponder_TickDebris_L_8005E458
    li r0, 0x0
    stb r0, 0x0(r4)
    b clItemBoxResponder_TickDebris_L_8005E45C
    clItemBoxResponder_TickDebris_L_8005E458:
    li r0, 0x1
    clItemBoxResponder_TickDebris_L_8005E45C:
    clrlwi r0, r0, 24
    cntlzw r0, r0
    extrwi r3, r0, 8, 19
    blr
}
