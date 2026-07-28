/* === extracted from auto_FrameSelection_Updat_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void FrameSelection_Confirm();
extern void GetVBlankFlag();
extern void IsSyncReached();
extern void NamCam_GetImageHandle();
extern void NamCam_LoadImage();
extern void PlayCursorMoveSE();
extern void ResetIOPorts();
extern void RumbleUpdate();
extern void SetSyncTarget();
extern void Sprite_AdvanceAnim();
extern void Sprite_SetAnimTime();
extern void StartScreenFade();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int DOUBLE_INT2FLOAT_MAGIC;
extern unsigned int FLOAT_ANIM_RESET;
extern unsigned int FLOAT_DELTA_TIME;
extern unsigned int FLOAT_DELTA_TIME_2X;
extern unsigned int FLOAT_FADE_OFFSET;
extern unsigned int FLOAT_FOCUSED_SCALE;
extern unsigned int FLOAT_TITLE_BASE_X;
extern unsigned int FLOAT_TITLE_POS_Y;
extern unsigned int FLOAT_TITLE_STEP_X;
extern unsigned int FLOAT_UNFOCUSED_ALPHA;
extern unsigned int FLOAT_UNFOCUSED_SCALE;
extern unsigned int g_pInputState;

/* --- function index (1 fns, .text 0x801C5890..0x801C5C34) ---
 * [  0] 0x801C5890 size:0x3A4   global FrameSelection_Update
 */

/* --- forward decls --- */
asm void FrameSelection_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_FrameSelection_Update[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_FrameSelection_Update = {
    (void *)&FrameSelection_Update, 0x000003A4, (void *)extab_FrameSelection_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void FrameSelection_Update(void) { /* 0x801C5890 size:0x3A4 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r3
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    bl RumbleUpdate
    lwz r0, 0x24(r31)
    cmpwi r0, 0x0
    beq FrameSelection_Update_L_801C5918
    lwz r3, 0x30(r31)
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    lwz r3, 0x34(r31)
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    lwz r3, 0xa8(r31)
    cmplwi r3, 0x0
    beq FrameSelection_Update_L_801C58E8
    lfs f1, FLOAT_DELTA_TIME_2X(r2)
    bl Sprite_AdvanceAnim
    FrameSelection_Update_L_801C58E8:
    lwz r3, 0x24(r31)
    subic. r0, r3, 0x1
    stw r0, 0x24(r31)
    bne FrameSelection_Update_L_801C5910
    li r0, 0x1
    lfs f1, FLOAT_FADE_OFFSET(r2)
    stb r0, 0xc(r31)
    bl StartScreenFade
    lwz r3, 0x2c(r31)
    b FrameSelection_Update_L_801C5C18
    FrameSelection_Update_L_801C5910:
    li r3, -0x1
    b FrameSelection_Update_L_801C5C18
    FrameSelection_Update_L_801C5918:
    lbz r0, 0xc(r31)
    cmplwi r0, 0x0
    beq FrameSelection_Update_L_801C5988
    lwz r3, 0x30(r31)
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    li r3, 0x14
    bl SetSyncTarget
    lwz r3, 0x28(r31)
    cmpwi r3, 0x0
    bne FrameSelection_Update_L_801C595C
    bl IsSyncReached
    clrlwi. r0, r3, 24
    beq FrameSelection_Update_L_801C5980
    li r0, 0x8
    stw r0, 0x28(r31)
    b FrameSelection_Update_L_801C5980
    FrameSelection_Update_L_801C595C:
    subic. r0, r3, 0x1
    stw r0, 0x28(r31)
    bgt FrameSelection_Update_L_801C5980
    lbz r0, 0x19(r31)
    cmplwi r0, 0x0
    beq FrameSelection_Update_L_801C5978
    bl ResetIOPorts
    FrameSelection_Update_L_801C5978:
    li r0, 0x19
    stw r0, 0x2c(r31)
    FrameSelection_Update_L_801C5980:
    lwz r3, 0x2c(r31)
    b FrameSelection_Update_L_801C5C18
    FrameSelection_Update_L_801C5988:
    lwz r3, 0x30(r31)
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    lwz r30, 0xac(r31)
    bl GetVBlankFlag
    clrlwi. r0, r3, 24
    beq FrameSelection_Update_L_801C59DC
    lbz r0, 0x0(r30)
    cmplwi r0, 0x0
    beq FrameSelection_Update_L_801C59DC
    addi r3, r1, 0x8
    li r4, 0x0
    bl NamCam_GetImageHandle
    cmpwi r3, 0x1
    bne FrameSelection_Update_L_801C59DC
    lwz r3, 0x8(r1)
    addi r5, r1, 0xc
    lwz r4, 0x4(r30)
    bl NamCam_LoadImage
    li r0, 0x1
    stb r0, 0x1(r30)
    FrameSelection_Update_L_801C59DC:
    lwz r4, g_pInputState(r13)
    cmplwi r4, 0x0
    bne FrameSelection_Update_L_801C59F0
    li r0, 0x0
    b FrameSelection_Update_L_801C59F4
    FrameSelection_Update_L_801C59F0:
    mr r0, r4
    FrameSelection_Update_L_801C59F4:
    cmplwi r0, 0x0
    beq FrameSelection_Update_L_801C5B50
    cmplwi r4, 0x0
    lwz r5, 0x4(r31)
    bne FrameSelection_Update_L_801C5A10
    li r3, 0x0
    b FrameSelection_Update_L_801C5A14
    FrameSelection_Update_L_801C5A10:
    mr r3, r4
    FrameSelection_Update_L_801C5A14:
    lwz r0, 0x14(r3)
    cmpwi r0, 0x0
    ble FrameSelection_Update_L_801C5A60
    li r0, 0xb
    li r4, 0x0
    mtctr r0
    FrameSelection_Update_L_801C5A2C:
    lwz r3, 0x4(r31)
    addi r0, r3, 0x1
    cmpwi r0, 0xb
    stw r0, 0x4(r31)
    blt FrameSelection_Update_L_801C5A44
    stw r4, 0x4(r31)
    FrameSelection_Update_L_801C5A44:
    lwz r3, 0x4(r31)
    addi r0, r3, 0xd
    lbzx r0, r31, r0
    cmplwi r0, 0x0
    bne FrameSelection_Update_L_801C5AB0
    bdnz FrameSelection_Update_L_801C5A2C
    b FrameSelection_Update_L_801C5AB0
    FrameSelection_Update_L_801C5A60:
    cmplwi r4, 0x0
    bne FrameSelection_Update_L_801C5A6C
    li r4, 0x0
    FrameSelection_Update_L_801C5A6C:
    lwz r0, 0x14(r4)
    cmpwi r0, 0x0
    bge FrameSelection_Update_L_801C5AB0
    li r0, 0xb
    li r4, 0xa
    mtctr r0
    FrameSelection_Update_L_801C5A84:
    lwz r3, 0x4(r31)
    subic. r0, r3, 0x1
    stw r0, 0x4(r31)
    bge FrameSelection_Update_L_801C5A98
    stw r4, 0x4(r31)
    FrameSelection_Update_L_801C5A98:
    lwz r3, 0x4(r31)
    addi r0, r3, 0xd
    lbzx r0, r31, r0
    cmplwi r0, 0x0
    bne FrameSelection_Update_L_801C5AB0
    bdnz FrameSelection_Update_L_801C5A84
    FrameSelection_Update_L_801C5AB0:
    lwz r0, 0x4(r31)
    cmpw r5, r0
    beq FrameSelection_Update_L_801C5B50
    slwi r3, r5, 2
    lis r0, 0x4330
    add r4, r31, r3
    lfs f1, FLOAT_UNFOCUSED_ALPHA(r2)
    lwz r3, 0x50(r4)
    lfs f0, FLOAT_UNFOCUSED_SCALE(r2)
    stfs f1, 0x20(r3)
    lfs f2, FLOAT_FOCUSED_SCALE(r2)
    lwz r3, 0x50(r4)
    stw r0, 0x18(r1)
    lfd f3, DOUBLE_INT2FLOAT_MAGIC(r2)
    stfs f0, 0x14(r3)
    lfs f4, FLOAT_TITLE_STEP_X(r2)
    stfs f0, 0x18(r3)
    lfs f1, FLOAT_TITLE_BASE_X(r2)
    lwz r0, 0x4(r31)
    lfs f0, FLOAT_TITLE_POS_Y(r2)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x50(r3)
    stfs f2, 0x20(r3)
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x50(r3)
    stfs f2, 0x14(r3)
    stfs f2, 0x18(r3)
    lwz r0, 0x4(r31)
    lwz r3, 0x34(r31)
    xoris r0, r0, 0x8000
    stw r0, 0x1c(r1)
    lfd f2, 0x18(r1)
    fsubs f2, f2, f3
    fmadds f1, f4, f2, f1
    stfs f1, 0xc(r3)
    stfs f0, 0x10(r3)
    bl PlayCursorMoveSE
    FrameSelection_Update_L_801C5B50:
    li r29, 0x0
    mr r30, r31
    FrameSelection_Update_L_801C5B58:
    lwz r3, 0x50(r30)
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    lwz r3, 0x7c(r30)
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    addi r29, r29, 0x1
    addi r30, r30, 0x4
    cmpwi r29, 0xb
    blt FrameSelection_Update_L_801C5B58
    lwz r3, 0x34(r31)
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    lwz r0, 0x20(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x40(r3)
    cmplwi r3, 0x0
    beq FrameSelection_Update_L_801C5BE8
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    clrlwi. r0, r3, 24
    bne FrameSelection_Update_L_801C5BE8
    lwz r3, 0x20(r31)
    lfs f1, FLOAT_ANIM_RESET(r2)
    addi r0, r3, 0x1
    srwi r3, r0, 31
    clrlwi r0, r0, 31
    xor r0, r0, r3
    subf r0, r3, r0
    stw r0, 0x20(r31)
    lwz r0, 0x20(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x40(r3)
    bl Sprite_SetAnimTime
    FrameSelection_Update_L_801C5BE8:
    lwz r3, 0x38(r31)
    cmplwi r3, 0x0
    beq FrameSelection_Update_L_801C5BFC
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    FrameSelection_Update_L_801C5BFC:
    lwz r3, 0x3c(r31)
    cmplwi r3, 0x0
    beq FrameSelection_Update_L_801C5C10
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    FrameSelection_Update_L_801C5C10:
    mr r3, r31
    bl FrameSelection_Confirm
    FrameSelection_Update_L_801C5C18:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
