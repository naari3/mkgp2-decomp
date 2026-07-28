/* === extracted from auto_clFlowChara_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void CharaSelect_SetupCharacterDisplay();
extern void FileLoader_Open();
extern void GetFrameIdxFromVisualIdx();
extern void GetKartModelNameEntry();
extern void LObjList_Destroy();
extern void MTXIdentity();
extern void Object_DriveAnimMatrix();
extern void Object_GetField8();
extern void Object_SetAnimBinding();
extern void PSMTXConcat();
extern void PSMTXScale();
extern void PSMTXTrans();
extern void RumbleUpdate();
extern void SetScreenBrightness();
extern void Sprite_AdvanceAnim();
extern void Sprite_Destroy();
extern void Sprite_InitWithAnim();
extern void __assert();
extern void clFlowChara_HandleConfirm();
extern void clNormal3D_Construct();
extern void clNormal3D_Exec();
extern void clNormal3D_SetScale();
extern void fn_801699D8();
extern void fn_8019FF6C();
extern void fn_801A024C();
extern void fn_801B7CAC();
extern void fn_801B8398();
extern void fn_801B84B4();
extern void fn_801B8540();
extern void fn_801B85DC();
extern void fn_801B87D8();
extern void fn_801B8918();
extern void fn_801C37E8();
extern void fn_8021A660();
extern void fn_8021A71C();
extern void fn_8021A9E8();
extern void fn_8021ABFC();
extern void fn_8025D770();
extern void fn_802D1E34();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_ARROW_RIGHT_OFFSET;
extern unsigned int FLOAT_ARROW_SCALE;
extern unsigned int FLOAT_BRIGHTNESS_DARK;
extern unsigned int FLOAT_FULL_ALPHA;
extern unsigned int FLOAT_SPRITE_INIT_TIME;
extern unsigned int g_pInputState;
extern unsigned int lbl_806D184C;
extern unsigned int lbl_806D184D;
extern unsigned int lbl_806D9B7C;
extern unsigned int lbl_806D9B80;
extern unsigned int lbl_806D9B88;
extern unsigned int lbl_806D9BA8;
extern unsigned int lbl_806D9BB0;
extern unsigned int lbl_806D9BB4;
extern unsigned int lbl_806D9BBC;
extern unsigned int lbl_806D9BC0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int FrameParam_ARRAY_8049aad0[];
extern unsigned int g_tierCursorPosTable[];
extern unsigned int jumptable_8049AC90[];
extern unsigned int lbl_8039AA40[];

/* --- function index (1 fns, .text 0x801C3D48..0x801C4CA4) ---
 * [  0] 0x801C3D48 size:0xF5C   global clFlowChara_Update
 */

/* --- forward decls --- */
asm void clFlowChara_Update(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; void *f13; unsigned int f14; void *f15; unsigned int f16; void *f17; } extab_clFlowChara_Update = { 0x300A0000, 0x0000016C, 0x00000028, 0x000001E8, 0x00060030, 0x0000024C, 0x00000038, 0x00000438, 0x00000040, 0x00000000, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowChara_Update = {
    (void *)&clFlowChara_Update, 0x00000F5C, (void *)&extab_clFlowChara_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowChara_Update(void) { /* 0x801C3D48 size:0xF5C */
    nofralloc
    stwu r1, -0xe0(r1)
    mflr r0
    lis r4, lbl_8039AA40@ha
    stw r0, 0xe4(r1)
    stmw r26, 0xc8(r1)
    addi r30, r4, lbl_8039AA40@l
    mr r31, r3
    lwz r8, 0x74c(r30)
    lwz r7, 0x750(r30)
    lwz r6, 0x754(r30)
    lwz r5, 0x758(r30)
    lwz r4, 0x75c(r30)
    lwz r3, 0x760(r30)
    lhz r0, 0x764(r30)
    stw r8, 0x8(r1)
    stw r7, 0xc(r1)
    stw r6, 0x10(r1)
    stw r5, 0x14(r1)
    stw r4, 0x18(r1)
    stw r3, 0x1c(r1)
    sth r0, 0x20(r1)
    bl RumbleUpdate
    lbz r0, 0xc(r31)
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C3DC0
    lwz r3, 0x8(r31)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0x8(r31)
    stb r0, 0xc(r31)
    clFlowChara_Update_L_801C3DC0:
    lwz r3, 0x10(r31)
    addi r0, r3, 0x1
    stw r0, 0x10(r31)
    lwz r0, 0x8(r31)
    cmplwi r0, 0x6
    bgt clFlowChara_Update_L_801C49DC
    lis r3, jumptable_8049AC90@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_8049AC90@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lwz r0, 0x10(r31)
    cmpwi r0, 0x2
    blt clFlowChara_Update_L_801C3E18
    cmpwi r0, 0xe
    bgt clFlowChara_Update_L_801C3E18
    addi r3, r30, 0x70c
    slwi r0, r0, 2
    add r3, r3, r0
    lwz r3, -0x8(r3)
    bl FileLoader_Open
    clFlowChara_Update_L_801C3E18:
    lwz r3, 0x10(r31)
    cmpwi r3, 0xf
    blt clFlowChara_Update_L_801C3E80
    cmpwi r3, 0x1b
    bgt clFlowChara_Update_L_801C3E80
    subi r28, r3, 0xf
    mr r3, r31
    mr r4, r28
    bl GetFrameIdxFromVisualIdx
    slwi r0, r3, 2
    add r3, r31, r0
    lwz r0, 0xa8(r3)
    cmpwi r0, 0x1
    blt clFlowChara_Update_L_801C3E70
    mr r3, r31
    mr r4, r28
    bl GetFrameIdxFromVisualIdx
    li r4, 0x2
    bl GetKartModelNameEntry
    lwz r3, 0x0(r3)
    bl FileLoader_Open
    b clFlowChara_Update_L_801C3E80
    clFlowChara_Update_L_801C3E70:
    slwi r0, r28, 2
    addi r3, r30, 0x5d4
    lwzx r3, r3, r0
    bl FileLoader_Open
    clFlowChara_Update_L_801C3E80:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1c
    bne clFlowChara_Update_L_801C3EDC
    mr r28, r31
    addi r29, r30, 0x70c
    li r27, 0x0
    clFlowChara_Update_L_801C3E98:
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq clFlowChara_Update_L_801C3EB4
    lwz r4, 0x0(r29)
    li r5, 0x0
    bl clNormal3D_Construct
    clFlowChara_Update_L_801C3EB4:
    stw r26, 0xdc(r28)
    addi r4, r31, 0x78
    li r5, 0x0
    lwz r3, 0xdc(r28)
    bl Object_SetAnimBinding
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0xd
    addi r29, r29, 0x4
    blt clFlowChara_Update_L_801C3E98
    clFlowChara_Update_L_801C3EDC:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1d
    bne clFlowChara_Update_L_801C3FAC
    mr r28, r31
    addi r29, r30, 0x5d4
    li r27, 0x0
    clFlowChara_Update_L_801C3EF4:
    mr r3, r31
    mr r4, r27
    bl GetFrameIdxFromVisualIdx
    slwi r3, r3, 2
    addi r0, r3, 0xa8
    lwzx r0, r31, r0
    cmpwi r0, 0x1
    blt clFlowChara_Update_L_801C3F78
    li r3, 0x64
    bl Alloc
    mr. r26, r3
    beq clFlowChara_Update_L_801C3F48
    mr r3, r31
    mr r4, r27
    bl GetFrameIdxFromVisualIdx
    mr r4, r3
    mr r3, r26
    li r5, 0x2
    li r6, 0x0
    li r7, 0x0
    bl fn_8021ABFC
    clFlowChara_Update_L_801C3F48:
    lfs f1, lbl_806D9BB0(r2)
    stw r26, 0x144(r28)
    fmr f2, f1
    fmr f3, f1
    lwz r3, 0x144(r28)
    bl fn_8021A660
    lwz r3, 0x144(r28)
    lfs f1, lbl_806D9B7C(r2)
    lfs f2, FLOAT_BRIGHTNESS_DARK(r2)
    lfs f3, lbl_806D9BB4(r2)
    bl fn_8021A71C
    b clFlowChara_Update_L_801C3F98
    clFlowChara_Update_L_801C3F78:
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq clFlowChara_Update_L_801C3F94
    lwz r4, 0x0(r29)
    li r5, 0x0
    bl clNormal3D_Construct
    clFlowChara_Update_L_801C3F94:
    stw r26, 0x110(r28)
    clFlowChara_Update_L_801C3F98:
    addi r27, r27, 0x1
    addi r29, r29, 0x4
    cmpwi r27, 0xd
    addi r28, r28, 0x4
    blt clFlowChara_Update_L_801C3EF4
    clFlowChara_Update_L_801C3FAC:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1
    bne clFlowChara_Update_L_801C3FE8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x6
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x7
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C3FE8:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x3
    bne clFlowChara_Update_L_801C4024
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x5
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x8
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C4024:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x5
    bne clFlowChara_Update_L_801C4060
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x4
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x9
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C4060:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x7
    bne clFlowChara_Update_L_801C409C
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x3
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xa
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C409C:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x9
    bne clFlowChara_Update_L_801C40D8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x2
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xb
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C40D8:
    lwz r0, 0x10(r31)
    cmpwi r0, 0xb
    bne clFlowChara_Update_L_801C4114
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x1
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xc
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C4114:
    lwz r0, 0x10(r31)
    cmpwi r0, 0xd
    bne clFlowChara_Update_L_801C4154
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x0
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lwz r0, 0x4(r31)
    addi r5, r1, 0x8
    li r3, 0xd
    li r4, 0x0
    slwi r0, r0, 1
    lhax r5, r5, r0
    bl fn_801B85DC
    clFlowChara_Update_L_801C4154:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x16
    bne clFlowChara_Update_L_801C41A8
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowChara_Update_L_801C4180
    li r4, 0x16a
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowChara_Update_L_801C4180:
    stw r26, 0x5c(r31)
    li r3, 0x1
    lfs f1, lbl_806D9BA8(r2)
    li r0, 0x0
    lwz r4, 0x5c(r31)
    lfs f0, lbl_806D9BBC(r2)
    stfs f1, 0xc(r4)
    stfs f0, 0x10(r4)
    stb r3, lbl_806D184C(r13)
    stb r0, lbl_806D184D(r13)
    clFlowChara_Update_L_801C41A8:
    lis r3, FrameParam_ARRAY_8049aad0@ha
    li r0, 0xd
    addi r5, r3, FrameParam_ARRAY_8049aad0@l
    mr r4, r31
    li r7, 0x1
    mtctr r0
    clFlowChara_Update_L_801C41C0:
    lwz r6, 0x14(r4)
    cmplwi r6, 0x0
    beq clFlowChara_Update_L_801C421C
    lwz r3, 0x8(r5)
    lis r0, 0x4330
    stw r0, 0xb8(r1)
    xoris r0, r3, 0x8000
    lfd f2, lbl_806D9B88(r2)
    stw r0, 0xbc(r1)
    lfs f3, 0xc(r5)
    lfd f1, 0xb8(r1)
    lfs f0, 0x10(r5)
    fsubs f1, f1, f2
    lfs f2, 0x14(r5)
    fmadds f0, f3, f1, f0
    stfs f0, 0xc(r6)
    stfs f2, 0x10(r6)
    lwz r3, 0x8(r5)
    cmpwi r3, 0x0
    beq clFlowChara_Update_L_801C421C
    subi r0, r3, 0x1
    li r7, 0x0
    stw r0, 0x8(r5)
    clFlowChara_Update_L_801C421C:
    addi r4, r4, 0x4
    addi r5, r5, 0x18
    bdnz clFlowChara_Update_L_801C41C0
    clrlwi. r0, r7, 24
    beq clFlowChara_Update_L_801C49DC
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1e
    blt clFlowChara_Update_L_801C49DC
    li r27, 0x0
    clFlowChara_Update_L_801C4240:
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    mr r4, r27
    li r5, 0x20
    li r6, -0x1
    bl fn_801C37E8
    addi r27, r27, 0x1
    cmpwi r27, 0xd
    blt clFlowChara_Update_L_801C4240
    li r3, 0x1ae1
    bl fn_801B8918
    lfs f1, lbl_806D9B80(r2)
    addi r3, r1, 0x24
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    lfs f1, FLOAT_SPRITE_INIT_TIME(r2)
    addi r3, r1, 0x54
    li r4, 0x79
    bl fn_8025D770
    addi r4, r30, 0x740
    lfs f1, 0x740(r30)
    lfs f2, 0x4(r4)
    addi r3, r1, 0x84
    lfs f3, 0x8(r4)
    bl PSMTXTrans
    addi r3, r31, 0x78
    bl MTXIdentity
    addi r4, r31, 0x78
    addi r3, r1, 0x24
    mr r5, r4
    bl PSMTXConcat
    addi r4, r31, 0x78
    addi r3, r1, 0x54
    mr r5, r4
    bl PSMTXConcat
    addi r4, r31, 0x78
    addi r3, r1, 0x84
    mr r5, r4
    bl PSMTXConcat
    lwz r4, 0x4(r31)
    mr r3, r31
    bl GetFrameIdxFromVisualIdx
    mr r4, r3
    mr r3, r31
    bl CharaSelect_SetupCharacterDisplay
    li r0, 0x1
    stb r0, 0x65(r31)
    stb r0, 0xc(r31)
    b clFlowChara_Update_L_801C49DC
    li r27, 0x0
    mr r28, r31
    clFlowChara_Update_L_801C4310:
    lwz r3, 0x14(r28)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4344
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clrlwi. r0, r3, 24
    beq clFlowChara_Update_L_801C4344
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    mr r4, r27
    li r5, 0x169
    li r6, 0x0
    bl fn_801C37E8
    clFlowChara_Update_L_801C4344:
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0xd
    blt clFlowChara_Update_L_801C4310
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1e
    ble clFlowChara_Update_L_801C49DC
    li r27, 0x0
    mr r28, r31
    clFlowChara_Update_L_801C4368:
    lwz r0, 0x4(r31)
    cmpw r27, r0
    bne clFlowChara_Update_L_801C4390
    lfs f1, FLOAT_FULL_ALPHA(r2)
    mr r3, r31
    mr r4, r27
    li r5, 0x1e
    li r6, 0x0
    bl fn_801C37E8
    b clFlowChara_Update_L_801C43A8
    clFlowChara_Update_L_801C4390:
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    mr r4, r27
    li r5, 0x168
    li r6, 0x0
    bl fn_801C37E8
    clFlowChara_Update_L_801C43A8:
    lwz r3, 0x14(r28)
    li r4, 0x1
    bl fn_8019FF6C
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0xd
    blt clFlowChara_Update_L_801C4368
    lfs f1, 0x6c(r31)
    bl SetScreenBrightness
    li r0, 0x1
    li r3, 0x0
    stb r0, 0xc(r31)
    li r4, 0x1
    bl fn_801699D8
    b clFlowChara_Update_L_801C49DC
    lwz r5, g_pInputState(r13)
    cmplwi r5, 0x0
    bne clFlowChara_Update_L_801C43F8
    li r0, 0x0
    b clFlowChara_Update_L_801C43FC
    clFlowChara_Update_L_801C43F8:
    mr r0, r5
    clFlowChara_Update_L_801C43FC:
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C451C
    cmplwi r5, 0x0
    lwz r4, 0x4(r31)
    bne clFlowChara_Update_L_801C4414
    li r5, 0x0
    clFlowChara_Update_L_801C4414:
    lwz r3, 0x4(r31)
    lwz r0, 0x14(r5)
    add r0, r3, r0
    stw r0, 0x4(r31)
    lwz r0, 0x4(r31)
    cmpwi r0, 0xc
    ble clFlowChara_Update_L_801C4438
    li r0, 0x0
    stw r0, 0x4(r31)
    clFlowChara_Update_L_801C4438:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    bge clFlowChara_Update_L_801C444C
    li r0, 0xc
    stw r0, 0x4(r31)
    clFlowChara_Update_L_801C444C:
    lwz r0, 0x4(r31)
    cmpw r4, r0
    beq clFlowChara_Update_L_801C451C
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r5, 0x168
    li r6, -0x1
    bl fn_801C37E8
    lwz r4, 0x4(r31)
    mr r3, r31
    lfs f1, FLOAT_FULL_ALPHA(r2)
    li r5, 0x1e
    li r6, -0x1
    bl fn_801C37E8
    lwz r4, 0x4(r31)
    mr r3, r31
    bl GetFrameIdxFromVisualIdx
    mr r4, r3
    mr r3, r31
    bl CharaSelect_SetupCharacterDisplay
    lwz r0, 0x4(r31)
    addi r3, r1, 0x8
    slwi r0, r0, 1
    lhax r3, r3, r0
    bl fn_801B84B4
    bl fn_801B7CAC
    lwz r5, 0x48(r31)
    cmplwi r5, 0x0
    beq clFlowChara_Update_L_801C44E4
    lwz r0, 0x4(r31)
    lis r3, g_tierCursorPosTable@ha
    addi r4, r3, g_tierCursorPosTable@l
    slwi r0, r0, 3
    add r3, r4, r0
    lfsx f0, r4, r0
    lfs f1, 0x4(r3)
    stfs f0, 0xc(r5)
    stfs f1, 0x10(r5)
    clFlowChara_Update_L_801C44E4:
    lwz r4, 0x4c(r31)
    cmplwi r4, 0x0
    beq clFlowChara_Update_L_801C451C
    lwz r0, 0x4(r31)
    lis r3, g_tierCursorPosTable@ha
    addi r3, r3, g_tierCursorPosTable@l
    lfs f1, FLOAT_ARROW_RIGHT_OFFSET(r2)
    slwi r0, r0, 3
    lfsx f0, r3, r0
    add r3, r3, r0
    lfs f2, 0x4(r3)
    fadds f0, f1, f0
    stfs f0, 0xc(r4)
    stfs f2, 0x10(r4)
    clFlowChara_Update_L_801C451C:
    mr r3, r31
    bl clFlowChara_HandleConfirm
    cmpwi r3, -0x1
    beq clFlowChara_Update_L_801C49DC
    lwz r4, 0x4(r31)
    mr r3, r31
    lfs f1, FLOAT_FULL_ALPHA(r2)
    li r5, 0x1f
    li r6, -0x1
    bl fn_801C37E8
    addi r5, r30, 0x4a4
    lwz r0, 0x4(r31)
    lfs f1, 0x8(r5)
    li r4, 0x0
    slwi r0, r0, 2
    lfs f2, FLOAT_FULL_ALPHA(r2)
    add r3, r31, r0
    fmr f3, f1
    lwz r3, 0xdc(r3)
    lfs f4, 0xc(r5)
    bl clNormal3D_SetScale
    li r0, -0x1
    li r4, 0x1
    stb r0, lbl_806D184C(r13)
    lwz r3, 0x48(r31)
    bl Sprite_Destroy
    lwz r3, 0x4c(r31)
    li r4, 0x1
    bl Sprite_Destroy
    li r3, 0x0
    li r0, 0x1
    stw r3, 0x48(r31)
    stw r3, 0x4c(r31)
    stb r0, 0xc(r31)
    b clFlowChara_Update_L_801C49DC
    lbz r0, 0x64(r31)
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C49DC
    li r0, 0x1
    stb r0, 0xc(r31)
    b clFlowChara_Update_L_801C49DC
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x14(r3)
    bl fn_801A024C
    clrlwi. r0, r3, 24
    bne clFlowChara_Update_L_801C4608
    lwz r4, 0x4(r31)
    mr r3, r31
    lfs f1, FLOAT_FULL_ALPHA(r2)
    li r5, 0x1d
    li r6, -0x1
    bl fn_801C37E8
    bl fn_801B87D8
    li r3, 0x0
    li r0, 0x1
    stw r3, 0x10(r31)
    stb r0, 0xc(r31)
    clFlowChara_Update_L_801C4608:
    lis r3, FrameParam_ARRAY_8049aad0@ha
    li r0, 0xd
    addi r4, r3, FrameParam_ARRAY_8049aad0@l
    li r5, 0x0
    li r3, 0x0
    mtctr r0
    clFlowChara_Update_L_801C4620:
    lwz r0, 0x4(r31)
    cmpw r5, r0
    beq clFlowChara_Update_L_801C4630
    stw r3, 0x8(r4)
    clFlowChara_Update_L_801C4630:
    addi r4, r4, 0x18
    addi r5, r5, 0x1
    bdnz clFlowChara_Update_L_801C4620
    b clFlowChara_Update_L_801C49DC
    lwz r0, 0x10(r31)
    cmpwi r0, 0xe
    bne clFlowChara_Update_L_801C4714
    lwz r0, 0x60(r31)
    cmpwi r0, 0xf
    bne clFlowChara_Update_L_801C4670
    lwz r0, 0x4(r31)
    addi r3, r1, 0x8
    slwi r0, r0, 1
    lhax r3, r3, r0
    bl fn_801B8540
    b clFlowChara_Update_L_801C4684
    clFlowChara_Update_L_801C4670:
    lwz r0, 0x4(r31)
    addi r3, r1, 0x8
    slwi r0, r0, 1
    lhax r3, r3, r0
    bl fn_801B8398
    clFlowChara_Update_L_801C4684:
    lwz r3, 0x70(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C46A4
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    clFlowChara_Update_L_801C46A4:
    lwz r3, 0x74(r31)
    li r4, 0x1
    bl LObjList_Destroy
    li r0, 0x0
    li r4, 0x1
    stw r0, 0x70(r31)
    stw r0, 0x74(r31)
    stb r0, 0x65(r31)
    lwz r3, 0x5c(r31)
    bl Sprite_Destroy
    li r0, 0x0
    li r4, 0x1
    stw r0, 0x5c(r31)
    lwz r3, 0x50(r31)
    bl Sprite_Destroy
    lwz r3, 0x54(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x58(r31)
    li r4, 0x1
    bl Sprite_Destroy
    li r0, 0x0
    li r3, 0x0
    stw r0, 0x50(r31)
    li r4, 0x0
    stw r0, 0x54(r31)
    stw r0, 0x58(r31)
    bl fn_801699D8
    clFlowChara_Update_L_801C4714:
    lwz r0, 0x10(r31)
    cmpwi r0, 0xe
    bne clFlowChara_Update_L_801C4768
    lwz r0, 0x4(r31)
    cmpwi r0, 0x6
    beq clFlowChara_Update_L_801C4744
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x6
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4744:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x7
    beq clFlowChara_Update_L_801C4768
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x7
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4768:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x12
    bne clFlowChara_Update_L_801C47BC
    lwz r0, 0x4(r31)
    cmpwi r0, 0x5
    beq clFlowChara_Update_L_801C4798
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x5
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4798:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x8
    beq clFlowChara_Update_L_801C47BC
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x8
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C47BC:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x16
    bne clFlowChara_Update_L_801C4810
    lwz r0, 0x4(r31)
    cmpwi r0, 0x4
    beq clFlowChara_Update_L_801C47EC
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x4
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C47EC:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x9
    beq clFlowChara_Update_L_801C4810
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x9
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4810:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x18
    bne clFlowChara_Update_L_801C4864
    lwz r0, 0x4(r31)
    cmpwi r0, 0x3
    beq clFlowChara_Update_L_801C4840
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x3
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4840:
    lwz r0, 0x4(r31)
    cmpwi r0, 0xa
    beq clFlowChara_Update_L_801C4864
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xa
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4864:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1c
    bne clFlowChara_Update_L_801C48B8
    lwz r0, 0x4(r31)
    cmpwi r0, 0x2
    beq clFlowChara_Update_L_801C4894
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x2
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4894:
    lwz r0, 0x4(r31)
    cmpwi r0, 0xb
    beq clFlowChara_Update_L_801C48B8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xb
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C48B8:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x20
    bne clFlowChara_Update_L_801C490C
    lwz r0, 0x4(r31)
    cmpwi r0, 0x1
    beq clFlowChara_Update_L_801C48E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x1
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C48E8:
    lwz r0, 0x4(r31)
    cmpwi r0, 0xc
    beq clFlowChara_Update_L_801C490C
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xc
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C490C:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x24
    bne clFlowChara_Update_L_801C493C
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    beq clFlowChara_Update_L_801C493C
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x0
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C493C:
    lis r3, FrameParam_ARRAY_8049aad0@ha
    li r0, 0xd
    addi r5, r3, FrameParam_ARRAY_8049aad0@l
    mr r4, r31
    mtctr r0
    clFlowChara_Update_L_801C4950:
    lwz r6, 0x14(r4)
    cmplwi r6, 0x0
    beq clFlowChara_Update_L_801C49B0
    lwz r3, 0x8(r5)
    lis r0, 0x4330
    stw r0, 0xb8(r1)
    xoris r0, r3, 0x8000
    lfd f2, lbl_806D9B88(r2)
    stw r0, 0xbc(r1)
    lfs f3, 0xc(r5)
    lfd f1, 0xb8(r1)
    lfs f0, 0x10(r5)
    fsubs f1, f1, f2
    lfs f2, 0x14(r5)
    fnmsubs f0, f3, f1, f0
    stfs f0, 0xc(r6)
    stfs f2, 0x10(r6)
    lwz r3, 0x8(r5)
    cmpwi r3, 0x0
    beq clFlowChara_Update_L_801C49B0
    cmpwi r3, -0x10
    beq clFlowChara_Update_L_801C49B0
    addi r0, r3, 0x1
    stw r0, 0x8(r5)
    clFlowChara_Update_L_801C49B0:
    addi r4, r4, 0x4
    addi r5, r5, 0x18
    bdnz clFlowChara_Update_L_801C4950
    lwz r0, 0x10(r31)
    cmpwi r0, 0x3c
    bne clFlowChara_Update_L_801C49DC
    li r0, 0x1
    stb r0, 0xc(r31)
    b clFlowChara_Update_L_801C49DC
    lwz r3, 0x60(r31)
    b clFlowChara_Update_L_801C4C90
    clFlowChara_Update_L_801C49DC:
    li r27, 0x0
    mr r28, r31
    clFlowChara_Update_L_801C49E4:
    lwz r3, 0x14(r28)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C49F8
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C49F8:
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0xd
    blt clFlowChara_Update_L_801C49E4
    lwz r3, 0x5c(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A1C
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A1C:
    lbz r0, 0x65(r31)
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C4C8C
    lwz r3, 0x48(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A3C
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A3C:
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A50
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A50:
    lwz r3, 0x50(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A64
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A64:
    lwz r3, 0x54(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A78
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A78:
    lwz r3, 0x58(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A8C
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A8C:
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0xdc(r3)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4B20
    bl clNormal3D_Exec
    lwz r0, 0x8(r31)
    cmpwi r0, 0x3
    blt clFlowChara_Update_L_801C4B0C
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0xdc(r3)
    bl Object_GetField8
    addi r3, r30, 0x4a4
    lfs f0, 0xc(r3)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne clFlowChara_Update_L_801C4B0C
    li r0, 0x1
    lfs f2, FLOAT_FULL_ALPHA(r2)
    stb r0, 0x64(r31)
    li r4, 0x0
    fsubs f1, f0, f2
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    fmr f3, f1
    add r3, r31, r0
    fmr f4, f1
    lwz r3, 0xdc(r3)
    bl clNormal3D_SetScale
    clFlowChara_Update_L_801C4B0C:
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0xdc(r3)
    bl Object_DriveAnimMatrix
    clFlowChara_Update_L_801C4B20:
    lwz r0, 0x4(r31)
    slwi r4, r0, 2
    add r3, r31, r4
    lwz r0, 0x110(r3)
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C4BE8
    lwz r28, 0x1d4(r31)
    cmplwi r28, 0x0
    beq clFlowChara_Update_L_801C4BE8
    bne clFlowChara_Update_L_801C4B58
    addi r3, r2, -0x69C  /* lbl_806D9BC4 */
    li r4, 0x47c
    addi r5, r2, -0x694  /* lbl_806D9BCC */
    bl __assert
    clFlowChara_Update_L_801C4B58:
    cmplwi r28, 0x0
    beq clFlowChara_Update_L_801C4BA0
    bne clFlowChara_Update_L_801C4B74
    addi r3, r2, -0x69C  /* lbl_806D9BC4 */
    li r4, 0x25d
    addi r5, r2, -0x694  /* lbl_806D9BCC */
    bl __assert
    clFlowChara_Update_L_801C4B74:
    lwz r4, 0x14(r28)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne clFlowChara_Update_L_801C4B90
    rlwinm. r0, r4, 0, 25, 25
    beq clFlowChara_Update_L_801C4B90
    li r3, 0x1
    clFlowChara_Update_L_801C4B90:
    clrlwi. r0, r3, 24
    beq clFlowChara_Update_L_801C4BA0
    mr r3, r28
    bl fn_802D1E34
    clFlowChara_Update_L_801C4BA0:
    lwz r0, 0x4(r31)
    addi r4, r28, 0x44
    li r5, 0x0
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x110(r3)
    bl Object_SetAnimBinding
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x110(r3)
    bl clNormal3D_Exec
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x110(r3)
    bl Object_DriveAnimMatrix
    b clFlowChara_Update_L_801C4C8C
    clFlowChara_Update_L_801C4BE8:
    add r3, r31, r4
    lwz r0, 0x144(r3)
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C4C8C
    lwz r28, 0x1d4(r31)
    cmplwi r28, 0x0
    beq clFlowChara_Update_L_801C4C8C
    bne clFlowChara_Update_L_801C4C18
    addi r3, r2, -0x69C  /* lbl_806D9BC4 */
    li r4, 0x47c
    addi r5, r2, -0x694  /* lbl_806D9BCC */
    bl __assert
    clFlowChara_Update_L_801C4C18:
    cmplwi r28, 0x0
    beq clFlowChara_Update_L_801C4C60
    bne clFlowChara_Update_L_801C4C34
    addi r3, r2, -0x69C  /* lbl_806D9BC4 */
    li r4, 0x25d
    addi r5, r2, -0x694  /* lbl_806D9BCC */
    bl __assert
    clFlowChara_Update_L_801C4C34:
    lwz r4, 0x14(r28)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne clFlowChara_Update_L_801C4C50
    rlwinm. r0, r4, 0, 25, 25
    beq clFlowChara_Update_L_801C4C50
    li r3, 0x1
    clFlowChara_Update_L_801C4C50:
    clrlwi. r0, r3, 24
    beq clFlowChara_Update_L_801C4C60
    mr r3, r28
    bl fn_802D1E34
    clFlowChara_Update_L_801C4C60:
    lwz r0, 0x4(r31)
    addi r4, r28, 0x44
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x144(r3)
    stw r4, 0x58(r3)
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x144(r3)
    bl fn_8021A9E8
    clFlowChara_Update_L_801C4C8C:
    li r3, -0x1
    clFlowChara_Update_L_801C4C90:
    lmw r26, 0xc8(r1)
    lwz r0, 0xe4(r1)
    mtlr r0
    addi r1, r1, 0xe0
    blr
}
