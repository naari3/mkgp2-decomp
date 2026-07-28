/* === extracted from auto_TornadoEffect_ApplyI_text_2 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void TornadoEffect_ApplyItemVisual_Primary();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10A8;
extern unsigned int lbl_806D2914;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_803F98F4[];

/* --- function index (1 fns, .text 0x80058C80..0x80058DDC) ---
 * [  0] 0x80058C80 size:0x15C   global TornadoEffect_ApplyItemVisual_Compact
 */

/* --- forward decls --- */
asm void TornadoEffect_ApplyItemVisual_Compact(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_ApplyItemVisual_Compact[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_ApplyItemVisual_Compact = {
    (void *)&TornadoEffect_ApplyItemVisual_Compact, 0x0000015C, (void *)extab_TornadoEffect_ApplyItemVisual_Compact
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_ApplyItemVisual_Compact(void) { /* 0x80058C80 size:0x15C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r5
    stw r30, 0x18(r1)
    mr r30, r3
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    mr r28, r4
    lwz r4, 0x14c(r3)
    subf r0, r28, r4
    cmpwi r4, -0x1
    cntlzw r0, r0
    srwi r5, r0, 5
    neg r0, r5
    or r0, r0, r5
    srwi r29, r0, 31
    beq TornadoEffect_ApplyItemVisual_Compact_L_80058CD0
    bl TornadoEffect_ApplyItemVisual_Primary
    TornadoEffect_ApplyItemVisual_Compact_L_80058CD0:
    subi r0, r28, 0xc
    stw r28, 0x14c(r30)
    cmplwi r0, 0x1c
    li r4, 0x0
    li r5, 0x0
    bgt TornadoEffect_ApplyItemVisual_Compact_L_80058D60
    lis r3, jumptable_803F98F4@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_803F98F4@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    cmplwi r29, 0x0
    bne TornadoEffect_ApplyItemVisual_Compact_L_80058D60
    li r0, 0x2
    lfs f0, lbl_806D2914(r2)
    stw r0, 0xd4(r30)
    stfs f0, 0xe0(r30)
    stfs f0, 0xe4(r30)
    stfs f0, 0xe8(r30)
    b TornadoEffect_ApplyItemVisual_Compact_L_80058D60
    li r4, 0x4
    b TornadoEffect_ApplyItemVisual_Compact_L_80058D60
    li r4, 0x2
    b TornadoEffect_ApplyItemVisual_Compact_L_80058D60
    li r4, 0x5
    b TornadoEffect_ApplyItemVisual_Compact_L_80058D60
    lwz r3, lbl_806D10A8(r13)
    li r5, 0x9
    addi r0, r3, 0x1
    stw r0, lbl_806D10A8(r13)
    b TornadoEffect_ApplyItemVisual_Compact_L_80058D60
    lwz r3, lbl_806D10A8(r13)
    li r5, 0xa
    addi r0, r3, 0x1
    stw r0, lbl_806D10A8(r13)
    TornadoEffect_ApplyItemVisual_Compact_L_80058D60:
    cmpwi r4, 0x0
    beq TornadoEffect_ApplyItemVisual_Compact_L_80058D98
    beq TornadoEffect_ApplyItemVisual_Compact_L_80058D98
    clrlwi r0, r31, 24
    cmplwi r0, 0x1
    bne TornadoEffect_ApplyItemVisual_Compact_L_80058D80
    li r0, 0x0
    stw r0, 0x130(r30)
    TornadoEffect_ApplyItemVisual_Compact_L_80058D80:
    stw r4, 0x124(r30)
    lwz r0, 0x124(r30)
    cmpwi r0, 0x6
    bne TornadoEffect_ApplyItemVisual_Compact_L_80058D98
    li r0, 0x1
    stb r0, 0x12c(r30)
    TornadoEffect_ApplyItemVisual_Compact_L_80058D98:
    cmpwi r5, 0x0
    beq TornadoEffect_ApplyItemVisual_Compact_L_80058DBC
    beq TornadoEffect_ApplyItemVisual_Compact_L_80058DBC
    clrlwi r0, r31, 24
    cmplwi r0, 0x1
    bne TornadoEffect_ApplyItemVisual_Compact_L_80058DB8
    li r0, 0x0
    stw r0, 0x134(r30)
    TornadoEffect_ApplyItemVisual_Compact_L_80058DB8:
    stw r5, 0x128(r30)
    TornadoEffect_ApplyItemVisual_Compact_L_80058DBC:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

