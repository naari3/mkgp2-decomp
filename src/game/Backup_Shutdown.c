/* === extracted from auto_Backup_Shutdown_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void OperationClockState_CommitDelta();
extern void PlayStats_AddTotalPlaySeconds();
extern void PlayStats_PublishStatsBlockShadow();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1120;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_805A5EA0[];

/* --- function index (1 fns, .text 0x800758EC..0x8007593C) ---
 * [  0] 0x800758EC size:0x50    global Backup_Shutdown
 */

/* --- forward decls --- */
asm void Backup_Shutdown(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Backup_Shutdown[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Backup_Shutdown = {
    (void *)&Backup_Shutdown, 0x00000050, (void *)extab_Backup_Shutdown
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Backup_Shutdown(void) { /* 0x800758EC size:0x50 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lbz r0, lbl_806D1120(r13)
    cmplwi r0, 0x0
    beq Backup_Shutdown_L_8007592C
    lis r3, lbl_805A5EA0@ha
    addi r3, r3, lbl_805A5EA0@l
    bl OperationClockState_CommitDelta
    lis r3, lbl_805A5EA0@ha
    addi r3, r3, lbl_805A5EA0@l
    lwz r3, 0xc(r3)
    bl PlayStats_AddTotalPlaySeconds
    bl PlayStats_PublishStatsBlockShadow
    li r0, 0x0
    stb r0, lbl_806D1120(r13)
    Backup_Shutdown_L_8007592C:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


