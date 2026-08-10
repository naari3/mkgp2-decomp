/* === extracted from auto_clFlowKart_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void KartDriver_Dtor();
extern void KartMovement_ResetOnGoal();
extern void RenderObj_ItemStateMachine_Timed();
extern void RumbleUpdate();
extern void SetScreenBrightness();
extern void Sprite_AdvanceAnim();
extern void Sprite_CreateWithParams();
extern void Sprite_Destroy();
extern void clFlowKart_HandleConfirm();
extern void clFlowKart_UpdateDisplay();
extern void fn_801699D8();
extern void fn_801B7CAC();
extern void fn_801B8398();
extern void fn_801B87D8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_characterId;
extern unsigned int g_pInputState;
extern unsigned int lbl_806D184C;
extern unsigned int lbl_806D184D;
extern unsigned int lbl_806DA13C;
extern unsigned int lbl_806DA148;
extern unsigned int lbl_806DA158;
extern unsigned int lbl_806DA15C;
extern unsigned int lbl_806DA160;
extern unsigned int lbl_806DA164;
extern unsigned int lbl_806DA168;
extern unsigned int lbl_806DA16C;
extern unsigned int lbl_806DA170;

/* --- function index (1 fns, .text 0x801D7E84..0x801D8284) ---
 * [  0] 0x801D7E84 size:0x400   global clFlowKart_Update
 */

/* --- forward decls --- */
asm void clFlowKart_Update(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; void *f11; unsigned int f12; void *f13; } extab_clFlowKart_Update = { 0x100A0000, 0x000000B8, 0x00000020, 0x000000F0, 0x00000028, 0x00000128, 0x00000030, 0x00000000, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x8A80001E, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowKart_Update = {
    (void *)&clFlowKart_Update, 0x00000400, (void *)&extab_clFlowKart_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowKart_Update(void) { /* 0x801D7E84 size:0x400 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 0x8(r1)
    bl RumbleUpdate
    lbz r0, 0x10(r31)
    cmplwi r0, 0x0
    beq clFlowKart_Update_L_801D7EC0
    lwz r3, 0xc(r31)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0xc(r31)
    stb r0, 0x10(r31)
    clFlowKart_Update_L_801D7EC0:
    lwz r3, 0x14(r31)
    addi r0, r3, 0x1
    stw r0, 0x14(r31)
    lwz r0, 0xc(r31)
    cmpwi r0, 0x2
    beq clFlowKart_Update_L_801D80E0
    bge clFlowKart_Update_L_801D7EEC
    cmpwi r0, 0x0
    beq clFlowKart_Update_L_801D7EFC
    bge clFlowKart_Update_L_801D7FF4
    b clFlowKart_Update_L_801D81B8
    clFlowKart_Update_L_801D7EEC:
    cmpwi r0, 0x4
    beq clFlowKart_Update_L_801D81B0
    bge clFlowKart_Update_L_801D81B8
    b clFlowKart_Update_L_801D8198
    clFlowKart_Update_L_801D7EFC:
    lwz r0, 0x14(r31)
    cmpwi r0, 0x1
    bne clFlowKart_Update_L_801D7FC4
    li r3, 0x30
    bl Alloc
    mr. r30, r3
    beq clFlowKart_Update_L_801D7F3C
    lfs f3, lbl_806DA15C(r2)
    li r4, 0x16a
    lfs f1, lbl_806DA148(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f2, lbl_806DA158(r2)
    fmr f6, f3
    lfs f5, lbl_806DA13C(r2)
    bl Sprite_CreateWithParams
    clFlowKart_Update_L_801D7F3C:
    stw r30, 0x68(r31)
    li r3, 0x30
    bl Alloc
    mr. r30, r3
    beq clFlowKart_Update_L_801D7F74
    lfs f3, lbl_806DA15C(r2)
    li r4, 0x9c
    lfs f1, lbl_806DA160(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f2, lbl_806DA164(r2)
    fmr f6, f3
    lfs f5, lbl_806DA168(r2)
    bl Sprite_CreateWithParams
    clFlowKart_Update_L_801D7F74:
    stw r30, 0x6c(r31)
    li r3, 0x30
    bl Alloc
    mr. r30, r3
    beq clFlowKart_Update_L_801D7FAC
    lfs f3, lbl_806DA15C(r2)
    li r4, 0x9c
    lfs f1, lbl_806DA16C(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f2, lbl_806DA164(r2)
    fmr f6, f3
    lfs f5, lbl_806DA13C(r2)
    bl Sprite_CreateWithParams
    clFlowKart_Update_L_801D7FAC:
    stw r30, 0x70(r31)
    mr r3, r31
    lwz r4, g_characterId(r13)
    bl clFlowKart_UpdateDisplay
    lfs f1, 0x18(r31)
    bl SetScreenBrightness
    clFlowKart_Update_L_801D7FC4:
    lwz r0, 0x14(r31)
    cmpwi r0, 0x1e
    ble clFlowKart_Update_L_801D81B8
    li r3, 0x0
    li r4, 0x1
    bl fn_801699D8
    li r3, 0x1
    li r0, 0x0
    stb r3, lbl_806D184C(r13)
    stb r0, lbl_806D184D(r13)
    stb r3, 0x10(r31)
    b clFlowKart_Update_L_801D81B8
    clFlowKart_Update_L_801D7FF4:
    lwz r4, g_pInputState(r13)
    lwz r5, 0x4(r31)
    cmplwi r4, 0x0
    bne clFlowKart_Update_L_801D800C
    li r0, 0x0
    b clFlowKart_Update_L_801D8010
    clFlowKart_Update_L_801D800C:
    mr r0, r4
    clFlowKart_Update_L_801D8010:
    cmplwi r0, 0x0
    beq clFlowKart_Update_L_801D8078
    cmplwi r4, 0x0
    bne clFlowKart_Update_L_801D8024
    li r4, 0x0
    clFlowKart_Update_L_801D8024:
    lwz r3, 0x4(r31)
    lwz r0, 0x14(r4)
    add r0, r3, r0
    stw r0, 0x4(r31)
    lwz r0, 0x4(r31)
    cmpwi r0, 0x1
    ble clFlowKart_Update_L_801D8048
    li r0, 0x1
    stw r0, 0x4(r31)
    clFlowKart_Update_L_801D8048:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    bge clFlowKart_Update_L_801D805C
    li r0, 0x0
    stw r0, 0x4(r31)
    clFlowKart_Update_L_801D805C:
    lwz r0, 0x4(r31)
    cmpw r5, r0
    beq clFlowKart_Update_L_801D806C
    bl fn_801B7CAC
    clFlowKart_Update_L_801D806C:
    lwz r4, g_characterId(r13)
    mr r3, r31
    bl clFlowKart_UpdateDisplay
    clFlowKart_Update_L_801D8078:
    mr r3, r31
    bl clFlowKart_HandleConfirm
    cmpwi r3, -0x1
    beq clFlowKart_Update_L_801D81B8
    li r3, 0x0
    li r0, 0x1
    stw r3, 0x14(r31)
    stb r0, 0x10(r31)
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x24(r3)
    bl KartMovement_ResetOnGoal
    bl fn_801B87D8
    li r0, -0x1
    li r4, 0x1
    stb r0, lbl_806D184C(r13)
    lwz r3, 0x6c(r31)
    bl Sprite_Destroy
    lwz r3, 0x70(r31)
    li r4, 0x1
    bl Sprite_Destroy
    li r0, 0x0
    stw r0, 0x6c(r31)
    stw r0, 0x70(r31)
    b clFlowKart_Update_L_801D81B8
    clFlowKart_Update_L_801D80E0:
    lwz r0, 0x14(r31)
    cmpwi r0, 0x32
    bne clFlowKart_Update_L_801D81B8
    bl fn_801B87D8
    li r3, 0x0
    bl fn_801B8398
    lwz r3, 0x24(r31)
    li r4, 0x1
    bl KartDriver_Dtor
    lwz r3, 0x28(r31)
    li r4, 0x1
    bl KartDriver_Dtor
    lwz r3, 0x68(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x6c(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x70(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x74(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x78(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x7c(r31)
    li r4, 0x1
    bl Sprite_Destroy
    li r5, 0x0
    li r0, 0x1
    stw r5, 0x24(r31)
    li r3, 0x0
    li r4, 0x0
    stw r5, 0x28(r31)
    stw r5, 0x68(r31)
    stw r5, 0x6c(r31)
    stw r5, 0x70(r31)
    stw r5, 0x14(r31)
    stw r5, 0x74(r31)
    stw r5, 0x78(r31)
    stw r5, 0x7c(r31)
    stb r0, 0x10(r31)
    bl fn_801699D8
    b clFlowKart_Update_L_801D81B8
    clFlowKart_Update_L_801D8198:
    lwz r0, 0x14(r31)
    cmpwi r0, 0x34
    bne clFlowKart_Update_L_801D81B8
    li r0, 0x1
    stb r0, 0x10(r31)
    b clFlowKart_Update_L_801D81B8
    clFlowKart_Update_L_801D81B0:
    lwz r3, 0x8(r31)
    b clFlowKart_Update_L_801D826C
    clFlowKart_Update_L_801D81B8:
    lwz r3, 0x68(r31)
    cmplwi r3, 0x0
    beq clFlowKart_Update_L_801D81CC
    lfs f1, lbl_806DA170(r2)
    bl Sprite_AdvanceAnim
    clFlowKart_Update_L_801D81CC:
    lwz r3, 0x6c(r31)
    cmplwi r3, 0x0
    beq clFlowKart_Update_L_801D81E0
    lfs f1, lbl_806DA170(r2)
    bl Sprite_AdvanceAnim
    clFlowKart_Update_L_801D81E0:
    lwz r3, 0x70(r31)
    cmplwi r3, 0x0
    beq clFlowKart_Update_L_801D81F4
    lfs f1, lbl_806DA170(r2)
    bl Sprite_AdvanceAnim
    clFlowKart_Update_L_801D81F4:
    lwz r3, 0x24(r31)
    cmplwi r3, 0x0
    beq clFlowKart_Update_L_801D8210
    lfs f1, lbl_806DA13C(r2)
    li r4, 0x0
    fmr f2, f1
    bl RenderObj_ItemStateMachine_Timed
    clFlowKart_Update_L_801D8210:
    lwz r3, 0x28(r31)
    cmplwi r3, 0x0
    beq clFlowKart_Update_L_801D822C
    lfs f1, lbl_806DA13C(r2)
    li r4, 0x0
    fmr f2, f1
    bl RenderObj_ItemStateMachine_Timed
    clFlowKart_Update_L_801D822C:
    lwz r3, 0x74(r31)
    cmplwi r3, 0x0
    beq clFlowKart_Update_L_801D8240
    lfs f1, lbl_806DA170(r2)
    bl Sprite_AdvanceAnim
    clFlowKart_Update_L_801D8240:
    lwz r3, 0x78(r31)
    cmplwi r3, 0x0
    beq clFlowKart_Update_L_801D8254
    lfs f1, lbl_806DA170(r2)
    bl Sprite_AdvanceAnim
    clFlowKart_Update_L_801D8254:
    lwz r3, 0x7c(r31)
    cmplwi r3, 0x0
    beq clFlowKart_Update_L_801D8268
    lfs f1, lbl_806DA170(r2)
    bl Sprite_AdvanceAnim
    clFlowKart_Update_L_801D8268:
    li r3, -0x1
    clFlowKart_Update_L_801D826C:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

