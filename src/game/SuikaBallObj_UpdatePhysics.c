extern void Object_DriveAnimMatrix();
extern void PSMTXConcat();
extern void PSMTXRotAxisRad();
extern void PSMTXRotRad();
extern void PSVECAdd();
extern void PSVECScale();
extern void Terrain_GetGroundHeight();
extern void Terrain_RaycastWall();
extern void Vec3_Dot();
extern void Vec3_Magnitude();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern unsigned int lbl_806D6E58;
extern unsigned int lbl_806D6E5C;
extern unsigned int lbl_806D6E60;
extern unsigned int lbl_806D6E64;
extern unsigned int lbl_806D6E68;
extern unsigned int lbl_806D6E6C;
extern unsigned int lbl_806D6E70;
extern unsigned int lbl_806D6E74;
extern unsigned int lbl_806D6E78;
extern unsigned int lbl_806D6E7C;
extern unsigned int lbl_806D6E80;
extern unsigned int lbl_806D6E84;
extern unsigned int lbl_806D6E88;
extern unsigned int lbl_80355918[];
extern unsigned int lbl_80355948[];
asm void SuikaBallObj_UpdatePhysics(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SuikaBallObj_UpdatePhysics[8] = {
    0x49, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SuikaBallObj_UpdatePhysics = {
    (void *)&SuikaBallObj_UpdatePhysics, 0x00000838, (void *)extab_SuikaBallObj_UpdatePhysics
};



asm void SuikaBallObj_UpdatePhysics(void) { /* 0x801240E4 size:0x838 */
    nofralloc
    stwu r1, -0x1b0(r1)
    mflr r0
    stw r0, 0x1b4(r1)
    stfd f31, 0x1a0(r1)
    psq_st f31, 0x1a8(r1), 0, 0
    stfd f30, 0x190(r1)
    psq_st f30, 0x198(r1), 0, 0
    stfd f29, 0x180(r1)
    psq_st f29, 0x188(r1), 0, 0
    stfd f28, 0x170(r1)
    psq_st f28, 0x178(r1), 0, 0
    stfd f27, 0x160(r1)
    psq_st f27, 0x168(r1), 0, 0
    stfd f26, 0x150(r1)
    psq_st f26, 0x158(r1), 0, 0
    stmw r23, 0x12c(r1)
    li r0, 0x0
    fmr f27, f1
    stb r0, 0x60(r3)
    mr. r24, r4
    mr r27, r3
    mr r23, r5
    lfs f0, 0x4(r3)
    lfs f30, 0x38(r3)
    fadds f31, f27, f0
    lfs f29, 0x3c(r3)
    lfs f28, 0x40(r3)
    beq SuikaBallObj_UpdatePhysics_L_80124428
    cmplwi r23, 0x0
    beq SuikaBallObj_UpdatePhysics_L_80124428
    lfs f0, 0x0(r24)
    addi r3, r27, 0x38
    addi r4, r1, 0x24
    addi r5, r1, 0x3c
    stfs f0, 0x18(r1)
    lfs f0, 0x10(r24)
    stfs f0, 0x1c(r1)
    lfs f0, 0x20(r24)
    stfs f0, 0x20(r1)
    lfs f0, 0x8(r24)
    stfs f0, 0xc(r1)
    lfs f0, 0x18(r24)
    stfs f0, 0x10(r1)
    lfs f0, 0x28(r24)
    stfs f0, 0x14(r1)
    lfs f0, 0xc(r24)
    stfs f0, 0x24(r1)
    lfs f0, 0x1c(r24)
    stfs f0, 0x28(r1)
    lfs f0, 0x2c(r24)
    stfs f0, 0x2c(r1)
    bl Vec3_Subtract
    addi r3, r1, 0x3c
    bl Vec3_Magnitude
    fcmpo cr0, f1, f31
    bge SuikaBallObj_UpdatePhysics_L_80124428
    li r0, 0x1
    addi r3, r1, 0x3c
    stb r0, 0x60(r27)
    mr r4, r3
    bl Vec3_Normalize
    lfs f1, 0x3c(r1)
    addi r3, r27, 0x44
    lfs f0, 0x24(r1)
    addi r4, r1, 0x30
    fmadds f0, f1, f31, f0
    stfs f0, 0x38(r27)
    lfs f1, 0x40(r1)
    lfs f0, 0x28(r1)
    fmadds f0, f1, f31, f0
    stfs f0, 0x3c(r27)
    lfs f1, 0x44(r1)
    lfs f0, 0x2c(r1)
    fmadds f0, f1, f31, f0
    stfs f0, 0x40(r27)
    bl Vec3_Normalize
    addi r3, r1, 0x3c
    addi r4, r1, 0x30
    bl Vec3_Dot
    lfs f0, lbl_806D6E58(r2)
    fcmpo cr0, f1, f0
    bge SuikaBallObj_UpdatePhysics_L_8012425C
    addi r3, r1, 0x3c
    addi r4, r27, 0x44
    bl Vec3_Dot
    lfs f0, lbl_806D6E5C(r2)
    addi r3, r1, 0x3c
    addi r4, r1, 0x30
    fmuls f1, f0, f1
    bl PSVECScale
    addi r4, r27, 0x44
    addi r3, r1, 0x30
    mr r5, r4
    bl PSVECAdd
    SuikaBallObj_UpdatePhysics_L_8012425C:
    lfs f2, 0x3c(r1)
    addi r3, r1, 0x30
    lfs f1, 0x40(r1)
    addi r4, r1, 0xc
    lfs f0, 0x44(r1)
    fmuls f2, f2, f27
    fmuls f1, f1, f27
    fmuls f0, f0, f27
    stfs f2, 0x30(r1)
    stfs f1, 0x34(r1)
    stfs f0, 0x38(r1)
    bl Vec3_Dot
    lfs f0, lbl_806D6E58(r2)
    fcmpu cr0, f1, f0
    beq SuikaBallObj_UpdatePhysics_L_80124428
    addi r3, r1, 0x30
    addi r4, r1, 0x18
    bl Vec3_Dot
    fmr f26, f1
    lfs f0, lbl_806D6E58(r2)
    fcmpo cr0, f26, f0
    bge SuikaBallObj_UpdatePhysics_L_801242BC
    fneg f27, f26
    b SuikaBallObj_UpdatePhysics_L_801242C0
    SuikaBallObj_UpdatePhysics_L_801242BC:
    fmr f27, f26
    SuikaBallObj_UpdatePhysics_L_801242C0:
    mr r3, r23
    bl Vec3_Magnitude
    lfs f3, 0x4(r27)
    fmr f31, f1
    lfs f0, 0x64(r27)
    fmuls f2, f3, f0
    fcmpo cr0, f27, f2
    cror eq, lt, eq
    bne SuikaBallObj_UpdatePhysics_L_80124338
    lfs f0, 0x8(r24)
    lfs f4, lbl_806D6E60(r2)
    fmuls f3, f0, f31
    lfs f2, 0x44(r27)
    lfs f1, lbl_806D6E64(r2)
    lfs f0, lbl_806D6E58(r2)
    fmadds f2, f4, f3, f2
    stfs f2, 0x44(r27)
    lfs f2, 0x18(r24)
    lfs f3, 0x48(r27)
    fmuls f2, f2, f31
    fmadds f1, f4, f2, f1
    fadds f1, f3, f1
    stfs f1, 0x48(r27)
    lfs f2, 0x28(r24)
    lfs f1, 0x4c(r27)
    fmuls f2, f2, f31
    fmadds f1, f4, f2, f1
    stfs f1, 0x4c(r27)
    stfs f0, 0x50(r27)
    b SuikaBallObj_UpdatePhysics_L_80124428
    SuikaBallObj_UpdatePhysics_L_80124338:
    lfs f1, 0x68(r27)
    fadds f0, f0, f1
    fmuls f0, f3, f0
    fcmpo cr0, f27, f0
    cror eq, lt, eq
    bne SuikaBallObj_UpdatePhysics_L_801243F0
    fsubs f2, f27, f2
    lfs f0, lbl_806D6E58(r2)
    fmuls f1, f3, f1
    fcmpo cr0, f26, f0
    fdivs f2, f2, f1
    bge SuikaBallObj_UpdatePhysics_L_80124370
    lfs f0, lbl_806D6E68(r2)
    fmuls f2, f2, f0
    SuikaBallObj_UpdatePhysics_L_80124370:
    lfs f0, lbl_806D6E70(r2)
    addi r3, r1, 0xf0
    lfs f1, lbl_806D6E6C(r2)
    li r4, 0x59
    fmuls f0, f0, f2
    fmuls f1, f1, f0
    bl PSMTXRotRad
    addi r4, r1, 0xf0
    mr r3, r24
    mr r5, r4
    bl PSMTXConcat
    lfs f0, 0xf8(r1)
    lfs f4, lbl_806D6E74(r2)
    fmuls f3, f0, f31
    lfs f2, 0x44(r27)
    lfs f1, lbl_806D6E64(r2)
    lfs f0, lbl_806D6E58(r2)
    fmadds f2, f4, f3, f2
    stfs f2, 0x44(r27)
    lfs f2, 0x108(r1)
    lfs f3, 0x48(r27)
    fmuls f2, f2, f31
    fmadds f1, f4, f2, f1
    fadds f1, f3, f1
    stfs f1, 0x48(r27)
    lfs f2, 0x118(r1)
    lfs f1, 0x4c(r27)
    fmuls f2, f2, f31
    fmadds f1, f4, f2, f1
    stfs f1, 0x4c(r27)
    stfs f0, 0x50(r27)
    b SuikaBallObj_UpdatePhysics_L_80124428
    SuikaBallObj_UpdatePhysics_L_801243F0:
    lfs f0, lbl_806D6E58(r2)
    stfs f31, 0x50(r27)
    fcmpo cr0, f26, f0
    ble SuikaBallObj_UpdatePhysics_L_8012440C
    lfs f0, lbl_806D6E64(r2)
    stfs f0, 0x58(r27)
    b SuikaBallObj_UpdatePhysics_L_80124414
    SuikaBallObj_UpdatePhysics_L_8012440C:
    lfs f0, lbl_806D6E68(r2)
    stfs f0, 0x58(r27)
    SuikaBallObj_UpdatePhysics_L_80124414:
    lfs f0, lbl_806D6E58(r2)
    stfs f0, 0x54(r27)
    stfs f0, 0x5c(r27)
    stfs f0, 0x44(r27)
    stfs f0, 0x4c(r27)
    SuikaBallObj_UpdatePhysics_L_80124428:
    addi r3, r27, 0x44
    bl Vec3_Magnitude
    lfs f0, lbl_806D6E78(r2)
    fcmpo cr0, f1, f0
    ble SuikaBallObj_UpdatePhysics_L_80124464
    fdivs f1, f0, f1
    lfs f0, 0x44(r27)
    fmuls f0, f0, f1
    stfs f0, 0x44(r27)
    lfs f0, 0x48(r27)
    fmuls f0, f0, f1
    stfs f0, 0x48(r27)
    lfs f0, 0x4c(r27)
    fmuls f0, f0, f1
    stfs f0, 0x4c(r27)
    SuikaBallObj_UpdatePhysics_L_80124464:
    addi r3, r27, 0x38
    addi r4, r27, 0x44
    mr r5, r3
    bl PSVECAdd
    lis r4, lbl_80355918@ha
    lis r3, lbl_80355948@ha
    addi r23, r4, lbl_80355918@l
    addi r31, r1, 0x90
    lwz r25, 0x0(r23)
    addi r24, r3, lbl_80355948@l
    lwz r12, 0x4(r23)
    addi r30, r1, 0xc0
    lwz r11, 0x8(r23)
    li r29, 0x0
    lwz r10, 0xc(r23)
    li r28, 0x0
    lwz r9, 0x10(r23)
    li r26, 0x0
    lwz r8, 0x14(r23)
    lwz r7, 0x18(r23)
    lwz r6, 0x1c(r23)
    lwz r5, 0x20(r23)
    lwz r4, 0x24(r23)
    lwz r3, 0x28(r23)
    lwz r0, 0x2c(r23)
    stw r25, 0xc0(r1)
    lwz r25, 0x0(r24)
    stw r12, 0xc4(r1)
    lwz r12, 0x4(r24)
    stw r11, 0xc8(r1)
    lwz r11, 0x8(r24)
    stw r10, 0xcc(r1)
    lwz r10, 0xc(r24)
    stw r9, 0xd0(r1)
    lwz r9, 0x10(r24)
    stw r8, 0xd4(r1)
    lwz r8, 0x14(r24)
    stw r7, 0xd8(r1)
    lwz r7, 0x18(r24)
    stw r6, 0xdc(r1)
    lwz r6, 0x1c(r24)
    stw r5, 0xe0(r1)
    lwz r5, 0x20(r24)
    stw r4, 0xe4(r1)
    lwz r4, 0x24(r24)
    stw r3, 0xe8(r1)
    lwz r3, 0x28(r24)
    stw r0, 0xec(r1)
    lwz r0, 0x2c(r24)
    lfs f6, 0x4(r27)
    fadds f3, f30, f6
    stfs f29, 0xc4(r1)
    fsubs f2, f30, f6
    fadds f1, f28, f6
    stfs f28, 0xc8(r1)
    fsubs f0, f28, f6
    stfs f3, 0xc0(r1)
    stfs f2, 0xcc(r1)
    stfs f29, 0xd0(r1)
    stfs f28, 0xd4(r1)
    stfs f30, 0xd8(r1)
    stfs f29, 0xdc(r1)
    stfs f1, 0xe0(r1)
    stfs f30, 0xe4(r1)
    stfs f29, 0xe8(r1)
    stfs f0, 0xec(r1)
    stw r25, 0x90(r1)
    stw r12, 0x94(r1)
    stw r11, 0x98(r1)
    stw r10, 0x9c(r1)
    stw r9, 0xa0(r1)
    stw r8, 0xa4(r1)
    stw r7, 0xa8(r1)
    stw r6, 0xac(r1)
    stw r5, 0xb0(r1)
    stw r4, 0xb4(r1)
    stw r3, 0xb8(r1)
    stw r0, 0xbc(r1)
    lfs f5, 0x38(r27)
    fadds f0, f5, f6
    fsubs f2, f5, f6
    stfs f0, 0x90(r1)
    lfs f4, 0x3c(r27)
    stfs f4, 0x94(r1)
    lfs f3, 0x40(r27)
    fadds f1, f3, f6
    stfs f3, 0x98(r1)
    fsubs f0, f3, f6
    stfs f2, 0x9c(r1)
    stfs f4, 0xa0(r1)
    stfs f3, 0xa4(r1)
    stfs f5, 0xa8(r1)
    stfs f4, 0xac(r1)
    stfs f1, 0xb0(r1)
    stfs f5, 0xb4(r1)
    stfs f4, 0xb8(r1)
    stfs f0, 0xbc(r1)
    SuikaBallObj_UpdatePhysics_L_801245E8:
    mr r3, r30
    mr r4, r31
    addi r5, r1, 0x54
    addi r6, r1, 0x48
    bl Terrain_RaycastWall
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBallObj_UpdatePhysics_L_80124664
    mr r4, r31
    addi r3, r1, 0x54
    addi r5, r1, 0x3c
    bl Vec3_Subtract
    lfs f0, lbl_806D6E58(r2)
    addi r3, r27, 0x38
    mr r5, r3
    addi r4, r1, 0x3c
    stfs f0, 0x40(r1)
    bl PSVECAdd
    addi r23, r1, 0x90
    mr r24, r28
    add r23, r23, r26
    b SuikaBallObj_UpdatePhysics_L_80124658
    SuikaBallObj_UpdatePhysics_L_80124640:
    mr r3, r23
    mr r5, r23
    addi r4, r1, 0x3c
    bl PSVECAdd
    addi r23, r23, 0xc
    addi r24, r24, 0x1
    SuikaBallObj_UpdatePhysics_L_80124658:
    cmpwi r24, 0x4
    blt SuikaBallObj_UpdatePhysics_L_80124640
    li r29, 0x1
    SuikaBallObj_UpdatePhysics_L_80124664:
    addi r28, r28, 0x1
    addi r30, r30, 0xc
    cmpwi r28, 0x4
    addi r26, r26, 0xc
    addi r31, r31, 0xc
    blt SuikaBallObj_UpdatePhysics_L_801245E8
    clrlwi. r0, r29, 24
    beq SuikaBallObj_UpdatePhysics_L_801246F8
    addi r3, r27, 0x44
    addi r4, r1, 0x30
    bl Vec3_Normalize
    addi r3, r1, 0x48
    addi r4, r1, 0x30
    bl Vec3_Dot
    lfs f0, lbl_806D6E58(r2)
    fcmpo cr0, f1, f0
    ble SuikaBallObj_UpdatePhysics_L_801246F8
    addi r3, r1, 0x48
    addi r4, r27, 0x44
    bl Vec3_Dot
    lfs f0, lbl_806D6E5C(r2)
    addi r3, r1, 0x48
    addi r4, r1, 0x30
    fmuls f1, f0, f1
    bl PSVECScale
    addi r4, r27, 0x44
    addi r3, r1, 0x30
    mr r5, r4
    bl PSVECAdd
    lfs f1, 0x44(r27)
    lfs f0, 0x6c(r27)
    fmuls f0, f1, f0
    stfs f0, 0x44(r27)
    lfs f1, 0x4c(r27)
    lfs f0, 0x6c(r27)
    fmuls f0, f1, f0
    stfs f0, 0x4c(r27)
    SuikaBallObj_UpdatePhysics_L_801246F8:
    addi r3, r27, 0x38
    addi r4, r1, 0x8
    li r23, 0x0
    li r5, 0x0
    li r6, 0x0
    bl Terrain_GetGroundHeight
    clrlwi. r0, r3, 24
    beq SuikaBallObj_UpdatePhysics_L_8012477C
    lfs f0, 0x3c(r27)
    lfs f1, 0x4(r27)
    lfs f2, 0x8(r1)
    fsubs f0, f0, f1
    fcmpo cr0, f0, f2
    bge SuikaBallObj_UpdatePhysics_L_8012474C
    fadds f0, f2, f1
    stfs f0, 0x3c(r27)
    lfs f0, 0x6c(r27)
    lfs f1, 0x48(r27)
    fneg f0, f0
    fmuls f0, f1, f0
    stfs f0, 0x48(r27)
    SuikaBallObj_UpdatePhysics_L_8012474C:
    lfs f1, 0x8(r1)
    lfs f0, 0x4(r27)
    lfs f2, lbl_806D6E64(r2)
    fadds f1, f1, f0
    lfs f3, 0x3c(r27)
    fadds f0, f2, f1
    fcmpo cr0, f3, f0
    bge SuikaBallObj_UpdatePhysics_L_8012477C
    fsubs f0, f1, f2
    fcmpo cr0, f3, f0
    ble SuikaBallObj_UpdatePhysics_L_8012477C
    li r23, 0x1
    SuikaBallObj_UpdatePhysics_L_8012477C:
    lwz r0, 0x0(r27)
    cmplwi r0, 0x0
    beq SuikaBallObj_UpdatePhysics_L_80124840
    lfs f1, lbl_806D6E58(r2)
    lfs f2, 0x50(r27)
    fcmpu cr0, f1, f2
    beq SuikaBallObj_UpdatePhysics_L_801247C8
    lfs f0, lbl_806D6E80(r2)
    addi r3, r1, 0x60
    lfs f1, lbl_806D6E7C(r2)
    addi r4, r27, 0x54
    fmuls f0, f0, f2
    fmuls f1, f1, f0
    bl PSMTXRotAxisRad
    addi r4, r27, 0x8
    addi r3, r1, 0x60
    mr r5, r4
    bl PSMTXConcat
    b SuikaBallObj_UpdatePhysics_L_80124820
    SuikaBallObj_UpdatePhysics_L_801247C8:
    lfs f0, 0x4c(r27)
    addi r3, r1, 0x30
    stfs f0, 0x30(r1)
    stfs f1, 0x34(r1)
    lfs f0, 0x44(r27)
    fneg f0, f0
    stfs f0, 0x38(r1)
    bl Vec3_Magnitude
    lfs f0, lbl_806D6E58(r2)
    fcmpo cr0, f1, f0
    ble SuikaBallObj_UpdatePhysics_L_80124820
    lfs f0, lbl_806D6E80(r2)
    addi r3, r1, 0x60
    lfs f2, lbl_806D6E7C(r2)
    addi r4, r1, 0x30
    fmuls f0, f0, f1
    fmuls f1, f2, f0
    bl PSMTXRotAxisRad
    addi r4, r27, 0x8
    addi r3, r1, 0x60
    mr r5, r4
    bl PSMTXConcat
    SuikaBallObj_UpdatePhysics_L_80124820:
    lfs f0, 0x38(r27)
    stfs f0, 0x14(r27)
    lfs f0, 0x3c(r27)
    stfs f0, 0x24(r27)
    lfs f0, 0x40(r27)
    stfs f0, 0x34(r27)
    lwz r3, 0x0(r27)
    bl Object_DriveAnimMatrix
    SuikaBallObj_UpdatePhysics_L_80124840:
    lbz r0, 0x61(r27)
    cmplwi r0, 0x0
    beq SuikaBallObj_UpdatePhysics_L_8012486C
    lfs f0, 0x44(r27)
    lfs f1, lbl_806D6E84(r2)
    fmuls f0, f0, f1
    stfs f0, 0x44(r27)
    lfs f0, 0x4c(r27)
    fmuls f0, f0, f1
    stfs f0, 0x4c(r27)
    b SuikaBallObj_UpdatePhysics_L_801248B8
    SuikaBallObj_UpdatePhysics_L_8012486C:
    clrlwi. r0, r23, 24
    beq SuikaBallObj_UpdatePhysics_L_80124898
    lfs f1, 0x44(r27)
    lfs f0, 0x78(r27)
    fmuls f0, f1, f0
    stfs f0, 0x44(r27)
    lfs f1, 0x4c(r27)
    lfs f0, 0x78(r27)
    fmuls f0, f1, f0
    stfs f0, 0x4c(r27)
    b SuikaBallObj_UpdatePhysics_L_801248B8
    SuikaBallObj_UpdatePhysics_L_80124898:
    lfs f1, 0x44(r27)
    lfs f0, 0x74(r27)
    fmuls f0, f1, f0
    stfs f0, 0x44(r27)
    lfs f1, 0x4c(r27)
    lfs f0, 0x74(r27)
    fmuls f0, f1, f0
    stfs f0, 0x4c(r27)
    SuikaBallObj_UpdatePhysics_L_801248B8:
    lfs f2, 0x48(r27)
    lfs f1, 0x70(r27)
    lfs f0, lbl_806D6E88(r2)
    fsubs f1, f2, f1
    stfs f1, 0x48(r27)
    lfs f1, 0x50(r27)
    fmuls f0, f1, f0
    stfs f0, 0x50(r27)
    psq_l f31, 0x1a8(r1), 0, 0
    lfd f31, 0x1a0(r1)
    psq_l f30, 0x198(r1), 0, 0
    lfd f30, 0x190(r1)
    psq_l f29, 0x188(r1), 0, 0
    lfd f29, 0x180(r1)
    psq_l f28, 0x178(r1), 0, 0
    lfd f28, 0x170(r1)
    psq_l f27, 0x168(r1), 0, 0
    lfd f27, 0x160(r1)
    psq_l f26, 0x158(r1), 0, 0
    lfd f26, 0x150(r1)
    lmw r23, 0x12c(r1)
    lwz r0, 0x1b4(r1)
    mtlr r0
    addi r1, r1, 0x1b0
    blr
}
