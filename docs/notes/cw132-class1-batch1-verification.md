# Class-1 recipe: first real-TU verification (2026-06-11, batch_promote_phase1_class1batch1)

Recipe `u8 b; if ((flags & MASK_ULL) == 0) { b = 0; } else { b = 1; }` verified byte-exact at 2 real sites in auto_ONKARTHIT_block.c, both zero-half polarities:

- CarObject_UpdateCoinSpeedBonus 0x8004D110 (mask 0x800000ULL, hi half = 0): matched -> fn promoted to 100% / SHA OK.
- KartItem_UpdateShadowBillboardAndViewport 0x8004EF18 (mask 0x0000200000000000ULL, LO half = 0): site matched inside a 97.95% build.

Coalesce precondition holds with either u64 mask half being the zero register. No site-specific tuning was needed.

## New sub-class: int-equality-chain bool (KartItem_ApplyImpactReflectAndDampVelocity 0x8004B1A8)

Target: `li r6,0` hoisted; per link `cmpw; bne Lnext; b LDONE`; only the final else materializes `li r6,1`. NOT the u64 family. 4 probes negative:

1. arms `{b=0;}` + init -> init dead-def-eliminated, arms keep own li (bne/b shape OK, +4 li) = best fallback (95.19%).
2. empty arms + init -> branch folding collapses to `beq LDONE` (fold applies to int compares too).
3. arms `b = zero;` copies of u8 zero=0 -> const-prop folds, identical to 1.
4. first-arm-empty mix -> init li SURVIVES and arm lis are STILL kept: the class-1 arm-li deletion is NOT a "register already holds 0" cleanup; it requires coalescing with an independent live zero web (the u64 mask half). The chain has no such web -> no source handle found.

## mr-SR-init negatives (ShadowBB = GetMaxSpeedWithBonus family)

- `int zero = 0; i = zero; off = zero;` -> both copies const-folded, zero DCE'd.
- `#pragma opt_propagation off` around the fn -> output bit-identical to baseline (does not disable the fold). Closes the pragma axis for this class.

## New win idioms (verified byte-exact)

- volatile-cast float const load dedup: `sel = *(volatile const float *)&lbl_806D26EC;` forces a second independent lfs when CW would otherwise CSE the const load with a later use and bridge with fmr (cascades cookie/register churn). Plain `if (b == 1) sel = lbl_806D2708;` after it reproduces the speculated-else layout; an if/else two-arm form does not.
- in-place MSL sqrtf: assign the NR result back into the same variable (`y = (float)(sq*guess); sq = y;` inside the guard) -> volatile reload lands in the variable's own register (f4), no else-path fmr. Helper-with-return form leaves a separate result web.
- 2-const scale block register split: hoist only the OUTER const into a local, keep the inner const literal (`cB = lbl_806D2714; *out = cB * (lbl_806D2730 * v);`) -> inner CSE temp = f1, local = f2. Both-local / both-literal permutations give a swap or per-component reloads.
- alias-driven reload: repeated `self->movement->fieldX` across `*(float* out)` stores reloads the pointer per store; reassign `mv = self->movement;` inside the arm for a single lwz.
- u64 split-arg ABI: `ItemEffectBus_OrMask(bus, 0x80ULL)` puts the mask in r5:r6 (r4 skipped) - prototype `(void *bus, unsigned long long mask)` is enough.
