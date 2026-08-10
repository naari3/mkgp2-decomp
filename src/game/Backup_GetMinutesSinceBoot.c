/* === extracted from auto_Backup_GetMinutesSin_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void OSGetTime();
extern void fn_8025CE88();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80598A60[];

/* --- function index (1 fns, .text 0x8007458C..0x800746A8) ---
 * [  0] 0x8007458C size:0x11C   global Backup_GetMinutesSinceBoot
 */

/* --- forward decls --- */
asm void Backup_GetMinutesSinceBoot(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Backup_GetMinutesSinceBoot[8] = {
    0x30, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Backup_GetMinutesSinceBoot = {
    (void *)&Backup_GetMinutesSinceBoot, 0x0000011C, (void *)extab_Backup_GetMinutesSinceBoot
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Backup_GetMinutesSinceBoot(void) { /* 0x8007458C size:0x11C */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    lis r4, lbl_80598A60@ha
    stw r0, 0x74(r1)
    addi r4, r4, lbl_80598A60@l
    addi r5, r1, 0x30
    stmw r26, 0x58(r1)
    mr r31, r3
    lwz r3, 0x18(r4)
    lwz r4, 0x1c(r4)
    bl fn_8025CE88
    bl OSGetTime
    addi r5, r1, 0x8
    bl fn_8025CE88
    lwz r6, 0x3c(r1)
    lis r4, 0x29
    lis r5, 0x1
    lwz r3, 0x14(r1)
    subi r11, r4, 0x2180
    lwz r4, 0x18(r1)
    subi r7, r6, 0x1
    addi r28, r5, 0x5180
    subi r6, r3, 0x1
    lwz r0, 0x40(r1)
    mullw r29, r7, r28
    lis r3, 0x1ea
    lwz r27, 0x38(r1)
    lwz r7, 0x10(r1)
    addi r12, r3, 0x6e00
    lwz r5, 0x44(r1)
    mullw r10, r0, r11
    lwz r26, 0x34(r1)
    lwz r8, 0xc(r1)
    subi r30, r5, 0x7d0
    lwz r3, 0x1c(r1)
    lwz r0, 0x30(r1)
    mullw r4, r4, r11
    subi r5, r3, 0x7d0
    add r10, r10, r29
    lwz r9, 0x8(r1)
    lis r3, 0x91a3
    subi r3, r3, 0x4c3b
    mullw r6, r6, r28
    add r4, r4, r6
    mulli r6, r7, 0xe10
    mulli r11, r27, 0xe10
    add r4, r4, r6
    add r7, r10, r11
    mulli r10, r26, 0x3c
    mulli r6, r8, 0x3c
    add r7, r7, r10
    add r4, r4, r6
    add r6, r7, r0
    add r0, r4, r9
    mullw r4, r5, r12
    mullw r7, r30, r12
    add r0, r4, r0
    add r5, r7, r6
    subf r0, r5, r0
    mulhwu r0, r3, r0
    srwi r3, r0, 11
    subf r0, r31, r3
    orc r3, r3, r31
    lmw r26, 0x58(r1)
    srwi r0, r0, 1
    subf r0, r0, r3
    srwi r3, r0, 31
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}


