/* === extracted from auto_ReverseChallenge_Dto_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ClRomTable_PurgeAll();
extern void CourseEnvironment_Dtor();
extern void GetRaceContextPtr();
extern void ItemObjectManager_Reset();
extern void LakituStart_Dtor();
extern void MemoryManager_TimedFree();
extern void RankingTable_Init();
extern void SceneDrawList_Reset();
extern void SetActiveCamera();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void VfxSlotMgr_Shutdown();
extern void clRom_PurgeAll();
extern void dtor_80122FD8();
extern void fn_80124C84();
extern void fn_8016C634();
extern void fn_80254134();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceCamera;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D10D0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80419E70[];

/* --- function index (1 fns, .text 0x800ACD60..0x800ACFC0) ---
 * [  0] 0x800ACD60 size:0x260   global ReverseChallenge_Dtor
 */

/* --- forward decls --- */
asm void ReverseChallenge_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ReverseChallenge_Dtor[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ReverseChallenge_Dtor = {
    (void *)&ReverseChallenge_Dtor, 0x00000260, (void *)extab_ReverseChallenge_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ReverseChallenge_Dtor(void) { /* 0x800ACD60 size:0x260 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r4
    stw r30, 0x18(r1)
    mr. r30, r3
    stw r29, 0x14(r1)
    beq ReverseChallenge_Dtor_L_800ACFA0
    lis r3, lbl_80419E70@ha
    addi r0, r3, lbl_80419E70@l
    stw r0, 0x0(r30)
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq ReverseChallenge_Dtor_L_800ACDAC
    li r4, 0x1
    bl fn_8016C634
    li r0, 0x0
    stw r0, g_weatherSystem(r13)
    ReverseChallenge_Dtor_L_800ACDAC:
    li r3, 0x0
    li r4, 0x0
    bl SetActiveCamera
    lwz r3, 0x1c(r30)
    cmplwi r3, 0x0
    beq ReverseChallenge_Dtor_L_800ACDD8
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    ReverseChallenge_Dtor_L_800ACDD8:
    lwz r3, 0x18(r30)
    li r4, 0x1
    bl LakituStart_Dtor
    lwz r3, 0x20(r30)
    li r4, 0x1
    bl fn_80124C84
    li r3, 0x0
    bl SetPlayerCarObject
    lwz r3, 0x14(r30)
    cmplwi r3, 0x0
    beq ReverseChallenge_Dtor_L_800ACE18
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    ReverseChallenge_Dtor_L_800ACE18:
    li r0, 0x0
    stw r0, g_raceCamera(r13)
    lwz r3, 0xc(r30)
    cmplwi r3, 0x0
    beq ReverseChallenge_Dtor_L_800ACE44
    beq ReverseChallenge_Dtor_L_800ACE44
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    ReverseChallenge_Dtor_L_800ACE44:
    lwz r29, 0x10(r30)
    cmplwi r29, 0x0
    beq ReverseChallenge_Dtor_L_800ACEC0
    beq ReverseChallenge_Dtor_L_800ACEC0
    lis r3, 0x1
    lhz r4, 0x4(r29)
    subi r0, r3, 0x1
    clrlwi r0, r0, 16
    subf r0, r4, r0
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq ReverseChallenge_Dtor_L_800ACE78
    b ReverseChallenge_Dtor_L_800ACE88
    ReverseChallenge_Dtor_L_800ACE78:
    subi r3, r4, 0x1
    cntlzw r0, r4
    sth r3, 0x4(r29)
    extrwi r0, r0, 8, 19
    ReverseChallenge_Dtor_L_800ACE88:
    cmpwi r0, 0x0
    beq ReverseChallenge_Dtor_L_800ACEC0
    cmplwi r29, 0x0
    beq ReverseChallenge_Dtor_L_800ACEC0
    lwz r4, 0x0(r29)
    mr r3, r29
    lwz r12, 0x30(r4)
    mtctr r12
    bctrl
    lwz r4, 0x0(r29)
    mr r3, r29
    lwz r12, 0x34(r4)
    mtctr r12
    bctrl
    ReverseChallenge_Dtor_L_800ACEC0:
    lwz r3, 0x8(r30)
    li r4, 0x1
    bl CourseEnvironment_Dtor
    lwz r3, 0x24(r30)
    li r4, 0x1
    bl fn_80254134
    lwz r3, 0x28(r30)
    cmplwi r3, 0x0
    beq ReverseChallenge_Dtor_L_800ACEE8
    bl MemoryManager_TimedFree
    ReverseChallenge_Dtor_L_800ACEE8:
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl ClRomTable_PurgeAll
    bl GetRaceContextPtr
    bl RankingTable_Init
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    beq ReverseChallenge_Dtor_L_800ACF1C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    ReverseChallenge_Dtor_L_800ACF1C:
    li r0, 0x0
    stw r0, lbl_806D10D0(r13)
    bl SceneDrawList_Reset
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    beq ReverseChallenge_Dtor_L_800ACF48
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    ReverseChallenge_Dtor_L_800ACF48:
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D109C(r13)
    bl SetResourceLoadingFlag
    bl clRom_PurgeAll
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    beq ReverseChallenge_Dtor_L_800ACF7C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    ReverseChallenge_Dtor_L_800ACF7C:
    li r0, 0x0
    mr r3, r30
    stw r0, lbl_806D10AC(r13)
    li r4, 0x0
    bl dtor_80122FD8
    extsh. r0, r31
    ble ReverseChallenge_Dtor_L_800ACFA0
    mr r3, r30
    bl MemoryManager_TimedFree
    ReverseChallenge_Dtor_L_800ACFA0:
    lwz r0, 0x24(r1)
    mr r3, r30
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

