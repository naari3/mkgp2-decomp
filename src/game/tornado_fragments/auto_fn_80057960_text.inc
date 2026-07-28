/* === extracted from auto_fn_80057960_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_SpawnWithDescriptor();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EDC30[];

/* --- function index (1 fns, .text 0x80057960..0x800579D8) ---
 * [  0] 0x80057960 size:0x78    global fn_80057960
 */

/* --- forward decls --- */
asm void fn_80057960(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80057960[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80057960 = {
    (void *)&fn_80057960, 0x00000078, (void *)extab_fn_80057960
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_80057960(void) { /* 0x80057960 size:0x78 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    lwz r0, 0x14(r3)
    cmplwi r0, 0x0
    beq fn_80057960_L_800579C8
    lis r3, lbl_802EDC30@ha
    addi r4, r1, 0x8
    addi r7, r3, lbl_802EDC30@l
    li r3, 0x0
    lwz r6, 0x0(r7)
    lwz r5, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r6, 0x14(r1)
    stw r5, 0x18(r1)
    stw r0, 0x1c(r1)
    stfs f1, 0x14(r1)
    stfs f2, 0x18(r1)
    lwz r6, 0x14(r1)
    stfs f3, 0x1c(r1)
    lwz r5, 0x18(r1)
    lwz r0, 0x1c(r1)
    stw r6, 0x8(r1)
    stw r5, 0xc(r1)
    stw r0, 0x10(r1)
    bl DrawEffect_SpawnWithDescriptor
    fn_80057960_L_800579C8:
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

