/* === extracted from auto_TornadoEffect_Trigge_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_SetByte10C();

/* --- function index (1 fns, .text 0x800576D8..0x8005771C) ---
 * [  0] 0x800576D8 size:0x44    global TornadoEffect_TriggerFlagD2WithTimer
 */

/* --- forward decls --- */
asm void TornadoEffect_TriggerFlagD2WithTimer(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_TriggerFlagD2WithTimer[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_TriggerFlagD2WithTimer = {
    (void *)&TornadoEffect_TriggerFlagD2WithTimer, 0x00000044, (void *)extab_TornadoEffect_TriggerFlagD2WithTimer
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_TriggerFlagD2WithTimer(void) { /* 0x800576D8 size:0x44 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 0x0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x10(r3)
    bl DrawEffect_SetByte10C
    li r3, 0x1
    li r0, 0xf
    stb r3, 0xd2(r31)
    stw r0, 0x13c(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

