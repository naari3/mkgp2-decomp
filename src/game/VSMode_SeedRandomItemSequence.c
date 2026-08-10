/* === extracted from auto_VSMode_SeedRandomIte_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_80278C54();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_805AC600[];

/* --- function index (1 fns, .text 0x8009BDC0..0x8009BEF4) ---
 * [  0] 0x8009BDC0 size:0x134   global VSMode_SeedRandomItemSequence
 */

/* --- forward decls --- */
asm void VSMode_SeedRandomItemSequence(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VSMode_SeedRandomItemSequence[8] = {
    0x30, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VSMode_SeedRandomItemSequence = {
    (void *)&VSMode_SeedRandomItemSequence, 0x00000134, (void *)extab_VSMode_SeedRandomItemSequence
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VSMode_SeedRandomItemSequence(void) { /* 0x8009BDC0 size:0x134 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    li r6, 0x0
    li r7, 0xc
    stw r0, 0x34(r1)
    subfic r0, r7, 0xd
    stmw r26, 0x18(r1)
    mr r30, r3
    mr r31, r5
    addi r3, r1, 0x14
    stb r6, 0x8(r1)
    stb r6, 0x9(r1)
    stb r6, 0xa(r1)
    stb r6, 0xb(r1)
    stb r6, 0xc(r1)
    stb r6, 0xd(r1)
    stb r6, 0xe(r1)
    stb r6, 0xf(r1)
    stb r6, 0x10(r1)
    stb r6, 0x11(r1)
    stb r6, 0x12(r1)
    stb r6, 0x13(r1)
    mtctr r0
    cmpwi r7, 0xd
    bge VSMode_SeedRandomItemSequence_L_8009BE30
    VSMode_SeedRandomItemSequence_L_8009BE24:
    stb r6, 0x0(r3)
    addi r3, r3, 0x1
    bdnz VSMode_SeedRandomItemSequence_L_8009BE24
    VSMode_SeedRandomItemSequence_L_8009BE30:
    mulli r5, r30, 0x18
    lis r3, lbl_805AC600@ha
    addi r28, r1, 0x8
    li r6, 0x1
    addi r0, r3, lbl_805AC600@l
    lis r3, 0x4ec5
    stbx r6, r28, r4
    add r27, r0, r5
    subi r29, r3, 0x13b1
    li r26, 0x0
    b VSMode_SeedRandomItemSequence_L_8009BED4
    VSMode_SeedRandomItemSequence_L_8009BE5C:
    bl fn_80278C54
    mulhw r0, r29, r3
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0xd
    subf r5, r0, r3
    lbzx r0, r28, r5
    cmplwi r0, 0x0
    bne VSMode_SeedRandomItemSequence_L_8009BE5C
    li r4, 0x1
    cmpwi r30, 0x0
    stbx r4, r28, r5
    blt VSMode_SeedRandomItemSequence_L_8009BEC8
    cmpwi r30, 0x8
    bge VSMode_SeedRandomItemSequence_L_8009BEC8
    cmpwi r5, 0x0
    blt VSMode_SeedRandomItemSequence_L_8009BEC8
    cmpwi r5, 0xf
    bge VSMode_SeedRandomItemSequence_L_8009BEC8
    li r3, 0x6
    li r0, 0x0
    stw r3, 0x0(r27)
    stw r5, 0x4(r27)
    stw r4, 0x8(r27)
    stw r0, 0xc(r27)
    stw r0, 0x10(r27)
    VSMode_SeedRandomItemSequence_L_8009BEC8:
    addi r27, r27, 0x18
    addi r30, r30, 0x1
    addi r26, r26, 0x1
    VSMode_SeedRandomItemSequence_L_8009BED4:
    cmpw r26, r31
    blt VSMode_SeedRandomItemSequence_L_8009BE5C
    mr r3, r30
    lmw r26, 0x18(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


