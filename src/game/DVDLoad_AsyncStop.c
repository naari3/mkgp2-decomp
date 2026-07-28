/* === extracted from auto_DVDLoad_AsyncStop_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_802C14B8();
extern void fn_802C352C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1150;
extern unsigned int lbl_806D1154;
extern unsigned int lbl_806D1158;
extern unsigned int lbl_806D115C;

/* --- function index (1 fns, .text 0x8007DC38..0x8007DC8C) ---
 * [  0] 0x8007DC38 size:0x54    global DVDLoad_AsyncStop
 */

/* --- forward decls --- */
asm void DVDLoad_AsyncStop(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_DVDLoad_AsyncStop[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_DVDLoad_AsyncStop = {
    (void *)&DVDLoad_AsyncStop, 0x00000054, (void *)extab_DVDLoad_AsyncStop
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void DVDLoad_AsyncStop(void) { /* 0x8007DC38 size:0x54 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r12, lbl_806D1154(r13)
    cmplwi r12, 0x0
    beq DVDLoad_AsyncStop_L_8007DC60
    lwz r3, lbl_806D115C(r13)
    lwz r4, lbl_806D1158(r13)
    mtctr r12
    bctrl
    DVDLoad_AsyncStop_L_8007DC60:
    li r3, 0x0
    bl fn_802C352C
    li r0, 0x0
    li r3, -0x1
    stw r0, lbl_806D1150(r13)
    stw r0, lbl_806D1154(r13)
    bl fn_802C14B8
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

