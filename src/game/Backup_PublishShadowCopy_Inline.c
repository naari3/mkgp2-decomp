/* === extracted from auto_Backup_PublishShadow_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_80288210();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1120;
extern unsigned int lbl_806D1128;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80598A60[];
extern unsigned int lbl_8059F480[];

/* --- function index (1 fns, .text 0x80075470..0x80075690) ---
 * [  0] 0x80075470 size:0x220   global Backup_PublishShadowCopy_Inline
 */

/* --- forward decls --- */
asm void Backup_PublishShadowCopy_Inline(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Backup_PublishShadowCopy_Inline[8] = {
    0x90, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Backup_PublishShadowCopy_Inline = {
    (void *)&Backup_PublishShadowCopy_Inline, 0x00000220, (void *)extab_Backup_PublishShadowCopy_Inline
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Backup_PublishShadowCopy_Inline(void) { /* 0x80075470 size:0x220 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stmw r14, 0x18(r1)
    lbz r0, lbl_806D1120(r13)
    cmplwi r0, 0x0
    bne Backup_PublishShadowCopy_Inline_L_80075494
    li r3, 0x0
    b Backup_PublishShadowCopy_Inline_L_8007567C
    Backup_PublishShadowCopy_Inline_L_80075494:
    lwz r0, lbl_806D1128(r13)
    cmpwi r0, 0x0
    beq Backup_PublishShadowCopy_Inline_L_800754A8
    li r3, 0x0
    b Backup_PublishShadowCopy_Inline_L_8007567C
    Backup_PublishShadowCopy_Inline_L_800754A8:
    lis r4, lbl_80598A60@ha
    li r3, 0x0
    addi r4, r4, lbl_80598A60@l
    bl fn_80288210
    lis r4, lbl_80598A60@ha
    lis r3, lbl_8059F480@ha
    addi r16, r4, lbl_80598A60@l
    lwz r15, 0x57(r16)
    addi r18, r3, lbl_8059F480@l
    lbz r0, 0x52(r16)
    addi r4, r18, 0x60
    stw r15, 0xc(r1)
    addi r3, r16, 0x60
    lwz r15, 0x5b(r16)
    stb r0, 0x52(r18)
    lwz r0, 0xc(r1)
    stw r15, 0x8(r1)
    lbz r17, 0x0(r16)
    stw r0, 0x57(r18)
    lwz r0, 0x8(r1)
    lwz r19, 0x4(r16)
    lwz r20, 0x8(r16)
    lwz r21, 0xc(r16)
    lwz r22, 0x10(r16)
    lwz r24, 0x18(r16)
    lwz r23, 0x1c(r16)
    lwz r25, 0x20(r16)
    lwz r26, 0x24(r16)
    lhz r27, 0x28(r16)
    lbz r28, 0x2a(r16)
    lwz r29, 0x2b(r16)
    lhz r30, 0x2f(r16)
    lbz r31, 0x31(r16)
    lwz r12, 0x34(r16)
    lwz r11, 0x38(r16)
    lwz r10, 0x3c(r16)
    lwz r9, 0x40(r16)
    lwz r8, 0x44(r16)
    lwz r7, 0x48(r16)
    lwz r6, 0x4c(r16)
    lhz r5, 0x50(r16)
    lwz r14, 0x53(r16)
    lhz r15, 0x5f(r16)
    stw r0, 0x5b(r18)
    li r0, 0x42
    stb r17, 0x0(r18)
    stw r19, 0x4(r18)
    stw r20, 0x8(r18)
    stw r21, 0xc(r18)
    stw r22, 0x10(r18)
    stw r23, 0x1c(r18)
    stw r24, 0x18(r18)
    stw r25, 0x20(r18)
    stw r26, 0x24(r18)
    sth r27, 0x28(r18)
    stb r28, 0x2a(r18)
    stw r29, 0x2b(r18)
    sth r30, 0x2f(r18)
    stb r31, 0x31(r18)
    stw r12, 0x34(r18)
    stw r11, 0x38(r18)
    stw r10, 0x3c(r18)
    stw r9, 0x40(r18)
    stw r8, 0x44(r18)
    stw r7, 0x48(r18)
    stw r6, 0x4c(r18)
    sth r5, 0x50(r18)
    stw r14, 0x53(r18)
    sth r15, 0x5f(r18)
    mtctr r0
    Backup_PublishShadowCopy_Inline_L_800755C0:
    lwz r5, 0x4(r3)
    lwzu r0, 0x8(r3)
    stw r5, 0x4(r4)
    stwu r0, 0x8(r4)
    bdnz Backup_PublishShadowCopy_Inline_L_800755C0
    lis r4, lbl_80598A60@ha
    lis r3, lbl_8059F480@ha
    addi r4, r4, lbl_80598A60@l
    li r0, 0x4d
    addi r3, r3, lbl_8059F480@l
    addi r6, r3, 0x270
    addi r4, r4, 0x270
    mtctr r0
    Backup_PublishShadowCopy_Inline_L_800755F4:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r6)
    stwu r0, 0x8(r6)
    bdnz Backup_PublishShadowCopy_Inline_L_800755F4
    lwz r5, 0x4(r4)
    lis r4, lbl_80598A60@ha
    lis r3, lbl_8059F480@ha
    li r0, 0x5a0
    addi r4, r4, lbl_80598A60@l
    stw r5, 0x4(r6)
    addi r3, r3, lbl_8059F480@l
    addi r5, r3, 0x4dc
    addi r4, r4, 0x4dc
    mtctr r0
    Backup_PublishShadowCopy_Inline_L_80075630:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r5)
    stwu r0, 0x8(r5)
    bdnz Backup_PublishShadowCopy_Inline_L_80075630
    lis r4, lbl_80598A60@ha
    lis r3, lbl_8059F480@ha
    addi r4, r4, lbl_80598A60@l
    li r0, 0x708
    addi r3, r3, lbl_8059F480@l
    addi r5, r3, 0x31dc
    addi r4, r4, 0x31dc
    mtctr r0
    Backup_PublishShadowCopy_Inline_L_80075664:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r5)
    stwu r0, 0x8(r5)
    bdnz Backup_PublishShadowCopy_Inline_L_80075664
    li r3, 0x1
    Backup_PublishShadowCopy_Inline_L_8007567C:
    lmw r14, 0x18(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

