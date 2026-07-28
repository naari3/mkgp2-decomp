/* === extracted from auto_clFlowChara_HandleCo_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GetFrameIdxFromVisualIdx();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void SetKartVariant();
extern void SetRumbleMode();
extern void SetScreenBrightness();
extern void fn_801B7B64();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_BRIGHTNESS_DARK;
extern unsigned int FLOAT_SPRITE_INIT_TIME;
extern unsigned int g_characterId;
extern unsigned int g_gameMode;
extern unsigned int g_pInputState;
extern unsigned int lbl_806D9B90;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];

/* --- function index (1 fns, .text 0x801C393C..0x801C3AA4) ---
 * [  0] 0x801C393C size:0x168   global clFlowChara_HandleConfirm
 */

/* --- forward decls --- */
asm void clFlowChara_HandleConfirm(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowChara_HandleConfirm[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowChara_HandleConfirm = {
    (void *)&clFlowChara_HandleConfirm, 0x00000168, (void *)extab_clFlowChara_HandleConfirm
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowChara_HandleConfirm(void) { /* 0x801C393C size:0x168 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 0x8(r1)
    lwz r3, 0x60(r3)
    cmpwi r3, -0x1
    beq clFlowChara_HandleConfirm_L_801C3964
    b clFlowChara_HandleConfirm_L_801C3A8C
    clFlowChara_HandleConfirm_L_801C3964:
    lfs f1, 0x6c(r31)
    lfs f0, lbl_806D9B90(r2)
    fsubs f0, f1, f0
    stfs f0, 0x6c(r31)
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne clFlowChara_HandleConfirm_L_801C3990
    li r3, 0x0
    clFlowChara_HandleConfirm_L_801C3990:
    lwz r0, 0x18(r3)
    cmpwi r0, 0x1
    beq clFlowChara_HandleConfirm_L_801C39AC
    lfs f1, 0x6c(r31)
    lfs f0, FLOAT_SPRITE_INIT_TIME(r2)
    fcmpo cr0, f1, f0
    bge clFlowChara_HandleConfirm_L_801C3A80
    clFlowChara_HandleConfirm_L_801C39AC:
    li r3, 0x0
    li r4, 0x1
    li r5, 0x1
    bl SetRumbleMode
    lis r5, g_playerData@ha
    lwz r4, 0x4(r31)
    mr r3, r31
    addi r30, r5, g_playerData@l
    bl GetFrameIdxFromVisualIdx
    stw r3, g_characterId(r13)
    lwz r0, 0x68(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r0, 0xa8(r3)
    cmpwi r0, 0x1
    blt clFlowChara_HandleConfirm_L_801C3A00
    li r3, 0x2
    bl SetKartVariant
    li r0, 0xf
    stw r0, 0x60(r31)
    b clFlowChara_HandleConfirm_L_801C3A70
    clFlowChara_HandleConfirm_L_801C3A00:
    li r3, 0x0
    bl SetKartVariant
    lwz r3, g_gameMode(r13)
    li r4, 0x0
    cmpwi r3, 0x2
    beq clFlowChara_HandleConfirm_L_801C3A3C
    lbz r0, 0x19f(r30)
    cmplwi r0, 0x0
    bne clFlowChara_HandleConfirm_L_801C3A28
    li r4, 0x1
    clFlowChara_HandleConfirm_L_801C3A28:
    lbz r0, 0x19d(r30)
    cmplwi r0, 0x1
    bne clFlowChara_HandleConfirm_L_801C3A40
    li r4, 0x1
    b clFlowChara_HandleConfirm_L_801C3A40
    clFlowChara_HandleConfirm_L_801C3A3C:
    li r4, 0x1
    clFlowChara_HandleConfirm_L_801C3A40:
    clrlwi. r0, r4, 24
    bne clFlowChara_HandleConfirm_L_801C3A68
    cmpwi r3, 0x0
    bne clFlowChara_HandleConfirm_L_801C3A5C
    li r0, 0x15
    stw r0, 0x60(r31)
    b clFlowChara_HandleConfirm_L_801C3A70
    clFlowChara_HandleConfirm_L_801C3A5C:
    li r0, 0x17
    stw r0, 0x60(r31)
    b clFlowChara_HandleConfirm_L_801C3A70
    clFlowChara_HandleConfirm_L_801C3A68:
    li r0, 0x13
    stw r0, 0x60(r31)
    clFlowChara_HandleConfirm_L_801C3A70:
    lfs f0, FLOAT_BRIGHTNESS_DARK(r2)
    stfs f0, 0x6c(r31)
    lwz r3, g_characterId(r13)
    bl fn_801B7B64
    clFlowChara_HandleConfirm_L_801C3A80:
    lfs f1, 0x6c(r31)
    bl SetScreenBrightness
    lwz r3, 0x60(r31)
    clFlowChara_HandleConfirm_L_801C3A8C:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
