/*
 * 0x8014DD80..0x8014E004: scene update.
 */
#pragma cplusplus on

extern "C" {
extern void Alloc();
extern void HSD_CObjAddAnim();
extern void HSD_CObjAnim();
extern void HSD_CObjReqAnim();
extern void Scene3D_Init();
extern void SceneModel_Init();
extern void clNormal3D_Construct();
extern void fn_80157A68();
extern unsigned int lbl_806D8064;
extern unsigned int lbl_806D8068;
extern unsigned int lbl_806D806C;
extern unsigned int lbl_80364368[];
extern unsigned int lbl_80419EF8[];
extern void MemoryManager_TimedFree();
asm void fn_8014DD80(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; void *f13; unsigned int f14; void *f15; unsigned int f16; void *f17; } extab_fn_8014DD80 = { 0x180A0000, 0x000000E0, 0x00000028, 0x00000118, 0x00000030, 0x00000150, 0x00000038, 0x0000022C, 0x00000040, 0x00000000, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014DD80 = {
    (void *)&fn_8014DD80, 0x00000284, (void *)&extab_fn_8014DD80
};

}


extern "C" asm void fn_8014DD80(void) { /* 0x8014DD80 size:0x284 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r3
    stw r30, 0x28(r1)
    mr r30, r4
    cmplwi r30, 0x1d
    stw r29, 0x24(r1)
    bge fn_8014DD80_L_8014DDB0
    cmplwi r5, 0x4
    blt fn_8014DD80_L_8014DDB8
    fn_8014DD80_L_8014DDB0:
    li r3, 0x0
    b fn_8014DD80_L_8014DFE8
    fn_8014DD80_L_8014DDB8:
    lwz r0, 0x0(r31)
    slwi r3, r5, 29
    or r6, r30, r3
    cmplwi r0, 0x0
    beq fn_8014DD80_L_8014DE04
    lwz r4, 0x8(r31)
    addi r0, r31, 0x4
    b fn_8014DD80_L_8014DDFC
    fn_8014DD80_L_8014DDD8:
    lwz r3, 0x8(r4)
    cmplw r3, r6
    bne fn_8014DD80_L_8014DDF8
    lwz r3, 0xc(r4)
    addi r0, r3, 0x1
    stw r0, 0xc(r4)
    lwz r3, 0x10(r4)
    b fn_8014DD80_L_8014DFE8
    fn_8014DD80_L_8014DDF8:
    lwz r4, 0x4(r4)
    fn_8014DD80_L_8014DDFC:
    cmplw r4, r0
    bne fn_8014DD80_L_8014DDD8
    fn_8014DD80_L_8014DE04:
    li r0, 0x1
    cmpwi r5, 0x2
    stw r6, 0x10(r1)
    stw r0, 0x14(r1)
    beq fn_8014DD80_L_8014DEAC
    bge fn_8014DD80_L_8014DE2C
    cmpwi r5, 0x0
    beq fn_8014DD80_L_8014DE38
    bge fn_8014DD80_L_8014DE74
    b fn_8014DD80_L_8014DFC0
    fn_8014DD80_L_8014DE2C:
    cmpwi r5, 0x4
    bge fn_8014DD80_L_8014DFC0
    b fn_8014DD80_L_8014DF84
    fn_8014DD80_L_8014DE38:
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq fn_8014DD80_L_8014DE60
    lis r4, lbl_80364368@ha
    slwi r0, r30, 2
    addi r4, r4, lbl_80364368@l
    li r5, 0x0
    lwzx r4, r4, r0
    bl clNormal3D_Construct
    fn_8014DD80_L_8014DE60:
    cmplwi r29, 0x0
    stw r29, 0x18(r1)
    bne fn_8014DD80_L_8014DFC8
    li r3, 0x0
    b fn_8014DD80_L_8014DFE8
    fn_8014DD80_L_8014DE74:
    li r3, 0x3084
    bl Alloc
    mr. r29, r3
    beq fn_8014DD80_L_8014DE98
    lis r4, lbl_80364368@ha
    slwi r0, r30, 2
    addi r4, r4, lbl_80364368@l
    lwzx r4, r4, r0
    bl Scene3D_Init
    fn_8014DD80_L_8014DE98:
    cmplwi r29, 0x0
    stw r29, 0x18(r1)
    bne fn_8014DD80_L_8014DFC8
    li r3, 0x0
    b fn_8014DD80_L_8014DFE8
    fn_8014DD80_L_8014DEAC:
    li r3, 0x3090
    bl Alloc
    mr. r29, r3
    beq fn_8014DD80_L_8014DEEC
    lis r4, lbl_80364368@ha
    slwi r0, r30, 2
    addi r4, r4, lbl_80364368@l
    lwzx r4, r4, r0
    bl Scene3D_Init
    lis r3, lbl_80419EF8@ha
    lfs f1, lbl_806D806C(r2)
    addi r0, r3, lbl_80419EF8@l
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x0(r29)
    stfs f1, 0x3088(r29)
    stfs f0, 0x308c(r29)
    fn_8014DD80_L_8014DEEC:
    cmplwi r29, 0x0
    stw r29, 0x18(r1)
    bne fn_8014DD80_L_8014DF00
    li r3, 0x0
    b fn_8014DD80_L_8014DFE8
    fn_8014DD80_L_8014DF00:
    lwz r0, 0x4(r29)
    cmplwi r0, 0x0
    beq fn_8014DD80_L_8014DFC8
    li r0, 0x1
    lfs f1, lbl_806D8064(r2)
    stb r0, 0x3084(r29)
    lfs f0, lbl_806D8068(r2)
    stfs f1, 0x308c(r29)
    stfs f0, 0x3088(r29)
    lwz r3, 0x2c(r29)
    cmplwi r3, 0x0
    bne fn_8014DD80_L_8014DF38
    li r4, 0x0
    b fn_8014DD80_L_8014DF64
    fn_8014DD80_L_8014DF38:
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne fn_8014DD80_L_8014DF4C
    li r4, 0x0
    b fn_8014DD80_L_8014DF64
    fn_8014DD80_L_8014DF4C:
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne fn_8014DD80_L_8014DF60
    li r4, 0x0
    b fn_8014DD80_L_8014DF64
    fn_8014DD80_L_8014DF60:
    lwz r4, 0x0(r3)
    fn_8014DD80_L_8014DF64:
    lwz r3, 0x4(r29)
    bl HSD_CObjAddAnim
    lwz r3, 0x4(r29)
    lfs f1, 0x308c(r29)
    bl HSD_CObjReqAnim
    lwz r3, 0x4(r29)
    bl HSD_CObjAnim
    b fn_8014DD80_L_8014DFC8
    fn_8014DD80_L_8014DF84:
    li r3, 0x28
    bl Alloc
    mr. r29, r3
    beq fn_8014DD80_L_8014DFAC
    lis r4, lbl_80364368@ha
    slwi r0, r30, 2
    addi r4, r4, lbl_80364368@l
    li r5, 0x1
    lwzx r4, r4, r0
    bl SceneModel_Init
    fn_8014DD80_L_8014DFAC:
    cmplwi r29, 0x0
    stw r29, 0x18(r1)
    bne fn_8014DD80_L_8014DFC8
    li r3, 0x0
    b fn_8014DD80_L_8014DFE8
    fn_8014DD80_L_8014DFC0:
    li r3, 0x0
    b fn_8014DD80_L_8014DFE8
    fn_8014DD80_L_8014DFC8:
    addi r0, r31, 0x4
    mr r4, r31
    stw r0, 0xc(r1)
    addi r3, r1, 0x8
    addi r5, r1, 0xc
    addi r6, r1, 0x10
    bl fn_80157A68
    lwz r3, 0x18(r1)
    fn_8014DD80_L_8014DFE8:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

