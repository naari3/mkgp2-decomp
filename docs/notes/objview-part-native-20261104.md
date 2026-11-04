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
