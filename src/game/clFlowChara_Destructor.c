/* === extracted from auto_clFlowChara_Destruct_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void LObjList_Destroy();
extern void MemoryManager_TimedFree();
extern void Object_DtorWithGXSync();
extern void SetScreenBrightness();
extern void Sprite_Destroy();
extern void clRom_PurgeAll();
extern void dtor_801BA14C();
extern void fn_80120A08();
extern void fn_80169C44();
extern void fn_801A1678();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_BRIGHTNESS_DARK;
extern unsigned int g_pInputState;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8049AC7C[];

/* --- function index (1 fns, .text 0x801C4CA4..0x801C4EA8) ---
 * [  0] 0x801C4CA4 size:0x204   global clFlowChara_Destructor
 */

/* --- forward decls --- */
asm void clFlowChara_Destructor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowChara_Destructor[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowChara_Destructor = {
    (void *)&clFlowChara_Destructor, 0x00000204, (void *)extab_clFlowChara_Destructor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowChara_Destructor(void) { /* 0x801C4CA4 size:0x204 */
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
    beq clFlowChara_Destructor_L_801C4E84
    lis r3, lbl_8049AC7C@ha
    addi r0, r3, lbl_8049AC7C@l
    stw r0, 0x0(r28)
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne clFlowChara_Destructor_L_801C4CEC
    li r0, 0x0
    b clFlowChara_Destructor_L_801C4CF0
    clFlowChara_Destructor_L_801C4CEC:
    mr r0, r3
    clFlowChara_Destructor_L_801C4CF0:
    cmplwi r0, 0x0
    beq clFlowChara_Destructor_L_801C4D14
    cmplwi r3, 0x0
    bne clFlowChara_Destructor_L_801C4D04
    li r3, 0x0
    clFlowChara_Destructor_L_801C4D04:
    li r0, 0x0
    stb r0, 0x4(r3)
    stw r0, 0x18(r3)
    stw r0, 0x1c(r3)
    clFlowChara_Destructor_L_801C4D14:
    lfs f1, FLOAT_BRIGHTNESS_DARK(r2)
    bl SetScreenBrightness
    bl fn_80169C44
    lwz r3, 0x48(r28)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x4c(r28)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x50(r28)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x54(r28)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x58(r28)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x178(r28)
    cmplwi r3, 0x0
    beq clFlowChara_Destructor_L_801C4D6C
    bl MemoryManager_TimedFree
    clFlowChara_Destructor_L_801C4D6C:
    li r30, 0x0
    mr r31, r28
    clFlowChara_Destructor_L_801C4D74:
    lwz r3, 0xdc(r31)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x110(r31)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x144(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Destructor_L_801C4DAC
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    clFlowChara_Destructor_L_801C4DAC:
    addi r30, r30, 0x1
    addi r31, r31, 0x4
    cmpwi r30, 0xd
    blt clFlowChara_Destructor_L_801C4D74
    bl clRom_PurgeAll
    lwz r3, 0x70(r28)
    cmplwi r3, 0x0
    beq clFlowChara_Destructor_L_801C4DE0
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    clFlowChara_Destructor_L_801C4DE0:
    lwz r3, 0x74(r28)
    li r4, 0x1
    bl LObjList_Destroy
    li r0, 0x0
    li r3, 0x167f
    stw r0, 0x70(r28)
    stw r0, 0x74(r28)
    stb r0, 0x65(r28)
    bl fn_80120A08
    li r3, 0x169b
    bl fn_80120A08
    li r3, 0x16ac
    bl fn_80120A08
    li r3, 0x16ae
    bl fn_80120A08
    li r3, 0x16ad
    bl fn_80120A08
    li r3, 0x16af
    bl fn_80120A08
    li r3, 0x16a8
    bl fn_80120A08
    li r30, 0x0
    mr r31, r28
    clFlowChara_Destructor_L_801C4E3C:
    lwz r3, 0x14(r31)
    li r4, 0x1
    bl Sprite_Destroy
    addi r30, r30, 0x1
    addi r31, r31, 0x4
    cmpwi r30, 0xd
    blt clFlowChara_Destructor_L_801C4E3C
    lwz r3, 0x5c(r28)
    li r4, 0x1
    bl Sprite_Destroy
    bl fn_801A1678
    mr r3, r28
    li r4, 0x0
    bl dtor_801BA14C
    extsh. r0, r29
    ble clFlowChara_Destructor_L_801C4E84
    mr r3, r28
    bl MemoryManager_TimedFree
    clFlowChara_Destructor_L_801C4E84:
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
