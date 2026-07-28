/* clFlowRound extab-backed unit.
 * Generated from the four target asm groups in address order; each body remains
 * inline asm until individually promoted to C.  Manual extab emits preserve the
 * target extab/extabindex layout for this combined TU.
 */

#ifdef __cplusplus
extern "C" {
#endif

/* === extracted from auto_clFlowRound_Draw_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GetCourseShortIdByCupAndMirror();
extern void fn_8011FAFC();
extern void fn_801A0004();
extern void fn_801A0DF0();
extern void fn_801A0FD4();
extern void fn_801A10DC();
extern void fn_801A1128();
extern void fn_801A1174();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_cupId;
extern unsigned int lbl_806D9D28;
extern unsigned int lbl_806D9D4C;
extern unsigned int lbl_806D9D50;
extern unsigned int lbl_806D9D54;
extern unsigned int lbl_806D9D58;
extern unsigned int lbl_806D9D5C;
extern unsigned int lbl_806D9D60;
extern unsigned int lbl_806D9D64;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8049AF8C[];
extern unsigned int lbl_8049AFA0[];

/* --- function index (1 fns, .text 0x801C9C28..0x801C9EAC) ---
 * [  0] 0x801C9C28 size:0x284   global clFlowRound_Draw
 */

/* --- forward decls --- */
asm void clFlowRound_Draw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowRound_Draw[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowRound_Draw = {
    (void *)&clFlowRound_Draw, 0x00000284, (void *)extab_clFlowRound_Draw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowRound_Draw(void) { /* 0x801C9C28 size:0x284 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    lwz r3, 0xf0(r3)
    cmplwi r3, 0x0
    beq clFlowRound_Draw_L_801C9C54
    bl fn_801A0004
    clFlowRound_Draw_L_801C9C54:
    lwz r3, 0x28(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Draw_L_801C9C64
    bl fn_801A0004
    clFlowRound_Draw_L_801C9C64:
    lwz r3, 0x88(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Draw_L_801C9C74
    bl fn_801A0004
    clFlowRound_Draw_L_801C9C74:
    lwz r3, 0xec(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Draw_L_801C9C84
    bl fn_801A0004
    clFlowRound_Draw_L_801C9C84:
    addi r3, r31, 0x94
    li r4, 0x5
    bl fn_8011FAFC
    addi r3, r31, 0xf4
    li r4, 0x5
    bl fn_8011FAFC
    lwz r5, g_cupId(r13)
    lis r3, lbl_8049AF8C@ha
    lwz r0, 0x4(r31)
    addi r4, r3, lbl_8049AF8C@l
    slwi r5, r5, 1
    addi r3, r13, -0x6F30  /* lbl_806CFDF0 */
    slwi r0, r0, 1
    lhax r30, r4, r5
    lhax r3, r3, r0
    li r4, 0x5
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    bl fn_801A1174
    lfs f1, lbl_806D9D4C(r2)
    lfs f2, lbl_806D9D50(r2)
    bl fn_801A1128
    lfs f1, lbl_806D9D28(r2)
    lfs f4, 0x158(r31)
    fmr f2, f1
    fmr f3, f1
    bl fn_801A0FD4
    bl fn_801A0DF0
    lis r3, lbl_8049AFA0@ha
    slwi r0, r30, 1
    addi r3, r3, lbl_8049AFA0@l
    li r4, 0x5
    lhax r3, r3, r0
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    bl fn_801A1174
    lfs f1, lbl_806D9D54(r2)
    lfs f2, lbl_806D9D58(r2)
    bl fn_801A1128
    lfs f1, lbl_806D9D28(r2)
    lfs f4, 0x150(r31)
    fmr f2, f1
    fmr f3, f1
    bl fn_801A0FD4
    bl fn_801A0DF0
    lwz r3, g_cupId(r13)
    lwz r4, 0x4(r31)
    bl GetCourseShortIdByCupAndMirror
    extsh r3, r3
    li r4, 0x5
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    bl fn_801A1174
    lfs f1, lbl_806D9D5C(r2)
    lfs f2, lbl_806D9D60(r2)
    bl fn_801A1128
    lfs f1, lbl_806D9D64(r2)
    fmr f2, f1
    bl fn_801A10DC
    lfs f1, lbl_806D9D28(r2)
    lfs f4, 0x154(r31)
    fmr f2, f1
    fmr f3, f1
    bl fn_801A0FD4
    bl fn_801A0DF0
    lwz r4, 0x4(r31)
    srwi r3, r4, 31
    clrlwi r0, r4, 31
    xor r0, r0, r3
    subf. r0, r3, r0
    bne clFlowRound_Draw_L_801C9DC8
    mulli r0, r4, 0x14
    add r3, r31, r0
    lwz r3, 0x3c(r3)
    cmplwi r3, 0x0
    beq clFlowRound_Draw_L_801C9DC8
    beq clFlowRound_Draw_L_801C9DC8
    bl fn_801A0004
    clFlowRound_Draw_L_801C9DC8:
    li r29, 0x0
    mr r30, r31
    clFlowRound_Draw_L_801C9DD0:
    lwz r0, 0x4(r31)
    cmpw r29, r0
    beq clFlowRound_Draw_L_801C9DF0
    lwz r3, 0x3c(r30)
    cmplwi r3, 0x0
    beq clFlowRound_Draw_L_801C9DF0
    beq clFlowRound_Draw_L_801C9DF0
    bl fn_801A0004
    clFlowRound_Draw_L_801C9DF0:
    addi r29, r29, 0x1
    addi r30, r30, 0x14
    cmpwi r29, 0x4
    blt clFlowRound_Draw_L_801C9DD0
    lwz r4, 0x4(r31)
    srwi r3, r4, 31
    clrlwi r0, r4, 31
    xor r0, r0, r3
    subf r0, r3, r0
    cmpwi r0, 0x1
    bne clFlowRound_Draw_L_801C9E38
    mulli r0, r4, 0x14
    add r3, r31, r0
    lwz r3, 0x3c(r3)
    cmplwi r3, 0x0
    beq clFlowRound_Draw_L_801C9E38
    beq clFlowRound_Draw_L_801C9E38
    bl fn_801A0004
    clFlowRound_Draw_L_801C9E38:
    lwz r3, 0x168(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Draw_L_801C9E58
    lbz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq clFlowRound_Draw_L_801C9E58
    lwz r3, 0x0(r3)
    bl fn_801A0004
    clFlowRound_Draw_L_801C9E58:
    lwz r3, 0x15c(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Draw_L_801C9E74
    lbz r0, 0x164(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Draw_L_801C9E74
    bl fn_801A0004
    clFlowRound_Draw_L_801C9E74:
    lwz r3, 0x160(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Draw_L_801C9E90
    lbz r0, 0x165(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Draw_L_801C9E90
    bl fn_801A0004
    clFlowRound_Draw_L_801C9E90:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

/* === extracted from auto_clFlowRound_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void IsItemSelectAllowed();
extern void RumbleUpdate();
extern void SetCourseParams();
extern void SetRumbleMode();
extern void SetScreenBrightness();
extern void Sprite_AdvanceAnim();
extern void Sprite_Destroy();
extern void Sprite_InitWithAnim();
extern void Sprite_SetAnimParam();
extern void Sprite_SetupAnim();
extern void fn_801699D8();
extern void fn_8019FF6C();
extern void fn_801A0550();
extern void fn_801B7C64();
extern void fn_801B7CAC();
extern void fn_801B8434();
extern void fn_801B87D8();
extern void fn_801BA060();
extern void fn_801C9288();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_cupId;
extern unsigned int g_pInputState;
extern unsigned int g_roundIndex;
extern unsigned int lbl_806D184C;
extern unsigned int lbl_806D184D;
extern unsigned int lbl_806D9D08;
extern unsigned int lbl_806D9D18;
extern unsigned int lbl_806D9D1C;
extern unsigned int lbl_806D9D20;
extern unsigned int lbl_806D9D24;
extern unsigned int lbl_806D9D28;
extern unsigned int lbl_806D9D30;
extern unsigned int lbl_806D9D38;
extern unsigned int lbl_806D9D44;
extern unsigned int lbl_806D9D48;
extern unsigned int lbl_806D9D68;
extern unsigned int lbl_806D9D6C;
extern unsigned int lbl_806D9D70;
extern unsigned int lbl_806D9D74;
extern unsigned int lbl_806D9D78;
extern unsigned int lbl_806D9D7C;
extern unsigned int lbl_806D9D80;
extern unsigned int lbl_806D9D84;
extern unsigned int lbl_806D9D88;
extern unsigned int lbl_806D9D8C;
extern unsigned int lbl_806D9D90;
extern unsigned int lbl_806D9D94;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8039B338[];
extern unsigned int lbl_8049AE70[];

/* --- function index (1 fns, .text 0x801C9EAC..0x801CADBC) ---
 * [  0] 0x801C9EAC size:0xF10   global clFlowRound_Update
 */

/* --- forward decls --- */
asm void clFlowRound_Update(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_clFlowRound_Update = { 0x488A0000, 0x00000CF4, 0x00000010, 0x00000000, 0x8A800017, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowRound_Update = {
    (void *)&clFlowRound_Update, 0x00000F10, (void *)&extab_clFlowRound_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowRound_Update(void) { /* 0x801C9EAC size:0xF10 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stfd f30, 0x40(r1)
    psq_st f30, 0x48(r1), 0, 0
    stmw r23, 0x1c(r1)
    lis r4, lbl_8049AE70@ha
    mr r31, r3
    addi r30, r4, lbl_8049AE70@l
    bl RumbleUpdate
    lbz r0, 0x20(r31)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801C9EFC
    lwz r3, 0x1c(r31)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0x1c(r31)
    stb r0, 0x20(r31)
    clFlowRound_Update_L_801C9EFC:
    lwz r3, 0x24(r31)
    addi r0, r3, 0x1
    stw r0, 0x24(r31)
    lwz r0, 0x1c(r31)
    cmpwi r0, 0x2
    beq clFlowRound_Update_L_801CA654
    bge clFlowRound_Update_L_801C9F28
    cmpwi r0, 0x0
    beq clFlowRound_Update_L_801C9F34
    bge clFlowRound_Update_L_801CA230
    b clFlowRound_Update_L_801CA914
    clFlowRound_Update_L_801C9F28:
    cmpwi r0, 0x4
    bge clFlowRound_Update_L_801CA914
    b clFlowRound_Update_L_801CA834
    clFlowRound_Update_L_801C9F34:
    lwz r0, 0x24(r31)
    cmpwi r0, 0xc
    bgt clFlowRound_Update_L_801C9FCC
    xoris r0, r0, 0x8000
    lis r3, 0x4330
    stw r0, 0xc(r1)
    li r0, 0x1
    lfd f1, lbl_806D9D30(r2)
    stw r3, 0x8(r1)
    lfs f4, lbl_806D9D1C(r2)
    lfd f0, 0x8(r1)
    lfs f3, lbl_806D9D20(r2)
    fsubs f0, f0, f1
    lfs f2, lbl_806D9D68(r2)
    stb r0, 0xa4(r31)
    lfs f1, lbl_806D9D6C(r2)
    fmuls f4, f4, f0
    lfs f0, lbl_806D9D28(r2)
    fdivs f3, f4, f3
    fsubs f2, f2, f3
    stfs f2, 0xa8(r31)
    stfs f1, 0xac(r31)
    stfs f0, 0xb0(r31)
    lwz r3, 0xf0(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801C9FA8
    lfs f0, lbl_806D9D70(r2)
    fadds f0, f0, f3
    stfs f0, 0xc(r3)
    clFlowRound_Update_L_801C9FA8:
    lfs f0, lbl_806D9D74(r2)
    li r0, 0x1
    stb r0, 0x104(r31)
    fadds f2, f0, f3
    lfs f1, lbl_806D9D78(r2)
    lfs f0, lbl_806D9D28(r2)
    stfs f2, 0x108(r31)
    stfs f1, 0x10c(r31)
    stfs f0, 0x110(r31)
    clFlowRound_Update_L_801C9FCC:
    lwz r3, 0x24(r31)
    cmpwi r3, 0x3
    blt clFlowRound_Update_L_801CA00C
    cmpwi r3, 0x8
    bgt clFlowRound_Update_L_801CA00C
    subi r3, r3, 0x3
    lis r0, 0x4330
    xoris r3, r3, 0x8000
    stw r0, 0x8(r1)
    lfd f2, lbl_806D9D30(r2)
    stw r3, 0xc(r1)
    lfs f0, lbl_806D9D7C(r2)
    lfd f1, 0x8(r1)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    stfs f0, 0x150(r31)
    clFlowRound_Update_L_801CA00C:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x14
    blt clFlowRound_Update_L_801CA05C
    cmpwi r0, 0x19
    bgt clFlowRound_Update_L_801CA05C
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lwz r3, 0x28(r31)
    stw r0, 0x8(r1)
    lfd f2, lbl_806D9D30(r2)
    cmplwi r3, 0x0
    lfd f0, 0x8(r1)
    lfs f1, lbl_806D9D80(r2)
    fsubs f2, f0, f2
    lfs f0, lbl_806D9D7C(r2)
    fsubs f1, f2, f1
    fdivs f0, f1, f0
    beq clFlowRound_Update_L_801CA05C
    stfs f0, 0x20(r3)
    clFlowRound_Update_L_801CA05C:
    lwz r3, 0x24(r31)
    cmpwi r3, 0x19
    blt clFlowRound_Update_L_801CA0A8
    subi r3, r3, 0x19
    lis r0, 0x4330
    xoris r3, r3, 0x8000
    lwz r4, 0xec(r31)
    stw r3, 0xc(r1)
    lfd f2, lbl_806D9D30(r2)
    cmplwi r4, 0x0
    stw r0, 0x8(r1)
    lfs f0, lbl_806D9D7C(r2)
    lfd f1, 0x8(r1)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    beq clFlowRound_Update_L_801CA0A0
    stfs f0, 0x20(r4)
    clFlowRound_Update_L_801CA0A0:
    stfs f0, 0x154(r31)
    stfs f0, 0x158(r31)
    clFlowRound_Update_L_801CA0A8:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x1e
    bne clFlowRound_Update_L_801CA914
    lwz r4, 0x4(r31)
    mr r3, r31
    li r5, 0x4
    bl fn_801C9288
    lfs f1, 0x90(r31)
    bl SetScreenBrightness
    li r5, 0x1
    li r0, 0x0
    stb r5, lbl_806D184C(r13)
    stb r0, lbl_806D184D(r13)
    stb r0, 0x164(r31)
    lwz r6, 0x15c(r31)
    cmplwi r6, 0x0
    beq clFlowRound_Update_L_801CA144
    lwz r0, 0x4(r31)
    lis r3, lbl_8039B338@ha
    addi r4, r3, lbl_8039B338@l
    lfd f1, lbl_806D9D08(r2)
    mulli r0, r0, 0x18
    lfsx f0, r4, r0
    add r3, r4, r0
    lfs f2, 0x4(r3)
    stfs f0, 0xc(r6)
    stfs f2, 0x10(r6)
    lwz r0, 0x4(r31)
    lwz r3, 0x15c(r31)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f0, 0x8(r4)
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x1c(r3)
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    beq clFlowRound_Update_L_801CA144
    stb r5, 0x164(r31)
    clFlowRound_Update_L_801CA144:
    li r0, 0x0
    stb r0, 0x165(r31)
    lwz r5, 0x160(r31)
    cmplwi r5, 0x0
    beq clFlowRound_Update_L_801CA1C4
    lwz r0, 0x4(r31)
    lis r3, lbl_8039B338@ha
    addi r4, r3, lbl_8039B338@l
    lfd f1, lbl_806D9D08(r2)
    mulli r0, r0, 0x18
    add r3, r4, r0
    lfs f0, 0xc(r3)
    lfs f2, 0x10(r3)
    stfs f0, 0xc(r5)
    stfs f2, 0x10(r5)
    lwz r0, 0x4(r31)
    lwz r3, 0x160(r31)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f0, 0x14(r4)
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x1c(r3)
    lwz r4, 0x4(r31)
    cmpwi r4, 0x3
    beq clFlowRound_Update_L_801CA1C4
    lwz r3, 0x8(r31)
    subi r0, r3, 0x1
    cmpw r4, r0
    bge clFlowRound_Update_L_801CA1C4
    li r0, 0x1
    stb r0, 0x165(r31)
    clFlowRound_Update_L_801CA1C4:
    li r0, 0x1
    li r3, 0x0
    stb r0, 0x8c(r31)
    li r4, 0x1
    stb r0, 0x20(r31)
    bl fn_801699D8
    lbz r0, 0x14c(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Update_L_801CA914
    lwz r0, 0x4(r31)
    cmpwi r0, 0x1
    bgt clFlowRound_Update_L_801CA914
    lwz r4, 0x168(r31)
    cmplwi r4, 0x0
    beq clFlowRound_Update_L_801CA914
    lbz r0, 0x4(r4)
    cmplwi r0, 0x1
    bne clFlowRound_Update_L_801CA218
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA914
    clFlowRound_Update_L_801CA218:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stb r0, 0x5(r4)
    stw r0, 0x8(r4)
    b clFlowRound_Update_L_801CA914
    clFlowRound_Update_L_801CA230:
    lwz r5, g_pInputState(r13)
    lwz r4, 0x4(r31)
    cmplwi r5, 0x0
    bne clFlowRound_Update_L_801CA248
    li r0, 0x0
    b clFlowRound_Update_L_801CA24C
    clFlowRound_Update_L_801CA248:
    mr r0, r5
    clFlowRound_Update_L_801CA24C:
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA29C
    cmplwi r5, 0x0
    bne clFlowRound_Update_L_801CA260
    li r5, 0x0
    clFlowRound_Update_L_801CA260:
    lwz r3, 0x4(r31)
    lwz r0, 0x14(r5)
    add r0, r3, r0
    stw r0, 0x4(r31)
    lwz r3, 0x8(r31)
    lwz r0, 0x4(r31)
    subi r3, r3, 0x1
    cmpw r0, r3
    ble clFlowRound_Update_L_801CA288
    stw r3, 0x4(r31)
    clFlowRound_Update_L_801CA288:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    bge clFlowRound_Update_L_801CA29C
    li r0, 0x0
    stw r0, 0x4(r31)
    clFlowRound_Update_L_801CA29C:
    lwz r0, 0x4(r31)
    cmpw r4, r0
    beq clFlowRound_Update_L_801CA4AC
    mr r3, r31
    li r5, 0x2
    bl fn_801C9288
    lwz r4, 0x4(r31)
    mr r3, r31
    li r5, 0x4
    bl fn_801C9288
    li r0, 0x0
    stb r0, 0x164(r31)
    lwz r5, 0x15c(r31)
    cmplwi r5, 0x0
    beq clFlowRound_Update_L_801CA334
    lwz r0, 0x4(r31)
    lis r3, lbl_8039B338@ha
    addi r4, r3, lbl_8039B338@l
    lfd f1, lbl_806D9D08(r2)
    mulli r0, r0, 0x18
    lfsx f0, r4, r0
    add r3, r4, r0
    lfs f2, 0x4(r3)
    stfs f0, 0xc(r5)
    stfs f2, 0x10(r5)
    lwz r0, 0x4(r31)
    lwz r3, 0x15c(r31)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f0, 0x8(r4)
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x1c(r3)
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    beq clFlowRound_Update_L_801CA334
    li r0, 0x1
    stb r0, 0x164(r31)
    clFlowRound_Update_L_801CA334:
    li r0, 0x0
    stb r0, 0x165(r31)
    lwz r5, 0x160(r31)
    cmplwi r5, 0x0
    beq clFlowRound_Update_L_801CA3B4
    lwz r0, 0x4(r31)
    lis r3, lbl_8039B338@ha
    addi r4, r3, lbl_8039B338@l
    lfd f1, lbl_806D9D08(r2)
    mulli r0, r0, 0x18
    add r3, r4, r0
    lfs f0, 0xc(r3)
    lfs f2, 0x10(r3)
    stfs f0, 0xc(r5)
    stfs f2, 0x10(r5)
    lwz r0, 0x4(r31)
    lwz r3, 0x160(r31)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f0, 0x14(r4)
    fmul f0, f1, f0
    frsp f0, f0
    stfs f0, 0x1c(r3)
    lwz r4, 0x4(r31)
    cmpwi r4, 0x3
    beq clFlowRound_Update_L_801CA3B4
    lwz r3, 0x8(r31)
    subi r0, r3, 0x1
    cmpw r4, r0
    bge clFlowRound_Update_L_801CA3B4
    li r0, 0x1
    stb r0, 0x165(r31)
    clFlowRound_Update_L_801CA3B4:
    lwz r0, 0x88(r31)
    lwz r3, 0x4(r31)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA424
    lwz r0, 0x80(r31)
    cmpwi r0, 0x1
    bne clFlowRound_Update_L_801CA424
    stw r3, 0x84(r31)
    li r4, 0x1bf
    li r5, 0x0
    li r6, 0x0
    lwz r3, 0x88(r31)
    bl Sprite_SetupAnim
    lwz r0, g_cupId(r13)
    addi r6, r30, 0x11c
    addi r5, r30, 0x108
    lwz r3, 0x88(r31)
    slwi r0, r0, 1
    li r4, 0x1970
    lhax r0, r6, r0
    slwi r0, r0, 1
    lhax r5, r5, r0
    bl Sprite_SetAnimParam
    lwz r3, 0x88(r31)
    bl fn_801A0550
    lwz r3, 0x88(r31)
    li r4, 0x1
    bl fn_8019FF6C
    clFlowRound_Update_L_801CA424:
    bl fn_801B7CAC
    lwz r4, 0x168(r31)
    cmplwi r4, 0x0
    beq clFlowRound_Update_L_801CA4AC
    lbz r0, 0x14c(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Update_L_801CA484
    lwz r0, 0x4(r31)
    cmpwi r0, 0x1
    bgt clFlowRound_Update_L_801CA484
    lbz r0, 0x4(r4)
    cmplwi r0, 0x0
    bne clFlowRound_Update_L_801CA4AC
    cmplwi r0, 0x1
    bne clFlowRound_Update_L_801CA46C
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA4AC
    clFlowRound_Update_L_801CA46C:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stb r0, 0x5(r4)
    stw r0, 0x8(r4)
    b clFlowRound_Update_L_801CA4AC
    clFlowRound_Update_L_801CA484:
    lbz r0, 0x4(r4)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA4AC
    lbz r0, 0x5(r4)
    cmplwi r0, 0x1
    beq clFlowRound_Update_L_801CA4AC
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x5(r4)
    stw r0, 0x8(r4)
    clFlowRound_Update_L_801CA4AC:
    lwz r0, 0x7c(r31)
    cmpwi r0, -0x1
    beq clFlowRound_Update_L_801CA4BC
    b clFlowRound_Update_L_801CA5D8
    clFlowRound_Update_L_801CA4BC:
    lfs f1, 0x90(r31)
    lfs f0, lbl_806D9D44(r2)
    fsubs f0, f1, f0
    stfs f0, 0x90(r31)
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r4, g_pInputState(r13)
    cmplwi r4, 0x0
    bne clFlowRound_Update_L_801CA4EC
    li r3, 0x0
    b clFlowRound_Update_L_801CA4F0
    clFlowRound_Update_L_801CA4EC:
    mr r3, r4
    clFlowRound_Update_L_801CA4F0:
    lwz r0, 0x18(r3)
    cmpwi r0, 0x1
    beq clFlowRound_Update_L_801CA50C
    lfs f1, 0x90(r31)
    lfs f0, lbl_806D9D38(r2)
    fcmpo cr0, f1, f0
    bge clFlowRound_Update_L_801CA5CC
    clFlowRound_Update_L_801CA50C:
    cmplwi r4, 0x0
    bne clFlowRound_Update_L_801CA51C
    li r0, 0x0
    b clFlowRound_Update_L_801CA520
    clFlowRound_Update_L_801CA51C:
    mr r0, r4
    clFlowRound_Update_L_801CA520:
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA544
    cmplwi r4, 0x0
    bne clFlowRound_Update_L_801CA534
    li r4, 0x0
    clFlowRound_Update_L_801CA534:
    li r0, 0x0
    stb r0, 0x4(r4)
    stw r0, 0x18(r4)
    stw r0, 0x1c(r4)
    clFlowRound_Update_L_801CA544:
    li r3, 0x0
    li r4, 0x1
    li r5, 0x1
    bl SetRumbleMode
    lbz r0, 0x14c(r31)
    li r3, 0x0
    lwz r4, 0x4(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Update_L_801CA56C
    li r3, 0x4
    clFlowRound_Update_L_801CA56C:
    add r26, r4, r3
    mr r3, r26
    bl fn_801BA060
    stw r26, g_roundIndex(r13)
    mr r6, r3
    lwz r3, g_cupId(r13)
    lwz r4, 0x0(r6)
    lwz r5, 0x4(r6)
    lwz r6, 0x8(r6)
    bl SetCourseParams
    bl IsItemSelectAllowed
    clrlwi. r0, r3, 24
    beq clFlowRound_Update_L_801CA5AC
    li r0, 0x21
    stw r0, 0x7c(r31)
    b clFlowRound_Update_L_801CA5B4
    clFlowRound_Update_L_801CA5AC:
    li r0, 0x25
    stw r0, 0x7c(r31)
    clFlowRound_Update_L_801CA5B4:
    lfs f0, lbl_806D9D48(r2)
    stfs f0, 0x90(r31)
    bl fn_801B7C64
    li r0, 0x0
    stb r0, 0x164(r31)
    stb r0, 0x165(r31)
    clFlowRound_Update_L_801CA5CC:
    lfs f1, 0x90(r31)
    bl SetScreenBrightness
    lwz r0, 0x7c(r31)
    clFlowRound_Update_L_801CA5D8:
    cmpwi r0, -0x1
    beq clFlowRound_Update_L_801CA914
    li r24, 0x0
    clFlowRound_Update_L_801CA5E4:
    lwz r0, 0x4(r31)
    cmpw r24, r0
    bne clFlowRound_Update_L_801CA604
    mr r3, r31
    mr r4, r24
    li r5, 0x5
    bl fn_801C9288
    b clFlowRound_Update_L_801CA614
    clFlowRound_Update_L_801CA604:
    mr r3, r31
    mr r4, r24
    li r5, 0x3
    bl fn_801C9288
    clFlowRound_Update_L_801CA614:
    addi r24, r24, 0x1
    cmpwi r24, 0x4
    blt clFlowRound_Update_L_801CA5E4
    lwz r3, 0x28(r31)
    li r4, 0x1
    bl Sprite_Destroy
    bl fn_801B87D8
    li r0, -0x1
    li r3, 0x0
    stb r0, lbl_806D184C(r13)
    li r0, 0x1
    stw r3, 0x28(r31)
    stw r3, 0x24(r31)
    stb r3, 0x8c(r31)
    stb r0, 0x20(r31)
    b clFlowRound_Update_L_801CA914
    clFlowRound_Update_L_801CA654:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x5
    bgt clFlowRound_Update_L_801CA6D8
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lwz r3, 0xec(r31)
    stw r0, 0x8(r1)
    lfd f2, lbl_806D9D30(r2)
    cmplwi r3, 0x0
    lfd f1, 0x8(r1)
    lfs f0, lbl_806D9D7C(r2)
    fsubs f1, f1, f2
    lfs f2, lbl_806D9D28(r2)
    fdivs f0, f1, f0
    fsubs f1, f2, f0
    beq clFlowRound_Update_L_801CA69C
    stfs f1, 0x20(r3)
    clFlowRound_Update_L_801CA69C:
    lwz r3, 0x28(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CA6AC
    stfs f1, 0x20(r3)
    clFlowRound_Update_L_801CA6AC:
    lfs f0, lbl_806D9D84(r2)
    li r3, -0x100
    fmuls f0, f0, f1
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r0, 0xc(r1)
    rlwimi r3, r0, 0, 24, 31
    stw r3, 0xc8(r31)
    stw r3, 0xcc(r31)
    stw r3, 0xd0(r31)
    stw r3, 0xd4(r31)
    clFlowRound_Update_L_801CA6D8:
    lwz r3, 0x24(r31)
    cmpwi r3, 0x28
    blt clFlowRound_Update_L_801CA740
    subi r3, r3, 0x28
    lis r0, 0x4330
    xoris r3, r3, 0x8000
    stw r0, 0x8(r1)
    lfd f2, lbl_806D9D30(r2)
    li r4, -0x100
    stw r3, 0xc(r1)
    lfs f0, lbl_806D9D7C(r2)
    lfd f1, 0x8(r1)
    lfs f3, lbl_806D9D28(r2)
    fsubs f1, f1, f2
    lfs f2, lbl_806D9D84(r2)
    fdivs f0, f1, f0
    fsubs f0, f3, f0
    fmuls f0, f2, f0
    fctiwz f0, f0
    stfd f0, 0x10(r1)
    lwz r0, 0x14(r1)
    rlwimi r4, r0, 0, 24, 31
    stw r4, 0x128(r31)
    stw r4, 0x12c(r31)
    stw r4, 0x130(r31)
    stw r4, 0x134(r31)
    clFlowRound_Update_L_801CA740:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x2d
    bne clFlowRound_Update_L_801CA914
    lwz r3, 0xf0(r31)
    li r4, 0xc7
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0xf0(r31)
    li r4, 0x1ad4
    li r5, 0x1ae4
    bl Sprite_SetAnimParam
    lwz r4, 0x4(r31)
    mr r3, r31
    li r5, 0x6
    bl fn_801C9288
    bl fn_801B8434
    lwz r0, 0x88(r31)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA7E8
    lwz r0, 0x80(r31)
    cmpwi r0, 0x1
    bne clFlowRound_Update_L_801CA7E8
    li r0, 0x2
    li r4, 0x83
    stw r0, 0x80(r31)
    li r5, 0x0
    li r6, 0x0
    lwz r3, 0x88(r31)
    bl Sprite_SetupAnim
    lwz r0, g_cupId(r13)
    addi r6, r30, 0x11c
    addi r5, r30, 0x108
    lwz r3, 0x88(r31)
    slwi r0, r0, 1
    li r4, 0x1970
    lhax r0, r6, r0
    slwi r0, r0, 1
    lhax r5, r5, r0
    bl Sprite_SetAnimParam
    lwz r3, 0x88(r31)
    bl fn_801A0550
    clFlowRound_Update_L_801CA7E8:
    li r4, 0x0
    li r3, 0x1
    stw r4, 0x24(r31)
    stb r3, 0x20(r31)
    lwz r5, 0x168(r31)
    cmplwi r5, 0x0
    beq clFlowRound_Update_L_801CA824
    lbz r0, 0x4(r5)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA824
    lbz r0, 0x5(r5)
    cmplwi r0, 0x1
    beq clFlowRound_Update_L_801CA824
    stb r3, 0x5(r5)
    stw r4, 0x8(r5)
    clFlowRound_Update_L_801CA824:
    li r3, 0x0
    li r4, 0x0
    bl fn_801699D8
    b clFlowRound_Update_L_801CA914
    clFlowRound_Update_L_801CA834:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x5
    bgt clFlowRound_Update_L_801CA870
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfd f2, lbl_806D9D30(r2)
    stw r0, 0x10(r1)
    lfs f0, lbl_806D9D7C(r2)
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D9D28(r2)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fsubs f0, f3, f0
    stfs f0, 0x154(r31)
    clFlowRound_Update_L_801CA870:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x6
    bgt clFlowRound_Update_L_801CA8AC
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfd f2, lbl_806D9D30(r2)
    stw r0, 0x10(r1)
    lfs f0, lbl_806D9D88(r2)
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D9D28(r2)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fsubs f0, f3, f0
    stfs f0, 0x150(r31)
    clFlowRound_Update_L_801CA8AC:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x7
    bgt clFlowRound_Update_L_801CA8E8
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfd f2, lbl_806D9D30(r2)
    stw r0, 0x10(r1)
    lfs f0, lbl_806D9D8C(r2)
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D9D28(r2)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fsubs f0, f3, f0
    stfs f0, 0x158(r31)
    clFlowRound_Update_L_801CA8E8:
    lwz r0, 0x24(r31)
    cmpwi r0, 0xf
    bne clFlowRound_Update_L_801CA900
    lfs f0, lbl_806D9D90(r2)
    lwz r3, 0xf0(r31)
    stfs f0, 0xc(r3)
    clFlowRound_Update_L_801CA900:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x2d
    bne clFlowRound_Update_L_801CA914
    lwz r3, 0x7c(r31)
    b clFlowRound_Update_L_801CAD98
    clFlowRound_Update_L_801CA914:
    lwz r4, 0x168(r31)
    cmplwi r4, 0x0
    beq clFlowRound_Update_L_801CA9D4
    lbz r0, 0x4(r4)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA9D4
    lwz r3, 0x8(r4)
    cmpwi r3, 0x8
    bgt clFlowRound_Update_L_801CA9C8
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    bne clFlowRound_Update_L_801CA96C
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfd f2, lbl_806D9D30(r2)
    stw r0, 0x10(r1)
    lfs f0, lbl_806D9D94(r2)
    lfd f1, 0x10(r1)
    fsubs f1, f1, f2
    fmuls f0, f1, f0
    b clFlowRound_Update_L_801CA994
    clFlowRound_Update_L_801CA96C:
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lfd f3, lbl_806D9D30(r2)
    stw r0, 0x8(r1)
    lfs f1, lbl_806D9D94(r2)
    lfd f2, 0x8(r1)
    lfs f0, lbl_806D9D28(r2)
    fsubs f2, f2, f3
    fnmsubs f0, f2, f1, f0
    clFlowRound_Update_L_801CA994:
    lwz r3, 0x0(r4)
    stfs f0, 0x20(r3)
    lwz r3, 0x8(r4)
    addi r0, r3, 0x1
    cmpwi r3, 0x8
    stw r0, 0x8(r4)
    bne clFlowRound_Update_L_801CA9C8
    lbz r0, 0x5(r4)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CA9C8
    li r0, 0x0
    stb r0, 0x4(r4)
    stb r0, 0x5(r4)
    clFlowRound_Update_L_801CA9C8:
    lwz r3, 0x0(r4)
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CA9D4:
    lwz r3, 0x15c(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CA9E8
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CA9E8:
    lwz r3, 0x160(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CA9FC
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CA9FC:
    lwz r3, 0xf0(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CAA10
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CAA10:
    lwz r3, 0xec(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CAA24
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CAA24:
    lwz r3, 0x28(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CAA38
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clFlowRound_Update_L_801CAA38:
    lfs f0, lbl_806D9D24(r2)
    mr r29, r31
    addi r28, r30, 0x0
    li r26, 0x0
    fneg f30, f0
    li r27, 0x0
    clFlowRound_Update_L_801CAA50:
    lwz r3, 0x3c(r29)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CACB0
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    beq clFlowRound_Update_L_801CACB0
    lwz r0, 0x2c(r29)
    cmpwi r0, 0x4
    beq clFlowRound_Update_L_801CACB0
    bge clFlowRound_Update_L_801CAA98
    cmpwi r0, 0x2
    beq clFlowRound_Update_L_801CACB0
    bge clFlowRound_Update_L_801CAC98
    cmpwi r0, 0x1
    bge clFlowRound_Update_L_801CAAA8
    b clFlowRound_Update_L_801CACB0
    clFlowRound_Update_L_801CAA98:
    cmpwi r0, 0x6
    beq clFlowRound_Update_L_801CAC98
    bge clFlowRound_Update_L_801CACB0
    b clFlowRound_Update_L_801CAB2C
    clFlowRound_Update_L_801CAAA8:
    lwz r0, 0x34(r29)
    cmpwi r0, 0x0
    bne clFlowRound_Update_L_801CACB0
    lwz r3, 0x38(r29)
    lis r0, 0x4330
    stw r0, 0x10(r1)
    addi r0, r3, 0x1
    lfd f2, lbl_806D9D30(r2)
    stw r0, 0x38(r29)
    lfs f4, lbl_806D9D1C(r2)
    lwz r0, 0x38(r29)
    lfs f1, 0x4(r28)
    xoris r0, r0, 0x8000
    lfs f0, lbl_806D9D20(r2)
    stw r0, 0x14(r1)
    fadds f3, f4, f1
    lwz r3, 0x3c(r29)
    lfd f1, 0x10(r1)
    fsubs f1, f1, f2
    fmuls f1, f4, f1
    fdivs f0, f1, f0
    fsubs f0, f3, f0
    stfs f0, 0xc(r3)
    lwz r0, 0x38(r29)
    cmpwi r0, 0xc
    blt clFlowRound_Update_L_801CACB0
    lwz r3, 0x34(r29)
    li r4, 0x1
    addi r0, r3, 0x1
    stw r0, 0x34(r29)
    lwz r3, 0x3c(r29)
    bl fn_8019FF6C
    b clFlowRound_Update_L_801CACB0
    clFlowRound_Update_L_801CAB2C:
    lwz r3, g_cupId(r13)
    addi r4, r30, 0x11c
    lwz r0, 0x30(r29)
    cmpwi r26, 0x2
    slwi r5, r3, 1
    addi r3, r30, 0xc0
    lhax r5, r4, r5
    slwi r0, r0, 2
    addi r4, r30, 0x30
    lfs f31, lbl_806D9D24(r2)
    slwi r5, r5, 4
    lwzx r25, r3, r0
    add r24, r5, r27
    add r24, r4, r24
    beq clFlowRound_Update_L_801CAB70
    cmpwi r26, 0x4
    bne clFlowRound_Update_L_801CAB74
    clFlowRound_Update_L_801CAB70:
    fmr f31, f30
    clFlowRound_Update_L_801CAB74:
    lwz r3, 0x3c(r29)
    cmplwi r3, 0x0
    bne clFlowRound_Update_L_801CABA8
    li r3, 0x30
    bl Alloc
    mr. r23, r3
    beq clFlowRound_Update_L_801CABA0
    mr r4, r25
    li r5, 0x0
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowRound_Update_L_801CABA0:
    stw r23, 0x3c(r29)
    b clFlowRound_Update_L_801CABB8
    clFlowRound_Update_L_801CABA8:
    mr r4, r25
    li r5, 0x0
    li r6, 0x0
    bl Sprite_SetupAnim
    clFlowRound_Update_L_801CABB8:
    lwz r0, 0x30(r29)
    cmpwi r0, 0x1
    beq clFlowRound_Update_L_801CAC04
    bge clFlowRound_Update_L_801CABD4
    cmpwi r0, 0x0
    bge clFlowRound_Update_L_801CABE0
    b clFlowRound_Update_L_801CAC48
    clFlowRound_Update_L_801CABD4:
    cmpwi r0, 0x3
    bge clFlowRound_Update_L_801CAC48
    b clFlowRound_Update_L_801CAC28
    clFlowRound_Update_L_801CABE0:
    lwz r3, 0x3c(r29)
    li r4, 0x1951
    lha r5, 0x0(r28)
    bl Sprite_SetAnimParam
    lwz r3, 0x3c(r29)
    li r4, 0x19b0
    lha r5, 0x2(r24)
    bl Sprite_SetAnimParam
    b clFlowRound_Update_L_801CAC48
    clFlowRound_Update_L_801CAC04:
    lwz r3, 0x3c(r29)
    li r4, 0x194c
    lha r5, 0x2(r28)
    bl Sprite_SetAnimParam
    lwz r3, 0x3c(r29)
    li r4, 0x19b0
    lha r5, 0x2(r24)
    bl Sprite_SetAnimParam
    b clFlowRound_Update_L_801CAC48
    clFlowRound_Update_L_801CAC28:
    lwz r3, 0x3c(r29)
    li r4, 0x194c
    lha r5, 0x2(r28)
    bl Sprite_SetAnimParam
    lwz r3, 0x3c(r29)
    li r4, 0x19b0
    lha r5, 0x2(r24)
    bl Sprite_SetAnimParam
    clFlowRound_Update_L_801CAC48:
    lwz r3, 0x3c(r29)
    li r4, 0x1a1e
    lha r5, 0x0(r24)
    bl Sprite_SetAnimParam
    lwz r3, 0x3c(r29)
    bl fn_801A0550
    lfs f0, 0x8(r28)
    li r4, 0x1
    lwz r3, 0x3c(r29)
    lfs f1, 0x4(r28)
    fadds f2, f0, f31
    lfs f0, lbl_806D9D28(r2)
    stfs f1, 0xc(r3)
    stfs f2, 0x10(r3)
    lwz r3, 0x3c(r29)
    stfs f0, 0x14(r3)
    stfs f0, 0x18(r3)
    lwz r3, 0x3c(r29)
    bl fn_8019FF6C
    b clFlowRound_Update_L_801CACB0
    clFlowRound_Update_L_801CAC98:
    lwz r3, 0x3c(r29)
    li r4, 0x1
    bl Sprite_Destroy
    li r0, 0x0
    stw r0, 0x2c(r29)
    stw r0, 0x3c(r29)
    clFlowRound_Update_L_801CACB0:
    addi r26, r26, 0x1
    addi r28, r28, 0xc
    cmpwi r26, 0x4
    addi r27, r27, 0x4
    addi r29, r29, 0x14
    blt clFlowRound_Update_L_801CAA50
    lwz r3, 0x88(r31)
    cmplwi r3, 0x0
    beq clFlowRound_Update_L_801CAD94
    lfs f1, lbl_806D9D18(r2)
    bl Sprite_AdvanceAnim
    clrlwi. r0, r3, 24
    bne clFlowRound_Update_L_801CAD94
    lwz r3, 0x80(r31)
    cmpwi r3, 0x0
    bne clFlowRound_Update_L_801CAD68
    addi r0, r3, 0x1
    stw r0, 0x80(r31)
    lwz r0, 0x88(r31)
    lwz r3, 0x84(r31)
    cmplwi r0, 0x0
    beq clFlowRound_Update_L_801CAD68
    lwz r0, 0x80(r31)
    cmpwi r0, 0x1
    bne clFlowRound_Update_L_801CAD68
    stw r3, 0x84(r31)
    li r4, 0x1bf
    li r5, 0x0
    li r6, 0x0
    lwz r3, 0x88(r31)
    bl Sprite_SetupAnim
    lwz r0, g_cupId(r13)
    addi r6, r30, 0x11c
    addi r5, r30, 0x108
    lwz r3, 0x88(r31)
    slwi r0, r0, 1
    li r4, 0x1970
    lhax r0, r6, r0
    slwi r0, r0, 1
    lhax r5, r5, r0
    bl Sprite_SetAnimParam
    lwz r3, 0x88(r31)
    bl fn_801A0550
    lwz r3, 0x88(r31)
    li r4, 0x1
    bl fn_8019FF6C
    clFlowRound_Update_L_801CAD68:
    lwz r0, 0x80(r31)
    cmpwi r0, 0x2
    bne clFlowRound_Update_L_801CAD94
    lwz r3, 0x88(r31)
    li r4, 0x1
    bl Sprite_Destroy
    li r0, 0x0
    stw r0, 0x88(r31)
    lwz r3, 0x80(r31)
    addi r0, r3, 0x1
    stw r0, 0x80(r31)
    clFlowRound_Update_L_801CAD94:
    li r3, -0x1
    clFlowRound_Update_L_801CAD98:
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    psq_l f30, 0x48(r1), 0, 0
    lfd f30, 0x40(r1)
    lmw r23, 0x1c(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}


/* === extracted from auto_clFlowRound_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree();
extern void SetScreenBrightness();
extern void Sprite_Destroy();
extern void dtor_801BA14C();
extern void fn_80120A08();
extern void fn_80169C44();
extern void fn_801A1678();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_cupId;
extern unsigned int g_pInputState;
extern unsigned int lbl_806CFDF0;
extern unsigned int lbl_806D9D48;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8049AE70[];

/* --- function index (1 fns, .text 0x801CADBC..0x801CAF34) ---
 * [  0] 0x801CADBC size:0x178   global clFlowRound_Dtor
 */

/* --- forward decls --- */
asm void clFlowRound_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowRound_Dtor[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowRound_Dtor = {
    (void *)&clFlowRound_Dtor, 0x00000178, (void *)extab_clFlowRound_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowRound_Dtor(void) { /* 0x801CADBC size:0x178 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr. r31, r3
    lis r3, lbl_8049AE70@ha
    stw r30, 0x18(r1)
    addi r30, r3, lbl_8049AE70@l
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    mr r28, r4
    beq clFlowRound_Dtor_L_801CAF10
    addi r0, r30, 0x14c
    stw r0, 0x0(r31)
    bl fn_80169C44
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne clFlowRound_Dtor_L_801CAE0C
    li r0, 0x0
    b clFlowRound_Dtor_L_801CAE10
    clFlowRound_Dtor_L_801CAE0C:
    mr r0, r3
    clFlowRound_Dtor_L_801CAE10:
    cmplwi r0, 0x0
    beq clFlowRound_Dtor_L_801CAE34
    cmplwi r3, 0x0
    bne clFlowRound_Dtor_L_801CAE24
    li r3, 0x0
    clFlowRound_Dtor_L_801CAE24:
    li r0, 0x0
    stb r0, 0x4(r3)
    stw r0, 0x18(r3)
    stw r0, 0x1c(r3)
    clFlowRound_Dtor_L_801CAE34:
    lfs f1, lbl_806D9D48(r2)
    bl SetScreenBrightness
    lwz r0, g_cupId(r13)
    addi r4, r30, 0x11c
    addi r3, r30, 0x130
    slwi r0, r0, 1
    lhax r0, r4, r0
    slwi r0, r0, 1
    lhax r3, r3, r0
    bl fn_80120A08
    lha r3, lbl_806CFDF0(r13)
    bl fn_80120A08
    lwz r3, 0x160(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x15c(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0xec(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x88(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x28(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0xf0(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r30, 0x168(r31)
    cmplwi r30, 0x0
    beq clFlowRound_Dtor_L_801CAECC
    lwz r3, 0x0(r30)
    li r4, 0x1
    bl Sprite_Destroy
    mr r3, r30
    bl MemoryManager_TimedFree
    clFlowRound_Dtor_L_801CAECC:
    li r29, 0x0
    mr r30, r31
    clFlowRound_Dtor_L_801CAED4:
    lwz r3, 0x3c(r30)
    li r4, 0x1
    bl Sprite_Destroy
    addi r29, r29, 0x1
    addi r30, r30, 0x14
    cmpwi r29, 0x4
    blt clFlowRound_Dtor_L_801CAED4
    bl fn_801A1678
    mr r3, r31
    li r4, 0x0
    bl dtor_801BA14C
    extsh. r0, r28
    ble clFlowRound_Dtor_L_801CAF10
    mr r3, r31
    bl MemoryManager_TimedFree
    clFlowRound_Dtor_L_801CAF10:
    lwz r0, 0x24(r1)
    mr r3, r31
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


/* === extracted from auto_clFlowRound_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void DebugPrintf();
extern void InitBGM();
extern void InitRumbleController();
extern void InitializeFrameSelection();
extern void PreloadResource();
extern void ResCtrl_Init();
extern void RoundCupIsCompleted();
extern void RoundIsUnlocked();
extern void SetScreenBrightness();
extern void SetSyncTarget();
extern void SetupBgSprites();
extern void SpriteSystem_EnsureInit();
extern void Sprite_CreateWithParams();
extern void Sprite_InitWithAnim();
extern void Sprite_SetAnimParam();
extern void fn_801A0550();
extern void fn_801B8540();
extern void fn_801B85DC();
extern void fn_801C9288();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_cupId;
extern unsigned int g_pInputState;
extern unsigned int g_roundIndex;
extern unsigned int lbl_806D9D10;
extern unsigned int lbl_806D9D14;
extern unsigned int lbl_806D9D28;
extern unsigned int lbl_806D9D38;
extern unsigned int lbl_806D9D3C;
extern unsigned int lbl_806D9D48;
extern unsigned int lbl_806D9D68;
extern unsigned int lbl_806D9D6C;
extern unsigned int lbl_806D9D70;
extern unsigned int lbl_806D9D74;
extern unsigned int lbl_806D9D78;
extern unsigned int lbl_806D9D80;
extern unsigned int lbl_806D9D98;
extern unsigned int lbl_806D9D9C;
extern unsigned int lbl_806D9DA0;
extern unsigned int lbl_806D9DA4;
extern unsigned int lbl_806D9DA8;
extern unsigned int lbl_806D9DAC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];
extern unsigned int lbl_8039B308[];
extern unsigned int lbl_8039B3B4[];
extern unsigned int lbl_8049AE70[];

/* --- function index (1 fns, .text 0x801CAF34..0x801CB620) ---
 * [  0] 0x801CAF34 size:0x6EC   global clFlowRound_Init
 */

/* --- forward decls --- */
asm void clFlowRound_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80082960();
extern void dtor_801BA14C();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; void *f39; unsigned int f40; unsigned int f41; void *f42; unsigned int f43; unsigned int f44; void *f45; unsigned int f46; unsigned int f47; void *f48; unsigned int f49; void *f50; unsigned int f51; unsigned int f52; void *f53; unsigned int f54; unsigned int f55; void *f56; unsigned int f57; unsigned int f58; void *f59; unsigned int f60; unsigned int f61; void *f62; unsigned int f63; void *f64; unsigned int f65; unsigned int f66; void *f67; unsigned int f68; } extab_clFlowRound_Init = { 0x380A0000, 0x00000030, 0x000000B8, 0x00000038, 0x000000AC, 0x0000003C, 0x009D00A0, 0x000002DC, 0x00000098, 0x000002F8, 0x004700A0, 0x00000440, 0x000000C4, 0x0000044C, 0x000000A0, 0x00000478, 0x000000D0, 0x0000048C, 0x001A00A0, 0x00000520, 0x000000DC, 0x0000052C, 0x000000A0, 0x00000558, 0x000000E8, 0x0000057C, 0x000000A0, 0x0000059C, 0x000000FC, 0x000005C8, 0x000000F4, 0x00000618, 0x001100A0, 0x00000674, 0x00000108, 0x000006A0, 0x000D00A0, 0x00000000, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x000000F4, (void *)&dtor_80082960, 0x0780001F, 0x00000094, (void *)&dtor_80082960, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x010000A0, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x010000A0, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x010000A0, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x010000A0, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x010000A0, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x010000A0 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowRound_Init = {
    (void *)&clFlowRound_Init, 0x000006EC, (void *)&extab_clFlowRound_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowRound_Init(void) { /* 0x801CAF34 size:0x6EC */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r4, lbl_8049AE70@ha
    stw r0, 0x34(r1)
    stmw r25, 0x14(r1)
    mr r31, r3
    addi r29, r4, lbl_8049AE70@l
    bl InitializeFrameSelection
    addi r0, r29, 0x14c
    addi r3, r31, 0x94
    stw r0, 0x0(r31)
    bl ResCtrl_Init
    addi r3, r31, 0xf4
    bl ResCtrl_Init
    bl SpriteSystem_EnsureInit
    lwz r0, g_cupId(r13)
    addi r4, r29, 0x11c
    li r3, 0x1b
    slwi r0, r0, 1
    lhax r27, r4, r0
    bl SetSyncTarget
    slwi r25, r27, 1
    addi r26, r29, 0x130
    lhax r3, r26, r25
    bl PreloadResource
    lhax r3, r26, r25
    addi r3, r3, 0xc
    bl PreloadResource
    addi r0, r29, 0x30
    slwi r26, r27, 4
    add r25, r0, r26
    lhau r3, 0x2(r25)
    bl PreloadResource
    lha r3, 0x0(r25)
    addi r3, r3, 0x6
    bl PreloadResource
    addi r25, r29, 0x30
    lhax r3, r25, r26
    bl PreloadResource
    lhax r3, r25, r26
    addi r3, r3, 0x9
    bl PreloadResource
    mr r0, r25
    add r25, r0, r26
    lhau r3, 0x6(r25)
    bl PreloadResource
    lha r3, 0x0(r25)
    addi r3, r3, 0x6
    bl PreloadResource
    addi r0, r29, 0x30
    add r25, r0, r26
    lhau r3, 0x4(r25)
    bl PreloadResource
    lha r3, 0x0(r25)
    addi r3, r3, 0x9
    bl PreloadResource
    mulli r26, r27, 0x6
    lis r3, lbl_8039B308@ha
    addi r25, r3, lbl_8039B308@l
    lhax r3, r25, r26
    bl PreloadResource
    lhax r3, r25, r26
    addi r3, r3, 0x9
    bl PreloadResource
    li r3, 0x194c
    bl PreloadResource
    li r3, 0x195e
    bl PreloadResource
    li r3, 0x196f
    bl PreloadResource
    li r3, 0x197c
    bl PreloadResource
    li r3, 0x1dec
    bl PreloadResource
    li r3, 0x195b
    bl PreloadResource
    li r3, 0x196d
    bl PreloadResource
    li r3, 0x1863
    bl PreloadResource
    li r3, 0x18ba
    bl PreloadResource
    li r3, 0x1843
    bl PreloadResource
    li r3, 0x189a
    bl PreloadResource
    li r3, 0x196e
    bl PreloadResource
    li r3, 0x197b
    bl PreloadResource
    lwz r0, g_roundIndex(r13)
    li r6, 0x4
    lis r3, g_playerData@ha
    li r27, 0x0
    srawi r5, r0, 31
    srwi r4, r6, 31
    subfc r0, r6, r0
    addi r30, r3, g_playerData@l
    adde r0, r5, r4
    li r26, 0x1
    stb r0, 0x14c(r31)
    li r25, 0x0
    stw r27, 0x8(r31)
    lbz r4, 0x14c(r31)
    subi r3, r4, 0x1
    subfic r0, r4, 0x1
    nor r0, r3, r0
    srawi r0, r0, 31
    and r28, r6, r0
    clFlowRound_Init_L_801CB0E8:
    addi r0, r27, 0x2c
    li r6, 0x0
    stwx r6, r31, r0
    addi r3, r27, 0x34
    addi r5, r27, 0x38
    addi r0, r27, 0x3c
    stwx r6, r31, r3
    mr r3, r30
    add r4, r25, r28
    stwx r6, r31, r5
    stwx r6, r31, r0
    bl RoundIsUnlocked
    clrlwi. r0, r3, 24
    beq clFlowRound_Init_L_801CB13C
    addi r0, r27, 0x30
    li r3, 0x0
    stwx r3, r31, r0
    lwz r3, 0x8(r31)
    addi r0, r3, 0x1
    stw r0, 0x8(r31)
    b clFlowRound_Init_L_801CB170
    clFlowRound_Init_L_801CB13C:
    clrlwi. r0, r26, 24
    beq clFlowRound_Init_L_801CB164
    addi r0, r27, 0x30
    li r3, 0x1
    stwx r3, r31, r0
    li r26, 0x0
    lwz r3, 0x8(r31)
    addi r0, r3, 0x1
    stw r0, 0x8(r31)
    b clFlowRound_Init_L_801CB170
    clFlowRound_Init_L_801CB164:
    addi r0, r27, 0x30
    li r3, 0x2
    stwx r3, r31, r0
    clFlowRound_Init_L_801CB170:
    mr r3, r31
    mr r4, r25
    li r5, 0x1
    bl fn_801C9288
    addi r25, r25, 0x1
    addi r27, r27, 0x14
    cmpwi r25, 0x4
    blt clFlowRound_Init_L_801CB0E8
    li r4, 0x0
    li r0, -0x1
    stw r4, 0x4(r31)
    li r3, 0x30
    lfs f1, lbl_806D9D80(r2)
    stw r0, 0x7c(r31)
    lfs f0, lbl_806D9D38(r2)
    stw r4, 0x1c(r31)
    stb r4, 0x20(r31)
    stw r4, 0x24(r31)
    stw r4, 0x28(r31)
    stw r4, 0xec(r31)
    stw r4, 0x168(r31)
    stw r4, 0x88(r31)
    stw r4, 0x80(r31)
    stb r4, 0x8c(r31)
    stfs f1, 0x90(r31)
    stfs f0, 0x150(r31)
    stfs f0, 0x154(r31)
    stfs f0, 0x158(r31)
    bl Alloc
    mr. r25, r3
    beq clFlowRound_Init_L_801CB210
    lfs f3, lbl_806D9D28(r2)
    li r4, 0x1c0
    lfs f5, lbl_806D9D38(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9D98(r2)
    fmr f6, f5
    lfs f2, lbl_806D9D9C(r2)
    bl Sprite_CreateWithParams
    clFlowRound_Init_L_801CB210:
    lis r3, g_playerData@ha
    stw r25, 0x28(r31)
    addi r25, r3, g_playerData@l
    li r26, 0x3
    clFlowRound_Init_L_801CB220:
    mr r3, r25
    add r4, r28, r26
    bl RoundIsUnlocked
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clFlowRound_Init_L_801CB250
    cmpwi r26, 0x3
    li r0, 0x3
    beq clFlowRound_Init_L_801CB248
    addi r0, r26, 0x1
    clFlowRound_Init_L_801CB248:
    stw r0, 0x4(r31)
    b clFlowRound_Init_L_801CB258
    clFlowRound_Init_L_801CB250:
    subic. r26, r26, 0x1
    bge clFlowRound_Init_L_801CB220
    clFlowRound_Init_L_801CB258:
    lbz r0, 0x14c(r31)
    lis r3, g_playerData@ha
    addi r3, r3, g_playerData@l
    li r25, 0x0
    cmplwi r0, 0x1
    li r4, 0x3
    bne clFlowRound_Init_L_801CB278
    li r4, 0x7
    clFlowRound_Init_L_801CB278:
    bl RoundIsUnlocked
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clFlowRound_Init_L_801CB28C
    li r25, 0x1
    clFlowRound_Init_L_801CB28C:
    lbz r0, 0x14c(r31)
    lis r3, g_playerData@ha
    lwz r4, g_ccClass(r13)
    addi r3, r3, g_playerData@l
    subfic r0, r0, 0x1
    lwz r5, g_cupId(r13)
    cntlzw r0, r0
    srwi r6, r0, 5
    bl RoundCupIsCompleted
    clrlwi. r0, r3, 24
    beq clFlowRound_Init_L_801CB2BC
    li r25, 0x2
    clFlowRound_Init_L_801CB2BC:
    lwz r4, g_cupId(r13)
    lis r5, lbl_8039B308@ha
    addi r6, r5, lbl_8039B308@l
    lis r3, g_playerData@ha
    mulli r4, r4, 0x6
    slwi r0, r25, 1
    li r5, 0x1
    lfs f2, lbl_806D9D68(r2)
    lfs f1, lbl_806D9D6C(r2)
    addi r3, r3, g_playerData@l
    add r4, r6, r4
    lfs f0, lbl_806D9D28(r2)
    add r4, r4, r0
    li r0, -0x1
    lha r6, -0x6(r4)
    li r4, 0x3
    stw r6, 0x94(r31)
    stb r5, 0xa4(r31)
    stfs f2, 0xa8(r31)
    stfs f1, 0xac(r31)
    stfs f0, 0xb0(r31)
    stw r0, 0xc8(r31)
    stw r0, 0xcc(r31)
    stw r0, 0xd0(r31)
    stw r0, 0xd4(r31)
    lbz r0, 0x14c(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Init_L_801CB330
    li r4, 0x7
    clFlowRound_Init_L_801CB330:
    bl RoundIsUnlocked
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clFlowRound_Init_L_801CB378
    li r3, 0x30
    bl Alloc
    mr. r25, r3
    beq clFlowRound_Init_L_801CB374
    lfs f3, lbl_806D9D28(r2)
    li r4, 0x85
    lfs f5, lbl_806D9D38(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9DA0(r2)
    fmr f6, f5
    lfs f2, lbl_806D9DA4(r2)
    bl Sprite_CreateWithParams
    clFlowRound_Init_L_801CB374:
    stw r25, 0xec(r31)
    clFlowRound_Init_L_801CB378:
    li r3, 0x30
    bl Alloc
    mr. r25, r3
    beq clFlowRound_Init_L_801CB3AC
    lfs f3, lbl_806D9D28(r2)
    li r4, 0x1dd
    lfs f1, lbl_806D9DA8(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D78(r2)
    fmr f6, f3
    lfs f5, lbl_806D9D38(r2)
    bl Sprite_CreateWithParams
    clFlowRound_Init_L_801CB3AC:
    stw r25, 0xf0(r31)
    li r4, 0x1ad4
    li r5, 0x1ae4
    lwz r3, 0xf0(r31)
    bl Sprite_SetAnimParam
    lbz r0, 0x14c(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Init_L_801CB418
    li r3, 0x15f4
    bl PreloadResource
    li r3, 0x15fe
    bl PreloadResource
    lwz r4, 0xf0(r31)
    li r3, 0x15f4
    lfs f0, lbl_806D9D70(r2)
    li r0, 0x1
    lfs f2, lbl_806D9D78(r2)
    stfs f0, 0xc(r4)
    lfs f1, lbl_806D9D74(r2)
    stfs f2, 0x10(r4)
    lfs f0, lbl_806D9D28(r2)
    stw r3, 0xf4(r31)
    stb r0, 0x104(r31)
    stfs f1, 0x108(r31)
    stfs f2, 0x10c(r31)
    stfs f0, 0x110(r31)
    b clFlowRound_Init_L_801CB420
    clFlowRound_Init_L_801CB418:
    li r0, 0x1ecd
    stw r0, 0xf4(r31)
    clFlowRound_Init_L_801CB420:
    li r3, 0x30
    bl Alloc
    mr. r25, r3
    beq clFlowRound_Init_L_801CB454
    lfs f1, lbl_806D9D38(r2)
    li r4, 0x9c
    lfs f3, lbl_806D9D3C(r2)
    li r5, 0x1
    fmr f2, f1
    lfs f6, lbl_806D9D28(r2)
    fmr f4, f3
    fmr f5, f1
    bl Sprite_CreateWithParams
    clFlowRound_Init_L_801CB454:
    stw r25, 0x15c(r31)
    li r3, 0x30
    bl Alloc
    mr. r25, r3
    beq clFlowRound_Init_L_801CB48C
    lfs f1, lbl_806D9D38(r2)
    li r4, 0x9c
    lfs f3, lbl_806D9D3C(r2)
    li r5, 0x1
    fmr f2, f1
    lfs f6, lbl_806D9D28(r2)
    fmr f4, f3
    fmr f5, f1
    bl Sprite_CreateWithParams
    clFlowRound_Init_L_801CB48C:
    stw r25, 0x160(r31)
    li r0, 0x0
    stb r0, 0x164(r31)
    stb r0, 0x165(r31)
    lbz r0, 0x14c(r31)
    cmplwi r0, 0x1
    bne clFlowRound_Init_L_801CB504
    li r3, 0xc
    bl Alloc
    mr. r25, r3
    beq clFlowRound_Init_L_801CB500
    li r0, 0x0
    li r3, 0x30
    stb r0, 0x4(r25)
    stb r0, 0x5(r25)
    stw r0, 0x8(r25)
    bl Alloc
    mr. r26, r3
    beq clFlowRound_Init_L_801CB4FC
    lfs f1, lbl_806D9DAC(r2)
    li r4, 0x9e
    lfs f3, lbl_806D9D28(r2)
    li r5, 0x1
    lfs f5, lbl_806D9D38(r2)
    fmr f2, f1
    fmr f4, f3
    fmr f6, f5
    bl Sprite_CreateWithParams
    clFlowRound_Init_L_801CB4FC:
    stw r26, 0x0(r25)
    clFlowRound_Init_L_801CB500:
    stw r25, 0x168(r31)
    clFlowRound_Init_L_801CB504:
    lwz r4, g_pInputState(r13)
    cmplwi r4, 0x0
    bne clFlowRound_Init_L_801CB518
    li r0, 0x0
    b clFlowRound_Init_L_801CB51C
    clFlowRound_Init_L_801CB518:
    mr r0, r4
    clFlowRound_Init_L_801CB51C:
    cmplwi r0, 0x0
    beq clFlowRound_Init_L_801CB544
    cmplwi r4, 0x0
    bne clFlowRound_Init_L_801CB530
    li r4, 0x0
    clFlowRound_Init_L_801CB530:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stw r0, 0x18(r4)
    stw r0, 0x1c(r4)
    clFlowRound_Init_L_801CB544:
    lfs f1, lbl_806D9D48(r2)
    bl SetScreenBrightness
    lbz r4, 0x14c(r31)
    li r3, 0x1b
    li r5, 0x0
    bl fn_801B85DC
    li r3, 0x0
    bl fn_801B8540
    bl InitBGM
    li r3, 0x1
    bl SetupBgSprites
    lwz r0, 0x88(r31)
    cmplwi r0, 0x0
    bne clFlowRound_Init_L_801CB5F0
    li r0, 0x0
    li r3, 0x30
    stw r0, 0x80(r31)
    stw r0, 0x84(r31)
    bl Alloc
    mr. r25, r3
    beq clFlowRound_Init_L_801CB5A8
    li r4, 0x84
    li r5, 0x0
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowRound_Init_L_801CB5A8:
    stw r25, 0x88(r31)
    addi r6, r29, 0x11c
    addi r5, r29, 0x108
    li r4, 0x1970
    lwz r0, g_cupId(r13)
    lwz r3, 0x88(r31)
    slwi r0, r0, 1
    lhax r0, r6, r0
    slwi r0, r0, 1
    lhax r5, r5, r0
    bl Sprite_SetAnimParam
    lwz r3, 0x88(r31)
    bl fn_801A0550
    lwz r3, 0x88(r31)
    lfs f1, lbl_806D9D10(r2)
    lfs f0, lbl_806D9D14(r2)
    stfs f1, 0xc(r3)
    stfs f0, 0x10(r3)
    clFlowRound_Init_L_801CB5F0:
    lis r3, lbl_8039B3B4@ha
    addi r3, r3, lbl_8039B3B4@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0x1
    bl InitRumbleController
    mr r3, r31
    lmw r25, 0x14(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

#ifdef __cplusplus
}
#endif
