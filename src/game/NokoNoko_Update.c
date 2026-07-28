/* === extracted from auto_NokoNoko_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void LookupCos();
extern void LookupSin();
extern void Terrain_GetGroundHeight();
extern void Terrain_RaycastWall();
extern void Vec3_Dot();
extern void Vec3_Magnitude();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void fn_8025E264();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_nokonokoHead;
extern unsigned int lbl_806CFBD8;
extern unsigned int lbl_806D168C;
extern unsigned int lbl_806D931C;
extern unsigned int lbl_806D9320;
extern unsigned int lbl_806D9324;
extern unsigned int lbl_806D9328;
extern unsigned int lbl_806D932C;
extern unsigned int lbl_806D9330;
extern unsigned int lbl_806D9334;
extern unsigned int lbl_806D9338;
extern unsigned int lbl_806D933C;
extern unsigned int lbl_806D9340;
extern unsigned int lbl_806D9344;
extern unsigned int lbl_806D9348;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80377664[];
extern unsigned int lbl_80377694[];
extern unsigned int lbl_80495D28[];
extern unsigned int lbl_80677ED8[];

/* --- function index (1 fns, .text 0x80187D2C..0x801884E8) ---
 * [  0] 0x80187D2C size:0x7BC   global NokoNoko_Update
 */

/* --- forward decls --- */
asm void NokoNoko_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NokoNoko_Update[8] = {
    0x40, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NokoNoko_Update = {
    (void *)&NokoNoko_Update, 0x000007BC, (void *)extab_NokoNoko_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NokoNoko_Update(void) { /* 0x80187D2C size:0x7BC */
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
    stmw r24, 0x90(r1)
    mr r27, r3
    lwz r0, 0xc(r3)
    lfs f31, 0x1c(r3)
    cmpwi r0, 0x4
    lfs f30, 0x20(r3)
    lfs f29, 0x24(r3)
    bge NokoNoko_Update_L_80188164
    lfs f2, 0x28(r27)
    lfs f1, 0x30(r27)
    lfs f0, lbl_806D9324(r2)
    fadds f1, f2, f1
    stfs f1, 0x28(r27)
    lfs f1, 0x28(r27)
    fcmpo cr0, f1, f0
    bge NokoNoko_Update_L_80187D9C
    lfs f0, lbl_806D9328(r2)
    fadds f0, f1, f0
    stfs f0, 0x28(r27)
    NokoNoko_Update_L_80187D9C:
    lfs f1, 0x28(r27)
    lfs f0, lbl_806D9328(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne NokoNoko_Update_L_80187DB8
    fsubs f0, f1, f0
    stfs f0, 0x28(r27)
    NokoNoko_Update_L_80187DB8:
    lfs f1, 0x28(r27)
    bl LookupSin
    lfs f0, 0x2c(r27)
    lfs f2, lbl_806CFBD8(r13)
    fmuls f3, f0, f1
    lfs f1, 0x1c(r27)
    lfs f0, lbl_806D931C(r2)
    fmadds f1, f2, f3, f1
    stfs f1, 0x1c(r27)
    lfs f1, 0x20(r27)
    fsubs f0, f1, f0
    stfs f0, 0x20(r27)
    lfs f1, 0x28(r27)
    bl LookupCos
    lfs f0, 0x2c(r27)
    lfs f2, lbl_806CFBD8(r13)
    fmuls f1, f0, f1
    lfs f0, 0x24(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x24(r27)
    lwz r3, 0x18(r27)
    cmpwi r3, 0x0
    ble NokoNoko_Update_L_80187E1C
    subi r0, r3, 0x1
    stw r0, 0x18(r27)
    NokoNoko_Update_L_80187E1C:
    lfs f2, 0x14(r27)
    lfs f1, lbl_806D931C(r2)
    lfs f0, lbl_806D9320(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x14(r27)
    cror eq, gt, eq
    bne NokoNoko_Update_L_80187E44
    lfs f0, lbl_806D9324(r2)
    stfs f0, 0x14(r27)
    NokoNoko_Update_L_80187E44:
    lwz r0, 0x18(r27)
    cmpwi r0, 0x0
    bne NokoNoko_Update_L_80187F94
    lwz r0, 0x4(r27)
    cmpwi r0, 0x0
    blt NokoNoko_Update_L_80187F94
    lwz r3, 0x8(r27)
    addi r0, r3, 0x1
    stw r0, 0x8(r27)
    lwz r0, 0x8(r27)
    cmpwi r0, 0x0
    bge NokoNoko_Update_L_80187E7C
    li r0, 0x0
    stw r0, 0x8(r27)
    NokoNoko_Update_L_80187E7C:
    lwz r4, 0x4(r27)
    lis r3, lbl_80495D28@ha
    lwz r0, 0x8(r27)
    addi r3, r3, lbl_80495D28@l
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r3, r3, r4
    lwzx r0, r3, r0
    cmpwi r0, -0x1
    bne NokoNoko_Update_L_80187EAC
    li r0, 0x0
    stw r0, 0x8(r27)
    NokoNoko_Update_L_80187EAC:
    lwz r4, 0x4(r27)
    lis r3, lbl_80495D28@ha
    lwz r0, 0x8(r27)
    addi r3, r3, lbl_80495D28@l
    slwi r4, r4, 2
    lwz r5, 0x10(r27)
    mulli r0, r0, 0x14
    lwzx r3, r3, r4
    add r3, r3, r0
    lwz r0, 0x4(r3)
    cmpw r5, r0
    beq NokoNoko_Update_L_80187EF0
    stw r5, 0x34(r27)
    lfs f0, lbl_806D9324(r2)
    stfs f0, 0x38(r27)
    lfs f0, 0x14(r27)
    stfs f0, 0x3c(r27)
    NokoNoko_Update_L_80187EF0:
    lwz r4, 0x4(r27)
    lis r3, lbl_80495D28@ha
    lwz r0, 0x8(r27)
    addi r3, r3, lbl_80495D28@l
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r4, r3, r4
    lwzx r0, r4, r0
    stw r0, 0xc(r27)
    lwz r4, 0x4(r27)
    lwz r0, 0x8(r27)
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r4, r3, r4
    add r4, r4, r0
    lwz r0, 0x4(r4)
    stw r0, 0x10(r27)
    lwz r4, 0x4(r27)
    lwz r0, 0x8(r27)
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r4, r3, r4
    add r4, r4, r0
    lwz r0, 0x8(r4)
    stw r0, 0x18(r27)
    lwz r4, 0x4(r27)
    lwz r0, 0x8(r27)
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r4, r3, r4
    add r4, r4, r0
    lfs f0, 0xc(r4)
    stfs f0, 0x2c(r27)
    lwz r4, 0x4(r27)
    lwz r0, 0x8(r27)
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r3, r3, r4
    add r3, r3, r0
    lfs f0, 0x10(r3)
    stfs f0, 0x30(r27)
    NokoNoko_Update_L_80187F94:
    lfs f1, 0x2c(r27)
    lfs f0, lbl_806D9324(r2)
    fcmpo cr0, f1, f0
    ble NokoNoko_Update_L_801881E4
    lwz r24, g_nokonokoHead(r13)
    b NokoNoko_Update_L_8018806C
    NokoNoko_Update_L_80187FAC:
    cmplw r24, r27
    beq NokoNoko_Update_L_80188068
    addi r3, r24, 0x1c
    addi r4, r27, 0x1c
    addi r5, r1, 0x24
    bl Vec3_Subtract
    addi r3, r1, 0x24
    bl Vec3_Magnitude
    lfs f0, lbl_806D932C(r2)
    fcmpo cr0, f1, f0
    bge NokoNoko_Update_L_80188068
    addi r3, r1, 0x24
    mr r4, r3
    bl Vec3_Normalize
    lfs f1, 0x28(r27)
    bl LookupSin
    lfs f0, lbl_806D9324(r2)
    stfs f1, 0x18(r1)
    stfs f0, 0x1c(r1)
    lfs f1, 0x28(r27)
    bl LookupCos
    stfs f1, 0x20(r1)
    addi r3, r1, 0x24
    addi r4, r1, 0x18
    bl Vec3_Dot
    lfs f0, lbl_806D9330(r2)
    fcmpo cr0, f1, f0
    ble NokoNoko_Update_L_80188068
    lwz r0, 0x10(r27)
    cmpwi r0, 0x1
    beq NokoNoko_Update_L_8018803C
    stw r0, 0x34(r27)
    lfs f0, lbl_806D9324(r2)
    stfs f0, 0x38(r27)
    lfs f0, 0x14(r27)
    stfs f0, 0x3c(r27)
    NokoNoko_Update_L_8018803C:
    li r0, -0x1
    li r3, 0x1
    stw r0, 0x8(r27)
    li r0, 0x78
    lfs f1, lbl_806D9324(r2)
    stw r3, 0xc(r27)
    lfs f0, lbl_806D9334(r2)
    stw r3, 0x10(r27)
    stw r0, 0x18(r27)
    stfs f1, 0x2c(r27)
    stfs f0, 0x30(r27)
    NokoNoko_Update_L_80188068:
    lwz r24, 0x0(r24)
    NokoNoko_Update_L_8018806C:
    cmplwi r24, 0x0
    bne NokoNoko_Update_L_80187FAC
    lfs f1, lbl_806D168C(r13)
    lfs f0, lbl_806D9324(r2)
    fcmpo cr0, f1, f0
    ble NokoNoko_Update_L_801881E4
    lwz r0, 0xc(r27)
    cmpwi r0, 0x2
    beq NokoNoko_Update_L_80188098
    cmpwi r0, 0x3
    bne NokoNoko_Update_L_801881E4
    NokoNoko_Update_L_80188098:
    lis r3, lbl_80677ED8@ha
    addi r4, r27, 0x1c
    addi r3, r3, lbl_80677ED8@l
    addi r5, r1, 0x24
    bl Vec3_Subtract
    addi r3, r1, 0x24
    bl Vec3_Magnitude
    lfs f2, lbl_806D933C(r2)
    lfs f0, lbl_806D168C(r13)
    lfs f3, lbl_806D9338(r2)
    fadds f0, f2, f0
    fmuls f0, f3, f0
    fcmpo cr0, f1, f0
    bge NokoNoko_Update_L_801881E4
    addi r3, r1, 0x24
    mr r4, r3
    bl Vec3_Normalize
    lfs f1, 0x28(r27)
    bl LookupSin
    lfs f0, lbl_806D9324(r2)
    stfs f1, 0x18(r1)
    stfs f0, 0x1c(r1)
    lfs f1, 0x28(r27)
    bl LookupCos
    stfs f1, 0x20(r1)
    addi r3, r1, 0x24
    addi r4, r1, 0x18
    bl Vec3_Dot
    lfs f0, lbl_806D9330(r2)
    fcmpo cr0, f1, f0
    ble NokoNoko_Update_L_801881E4
    lwz r0, 0x10(r27)
    cmpwi r0, 0x1
    beq NokoNoko_Update_L_80188134
    stw r0, 0x34(r27)
    lfs f0, lbl_806D9324(r2)
    stfs f0, 0x38(r27)
    lfs f0, 0x14(r27)
    stfs f0, 0x3c(r27)
    NokoNoko_Update_L_80188134:
    li r0, -0x1
    li r3, 0x1
    stw r0, 0x8(r27)
    li r0, 0x78
    lfs f1, lbl_806D9324(r2)
    stw r3, 0xc(r27)
    lfs f0, lbl_806D9334(r2)
    stw r3, 0x10(r27)
    stw r0, 0x18(r27)
    stfs f1, 0x2c(r27)
    stfs f0, 0x30(r27)
    b NokoNoko_Update_L_801881E4
    NokoNoko_Update_L_80188164:
    bne NokoNoko_Update_L_801881E4
    lfs f1, 0x28(r27)
    bl LookupSin
    lfs f3, lbl_806D9340(r2)
    lfs f0, 0x1c(r27)
    lfs f2, lbl_806D9344(r2)
    fnmsubs f1, f3, f1, f0
    lfs f0, lbl_806D9338(r2)
    stfs f1, 0x1c(r27)
    lfs f1, 0x14(r27)
    lfs f3, 0x20(r27)
    fnmsubs f0, f2, f1, f0
    fadds f0, f3, f0
    stfs f0, 0x20(r27)
    lfs f1, 0x28(r27)
    bl LookupCos
    lfs f3, lbl_806D9340(r2)
    lfs f0, 0x24(r27)
    lfs f2, lbl_806D931C(r2)
    fnmsubs f1, f3, f1, f0
    lfs f0, lbl_806D9320(r2)
    stfs f1, 0x24(r27)
    lfs f1, 0x14(r27)
    fadds f1, f1, f2
    fcmpo cr0, f1, f0
    stfs f1, 0x14(r27)
    cror eq, gt, eq
    bne NokoNoko_Update_L_801881E4
    li r3, 0x5
    li r0, -0x1
    stw r3, 0xc(r27)
    stw r0, 0x10(r27)
    NokoNoko_Update_L_801881E4:
    lis r3, lbl_80377664@ha
    lfs f6, lbl_806D933C(r2)
    addi r26, r3, lbl_80377664@l
    lis r3, lbl_80377694@ha
    lwz r25, 0x0(r26)
    addi r24, r3, lbl_80377694@l
    lwz r12, 0x4(r26)
    fadds f3, f6, f31
    lwz r11, 0x8(r26)
    fsubs f2, f31, f6
    lwz r10, 0xc(r26)
    fadds f1, f6, f29
    lwz r9, 0x10(r26)
    lwz r8, 0x14(r26)
    fsubs f0, f29, f6
    lwz r7, 0x18(r26)
    addi r31, r1, 0x30
    lwz r6, 0x1c(r26)
    addi r30, r1, 0x60
    lwz r5, 0x20(r26)
    lwz r4, 0x24(r26)
    li r28, 0x0
    lwz r3, 0x28(r26)
    li r29, 0x0
    lwz r0, 0x2c(r26)
    li r26, 0x0
    stw r25, 0x60(r1)
    lwz r25, 0x0(r24)
    stw r12, 0x64(r1)
    lwz r12, 0x4(r24)
    stw r11, 0x68(r1)
    lwz r11, 0x8(r24)
    stw r10, 0x6c(r1)
    lwz r10, 0xc(r24)
    stw r9, 0x70(r1)
    lwz r9, 0x10(r24)
    stw r8, 0x74(r1)
    lwz r8, 0x14(r24)
    stw r7, 0x78(r1)
    lwz r7, 0x18(r24)
    stw r6, 0x7c(r1)
    lwz r6, 0x1c(r24)
    stw r5, 0x80(r1)
    lwz r5, 0x20(r24)
    stw r4, 0x84(r1)
    lwz r4, 0x24(r24)
    stw r3, 0x88(r1)
    lwz r3, 0x28(r24)
    stw r0, 0x8c(r1)
    lwz r0, 0x2c(r24)
    stfs f3, 0x60(r1)
    stfs f30, 0x64(r1)
    stfs f29, 0x68(r1)
    stfs f2, 0x6c(r1)
    stfs f30, 0x70(r1)
    stfs f29, 0x74(r1)
    stfs f31, 0x78(r1)
    stfs f30, 0x7c(r1)
    stfs f1, 0x80(r1)
    stfs f31, 0x84(r1)
    stfs f30, 0x88(r1)
    stfs f0, 0x8c(r1)
    stw r25, 0x30(r1)
    stw r12, 0x34(r1)
    stw r11, 0x38(r1)
    stw r10, 0x3c(r1)
    stw r9, 0x40(r1)
    stw r8, 0x44(r1)
    stw r7, 0x48(r1)
    stw r6, 0x4c(r1)
    stw r5, 0x50(r1)
    stw r4, 0x54(r1)
    stw r3, 0x58(r1)
    stw r0, 0x5c(r1)
    lfs f5, 0x1c(r27)
    fadds f0, f6, f5
    fsubs f2, f5, f6
    stfs f0, 0x30(r1)
    lfs f4, 0x20(r27)
    stfs f4, 0x34(r1)
    lfs f3, 0x24(r27)
    fadds f1, f6, f3
    stfs f3, 0x38(r1)
    fsubs f0, f3, f6
    stfs f2, 0x3c(r1)
    stfs f4, 0x40(r1)
    stfs f3, 0x44(r1)
    stfs f5, 0x48(r1)
    stfs f4, 0x4c(r1)
    stfs f1, 0x50(r1)
    stfs f5, 0x54(r1)
    stfs f4, 0x58(r1)
    stfs f0, 0x5c(r1)
    NokoNoko_Update_L_80188358:
    mr r3, r30
    mr r4, r31
    addi r5, r1, 0x18
    addi r6, r1, 0xc
    bl Terrain_RaycastWall
    clrlwi. r0, r3, 24
    beq NokoNoko_Update_L_801883D0
    mr r4, r31
    addi r3, r1, 0x18
    addi r5, r1, 0x24
    bl Vec3_Subtract
    lfs f0, lbl_806D9324(r2)
    addi r3, r27, 0x1c
    mr r5, r3
    addi r4, r1, 0x24
    stfs f0, 0x28(r1)
    bl fn_8025E264
    addi r24, r1, 0x30
    mr r25, r29
    add r24, r24, r26
    b NokoNoko_Update_L_801883C4
    NokoNoko_Update_L_801883AC:
    mr r3, r24
    mr r5, r24
    addi r4, r1, 0x24
    bl fn_8025E264
    addi r24, r24, 0xc
    addi r25, r25, 0x1
    NokoNoko_Update_L_801883C4:
    cmpwi r25, 0x4
    blt NokoNoko_Update_L_801883AC
    li r28, 0x1
    NokoNoko_Update_L_801883D0:
    addi r29, r29, 0x1
    addi r30, r30, 0xc
    cmpwi r29, 0x4
    addi r26, r26, 0xc
    addi r31, r31, 0xc
    blt NokoNoko_Update_L_80188358
    clrlwi. r0, r28, 24
    beq NokoNoko_Update_L_80188448
    lwz r0, 0xc(r27)
    cmpwi r0, 0x4
    bge NokoNoko_Update_L_80188448
    lwz r0, 0x10(r27)
    cmpwi r0, 0x1
    beq NokoNoko_Update_L_8018841C
    stw r0, 0x34(r27)
    lfs f0, lbl_806D9324(r2)
    stfs f0, 0x38(r27)
    lfs f0, 0x14(r27)
    stfs f0, 0x3c(r27)
    NokoNoko_Update_L_8018841C:
    li r0, -0x1
    li r3, 0x1
    stw r0, 0x8(r27)
    li r0, 0x78
    lfs f1, lbl_806D9324(r2)
    stw r3, 0xc(r27)
    lfs f0, lbl_806D9334(r2)
    stw r3, 0x10(r27)
    stw r0, 0x18(r27)
    stfs f1, 0x2c(r27)
    stfs f0, 0x30(r27)
    NokoNoko_Update_L_80188448:
    addi r3, r27, 0x1c
    addi r4, r1, 0x8
    li r5, 0x0
    li r6, 0x0
    bl Terrain_GetGroundHeight
    clrlwi. r0, r3, 24
    beq NokoNoko_Update_L_80188478
    lfs f0, 0x20(r27)
    lfs f1, 0x8(r1)
    fcmpo cr0, f0, f1
    bge NokoNoko_Update_L_80188478
    stfs f1, 0x20(r27)
    NokoNoko_Update_L_80188478:
    lwz r0, 0x34(r27)
    cmpwi r0, -0x1
    beq NokoNoko_Update_L_801884BC
    lfs f2, 0x38(r27)
    lfs f1, lbl_806D9348(r2)
    lfs f0, lbl_806D931C(r2)
    fadds f1, f2, f1
    stfs f1, 0x38(r27)
    lfs f1, 0x38(r27)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne NokoNoko_Update_L_801884BC
    li r0, -0x1
    lfs f0, lbl_806D9324(r2)
    stw r0, 0x34(r27)
    stfs f0, 0x38(r27)
    stfs f0, 0x3c(r27)
    NokoNoko_Update_L_801884BC:
    psq_l f31, 0xd8(r1), 0, 0
    lfd f31, 0xd0(r1)
    psq_l f30, 0xc8(r1), 0, 0
    lfd f30, 0xc0(r1)
    psq_l f29, 0xb8(r1), 0, 0
    lfd f29, 0xb0(r1)
    lmw r24, 0x90(r1)
    lwz r0, 0xe4(r1)
    mtlr r0
    addi r1, r1, 0xe0
    blr
}

