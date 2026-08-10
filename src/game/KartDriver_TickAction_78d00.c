/* === extracted from auto_KartDriver_TickActio_text_3 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void KartTireFX_SetVisibleAll4Wheels();

/* --- function index (1 fns, .text 0x800422D8..0x80042328) ---
 * [  0] 0x800422D8 size:0x50    global KartDriver_TickAction_78d00
 */

/* --- forward decls --- */
asm void KartDriver_TickAction_78d00(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_TickAction_78d00[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_TickAction_78d00 = {
    (void *)&KartDriver_TickAction_78d00, 0x00000050, (void *)extab_KartDriver_TickAction_78d00
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_TickAction_78d00(void) { /* 0x800422D8 size:0x50 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    beq KartDriver_TickAction_78d00_L_800422FC
    lwz r0, 0xc(r3)
    cmplwi r0, 0x0
    bne KartDriver_TickAction_78d00_L_80042304
    KartDriver_TickAction_78d00_L_800422FC:
    li r3, 0x0
    b KartDriver_TickAction_78d00_L_80042318
    KartDriver_TickAction_78d00_L_80042304:
    lwz r3, 0x30c(r3)
    cmplwi r3, 0x0
    beq KartDriver_TickAction_78d00_L_80042314
    bl KartTireFX_SetVisibleAll4Wheels
    KartDriver_TickAction_78d00_L_80042314:
    li r3, 0x1
    KartDriver_TickAction_78d00_L_80042318:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


