# strpcbrun batch idioms (2026-06-10, batch_promote_8004f174_strpcbrun)

Verified win idioms (all matched in src/game/auto_ONKARTHIT_block.c, commit e3ff0e2):

1. `q->field = i = 0;` assignment-chain: coalesces the stored zero into the loop-counter web (`stw r31` + single `li r31,0`). Separate statements emit a second `li r0,0`.
2. `if ((p = gInstance) == 0) { p = 0; }`: reproduces the inlined sda21 GetInstance fold `lwz r3,g(r13); cmplwi r3,0; bne L; li r3,0; L:` exactly. Ternary `g ? g : 0` emits branch-over (`beq/b/li`); assign-then-`if (!p) p = 0;` moves the load to r0 with an `mr r3,r0`. Only the condition-assign form pins the load to the result web.
3. `volatile Vec3 v;` local + scalar member stores: retains dead spill stores (frame + stack stores) against CW 1.3.2 DSE. Non-volatile locals lose them even when address-taken via a pointer alias (partial answer to the WarpZone_CalcExitPosition DSE hard-block). volatile store order is source order, so write members in the target store order; feed the out-param stores from plain float locals to avoid reloads.
4. Strength-reduced lane walk (`mr rC, rBase` init, displacement +0x28, `addi rC, rC, 0x18`): use a pad-0x28 cursor view struct and bump with `(T *)((char *)c + 0x18)`. Indexed `tbl->lanes[i].f` gives the same shape but the SR temp insertion shifts the callee-saved numbering by one; a named cursor makes the assignment fully controllable via decl order.
5. Callee-saved decl-order observation: in this stmw fn the FIRST declared local got the HIGHEST register (descending r31..r25), opposite of the ascending rule seen elsewhere. Read target registers, then declare in reverse of the ascending target order.
6. `li r6,X; li r5,0` pairs before a call with r4 untouched = u64 second arg (EABI aligned pair skips r4). ItemEffectBus_ClearMask/OrMask take (void *, unsigned long long).
7. fmuls web pinning for `(int)(C1 * s * C2)`: single expression swaps f0/f1 and flips the final fmuls operands; `scaled = C1 * s;` then `(int)(scaled * C2)` pins C1->f1 (coalesced into scaled) and C2/result->f0. Capturing a call result in `void *pcb` before the float math costs zero instructions (r3 stays live).
8. New scheduler hard-block instance: KartItem_GetCarVelocityVec3 0x8004F50C, 99.08% C, only the first two lfs swapped (target z,y,x; CW emits y,z,x for every init permutation). Same single-pair-swap family as the subi/lwz ScopedTimer block.

TU note: promoting KartItem_CancelActiveEffect required extra_cflags [-use_lmw_stmw on] on the game/auto_ONKARTHIT_block.c Object line (stmw r24 vs _savegpr_24), confirming the section 14.2 OnKartHit prediction. All previously matched fns in the TU stay 100% with the flag (none save 3+ GPRs from C).
