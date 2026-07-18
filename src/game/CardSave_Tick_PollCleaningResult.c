/* === extracted from auto_CardSave_Tick_PollCl_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Backup_PublishShadowCopy_Inline();
extern void Sci2Card_GetResponseStatus();
extern void Sci2Card_IsIdleOrExhausted();
extern void Sci2Card_IsRetryExhausted();
extern void Sci2Card_IsStatus2A();
extern void Sci2Card_IsStatus2Five();
extern void Sci2Card_IsStatus2One();
extern void Sci2Card_IsStatus2Three();
extern void Sci2Card_IsStatus2Two();
extern void Sci2Card_IsStatus3Five();
extern void Sci2Card_IsStatus3Zero();
extern void Sci2Card_IsStatusOkNonTerm();
extern void Sci2Card_ResetRetryCount();
extern void Sci2Card_SendCmdCleaning();
extern void Sci2Card_Singleton_Get();
extern void ServiceLatch_CheckTriggered();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806CF0D0;
extern unsigned int lbl_806CF0DC;
extern unsigned int lbl_806D1210;
extern unsigned int lbl_806D1214;
extern unsigned int lbl_806D121C;
extern unsigned int lbl_806D1224;
extern unsigned int lbl_806D1225;
extern unsigned int lbl_806D1226;
extern unsigned int lbl_806D1229;
extern unsigned int lbl_806D122A;
extern unsigned int lbl_806D122B;
extern unsigned int lbl_806D1248;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80598A60[];

/* --- function index (1 fns, .text 0x800934F0..0x800937D4) ---
 * [  0] 0x800934F0 size:0x2E4   global CardSave_Tick_PollCleaningResult
 */

/* --- forward decls --- */
asm void CardSave_Tick_PollCleaningResult(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardSave_Tick_PollCleaningResult[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardSave_Tick_PollCleaningResult = {
    (void *)&CardSave_Tick_PollCleaningResult, 0x000002E4, (void *)extab_CardSave_Tick_PollCleaningResult
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardSave_Tick_PollCleaningResult(void) { /* 0x800934F0 size:0x2E4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    bl ServiceLatch_CheckTriggered
    clrlwi. r0, r3, 24
    bne CardSave_Tick_PollCleaningResult_L_8009351C
    li r0, 0x1
    li r3, 0x1
    stw r0, lbl_806D1210(r13)
    b CardSave_Tick_PollCleaningResult_L_800937C0
    CardSave_Tick_PollCleaningResult_L_8009351C:
    bl Sci2Card_Singleton_Get
    lwz r0, lbl_806D1210(r13)
    mr r31, r3
    cmpwi r0, 0x0
    beq CardSave_Tick_PollCleaningResult_L_80093538
    li r3, 0x1
    b CardSave_Tick_PollCleaningResult_L_800937C0
    CardSave_Tick_PollCleaningResult_L_80093538:
    lbz r0, lbl_806D121C(r13)
    cmplwi r0, 0x0
    bne CardSave_Tick_PollCleaningResult_L_80093554
    bl Sci2Card_SendCmdCleaning
    stb r3, lbl_806D121C(r13)
    li r3, 0x0
    b CardSave_Tick_PollCleaningResult_L_800937C0
    CardSave_Tick_PollCleaningResult_L_80093554:
    bl Sci2Card_IsIdleOrExhausted
    clrlwi. r0, r3, 24
    bne CardSave_Tick_PollCleaningResult_L_80093568
    li r3, 0x0
    b CardSave_Tick_PollCleaningResult_L_800937C0
    CardSave_Tick_PollCleaningResult_L_80093568:
    bl Sci2Card_Singleton_Get
    addi r4, r1, 0xb
    addi r5, r1, 0xc
    addi r6, r1, 0xd
    bl Sci2Card_GetResponseStatus
    mr r3, r31
    bl Sci2Card_IsStatusOkNonTerm
    clrlwi. r0, r3, 24
    bne CardSave_Tick_PollCleaningResult_L_80093728
    lbz r0, lbl_806D1248(r13)
    cmplwi r0, 0x0
    bne CardSave_Tick_PollCleaningResult_L_800936D0
    bl Sci2Card_Singleton_Get
    li r0, 0x0
    mr r31, r3
    stw r0, lbl_806D1210(r13)
    bl Sci2Card_IsStatus3Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardSave_Tick_PollCleaningResult_L_800935C0
    li r0, 0x2
    stw r0, lbl_806D1210(r13)
    CardSave_Tick_PollCleaningResult_L_800935C0:
    mr r3, r31
    bl Sci2Card_IsRetryExhausted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardSave_Tick_PollCleaningResult_L_800935DC
    li r0, 0x65
    stw r0, lbl_806D1210(r13)
    CardSave_Tick_PollCleaningResult_L_800935DC:
    mr r3, r31
    bl Sci2Card_IsStatus2Two
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardSave_Tick_PollCleaningResult_L_800935F8
    li r0, 0x66
    stw r0, lbl_806D1210(r13)
    CardSave_Tick_PollCleaningResult_L_800935F8:
    mr r3, r31
    bl Sci2Card_IsStatus2One
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardSave_Tick_PollCleaningResult_L_80093614
    li r0, 0x67
    stw r0, lbl_806D1210(r13)
    CardSave_Tick_PollCleaningResult_L_80093614:
    mr r3, r31
    bl Sci2Card_IsStatus2Three
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardSave_Tick_PollCleaningResult_L_80093630
    li r0, 0x68
    stw r0, lbl_806D1210(r13)
    CardSave_Tick_PollCleaningResult_L_80093630:
    mr r3, r31
    bl Sci2Card_IsStatus2Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardSave_Tick_PollCleaningResult_L_8009364C
    li r0, 0x69
    stw r0, lbl_806D1210(r13)
    CardSave_Tick_PollCleaningResult_L_8009364C:
    mr r3, r31
    bl Sci2Card_IsStatus2A
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardSave_Tick_PollCleaningResult_L_80093668
    li r0, 0x6a
    stw r0, lbl_806D1210(r13)
    CardSave_Tick_PollCleaningResult_L_80093668:
    lwz r0, lbl_806D1210(r13)
    cmpwi r0, 0x0
    bne CardSave_Tick_PollCleaningResult_L_800936A8
    mr r3, r31
    addi r4, r1, 0x8
    addi r5, r1, 0x9
    addi r6, r1, 0xa
    bl Sci2Card_GetResponseStatus
    lbz r0, 0xa(r1)
    cmplwi r0, 0x32
    bne CardSave_Tick_PollCleaningResult_L_800936A0
    li r0, 0x64
    stw r0, lbl_806D1210(r13)
    b CardSave_Tick_PollCleaningResult_L_800936A8
    CardSave_Tick_PollCleaningResult_L_800936A0:
    li r0, 0x1
    stw r0, lbl_806D1210(r13)
    CardSave_Tick_PollCleaningResult_L_800936A8:
    lwz r0, lbl_806D1210(r13)
    cmpwi r0, 0x2
    bne CardSave_Tick_PollCleaningResult_L_80093718
    lis r3, lbl_80598A60@ha
    li r0, 0x1
    addi r3, r3, lbl_80598A60@l
    stb r0, lbl_806D1226(r13)
    stb r0, 0x270(r3)
    bl Backup_PublishShadowCopy_Inline
    b CardSave_Tick_PollCleaningResult_L_80093718
    CardSave_Tick_PollCleaningResult_L_800936D0:
    mr r3, r31
    bl Sci2Card_IsStatus3Five
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardSave_Tick_PollCleaningResult_L_800936FC
    lis r3, lbl_80598A60@ha
    li r0, 0x1
    addi r3, r3, lbl_80598A60@l
    stb r0, lbl_806D1226(r13)
    stb r0, 0x270(r3)
    bl Backup_PublishShadowCopy_Inline
    CardSave_Tick_PollCleaningResult_L_800936FC:
    mr r3, r31
    bl Sci2Card_ResetRetryCount
    li r3, 0x0
    li r0, 0x1
    stb r3, lbl_806D122A(r13)
    stw r0, lbl_806D1210(r13)
    stb r3, lbl_806D122B(r13)
    CardSave_Tick_PollCleaningResult_L_80093718:
    li r0, 0x5
    li r3, 0x1
    stw r0, lbl_806CF0D0(r13)
    b CardSave_Tick_PollCleaningResult_L_800937C0
    CardSave_Tick_PollCleaningResult_L_80093728:
    mr r3, r31
    bl Sci2Card_IsStatus3Zero
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardSave_Tick_PollCleaningResult_L_800937BC
    lbz r0, lbl_806D1248(r13)
    li r4, 0x0
    li r3, 0x1
    stb r4, lbl_806D122A(r13)
    cmplwi r0, 0x1
    stw r3, lbl_806D1210(r13)
    stb r4, lbl_806D122B(r13)
    bne CardSave_Tick_PollCleaningResult_L_80093764
    li r3, 0x1
    b CardSave_Tick_PollCleaningResult_L_800937C0
    CardSave_Tick_PollCleaningResult_L_80093764:
    lbz r0, lbl_806D1225(r13)
    stb r3, lbl_806D1224(r13)
    cmplwi r0, 0x1
    bne CardSave_Tick_PollCleaningResult_L_80093778
    li r3, 0x4
    CardSave_Tick_PollCleaningResult_L_80093778:
    li r0, 0x0
    stw r3, lbl_806D1214(r13)
    mr r3, r31
    stb r0, lbl_806D1225(r13)
    bl Sci2Card_SendCmdCleaning
    li r4, 0x1
    li r0, 0x0
    stb r3, lbl_806D121C(r13)
    stb r4, lbl_806D1248(r13)
    stw r0, lbl_806D1210(r13)
    bl ServiceLatch_CheckTriggered
    clrlwi. r0, r3, 24
    beq CardSave_Tick_PollCleaningResult_L_800937B4
    li r0, 0x1
    stb r0, lbl_806D1229(r13)
    CardSave_Tick_PollCleaningResult_L_800937B4:
    li r0, 0x0
    stw r0, lbl_806CF0DC(r13)
    CardSave_Tick_PollCleaningResult_L_800937BC:
    li r3, 0x0
    CardSave_Tick_PollCleaningResult_L_800937C0:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

