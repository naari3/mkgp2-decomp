/* === extracted from auto_Backup_LoadFromMemor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void OSGetTime();
extern void fn_80289A90();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1120;
extern unsigned int lbl_806D1128;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80598A60[];

/* --- function index (1 fns, .text 0x80074190..0x80074370) ---
 * [  0] 0x80074190 size:0x1E0   global Backup_LoadFromMemoryOrInit
 */

/* --- forward decls --- */
asm void Backup_LoadFromMemoryOrInit(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Backup_LoadFromMemoryOrInit[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Backup_LoadFromMemoryOrInit = {
    (void *)&Backup_LoadFromMemoryOrInit, 0x000001E0, (void *)extab_Backup_LoadFromMemoryOrInit
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Backup_LoadFromMemoryOrInit(void) { /* 0x80074190 size:0x1E0 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    stw r30, 0x48(r1)
    lbz r0, lbl_806D1120(r13)
    cmplwi r0, 0x0
    bne Backup_LoadFromMemoryOrInit_L_800741B8
    li r3, 0x0
    b Backup_LoadFromMemoryOrInit_L_80074358
    Backup_LoadFromMemoryOrInit_L_800741B8:
    lwz r0, lbl_806D1128(r13)
    cmpwi r0, 0x0
    beq Backup_LoadFromMemoryOrInit_L_800741CC
    li r3, 0x0
    b Backup_LoadFromMemoryOrInit_L_80074358
    Backup_LoadFromMemoryOrInit_L_800741CC:
    li r6, 0x0
    lis r3, lbl_80598A60@ha
    addi r5, r3, lbl_80598A60@l
    li r4, 0x1
    li r3, 0x2
    extsb. r0, r6
    stb r6, 0x20(r5)
    stb r4, 0x21(r5)
    stb r3, 0x22(r5)
    stb r4, 0x25(r5)
    stb r6, 0x2a(r5)
    stb r6, 0x28(r5)
    stb r6, 0x29(r5)
    bne Backup_LoadFromMemoryOrInit_L_80074218
    stb r4, 0x24(r5)
    stb r4, 0x23(r5)
    stb r4, 0x27(r5)
    stb r4, 0x26(r5)
    b Backup_LoadFromMemoryOrInit_L_80074248
    Backup_LoadFromMemoryOrInit_L_80074218:
    cmpwi r6, 0x1
    bne Backup_LoadFromMemoryOrInit_L_80074234
    stb r4, 0x24(r5)
    stb r4, 0x23(r5)
    stb r6, 0x27(r5)
    stb r4, 0x26(r5)
    b Backup_LoadFromMemoryOrInit_L_80074248
    Backup_LoadFromMemoryOrInit_L_80074234:
    stb r6, 0x24(r5)
    stb r6, 0x23(r5)
    stb r6, 0x27(r5)
    stb r4, 0x28(r5)
    stb r6, 0x26(r5)
    Backup_LoadFromMemoryOrInit_L_80074248:
    lis r3, lbl_80598A60@ha
    li r30, 0x60
    addi r31, r3, lbl_80598A60@l
    li r5, 0x0
    li r12, 0xc
    li r8, 0x3f
    li r4, 0x1
    li r11, 0x8
    li r10, 0x78
    li r9, 0x55
    li r7, 0x7fff
    li r6, 0x1ff
    li r0, -0x10
    stb r30, 0x2b(r31)
    addi r3, r1, 0x8
    stb r12, 0x2c(r31)
    stb r11, 0x2d(r31)
    stb r10, 0x2e(r31)
    stb r9, 0x2f(r31)
    stb r8, 0x30(r31)
    stb r8, 0x31(r31)
    stw r7, 0x34(r31)
    stw r6, 0x38(r31)
    stw r5, 0x40(r31)
    stw r5, 0x3c(r31)
    stb r4, 0x44(r31)
    stb r4, 0x45(r31)
    stw r12, 0x48(r31)
    stw r0, 0x4c(r31)
    stb r5, 0x50(r31)
    stb r5, 0x51(r31)
    stb r5, 0x52(r31)
    stb r5, 0x53(r31)
    stb r5, 0x54(r31)
    stb r5, 0x55(r31)
    stb r5, 0x56(r31)
    stb r5, 0x57(r31)
    stb r5, 0x58(r31)
    stb r5, 0x59(r31)
    stb r5, 0x5a(r31)
    stb r5, 0x5b(r31)
    stb r5, 0x5c(r31)
    stb r5, 0x5d(r31)
    stb r5, 0x5e(r31)
    stb r5, 0x5f(r31)
    stb r5, 0x60(r31)
    stb r5, 0x64(r31)
    stw r5, 0x26c(r31)
    stb r5, 0x270(r31)
    bl fn_80289A90
    lis r3, lbl_80598A60@ha
    lwz r7, 0x18(r1)
    addi r6, r3, lbl_80598A60@l
    lwz r5, 0x20(r1)
    li r4, 0xf
    li r3, 0x0
    li r0, -0x1
    stw r7, 0xc(r6)
    stw r5, 0x10(r6)
    stb r4, 0x0(r6)
    stw r3, 0x8(r6)
    stw r0, 0x4(r6)
    bl OSGetTime
    lis r5, lbl_80598A60@ha
    addi r5, r5, lbl_80598A60@l
    stw r3, 0x18(r5)
    li r3, 0x1
    stw r4, 0x1c(r5)
    Backup_LoadFromMemoryOrInit_L_80074358:
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}
