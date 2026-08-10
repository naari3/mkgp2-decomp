/* === extracted from auto_KartDriver_GetKartRo_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Object_GetJObjLocalMatrix();

/* --- function index (1 fns, .text 0x80041748..0x8004178C) ---
 * [  0] 0x80041748 size:0x44    global KartDriver_GetKartRootMtx
 */

/* --- forward decls --- */
asm void KartDriver_GetKartRootMtx(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_GetKartRootMtx[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_GetKartRootMtx = {
    (void *)&KartDriver_GetKartRootMtx, 0x00000044, (void *)extab_KartDriver_GetKartRootMtx
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_GetKartRootMtx(void) { /* 0x80041748 size:0x44 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r4, 0x0(r3)
    cmplwi r4, 0x0
    beq KartDriver_GetKartRootMtx_L_8004176C
    lwz r0, 0xc(r3)
    cmplwi r0, 0x0
    bne KartDriver_GetKartRootMtx_L_80041774
    KartDriver_GetKartRootMtx_L_8004176C:
    li r3, 0x0
    b KartDriver_GetKartRootMtx_L_8004177C
    KartDriver_GetKartRootMtx_L_80041774:
    mr r3, r4
    bl Object_GetJObjLocalMatrix
    KartDriver_GetKartRootMtx_L_8004177C:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

