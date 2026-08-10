/* === extracted from auto_BtMode_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AI_SystemDtor();
extern void ClRomTable_PurgeAll();
extern void CourseBgm_Free();
extern void CourseEnvironment_Dtor();
extern void GetRaceContextPtr();
extern void HitMessageOverlay_Destroy();
extern void ItemObjectManager_Reset();
extern void ItemSelect_Dtor();
extern void Jyugemu_Flag_Dtor();
extern void Jyugemu_ReverseFlag_Dtor();
extern void LakituStart_Dtor();
extern void LapBannerScene_Dtor();
extern void MemoryManager_TimedFree();
extern void PathParticipantArray_Dtor();
extern void ProcessSystemTick();
extern void RankingTable_Init();
extern void SceneDrawList_Reset();
extern void SetActiveCamera();
extern void SetCourseScene3D();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void Tachometer_Destroy();
extern void VfxSlotMgr_Shutdown();
extern void clRom_PurgeAll();
extern void fn_8013A6F8();
extern void fn_8016C634();
extern void fn_801B6B94();
extern void fn_80208FE4();
extern void fn_8020AF08();
extern void fn_80254134();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_courseData;
extern unsigned int g_currentSceneState;
extern unsigned int g_raceCamera;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10D0;
extern unsigned int lbl_806D129C;
extern unsigned int lbl_806D12F4;
extern unsigned int lbl_806D12F8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_carObjects[];
extern unsigned int g_itemSelects[];
extern unsigned int lbl_80320960[];
extern unsigned int lbl_8040E734[];
extern unsigned int lbl_8040E76C[];

/* --- function index (1 fns, .text 0x8009F47C..0x8009F814) ---
 * [  0] 0x8009F47C size:0x398   global BtMode_Dtor
 */

/* --- forward decls --- */
asm void BtMode_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BtMode_Dtor[8] = {
    0x30, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BtMode_Dtor = {
    (void *)&BtMode_Dtor, 0x00000398, (void *)extab_BtMode_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BtMode_Dtor(void) { /* 0x8009F47C size:0x398 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r26, 0x8(r1)
    mr. r29, r3
    lis r3, lbl_80320960@ha
    mr r30, r4
    addi r31, r3, lbl_80320960@l
    beq BtMode_Dtor_L_8009F7FC
    lis r3, lbl_8040E734@ha
    addi r0, r3, lbl_8040E734@l
    stw r0, 0x0(r29)
    bl fn_801B6B94
    lwz r0, g_currentSceneState(r13)
    li r3, 0x0
    stw r3, lbl_806D129C(r13)
    cmpwi r0, 0x2a
    beq BtMode_Dtor_L_8009F7D8
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq BtMode_Dtor_L_8009F4E0
    li r4, 0x1
    bl fn_8016C634
    li r0, 0x0
    stw r0, g_weatherSystem(r13)
    BtMode_Dtor_L_8009F4E0:
    li r3, 0x0
    li r4, 0x0
    bl SetActiveCamera
    lwz r3, 0x34(r29)
    cmplwi r3, 0x0
    beq BtMode_Dtor_L_8009F508
    li r4, 0x1
    bl fn_8020AF08
    li r0, 0x0
    stw r0, 0x34(r29)
    BtMode_Dtor_L_8009F508:
    addi r3, r31, 0x4e4
    bl ProcessSystemTick
    lwz r3, 0x2c(r29)
    li r4, 0x1
    bl AI_SystemDtor
    lwz r3, 0x30(r29)
    li r4, 0x1
    bl fn_80208FE4
    addi r3, r31, 0x4f4
    bl ProcessSystemTick
    lis r3, g_itemSelects@ha
    li r26, 0x0
    addi r27, r3, g_itemSelects@l
    li r28, 0x0
    BtMode_Dtor_L_8009F540:
    lwz r3, 0x0(r27)
    cmplwi r3, 0x0
    beq BtMode_Dtor_L_8009F554
    li r4, 0x1
    bl ItemSelect_Dtor
    BtMode_Dtor_L_8009F554:
    addi r26, r26, 0x1
    stw r28, 0x0(r27)
    cmpwi r26, 0x4
    addi r27, r27, 0x4
    blt BtMode_Dtor_L_8009F540
    bl Tachometer_Destroy
    bl HitMessageOverlay_Destroy
    addi r3, r31, 0x500
    bl ProcessSystemTick
    lwz r3, 0x24(r29)
    li r4, 0x1
    bl fn_80254134
    lwz r3, 0x18(r29)
    cmplwi r3, 0x0
    beq BtMode_Dtor_L_8009F5A4
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    BtMode_Dtor_L_8009F5A4:
    lwz r3, 0x4(r29)
    li r4, 0x1
    bl LakituStart_Dtor
    lwz r3, 0x8(r29)
    li r4, 0x1
    bl Jyugemu_Flag_Dtor
    lwz r3, 0xc(r29)
    li r4, 0x1
    bl Jyugemu_ReverseFlag_Dtor
    lwz r3, 0x10(r29)
    li r4, 0x1
    bl LapBannerScene_Dtor
    lwz r3, lbl_806D12F4(r13)
    li r4, 0x1
    bl PathParticipantArray_Dtor
    addi r3, r31, 0x524
    bl ProcessSystemTick
    lis r3, g_carObjects@ha
    li r26, 0x0
    addi r27, r3, g_carObjects@l
    li r28, 0x0
    BtMode_Dtor_L_8009F5F8:
    lwz r3, 0x0(r27)
    cmplwi r3, 0x0
    beq BtMode_Dtor_L_8009F61C
    beq BtMode_Dtor_L_8009F61C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    BtMode_Dtor_L_8009F61C:
    addi r26, r26, 0x1
    stw r28, 0x0(r27)
    cmpwi r26, 0x4
    addi r27, r27, 0x4
    blt BtMode_Dtor_L_8009F5F8
    lwz r3, 0x20(r29)
    cmplwi r3, 0x0
    beq BtMode_Dtor_L_8009F654
    beq BtMode_Dtor_L_8009F654
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    BtMode_Dtor_L_8009F654:
    lwz r3, 0x14(r29)
    li r4, 0x1
    bl CourseEnvironment_Dtor
    addi r3, r31, 0x548
    bl ProcessSystemTick
    lwz r27, lbl_806D12F8(r13)
    cmplwi r27, 0x0
    beq BtMode_Dtor_L_8009F6EC
    beq BtMode_Dtor_L_8009F6E4
    lis r3, 0x1
    lhz r4, 0x4(r27)
    subi r0, r3, 0x1
    clrlwi r0, r0, 16
    subf r0, r4, r0
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq BtMode_Dtor_L_8009F69C
    b BtMode_Dtor_L_8009F6AC
    BtMode_Dtor_L_8009F69C:
    subi r3, r4, 0x1
    cntlzw r0, r4
    sth r3, 0x4(r27)
    extrwi r0, r0, 8, 19
    BtMode_Dtor_L_8009F6AC:
    cmpwi r0, 0x0
    beq BtMode_Dtor_L_8009F6E4
    cmplwi r27, 0x0
    beq BtMode_Dtor_L_8009F6E4
    lwz r4, 0x0(r27)
    mr r3, r27
    lwz r12, 0x30(r4)
    mtctr r12
    bctrl
    lwz r4, 0x0(r27)
    mr r3, r27
    lwz r12, 0x34(r4)
    mtctr r12
    bctrl
    BtMode_Dtor_L_8009F6E4:
    li r0, 0x0
    stw r0, lbl_806D12F8(r13)
    BtMode_Dtor_L_8009F6EC:
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl GetRaceContextPtr
    bl RankingTable_Init
    bl ClRomTable_PurgeAll
    li r0, 0x0
    li r3, 0x0
    stw r0, 0x4(r29)
    stw r0, 0x8(r29)
    stw r0, 0xc(r29)
    stw r0, 0x10(r29)
    stw r0, lbl_806D12F4(r13)
    stw r0, 0x18(r29)
    stw r0, 0x14(r29)
    bl SetPlayerCarObject
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    beq BtMode_Dtor_L_8009F748
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    BtMode_Dtor_L_8009F748:
    li r0, 0x0
    stw r0, lbl_806D10D0(r13)
    bl fn_8013A6F8
    lwz r3, lbl_806D109C(r13)
    li r0, 0x0
    stw r0, g_raceCamera(r13)
    cmplwi r3, 0x0
    beq BtMode_Dtor_L_8009F77C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    BtMode_Dtor_L_8009F77C:
    li r0, 0x0
    stw r0, lbl_806D109C(r13)
    bl CourseBgm_Free
    bl SceneDrawList_Reset
    addi r3, r31, 0x55c
    bl ProcessSystemTick
    lwz r3, g_courseData(r13)
    cmplwi r3, 0x0
    beq BtMode_Dtor_L_8009F7B4
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    BtMode_Dtor_L_8009F7B4:
    li r0, 0x0
    li r3, 0x0
    stw r0, g_courseData(r13)
    bl SetResourceLoadingFlag
    bl clRom_PurgeAll
    li r3, 0x0
    bl SetCourseScene3D
    addi r3, r31, 0x578
    bl ProcessSystemTick
    BtMode_Dtor_L_8009F7D8:
    cmplwi r29, 0x0
    beq BtMode_Dtor_L_8009F7EC
    lis r3, lbl_8040E76C@ha
    addi r0, r3, lbl_8040E76C@l
    stw r0, 0x0(r29)
    BtMode_Dtor_L_8009F7EC:
    extsh. r0, r30
    ble BtMode_Dtor_L_8009F7FC
    mr r3, r29
    bl MemoryManager_TimedFree
    BtMode_Dtor_L_8009F7FC:
    mr r3, r29
    lmw r26, 0x8(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
