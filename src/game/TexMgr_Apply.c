/*
 * TexMgr_Apply @ 0x801F947C (size 0x9C). Singleton TU with own
 * extab/extabindex (extab @ 0x800176C8 8B, extabindex @ 0x800290B4 12B).
 *
 * Held as asm_fn after C-matching plateaued at 61.79% (functionally
 * equivalent; the residual diff is a callee-saved register-coloring quirk
 * that swaps r28<->r29 between loop counter `i` and the local copy of the
 * `self` parameter). CW 1.3.2 keeps `i = 0` scheduled early in the
 * prologue, taking r29 instead of r28; reorder of decls, init-in-decl,
 * for-loop reshape, and a local base pointer were all tried (`docs/notes/
 * cw132-fp-decl-order-regalloc.md` style); none flipped the coloring.
 *
 * Walks a 256-entry u16 id table at self+0x24 (stride 2 bytes); for each
 * non-0xFFFF entry preloads one of two parallel pointer tables at
 * lbl_804E5590 keyed by self+0x18 (==1 -> +8 / table A, else +4 / table B).
 *
 * Manual extab/extabindex emit follows the Phase 1b pattern
 * (docs/per_fn_matching_strategy.md §12): `.extab_user`/`.extabindex_user`
 * sections are renamed to `extab`/`extabindex` by
 * tools/postprocess_extab_user.py before `dtk extab clean`. The matching
 * entries in tools/extab_user_renames.json bind the C symbol names to the
 * anonymous local `@etb_800176C8` / `@eti_800290B4` dtk regenerates.
 */

extern void PreloadResource(void *res);

extern unsigned int lbl_804E5590[];

asm void TexMgr_Apply(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TexMgr_Apply[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TexMgr_Apply = {
    (void *)&TexMgr_Apply, 0x0000009C, (void *)extab_TexMgr_Apply
};

asm void TexMgr_Apply(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r4, lbl_804E5590@ha
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    addi r31, r4, lbl_804E5590@l
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r3
    mr r30, r29
    stw r28, 0x10(r1)
    li r28, 0
TexMgr_Apply_L_801F94AC:
    lhz r3, 0x24(r30)
    cmplwi r3, 0xffff
    beq TexMgr_Apply_L_801F94F8
    lwz r0, 0x18(r29)
    cmpwi r0, 1
    bne TexMgr_Apply_L_801F94D8
    clrlslwi r0, r3, 16, 4
    add r3, r31, r0
    lwz r3, 0x8(r3)
    bl PreloadResource
    b TexMgr_Apply_L_801F94E8
TexMgr_Apply_L_801F94D8:
    clrlslwi r0, r3, 16, 4
    add r3, r31, r0
    lwz r3, 0x4(r3)
    bl PreloadResource
TexMgr_Apply_L_801F94E8:
    addi r28, r28, 1
    addi r30, r30, 2
    cmpwi r28, 0x100
    blt TexMgr_Apply_L_801F94AC
TexMgr_Apply_L_801F94F8:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
