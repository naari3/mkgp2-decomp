
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D6F24[7];
extern unsigned char lbl_806D6F2C[5];
extern void CObj_DebugVizPathFlush();
extern void DrawEffect_TickAndCull();
extern void HSD_StateInvalidate();
extern void ItemObjectManager_Render();
extern void KartDriver_RenderTimed();
extern void Object_RenderJObjTree();
extern void TransparentDraw_SortAndDispatch();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void fn_8016B0C4();
extern void fn_8016EACC();
extern void fn_80181790();
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D6EF8;
extern unsigned int lbl_806D6EFC;
extern unsigned int lbl_806D6F00;
extern unsigned int lbl_806D6F04;
extern unsigned int lbl_806D6F08;
extern unsigned int lbl_806D6F0C;
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void GetDisplayBufferIndex();
extern void GetInputManager();
extern void HSD_CObjAnim();
extern void HSD_CObjReqAnim();
extern void HSD_JObjClearFlagsAll();
extern void HSD_JObjSetFlagsAll();
extern void HSD_JObjSetMtxDirtySub();
extern void HSD_JObjSetupMatrixSub();
extern void InputMgr_GetPlayer();
extern void ItemObjectManager_Update();
extern void Object_SetField8_AndDirty();
extern void PSMTXConcat();
extern void PSMTXScale();
extern void PSVECCrossProduct();
extern void RenderObj_ItemStateMachine_Timed();
extern void Saturate_Double();
extern void SoundMgr_Play();
extern void TornadoEffect_Tick();
extern void Vec3_Magnitude();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void VfxSlotMgr_Update();
extern void __assert();
extern void asin();
extern void clNormal3D_Exec();
extern void fn_8016EC80();
extern void fn_80182204();
extern void fn_80182B50();
extern unsigned int lbl_806CF4C0;
extern unsigned int lbl_806D1508;
extern unsigned int lbl_806D6F10;
extern unsigned int lbl_806D6F14;
extern unsigned int lbl_806D6F18;
extern unsigned int lbl_806D6F1C;
extern unsigned int lbl_806D6F20;
extern unsigned int lbl_806D6F34;
extern unsigned int lbl_806D6F38;
extern unsigned int lbl_806D6F3C;
extern unsigned int lbl_806D6F40;
extern unsigned int lbl_806D6F44;
extern unsigned int lbl_806D6F48;
extern unsigned int lbl_806D6F4C;
extern unsigned int lbl_806D6F50;
extern unsigned int lbl_806D6F54;
extern unsigned int lbl_806D6F58;
extern unsigned int lbl_806D6F5C;
extern unsigned int lbl_806D6F60;
extern unsigned int lbl_806D6F64;
extern unsigned int lbl_806D6F68;
extern unsigned int lbl_806D6F6C;
extern unsigned int lbl_806D6F70;
extern unsigned int lbl_806D6F74;
extern unsigned int lbl_806D6F78;
extern unsigned int lbl_806D6F7C;
extern unsigned int lbl_806D6F80;
extern unsigned int lbl_806D6F84;
extern unsigned int lbl_806D6F88;
extern unsigned int lbl_80355EB4[];
extern void ClRomTable_PurgeAll();
extern void ItemObjectManager_Reset();
extern void KartDriver_Dtor();
extern void MemoryManager_TimedFree();
extern void Object_DtorWithGXSync();
extern void SceneDrawList_Reset();
extern void SetActiveCamera();
extern void SetCourseScene3D();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void TransparentDraw_RemoveByOwner();
extern void VfxSlotMgr_Shutdown();
extern void VisualEffectHolder_Dtor();
extern void clRom_PurgeAll();
extern void dtor_8002CDF4();
extern void fn_8016EFA8();
extern unsigned int lbl_80419F0C[];
extern unsigned int lbl_8048E258[];
extern void Alloc();
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void GameMode_BaseInit();
extern void HSD_CObjAddAnim();
extern void ItemObjectManager_Init();
extern void KartDriver_New_Full();
extern void PSMTXIdentity();
extern void ProcessSystemTick();
extern void ResolveJointByName();
extern void Scene3D_Init();
extern void SceneDrawList_RegisterArchive();
extern void SoundChannels_ClearAll();
extern void TornadoEffect_Ctor();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();
extern void fn_8016F010();
extern void fn_801825C8();
extern void fn_801825FC();
extern unsigned int g_characterId;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceCamera;
extern unsigned int lbl_806CF4B8;
extern unsigned int lbl_806CF4BC;
extern unsigned int lbl_80355A58[];
extern unsigned int lbl_80419EF8[];
extern void clCGameDemo_Dtor();
asm void fn_80125948(void);
asm void fn_80125B04(void);
asm void fn_80126728(void);
asm void fn_80126878(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80125948[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80125B04[8] = {
    0x18, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80126728[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; void *f37; unsigned int f38; unsigned int f39; void *f40; unsigned int f41; void *f42; unsigned int f43; unsigned int f44; void *f45; unsigned int f46; void *f47; unsigned int f48; unsigned int f49; void *f50; unsigned int f51; void *f52; unsigned int f53; unsigned int f54; void *f55; unsigned int f56; void *f57; unsigned int f58; unsigned int f59; void *f60; unsigned int f61; void *f62; unsigned int f63; unsigned int f64; void *f65; unsigned int f66; void *f67; unsigned int f68; unsigned int f69; void *f70; unsigned int f71; void *f72; unsigned int f73; unsigned int f74; void *f75; } extab_fn_80126878 = { 0x200A0000, 0x000000A4, 0x00130098, 0x00000100, 0x00000090, 0x00000190, 0x00070098, 0x000001C0, 0x000000A4, 0x000001E0, 0x00040098, 0x00000200, 0x000800B8, 0x0000022C, 0x00000098, 0x00000254, 0x000000CC, 0x00000264, 0x00060098, 0x00000290, 0x000000E0, 0x000002A0, 0x00040098, 0x000002C4, 0x000000F4, 0x000002D4, 0x000D0098, 0x0000031C, 0x00000108, 0x00000324, 0x003B0098, 0x0000041C, 0x0000011C, 0x00000428, 0x00000098, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&clCGameDemo_Dtor };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80125948 = {
    (void *)&fn_80125948, 0x000001BC, (void *)extab_fn_80125948
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80125B04 = {
    (void *)&fn_80125B04, 0x00000C24, (void *)extab_fn_80125B04
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80126728 = {
    (void *)&fn_80126728, 0x00000150, (void *)extab_fn_80126728
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80126878 = {
    (void *)&fn_80126878, 0x0000044C, (void *)&extab_fn_80126878
};



asm void fn_80125948(void) { /* 0x80125948 size:0x1BC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    lwz r3, 0xc(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_80125948_L_80125AF0
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_80125948_L_8012598C
    li r3, 0x0
    fn_80125948_L_8012598C:
    bl clDrawMan_Buckets_Reset
    bl TransparentDraw_SortAndDispatch
    lwz r3, 0xc(r31)
    bl CObj_DebugVizPathFlush
    bl fn_8016B0C4
    lwz r3, 0x14(r31)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0x18(r31)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0x38(r31)
    li r4, 0x0
    li r5, 0x1
    bl KartDriver_RenderTimed
    bl ItemObjectManager_Render
    bl DrawEffect_TickAndCull
    lwz r3, 0x1c(r31)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0x74(r31)
    bl fn_8016EACC
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_80125948_L_801259F4
    li r3, 0x0
    fn_80125948_L_801259F4:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_80125948_L_80125A08
    li r3, 0x0
    fn_80125948_L_80125A08:
    bl clDrawMan_Buckets_Dispatch
    lfs f2, 0x8(r31)
    li r7, 0x0
    lfs f0, lbl_806D6EF8(r2)
    fcmpo cr0, f2, f0
    bge fn_80125948_L_80125A5C
    fdivs f0, f2, f0
    lfs f1, lbl_806D6EFC(r2)
    fcmpo cr0, f0, f1
    bge fn_80125948_L_80125A34
    b fn_80125948_L_80125A48
    fn_80125948_L_80125A34:
    lfs f1, lbl_806D6F00(r2)
    fcmpo cr0, f0, f1
    ble fn_80125948_L_80125A44
    b fn_80125948_L_80125A48
    fn_80125948_L_80125A44:
    fmr f1, f0
    fn_80125948_L_80125A48:
    lfs f0, lbl_806D6F04(r2)
    fnmsubs f0, f0, f1, f0
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r7, 0xc(r1)
    fn_80125948_L_80125A5C:
    lfs f0, lbl_806D6F08(r2)
    fcmpo cr0, f2, f0
    ble fn_80125948_L_80125AB0
    lfs f1, lbl_806D6F0C(r2)
    lfs f0, lbl_806D6EF8(r2)
    fsubs f1, f1, f2
    lfs f2, lbl_806D6EFC(r2)
    fdivs f0, f1, f0
    fcmpo cr0, f0, f2
    bge fn_80125948_L_80125A88
    b fn_80125948_L_80125A9C
    fn_80125948_L_80125A88:
    lfs f2, lbl_806D6F00(r2)
    fcmpo cr0, f0, f2
    ble fn_80125948_L_80125A98
    b fn_80125948_L_80125A9C
    fn_80125948_L_80125A98:
    fmr f2, f0
    fn_80125948_L_80125A9C:
    lfs f0, lbl_806D6F04(r2)
    fnmsubs f0, f0, f2, f0
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r7, 0xc(r1)
    fn_80125948_L_80125AB0:
    clrlwi. r0, r7, 24
    beq fn_80125948_L_80125AD4
    lwz r3, 0xc(r31)
    li r4, 0x0
    lfs f1, lbl_806D6F00(r2)
    li r5, 0x0
    li r6, 0x0
    li r8, 0x0
    bl fn_80181790
    fn_80125948_L_80125AD4:
    lwz r3, 0xc(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    li r3, 0x7f
    bl HSD_StateInvalidate
    fn_80125948_L_80125AF0:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

asm void fn_80125B04(void) { /* 0x80125B04 size:0xC24 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stfd f30, 0xa0(r1)
    psq_st f30, 0xa8(r1), 0, 0
    stfd f29, 0x90(r1)
    psq_st f29, 0x98(r1), 0, 0
    stw r31, 0x8c(r1)
    stw r30, 0x88(r1)
    stw r29, 0x84(r1)
    mr r31, r3
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq fn_80125B04_L_80125B50
    li r0, 0x0
    stb r0, 0x4(r31)
    b fn_80125B04_L_80125B7C
    fn_80125B04_L_80125B50:
    lfs f2, 0x8(r31)
    lfs f1, lbl_806D6F00(r2)
    lfs f0, lbl_806D6F0C(r2)
    fadds f1, f2, f1
    stfs f1, 0x8(r31)
    lfs f1, 0x8(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80125B04_L_80125B7C
    li r3, 0xf
    b fn_80125B04_L_801266F4
    fn_80125B04_L_80125B7C:
    lfs f1, lbl_806D6F10(r2)
    lfs f0, 0x8(r31)
    fcmpu cr0, f1, f0
    bne fn_80125B04_L_80125B94
    li r3, 0xb5
    bl SoundMgr_Play
    fn_80125B04_L_80125B94:
    lwz r3, 0x14(r31)
    lfs f1, 0x8(r31)
    bl Object_SetField8_AndDirty
    lwz r3, 0x14(r31)
    bl clNormal3D_Exec
    lwz r3, 0xc(r31)
    lfs f0, lbl_806D6EFC(r2)
    lfs f1, 0x308c(r3)
    lfs f2, 0x8(r31)
    fcmpo cr0, f1, f0
    blt fn_80125B04_L_80125BD4
    fcmpo cr0, f2, f0
    blt fn_80125B04_L_80125BD4
    li r0, 0x1
    stb r0, 0x3084(r3)
    stfs f2, 0x308c(r3)
    fn_80125B04_L_80125BD4:
    lwz r30, 0xc(r31)
    lfs f0, lbl_806D6F14(r2)
    lfs f1, 0x3088(r30)
    fcmpu cr0, f0, f1
    beq fn_80125B04_L_80125C20
    lbz r0, 0x3084(r30)
    cmplwi r0, 0x0
    beq fn_80125B04_L_80125C00
    li r0, 0x0
    stb r0, 0x3084(r30)
    b fn_80125B04_L_80125C0C
    fn_80125B04_L_80125C00:
    lfs f0, 0x308c(r30)
    fadds f0, f0, f1
    stfs f0, 0x308c(r30)
    fn_80125B04_L_80125C0C:
    lwz r3, 0x4(r30)
    lfs f1, 0x308c(r30)
    bl HSD_CObjReqAnim
    lwz r3, 0x4(r30)
    bl HSD_CObjAnim
    fn_80125B04_L_80125C20:
    lwz r3, 0x18(r31)
    lfs f1, 0x8(r31)
    bl Object_SetField8_AndDirty
    lwz r3, 0x18(r31)
    bl clNormal3D_Exec
    lwz r3, 0x1c(r31)
    lfs f1, 0x8(r31)
    bl Object_SetField8_AndDirty
    lwz r3, 0x1c(r31)
    bl clNormal3D_Exec
    lwz r3, 0x24(r31)
    cmplwi r3, 0x0
    beq fn_80125B04_L_80125E40
    lfs f1, 0x8(r31)
    lfs f0, lbl_806D6F18(r2)
    fcmpo cr0, f1, f0
    blt fn_80125B04_L_80125C70
    lfs f0, lbl_806D6F1C(r2)
    fcmpo cr0, f1, f0
    ble fn_80125B04_L_80125C7C
    fn_80125B04_L_80125C70:
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    b fn_80125B04_L_80125E40
    fn_80125B04_L_80125C7C:
    li r4, 0x10
    bl HSD_JObjClearFlagsAll
    lfs f2, 0x8(r31)
    lfs f1, lbl_806D6F18(r2)
    lfs f0, lbl_806D6F20(r2)
    fsubs f1, f2, f1
    lfs f2, lbl_806D6EFC(r2)
    lfs f3, lbl_806D6F00(r2)
    fdivs f1, f1, f0
    bl Saturate_Double
    lwz r30, 0x24(r31)
    fmr f31, f1
    cmplwi r30, 0x0
    bne fn_80125B04_L_80125CC4
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x325
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125CC4:
    lfs f1, lbl_806D6F34(r2)
    lfs f0, lbl_806D6F00(r2)
    fmadds f29, f1, f31, f0
    stfs f29, 0x2c(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_80125D28
    cmplwi r30, 0x0
    beq fn_80125B04_L_80125D28
    bne fn_80125B04_L_80125CFC
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125CFC:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_80125D18
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_80125D18
    li r3, 0x1
    fn_80125B04_L_80125D18:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_80125D28
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_80125D28:
    lwz r30, 0x24(r31)
    cmplwi r30, 0x0
    bne fn_80125B04_L_80125D44
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x333
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125D44:
    lfs f1, lbl_806D6F38(r2)
    lfs f0, lbl_806D6F00(r2)
    fmadds f0, f1, f31, f0
    stfs f0, 0x30(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_80125DA8
    cmplwi r30, 0x0
    beq fn_80125B04_L_80125DA8
    bne fn_80125B04_L_80125D7C
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125D7C:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_80125D98
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_80125D98
    li r3, 0x1
    fn_80125B04_L_80125D98:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_80125DA8
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_80125DA8:
    lwz r30, 0x24(r31)
    cmplwi r30, 0x0
    bne fn_80125B04_L_80125DC4
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x341
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125DC4:
    stfs f29, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_80125E1C
    cmplwi r30, 0x0
    beq fn_80125B04_L_80125E1C
    bne fn_80125B04_L_80125DF0
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125DF0:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_80125E0C
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_80125E0C
    li r3, 0x1
    fn_80125B04_L_80125E0C:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_80125E1C
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_80125E1C:
    lfs f0, lbl_806D6F04(r2)
    lwz r3, 0x24(r31)
    fmuls f0, f0, f31
    fctiwz f0, f0
    stfd f0, 0x78(r1)
    lwz r0, 0x7c(r1)
    subfic r0, r0, 0xff
    clrlwi r4, r0, 24
    bl fn_80182204
    fn_80125B04_L_80125E40:
    lwz r3, 0x28(r31)
    cmplwi r3, 0x0
    beq fn_80125B04_L_80126038
    lfs f1, 0x8(r31)
    lfs f0, lbl_806D6F3C(r2)
    fcmpo cr0, f1, f0
    blt fn_80125B04_L_80125E68
    lfs f0, lbl_806D6F40(r2)
    fcmpo cr0, f1, f0
    ble fn_80125B04_L_80125E74
    fn_80125B04_L_80125E68:
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    b fn_80125B04_L_80126038
    fn_80125B04_L_80125E74:
    li r4, 0x10
    bl HSD_JObjClearFlagsAll
    lfs f2, 0x8(r31)
    lfs f1, lbl_806D6F3C(r2)
    lfs f0, lbl_806D6F20(r2)
    fsubs f1, f2, f1
    lfs f2, lbl_806D6EFC(r2)
    lfs f3, lbl_806D6F00(r2)
    fdivs f1, f1, f0
    bl Saturate_Double
    lwz r30, 0x28(r31)
    fmr f31, f1
    cmplwi r30, 0x0
    bne fn_80125B04_L_80125EBC
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x325
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125EBC:
    lfs f1, lbl_806D6F34(r2)
    lfs f0, lbl_806D6F00(r2)
    fmadds f29, f1, f31, f0
    stfs f29, 0x2c(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_80125F20
    cmplwi r30, 0x0
    beq fn_80125B04_L_80125F20
    bne fn_80125B04_L_80125EF4
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125EF4:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_80125F10
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_80125F10
    li r3, 0x1
    fn_80125B04_L_80125F10:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_80125F20
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_80125F20:
    lwz r30, 0x28(r31)
    cmplwi r30, 0x0
    bne fn_80125B04_L_80125F3C
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x333
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125F3C:
    lfs f1, lbl_806D6F38(r2)
    lfs f0, lbl_806D6F00(r2)
    fmadds f0, f1, f31, f0
    stfs f0, 0x30(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_80125FA0
    cmplwi r30, 0x0
    beq fn_80125B04_L_80125FA0
    bne fn_80125B04_L_80125F74
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125F74:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_80125F90
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_80125F90
    li r3, 0x1
    fn_80125B04_L_80125F90:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_80125FA0
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_80125FA0:
    lwz r30, 0x28(r31)
    cmplwi r30, 0x0
    bne fn_80125B04_L_80125FBC
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x341
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125FBC:
    stfs f29, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_80126014
    cmplwi r30, 0x0
    beq fn_80125B04_L_80126014
    bne fn_80125B04_L_80125FE8
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80125FE8:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_80126004
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_80126004
    li r3, 0x1
    fn_80125B04_L_80126004:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_80126014
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_80126014:
    lfs f0, lbl_806D6F04(r2)
    lwz r3, 0x28(r31)
    fmuls f0, f0, f31
    fctiwz f0, f0
    stfd f0, 0x78(r1)
    lwz r0, 0x7c(r1)
    subfic r0, r0, 0xff
    clrlwi r4, r0, 24
    bl fn_80182204
    fn_80125B04_L_80126038:
    lwz r3, 0x2c(r31)
    cmplwi r3, 0x0
    beq fn_80125B04_L_801262A4
    lwz r29, 0x20(r31)
    cmplwi r29, 0x0
    beq fn_80125B04_L_801262A4
    lfs f1, 0x8(r31)
    lfs f0, lbl_806D6F44(r2)
    fcmpo cr0, f1, f0
    ble fn_80125B04_L_8012606C
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    b fn_80125B04_L_801262A4
    fn_80125B04_L_8012606C:
    cmplwi r29, 0x0
    bne fn_80125B04_L_80126084
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x47c
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80126084:
    cmplwi r29, 0x0
    beq fn_80125B04_L_801260CC
    bne fn_80125B04_L_801260A0
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_801260A0:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_801260BC
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_801260BC
    li r3, 0x1
    fn_80125B04_L_801260BC:
    clrlwi. r0, r3, 24
    beq fn_80125B04_L_801260CC
    mr r3, r29
    bl HSD_JObjSetupMatrixSub
    fn_80125B04_L_801260CC:
    lwz r30, 0x2c(r31)
    lfs f30, 0x60(r29)
    lfs f1, lbl_806D6F48(r2)
    cmplwi r30, 0x0
    lfs f29, 0x70(r29)
    lfs f0, lbl_806D6F4C(r2)
    fadds f30, f30, f1
    lfs f31, 0x50(r29)
    fadds f29, f29, f0
    bne fn_80125B04_L_80126104
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x3a9
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80126104:
    stfs f31, 0x38(r30)
    stfs f30, 0x3c(r30)
    stfs f29, 0x40(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_80126164
    cmplwi r30, 0x0
    beq fn_80125B04_L_80126164
    bne fn_80125B04_L_80126138
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80126138:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_80126154
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_80126154
    li r3, 0x1
    fn_80125B04_L_80126154:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_80126164
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_80126164:
    lfs f1, 0x8(r31)
    lfs f0, lbl_806D6F50(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80125B04_L_80126294
    fsubs f1, f1, f0
    lfs f0, lbl_806D6F54(r2)
    lfs f2, lbl_806D6EFC(r2)
    lfs f3, lbl_806D6F00(r2)
    fdivs f1, f1, f0
    bl Saturate_Double
    lwz r30, 0x2c(r31)
    fmr f31, f1
    cmplwi r30, 0x0
    bne fn_80125B04_L_801261B0
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x325
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_801261B0:
    lfs f1, lbl_806D6F58(r2)
    lfs f0, lbl_806D6F00(r2)
    fmadds f0, f1, f31, f0
    stfs f0, 0x2c(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_80126214
    cmplwi r30, 0x0
    beq fn_80125B04_L_80126214
    bne fn_80125B04_L_801261E8
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_801261E8:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_80126204
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_80126204
    li r3, 0x1
    fn_80125B04_L_80126204:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_80126214
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_80126214:
    lwz r30, 0x2c(r31)
    cmplwi r30, 0x0
    bne fn_80125B04_L_80126230
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x333
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80126230:
    lfs f1, lbl_806D6F5C(r2)
    lfs f0, lbl_806D6F00(r2)
    fnmsubs f0, f1, f31, f0
    stfs f0, 0x30(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_80126294
    cmplwi r30, 0x0
    beq fn_80125B04_L_80126294
    bne fn_80125B04_L_80126268
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80126268:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_80126284
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_80126284
    li r3, 0x1
    fn_80125B04_L_80126284:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_80126294
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_80126294:
    lwz r3, 0x2c(r31)
    lfs f1, lbl_806CF4C0(r13)
    lfs f2, lbl_806D1508(r13)
    bl fn_80182B50
    fn_80125B04_L_801262A4:
    lwz r0, 0x30(r31)
    cmplwi r0, 0x0
    beq fn_80125B04_L_80126330
    lwz r0, 0x34(r31)
    cmplwi r0, 0x0
    beq fn_80125B04_L_80126330
    lfs f2, 0x8(r31)
    lfs f0, lbl_806D6F3C(r2)
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    beq fn_80125B04_L_801262E0
    lfs f0, lbl_806D6F60(r2)
    fcmpo cr0, f2, f0
    cror eq, lt, eq
    bne fn_80125B04_L_80126330
    fn_80125B04_L_801262E0:
    lfs f1, lbl_806D6F64(r2)
    lfs f0, lbl_806D6F68(r2)
    fsubs f1, f2, f1
    lfs f2, lbl_806D6EFC(r2)
    lfs f3, lbl_806D6F00(r2)
    fdivs f1, f1, f0
    bl Saturate_Double
    lfs f0, lbl_806D6F04(r2)
    lwz r3, 0x30(r31)
    fmuls f0, f0, f1
    fctiwz f0, f0
    stfd f0, 0x78(r1)
    lwz r0, 0x7c(r1)
    clrlwi r0, r0, 24
    subfic r29, r0, 0xff
    clrlwi r4, r29, 24
    bl fn_80182204
    lwz r3, 0x34(r31)
    clrlwi r4, r29, 24
    bl fn_80182204
    fn_80125B04_L_80126330:
    lwz r3, 0x78(r31)
    lfs f1, lbl_806D6EFC(r2)
    lfs f2, lbl_806D6F6C(r2)
    bl fn_80182B50
    lwz r3, 0x7c(r31)
    lfs f1, lbl_806D6EFC(r2)
    lfs f2, lbl_806D6F70(r2)
    bl fn_80182B50
    lwz r3, 0x80(r31)
    lfs f1, lbl_806D6EFC(r2)
    lfs f2, lbl_806D6F70(r2)
    bl fn_80182B50
    lfs f2, 0x8c(r31)
    lfs f1, lbl_806D6F74(r2)
    lfs f0, lbl_806D6F78(r2)
    fadds f1, f2, f1
    stfs f1, 0x8c(r31)
    lfs f1, 0x8c(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80125B04_L_8012638C
    fsubs f0, f1, f0
    stfs f0, 0x8c(r31)
    fn_80125B04_L_8012638C:
    lfs f2, 0x90(r31)
    lfs f1, lbl_806D6F7C(r2)
    lfs f0, lbl_806D6F78(r2)
    fadds f1, f2, f1
    stfs f1, 0x90(r31)
    lfs f1, 0x90(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80125B04_L_801263B8
    fsubs f0, f1, f0
    stfs f0, 0x90(r31)
    fn_80125B04_L_801263B8:
    lwz r30, 0x84(r31)
    lfs f31, 0x8c(r31)
    cmplwi r30, 0x0
    bne fn_80125B04_L_801263D8
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x2b8
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_801263D8:
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 14, 14
    beq fn_80125B04_L_801263F8
    lis r4, lbl_80355EB4@ha
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    addi r5, r4, lbl_80355EB4@l
    li r4, 0x2b9
    bl __assert
    fn_80125B04_L_801263F8:
    stfs f31, 0x20(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_80126450
    cmplwi r30, 0x0
    beq fn_80125B04_L_80126450
    bne fn_80125B04_L_80126424
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80126424:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_80126440
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_80126440
    li r3, 0x1
    fn_80125B04_L_80126440:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_80126450
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_80126450:
    lwz r30, 0x88(r31)
    lfs f31, 0x90(r31)
    cmplwi r30, 0x0
    bne fn_80125B04_L_80126470
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x2b8
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80126470:
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 14, 14
    beq fn_80125B04_L_80126490
    lis r4, lbl_80355EB4@ha
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    addi r5, r4, lbl_80355EB4@l
    li r4, 0x2b9
    bl __assert
    fn_80125B04_L_80126490:
    stfs f31, 0x20(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_80125B04_L_801264E8
    cmplwi r30, 0x0
    beq fn_80125B04_L_801264E8
    bne fn_80125B04_L_801264BC
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_801264BC:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_801264D8
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_801264D8
    li r3, 0x1
    fn_80125B04_L_801264D8:
    clrlwi. r0, r3, 24
    bne fn_80125B04_L_801264E8
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    fn_80125B04_L_801264E8:
    lfs f0, 0x4c(r31)
    addi r3, r31, 0x40
    lfs f1, lbl_806D6F80(r2)
    stfs f0, 0x68(r1)
    fmr f2, f1
    lfs f29, lbl_806D6EFC(r2)
    lfs f0, 0x5c(r31)
    fmr f3, f1
    stfs f0, 0x6c(r1)
    lfs f0, 0x6c(r31)
    stfs f0, 0x70(r1)
    bl PSMTXScale
    lwz r30, 0x70(r31)
    cmplwi r30, 0x0
    bne fn_80125B04_L_80126534
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x47c
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80126534:
    cmplwi r30, 0x0
    beq fn_80125B04_L_8012657C
    bne fn_80125B04_L_80126550
    la r3, lbl_806D6F24(r2)  /* lbl_806D6F24 */
    li r4, 0x25d
    la r5, lbl_806D6F2C(r2)  /* lbl_806D6F2C */
    bl __assert
    fn_80125B04_L_80126550:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_80125B04_L_8012656C
    rlwinm. r0, r4, 0, 25, 25
    beq fn_80125B04_L_8012656C
    li r3, 0x1
    fn_80125B04_L_8012656C:
    clrlwi. r0, r3, 24
    beq fn_80125B04_L_8012657C
    mr r3, r30
    bl HSD_JObjSetupMatrixSub
    fn_80125B04_L_8012657C:
    addi r4, r31, 0x40
    addi r3, r30, 0x44
    mr r5, r4
    bl PSMTXConcat
    lfs f0, 0x4c(r31)
    addi r3, r1, 0x5c
    addi r4, r1, 0x68
    addi r5, r1, 0x50
    stfs f0, 0x5c(r1)
    lfs f0, 0x5c(r31)
    stfs f0, 0x60(r1)
    lfs f0, 0x6c(r31)
    stfs f0, 0x64(r1)
    bl Vec3_Subtract
    addi r3, r1, 0x50
    bl Vec3_Magnitude
    fmr f31, f1
    lfs f1, lbl_806D6EFC(r2)
    fcmpu cr0, f1, f31
    beq fn_80125B04_L_8012663C
    lfs f0, 0x8(r31)
    fcmpo cr0, f0, f1
    ble fn_80125B04_L_8012663C
    lfs f0, 0x48(r31)
    addi r3, r1, 0x50
    mr r4, r3
    stfs f0, 0x44(r1)
    lfs f0, 0x58(r31)
    stfs f0, 0x48(r1)
    lfs f0, 0x68(r31)
    stfs f0, 0x4c(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x44
    mr r4, r3
    bl Vec3_Normalize
    addi r3, r1, 0x50
    addi r4, r1, 0x44
    addi r5, r1, 0x38
    bl PSVECCrossProduct
    lfs f1, 0x38(r1)
    lfs f0, 0x3c(r1)
    lfs f2, 0x40(r1)
    fadds f0, f1, f0
    fadds f1, f2, f0
    bl asin
    frsp f1, f1
    lfs f0, lbl_806D6F84(r2)
    fmuls f29, f0, f1
    fn_80125B04_L_8012663C:
    lfs f0, lbl_806D6F88(r2)
    fmr f1, f29
    lwz r3, 0x38(r31)
    li r4, 0x0
    fmuls f2, f0, f31
    bl RenderObj_ItemStateMachine_Timed
    bl GetDisplayBufferIndex
    mr r4, r3
    lwz r3, 0x3c(r31)
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
    lwz r3, 0x74(r31)
    bl fn_8016EC80
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
    beq fn_80125B04_L_801266F4
    li r3, 0xf
    fn_80125B04_L_801266F4:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    psq_l f30, 0xa8(r1), 0, 0
    lfd f30, 0xa0(r1)
    psq_l f29, 0x98(r1), 0, 0
    lfd f29, 0x90(r1)
    lwz r31, 0x8c(r1)
    lwz r30, 0x88(r1)
    lwz r0, 0xc4(r1)
    lwz r29, 0x84(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

asm void fn_80126728(void) { /* 0x80126728 size:0x150 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq fn_80126728_L_8012685C
    lis r4, lbl_8048E258@ha
    li r3, 0x0
    addi r0, r4, lbl_8048E258@l
    li r4, 0x0
    stw r0, 0x0(r30)
    bl SetActiveCamera
    lwz r3, 0x10(r30)
    cmpwi r3, 0x0
    blt fn_80126728_L_80126770
    bl TransparentDraw_RemoveByOwner
    fn_80126728_L_80126770:
    li r3, 0x0
    bl SetPlayerCarObject
    li r3, 0x0
    bl SetCourseScene3D
    lwz r3, 0xc(r30)
    cmplwi r3, 0x0
    beq fn_80126728_L_801267A0
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80126728_L_801267A0:
    lwz r3, 0x14(r30)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x18(r30)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x1c(r30)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x3c(r30)
    li r4, 0x1
    bl VisualEffectHolder_Dtor
    lwz r3, 0x38(r30)
    li r4, 0x1
    bl KartDriver_Dtor
    lwz r3, 0x74(r30)
    li r4, 0x1
    bl fn_8016EFA8
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl ClRomTable_PurgeAll
    bl SceneDrawList_Reset
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    beq fn_80126728_L_80126818
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80126728_L_80126818:
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D10AC(r13)
    bl SetResourceLoadingFlag
    bl clRom_PurgeAll
    cmplwi r30, 0x0
    beq fn_80126728_L_8012684C
    lis r4, lbl_80419F0C@ha
    mr r3, r30
    addi r0, r4, lbl_80419F0C@l
    li r4, 0x0
    stw r0, 0x0(r30)
    bl dtor_8002CDF4
    fn_80126728_L_8012684C:
    extsh. r0, r31
    ble fn_80126728_L_8012685C
    mr r3, r30
    bl MemoryManager_TimedFree
    fn_80126728_L_8012685C:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void fn_80126878(void) { /* 0x80126878 size:0x44C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r4, lbl_80355A58@ha
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    addi r31, r4, lbl_80355A58@l
    stw r30, 0x18(r1)
    mr r30, r3
    mr r0, r30
    stw r29, 0x14(r1)
    mr r29, r0
    stw r28, 0x10(r1)
    bl GameMode_BaseInit
    lis r4, lbl_80419F0C@ha
    lis r3, lbl_8048E258@ha
    addi r0, r4, lbl_80419F0C@l
    li r5, 0x1
    stw r0, 0x0(r29)
    addi r0, r3, lbl_8048E258@l
    lfs f0, lbl_806D6EFC(r2)
    li r4, 0x0
    stw r0, 0x0(r30)
    li r0, -0x1
    addi r3, r30, 0x40
    stb r5, 0x4(r30)
    stfs f0, 0x8(r30)
    stw r4, 0xc(r30)
    stw r0, 0x10(r30)
    stw r4, 0x14(r30)
    stw r4, 0x18(r30)
    stw r4, 0x20(r30)
    stw r4, 0x1c(r30)
    stw r4, 0x24(r30)
    stw r4, 0x28(r30)
    stw r4, 0x2c(r30)
    stw r4, 0x30(r30)
    stw r4, 0x34(r30)
    stw r4, 0x38(r30)
    stw r4, 0x3c(r30)
    stw r4, 0x70(r30)
    bl PSMTXIdentity
    li r0, 0x0
    lfs f0, lbl_806D6EFC(r2)
    stw r0, 0x74(r30)
    li r3, 0x0
    stw r0, 0x78(r30)
    stw r0, 0x7c(r30)
    stw r0, 0x80(r30)
    stw r0, 0x84(r30)
    stw r0, 0x88(r30)
    stfs f0, 0x8c(r30)
    stfs f0, 0x90(r30)
    bl SetResourceLoadingFlag
    bl DrawManager_GetOrCreate
    bl DMAChannelManager_Init
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    li r3, 0x3090
    bl Alloc
    mr. r29, r3
    beq fn_80126878_L_80126994
    lwz r4, lbl_806CF4B8(r13)
    bl Scene3D_Init
    lis r3, lbl_80419EF8@ha
    lfs f1, lbl_806D6F14(r2)
    addi r0, r3, lbl_80419EF8@l
    lfs f0, lbl_806D6EFC(r2)
    stw r0, 0x0(r29)
    stfs f1, 0x3088(r29)
    stfs f0, 0x308c(r29)
    fn_80126878_L_80126994:
    stw r29, 0xc(r30)
    lwz r29, 0xc(r30)
    lwz r0, 0x4(r29)
    cmplwi r0, 0x0
    beq fn_80126878_L_80126A1C
    li r0, 0x1
    lfs f1, lbl_806D6EFC(r2)
    stb r0, 0x3084(r29)
    lfs f0, lbl_806D6F00(r2)
    stfs f1, 0x308c(r29)
    stfs f0, 0x3088(r29)
    lwz r3, 0x2c(r29)
    cmplwi r3, 0x0
    bne fn_80126878_L_801269D4
    li r4, 0x0
    b fn_80126878_L_80126A00
    fn_80126878_L_801269D4:
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne fn_80126878_L_801269E8
    li r4, 0x0
    b fn_80126878_L_80126A00
    fn_80126878_L_801269E8:
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne fn_80126878_L_801269FC
    li r4, 0x0
    b fn_80126878_L_80126A00
    fn_80126878_L_801269FC:
    lwz r4, 0x0(r3)
    fn_80126878_L_80126A00:
    lwz r3, 0x4(r29)
    bl HSD_CObjAddAnim
    lwz r3, 0x4(r29)
    lfs f1, 0x308c(r29)
    bl HSD_CObjReqAnim
    lwz r3, 0x4(r29)
    bl HSD_CObjAnim
    fn_80126878_L_80126A1C:
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq fn_80126878_L_80126A38
    lwz r4, lbl_806CF4B8(r13)
    li r5, 0x0
    bl clNormal3D_Construct
    fn_80126878_L_80126A38:
    lfs f1, lbl_806D6EFC(r2)
    li r4, 0x0
    stw r29, 0x14(r30)
    fmr f3, f1
    lfs f2, lbl_806D6F00(r2)
    fmr f4, f1
    lwz r3, 0x14(r30)
    bl clNormal3D_SetScale
    li r3, 0x0
    bl ProcessSystemTick
    li r3, 0x384
    bl Alloc
    mr. r28, r3
    beq fn_80126878_L_80126A98
    lwz r29, g_characterId(r13)
    bl GetDisplayBufferIndex
    mr r4, r3
    mr r3, r28
    mr r5, r29
    addi r6, r30, 0x40
    li r7, 0x0
    li r8, 0x0
    li r9, 0x0
    bl KartDriver_New_Full
    fn_80126878_L_80126A98:
    stw r28, 0x38(r30)
    li r3, 0x154
    bl Alloc
    mr. r28, r3
    beq fn_80126878_L_80126ACC
    lfs f1, lbl_806D6EFC(r2)
    li r4, 0x0
    lwz r5, 0x38(r30)
    li r7, 0x0
    fmr f2, f1
    lwz r6, g_characterId(r13)
    fmr f3, f1
    bl TornadoEffect_Ctor
    fn_80126878_L_80126ACC:
    stw r28, 0x3c(r30)
    lwz r3, 0x14(r30)
    lwz r4, lbl_806CF4BC(r13)
    bl ResolveJointByName
    stw r3, 0x70(r30)
    lwz r0, g_characterId(r13)
    cmpwi r0, 0x4
    bne fn_80126878_L_80126B20
    li r3, 0x5c
    bl Alloc
    mr. r28, r3
    beq fn_80126878_L_80126B08
    addi r4, r31, 0x484
    li r5, 0x0
    bl clNormal3D_Construct
    fn_80126878_L_80126B08:
    stw r28, 0x18(r30)
    addi r4, r31, 0x498
    lwz r3, 0x18(r30)
    bl ResolveJointByName
    stw r3, 0x20(r30)
    b fn_80126878_L_80126B50
    fn_80126878_L_80126B20:
    li r3, 0x5c
    bl Alloc
    mr. r28, r3
    beq fn_80126878_L_80126B3C
    addi r4, r31, 0x4c0
    li r5, 0x0
    bl clNormal3D_Construct
    fn_80126878_L_80126B3C:
    stw r28, 0x18(r30)
    addi r4, r31, 0x4d0
    lwz r3, 0x18(r30)
    bl ResolveJointByName
    stw r3, 0x20(r30)
    fn_80126878_L_80126B50:
    lfs f1, lbl_806D6EFC(r2)
    li r4, 0x0
    lwz r3, 0x18(r30)
    fmr f3, f1
    lfs f2, lbl_806D6F00(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    li r3, 0x0
    bl ProcessSystemTick
    bl fn_801825FC
    li r3, 0x5c
    bl Alloc
    mr. r28, r3
    beq fn_80126878_L_80126B94
    addi r4, r31, 0x4f4
    li r5, 0x0
    bl clNormal3D_Construct
    fn_80126878_L_80126B94:
    stw r28, 0x1c(r30)
    bl fn_801825C8
    lfs f1, lbl_806D6EFC(r2)
    li r4, 0x0
    lwz r3, 0x1c(r30)
    fmr f3, f1
    lfs f2, lbl_806D6F00(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lwz r3, 0x1c(r30)
    addi r4, r31, 0x50c
    bl ResolveJointByName
    stw r3, 0x24(r30)
    addi r4, r31, 0x520
    lwz r3, 0x1c(r30)
    bl ResolveJointByName
    stw r3, 0x28(r30)
    addi r4, r31, 0x534
    lwz r3, 0x1c(r30)
    bl ResolveJointByName
    stw r3, 0x2c(r30)
    addi r4, r31, 0x548
    lwz r3, 0x1c(r30)
    bl ResolveJointByName
    stw r3, 0x30(r30)
    addi r4, r31, 0x558
    lwz r3, 0x1c(r30)
    bl ResolveJointByName
    stw r3, 0x34(r30)
    addi r4, r31, 0x568
    lwz r3, 0x14(r30)
    bl ResolveJointByName
    stw r3, 0x78(r30)
    addi r4, r31, 0x584
    lwz r3, 0x14(r30)
    bl ResolveJointByName
    stw r3, 0x7c(r30)
    addi r4, r31, 0x5a0
    lwz r3, 0x14(r30)
    bl ResolveJointByName
    stw r3, 0x80(r30)
    addi r4, r31, 0x5bc
    lwz r3, 0x14(r30)
    bl ResolveJointByName
    stw r3, 0x84(r30)
    addi r4, r31, 0x5dc
    lwz r3, 0x14(r30)
    bl ResolveJointByName
    stw r3, 0x88(r30)
    li r0, 0x0
    stw r0, g_raceCamera(r13)
    stb r0, g_lakituStartAnimDone(r13)
    lwz r3, 0xc(r30)
    bl SetCourseScene3D
    lwz r3, 0x14(r30)
    li r4, 0x4
    lwz r3, 0x24(r3)
    bl SceneDrawList_RegisterArchive
    stw r3, 0x10(r30)
    li r3, 0x898
    bl Alloc
    mr. r28, r3
    beq fn_80126878_L_80126C94
    bl fn_8016F010
    fn_80126878_L_80126C94:
    stw r28, 0x74(r30)
    li r3, 0x1
    bl SetResourceLoadingFlag
    lwz r0, 0x24(r1)
    mr r3, r30
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
