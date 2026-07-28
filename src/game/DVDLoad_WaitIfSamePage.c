/* === extracted from auto_DVDLoad_WaitIfSamePa_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void OSGetTick();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1140;
extern unsigned int lbl_806D1144;

/* --- function index (1 fns, .text 0x8007E2B8..0x8007E344) ---
 * [  0] 0x8007E2B8 size:0x8C    global DVDLoad_WaitIfSamePage
 */

/* --- forward decls --- */
asm void DVDLoad_WaitIfSamePage(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_DVDLoad_WaitIfSamePage[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_DVDLoad_WaitIfSamePage = {
    (void *)&DVDLoad_WaitIfSamePage, 0x0000008C, (void *)extab_DVDLoad_WaitIfSamePage
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void DVDLoad_WaitIfSamePage(void) { /* 0x8007E2B8 size:0x8C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    srwi r0, r3, 10
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    li r29, 0x0
    lwz r4, lbl_806D1140(r13)
    cmplw r4, r0
    bne DVDLoad_WaitIfSamePage_L_8007E324
    lis r3, 0x431c
    lis r31, 0x8000
    subi r30, r3, 0x217d
    DVDLoad_WaitIfSamePage_L_8007E2F0:
    bl OSGetTick
    lwz r0, 0xf8(r31)
    lwz r4, lbl_806D1144(r13)
    srwi r0, r0, 2
    mulhwu r0, r30, r0
    subf r3, r4, r3
    slwi r3, r3, 3
    srwi r0, r0, 15
    divwu r0, r3, r0
    cmplwi r0, 0x42
    bge DVDLoad_WaitIfSamePage_L_8007E324
    addi r29, r29, 0x1
    b DVDLoad_WaitIfSamePage_L_8007E2F0
    DVDLoad_WaitIfSamePage_L_8007E324:
    lwz r0, 0x24(r1)
    mr r3, r29
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

