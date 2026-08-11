/* === extracted from auto_KartDriver_Render_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_LoadProjMatrix();
extern void GetCourseScene3D();
extern void IsRaceStarted();
extern void KartTireFX_ApplyAndRender();
extern void Object_BindMatrixSource();
extern void Object_DriveAnimMatrix();
extern void Object_GetJObjPositionVec();
extern void Object_RenderJObjTree();
extern void fn_801375D8();
extern void fn_80231D4C();
extern void fn_80245700();
extern void fn_8025E3C4();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D25D0;
extern unsigned int lbl_806D25D4;
extern unsigned int lbl_806D25D8;
extern unsigned int lbl_806D25DC;

/* --- function index (1 fns, .text 0x80042350..0x80042610) ---
 * [  0] 0x80042350 size:0x2C0   global KartDriver_Render
 */

/* --- forward decls --- */
asm void KartDriver_Render(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_Render[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_Render = {
    (void *)&KartDriver_Render, 0x000002C0, (void *)extab_KartDriver_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_Render(void) { /* 0x80042350 size:0x2C0 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    mr r30, r3
    mr r31, r4
    lbz r0, 0x2d0(r3)
    cmplwi r0, 0x0
    bne KartDriver_Render_L_800423C8
    lwz r5, 0x304(r30)
    li r4, 0x0
    li r0, 0x80
    lwz r3, 0x10(r5)
    lwz r5, 0x14(r5)
    and r0, r3, r0
    and r3, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne KartDriver_Render_L_800423B0
    b KartDriver_Render_L_800423B4
    KartDriver_Render_L_800423B0:
    li r4, 0x1
    KartDriver_Render_L_800423B4:
    clrlwi r0, r4, 24
    cmplwi r0, 0x1
    bne KartDriver_Render_L_800423C8
    li r3, 0x1
    b KartDriver_Render_L_800425F0
    KartDriver_Render_L_800423C8:
    lwz r0, 0x1e8(r30)
    cmpwi r0, 0x0
    bne KartDriver_Render_L_800423DC
    li r3, 0x0
    b KartDriver_Render_L_800425F0
    KartDriver_Render_L_800423DC:
    lwz r0, 0x0(r30)
    cmplwi r0, 0x0
    beq KartDriver_Render_L_800423F4
    lwz r0, 0xc(r30)
    cmplwi r0, 0x0
    bne KartDriver_Render_L_800423FC
    KartDriver_Render_L_800423F4:
    li r3, 0x0
    b KartDriver_Render_L_800425F0
    KartDriver_Render_L_800423FC:
    bl GetCourseScene3D
    addi r4, r1, 0x8
    bl CObj_LoadProjMatrix
    lwz r3, 0x0(r30)
    addi r4, r1, 0x14
    bl Object_GetJObjPositionVec
    addi r3, r1, 0x14
    addi r4, r1, 0x8
    bl fn_8025E3C4
    fmr f31, f1
    lfs f0, lbl_806D25D0(r2)
    fcmpo cr0, f31, f0
    cror eq, gt, eq
    bne KartDriver_Render_L_8004243C
    li r3, 0x1
    b KartDriver_Render_L_800425F0
    KartDriver_Render_L_8004243C:
    lfs f1, lbl_806D25D4(r2)
    addi r3, r1, 0x14
    bl fn_801375D8
    clrlwi. r0, r3, 24
    bne KartDriver_Render_L_80042458
    li r3, 0x1
    b KartDriver_Render_L_800425F0
    KartDriver_Render_L_80042458:
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    bne KartDriver_Render_L_80042494
    cmplwi r31, 0x1
    ble KartDriver_Render_L_80042474
    cmpwi r31, 0x4
    bne KartDriver_Render_L_80042570
    KartDriver_Render_L_80042474:
    lwz r3, 0x0(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0x30c(r30)
    cmplwi r3, 0x0
    beq KartDriver_Render_L_80042570
    bl KartTireFX_ApplyAndRender
    b KartDriver_Render_L_80042570
    KartDriver_Render_L_80042494:
    lwz r3, 0x8(r30)
    cmplwi r3, 0x0
    beq KartDriver_Render_L_800424E4
    lfs f0, lbl_806D25D8(r2)
    fcmpo cr0, f31, f0
    cror eq, gt, eq
    bne KartDriver_Render_L_800424E4
    cmplwi r31, 0x1
    ble KartDriver_Render_L_800424C0
    cmpwi r31, 0x4
    bne KartDriver_Render_L_80042570
    KartDriver_Render_L_800424C0:
    lwz r4, 0x17c(r30)
    li r5, 0x0
    bl Object_BindMatrixSource
    lwz r3, 0x8(r30)
    bl Object_DriveAnimMatrix
    lwz r3, 0x8(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    b KartDriver_Render_L_80042570
    KartDriver_Render_L_800424E4:
    lwz r3, 0x4(r30)
    cmplwi r3, 0x0
    beq KartDriver_Render_L_80042534
    lfs f0, lbl_806D25DC(r2)
    fcmpo cr0, f31, f0
    cror eq, gt, eq
    bne KartDriver_Render_L_80042534
    cmplwi r31, 0x1
    ble KartDriver_Render_L_80042510
    cmpwi r31, 0x4
    bne KartDriver_Render_L_80042570
    KartDriver_Render_L_80042510:
    lwz r4, 0x17c(r30)
    li r5, 0x0
    bl Object_BindMatrixSource
    lwz r3, 0x4(r30)
    bl Object_DriveAnimMatrix
    lwz r3, 0x4(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    b KartDriver_Render_L_80042570
    KartDriver_Render_L_80042534:
    cmplwi r31, 0x1
    ble KartDriver_Render_L_80042544
    cmpwi r31, 0x4
    bne KartDriver_Render_L_80042550
    KartDriver_Render_L_80042544:
    lwz r3, 0x0(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    KartDriver_Render_L_80042550:
    cmpwi r31, 0x0
    beq KartDriver_Render_L_80042560
    cmpwi r31, 0x2
    bne KartDriver_Render_L_80042570
    KartDriver_Render_L_80042560:
    lwz r3, 0x30c(r30)
    cmplwi r3, 0x0
    beq KartDriver_Render_L_80042570
    bl KartTireFX_ApplyAndRender
    KartDriver_Render_L_80042570:
    cmplwi r31, 0x1
    ble KartDriver_Render_L_80042580
    cmpwi r31, 0x3
    bne KartDriver_Render_L_800425EC
    KartDriver_Render_L_80042580:
    lwz r3, 0xc(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0x1c(r30)
    cmplwi r3, 0x0
    beq KartDriver_Render_L_800425AC
    lbz r0, 0x174(r30)
    cmplwi r0, 0x0
    beq KartDriver_Render_L_800425AC
    li r4, 0x7
    bl Object_RenderJObjTree
    KartDriver_Render_L_800425AC:
    lwz r0, 0x150(r30)
    cmplwi r0, 0x0
    beq KartDriver_Render_L_800425CC
    lwz r3, 0x20(r30)
    cmplwi r3, 0x0
    beq KartDriver_Render_L_800425CC
    li r4, 0x7
    bl Object_RenderJObjTree
    KartDriver_Render_L_800425CC:
    lwz r3, 0x35c(r30)
    cmplwi r3, 0x0
    beq KartDriver_Render_L_800425DC
    bl fn_80231D4C
    KartDriver_Render_L_800425DC:
    lwz r3, 0x360(r30)
    cmplwi r3, 0x0
    beq KartDriver_Render_L_800425EC
    bl fn_80245700
    KartDriver_Render_L_800425EC:
    li r3, 0x1
    KartDriver_Render_L_800425F0:
    psq_l f31, 0x38(r1), 0, 0
    lwz r0, 0x44(r1)
    lfd f31, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

