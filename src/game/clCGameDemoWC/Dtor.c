/* === extracted from auto_clCGameDemoWC_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
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

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10AC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80419ED8[];
extern unsigned int lbl_80419F0C[];

/* --- function index (1 fns, .text 0x800ADDAC..0x800ADEF8) ---
 * [  0] 0x800ADDAC size:0x14C   global clCGameDemoWC_Dtor
 */

/* --- forward decls --- */
asm void clCGameDemoWC_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clCGameDemoWC_Dtor[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clCGameDemoWC_Dtor = {
    (void *)&clCGameDemoWC_Dtor, 0x0000014C, (void *)extab_clCGameDemoWC_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clCGameDemoWC_Dtor(void) { /* 0x800ADDAC size:0x14C */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq clCGameDemoWC_Dtor_L_800ADEDC
    lis r4, lbl_80419ED8@ha
    li r3, 0x0
    addi r0, r4, lbl_80419ED8@l
    li r4, 0x0
    stw r0, 0x0(r30)
    bl SetActiveCamera
    lwz r3, 0x10(r30)
    cmpwi r3, 0x0
    blt clCGameDemoWC_Dtor_L_800ADDF4
    bl TransparentDraw_RemoveByOwner
    clCGameDemoWC_Dtor_L_800ADDF4:
    li r3, 0x0
    bl SetPlayerCarObject
    li r3, 0x0
    bl SetCourseScene3D
    lwz r3, 0xc(r30)
    cmplwi r3, 0x0
    beq clCGameDemoWC_Dtor_L_800ADE24
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    clCGameDemoWC_Dtor_L_800ADE24:
    lwz r3, 0x14(r30)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x58(r30)
    cmplwi r3, 0x0
    beq clCGameDemoWC_Dtor_L_800ADE50
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    clCGameDemoWC_Dtor_L_800ADE50:
    lwz r3, 0x1c(r30)
    li r4, 0x1
    bl VisualEffectHolder_Dtor
    lwz r3, 0x18(r30)
    li r4, 0x1
    bl KartDriver_Dtor
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl ClRomTable_PurgeAll
    bl SceneDrawList_Reset
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    beq clCGameDemoWC_Dtor_L_800ADE98
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    clCGameDemoWC_Dtor_L_800ADE98:
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D10AC(r13)
    bl SetResourceLoadingFlag
    bl clRom_PurgeAll
    cmplwi r30, 0x0
    beq clCGameDemoWC_Dtor_L_800ADECC
    lis r4, lbl_80419F0C@ha
    mr r3, r30
    addi r0, r4, lbl_80419F0C@l
    li r4, 0x0
    stw r0, 0x0(r30)
    bl dtor_8002CDF4
    clCGameDemoWC_Dtor_L_800ADECC:
    extsh. r0, r31
    ble clCGameDemoWC_Dtor_L_800ADEDC
    mr r3, r30
    bl MemoryManager_TimedFree
    clCGameDemoWC_Dtor_L_800ADEDC:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

