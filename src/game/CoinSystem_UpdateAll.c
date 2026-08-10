/* === extracted from auto_CoinSystem_UpdateAll_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void GetCourseScene3D();
extern void GetKartSlotKartVariant();
extern void KartDriver_GetKartRootMtx();
extern void KartMovement_GetVelocityMagnitude();
extern void KartMovement_GetVelocityPtr();
extern void LUT_Sin12Bit();
extern void SoundMgr_PlaySE();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void fn_8016C360();
extern void fn_8016C394();
extern void fn_80186960();
extern void fn_801B377C();
extern void fn_8024F588();
extern void fn_8025D770();
extern void fn_8025DF40();
extern void fn_8025E264();
extern void fn_8025E2AC();
extern void fn_8025E30C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceEnded;
extern unsigned int lbl_806D1534;
extern unsigned int lbl_806D1538;
extern unsigned int lbl_806D153C;
extern unsigned int lbl_806D1540;
extern unsigned int lbl_806D1544;
extern unsigned int lbl_806D1548;
extern unsigned int lbl_806D73E8;
extern unsigned int lbl_806D73EC;
extern unsigned int lbl_806D73F8;
extern unsigned int lbl_806D73FC;
extern unsigned int lbl_806D7410;
extern unsigned int lbl_806D7414;
extern unsigned int lbl_806D7418;
extern unsigned int lbl_806D741C;
extern unsigned int lbl_806D7420;
extern unsigned int lbl_806D7424;
extern unsigned int lbl_806D7428;
extern unsigned int lbl_806D742C;
extern unsigned int lbl_806D7430;
extern unsigned int lbl_806D7434;
extern unsigned int lbl_806D7438;
extern unsigned int lbl_806D743C;
extern unsigned int lbl_806D7440;
extern unsigned int lbl_806D7444;
extern unsigned int lbl_806D7448;
extern unsigned int lbl_806D744C;
extern unsigned int lbl_806D7450;
extern unsigned int lbl_806D7454;
extern unsigned int lbl_806D7458;
extern unsigned int lbl_806D745C;
extern unsigned int lbl_806D7460;
extern unsigned int lbl_806D7464;
extern unsigned int lbl_806D7468;
extern unsigned int lbl_806D746C;
extern unsigned int lbl_806D7470;
extern unsigned int lbl_806D7474;
extern unsigned int lbl_806D7478;
extern unsigned int lbl_806D747C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_8048E4B8[];
extern unsigned int lbl_80495994[];
extern unsigned int lbl_80495A94[];
extern unsigned int lbl_80677CC8[];

/* --- function index (1 fns, .text 0x80139898..0x8013A534) ---
 * [  0] 0x80139898 size:0xC9C   global CoinSystem_UpdateAll
 */

/* --- forward decls --- */
asm void CoinSystem_UpdateAll(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CoinSystem_UpdateAll[8] = {
    0x21, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CoinSystem_UpdateAll = {
    (void *)&CoinSystem_UpdateAll, 0x00000C9C, (void *)extab_CoinSystem_UpdateAll
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CoinSystem_UpdateAll(void) { /* 0x80139898 size:0xC9C */
    nofralloc
    stwu r1, -0xe0(r1)
    mflr r0
    stw r0, 0xe4(r1)
    stfd f31, 0xd0(r1)
    psq_st f31, 0xd8(r1), 0, 0
    stfd f30, 0xc0(r1)
    psq_st f30, 0xc8(r1), 0, 0
    stfd f29, 0xb0(r1)
    psq_st f29, 0xb8(r1), 0, 0
    stfd f28, 0xa0(r1)
    psq_st f28, 0xa8(r1), 0, 0
    stw r31, 0x9c(r1)
    stw r30, 0x98(r1)
    stw r29, 0x94(r1)
    stw r28, 0x90(r1)
    lwz r0, lbl_806D1538(r13)
    cmpwi r0, 0x0
    beq CoinSystem_UpdateAll_L_8013A4F4
    li r31, 0x0
    CoinSystem_UpdateAll_L_801398E4:
    mr r3, r31
    bl GetKartSlotKartVariant
    mr. r30, r3
    beq CoinSystem_UpdateAll_L_80139A20
    lwz r0, 0x1f4(r30)
    cmpwi r0, 0x0
    blt CoinSystem_UpdateAll_L_80139A20
    cmpwi r0, 0x3
    bgt CoinSystem_UpdateAll_L_80139A20
    lwz r29, lbl_806D1534(r13)
    b CoinSystem_UpdateAll_L_80139A08
    CoinSystem_UpdateAll_L_80139910:
    lwz r0, 0x2cc(r30)
    cmpwi r0, 0x63
    bge CoinSystem_UpdateAll_L_80139A20
    lwz r0, 0x18(r29)
    cmpwi r0, 0x2
    bne CoinSystem_UpdateAll_L_80139A04
    mr r3, r30
    bl KartDriver_GetKartRootMtx
    lfs f1, 0xc(r3)
    mr r3, r30
    lfs f0, 0x20(r29)
    fsubs f0, f1, f0
    stfs f0, 0x44(r1)
    bl KartDriver_GetKartRootMtx
    lfs f1, 0x1c(r3)
    mr r3, r30
    lfs f0, 0x24(r29)
    fsubs f0, f1, f0
    stfs f0, 0x48(r1)
    bl KartDriver_GetKartRootMtx
    lfs f1, 0x2c(r3)
    li r4, 0x0
    lfs f0, 0x28(r29)
    li r0, 0x4000
    lfs f28, lbl_806D7410(r2)
    fsubs f0, f1, f0
    stfs f0, 0x4c(r1)
    lwz r28, 0x304(r30)
    lwz r3, 0x10(r28)
    lwz r5, 0x14(r28)
    and r0, r3, r0
    and r3, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    beq CoinSystem_UpdateAll_L_801399A4
    lfs f28, lbl_806D7414(r2)
    CoinSystem_UpdateAll_L_801399A4:
    addi r3, r1, 0x44
    bl fn_8025E30C
    fcmpo cr0, f1, f28
    bge CoinSystem_UpdateAll_L_80139A04
    li r0, 0x3
    li r4, 0x0
    stw r0, 0x18(r29)
    li r0, 0x4000
    lwz r3, 0x10(r28)
    lwz r5, 0x14(r28)
    and r0, r3, r0
    and r3, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    beq CoinSystem_UpdateAll_L_801399EC
    li r0, 0x7
    stw r0, 0x18(r29)
    CoinSystem_UpdateAll_L_801399EC:
    stw r30, 0x10(r29)
    li r0, -0x1
    lfs f0, lbl_806D73E8(r2)
    stw r0, 0x14(r29)
    stfs f0, 0x1c(r29)
    stfs f0, 0x34(r29)
    CoinSystem_UpdateAll_L_80139A04:
    addi r29, r29, 0xc0
    CoinSystem_UpdateAll_L_80139A08:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r29, r0
    blt CoinSystem_UpdateAll_L_80139910
    CoinSystem_UpdateAll_L_80139A20:
    addi r31, r31, 0x1
    cmpwi r31, 0x8
    blt CoinSystem_UpdateAll_L_801398E4
    lwz r3, lbl_806D153C(r13)
    cmpwi r3, 0x0
    beq CoinSystem_UpdateAll_L_80139A40
    subi r0, r3, 0x1
    stw r0, lbl_806D153C(r13)
    CoinSystem_UpdateAll_L_80139A40:
    lwz r31, lbl_806D1534(r13)
    b CoinSystem_UpdateAll_L_8013A4DC
    CoinSystem_UpdateAll_L_80139A48:
    lwz r0, 0x18(r31)
    cmplwi r0, 0xa
    bgt CoinSystem_UpdateAll_L_8013A4D8
    lis r3, jumptable_8048E4B8@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_8048E4B8@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lfs f2, 0x1c(r31)
    lfs f1, lbl_806D73E8(r2)
    fcmpo cr0, f2, f1
    ble CoinSystem_UpdateAll_L_80139A8C
    lfs f0, lbl_806D73EC(r2)
    fsubs f0, f2, f0
    stfs f0, 0x1c(r31)
    b CoinSystem_UpdateAll_L_8013A4D8
    CoinSystem_UpdateAll_L_80139A8C:
    lwz r0, lbl_806D153C(r13)
    cmpwi r0, 0x0
    bne CoinSystem_UpdateAll_L_8013A4D8
    li r3, 0x1
    li r0, 0x5
    stw r3, 0x18(r31)
    stfs f1, 0x1c(r31)
    lfs f0, 0x4(r31)
    stfs f0, 0x20(r31)
    lfs f0, 0x8(r31)
    stfs f0, 0x24(r31)
    lfs f0, 0xc(r31)
    stfs f0, 0x28(r31)
    stfs f1, 0x30(r31)
    stfs f1, 0x34(r31)
    stw r0, lbl_806D153C(r13)
    b CoinSystem_UpdateAll_L_8013A4D8
    lfs f1, 0x1c(r31)
    lfs f3, lbl_806D7418(r2)
    lfs f0, 0x4(r31)
    fdivs f4, f1, f3
    lfs f2, lbl_806D741C(r2)
    stfs f0, 0x20(r31)
    lfs f1, lbl_806D73EC(r2)
    lfs f0, 0x8(r31)
    fmadds f0, f2, f4, f0
    stfs f0, 0x24(r31)
    lfs f0, 0xc(r31)
    stfs f0, 0x28(r31)
    stfs f4, 0x34(r31)
    lfs f0, 0x1c(r31)
    fadds f0, f0, f1
    fcmpo cr0, f0, f3
    stfs f0, 0x1c(r31)
    cror eq, gt, eq
    bne CoinSystem_UpdateAll_L_8013A4D8
    li r0, 0x2
    lfs f0, lbl_806D73E8(r2)
    stw r0, 0x18(r31)
    stfs f0, 0x1c(r31)
    stfs f1, 0x34(r31)
    b CoinSystem_UpdateAll_L_8013A4D8
    lfs f2, 0x1c(r31)
    lfs f1, lbl_806D7420(r2)
    lfs f0, lbl_806D7428(r2)
    fdivs f28, f2, f1
    fmuls f1, f0, f28
    bl LUT_Sin12Bit
    lfs f3, lbl_806D7424(r2)
    lfs f2, 0x30(r31)
    lfs f0, lbl_806D742C(r2)
    fmadds f1, f3, f1, f2
    stfs f1, 0x30(r31)
    lfs f1, 0x30(r31)
    fcmpo cr0, f1, f0
    bge CoinSystem_UpdateAll_L_80139B74
    fadds f0, f1, f0
    stfs f0, 0x30(r31)
    CoinSystem_UpdateAll_L_80139B74:
    lfs f1, 0x30(r31)
    lfs f0, lbl_806D742C(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CoinSystem_UpdateAll_L_80139B90
    fsubs f0, f1, f0
    stfs f0, 0x30(r31)
    CoinSystem_UpdateAll_L_80139B90:
    lfs f0, lbl_806D7434(r2)
    fmuls f1, f0, f28
    bl LUT_Sin12Bit
    lfs f2, lbl_806D7430(r2)
    lfs f0, 0x8(r31)
    lfs f4, lbl_806D741C(r2)
    fadds f3, f2, f0
    lfs f2, lbl_806D73EC(r2)
    lfs f0, lbl_806D7420(r2)
    fmadds f1, f4, f1, f3
    stfs f1, 0x24(r31)
    lfs f1, 0x1c(r31)
    fadds f1, f1, f2
    fcmpo cr0, f1, f0
    stfs f1, 0x1c(r31)
    cror eq, gt, eq
    bne CoinSystem_UpdateAll_L_8013A4D8
    lfs f0, lbl_806D73E8(r2)
    stfs f0, 0x1c(r31)
    b CoinSystem_UpdateAll_L_8013A4D8
    lfs f1, lbl_806D73E8(r2)
    lfs f0, 0x1c(r31)
    fcmpu cr0, f1, f0
    bne CoinSystem_UpdateAll_L_80139CEC
    lwz r0, 0x0(r31)
    cmpwi r0, 0x2
    bne CoinSystem_UpdateAll_L_80139C48
    lwz r5, 0x10(r31)
    lis r3, lbl_80677CC8@ha
    addi r4, r3, lbl_80677CC8@l
    lwz r0, 0x1f4(r5)
    slwi r5, r0, 2
    lwzx r3, r4, r5
    addi r0, r3, 0x1
    stwx r0, r4, r5
    lwz r3, 0x10(r31)
    lbz r0, 0x2d0(r3)
    cmplwi r0, 0x1
    bne CoinSystem_UpdateAll_L_80139C48
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x0
    bne CoinSystem_UpdateAll_L_80139C48
    bl fn_8024F588
    lwz r4, 0x18(r3)
    addi r0, r4, 0x1
    stw r0, 0x18(r3)
    CoinSystem_UpdateAll_L_80139C48:
    lwz r3, 0x10(r31)
    lwz r0, 0x2cc(r3)
    stw r0, 0x14(r31)
    lwz r4, 0x10(r31)
    lwz r3, 0x2cc(r4)
    addi r0, r3, 0x1
    stw r0, 0x2cc(r4)
    bl fn_801B377C
    lbz r0, lbl_806D1548(r13)
    cmplwi r0, 0x1
    bne CoinSystem_UpdateAll_L_80139C84
    li r3, 0x0
    li r0, 0x2
    stb r3, lbl_806D1548(r13)
    stw r0, 0x0(r31)
    CoinSystem_UpdateAll_L_80139C84:
    lwz r3, 0x10(r31)
    lbz r0, 0x2d0(r3)
    cmplwi r0, 0x1
    bne CoinSystem_UpdateAll_L_80139CEC
    lwz r0, 0x0(r31)
    cmpwi r0, 0x2
    bne CoinSystem_UpdateAll_L_80139CC8
    li r3, 0x71
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CoinSystem_UpdateAll_L_80139CBC
    li r3, 0x71
    bl fn_8016C394
    CoinSystem_UpdateAll_L_80139CBC:
    li r3, 0x71
    bl SoundMgr_PlaySE
    b CoinSystem_UpdateAll_L_80139CEC
    CoinSystem_UpdateAll_L_80139CC8:
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CoinSystem_UpdateAll_L_80139CE4
    li r3, 0xab
    bl fn_8016C394
    CoinSystem_UpdateAll_L_80139CE4:
    li r3, 0xab
    bl SoundMgr_PlaySE
    CoinSystem_UpdateAll_L_80139CEC:
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D7438(r2)
    lwz r3, 0x10(r31)
    fdivs f28, f1, f0
    bl KartDriver_GetKartRootMtx
    lfs f0, 0xc(r3)
    stfs f0, 0x20(r31)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f2, 0x1c(r3)
    lfs f1, lbl_806D73F8(r2)
    lfs f0, lbl_806D7438(r2)
    fadds f1, f1, f2
    fmadds f0, f0, f28, f1
    stfs f0, 0x24(r31)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f5, lbl_806D73EC(r2)
    li r0, 0x5
    lfs f1, 0x2c(r3)
    mr r3, r31
    fsubs f0, f5, f28
    lfs f4, lbl_806D73E8(r2)
    stfs f1, 0x28(r31)
    lfs f3, lbl_806D743C(r2)
    stfs f0, 0x34(r31)
    lfs f1, lbl_806D73F8(r2)
    lfs f0, lbl_806D7440(r2)
    mtctr r0
    CoinSystem_UpdateAll_L_80139D60:
    lfs f2, 0x70(r3)
    fcmpo cr0, f2, f4
    cror eq, gt, eq
    bne CoinSystem_UpdateAll_L_80139D94
    lfs f2, 0x78(r3)
    fsubs f2, f2, f3
    stfs f2, 0x78(r3)
    lfs f2, 0x70(r3)
    fadds f2, f2, f5
    fcmpo cr0, f2, f1
    stfs f2, 0x70(r3)
    ble CoinSystem_UpdateAll_L_80139D94
    stfs f0, 0x70(r3)
    CoinSystem_UpdateAll_L_80139D94:
    addi r3, r3, 0x10
    bdnz CoinSystem_UpdateAll_L_80139D60
    lfs f0, 0x1c(r31)
    fctiwz f0, f0
    stfd f0, 0x80(r1)
    lwz r0, 0x84(r1)
    clrlwi. r0, r0, 30
    bne CoinSystem_UpdateAll_L_80139EA0
    li r0, 0x5
    mr r3, r31
    lfs f0, lbl_806D73E8(r2)
    li r4, 0x0
    mtctr r0
    CoinSystem_UpdateAll_L_80139DC8:
    lfs f1, 0x70(r3)
    fcmpo cr0, f1, f0
    bge CoinSystem_UpdateAll_L_80139E94
    slwi r0, r4, 4
    lis r3, lbl_80495994@ha
    add r28, r31, r0
    lfs f1, lbl_806D7428(r2)
    stfs f0, 0x70(r28)
    addi r3, r3, lbl_80495994@l
    lwz r0, lbl_806D1540(r13)
    slwi r0, r0, 2
    lfsx f0, r3, r0
    fmuls f1, f1, f0
    bl LUT_Sin12Bit
    lfs f0, lbl_806D741C(r2)
    lis r4, lbl_80495A94@ha
    lis r3, lbl_80495994@ha
    lfs f2, lbl_806D73F8(r2)
    fmuls f0, f0, f1
    addi r4, r4, lbl_80495A94@l
    addi r3, r3, lbl_80495994@l
    lfs f1, lbl_806D7428(r2)
    stfs f0, 0x74(r28)
    lwz r0, lbl_806D1544(r13)
    slwi r0, r0, 2
    lfsx f0, r4, r0
    fmuls f0, f2, f0
    stfs f0, 0x78(r28)
    lwz r0, lbl_806D1540(r13)
    slwi r0, r0, 2
    lfsx f0, r3, r0
    fmuls f1, f1, f0
    bl fn_80186960
    lfs f0, lbl_806D741C(r2)
    fmuls f0, f0, f1
    stfs f0, 0x7c(r28)
    lwz r3, lbl_806D1540(r13)
    addi r0, r3, 0x1
    cmpwi r0, 0x40
    stw r0, lbl_806D1540(r13)
    blt CoinSystem_UpdateAll_L_80139E74
    li r0, 0x0
    stw r0, lbl_806D1540(r13)
    CoinSystem_UpdateAll_L_80139E74:
    lwz r3, lbl_806D1544(r13)
    addi r0, r3, 0x1
    cmpwi r0, 0x30
    stw r0, lbl_806D1544(r13)
    blt CoinSystem_UpdateAll_L_80139EA0
    li r0, 0x0
    stw r0, lbl_806D1544(r13)
    b CoinSystem_UpdateAll_L_80139EA0
    CoinSystem_UpdateAll_L_80139E94:
    addi r3, r3, 0x10
    addi r4, r4, 0x1
    bdnz CoinSystem_UpdateAll_L_80139DC8
    CoinSystem_UpdateAll_L_80139EA0:
    lfs f2, 0x1c(r31)
    lfs f1, lbl_806D73EC(r2)
    lfs f0, lbl_806D7438(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x1c(r31)
    cror eq, gt, eq
    bne CoinSystem_UpdateAll_L_8013A4D8
    li r0, 0x4
    lfs f0, lbl_806D73E8(r2)
    stw r0, 0x18(r31)
    stfs f0, 0x1c(r31)
    stfs f0, 0x34(r31)
    b CoinSystem_UpdateAll_L_8013A4D8
    lfs f2, lbl_806D73E8(r2)
    lfs f0, 0x1c(r31)
    fcmpu cr0, f2, f0
    bne CoinSystem_UpdateAll_L_80139EFC
    lfs f1, lbl_806D73EC(r2)
    lfs f0, lbl_806D7444(r2)
    stfs f1, 0x34(r31)
    stfs f0, 0x1c(r31)
    stfs f2, 0x2c(r31)
    CoinSystem_UpdateAll_L_80139EFC:
    lfs f2, 0x30(r31)
    lfs f1, lbl_806D7448(r2)
    lfs f0, lbl_806D742C(r2)
    fadds f1, f2, f1
    stfs f1, 0x30(r31)
    lfs f1, 0x30(r31)
    fcmpo cr0, f1, f0
    bge CoinSystem_UpdateAll_L_80139F24
    fadds f0, f1, f0
    stfs f0, 0x30(r31)
    CoinSystem_UpdateAll_L_80139F24:
    lfs f1, 0x30(r31)
    lfs f0, lbl_806D742C(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CoinSystem_UpdateAll_L_80139F40
    fsubs f0, f1, f0
    stfs f0, 0x30(r31)
    CoinSystem_UpdateAll_L_80139F40:
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f30, 0xc(r3)
    lwz r3, 0x10(r31)
    bl KartMovement_GetVelocityPtr
    lfs f1, 0x0(r3)
    lfs f0, lbl_806D744C(r2)
    lwz r3, 0x10(r31)
    fmadds f29, f0, f1, f30
    bl KartDriver_GetKartRootMtx
    lfs f30, 0x1c(r3)
    lwz r3, 0x10(r31)
    bl KartMovement_GetVelocityPtr
    lfs f1, 0x4(r3)
    lfs f0, lbl_806D744C(r2)
    lwz r3, 0x10(r31)
    fmadds f28, f0, f1, f30
    bl KartDriver_GetKartRootMtx
    lfs f30, 0x2c(r3)
    lwz r3, 0x10(r31)
    bl KartMovement_GetVelocityPtr
    lfs f3, lbl_806D744C(r2)
    lfs f1, 0x1c(r31)
    lfs f0, 0x20(r31)
    fdivs f1, f1, f3
    lfs f2, lbl_806D73EC(r2)
    lfs f4, 0x8(r3)
    fsubs f31, f2, f1
    fsubs f0, f29, f0
    fmadds f1, f3, f4, f30
    fnmsubs f0, f31, f0, f29
    stfs f0, 0x20(r31)
    lfs f0, 0x24(r31)
    fsubs f0, f28, f0
    fnmsubs f0, f31, f0, f28
    stfs f0, 0x24(r31)
    lfs f0, 0x28(r31)
    fsubs f0, f1, f0
    fnmsubs f0, f31, f0, f1
    stfs f0, 0x28(r31)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f1, 0xc(r3)
    lfs f0, 0x20(r31)
    fsubs f0, f1, f0
    stfs f0, 0x38(r1)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f1, 0x1c(r3)
    lfs f0, 0x24(r31)
    fsubs f0, f1, f0
    stfs f0, 0x3c(r1)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f1, 0x2c(r3)
    addi r3, r1, 0x38
    lfs f0, 0x28(r31)
    fsubs f0, f1, f0
    stfs f0, 0x40(r1)
    bl fn_8025E30C
    lfs f0, lbl_806D7450(r2)
    lfs f3, 0x1c(r31)
    fsubs f2, f0, f31
    lfs f0, lbl_806D7418(r2)
    fadds f2, f3, f2
    stfs f2, 0x1c(r31)
    lfs f2, 0x1c(r31)
    fcmpo cr0, f2, f0
    bge CoinSystem_UpdateAll_L_8013A064
    lfs f2, 0x24(r31)
    lfs f0, lbl_806D73FC(r2)
    fadds f0, f2, f0
    stfs f0, 0x24(r31)
    CoinSystem_UpdateAll_L_8013A064:
    lfs f3, 0x34(r31)
    lfs f2, lbl_806D7454(r2)
    lfs f0, lbl_806D7410(r2)
    fsubs f2, f3, f2
    fcmpo cr0, f1, f0
    stfs f2, 0x34(r31)
    bge CoinSystem_UpdateAll_L_8013A4D8
    li r0, 0x3
    lfs f1, lbl_806D73E8(r2)
    stw r0, 0x18(r31)
    lfs f0, lbl_806D73EC(r2)
    stfs f1, 0x1c(r31)
    stfs f0, 0x34(r31)
    stfs f1, 0x2c(r31)
    b CoinSystem_UpdateAll_L_8013A4D8
    lfs f1, 0x1c(r31)
    lfs f3, lbl_806D73E8(r2)
    fcmpo cr0, f1, f3
    ble CoinSystem_UpdateAll_L_8013A0C0
    lfs f0, lbl_806D73EC(r2)
    fsubs f0, f1, f0
    stfs f0, 0x1c(r31)
    b CoinSystem_UpdateAll_L_8013A4D8
    CoinSystem_UpdateAll_L_8013A0C0:
    stfs f3, 0x1c(r31)
    lis r3, lbl_80495A94@ha
    addi r4, r3, lbl_80495A94@l
    lfs f2, lbl_806D7458(r2)
    lwz r0, lbl_806D1544(r13)
    li r3, 0x6
    lfs f0, lbl_806D745C(r2)
    slwi r0, r0, 2
    lfsx f1, r4, r0
    fmsubs f0, f2, f1, f0
    stfs f0, 0x2c(r31)
    stfs f3, 0x34(r31)
    lwz r0, 0x18(r31)
    cmpwi r0, 0x8
    bne CoinSystem_UpdateAll_L_8013A100
    li r3, 0x9
    CoinSystem_UpdateAll_L_8013A100:
    stw r3, 0x18(r31)
    lwz r3, lbl_806D1544(r13)
    addi r0, r3, 0x1
    cmpwi r0, 0x30
    stw r0, lbl_806D1544(r13)
    blt CoinSystem_UpdateAll_L_8013A4D8
    li r0, 0x0
    stw r0, lbl_806D1544(r13)
    b CoinSystem_UpdateAll_L_8013A4D8
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D7438(r2)
    lwz r3, 0x10(r31)
    fdivs f28, f1, f0
    bl KartDriver_GetKartRootMtx
    lfs f0, 0xc(r3)
    stfs f0, 0x20(r31)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f0, 0x1c(r3)
    stfs f0, 0x24(r31)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f0, 0x2c(r3)
    stfs f0, 0x28(r31)
    bl GetCourseScene3D
    cmplwi r3, 0x0
    beq CoinSystem_UpdateAll_L_8013A1A4
    bl GetCourseScene3D
    addi r4, r1, 0x20
    bl CObj_LoadProjMatrix
    bl GetCourseScene3D
    addi r4, r1, 0x14
    bl CObj_ApplyScissor
    addi r3, r1, 0x20
    addi r4, r1, 0x14
    addi r5, r1, 0x2c
    bl Vec3_Subtract
    addi r3, r1, 0x2c
    mr r4, r3
    bl Vec3_Normalize
    b CoinSystem_UpdateAll_L_8013A1D4
    CoinSystem_UpdateAll_L_8013A1A4:
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f0, 0x8(r3)
    stfs f0, 0x2c(r1)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f0, 0x18(r3)
    stfs f0, 0x30(r1)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f0, 0x28(r3)
    stfs f0, 0x34(r1)
    CoinSystem_UpdateAll_L_8013A1D4:
    lfs f1, lbl_806D7460(r2)
    addi r3, r1, 0x50
    lfs f0, 0x2c(r31)
    li r4, 0x59
    fadds f1, f1, f0
    bl fn_8025D770
    addi r4, r1, 0x2c
    addi r3, r1, 0x50
    mr r5, r4
    bl fn_8025DF40
    lwz r3, 0x10(r31)
    bl KartMovement_GetVelocityMagnitude
    lfs f0, lbl_806D7464(r2)
    addi r3, r1, 0x2c
    mr r4, r3
    fmuls f0, f0, f1
    fmuls f1, f28, f0
    bl fn_8025E2AC
    addi r3, r31, 0x20
    addi r4, r1, 0x2c
    mr r5, r3
    bl fn_8025E264
    lfs f0, lbl_806D7468(r2)
    fmuls f1, f0, f28
    bl LUT_Sin12Bit
    fmr f30, f1
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f0, 0x4(r3)
    stfs f0, 0x2c(r1)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f0, 0x14(r3)
    stfs f0, 0x30(r1)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f1, lbl_806D746C(r2)
    lfs f2, 0x24(r3)
    addi r3, r1, 0x2c
    lfs f0, lbl_806D73F8(r2)
    mr r4, r3
    stfs f2, 0x34(r1)
    fmadds f1, f1, f30, f0
    bl fn_8025E2AC
    addi r3, r31, 0x20
    addi r4, r1, 0x2c
    mr r5, r3
    bl fn_8025E264
    lfs f2, 0x30(r31)
    lfs f1, lbl_806D7470(r2)
    lfs f0, lbl_806D742C(r2)
    fadds f1, f2, f1
    stfs f1, 0x30(r31)
    lfs f1, 0x30(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CoinSystem_UpdateAll_L_8013A2C0
    fsubs f0, f1, f0
    stfs f0, 0x30(r31)
    CoinSystem_UpdateAll_L_8013A2C0:
    lfs f1, 0x1c(r31)
    lfs f2, lbl_806D73EC(r2)
    lfs f0, lbl_806D73F8(r2)
    fadds f1, f1, f2
    fcmpo cr0, f1, f0
    stfs f1, 0x1c(r31)
    bge CoinSystem_UpdateAll_L_8013A2E4
    stfs f2, 0x34(r31)
    b CoinSystem_UpdateAll_L_8013A2E8
    CoinSystem_UpdateAll_L_8013A2E4:
    stfs f30, 0x34(r31)
    CoinSystem_UpdateAll_L_8013A2E8:
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D7438(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CoinSystem_UpdateAll_L_8013A4D8
    li r0, 0x0
    lfs f1, lbl_806D7474(r2)
    stw r0, 0x18(r31)
    lfs f0, lbl_806D73E8(r2)
    stfs f1, 0x1c(r31)
    stw r0, 0x10(r31)
    stfs f0, 0x34(r31)
    b CoinSystem_UpdateAll_L_8013A4D8
    lfs f2, lbl_806D73E8(r2)
    lfs f0, 0x1c(r31)
    fcmpu cr0, f2, f0
    bne CoinSystem_UpdateAll_L_8013A340
    lfs f1, lbl_806D73EC(r2)
    lfs f0, lbl_806D7444(r2)
    stfs f1, 0x34(r31)
    stfs f0, 0x1c(r31)
    stfs f2, 0x2c(r31)
    CoinSystem_UpdateAll_L_8013A340:
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D7478(r2)
    lfs f2, lbl_806D7428(r2)
    fdivs f0, f1, f0
    fmuls f1, f2, f0
    bl LUT_Sin12Bit
    lfs f3, lbl_806D7424(r2)
    lfs f2, 0x30(r31)
    lfs f0, lbl_806D742C(r2)
    fmadds f1, f3, f1, f2
    stfs f1, 0x30(r31)
    lfs f1, 0x30(r31)
    fcmpo cr0, f1, f0
    bge CoinSystem_UpdateAll_L_8013A380
    fadds f0, f1, f0
    stfs f0, 0x30(r31)
    CoinSystem_UpdateAll_L_8013A380:
    lfs f1, 0x30(r31)
    lfs f0, lbl_806D742C(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CoinSystem_UpdateAll_L_8013A39C
    fsubs f0, f1, f0
    stfs f0, 0x30(r31)
    CoinSystem_UpdateAll_L_8013A39C:
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f30, 0xc(r3)
    lwz r3, 0x10(r31)
    bl KartMovement_GetVelocityPtr
    lfs f1, 0x0(r3)
    lfs f0, lbl_806D7418(r2)
    lwz r3, 0x10(r31)
    fmadds f28, f0, f1, f30
    bl KartDriver_GetKartRootMtx
    lfs f30, 0x1c(r3)
    lwz r3, 0x10(r31)
    bl KartMovement_GetVelocityPtr
    lfs f1, 0x4(r3)
    lfs f0, lbl_806D7418(r2)
    lwz r3, 0x10(r31)
    fmadds f29, f0, f1, f30
    bl KartDriver_GetKartRootMtx
    lfs f30, 0x2c(r3)
    lwz r3, 0x10(r31)
    bl KartMovement_GetVelocityPtr
    lfs f3, lbl_806D7418(r2)
    lfs f1, 0x1c(r31)
    lfs f0, 0x20(r31)
    fdivs f1, f1, f3
    lfs f2, lbl_806D73EC(r2)
    lfs f4, 0x8(r3)
    fsubs f31, f2, f1
    fsubs f0, f28, f0
    fmadds f1, f3, f4, f30
    fnmsubs f0, f31, f0, f28
    stfs f0, 0x20(r31)
    lfs f0, 0x24(r31)
    fsubs f0, f29, f0
    fnmsubs f0, f31, f0, f29
    stfs f0, 0x24(r31)
    lfs f0, 0x28(r31)
    fsubs f0, f1, f0
    fnmsubs f0, f31, f0, f1
    stfs f0, 0x28(r31)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f1, 0xc(r3)
    lfs f0, 0x20(r31)
    fsubs f0, f1, f0
    stfs f0, 0x8(r1)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f1, 0x1c(r3)
    lfs f0, 0x24(r31)
    fsubs f0, f1, f0
    stfs f0, 0xc(r1)
    lwz r3, 0x10(r31)
    bl KartDriver_GetKartRootMtx
    lfs f1, 0x2c(r3)
    addi r3, r1, 0x8
    lfs f0, 0x28(r31)
    fsubs f0, f1, f0
    stfs f0, 0x10(r1)
    bl fn_8025E30C
    lfs f2, lbl_806D7450(r2)
    lfs f0, lbl_806D747C(r2)
    fsubs f3, f2, f31
    lfs f4, 0x1c(r31)
    lfs f2, lbl_806D7454(r2)
    fcmpo cr0, f1, f0
    fadds f0, f4, f3
    stfs f0, 0x1c(r31)
    lfs f0, 0x34(r31)
    fsubs f0, f0, f2
    stfs f0, 0x34(r31)
    bge CoinSystem_UpdateAll_L_8013A4D8
    li r0, 0x3
    lfs f1, lbl_806D73E8(r2)
    stw r0, 0x18(r31)
    lfs f0, lbl_806D73EC(r2)
    stfs f1, 0x1c(r31)
    stfs f0, 0x34(r31)
    stfs f1, 0x2c(r31)
    CoinSystem_UpdateAll_L_8013A4D8:
    addi r31, r31, 0xc0
    CoinSystem_UpdateAll_L_8013A4DC:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r31, r0
    blt CoinSystem_UpdateAll_L_80139A48
    CoinSystem_UpdateAll_L_8013A4F4:
    psq_l f31, 0xd8(r1), 0, 0
    lfd f31, 0xd0(r1)
    psq_l f30, 0xc8(r1), 0, 0
    lfd f30, 0xc0(r1)
    psq_l f29, 0xb8(r1), 0, 0
    lfd f29, 0xb0(r1)
    psq_l f28, 0xa8(r1), 0, 0
    lfd f28, 0xa0(r1)
    lwz r31, 0x9c(r1)
    lwz r30, 0x98(r1)
    lwz r29, 0x94(r1)
    lwz r0, 0xe4(r1)
    lwz r28, 0x90(r1)
    mtlr r0
    addi r1, r1, 0xe0
    blr
}

