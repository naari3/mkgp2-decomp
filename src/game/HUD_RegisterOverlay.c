/* === extracted from auto_HUD_RegisterOverlay_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_8021984C();
extern void fn_802437AC();
extern void fn_80253294();
extern void fn_80271340();
extern unsigned int lbl_806D0A60[2];
extern unsigned int lbl_806D0A68[2];
extern unsigned int s_clCDispInterface[2];

/* --- function index (1 fns, .text 0x80253B14..0x80253BE4) ---
 * [  0] 0x80253B14 size:0xD0    global HUD_RegisterOverlay
 */

/* --- forward decls --- */
asm void HUD_RegisterOverlay(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_HUD_RegisterOverlay[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_HUD_RegisterOverlay = {
    (void *)&HUD_RegisterOverlay, 0x000000D0, (void *)extab_HUD_RegisterOverlay
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void HUD_RegisterOverlay(void) { /* 0x80253B14 size:0xD0 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    slwi r0, r4, 2
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr r29, r3
    add r31, r29, r0
    lwz r0, 0x10(r31)
    cmplwi r0, 0x0
    bne HUD_RegisterOverlay_L_80253B50
    bl fn_80253294
    stw r3, 0x10(r31)
    HUD_RegisterOverlay_L_80253B50:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq HUD_RegisterOverlay_L_80253BC8
    lwz r31, 0xc(r29)
    cmplwi r31, 0x0
    beq HUD_RegisterOverlay_L_80253BC8
    cmpwi r30, 0xb
    beq HUD_RegisterOverlay_L_80253BC8
    bge HUD_RegisterOverlay_L_80253B80
    cmpwi r30, 0xa
    bge HUD_RegisterOverlay_L_80253B8C
    b HUD_RegisterOverlay_L_80253BC8
    HUD_RegisterOverlay_L_80253B80:
    cmpwi r30, 0xd
    bge HUD_RegisterOverlay_L_80253BC8
    b HUD_RegisterOverlay_L_80253BAC
    HUD_RegisterOverlay_L_80253B8C:
    li r4, 0x0
    la r5, lbl_806D0A68(r13)
    la r6, s_clCDispInterface(r13)
    li r7, 0x0
    bl fn_80271340
    mr r4, r31
    bl fn_8021984C
    b HUD_RegisterOverlay_L_80253BC8
    HUD_RegisterOverlay_L_80253BAC:
    li r4, 0x0
    la r5, lbl_806D0A60(r13)
    la r6, s_clCDispInterface(r13)
    li r7, 0x0
    bl fn_80271340
    mr r4, r31
    bl fn_802437AC
    HUD_RegisterOverlay_L_80253BC8:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

