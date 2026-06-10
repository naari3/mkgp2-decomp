# ItemEffect batch idioms (2026-06-10, batch_promote_8004f6b0_itemeffect1)

Matched in src/game/auto_ONKARTHIT_block.c (commit 4fdc7ae): KartItem_OnFallOffOrDeath / ItemEffect_SelectAndDispatch_Wrap / ItemEffect_GenericHandler. Probe history comments live above the two remaining asm bodies in the TU.

Win idioms:

1. Param-register reuse for a derived pointer: `self = (ItemEffectTable *)self->owner;` + `((KartItemOpsView *)self)->field` accesses reproduce `lwz r28, 0x0(r28)` (target overwrites the param web). A separate `KartItemOpsView *o` local picks a fresh callee-saved (r27) and mismatches. Works because the original param value is dead on that path.
2. mtctr/bdnz scan loop (calls only on exit paths): `for (n = 0; n < K; n++)` with n otherwise unused + separate user pointer walk `desc++` converts to `li r0, K; mtctr; ...; addi rP, rP, stride; bdnz`. A do-while with `--n != 0` does NOT convert (stays subic./bne with the counter in a volatile). Indexed `&tbl[n]` as a call argument blocks the clean form: it re-derives the address via mulli and keeps both inductions live.
3. Table-base init split vs direct (new observation): for a user pointer-walk induction web crossing calls, CW 1.3.2 splits the constant init (`addi r0, rHi, sym@l` hoisted above stmw + `mr rC, r0`). The SR-generated pointer from an indexed `tbl[n]` loop gets a DIRECT `addi rC, rHi, sym@l` placed after the first param mr. Target SelectAndDispatch has direct init + down-count subic./bgt + goto-pair branch shape simultaneously; no single source form reproduced all three (SR form flips to up-count cmpwi/blt and renumbers the callee-saved pair).
4. Decl-position LIFO register reuse: in OnFallOffOrDeath, declaring the late-lifetime `sec` pointer between `tbl` and `cursor` lands it on r26 = tbl register (freed last before sec def). Declared after `itemId` it lands on r24. Matches the descending decl-order model plus last-freed-first-reused.
5. subf operand order for branchless equality: pointer-deref form `desc->itemId == itemId` -> `subf r0, r0(descId), r29(itemId)` (a==b -> b-a). The indexed form `tbl[n].itemId == itemId` flipped the subf operands in one probe; prefer the deref form when matching.

Hard-block instances (new data points):

- ItemEffect_OnHit 0x800502F0: 71/72, the only residue is the first member load scheduled ABOVE stmw in target (between LR-save stw r0 and stmw r22). exceptions on/off probe leaves codegen identical -> allocator/scheduler-internal, not the approach-B class. This is also a counter-example to the blanket rule in cw132-prologue-load-hoist-unreproduced.md: CW-built target code can carry a load above a stack store (stmw) in the prologue, just not above the LR-save stw that defines r0.
- ItemEffect_SelectAndDispatch 0x80050030: goto-pair `if (sel < 0) goto next; goto have_sel;` collapses to a single inverted bge in every probed form, consistent with sec 14.2 (explicit goto-pair listed as collapsing). Plus volatile-pair swap (p/n2 on r3/r5) and vtable indirect-call temp choice (CW lwz r6/lwz r12 vs target r12/r12) as further residues.
