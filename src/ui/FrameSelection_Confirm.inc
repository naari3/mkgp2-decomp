/* === extracted from auto_FrameSelection_Confi_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void DrawNamCamImage();
extern void GX_BeginDraw();
extern void GX_EndDraw();
extern void GX_ResetVertex();
extern void GetDisplayBufferIndex();
extern void GetDisplayContext();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void PlaySoundDSP();
extern void SetRumbleMode();
extern void SoundMgr_Play();
extern void Sprite_AdvanceAnim();
extern void Sprite_Destroy();
extern void Sprite_InitWithAnim();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_CURSOR_LEFT_X;
extern unsigned int FLOAT_CURSOR_RIGHT_X;
extern unsigned int FLOAT_CURSOR_Y;
extern unsigned int FLOAT_DELTA_TIME;
extern unsigned int FLOAT_NAMCAM_BOTTOM;
extern unsigned int FLOAT_NAMCAM_LEFT;
extern unsigned int FLOAT_NAMCAM_RIGHT;
extern unsigned int FLOAT_NAMCAM_TOP;
extern unsigned int g_confirmFlag;
extern unsigned int g_consecutiveWinsTier;
extern unsigned int g_gameMode;
extern unsigned int g_namCamFlag;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80598A60[];

/* --- function index (1 fns, .text 0x801C53A0..0x801C569C) ---
 * [  0] 0x801C53A0 size:0x2FC   global FrameSelection_Confirm
 */

/* --- forward decls --- */
asm void FrameSelection_Confirm(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; void *f9; } extab_FrameSelection_Confirm = { 0x180A0000, 0x00000064, 0x00000018, 0x00000088, 0x00000020, 0x00000000, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_FrameSelection_Confirm = {
    (void *)&FrameSelection_Confirm, 0x000002FC, (void *)&extab_FrameSelection_Confirm
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void FrameSelection_Confirm(void) { /* 0x801C53A0 size:0x2FC */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    stw r30, 0x48(r1)
    mr r30, r3
    stw r29, 0x44(r1)
    lwz r3, 0x2c(r3)
    cmpwi r3, -0x1
    beq FrameSelection_Confirm_L_801C53CC
    b FrameSelection_Confirm_L_801C5680
    FrameSelection_Confirm_L_801C53CC:
    lwz r3, 0x1c(r30)
    addi r0, r3, 0x1
    stw r0, 0x1c(r30)
    lwz r0, 0x1c(r30)
    cmpwi r0, 0x168
    bne FrameSelection_Confirm_L_801C5450
    li r3, 0x30
    bl Alloc
    mr. r29, r3
    beq FrameSelection_Confirm_L_801C5404
    li r4, 0x5b
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    FrameSelection_Confirm_L_801C5404:
    stw r29, 0x48(r30)
    li r3, 0x30
    bl Alloc
    mr. r29, r3
    beq FrameSelection_Confirm_L_801C5428
    li r4, 0x5b
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    FrameSelection_Confirm_L_801C5428:
    stw r29, 0x4c(r30)
    lfs f0, FLOAT_CURSOR_LEFT_X(r2)
    lwz r3, 0x48(r30)
    lfs f1, FLOAT_CURSOR_Y(r2)
    stfs f0, 0xc(r3)
    lfs f0, FLOAT_CURSOR_RIGHT_X(r2)
    stfs f1, 0x10(r3)
    lwz r3, 0x4c(r30)
    stfs f0, 0xc(r3)
    stfs f1, 0x10(r3)
    FrameSelection_Confirm_L_801C5450:
    lwz r0, 0x1c(r30)
    cmpwi r0, 0x1e0
    bne FrameSelection_Confirm_L_801C5464
    li r3, 0x276
    bl PlaySoundDSP
    FrameSelection_Confirm_L_801C5464:
    lwz r0, 0x1c(r30)
    cmpwi r0, 0x21c
    bne FrameSelection_Confirm_L_801C5478
    li r3, 0x277
    bl PlaySoundDSP
    FrameSelection_Confirm_L_801C5478:
    lwz r0, 0x1c(r30)
    cmpwi r0, 0x258
    bne FrameSelection_Confirm_L_801C548C
    li r3, 0x278
    bl PlaySoundDSP
    FrameSelection_Confirm_L_801C548C:
    li r29, 0x0
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r0, 0x48(r30)
    mr r31, r3
    cmplwi r0, 0x0
    beq FrameSelection_Confirm_L_801C54C4
    lfs f1, FLOAT_DELTA_TIME(r2)
    mr r3, r0
    bl Sprite_AdvanceAnim
    clrlwi. r0, r3, 24
    bne FrameSelection_Confirm_L_801C54C4
    li r29, 0x1
    FrameSelection_Confirm_L_801C54C4:
    lwz r3, 0xac(r30)
    lbz r0, 0x1(r3)
    cmplwi r0, 0x0
    beq FrameSelection_Confirm_L_801C54F8
    mr r3, r31
    li r4, 0x2000
    lwz r12, 0x0(r31)
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl
    cmplwi r3, 0x0
    beq FrameSelection_Confirm_L_801C54F8
    li r29, 0x1
    FrameSelection_Confirm_L_801C54F8:
    lwz r3, 0x4c(r30)
    cmplwi r3, 0x0
    beq FrameSelection_Confirm_L_801C550C
    lfs f1, FLOAT_DELTA_TIME(r2)
    bl Sprite_AdvanceAnim
    FrameSelection_Confirm_L_801C550C:
    clrlwi. r0, r29, 24
    beq FrameSelection_Confirm_L_801C567C
    li r3, 0x0
    li r4, 0x1
    li r5, 0x1
    bl SetRumbleMode
    lwz r3, 0x48(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x4c(r30)
    li r4, 0x1
    bl Sprite_Destroy
    li r0, 0x0
    stw r0, 0x48(r30)
    stw r0, 0x4c(r30)
    lwz r3, 0xac(r30)
    lbz r0, 0x1(r3)
    cmplwi r0, 0x0
    beq FrameSelection_Confirm_L_801C563C
    bl GX_BeginDraw
    bl GX_ResetVertex
    lis r3, lbl_80598A60@ha
    addi r3, r3, lbl_80598A60@l
    lwz r31, 0x4c(r3)
    lwz r29, 0x48(r3)
    bl GetDisplayBufferIndex
    bl GetDisplayContext
    lfs f0, FLOAT_NAMCAM_BOTTOM(r2)
    li r9, 0x80
    lfs f2, FLOAT_NAMCAM_LEFT(r2)
    li r10, 0x4
    fctiwz f3, f0
    lfs f1, FLOAT_NAMCAM_TOP(r2)
    lfs f0, FLOAT_NAMCAM_RIGHT(r2)
    fctiwz f2, f2
    fctiwz f1, f1
    li r5, 0x140
    stfd f3, 0x18(r1)
    fctiwz f0, f0
    li r6, 0xf0
    li r7, 0x6
    lwz r0, 0x1c(r1)
    stfd f2, 0x20(r1)
    subf r4, r29, r0
    subi r0, r4, 0xa
    stfd f1, 0x28(r1)
    clrlwi r0, r0, 16
    lwz r4, 0x24(r1)
    stw r0, 0x8(r1)
    lwz r0, 0x2c(r1)
    subf r4, r31, r4
    stw r9, 0xc(r1)
    subi r8, r4, 0x7
    subf r4, r29, r0
    stw r9, 0x10(r1)
    subi r0, r4, 0xa
    clrlwi r8, r8, 16
    stfd f0, 0x30(r1)
    clrlwi r9, r0, 16
    stw r10, 0x14(r1)
    lwz r0, 0x34(r1)
    lwz r10, 0xac(r30)
    subf r4, r31, r0
    subi r0, r4, 0x7
    lwz r4, 0x4(r10)
    clrlwi r10, r0, 16
    bl DrawNamCamImage
    li r3, 0x0
    bl GX_EndDraw
    li r0, 0x1
    li r3, 0x16
    stb r0, 0x19(r30)
    bl SoundMgr_Play
    li r0, 0x1
    stb r0, g_namCamFlag(r13)
    stb r0, g_confirmFlag(r13)
    FrameSelection_Confirm_L_801C563C:
    lwz r3, g_gameMode(r13)
    lwz r0, 0x4(r30)
    cmpwi r3, 0x0
    stw r0, g_consecutiveWinsTier(r13)
    bne FrameSelection_Confirm_L_801C565C
    li r0, 0x15
    stw r0, 0x2c(r30)
    b FrameSelection_Confirm_L_801C566C
    FrameSelection_Confirm_L_801C565C:
    cmpwi r3, 0x1
    bne FrameSelection_Confirm_L_801C566C
    li r0, 0x17
    stw r0, 0x2c(r30)
    FrameSelection_Confirm_L_801C566C:
    li r0, 0x50
    li r3, -0x1
    stw r0, 0x24(r30)
    b FrameSelection_Confirm_L_801C5680
    FrameSelection_Confirm_L_801C567C:
    lwz r3, 0x2c(r30)
    FrameSelection_Confirm_L_801C5680:
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    lwz r29, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}
