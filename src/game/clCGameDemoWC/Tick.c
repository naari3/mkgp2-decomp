/* === extracted from auto_clCGameDemoWC_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void GetDisplayBufferIndex();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void ItemObjectManager_Update();
extern void KartItem_CancelAndQueueDefault();
extern void Object_SetField8_AndDirty();
extern void PSMTXConcat();
extern void PSMTXScale();
extern void RenderObj_ItemStateMachine_Timed();
extern void SetAnimWallHitA();
extern void SetAnimWallHitB();
extern void TornadoEffect_Tick();
extern void Vec3_Magnitude();
extern void Vec3_Subtract();
extern void VfxSlotMgr_Update();
extern void __assert();
extern void clNormal3D_Exec();
extern void fn_802C65F0();
extern void fn_802C6640();
extern void fn_802D1E34();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D4F94;
extern unsigned int lbl_806D4F98;
extern unsigned int lbl_806D4FA4;
extern unsigned int lbl_806D4FA8;
extern unsigned int lbl_806D4FAC;
extern unsigned int lbl_806D4FC0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80419E88[];
extern unsigned int lbl_80419EA0[];

/* --- function index (1 fns, .text 0x800AE108..0x800AE438) ---
 * [  0] 0x800AE108 size:0x330   global clCGameDemoWC_Tick
 */

/* --- forward decls --- */
asm void clCGameDemoWC_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clCGameDemoWC_Tick[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clCGameDemoWC_Tick = {
    (void *)&clCGameDemoWC_Tick, 0x00000330, (void *)extab_clCGameDemoWC_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clCGameDemoWC_Tick(void) { /* 0x800AE108 size:0x330 */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stfd f31, 0x70(r1)
    psq_st f31, 0x78(r1), 0, 0
    stw r31, 0x6c(r1)
    stw r30, 0x68(r1)
    mr r31, r3
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq clCGameDemoWC_Tick_L_800AE140
    li r0, 0x0
    stb r0, 0x4(r31)
    b clCGameDemoWC_Tick_L_800AE168
    clCGameDemoWC_Tick_L_800AE140:
    lfs f1, 0x8(r31)
    lfs f0, lbl_806D4F98(r2)
    lfs f2, lbl_806D4FA4(r2)
    fadds f0, f1, f0
    fcmpo cr0, f2, f0
    stfs f0, 0x8(r31)
    cror eq, lt, eq
    bne clCGameDemoWC_Tick_L_800AE168
    li r3, 0xf
    b clCGameDemoWC_Tick_L_800AE418
    clCGameDemoWC_Tick_L_800AE168:
    lwz r3, 0x14(r31)
    lfs f1, 0x8(r31)
    bl Object_SetField8_AndDirty
    lwz r3, 0x14(r31)
    bl clNormal3D_Exec
    lwz r3, 0xc(r31)
    lfs f0, lbl_806D4F94(r2)
    lfs f1, 0x308c(r3)
    lfs f2, 0x8(r31)
    fcmpo cr0, f1, f0
    blt clCGameDemoWC_Tick_L_800AE1A8
    fcmpo cr0, f2, f0
    blt clCGameDemoWC_Tick_L_800AE1A8
    li r0, 0x1
    stb r0, 0x3084(r3)
    stfs f2, 0x308c(r3)
    clCGameDemoWC_Tick_L_800AE1A8:
    lwz r30, 0xc(r31)
    lfs f0, lbl_806D4FA8(r2)
    lfs f1, 0x3088(r30)
    fcmpu cr0, f0, f1
    beq clCGameDemoWC_Tick_L_800AE1F4
    lbz r0, 0x3084(r30)
    cmplwi r0, 0x0
    beq clCGameDemoWC_Tick_L_800AE1D4
    li r0, 0x0
    stb r0, 0x3084(r30)
    b clCGameDemoWC_Tick_L_800AE1E0
    clCGameDemoWC_Tick_L_800AE1D4:
    lfs f0, 0x308c(r30)
    fadds f0, f0, f1
    stfs f0, 0x308c(r30)
    clCGameDemoWC_Tick_L_800AE1E0:
    lwz r3, 0x4(r30)
    lfs f1, 0x308c(r30)
    bl fn_802C6640
    lwz r3, 0x4(r30)
    bl fn_802C65F0
    clCGameDemoWC_Tick_L_800AE1F4:
    lwz r3, 0x58(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lfs f0, 0x2c(r31)
    addi r3, r31, 0x20
    lfs f1, lbl_806D4FAC(r2)
    stfs f0, 0x50(r1)
    fmr f2, f1
    lfs f0, 0x3c(r31)
    fmr f3, f1
    stfs f0, 0x54(r1)
    lfs f0, 0x4c(r31)
    stfs f0, 0x58(r1)
    bl PSMTXScale
    lwz r30, 0x50(r31)
    cmplwi r30, 0x0
    bne clCGameDemoWC_Tick_L_800AE250
    addi r3, r2, -0x52B0  /* lbl_806D4FB0 */
    li r4, 0x47c
    addi r5, r2, -0x52A8  /* lbl_806D4FB8 */
    bl __assert
    clCGameDemoWC_Tick_L_800AE250:
    cmplwi r30, 0x0
    beq clCGameDemoWC_Tick_L_800AE298
    bne clCGameDemoWC_Tick_L_800AE26C
    addi r3, r2, -0x52B0  /* lbl_806D4FB0 */
    li r4, 0x25d
    addi r5, r2, -0x52A8  /* lbl_806D4FB8 */
    bl __assert
    clCGameDemoWC_Tick_L_800AE26C:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne clCGameDemoWC_Tick_L_800AE288
    rlwinm. r0, r4, 0, 25, 25
    beq clCGameDemoWC_Tick_L_800AE288
    li r3, 0x1
    clCGameDemoWC_Tick_L_800AE288:
    clrlwi. r0, r3, 24
    beq clCGameDemoWC_Tick_L_800AE298
    mr r3, r30
    bl fn_802D1E34
    clCGameDemoWC_Tick_L_800AE298:
    addi r4, r31, 0x20
    addi r3, r30, 0x44
    mr r5, r4
    bl PSMTXConcat
    lfs f0, 0x2c(r31)
    addi r3, r1, 0x44
    addi r4, r1, 0x50
    addi r5, r1, 0x38
    stfs f0, 0x44(r1)
    lfs f0, 0x3c(r31)
    stfs f0, 0x48(r1)
    lfs f0, 0x4c(r31)
    stfs f0, 0x4c(r1)
    bl Vec3_Subtract
    addi r3, r1, 0x38
    bl Vec3_Magnitude
    lwz r0, 0x54(r31)
    lis r3, lbl_80419E88@ha
    lfs f2, lbl_806D4FA8(r2)
    addi r3, r3, lbl_80419E88@l
    slwi r0, r0, 2
    lfs f0, lbl_806D4F94(r2)
    lfsx f3, r3, r0
    fmuls f31, f2, f1
    fcmpo cr0, f0, f3
    cror eq, lt, eq
    bne clCGameDemoWC_Tick_L_800AE368
    lfs f0, 0x8(r31)
    fcmpo cr0, f3, f0
    cror eq, lt, eq
    bne clCGameDemoWC_Tick_L_800AE368
    lis r4, lbl_80419EA0@ha
    lwz r3, 0x18(r31)
    addi r4, r4, lbl_80419EA0@l
    lwzx r0, r4, r0
    cmpwi r0, 0x1
    beq clCGameDemoWC_Tick_L_800AE350
    bge clCGameDemoWC_Tick_L_800AE33C
    cmpwi r0, 0x0
    bge clCGameDemoWC_Tick_L_800AE348
    b clCGameDemoWC_Tick_L_800AE35C
    clCGameDemoWC_Tick_L_800AE33C:
    cmpwi r0, 0x3
    bge clCGameDemoWC_Tick_L_800AE35C
    b clCGameDemoWC_Tick_L_800AE358
    clCGameDemoWC_Tick_L_800AE348:
    bl KartItem_CancelAndQueueDefault
    b clCGameDemoWC_Tick_L_800AE35C
    clCGameDemoWC_Tick_L_800AE350:
    bl SetAnimWallHitB
    b clCGameDemoWC_Tick_L_800AE35C
    clCGameDemoWC_Tick_L_800AE358:
    bl SetAnimWallHitA
    clCGameDemoWC_Tick_L_800AE35C:
    lwz r3, 0x54(r31)
    addi r0, r3, 0x1
    stw r0, 0x54(r31)
    clCGameDemoWC_Tick_L_800AE368:
    lfs f0, lbl_806D4FC0(r2)
    li r4, 0x0
    lwz r3, 0x18(r31)
    fmuls f2, f0, f31
    lfs f1, lbl_806D4F94(r2)
    bl RenderObj_ItemStateMachine_Timed
    bl GetDisplayBufferIndex
    mr r4, r3
    lwz r3, 0x1c(r31)
    bl TornadoEffect_Tick
    lwz r3, 0xc(r31)
    addi r4, r1, 0x2c
    bl CObj_LoadProjMatrix
    lwz r3, 0xc(r31)
    addi r4, r1, 0x20
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lwz r9, 0x20(r1)
    addi r3, r1, 0x14
    lwz r8, 0x24(r1)
    addi r4, r1, 0x8
    lwz r7, 0x28(r1)
    lwz r6, 0x2c(r1)
    lwz r5, 0x30(r1)
    lwz r0, 0x34(r1)
    stw r9, 0x8(r1)
    stw r8, 0xc(r1)
    stw r7, 0x10(r1)
    stw r6, 0x14(r1)
    stw r5, 0x18(r1)
    stw r0, 0x1c(r1)
    bl VfxSlotMgr_Update
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    li r4, 0x400
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    li r3, -0x2
    beq clCGameDemoWC_Tick_L_800AE418
    li r3, 0xf
    clCGameDemoWC_Tick_L_800AE418:
    psq_l f31, 0x78(r1), 0, 0
    lwz r0, 0x84(r1)
    lfd f31, 0x70(r1)
    lwz r31, 0x6c(r1)
    lwz r30, 0x68(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

