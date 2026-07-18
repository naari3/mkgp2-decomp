/* === extracted from auto_CardSave_Tick_Captur_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void OSGetTick();
extern void Sci2Card_SendCmdCleaning();
extern void Sci2Card_Singleton_Get();
extern void ServiceLatch_CheckTriggered();
extern void card_backup();
extern void card_rw_state_machine();
extern void fn_80270C48();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806CF0D0;
extern unsigned int lbl_806CF0D8;
extern unsigned int lbl_806CF0E4;
extern unsigned int lbl_806D1210;
extern unsigned int lbl_806D121C;
extern unsigned int lbl_806D1220;
extern unsigned int lbl_806D1227;
extern unsigned int lbl_806D1228;
extern unsigned int lbl_806D122A;
extern unsigned int lbl_806D122C;
extern unsigned int lbl_806D124C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];
extern unsigned int lbl_80598A60[];

/* --- function index (1 fns, .text 0x800937D4..0x80093C28) ---
 * [  0] 0x800937D4 size:0x454   global CardSave_Tick_CaptureAndStart
 */

/* --- forward decls --- */
asm void CardSave_Tick_CaptureAndStart(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardSave_Tick_CaptureAndStart[8] = {
    0x90, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardSave_Tick_CaptureAndStart = {
    (void *)&CardSave_Tick_CaptureAndStart, 0x00000454, (void *)extab_CardSave_Tick_CaptureAndStart
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardSave_Tick_CaptureAndStart(void) { /* 0x800937D4 size:0x454 */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stmw r14, 0x38(r1)
    bl ServiceLatch_CheckTriggered
    clrlwi. r0, r3, 24
    bne CardSave_Tick_CaptureAndStart_L_80093800
    li r0, 0x1
    li r3, 0x1
    stw r0, lbl_806D1210(r13)
    b CardSave_Tick_CaptureAndStart_L_80093C14
    CardSave_Tick_CaptureAndStart_L_80093800:
    bl card_rw_state_machine
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardSave_Tick_CaptureAndStart_L_80093C10
    lwz r3, lbl_806D1210(r13)
    li r0, 0x0
    stb r0, 0x8(r1)
    cmpwi r3, 0x5
    beq CardSave_Tick_CaptureAndStart_L_80093C00
    bge CardSave_Tick_CaptureAndStart_L_80093850
    cmpwi r3, 0x2
    beq CardSave_Tick_CaptureAndStart_L_80093C00
    bge CardSave_Tick_CaptureAndStart_L_80093844
    cmpwi r3, 0x0
    beq CardSave_Tick_CaptureAndStart_L_80093868
    bge CardSave_Tick_CaptureAndStart_L_800938C8
    b CardSave_Tick_CaptureAndStart_L_80093C00
    CardSave_Tick_CaptureAndStart_L_80093844:
    cmpwi r3, 0x4
    bge CardSave_Tick_CaptureAndStart_L_80093C00
    b CardSave_Tick_CaptureAndStart_L_800938C8
    CardSave_Tick_CaptureAndStart_L_80093850:
    cmpwi r3, 0x64
    bge CardSave_Tick_CaptureAndStart_L_80093C00
    cmpwi r3, 0x7
    beq CardSave_Tick_CaptureAndStart_L_80093868
    b CardSave_Tick_CaptureAndStart_L_80093C00
    b CardSave_Tick_CaptureAndStart_L_80093C00
    CardSave_Tick_CaptureAndStart_L_80093868:
    lbz r0, lbl_806D1228(r13)
    cmplwi r0, 0x1
    beq CardSave_Tick_CaptureAndStart_L_80093C08
    bl OSGetTick
    li r5, 0x0
    li r4, 0x1
    li r0, 0x5
    stw r3, lbl_806D122C(r13)
    stw r5, lbl_806D1210(r13)
    stb r4, lbl_806D122A(r13)
    stb r5, lbl_806D121C(r13)
    stw r0, lbl_806CF0E4(r13)
    bl ServiceLatch_CheckTriggered
    clrlwi. r0, r3, 24
    bne CardSave_Tick_CaptureAndStart_L_800938B0
    li r0, 0x1
    stw r0, lbl_806D1210(r13)
    b CardSave_Tick_CaptureAndStart_L_80093C08
    CardSave_Tick_CaptureAndStart_L_800938B0:
    li r0, 0x0
    stb r0, lbl_806D1227(r13)
    stw r0, lbl_806D1220(r13)
    stw r0, lbl_806CF0D8(r13)
    bl card_rw_state_machine
    b CardSave_Tick_CaptureAndStart_L_80093C08
    CardSave_Tick_CaptureAndStart_L_800938C8:
    lis r4, g_playerData@ha
    lis r3, lbl_80598A60@ha
    addi r14, r4, g_playerData@l
    lwz r29, 0x54(r14)
    addi r28, r3, lbl_80598A60@l
    lwz r0, 0x4c(r14)
    addi r31, r28, 0x90
    stw r29, 0x24(r1)
    lwz r29, 0x58(r14)
    stw r0, 0xdc(r28)
    lwz r0, 0x24(r1)
    stw r29, 0xc(r1)
    lwz r29, 0x5c(r14)
    stw r0, 0xe4(r28)
    lwz r0, 0xc(r1)
    stw r29, 0x10(r1)
    lwz r29, 0x60(r14)
    stw r0, 0xe8(r28)
    lwz r0, 0x10(r1)
    stw r29, 0x14(r1)
    lwz r29, 0x64(r14)
    stw r0, 0xec(r28)
    lwz r0, 0x14(r1)
    stw r29, 0x18(r1)
    li r29, 0x0
    lwz r27, 0x0(r14)
    lwz r26, 0x4(r14)
    lwz r25, 0x8(r14)
    lbz r24, 0xc(r14)
    lbz r23, 0xd(r14)
    lhz r22, 0xe(r14)
    lhz r21, 0x10(r14)
    lwz r20, 0x14(r14)
    lbz r19, 0x18(r14)
    lbz r18, 0x19(r14)
    lbz r17, 0x1a(r14)
    lwz r16, 0x1c(r14)
    lwz r15, 0x20(r14)
    lwz r12, 0x24(r14)
    lwz r11, 0x28(r14)
    lwz r10, 0x2c(r14)
    lwz r9, 0x30(r14)
    lwz r8, 0x34(r14)
    lwz r7, 0x38(r14)
    lwz r6, 0x3c(r14)
    lwz r5, 0x40(r14)
    lwz r4, 0x44(r14)
    lwz r3, 0x48(r14)
    lwz r30, 0x50(r14)
    stb r29, 0x199(r14)
    li r29, 0x32
    stw r0, 0xf0(r28)
    lwz r0, 0x18(r1)
    stb r29, 0x198(r14)
    li r29, 0x1
    stb r29, 0x64(r28)
    stw r27, 0x90(r28)
    stw r26, 0x94(r28)
    stw r25, 0x98(r28)
    stb r24, 0x9c(r28)
    stb r23, 0x9d(r28)
    sth r22, 0x9e(r28)
    sth r21, 0xa0(r28)
    stw r20, 0xa4(r28)
    stb r19, 0xa8(r28)
    stb r18, 0xa9(r28)
    stb r17, 0xaa(r28)
    stw r16, 0xac(r28)
    stw r15, 0xb0(r28)
    stw r12, 0xb4(r28)
    stw r11, 0xb8(r28)
    stw r10, 0xbc(r28)
    stw r9, 0xc0(r28)
    stw r8, 0xc4(r28)
    stw r7, 0xc8(r28)
    stw r6, 0xcc(r28)
    stw r5, 0xd0(r28)
    stw r4, 0xd4(r28)
    stw r3, 0xd8(r28)
    stw r30, 0xe0(r28)
    stw r0, 0xf4(r28)
    lwz r22, 0x68(r14)
    addi r3, r31, 0xa8
    lwz r21, 0x6c(r14)
    addi r4, r14, 0xa8
    lwz r20, 0x70(r14)
    li r5, 0x79
    lwz r19, 0x74(r14)
    lwz r18, 0x78(r14)
    lwz r17, 0x7c(r14)
    lwz r16, 0x80(r14)
    lwz r15, 0x84(r14)
    lwz r12, 0x88(r14)
    lwz r11, 0x8c(r14)
    lwz r10, 0x90(r14)
    lwz r9, 0x94(r14)
    lwz r8, 0x98(r14)
    lwz r7, 0x9c(r14)
    lwz r6, 0xa0(r14)
    lwz r0, 0xa4(r14)
    stw r22, 0x68(r31)
    stw r21, 0x6c(r31)
    stw r20, 0x70(r31)
    stw r19, 0x74(r31)
    stw r18, 0x78(r31)
    stw r17, 0x7c(r31)
    stw r16, 0x80(r31)
    stw r15, 0x84(r31)
    stw r12, 0x88(r31)
    stw r11, 0x8c(r31)
    stw r10, 0x90(r31)
    stw r9, 0x94(r31)
    stw r8, 0x98(r31)
    stw r7, 0x9c(r31)
    stw r6, 0xa0(r31)
    stw r0, 0xa4(r31)
    bl fn_80270C48
    lis r4, g_playerData@ha
    addi r3, r31, 0x121
    addi r4, r4, g_playerData@l
    li r5, 0x69
    addi r4, r4, 0x121
    bl fn_80270C48
    lis r3, g_playerData@ha
    lbz r0, 0x198(r14)
    addi r16, r3, g_playerData@l
    lbz r20, 0x199(r14)
    lbz r15, 0x1d8(r16)
    stw r0, 0x1c(r1)
    lwz r0, 0x1ce(r16)
    stw r15, 0x28(r1)
    lbz r15, 0x1d9(r16)
    stw r0, 0x1ce(r31)
    lwz r0, 0x28(r1)
    stw r15, 0x20(r1)
    lwz r17, 0x18c(r16)
    lwz r18, 0x190(r16)
    lwz r19, 0x194(r16)
    lbz r21, 0x19a(r16)
    lbz r22, 0x19b(r16)
    lbz r23, 0x19c(r16)
    lbz r24, 0x19d(r16)
    lbz r25, 0x19e(r16)
    lbz r26, 0x19f(r16)
    lbz r27, 0x1a0(r16)
    lwz r28, 0x1a4(r16)
    lbz r29, 0x1a8(r16)
    lwz r30, 0x1ac(r16)
    lbz r12, 0x1b0(r16)
    lbz r11, 0x1b1(r16)
    lwz r10, 0x1b4(r16)
    lbz r9, 0x1b8(r16)
    lbz r8, 0x1b9(r16)
    lwz r7, 0x1ba(r16)
    lwz r6, 0x1be(r16)
    lwz r5, 0x1c2(r16)
    lwz r4, 0x1c6(r16)
    lwz r3, 0x1ca(r16)
    lwz r14, 0x1d4(r16)
    lbz r15, 0x1da(r16)
    lwz r16, 0x1c(r1)
    stb r0, 0x1d8(r31)
    lwz r0, 0x20(r1)
    stw r17, 0x18c(r31)
    stw r18, 0x190(r31)
    stw r19, 0x194(r31)
    stb r16, 0x198(r31)
    stb r20, 0x199(r31)
    stb r21, 0x19a(r31)
    stb r22, 0x19b(r31)
    stb r23, 0x19c(r31)
    stb r24, 0x19d(r31)
    stb r25, 0x19e(r31)
    stb r26, 0x19f(r31)
    stb r27, 0x1a0(r31)
    stw r28, 0x1a4(r31)
    stb r29, 0x1a8(r31)
    stw r30, 0x1ac(r31)
    stb r12, 0x1b0(r31)
    stb r11, 0x1b1(r31)
    stw r10, 0x1b4(r31)
    stb r9, 0x1b8(r31)
    stb r8, 0x1b9(r31)
    stw r7, 0x1ba(r31)
    stw r6, 0x1be(r31)
    stw r5, 0x1c2(r31)
    stw r4, 0x1c6(r31)
    stw r3, 0x1ca(r31)
    stw r14, 0x1d4(r31)
    stb r0, 0x1d9(r31)
    stb r15, 0x1da(r31)
    bl card_backup
    li r4, 0x1
    li r3, 0x0
    li r0, 0x5
    stw r4, lbl_806D124C(r13)
    stw r3, lbl_806D1210(r13)
    stb r4, lbl_806D122A(r13)
    stb r3, lbl_806D121C(r13)
    stw r0, lbl_806CF0E4(r13)
    bl Sci2Card_Singleton_Get
    bl Sci2Card_SendCmdCleaning
    li r0, 0x4
    stb r3, lbl_806D121C(r13)
    stw r0, lbl_806CF0D0(r13)
    b CardSave_Tick_CaptureAndStart_L_80093C08
    CardSave_Tick_CaptureAndStart_L_80093C00:
    li r0, 0x1
    stb r0, 0x8(r1)
    CardSave_Tick_CaptureAndStart_L_80093C08:
    lbz r3, 0x8(r1)
    b CardSave_Tick_CaptureAndStart_L_80093C14
    CardSave_Tick_CaptureAndStart_L_80093C10:
    li r3, 0x0
    CardSave_Tick_CaptureAndStart_L_80093C14:
    lmw r14, 0x38(r1)
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

