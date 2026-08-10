/* === extracted from auto_clFlowKart_HandleCon_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GetCoinMilage();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void SetKartVariant();
extern void SetRumbleMode();
extern void SetScreenBrightness();
extern void fn_801B7C64();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_characterId;
extern unsigned int g_gameMode;
extern unsigned int g_pInputState;
extern unsigned int lbl_806DA13C;
extern unsigned int lbl_806DA140;
extern unsigned int lbl_806DA144;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_kartEnhancedUnlockThreshold[];
extern unsigned int g_playerData[];

/* --- function index (1 fns, .text 0x801D7B50..0x801D7CC4) ---
 * [  0] 0x801D7B50 size:0x174   global clFlowKart_HandleConfirm
 */

/* --- forward decls --- */
asm void clFlowKart_HandleConfirm(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowKart_HandleConfirm[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowKart_HandleConfirm = {
    (void *)&clFlowKart_HandleConfirm, 0x00000174, (void *)extab_clFlowKart_HandleConfirm
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowKart_HandleConfirm(void) { /* 0x801D7B50 size:0x174 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 0x8(r1)
    lwz r3, 0x8(r3)
    cmpwi r3, -0x1
    beq clFlowKart_HandleConfirm_L_801D7B78
    b clFlowKart_HandleConfirm_L_801D7CAC
    clFlowKart_HandleConfirm_L_801D7B78:
    lfs f1, 0x18(r31)
    lfs f0, lbl_806DA140(r2)
    fsubs f0, f1, f0
    stfs f0, 0x18(r31)
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne clFlowKart_HandleConfirm_L_801D7BA4
    li r3, 0x0
    clFlowKart_HandleConfirm_L_801D7BA4:
    lwz r0, 0x18(r3)
    cmpwi r0, 0x1
    beq clFlowKart_HandleConfirm_L_801D7BC0
    lfs f1, 0x18(r31)
    lfs f0, lbl_806DA13C(r2)
    fcmpo cr0, f1, f0
    bge clFlowKart_HandleConfirm_L_801D7CA0
    clFlowKart_HandleConfirm_L_801D7BC0:
    li r3, 0x0
    li r4, 0x1
    li r5, 0x1
    bl SetRumbleMode
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    bne clFlowKart_HandleConfirm_L_801D7BE8
    li r3, 0x0
    bl SetKartVariant
    b clFlowKart_HandleConfirm_L_801D7C24
    clFlowKart_HandleConfirm_L_801D7BE8:
    lis r3, g_playerData@ha
    lwz r30, g_characterId(r13)
    addi r3, r3, g_playerData@l
    bl GetCoinMilage
    lis r4, g_kartEnhancedUnlockThreshold@ha
    slwi r0, r30, 2
    addi r4, r4, g_kartEnhancedUnlockThreshold@l
    lwzx r0, r4, r0
    cmpw r3, r0
    blt clFlowKart_HandleConfirm_L_801D7C1C
    li r3, 0x3
    bl SetKartVariant
    b clFlowKart_HandleConfirm_L_801D7C24
    clFlowKart_HandleConfirm_L_801D7C1C:
    li r3, 0x2
    bl SetKartVariant
    clFlowKart_HandleConfirm_L_801D7C24:
    lwz r4, g_gameMode(r13)
    lis r3, g_playerData@ha
    addi r3, r3, g_playerData@l
    li r5, 0x0
    cmpwi r4, 0x2
    beq clFlowKart_HandleConfirm_L_801D7C60
    lbz r0, 0x19f(r3)
    cmplwi r0, 0x0
    bne clFlowKart_HandleConfirm_L_801D7C4C
    li r5, 0x1
    clFlowKart_HandleConfirm_L_801D7C4C:
    lbz r0, 0x19d(r3)
    cmplwi r0, 0x1
    bne clFlowKart_HandleConfirm_L_801D7C64
    li r5, 0x1
    b clFlowKart_HandleConfirm_L_801D7C64
    clFlowKart_HandleConfirm_L_801D7C60:
    li r5, 0x1
    clFlowKart_HandleConfirm_L_801D7C64:
    clrlwi. r0, r5, 24
    bne clFlowKart_HandleConfirm_L_801D7C8C
    cmpwi r4, 0x0
    bne clFlowKart_HandleConfirm_L_801D7C80
    li r0, 0x15
    stw r0, 0x8(r31)
    b clFlowKart_HandleConfirm_L_801D7C94
    clFlowKart_HandleConfirm_L_801D7C80:
    li r0, 0x17
    stw r0, 0x8(r31)
    b clFlowKart_HandleConfirm_L_801D7C94
    clFlowKart_HandleConfirm_L_801D7C8C:
    li r0, 0x13
    stw r0, 0x8(r31)
    clFlowKart_HandleConfirm_L_801D7C94:
    lfs f0, lbl_806DA144(r2)
    stfs f0, 0x18(r31)
    bl fn_801B7C64
    clFlowKart_HandleConfirm_L_801D7CA0:
    lfs f1, 0x18(r31)
    bl SetScreenBrightness
    lwz r3, 0x8(r31)
    clFlowKart_HandleConfirm_L_801D7CAC:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


