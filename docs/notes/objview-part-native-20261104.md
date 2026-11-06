# objview / map-effect parts (anon_80197130) — 2026-11-04

Source: Codex worker cx_a3_objview_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

## Native (source-linked, text/EH/data exact)
- fn_80198F84 (812B): representing the nearest-driver position as a by-value aggregate copy reproduces the temporary stack slot; plain `char` tracking/hit fields give signed compares without extsb.
- fn_801992B0 (1608B): named local vector copies passed to pointer ABIs reproduce the stack layout; compiler-generated 32-byte jump table matches (automatic local jump-table symbol name differs, relocations/data equal). The ground-advance return value is intentionally unused, as in the target.

## Honest NonMatching (kept as native drafts, budget exhausted)
- fn_80197130 99.68% / fn_80197F24 99.57%: native C++ scoped GXChannel lifetime, EH equal; residual GPR reuse / FPR assignment (F24: second-loop count/stride registers swapped; explicit stride trial worse).
- fn_801980C8 99.73%: writable random tables must be declared without `const` (moved index stores before indexed float loads, 93.90% → 99.73%); residual FPR identities.
- fn_80198ABC 99.74%: an explicit no-op `case 2` in the first inner switch is required to keep one branch and match text/EH lengths; residual FPR identities in height/lift clamps (named float intermediates did not move them).
- fn_80197D20 95.92% (worker-side bridged measurement): real derived C++ part constructor with `new`; resource-pool base/address scheduling differs. The worker's ad-hoc `configure.py` hook that rewrote build.ninja to inject llvm-objcopy renames was NOT accepted (non-standard tooling); a future attempt should use per-TU entries in `tools/extab_user_renames.json` (see cpp-ctor-retrofit-mangled-bridge.md). Without that bridge its object-level objdiff reads lower; it is NonMatching either way.
- fn_801972E0 (2468B) and fn_801987C4 (760B, part ctor with EH actions): not attempted (time), still in auto blobs.

## anon_8018F100 objview/zprobe singletons (cxb_b3, 2026-11-04)
- fn_80190064 (712B) native exact: carry the attribute value from the loop condition into the body (removes a redundant reload); shared reset helper for attribute setup.
- Honest NonMatching (3 approaches each unless noted): fn_8018F1E0 98.50% (literal FP constants beat extern constants; residual self/sid register identity), fn_8018F614 94.76% (2 approaches; real derived C++ part ctor with `new`, EH exact; base-vptr/address scheduling differs), fn_8018F8A8 98.91%, fn_8018FC24 97.19% (declaration order / destination-first expression best), fn_801903D0 98.98% (native `new` table entries; extra address-register copy). Per-TU bridges for the two C++ TUs are in tools/extab_user_renames.json.

## cxc_u6_objview186_20261105
Source: Codex worker cxc_u6_objview186_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

801869F8/80187084/80187410 operate on a two-element 0x54-byte path state: joints[4], points, count/index, three control vectors, t, position and yaw. 80187084 advances quadratic interpolation and heading; 801869F8 performs culling/rotation and two HSD render passes. Native drafts and residuals are in this batch HANDOFF. C++ ctor 80187410 emits exact owned extab with canonical base destructor and guarded clNormal3D new.

## c4_t1_objview_20261105
Source: Codex worker c4_t1_objview_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 1224 B.

c4_t1_objview_20261105: fn_80198ABC promoted native1224B. Scalar float literals (0,11,0.2,1,-0.1,2,0.05,5) instead of extern const objects resolve height/lift clamp FP identities; existing sdata2 postprocessor bridges constants, all text/EH/index100 and source-linked DOL SHA1 OK. Inline clamp parameterization is a no-op. fn_801980C8 remains99.72938: literal constants and integer-index helper return both leave identical15 FP operand residuals; moving arithmetic inside helpers does not fix homes and adds factor1 multiply. All C8 experiments reverted.

## c5_s21_fn801807e0_20261105
Source: Codex worker c5_s21_fn801807e0_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c5_s21: inline extraction of only the position-interpolation loop as MorphBlend(MorphNode*,int,float) improves fn_8018F1E0 98.50282 -> 98.98305 while preserving 708B and exact EH/index. Still NonMatching: self/side r27/r28 swap and inner address/stride colors remain. Whole-node helper and widened side/index scopes are worse. Path186 index-first pointer helper and wrapped-integer-return helper are byte-identical negative probes. Menu direct clear / column-zero before clear are byte-identical negatives. Table global-direct loses hoist; reference retains extra base copy; later base initialization worsens zero scheduling. All failed variants reverted.

## c5_s22_fn8018f614_20261105
Source: Codex worker c5_s22_fn8018f614_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 384 B.

c5_s22: fn_8018FC24 matches 384B text plus 8B extab and 12B index by replacing external 360.0f constant uses with literals and extracting UpdateUV(Wave*) with local declarations src,dst,i and fu,fv. Phase FP registers and loop index/stride/pointer homes become exact. Coordinator full build SHA-1 OK, source .o on main.elf edge. fn_80197130 scene declaration after particle pointer resolves scene r30 reuse; per-TU typed GXChannel ctor/dtor bridge fixes EH and call relocations, leaving f30/f31 height-width swap. fn_8018F614 pairs-before-name declarations fix those homes; base-vptr scheduling remains.

## c5_s23_fn80197f24_20261105
Source: Codex worker c5_s23_fn80197f24_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 816 B.

c5_s23: fn_80197F24 reaches exact 420-byte text and 24/12-byte EH/index by passing the outer item-loop int i by reference to inline DrawParticles. This preserves count r29/stride r30 across both loops. Per-TU GXChannel ctor/dtor bridges required. Full source-linked DOL SHA-1 OK.

## c14_u26_20261106
Source: Codex worker c14_u26_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 556 B.

c14_u26: fn_8018D0F4 556B promoted native. Null-first inline Child/Next accessors restore target branch arm order (93.66907 ->99.568344). Plain float literals restore angle FP homes; direct o->angle += 1.0f restores field-before-constant load order. All text/extab8/index12 100%, existing TU flag Matching, source main.elf edge and full DOL SHA-1 verified. No split, EH bridge, data ownership or header edits.

## c14_u50_20261106
Source: Codex worker c14_u50_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u50: fn_8018DAD0 remains NonMatching, 91.69401 ->94.49527. Writable random tables fix random-factor/position load-store scheduling. Typed aggregate table view improves addressing versus char-pointer offsets but still folds per-type table bases into index+offset. Inline array-pointer helpers do not prevent folding; float literals slightly worsen scheduling. Residual table-base shape, factor FP homes, and final-loop GPR reuse; 3 hypotheses used, no native gain.

## c14_u53_20261106
Source: Codex worker c14_u53_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u53: fn_801972E0 correct writable random tables lbl_80495994/lbl_80495A94 (.data) removes const-driven scheduling divergence: 91.0859 ->99.88655, exact text size2468/extab8/index12. Only enabled flag r30/r28 at +34/+140 and final-loop li r30,0 versus mr r30,r28 at +7CC remain. Reusing outer loop i reproduces shared zero but swaps other homes; p reuse 99.70827, decl order unchanged. Inline UpdateParticles with index pointer 99.71637 leaves pointer/stride r29/r30 swap; explicit stride99.700165. All loop probes reverted. Honest NonMatching retained; no new native functions.
