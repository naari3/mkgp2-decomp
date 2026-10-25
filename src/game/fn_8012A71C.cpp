/*
 * 0x8012A71C..0x8012B394: challenge scene update.
 */
#pragma cplusplus on

extern "C" {
extern void Archive_GetRootJObj();
extern void GetCharacterDataEntry();
extern void HSD_JObjSetMtxDirtySub();
extern void HSD_JObjSetupMatrixSub();
extern void JObj_Hide();
extern void JObj_Show();
extern void LUT_Sin12Bit();
extern void ObjectTree_BlendOrCopy_Timed();
extern void Object_DriveAnimAndSkin();
extern void Object_DriveAnimMatrix();
extern void Object_GetField8();
extern void Object_SetAnimBinding();
extern void Object_SetField8_10_14();
extern void Vec3_Magnitude();
extern void __assert();
extern void clNormal3D_Exec();
extern unsigned int lbl_806CF018;
extern unsigned int lbl_806D70D8;
extern unsigned int lbl_806D70DC;
extern unsigned int lbl_806D70E0;
extern unsigned int lbl_806D70E4;
extern unsigned int lbl_806D70E8;
extern unsigned int lbl_806D70EC;
extern unsigned int lbl_806D70F0;
extern unsigned int lbl_806D70F4;
extern unsigned int lbl_806D70F8;
extern unsigned int lbl_806D70FC;
extern unsigned int lbl_806D7100;
extern unsigned int lbl_806D7104;
extern unsigned int lbl_806D7108;
extern unsigned int lbl_806D710C;
extern unsigned int lbl_806D7110;
extern unsigned int lbl_806D7114;
extern unsigned int lbl_806D7118;
extern unsigned int lbl_806D7120;
asm void fn_8012A71C(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8012A71C[8] = {
    0x18, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8012A71C = {
    (void *)&fn_8012A71C, 0x00000C78, (void *)extab_fn_8012A71C
};

}


extern "C" asm void fn_8012A71C(void) { /* 0x8012A71C size:0xC78 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    mr r31, r3
    fmr f31, f1
    lwz r3, 0x0(r3)
    cmplwi r3, 0x0
    beq fn_8012A71C_L_8012A75C
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne fn_8012A71C_L_8012A764
    fn_8012A71C_L_8012A75C:
    li r3, 0x0
    b fn_8012A71C_L_8012B370
    fn_8012A71C_L_8012A764:
    bl Object_DriveAnimMatrix
    lfs f1, 0xf8(r31)
    fcmpo cr0, f1, f31
    ble fn_8012A71C_L_8012A790
    lfs f0, lbl_806CF018(r13)
    fsubs f0, f1, f0
    fcmpo cr0, f0, f31
    stfs f0, 0xf8(r31)
    bge fn_8012A71C_L_8012A7A8
    stfs f31, 0xf8(r31)
    b fn_8012A71C_L_8012A7A8
    fn_8012A71C_L_8012A790:
    lfs f0, lbl_806CF018(r13)
    fadds f0, f1, f0
    fcmpo cr0, f0, f31
    stfs f0, 0xf8(r31)
    ble fn_8012A71C_L_8012A7A8
    stfs f31, 0xf8(r31)
    fn_8012A71C_L_8012A7A8:
    lfs f0, lbl_806D70D8(r2)
    lfs f1, 0xf8(r31)
    fcmpo cr0, f0, f1
    bge fn_8012A71C_L_8012A810
    lfs f0, lbl_806D70DC(r2)
    fcmpo cr0, f1, f0
    bge fn_8012A71C_L_8012A810
    lfs f2, 0xfc(r31)
    lfs f1, lbl_806D70E0(r2)
    fcmpo cr0, f2, f1
    bge fn_8012A71C_L_8012A7F0
    lfs f0, lbl_806D70E4(r2)
    fadds f0, f2, f0
    fcmpo cr0, f0, f1
    stfs f0, 0xfc(r31)
    ble fn_8012A71C_L_8012A860
    stfs f1, 0xfc(r31)
    b fn_8012A71C_L_8012A860
    fn_8012A71C_L_8012A7F0:
    ble fn_8012A71C_L_8012A860
    lfs f0, lbl_806D70E4(r2)
    fsubs f0, f2, f0
    fcmpo cr0, f0, f1
    stfs f0, 0xfc(r31)
    bge fn_8012A71C_L_8012A860
    stfs f1, 0xfc(r31)
    b fn_8012A71C_L_8012A860
    fn_8012A71C_L_8012A810:
    lfs f0, lbl_806D70E0(r2)
    fcmpo cr0, f1, f0
    bge fn_8012A71C_L_8012A840
    lfs f2, 0xfc(r31)
    lfs f1, lbl_806D70E4(r2)
    lfs f0, lbl_806D70E8(r2)
    fsubs f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0xfc(r31)
    bge fn_8012A71C_L_8012A860
    stfs f0, 0xfc(r31)
    b fn_8012A71C_L_8012A860
    fn_8012A71C_L_8012A840:
    lfs f2, 0xfc(r31)
    lfs f1, lbl_806D70E4(r2)
    lfs f0, lbl_806D70EC(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0xfc(r31)
    ble fn_8012A71C_L_8012A860
    stfs f0, 0xfc(r31)
    fn_8012A71C_L_8012A860:
    lfs f2, lbl_806D70EC(r2)
    lfs f4, 0xfc(r31)
    lwz r0, 0xf0(r31)
    fadds f0, f2, f4
    lfs f1, lbl_806D70F4(r2)
    lfs f3, lbl_806D70F0(r2)
    cmpwi r0, 0x2a
    fsubs f0, f1, f0
    fmuls f1, f3, f0
    beq fn_8012A71C_L_8012A890
    cmpwi r0, 0x2b
    bne fn_8012A71C_L_8012A928
    fn_8012A71C_L_8012A890:
    slwi r0, r0, 2
    lwz r3, 0xc(r31)
    add r4, r31, r0
    lfs f1, 0x108(r31)
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, lbl_806D70E0(r2)
    mr r5, r29
    li r6, 0x0
    bl ObjectTree_BlendOrCopy_Timed
    lwz r0, 0xf0(r31)
    cmpwi r0, 0x2a
    bne fn_8012A71C_L_8012A8F4
    lwz r3, 0xe8(r31)
    bl GetCharacterDataEntry
    lfs f2, 0x1c(r3)
    b fn_8012A71C_L_8012A900
    fn_8012A71C_L_8012A8F4:
    lwz r3, 0xe8(r31)
    bl GetCharacterDataEntry
    lfs f2, 0x24(r3)
    fn_8012A71C_L_8012A900:
    lfs f1, 0x108(r31)
    lfs f0, 0x10c(r31)
    fadds f0, f1, f0
    fcmpo cr0, f0, f2
    stfs f0, 0x108(r31)
    cror eq, gt, eq
    bne fn_8012A71C_L_8012AFD8
    lfs f0, lbl_806D70E0(r2)
    stfs f0, 0x108(r31)
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012A928:
    cmpwi r0, 0x1
    bne fn_8012A71C_L_8012A9C4
    lwz r0, 0xf4(r31)
    lwz r3, 0xc(r31)
    slwi r0, r0, 2
    lfs f2, lbl_806D70E0(r2)
    add r4, r31, r0
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x10(r31)
    lfs f1, lbl_806D70E8(r2)
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x14(r31)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r30, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0x10(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, 0x11c(r31)
    mr r5, r29
    mr r6, r30
    bl ObjectTree_BlendOrCopy_Timed
    lfs f2, 0x11c(r31)
    lfs f1, 0x120(r31)
    lfs f0, lbl_806D70EC(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x11c(r31)
    cror eq, gt, eq
    bne fn_8012A71C_L_8012AFD8
    li r0, 0x0
    stw r0, 0xf0(r31)
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012A9C4:
    cmpwi r0, 0x0
    beq fn_8012A71C_L_8012AB9C
    cmpwi r0, -0x1
    beq fn_8012A71C_L_8012AAF0
    lfs f2, 0x108(r31)
    lfs f0, 0x110(r31)
    fcmpo cr0, f2, f0
    bge fn_8012A71C_L_8012AAF0
    slwi r0, r0, 2
    fmr f1, f2
    add r4, r31, r0
    lwz r3, 0xc(r31)
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lfs f2, 0x108(r31)
    lfs f1, 0x10c(r31)
    lfs f0, lbl_806D70EC(r2)
    fadds f1, f2, f1
    stfs f1, 0x108(r31)
    lfs f1, 0x114(r31)
    fcmpo cr0, f1, f0
    bge fn_8012A71C_L_8012AA8C
    lwz r0, 0xec(r31)
    lwz r3, 0x10(r31)
    slwi r0, r0, 2
    lfs f1, lbl_806D70E8(r2)
    add r4, r31, r0
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r30, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0x10(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, 0x114(r31)
    mr r5, r29
    mr r6, r30
    bl ObjectTree_BlendOrCopy_Timed
    lfs f1, 0x114(r31)
    lfs f0, 0x118(r31)
    fadds f0, f1, f0
    stfs f0, 0x114(r31)
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012AA8C:
    lwz r0, 0xf0(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x14(r3)
    bl clNormal3D_Exec
    lwz r0, 0xf0(r31)
    lwz r3, 0x10(r31)
    slwi r0, r0, 2
    lfs f1, 0x108(r31)
    add r4, r31, r0
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0x10(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, lbl_806D70E0(r2)
    mr r5, r29
    li r6, 0x0
    bl ObjectTree_BlendOrCopy_Timed
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012AAF0:
    lwz r4, 0x104(r31)
    lwz r0, 0xf4(r31)
    lwz r3, 0xc(r31)
    add r0, r4, r0
    lfs f2, lbl_806D70E0(r2)
    slwi r0, r0, 2
    add r4, r31, r0
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lwz r0, 0xf0(r31)
    lwz r3, 0x10(r31)
    slwi r0, r0, 2
    lfs f1, lbl_806D70E8(r2)
    add r4, r31, r0
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r30, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0x10(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, 0x11c(r31)
    mr r5, r29
    mr r6, r30
    bl ObjectTree_BlendOrCopy_Timed
    lfs f2, 0x11c(r31)
    lfs f1, 0x120(r31)
    lfs f0, lbl_806D70EC(r2)
    fadds f1, f2, f1
    stfs f1, 0x11c(r31)
    lfs f1, 0x11c(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8012A71C_L_8012AFD8
    li r0, 0x0
    stw r0, 0xf0(r31)
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012AB9C:
    lfs f0, lbl_806D70D8(r2)
    fcmpo cr0, f0, f4
    bge fn_8012A71C_L_8012ACBC
    lfs f0, lbl_806D70DC(r2)
    fcmpo cr0, f4, f0
    bge fn_8012A71C_L_8012ACBC
    li r0, 0x5
    lfs f0, lbl_806D70F8(r2)
    stw r0, 0x104(r31)
    lfs f1, 0x108(r31)
    fadds f1, f1, f2
    fcmpo cr0, f1, f0
    stfs f1, 0x108(r31)
    ble fn_8012A71C_L_8012ABDC
    lfs f0, lbl_806D70E0(r2)
    stfs f0, 0x108(r31)
    fn_8012A71C_L_8012ABDC:
    lwz r0, 0xf4(r31)
    lwz r3, 0xc(r31)
    slwi r0, r0, 2
    lfs f1, 0x108(r31)
    add r4, r31, r0
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x28(r4)
    bl Object_DriveAnimAndSkin
    lfs f1, 0x100(r31)
    lfs f0, lbl_806D70EC(r2)
    fcmpo cr0, f1, f0
    bge fn_8012A71C_L_8012AC8C
    lwz r0, 0xf4(r31)
    lwz r3, 0x10(r31)
    slwi r0, r0, 2
    lfs f1, lbl_806D70E8(r2)
    add r4, r31, r0
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r30, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0x10(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, 0x100(r31)
    mr r5, r29
    mr r6, r30
    bl ObjectTree_BlendOrCopy_Timed
    lfs f2, 0x100(r31)
    lfs f1, lbl_806D70FC(r2)
    lfs f0, lbl_806D70EC(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x100(r31)
    cror eq, gt, eq
    bne fn_8012A71C_L_8012AFD8
    stfs f0, 0x100(r31)
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012AC8C:
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, lbl_806D70E0(r2)
    mr r5, r29
    li r6, 0x0
    bl ObjectTree_BlendOrCopy_Timed
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012ACBC:
    lfs f0, lbl_806D7100(r2)
    fcmpo cr0, f0, f4
    bge fn_8012A71C_L_8012ADD4
    li r0, 0xa
    lfs f1, lbl_806D70EC(r2)
    stw r0, 0x104(r31)
    lfs f0, lbl_806D70F8(r2)
    lfs f2, 0x108(r31)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x108(r31)
    ble fn_8012A71C_L_8012ACF4
    lfs f0, lbl_806D70E0(r2)
    stfs f0, 0x108(r31)
    fn_8012A71C_L_8012ACF4:
    lwz r0, 0xf4(r31)
    lwz r3, 0xc(r31)
    slwi r0, r0, 2
    lfs f1, 0x108(r31)
    add r4, r31, r0
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x3c(r4)
    bl Object_DriveAnimAndSkin
    lfs f1, 0x100(r31)
    lfs f0, lbl_806D70EC(r2)
    fcmpo cr0, f1, f0
    bge fn_8012A71C_L_8012ADA4
    lwz r0, 0xf4(r31)
    lwz r3, 0x10(r31)
    slwi r0, r0, 2
    lfs f1, lbl_806D70E8(r2)
    add r4, r31, r0
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r30, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0x10(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, 0x100(r31)
    mr r5, r29
    mr r6, r30
    bl ObjectTree_BlendOrCopy_Timed
    lfs f2, 0x100(r31)
    lfs f1, lbl_806D70FC(r2)
    lfs f0, lbl_806D70EC(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x100(r31)
    cror eq, gt, eq
    bne fn_8012A71C_L_8012AFD8
    stfs f0, 0x100(r31)
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012ADA4:
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, lbl_806D70E0(r2)
    mr r5, r29
    li r6, 0x0
    bl ObjectTree_BlendOrCopy_Timed
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012ADD4:
    lfs f0, lbl_806D7104(r2)
    fcmpo cr0, f4, f0
    bge fn_8012A71C_L_8012AEEC
    li r0, 0xf
    lfs f1, lbl_806D70EC(r2)
    stw r0, 0x104(r31)
    lfs f0, lbl_806D70F8(r2)
    lfs f2, 0x108(r31)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x108(r31)
    ble fn_8012A71C_L_8012AE0C
    lfs f0, lbl_806D70E0(r2)
    stfs f0, 0x108(r31)
    fn_8012A71C_L_8012AE0C:
    lwz r0, 0xf4(r31)
    lwz r3, 0xc(r31)
    slwi r0, r0, 2
    lfs f1, 0x108(r31)
    add r4, r31, r0
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x50(r4)
    bl Object_DriveAnimAndSkin
    lfs f1, 0x100(r31)
    lfs f0, lbl_806D70EC(r2)
    fcmpo cr0, f1, f0
    bge fn_8012A71C_L_8012AEBC
    lwz r0, 0xf4(r31)
    lwz r3, 0x10(r31)
    slwi r0, r0, 2
    lfs f1, lbl_806D70E8(r2)
    add r4, r31, r0
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r30, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0x10(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, 0x100(r31)
    mr r5, r29
    mr r6, r30
    bl ObjectTree_BlendOrCopy_Timed
    lfs f2, 0x100(r31)
    lfs f1, lbl_806D70FC(r2)
    lfs f0, lbl_806D70EC(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x100(r31)
    cror eq, gt, eq
    bne fn_8012A71C_L_8012AFD8
    stfs f0, 0x100(r31)
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012AEBC:
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, lbl_806D70E0(r2)
    mr r5, r29
    li r6, 0x0
    bl ObjectTree_BlendOrCopy_Timed
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012AEEC:
    lwz r0, 0xf4(r31)
    lwz r3, 0xc(r31)
    slwi r0, r0, 2
    lfs f2, lbl_806D70E0(r2)
    add r4, r31, r0
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lfs f0, 0x100(r31)
    lfs f2, lbl_806D70E0(r2)
    fcmpo cr0, f0, f2
    ble fn_8012A71C_L_8012AFAC
    lwz r4, 0x104(r31)
    lwz r0, 0xf4(r31)
    lwz r3, 0x10(r31)
    add r0, r4, r0
    lfs f1, lbl_806D70E8(r2)
    slwi r0, r0, 2
    add r4, r31, r0
    lwz r4, 0x14(r4)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r30, r3
    lwz r3, 0x10(r31)
    bl Archive_GetRootJObj
    lfs f1, lbl_806D70EC(r2)
    mr r4, r3
    lfs f0, 0x100(r31)
    mr r5, r30
    lwz r3, 0x8(r31)
    mr r6, r29
    fsubs f1, f1, f0
    bl ObjectTree_BlendOrCopy_Timed
    lfs f2, 0x100(r31)
    lfs f1, lbl_806D70FC(r2)
    lfs f0, lbl_806D70E0(r2)
    fsubs f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x100(r31)
    cror eq, lt, eq
    bne fn_8012A71C_L_8012AFD8
    stfs f0, 0x100(r31)
    li r0, 0x0
    stw r0, 0x104(r31)
    b fn_8012A71C_L_8012AFD8
    fn_8012A71C_L_8012AFAC:
    lwz r3, 0x8(r31)
    bl Archive_GetRootJObj
    mr r30, r3
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r31)
    lfs f1, lbl_806D70E0(r2)
    mr r5, r30
    li r6, 0x0
    bl ObjectTree_BlendOrCopy_Timed
    fn_8012A71C_L_8012AFD8:
    lwz r3, 0x8(r31)
    bl Object_DriveAnimMatrix
    lwz r0, 0x154(r31)
    cmpwi r0, 0x2
    bne fn_8012A71C_L_8012B038
    lwz r4, 0x158(r31)
    cmplwi r4, 0x0
    beq fn_8012A71C_L_8012B004
    lwz r3, 0x8(r31)
    li r5, 0x10
    bl JObj_Hide
    fn_8012A71C_L_8012B004:
    lwz r4, 0x15c(r31)
    cmplwi r4, 0x0
    beq fn_8012A71C_L_8012B01C
    lwz r3, 0x8(r31)
    li r5, 0x10
    bl JObj_Hide
    fn_8012A71C_L_8012B01C:
    lwz r4, 0x160(r31)
    cmplwi r4, 0x0
    beq fn_8012A71C_L_8012B0D4
    lwz r3, 0x8(r31)
    li r5, 0x10
    bl JObj_Show
    b fn_8012A71C_L_8012B0D4
    fn_8012A71C_L_8012B038:
    cmpwi r0, 0x1
    bne fn_8012A71C_L_8012B08C
    lwz r4, 0x158(r31)
    cmplwi r4, 0x0
    beq fn_8012A71C_L_8012B058
    lwz r3, 0x8(r31)
    li r5, 0x10
    bl JObj_Hide
    fn_8012A71C_L_8012B058:
    lwz r4, 0x15c(r31)
    cmplwi r4, 0x0
    beq fn_8012A71C_L_8012B070
    lwz r3, 0x8(r31)
    li r5, 0x10
    bl JObj_Show
    fn_8012A71C_L_8012B070:
    lwz r4, 0x160(r31)
    cmplwi r4, 0x0
    beq fn_8012A71C_L_8012B0D4
    lwz r3, 0x8(r31)
    li r5, 0x10
    bl JObj_Hide
    b fn_8012A71C_L_8012B0D4
    fn_8012A71C_L_8012B08C:
    lwz r4, 0x158(r31)
    cmplwi r4, 0x0
    beq fn_8012A71C_L_8012B0A4
    lwz r3, 0x8(r31)
    li r5, 0x10
    bl JObj_Show
    fn_8012A71C_L_8012B0A4:
    lwz r4, 0x15c(r31)
    cmplwi r4, 0x0
    beq fn_8012A71C_L_8012B0BC
    lwz r3, 0x8(r31)
    li r5, 0x10
    bl JObj_Hide
    fn_8012A71C_L_8012B0BC:
    lwz r4, 0x160(r31)
    cmplwi r4, 0x0
    beq fn_8012A71C_L_8012B0D4
    lwz r3, 0x8(r31)
    li r5, 0x10
    bl JObj_Hide
    fn_8012A71C_L_8012B0D4:
    lfs f1, 0x138(r31)
    lfs f0, lbl_806D7108(r2)
    fadds f0, f1, f0
    stfs f0, 0x138(r31)
    lfs f1, 0x138(r31)
    bl LUT_Sin12Bit
    lfs f0, 0x134(r31)
    lwz r29, 0x12c(r31)
    fmuls f2, f0, f1
    lfs f1, lbl_806D710C(r2)
    lfs f0, 0x13c(r31)
    cmplwi r29, 0x0
    fmuls f1, f1, f2
    fadds f31, f1, f0
    bne fn_8012A71C_L_8012B120
    addi r3, r2, -0x3198  /* lbl_806D70C8 */
    li r4, 0x3c6
    addi r5, r2, -0x3190  /* lbl_806D70D0 */
    bl __assert
    fn_8012A71C_L_8012B120:
    stfs f31, 0x3c(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_8012A71C_L_8012B178
    cmplwi r29, 0x0
    beq fn_8012A71C_L_8012B178
    bne fn_8012A71C_L_8012B14C
    addi r3, r2, -0x3198  /* lbl_806D70C8 */
    li r4, 0x25d
    addi r5, r2, -0x3190  /* lbl_806D70D0 */
    bl __assert
    fn_8012A71C_L_8012B14C:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_8012A71C_L_8012B168
    rlwinm. r0, r4, 0, 25, 25
    beq fn_8012A71C_L_8012B168
    li r3, 0x1
    fn_8012A71C_L_8012B168:
    clrlwi. r0, r3, 24
    bne fn_8012A71C_L_8012B178
    mr r3, r29
    bl HSD_JObjSetMtxDirtySub
    fn_8012A71C_L_8012B178:
    lfs f1, 0x138(r31)
    bl LUT_Sin12Bit
    lfs f0, 0x134(r31)
    lwz r29, 0x130(r31)
    fmuls f2, f0, f1
    lfs f1, lbl_806D7110(r2)
    lfs f0, 0x140(r31)
    cmplwi r29, 0x0
    fmuls f1, f1, f2
    fadds f31, f1, f0
    bne fn_8012A71C_L_8012B1B4
    addi r3, r2, -0x3198  /* lbl_806D70C8 */
    li r4, 0x3c6
    addi r5, r2, -0x3190  /* lbl_806D70D0 */
    bl __assert
    fn_8012A71C_L_8012B1B4:
    stfs f31, 0x3c(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_8012A71C_L_8012B20C
    cmplwi r29, 0x0
    beq fn_8012A71C_L_8012B20C
    bne fn_8012A71C_L_8012B1E0
    addi r3, r2, -0x3198  /* lbl_806D70C8 */
    li r4, 0x25d
    addi r5, r2, -0x3190  /* lbl_806D70D0 */
    bl __assert
    fn_8012A71C_L_8012B1E0:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_8012A71C_L_8012B1FC
    rlwinm. r0, r4, 0, 25, 25
    beq fn_8012A71C_L_8012B1FC
    li r3, 0x1
    fn_8012A71C_L_8012B1FC:
    clrlwi. r0, r3, 24
    bne fn_8012A71C_L_8012B20C
    mr r3, r29
    bl HSD_JObjSetMtxDirtySub
    fn_8012A71C_L_8012B20C:
    lwz r3, 0x124(r31)
    cmplwi r3, 0x0
    beq fn_8012A71C_L_8012B36C
    lwz r0, 0x128(r31)
    cmplwi r0, 0x0
    beq fn_8012A71C_L_8012B36C
    bl clNormal3D_Exec
    lwz r3, 0x124(r31)
    bl Object_GetField8
    fctiwz f0, f1
    lis r3, 0x8889
    subi r0, r3, 0x7777
    stfd f0, 0x8(r1)
    lwz r4, 0xc(r1)
    mulhw r0, r0, r4
    add r0, r0, r4
    srawi r0, r0, 4
    srwi r3, r0, 31
    add r0, r0, r3
    mulli r0, r0, 0x1e
    subf. r0, r0, r4
    bne fn_8012A71C_L_8012B2E8
    addi r3, r31, 0xdc
    li r29, 0x0
    bl Vec3_Magnitude
    lfs f0, lbl_806D7114(r2)
    fcmpo cr0, f1, f0
    ble fn_8012A71C_L_8012B284
    li r29, 0x5a
    b fn_8012A71C_L_8012B2A8
    fn_8012A71C_L_8012B284:
    lfs f0, lbl_806D7118(r2)
    fcmpo cr0, f1, f0
    ble fn_8012A71C_L_8012B298
    li r29, 0x3c
    b fn_8012A71C_L_8012B2A8
    fn_8012A71C_L_8012B298:
    lfs f0, lbl_806D710C(r2)
    fcmpo cr0, f1, f0
    ble fn_8012A71C_L_8012B2A8
    li r29, 0x1e
    fn_8012A71C_L_8012B2A8:
    addi r0, r29, 0x1e
    lis r4, 0x4330
    xoris r3, r29, 0x8000
    stw r4, 0x8(r1)
    xoris r0, r0, 0x8000
    lfd f3, lbl_806D7120(r2)
    stw r3, 0xc(r1)
    lwz r3, 0x124(r31)
    lfd f0, 0x8(r1)
    stw r0, 0x14(r1)
    fsubs f1, f0, f3
    lfs f2, lbl_806D70EC(r2)
    stw r4, 0x10(r1)
    lfd f0, 0x10(r1)
    fsubs f3, f0, f3
    bl Object_SetField8_10_14
    fn_8012A71C_L_8012B2E8:
    lwz r29, 0x128(r31)
    cmplwi r29, 0x0
    bne fn_8012A71C_L_8012B304
    addi r3, r2, -0x3198  /* lbl_806D70C8 */
    li r4, 0x47c
    addi r5, r2, -0x3190  /* lbl_806D70D0 */
    bl __assert
    fn_8012A71C_L_8012B304:
    cmplwi r29, 0x0
    beq fn_8012A71C_L_8012B34C
    bne fn_8012A71C_L_8012B320
    addi r3, r2, -0x3198  /* lbl_806D70C8 */
    li r4, 0x25d
    addi r5, r2, -0x3190  /* lbl_806D70D0 */
    bl __assert
    fn_8012A71C_L_8012B320:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_8012A71C_L_8012B33C
    rlwinm. r0, r4, 0, 25, 25
    beq fn_8012A71C_L_8012B33C
    li r3, 0x1
    fn_8012A71C_L_8012B33C:
    clrlwi. r0, r3, 24
    beq fn_8012A71C_L_8012B34C
    mr r3, r29
    bl HSD_JObjSetupMatrixSub
    fn_8012A71C_L_8012B34C:
    lwz r3, 0x124(r31)
    addi r4, r29, 0x44
    li r5, 0x0
    bl Object_SetAnimBinding
    lwz r3, 0x124(r31)
    bl clNormal3D_Exec
    lwz r3, 0x124(r31)
    bl Object_DriveAnimMatrix
    fn_8012A71C_L_8012B36C:
    li r3, 0x1
    fn_8012A71C_L_8012B370:
    psq_l f31, 0x38(r1), 0, 0
    lwz r0, 0x44(r1)
    lfd f31, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

