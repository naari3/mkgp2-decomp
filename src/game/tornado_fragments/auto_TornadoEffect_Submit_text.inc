/* === extracted from auto_TornadoEffect_Submit_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void FinalLapCoinJump_CheckActiveForObject();
extern void Object_GetJObjPositionVec();
extern void clDrawMan_AddSorted();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D28E4;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */

/* --- function index (1 fns, .text 0x80056F40..0x80056FC0) ---
 * [  0] 0x80056F40 size:0x80    global TornadoEffect_SubmitRender
 */

/* --- forward decls --- */
asm void TornadoEffect_SubmitRender(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_SubmitRender[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_SubmitRender = {
    (void *)&TornadoEffect_SubmitRender, 0x00000080, (void *)extab_TornadoEffect_SubmitRender
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_SubmitRender(void) { /* 0x80056F40 size:0x80 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    lwz r3, 0xc(r3)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    bne TornadoEffect_SubmitRender_L_80056FAC
    lwz r0, 0x100(r31)
    cmpwi r0, 0x0
    ble TornadoEffect_SubmitRender_L_80056FAC
    lwz r3, 0xa8(r31)
    addi r4, r1, 0x8
    bl Object_GetJObjPositionVec
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne TornadoEffect_SubmitRender_L_80056F8C
    li r3, 0x0
    TornadoEffect_SubmitRender_L_80056F8C:
    lis r4, TornadoEffect_RenderCallback@ha
    lwz r5, 0xa8(r31)
    lfs f1, 0x8(r1)
    addi r4, r4, TornadoEffect_RenderCallback@l
    lfs f2, 0xc(r1)
    lfs f3, 0x10(r1)
    lfs f4, lbl_806D28E4(r2)
    bl clDrawMan_AddSorted
    TornadoEffect_SubmitRender_L_80056FAC:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

