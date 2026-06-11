# mr-SR-init (mr-vs-li const-fold): SOLVED via inline helper (2026-06-11, batch_research_mrsrinit_phase2c)

## Verdict
- Mechanism identified and reproduced: the dual-induction SR init `mr rOFF, rI` survives const-prop iff the loop is INLINED from a `static inline` helper function. No standalone source spelling can produce it.
- KartItem_UpdateShadowBillboardAndViewport 0x8004EDD4: PROMOTED asm_fn -> C (helper local decl order `(e, off, i)`), full-dol SHA-1 OK.
- KartItem_GetMaxSpeedWithBonus 0x8004F040: helper inline reproduces the whole fn structurally (51/51 insns incl. the mr + the li/lwz schedule swap) but parks on a GPR coloring permutation: emitted mv=r7/e=r5 vs target mv=r5/e=r7 (11 of 51 insns reference them). ~60 source variants floored there. Kept asm_fn.

## Observations (facts, all with GC/1.3.2 production flags unless noted)
1. The FRONT END folds every source-level copy of a known constant: 13 spellings of `off = i` / `off = 0` (addr-taken via pointer, unused-label EBB split, do-while(0), register, unsigned, `|0`, `*8`, `<<3`, volatile read, init-stmt vs for-init, swap/chain) all emit `li`. `-opt noprop` output is unchanged -> the fold happens before the -opt propagation pass. (results_mrsr_axis1/5.tsv)
2. SR-created byte IVs (plain `e->pairs[i].key` indexing, or `off = i*8` in the body) get init `slwi rOFF, rI, 3`; on GC 1.3+ a post-SR propagation rerun folds it to `li` (GC <=1.2.5n leaves the slwi). Never mr, and the i/off physical regs come out permuted vs target. (results_mrsr_axis2/3.tsv)
3. -O level sweep (-O2/-O3/-O4 x ,p) and the -opt sub-pass switches (nocse/nostrength/noloopinvariants/nopeephole/nodeadstore/nolifetimes) never produce mr. (results_mrsr_axis2/4.tsv)
4. Binary-wide mining (build/GNLJ82/asm): `li rA, K` followed <=5 insns later by `mr rB, rA` occurs in ~280 fns; K=0 in 420 pairs but also arbitrary K (0x1 x43, 0x100, 0x10, 0x140a, 0x1ecd, ...) -> the survivor is a generic same-constant-web copy, not zero-specific. 74 instances are loop-preheader shaped (mr then unconditional b).
5. Reproduced generators of the surviving copy (all are OPTIMIZER-INSERTED copies created after the last propagation run):
   - LICM-hoisted loop-invariant constant with availability check: OSInitAlloc (known SDK source) `hd->free = hd->allocated = NULL` chain temp -> preheader `mr r3, r6` reusing the SR-IV zero. Reproduced with prod flags (mrsr_min4.c o3 = li/li/mr byte shape).
   - INLINER-spliced loop init (this family): a static/static-inline helper containing the dual-induction loop, called from a wrapper -> the for-init copy survives as `mr` with the exact target schedule `li i; lwz mv; lfs; mr off; lfs; b`. EVERY init spelling inside the helper works (`off = i`, `off = 0`, chain, swap, stmt form). (mrsr_min5/6.c, mrsr_inits.c)
   - Observed-only in target: speculated-else hoisted constant pairs (Terrain_GetTractionFactor `li r4,0; mr r0,r4` above a beq with conditional oris arms).
6. KartMovement_CalcMaxSpeed 0x801999E0 is the standalone twin of the loop (param mv=r3, same constants from its own TU pool). Both 0x8004F040 and 0x8004EDD4 consume an inlined copy (tail multiply / divide shapes line up exactly) -> original code evidently had a cross-TU-visible inline definition (header inline). In-TU `static inline` reproduces it and is NOT emitted by CW 1.3.2 (TU byte layout safe); plain `static` IS emitted even when inlined at every call site (layout breaker). A helper defined after the call site (with prototype) does NOT inline at all.
7. Inlined web coloring is steered by the helper's local declaration order. ShadowBB context (self saved to r29, inline site in the else arm): decl `(e, off, i)` -> i=r5, off=r6, e=r7, mv=r3 = target, instruction-exact; the 4 remaining textual diffs are disasm cosmetics only (psq qr0 spelling, pre-postprocess_sdata2 @cookie reloc, sda21 r2-vs-r13 base guess). GetMaxSpeed context (wrapper at fn entry, self=r3): the three GPR locals color DESCENDING r6,r5,r4 in decl order and the mv/param-merged web pins to r7; sweeps over 24 decl perms x 6 init spellings x 6 wrapper forms x param type (Mv* vs Self* + helper-local mv) x raw-key vs mul-inside helpers all floor at the same mv<->e 11-insn permutation. No-wrapper-local forms (bonus via self->movement->coinBonus after the call) regress to 52 insns (the second 0x28 load does not CSE in that arrangement).

## Hypotheses (inference, keep separate from the above)
- CW pipeline reading: the front end folds constant copies during per-function IR gen; the inliner splices the callee body and re-materializes the for-init as a fresh inter-web copy that no later pass folds (copy-prop cannot substitute because i is redefined in the loop; const-prop does not re-run on the spliced webs).
- The GetMaxSpeed mv<->e color swap likely depends on the colorer's web visit order (interference graphs of probe and target appear identical); the unfound lever is probably in the hit-path `mv->table[mv->tableIdx].pairs[i].value` temp-web creation order or the wrapper tail expression. A future probe could also try perturbing the loop-body scratch webs.

## Recipe (future fns in this family; KartMovement_CalcMaxSpeed 0x801999E0 itself is a candidate)
1. Identify: dual-induction search loop with preheader `li rI, 0 ... mr rOFF, rI` (mr src = the freshly li'd count IV).
2. Wrap the loop (+ trailing cap/clamp if the standalone twin includes it) in a `static inline` helper returning the result; call it from the fn body. Keep `for (i = 0, off = i; ...)`.
3. Tune the helper's local decl order for GPR coloring; in a saved-self / else-arm context `(e, off, i)` was target-exact.
4. `static inline` is not emitted under prod flags (verified) -> safe inside byte-exact mega-bundle TUs. Plain `static` would insert a fn and break the layout.

## Files
- tools/compiler_probe/mrsr_min*.c, mrsr_perm*.c, mrsr_cross.c, mrsr_inits.c, mrsr_order.c, mrsr_rawkey.c, mrsr_selfp.c, mrsr_wdecl.c - probe TUs
- tools/compiler_probe/run_mrsr_axis1/2.py, run_mrsr_exact.py, run_mrsr_intu*.py - drivers (the intu scripts patched the pre-promotion TU text; historical after this batch)
- tools/compiler_probe/results_mrsr_axis*.tsv, target_getmaxspeed.txt, target_shadowbb.txt

## Correction (2026-06-11, batch_research_phase2e)

The hypothesis "const-prop does not re-run on the spliced webs" must be narrowed: post-splice
optimization DOES include iterative DCE. Adding a dead up-counter to this very CalcMaxSpeed
helper gets it deleted (both dead-in-callee and live-in-callee/ignored-at-site forms; probes
p2e_deadctr3.c g1/g2) while the mr init still survives in the same build. Only copy/const
FOLDING is FE-only. Consequence: no spliced web survives by deadness; surviving "dead-looking"
webs always have a coalesced-invisible use.
