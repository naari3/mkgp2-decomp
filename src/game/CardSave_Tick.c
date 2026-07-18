/* === extracted from auto_CardSave_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CardSave_Tick_CaptureAndStart();
extern void CardSave_Tick_PollCleaningResult();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D124C;

/* --- function index (1 fns, .text 0x800934B0..0x800934F0) ---
 * [  0] 0x800934B0 size:0x40    global CardSave_Tick
 */

/* --- forward decls --- */
asm void CardSave_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardSave_Tick[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardSave_Tick = {
    (void *)&CardSave_Tick, 0x00000040, (void *)extab_CardSave_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardSave_Tick(void) { /* 0x800934B0 size:0x40 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r3, 0x0
    stw r0, 0x14(r1)
    lwz r0, lbl_806D124C(r13)
    cmpwi r0, 0x0
    bne CardSave_Tick_L_800934D4
    bl CardSave_Tick_CaptureAndStart
    b CardSave_Tick_L_800934E0
    CardSave_Tick_L_800934D4:
    cmpwi r0, 0x1
    bne CardSave_Tick_L_800934E0
    bl CardSave_Tick_PollCleaningResult
    CardSave_Tick_L_800934E0:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

