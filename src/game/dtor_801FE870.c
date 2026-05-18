/* === extracted from auto_fn_801FE4D0_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf();
extern void dtor_8003AFB8();
extern void fn_8002D084();
extern void fn_8002D08C();
extern void fn_801F9888();
extern void fn_80209FA4();
extern void fn_8027B394();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_pInputState;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803BFF98[];
extern unsigned int lbl_803BFFAC[];
extern unsigned int lbl_804EC1AC[];
extern unsigned int lbl_804EC1B8[];

/* --- forward decls --- */
asm void fn_801FE4D0(void);
asm void fn_801FE554(void);
asm void fn_801FE584(void);
asm void fn_801FE588(void);
asm void fn_801FE5C8(void);
asm void fn_801FE858(void);
void *dtor_801FE870(void *self, short flag);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
/* dtor_801FE870's extab/extabindex are emitted automatically by CW   */
/* (#pragma exceptions on around the C body); only the asm_fn entries */
/* need manual emit. (Approach A per docs/per_fn_matching_strategy.md  */
/* §14.1.)                                                            */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_801FE4D0[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_fn_801FE554[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_fn_801FE588[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_fn_801FE5C8[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801FE4D0 = {
    (void *)&fn_801FE4D0, 0x00000084, (void *)extab_fn_801FE4D0
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801FE554 = {
    (void *)&fn_801FE554, 0x00000030, (void *)extab_fn_801FE554
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801FE588 = {
    (void *)&fn_801FE588, 0x00000040, (void *)extab_fn_801FE588
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801FE5C8 = {
    (void *)&fn_801FE5C8, 0x00000290, (void *)extab_fn_801FE5C8
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_801FE4D0(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq fn_801FE4D0_L_801FE538
    lis r3, lbl_804EC1AC@ha
    addi r0, r3, lbl_804EC1AC@l
    stw r0, 0x0(r30)
    bl fn_80209FA4
    bl fn_801F9888
    lis r3, lbl_803BFF98@ha
    addi r3, r3, lbl_803BFF98@l
    crxor 6, 6, 6
    bl DebugPrintf
    cmplwi r30, 0x0
    beq fn_801FE4D0_L_801FE528
    lis r3, lbl_804EC1B8@ha
    addi r0, r3, lbl_804EC1B8@l
    stw r0, 0x0(r30)
    fn_801FE4D0_L_801FE528:
    extsh. r0, r31
    ble fn_801FE4D0_L_801FE538
    mr r3, r30
    bl dtor_8003AFB8
    fn_801FE4D0_L_801FE538:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void fn_801FE554(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    mr r6, r3
    mr r3, r4
    stw r0, 0x14(r1)
    li r5, 0x5
    addi r4, r6, 0x158
    bl fn_8027B394
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void fn_801FE584(void) {
    nofralloc
    blr
}

asm void fn_801FE588(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    mr r5, r3
    lis r3, lbl_803BFFAC@ha
    stw r0, 0x14(r1)
    addi r3, r3, lbl_803BFFAC@l
    lwz r4, 0x4(r5)
    addi r0, r4, 0x1
    stw r0, 0x4(r5)
    lwz r5, 0x4(r5)
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void fn_801FE5C8(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    li r5, 0x0
    stw r0, 0x24(r1)
    li r0, 0x6
    stw r31, 0x1c(r1)
    mr r31, r3
    li r3, 0x0
    stw r30, 0x18(r1)
    mr r4, r31
    stw r29, 0x14(r1)
    stw r3, 0x4(r31)
    stw r3, 0x8(r31)
    stb r3, 0xc(r31)
    mtctr r0
    fn_801FE5C8_L_801FE604:
    add r3, r31, r5
    li r0, 0x0
    stb r0, 0xd(r3)
    addi r5, r5, 0x1
    stb r0, 0x13(r3)
    stb r0, 0x67(r3)
    stb r0, 0x6d(r3)
    stb r0, 0xa3(r3)
    stb r0, 0xa9(r3)
    stb r0, 0xdf(r3)
    stb r0, 0xe5(r3)
    stb r0, 0x1f(r4)
    stb r0, 0x37(r4)
    stb r0, 0x73(r4)
    stb r0, 0x8b(r4)
    stb r0, 0xaf(r4)
    stb r0, 0xc7(r4)
    stb r0, 0xeb(r4)
    stb r0, 0x103(r4)
    stb r0, 0x20(r4)
    stb r0, 0x38(r4)
    stb r0, 0x74(r4)
    stb r0, 0x8c(r4)
    stb r0, 0xb0(r4)
    stb r0, 0xc8(r4)
    stb r0, 0xec(r4)
    stb r0, 0x104(r4)
    stb r0, 0x21(r4)
    stb r0, 0x39(r4)
    stb r0, 0x75(r4)
    stb r0, 0x8d(r4)
    stb r0, 0xb1(r4)
    stb r0, 0xc9(r4)
    stb r0, 0xed(r4)
    stb r0, 0x105(r4)
    stb r0, 0x22(r4)
    stb r0, 0x3a(r4)
    stb r0, 0x76(r4)
    stb r0, 0x8e(r4)
    stb r0, 0xb2(r4)
    stb r0, 0xca(r4)
    stb r0, 0xee(r4)
    stb r0, 0x106(r4)
    stb r0, 0x4f(r4)
    stb r0, 0x11b(r4)
    stb r0, 0x50(r4)
    stb r0, 0x11c(r4)
    stb r0, 0x51(r4)
    stb r0, 0x11d(r4)
    stb r0, 0x52(r4)
    stb r0, 0x11e(r4)
    addi r4, r4, 0x4
    bdnz fn_801FE5C8_L_801FE604
    li r29, 0x0
    mr r30, r31
    fn_801FE5C8_L_801FE6E0:
    add r3, r31, r29
    li r0, 0x1
    stb r0, 0xd(r3)
    stb r0, 0x67(r3)
    stb r0, 0xa3(r3)
    stb r0, 0xdf(r3)
    bl fn_8002D08C
    clrlwi. r0, r3, 24
    beq fn_801FE5C8_L_801FE728
    bl fn_8002D084
    clrlwi. r0, r3, 24
    bne fn_801FE5C8_L_801FE728
    li r0, 0x1
    stb r0, 0x1f(r30)
    stb r0, 0x73(r30)
    stb r0, 0xaf(r30)
    stb r0, 0xeb(r30)
    b fn_801FE5C8_L_801FE74C
    fn_801FE5C8_L_801FE728:
    li r0, 0x1
    stb r0, 0x1f(r30)
    stb r0, 0x20(r30)
    stb r0, 0x73(r30)
    stb r0, 0x74(r30)
    stb r0, 0xaf(r30)
    stb r0, 0xb0(r30)
    stb r0, 0xeb(r30)
    stb r0, 0xec(r30)
    fn_801FE5C8_L_801FE74C:
    addi r29, r29, 0x1
    addi r30, r30, 0x4
    cmpwi r29, 0x6
    blt fn_801FE5C8_L_801FE6E0
    li r0, 0x1
    stb r0, 0x19(r31)
    stb r0, 0x4f(r31)
    stb r0, 0x50(r31)
    stb r0, 0x51(r31)
    stb r0, 0x52(r31)
    stb r0, 0x1a(r31)
    stb r0, 0x53(r31)
    stb r0, 0x54(r31)
    stb r0, 0x55(r31)
    stb r0, 0x56(r31)
    stb r0, 0x1b(r31)
    stb r0, 0x57(r31)
    stb r0, 0x58(r31)
    stb r0, 0x59(r31)
    stb r0, 0x5a(r31)
    stb r0, 0x1c(r31)
    stb r0, 0x5b(r31)
    stb r0, 0x5c(r31)
    stb r0, 0x5d(r31)
    stb r0, 0x5e(r31)
    stb r0, 0x1d(r31)
    stb r0, 0x5f(r31)
    stb r0, 0x60(r31)
    stb r0, 0x61(r31)
    stb r0, 0x62(r31)
    stb r0, 0x1e(r31)
    stb r0, 0x63(r31)
    stb r0, 0x64(r31)
    stb r0, 0x65(r31)
    stb r0, 0x66(r31)
    bl fn_8002D08C
    clrlwi. r0, r3, 24
    beq fn_801FE5C8_L_801FE804
    bl fn_8002D084
    clrlwi. r0, r3, 24
    bne fn_801FE5C8_L_801FE804
    li r0, 0x0
    stb r0, 0x12(r31)
    stb r0, 0x6c(r31)
    stb r0, 0xa8(r31)
    stb r0, 0xe4(r31)
    fn_801FE5C8_L_801FE804:
    li r0, 0x0
    stw r0, 0x134(r31)
    stw r0, 0x138(r31)
    stw r0, 0x13c(r31)
    stw r0, 0x140(r31)
    stw r0, 0x144(r31)
    stw r0, 0x148(r31)
    sth r0, 0x158(r31)
    sth r0, 0x15a(r31)
    sth r0, 0x15c(r31)
    sth r0, 0x15e(r31)
    sth r0, 0x160(r31)
    sth r0, 0x162(r31)
    stw r0, 0x164(r31)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

asm void fn_801FE858(void) {
    nofralloc
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne fn_801FE858_L_801FE868
    li r3, 0x0
    fn_801FE858_L_801FE868:
    lwz r3, 0x14(r3)
    blr
}

/*
 * Trivial deleting-dtor (vtable slot @ PTR_PTR_804EC1B8). Demotes
 * *self back to its base vtable, optionally frees the storage when
 * the C++ deleting-dtor flag is set, returns this in r3.
 *
 * Same shape as ObjectBase_Dtor (commit 9807e6c), BtMode_BaseDtor
 * (commit 746bb13), CourseAuxClass_VtableDtor (commit 5cb971a),
 * etc. Approach A per docs/per_fn_matching_strategy.md §14.1: the
 * extab/extabindex for this fn are auto-emitted by CW (#pragma
 * exceptions on); the surrounding asm_fn entries keep their manual
 * .extab_user emit.
 */
#pragma exceptions on
void *dtor_801FE870(void *self, short flag) {
    if (self != 0) {
        *(char **)self = (char *)lbl_804EC1B8;
        if (flag > 0) {
            dtor_8003AFB8(self);
        }
    }
    return self;
}
#pragma exceptions reset

// triggering rebuild
