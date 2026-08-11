/* === extracted from auto_KartDriver_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Archive_GetRootJObj();
extern void ISESlot_Dtor();
extern void KartTireFX_Dtor();
extern void MemoryManager_TimedFree();
extern void Object_DtorWithGXSync();
extern void RaceSlot_SetDriverPtr();
extern void SceneRender_CmdA_8a9e8();
extern void dtor_80091284();
extern void fn_80173CC4();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceCamera;

/* --- function index (1 fns, .text 0x80045950..0x80045B50) ---
 * [  0] 0x80045950 size:0x200   global KartDriver_Dtor
 */

/* --- forward decls --- */
asm void KartDriver_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_Dtor[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_Dtor = {
    (void *)&KartDriver_Dtor, 0x00000200, (void *)extab_KartDriver_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_Dtor(void) { /* 0x80045950 size:0x200 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr. r28, r3
    beq KartDriver_Dtor_L_80045B2C
    lwz r31, g_raceCamera(r13)
    cmplwi r31, 0x0
    beq KartDriver_Dtor_L_800459A0
    lwz r3, 0x18(r28)
    cmplwi r3, 0x0
    beq KartDriver_Dtor_L_800459A0
    bl Archive_GetRootJObj
    mr r4, r3
    mr r3, r31
    bl SceneRender_CmdA_8a9e8
    KartDriver_Dtor_L_800459A0:
    lwz r3, 0x8(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x4(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x0(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0xc(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x10(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x14(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x29c(r28)
    li r4, 0x1
    bl fn_80173CC4
    lwz r3, 0x304(r28)
    li r4, 0x1
    bl dtor_80091284
    lwz r3, 0x18(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x30c(r28)
    li r4, 0x1
    bl KartTireFX_Dtor
    lwz r3, 0x32c(r28)
    bl MemoryManager_TimedFree
    lwz r3, 0x20(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x344(r28)
    bl MemoryManager_TimedFree
    lwz r3, 0x35c(r28)
    cmplwi r3, 0x0
    beq KartDriver_Dtor_L_80045A54
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    KartDriver_Dtor_L_80045A54:
    lwz r3, 0x360(r28)
    cmplwi r3, 0x0
    beq KartDriver_Dtor_L_80045A74
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    KartDriver_Dtor_L_80045A74:
    lwz r3, 0x378(r28)
    cmplwi r3, 0x0
    beq KartDriver_Dtor_L_80045A94
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    KartDriver_Dtor_L_80045A94:
    lwz r3, 0x380(r28)
    cmplwi r3, 0x0
    beq KartDriver_Dtor_L_80045AB4
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    KartDriver_Dtor_L_80045AB4:
    li r30, 0x0
    mr r31, r28
    KartDriver_Dtor_L_80045ABC:
    lwz r3, 0x2dc(r31)
    li r4, 0x1
    bl ISESlot_Dtor
    addi r30, r30, 0x1
    addi r31, r31, 0x4
    cmpwi r30, 0xa
    blt KartDriver_Dtor_L_80045ABC
    li r30, 0x0
    mr r31, r28
    KartDriver_Dtor_L_80045AE0:
    lwz r3, 0x24(r31)
    li r4, 0x1
    bl Object_DtorWithGXSync
    addi r30, r30, 0x1
    addi r31, r31, 0x4
    cmpwi r30, 0x31
    blt KartDriver_Dtor_L_80045AE0
    lwz r3, 0x1c(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    li r0, 0x0
    li r4, 0x0
    stw r0, 0x1c(r28)
    lwz r3, 0x248(r28)
    bl RaceSlot_SetDriverPtr
    extsh. r0, r29
    ble KartDriver_Dtor_L_80045B2C
    mr r3, r28
    bl MemoryManager_TimedFree
    KartDriver_Dtor_L_80045B2C:
    lwz r0, 0x24(r1)
    mr r3, r28
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

