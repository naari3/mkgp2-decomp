/* === extracted from auto_Backup_ClearAll_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Backup_ClearHiScores();
extern void Backup_LoadFromMemoryOrInit();
extern void OperationClockState_CommitDelta();
extern void OperationClockState_Reset();
extern void OperationClockState_StartTick();
extern void PlayStats_Clear();
extern void memset();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1120;
extern unsigned int lbl_806D1128;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80598A60[];
extern unsigned int lbl_805A5EA0[];

/* --- function index (1 fns, .text 0x800751F0..0x8007526C) ---
 * [  0] 0x800751F0 size:0x7C    global Backup_ClearAll
 */

/* --- forward decls --- */
asm void Backup_ClearAll(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Backup_ClearAll[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Backup_ClearAll = {
    (void *)&Backup_ClearAll, 0x0000007C, (void *)extab_Backup_ClearAll
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Backup_ClearAll(void) { /* 0x800751F0 size:0x7C */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    bl Backup_LoadFromMemoryOrInit
    bl Backup_ClearHiScores
    lbz r0, lbl_806D1120(r13)
    cmplwi r0, 0x0
    beq Backup_ClearAll_L_8007525C
    lwz r0, lbl_806D1128(r13)
    cmpwi r0, 0x0
    bne Backup_ClearAll_L_8007525C
    lis r3, lbl_80598A60@ha
    li r4, 0x0
    addi r3, r3, lbl_80598A60@l
    li r5, 0x26c
    addi r3, r3, 0x274
    bl memset
    bl PlayStats_Clear
    lis r3, lbl_805A5EA0@ha
    addi r3, r3, lbl_805A5EA0@l
    bl OperationClockState_CommitDelta
    lis r3, lbl_805A5EA0@ha
    addi r3, r3, lbl_805A5EA0@l
    bl OperationClockState_Reset
    lis r3, lbl_805A5EA0@ha
    addi r3, r3, lbl_805A5EA0@l
    bl OperationClockState_StartTick
    Backup_ClearAll_L_8007525C:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

