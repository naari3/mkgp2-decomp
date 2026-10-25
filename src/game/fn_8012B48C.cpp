/*
 * 0x8012B48C..0x8012B924: challenge scene init.
 */
#pragma cplusplus on

extern "C" {
extern void Alloc();
extern void Archive_GetRootJObj();
extern void GetCharacterDataEntry();
extern void GetKartModelNameEntry();
extern void HSD_JObjSetupMatrixSub();
extern void KartTireFX_Ctor();
extern void KartTireFX_SetVisibleAll4Wheels();
extern void ObjectTree_BlendOrCopy_Timed();
extern void Object_DriveAnimAndSkin();
extern void Object_SetAnimBinding();
extern void ResolveJointByName();
extern void __assert();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();
extern void fn_8012BDF4();
extern unsigned int lbl_806D70E0;
extern unsigned int lbl_806D70EC;
extern unsigned int lbl_806D70F0;
extern unsigned int chara_mario_hand_fin_joint[];
extern unsigned int chara_mario_hand_goo_joint[];
extern unsigned int chara_mario_hand_pa_joint[];
extern unsigned int chara_mario_r_hand_null_joint[];
extern unsigned int lbl_80356708[];
extern unsigned int lbl_80356724[];
extern unsigned int mario_cart_body_joint[];
extern unsigned int mario_cart_engine_joint[];
extern unsigned int mario_cart_tire_fl_joint[];
extern unsigned int mario_cart_tire_fr_joint[];
extern unsigned int mario_cart_tire_rl_joint[];
extern unsigned int mario_cart_tire_rr_joint[];
extern void MemoryManager_TimedFree();
asm void fn_8012B48C(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; void *f17; unsigned int f18; void *f19; unsigned int f20; void *f21; unsigned int f22; void *f23; unsigned int f24; void *f25; unsigned int f26; void *f27; unsigned int f28; void *f29; } extab_fn_8012B48C = { 0x400A0000, 0x00000074, 0x00000040, 0x00000094, 0x00000048, 0x000000B4, 0x00000050, 0x000000D4, 0x00000058, 0x0000014C, 0x00000060, 0x00000320, 0x00000068, 0x00000378, 0x00000070, 0x00000000, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A800018, (void *)&MemoryManager_TimedFree, 0x8A800018, (void *)&MemoryManager_TimedFree, 0x8A800018, (void *)&MemoryManager_TimedFree };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8012B48C = {
    (void *)&fn_8012B48C, 0x00000498, (void *)&extab_fn_8012B48C
};

}


extern "C" asm void fn_8012B48C(void) { /* 0x8012B48C size:0x498 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r24, 0x10(r1)
    mr r30, r3
    mr r31, r4
    mr r25, r5
    bl fn_8012BDF4
    stw r31, 0xe8(r30)
    lwz r3, 0xe8(r30)
    cmpwi r3, 0x0
    blt fn_8012B48C_L_8012B4C4
    cmpwi r3, 0xd
    blt fn_8012B48C_L_8012B4CC
    fn_8012B48C_L_8012B4C4:
    mr r3, r30
    b fn_8012B48C_L_8012B910
    fn_8012B48C_L_8012B4CC:
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r29, r3
    lwz r3, 0xe8(r30)
    bl GetCharacterDataEntry
    mr r28, r3
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq fn_8012B48C_L_8012B500
    lwz r4, 0x0(r29)
    li r5, 0x0
    bl clNormal3D_Construct
    fn_8012B48C_L_8012B500:
    stw r26, 0x0(r30)
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq fn_8012B48C_L_8012B520
    lwz r4, 0x4(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    fn_8012B48C_L_8012B520:
    stw r26, 0x8(r30)
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq fn_8012B48C_L_8012B540
    lwz r4, 0x8(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    fn_8012B48C_L_8012B540:
    stw r26, 0xc(r30)
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq fn_8012B48C_L_8012B560
    lwz r4, 0xc(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    fn_8012B48C_L_8012B560:
    stw r26, 0x10(r30)
    mr r4, r25
    li r5, 0x0
    lwz r3, 0x0(r30)
    bl Object_SetAnimBinding
    lwz r3, 0x8(r30)
    mr r4, r25
    li r5, 0x0
    bl Object_SetAnimBinding
    lwz r3, 0x8(r30)
    li r4, 0x0
    lfs f1, lbl_806D70E0(r2)
    lfs f2, lbl_806D70EC(r2)
    bl Object_DriveAnimAndSkin
    li r27, 0x0
    mr r26, r30
    mr r29, r27
    li r25, 0x0
    fn_8012B48C_L_8012B5A8:
    lwz r3, 0x18(r28)
    lwzx r0, r3, r27
    cmplwi r0, 0x0
    beq fn_8012B48C_L_8012B5E0
    li r3, 0x5c
    bl Alloc
    mr. r24, r3
    beq fn_8012B48C_L_8012B5D8
    lwz r4, 0x18(r28)
    li r5, 0x0
    lwzx r4, r4, r27
    bl clNormal3D_Construct
    fn_8012B48C_L_8012B5D8:
    stw r24, 0x14(r26)
    b fn_8012B48C_L_8012B5E4
    fn_8012B48C_L_8012B5E0:
    stw r29, 0x14(r26)
    fn_8012B48C_L_8012B5E4:
    addi r25, r25, 0x1
    addi r26, r26, 0x4
    cmpwi r25, 0x31
    addi r27, r27, 0x4
    blt fn_8012B48C_L_8012B5A8
    lwz r3, 0xc(r30)
    lfs f1, lbl_806D70F0(r2)
    lfs f2, lbl_806D70E0(r2)
    lwz r4, 0x14(r30)
    bl Object_DriveAnimAndSkin
    lwz r3, 0x8(r30)
    bl Archive_GetRootJObj
    mr r29, r3
    lwz r3, 0xc(r30)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0x8(r30)
    lfs f1, lbl_806D70E0(r2)
    mr r5, r29
    li r6, 0x0
    bl ObjectTree_BlendOrCopy_Timed
    lwz r0, 0xe8(r30)
    lis r3, mario_cart_tire_fl_joint@ha
    addi r4, r3, mario_cart_tire_fl_joint@l
    lwz r3, 0x0(r30)
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl ResolveJointByName
    stw r3, 0x144(r30)
    lis r3, mario_cart_tire_fr_joint@ha
    addi r4, r3, mario_cart_tire_fr_joint@l
    lwz r0, 0xe8(r30)
    lwz r3, 0x0(r30)
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl ResolveJointByName
    stw r3, 0x148(r30)
    lis r3, mario_cart_tire_rl_joint@ha
    addi r4, r3, mario_cart_tire_rl_joint@l
    lwz r0, 0xe8(r30)
    lwz r3, 0x0(r30)
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl ResolveJointByName
    stw r3, 0x14c(r30)
    lis r3, mario_cart_tire_rr_joint@ha
    addi r4, r3, mario_cart_tire_rr_joint@l
    lwz r0, 0xe8(r30)
    lwz r3, 0x0(r30)
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl ResolveJointByName
    stw r3, 0x150(r30)
    lis r3, mario_cart_engine_joint@ha
    addi r4, r3, mario_cart_engine_joint@l
    lwz r0, 0xe8(r30)
    lwz r3, 0x0(r30)
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl ResolveJointByName
    stw r3, 0x12c(r30)
    lis r3, mario_cart_body_joint@ha
    addi r4, r3, mario_cart_body_joint@l
    lwz r0, 0xe8(r30)
    lwz r3, 0x0(r30)
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl ResolveJointByName
    stw r3, 0x130(r30)
    lwz r0, 0xe8(r30)
    cmpwi r0, 0xc
    beq fn_8012B48C_L_8012B760
    lis r3, chara_mario_hand_goo_joint@ha
    slwi r0, r0, 2
    addi r4, r3, chara_mario_hand_goo_joint@l
    lwz r3, 0x8(r30)
    lwzx r4, r4, r0
    bl ResolveJointByName
    stw r3, 0x158(r30)
    lis r3, chara_mario_hand_pa_joint@ha
    addi r4, r3, chara_mario_hand_pa_joint@l
    lwz r0, 0xe8(r30)
    lwz r3, 0x8(r30)
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl ResolveJointByName
    stw r3, 0x15c(r30)
    lis r3, chara_mario_hand_fin_joint@ha
    addi r4, r3, chara_mario_hand_fin_joint@l
    lwz r0, 0xe8(r30)
    lwz r3, 0x8(r30)
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl ResolveJointByName
    stw r3, 0x160(r30)
    fn_8012B48C_L_8012B760:
    lwz r0, 0xe8(r30)
    lis r3, chara_mario_r_hand_null_joint@ha
    addi r4, r3, chara_mario_r_hand_null_joint@l
    lwz r3, 0x8(r30)
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl ResolveJointByName
    stw r3, 0x164(r30)
    li r3, 0xc4
    bl Alloc
    mr. r24, r3
    beq fn_8012B48C_L_8012B7AC
    lwz r6, 0x144(r30)
    mr r4, r31
    lwz r7, 0x148(r30)
    li r5, 0x0
    lwz r8, 0x14c(r30)
    lwz r9, 0x150(r30)
    bl KartTireFX_Ctor
    fn_8012B48C_L_8012B7AC:
    stw r24, 0x4(r30)
    lwz r3, 0x4(r30)
    cmplwi r3, 0x0
    beq fn_8012B48C_L_8012B7C4
    li r4, 0x0
    bl KartTireFX_SetVisibleAll4Wheels
    fn_8012B48C_L_8012B7C4:
    lwz r0, 0xe8(r30)
    cmpwi r0, 0x3
    bne fn_8012B48C_L_8012B824
    lis r4, lbl_80356708@ha
    lwz r3, 0x8(r30)
    addi r4, r4, lbl_80356708@l
    bl ResolveJointByName
    stw r3, 0x128(r30)
    li r3, 0x5c
    bl Alloc
    mr. r24, r3
    beq fn_8012B48C_L_8012B804
    lis r4, lbl_80356724@ha
    li r5, 0x0
    addi r4, r4, lbl_80356724@l
    bl clNormal3D_Construct
    fn_8012B48C_L_8012B804:
    lfs f1, lbl_806D70E0(r2)
    li r4, 0x0
    stw r24, 0x124(r30)
    fmr f3, f1
    lfs f2, lbl_806D70EC(r2)
    lwz r3, 0x124(r30)
    lfs f4, lbl_806D70F0(r2)
    bl clNormal3D_SetScale
    fn_8012B48C_L_8012B824:
    lwz r28, 0x12c(r30)
    cmplwi r28, 0x0
    bne fn_8012B48C_L_8012B840
    addi r3, r2, -0x3198  /* lbl_806D70C8 */
    li r4, 0x47c
    addi r5, r2, -0x3190  /* lbl_806D70D0 */
    bl __assert
    fn_8012B48C_L_8012B840:
    cmplwi r28, 0x0
    beq fn_8012B48C_L_8012B888
    bne fn_8012B48C_L_8012B85C
    addi r3, r2, -0x3198  /* lbl_806D70C8 */
    li r4, 0x25d
    addi r5, r2, -0x3190  /* lbl_806D70D0 */
    bl __assert
    fn_8012B48C_L_8012B85C:
    lwz r4, 0x14(r28)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_8012B48C_L_8012B878
    rlwinm. r0, r4, 0, 25, 25
    beq fn_8012B48C_L_8012B878
    li r3, 0x1
    fn_8012B48C_L_8012B878:
    clrlwi. r0, r3, 24
    beq fn_8012B48C_L_8012B888
    mr r3, r28
    bl HSD_JObjSetupMatrixSub
    fn_8012B48C_L_8012B888:
    lfs f0, 0x60(r28)
    stfs f0, 0x13c(r30)
    lwz r28, 0x130(r30)
    cmplwi r28, 0x0
    bne fn_8012B48C_L_8012B8AC
    addi r3, r2, -0x3198  /* lbl_806D70C8 */
    li r4, 0x47c
    addi r5, r2, -0x3190  /* lbl_806D70D0 */
    bl __assert
    fn_8012B48C_L_8012B8AC:
    cmplwi r28, 0x0
    beq fn_8012B48C_L_8012B8F4
    bne fn_8012B48C_L_8012B8C8
    addi r3, r2, -0x3198  /* lbl_806D70C8 */
    li r4, 0x25d
    addi r5, r2, -0x3190  /* lbl_806D70D0 */
    bl __assert
    fn_8012B48C_L_8012B8C8:
    lwz r4, 0x14(r28)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_8012B48C_L_8012B8E4
    rlwinm. r0, r4, 0, 25, 25
    beq fn_8012B48C_L_8012B8E4
    li r3, 0x1
    fn_8012B48C_L_8012B8E4:
    clrlwi. r0, r3, 24
    beq fn_8012B48C_L_8012B8F4
    mr r3, r28
    bl HSD_JObjSetupMatrixSub
    fn_8012B48C_L_8012B8F4:
    lfs f0, 0x60(r28)
    mr r3, r30
    lfs f1, lbl_806D70EC(r2)
    stfs f0, 0x140(r30)
    lfs f0, lbl_806D70E0(r2)
    stfs f1, 0x134(r30)
    stfs f0, 0x138(r30)
    fn_8012B48C_L_8012B910:
    lmw r24, 0x10(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

