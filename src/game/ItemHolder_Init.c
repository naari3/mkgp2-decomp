/*
 * ItemHolder_Init @ 0x801E8FB8 (size 0xB8). Singleton extab group entry.
 *
 * Held as asm_fn after 7 C-matching cycles plateaued at 90.32% objdiff.
 * The diff is a register-allocation choice the CW1.3.2 scheduler refuses
 * to emit from any C source order we tried:
 *
 *   target: vtable load `addi r3, r8, @l` is deferred 9 instr after `lis`,
 *           interleaved with `mflr/li r0,-1/li r31,0/mr r29,r3/mr r30,r4`
 *           and ends up storing vtable from r3 (caller-save) while r0
 *           holds -1 (1 store) and r31 holds 0 (4 stores + slotIdx reuse).
 *   ours:   CW pairs `lis/addi` immediately, parks vtable in r0, then
 *           needs an extra `li r0,0` after the vtable store (one extra
 *           insn -> 48 vs target 47), keeping -1 in r3 and 0 in r0.
 *
 * Source orderings tried (all plateaued at 90.32%, no movement):
 *   - canonical (self[0]=vtable; self[1..4]=args; self[6]=-1; self[7..10]=0)
 *   - args-first then vtable last among prelude stores (-> 87.80%, worse)
 *   - self[7..10] = slotIdx (alias 0 via the loop var)
 *   - decl-order: slotIdx-first vs slotIdx-last (no effect)
 *   - `*(void **)&self[0]` cast vs `(int)` cast (no effect)
 *   - separate `int slotIdx; slotIdx = 0;` decl/init (no effect)
 *
 * Block D applies (extab present): the dtk reversed-extab group for
 * ItemHolder_Init has its own extab/extabindex pair @0x80016A98 / @0x8002897C
 * (Saved GPR range r29-r31, Large Frame=Yes, flag 0x18080000). asm_fn must
 * manually emit them via `.extab_user`/`.extabindex_user` (postprocess_extab_user
 * renames the sections + the `extab_*`/`extabindex_*` symbol names to the
 * `@etb_<addr>`/`@eti_<addr>` form dtk expects). configure.py gets
 * `extab_padding=b"\x00\x00"` to route through the mwcc_sjis_extab build rule.
 *
 * Future C-matching attempts should focus on coaxing the scheduler to defer
 * the `addi` and let r31 take 0 (probably needs a different statement that
 * yields the `mr r29, r3 ; addi r3, r8, @l` interleave naturally, perhaps
 * with vtable load expressed via an inlined accessor or a different lvalue
 * form). See docs/per_fn_matching_strategy.md §14.3 for related CW reg-alloc
 * hard-block patterns.
 */

/* === extracted from ItemHolder_Init === */

/* --- extern decls: branch callees (bl/b targets) --- */
extern void GetRaceContextPtr();
extern void RaceContextSlot_GetIfAlive(); /* RaceContextSlot_GetIfAlive */

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
extern unsigned int lbl_804E4AF0[]; /* PTR_PTR_804E4AF0 (initial vtable) */
extern unsigned int lbl_804E4B44[]; /* PTR_PTR_804E4B44 (final vtable) */

/* --- forward decls --- */
asm void ItemHolder_Init(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemHolder_Init[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemHolder_Init = {
    (void *)&ItemHolder_Init, 0x000000B8, (void *)extab_ItemHolder_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemHolder_Init(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r8, lbl_804E4AF0@ha
    stw r0, 0x24(r1)
    li r0, -0x1
    stw r31, 0x1c(r1)
    li r31, 0x0
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr r29, r3
    addi r3, r8, lbl_804E4AF0@l
    stw r3, 0x0(r29)
    stw r30, 0x4(r29)
    stw r5, 0x8(r29)
    stw r6, 0xc(r29)
    stw r7, 0x10(r29)
    stw r0, 0x18(r29)
    stw r31, 0x1c(r29)
    stw r31, 0x20(r29)
    stw r31, 0x28(r29)
    stw r31, 0x24(r29)
ItemHolder_Init_L_801E9010:
    bl GetRaceContextPtr
    mr r4, r31
    bl RaceContextSlot_GetIfAlive
    cmplwi r3, 0x0
    beq ItemHolder_Init_L_801E9038
    lwz r0, 0xb4(r3)
    cmplw r0, r30
    bne ItemHolder_Init_L_801E9038
    stw r31, 0x14(r29)
    b ItemHolder_Init_L_801E9044
ItemHolder_Init_L_801E9038:
    addi r31, r31, 0x1
    cmpwi r31, 0x80
    blt ItemHolder_Init_L_801E9010
ItemHolder_Init_L_801E9044:
    lis r4, lbl_804E4B44@ha
    mr r3, r29
    addi r0, r4, lbl_804E4B44@l
    stw r0, 0x0(r29)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
