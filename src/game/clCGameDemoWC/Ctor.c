/* === extracted from auto_clCGameDemoWC_Ctor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void GameMode_BaseInit();
extern void GetDisplayBufferIndex();
extern void ItemObjectManager_Init();
extern void KartDriver_New_Full();
extern void MTXIdentity();
extern void ProcessSystemTick();
extern void ResolveJointByName();
extern void Scene3D_Init();
extern void SceneDrawList_RegisterArchive();
extern void SetCourseScene3D();
extern void SetResourceLoadingFlag();
extern void SoundChannels_ClearAll();
extern void TornadoEffect_Ctor();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();
extern void fn_801967F0();
extern void fn_802C6430();
extern void fn_802C65F0();
extern void fn_802C6640();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_characterId;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceCamera;
extern unsigned int lbl_806CF2C8;
extern unsigned int lbl_806CF2CC;
extern unsigned int lbl_806D4F94;
extern unsigned int lbl_806D4F98;
extern unsigned int lbl_806D4FA8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80419ED8[];
extern unsigned int lbl_80419EF8[];
extern unsigned int lbl_80419F0C[];

/* --- function index (1 fns, .text 0x800AE438..0x800AE6BC) ---
 * [  0] 0x800AE438 size:0x284   global clCGameDemoWC_Ctor
 */

/* --- forward decls --- */
asm void clCGameDemoWC_Ctor(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void clCGameDemo_Dtor();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; void *f25; unsigned int f26; unsigned int f27; void *f28; unsigned int f29; void *f30; unsigned int f31; unsigned int f32; void *f33; unsigned int f34; void *f35; unsigned int f36; unsigned int f37; void *f38; unsigned int f39; void *f40; unsigned int f41; unsigned int f42; void *f43; unsigned int f44; void *f45; unsigned int f46; unsigned int f47; void *f48; } extab_clCGameDemoWC_Ctor = { 0x180A0000, 0x00000078, 0x00090068, 0x000000AC, 0x00000060, 0x0000013C, 0x00070068, 0x0000016C, 0x00000074, 0x0000018C, 0x00040068, 0x000001AC, 0x00080088, 0x000001D8, 0x00000068, 0x00000200, 0x0000009C, 0x00000210, 0x00050068, 0x00000230, 0x000000B0, 0x00000248, 0x00070068, 0x00000000, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&clCGameDemo_Dtor, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&clCGameDemo_Dtor };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clCGameDemoWC_Ctor = {
    (void *)&clCGameDemoWC_Ctor, 0x00000284, (void *)&extab_clCGameDemoWC_Ctor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clCGameDemoWC_Ctor(void) { /* 0x800AE438 size:0x284 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    mr r0, r31
    stw r30, 0x18(r1)
    mr r30, r0
    stw r29, 0x14(r1)
    bl GameMode_BaseInit
    lis r4, lbl_80419F0C@ha
    lis r3, lbl_80419ED8@ha
    addi r0, r4, lbl_80419F0C@l
    li r5, 0x1
    stw r0, 0x0(r30)
    addi r0, r3, lbl_80419ED8@l
    lfs f0, lbl_806D4F94(r2)
    li r4, 0x0
    stw r0, 0x0(r31)
    li r0, -0x1
    addi r3, r31, 0x20
    stb r5, 0x4(r31)
    stfs f0, 0x8(r31)
    stw r4, 0xc(r31)
    stw r0, 0x10(r31)
    stw r4, 0x14(r31)
    stw r4, 0x18(r31)
    stw r4, 0x1c(r31)
    stw r4, 0x50(r31)
    bl MTXIdentity
    li r3, 0x0
    bl SetResourceLoadingFlag
    bl DrawManager_GetOrCreate
    bl DMAChannelManager_Init
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    li r3, 0x3090
    bl Alloc
    mr. r30, r3
    beq clCGameDemoWC_Ctor_L_800AE500
    lwz r4, lbl_806CF2C8(r13)
    bl Scene3D_Init
    lis r3, lbl_80419EF8@ha
    lfs f1, lbl_806D4FA8(r2)
    addi r0, r3, lbl_80419EF8@l
    lfs f0, lbl_806D4F94(r2)
    stw r0, 0x0(r30)
    stfs f1, 0x3088(r30)
    stfs f0, 0x308c(r30)
    clCGameDemoWC_Ctor_L_800AE500:
    stw r30, 0xc(r31)
    lwz r30, 0xc(r31)
    lwz r0, 0x4(r30)
    cmplwi r0, 0x0
    beq clCGameDemoWC_Ctor_L_800AE588
    li r0, 0x1
    lfs f1, lbl_806D4F94(r2)
    stb r0, 0x3084(r30)
    lfs f0, lbl_806D4F98(r2)
    stfs f1, 0x308c(r30)
    stfs f0, 0x3088(r30)
    lwz r3, 0x2c(r30)
    cmplwi r3, 0x0
    bne clCGameDemoWC_Ctor_L_800AE540
    li r4, 0x0
    b clCGameDemoWC_Ctor_L_800AE56C
    clCGameDemoWC_Ctor_L_800AE540:
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne clCGameDemoWC_Ctor_L_800AE554
    li r4, 0x0
    b clCGameDemoWC_Ctor_L_800AE56C
    clCGameDemoWC_Ctor_L_800AE554:
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne clCGameDemoWC_Ctor_L_800AE568
    li r4, 0x0
    b clCGameDemoWC_Ctor_L_800AE56C
    clCGameDemoWC_Ctor_L_800AE568:
    lwz r4, 0x0(r3)
    clCGameDemoWC_Ctor_L_800AE56C:
    lwz r3, 0x4(r30)
    bl fn_802C6430
    lwz r3, 0x4(r30)
    lfs f1, 0x308c(r30)
    bl fn_802C6640
    lwz r3, 0x4(r30)
    bl fn_802C65F0
    clCGameDemoWC_Ctor_L_800AE588:
    li r3, 0x5c
    bl Alloc
    mr. r30, r3
    beq clCGameDemoWC_Ctor_L_800AE5A4
    lwz r4, lbl_806CF2C8(r13)
    li r5, 0x0
    bl clNormal3D_Construct
    clCGameDemoWC_Ctor_L_800AE5A4:
    lfs f1, lbl_806D4F94(r2)
    li r4, 0x0
    stw r30, 0x14(r31)
    fmr f3, f1
    lfs f2, lbl_806D4F98(r2)
    fmr f4, f1
    lwz r3, 0x14(r31)
    bl clNormal3D_SetScale
    li r3, 0x0
    bl ProcessSystemTick
    li r3, 0x384
    bl Alloc
    mr. r29, r3
    beq clCGameDemoWC_Ctor_L_800AE604
    lwz r30, g_characterId(r13)
    bl GetDisplayBufferIndex
    mr r4, r3
    mr r3, r29
    mr r5, r30
    addi r6, r31, 0x20
    li r7, 0x0
    li r8, 0x0
    li r9, 0x0
    bl KartDriver_New_Full
    clCGameDemoWC_Ctor_L_800AE604:
    stw r29, 0x18(r31)
    li r3, 0x154
    bl Alloc
    mr. r29, r3
    beq clCGameDemoWC_Ctor_L_800AE638
    lfs f1, lbl_806D4F94(r2)
    li r4, 0x0
    lwz r5, 0x18(r31)
    li r7, 0x0
    fmr f2, f1
    lwz r6, g_characterId(r13)
    fmr f3, f1
    bl TornadoEffect_Ctor
    clCGameDemoWC_Ctor_L_800AE638:
    stw r29, 0x1c(r31)
    lwz r3, 0x14(r31)
    lwz r4, lbl_806CF2CC(r13)
    bl ResolveJointByName
    stw r3, 0x50(r31)
    li r0, 0x0
    li r3, 0x24
    stw r0, 0x54(r31)
    bl Alloc
    mr. r29, r3
    beq clCGameDemoWC_Ctor_L_800AE668
    bl fn_801967F0
    clCGameDemoWC_Ctor_L_800AE668:
    stw r29, 0x58(r31)
    li r0, 0x0
    stw r0, g_raceCamera(r13)
    stb r0, g_lakituStartAnimDone(r13)
    lwz r3, 0xc(r31)
    bl SetCourseScene3D
    lwz r3, 0x14(r31)
    li r4, 0x4
    lwz r3, 0x24(r3)
    bl SceneDrawList_RegisterArchive
    stw r3, 0x10(r31)
    li r3, 0x1
    bl SetResourceLoadingFlag
    lwz r0, 0x24(r1)
    mr r3, r31
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

