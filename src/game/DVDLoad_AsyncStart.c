/* === extracted from auto_DVDLoad_AsyncStart_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_802C352C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1150;
extern unsigned int lbl_806D1154;
extern unsigned int lbl_806D1158;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int DVDLoad_DrawDoneCallback[];

/* --- function index (1 fns, .text 0x8007DC8C..0x8007DD00) ---
 * [  0] 0x8007DC8C size:0x74    global DVDLoad_AsyncStart
 */

/* --- forward decls --- */
asm void DVDLoad_AsyncStart(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_DVDLoad_AsyncStart[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_DVDLoad_AsyncStart = {
    (void *)&DVDLoad_AsyncStart, 0x00000074, (void *)extab_DVDLoad_AsyncStart
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void DVDLoad_AsyncStart(void) { /* 0x8007DC8C size:0x74 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r5
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr. r29, r3
    beq DVDLoad_AsyncStart_L_8007DCC0
    lwz r0, lbl_806D1150(r13)
    cmplwi r0, 0x0
    beq DVDLoad_AsyncStart_L_8007DCC8
    DVDLoad_AsyncStart_L_8007DCC0:
    li r3, 0x0
    b DVDLoad_AsyncStart_L_8007DCE4
    DVDLoad_AsyncStart_L_8007DCC8:
    lis r3, DVDLoad_DrawDoneCallback@ha
    addi r3, r3, DVDLoad_DrawDoneCallback@l
    bl fn_802C352C
    stw r29, lbl_806D1150(r13)
    li r3, 0x1
    stw r30, lbl_806D1154(r13)
    stw r31, lbl_806D1158(r13)
    DVDLoad_AsyncStart_L_8007DCE4:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

