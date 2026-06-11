# CW 1.3.2 dead-counter-in-ctr-loop hard-block (2026-06-10, batch_promote_8004f858_handleitemfx)

Target idiom: ctr-converted scan loop that ALSO materializes a never-read up-counter (`li r4,0x0` init + `addi r4,r4,0x1` per iteration, no reads before the register is clobbered). Seen in CarObject_HandleItemEffect 0x8004F858 loop 1 (pair-table scan over lbl_802ED94C, 0x13 iterations, two compares per iteration via lwz/lwzu). Same family as the dead `i` counter in CarObject_MainUpdate's mtx loop (sec 14.2 flavor 5) and the const-prop-escaped `mr r6,r4` init in KartItem_GetMaxSpeedWithBonus.

Probed source forms - ALL get the counter web deleted (or the loop fails to ctr-convert):

1. do-while with `++i` + `while (i < 0x13)`: keeps i but NO ctr conversion (cmpwi/blt, init split addi r0+mr).
2. `for (i = 0; i < 0x13; i++)` + manual `*p` / `*++p` / `++p` walk: ctr-converts, lwzu reproduced, counter eliminated with the loop control.
3. separate body counter (`for (n...)` control + `++i` in body): ctr-converts, i web DCEd.
4. shared u8 variable (loop-1 counter reused later as loop-2 found flag, hoping variable-granularity liveness): increments still DCEd.
5. dead copy `n = i;` after the loop (single-pass-DCE test): both copy and web removed - CW DCE is iterative.
6. `#pragma opt_dead_assignments off` around the fn: no effect (inert or not honored at -O4,p global optimizer).
7. pointer-bound for (`p < base + 0x26`) with i++ header increment: does NOT ctr-convert (cmplw kept per iteration; CW does not derive trip count from pointer bounds here).
8. inline `asm { addi i, i, 0x1 }` in the loop body (requires `register int i`, else "not assigned to a register" error): the asm statement itself is integrated into IR and DCEd; `#pragma volatile_asm on` does NOT protect it.

Conclusion: with -O4,p -inline auto, CW 1.3.2 always removes a never-read counter web in a ctr loop. No pure-C or pragma path found to retain it. Functions whose target carries this idiom cannot currently be promoted byte-identical.

Precan rule: in a ctr loop (`mtctr` + `bdnz`), an `addi rX,rX,1` whose register has no read before the next write to rX marks this class. Budget 0-2 probes, then park as asm_fn.

Secondary observation from the same batch: the missing web also seems to perturb downstream callee-saved tie-breaks (lane-clear inline sites 2/3 land permuted registers while site 1 matches exactly with identical inlined source) - allocator history is global, so solving the counter may cascade-fix the site permutations.

Additional negative result (inlining control): `-inline auto` refuses loop-containing fns regardless of `#pragma inline_max_size(1024)`; `-inline auto,deferred` as TU extra_cflags inlines nothing more and BREAKS the manual extab layout ([extab-0] dropped to 12.94%) - never use in extab_user TUs. Working mechanism for a loop-containing inline site: dedicated `static inline` helper (explicit inline takes loops).

## SUPERSEDED (2026-06-11, batch_research_phase2e)

This class is NOT a hard block. The counter is live via an INVISIBLE USE: in
CarObject_HandleItemEffect the loop counter is passed as an extra (ignored) argument to the
post-loop call (`ItemStateGuard_IsActive(guard, i)` with a K&R empty-paren extern); regalloc
coalesces i into the arg register (r4, vacated by the itemId->r31 save) so the use emits zero
instructions. Verified in-TU: loop region byte-identical, fn at 99.93%. Binary-wide, every
"dead" ctr-loop up-counter inspected has such a hidden use (most commonly: the counter IS the
return value on the break path, coalesced to r3/blr). The secondary cascade hypothesis (counter
web fixing the lane-clear site permutations) is REFUTED - those needed per-site decl-order
tuning + a fn-scope obj variable (see cw132-phase2e-research.md). Precan update: a ctr-loop
addi rX,rX,1 with no visible read => check whether rX is an arg slot of the next bl or the
return register on an exit path; reproduce with an ignored extra arg / returned counter, do NOT
park.
