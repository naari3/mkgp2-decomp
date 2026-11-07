# Pragma fixes for onmokoworks-claimed TUs (verified, not applied)

These patches come from the zero-diff hits in docs/pragmasweep_results.md
(tools/pragmasweep.py). They were verified by R5 on a throwaway branch off main
ce0e1c8, 2026-11-07. The TU sources on main are untouched: the
TUs are claimed by onmokoworks, so the owner applies them (`git apply docs/onmoko_patches/<name>.patch`).

Verification: all five source patches applied together, then a clean build
(`rm -rf build/GNLJ82/src build/GNLJ82/ok`, ninja). main.dol SHA OK and every
listed function at 100% in report.json (7248 matched functions on that build;
before count not measured). Each Matching flip was then checked
on its own with a fresh link; main.dol stayed OK.

| Patch | Function | TU | Before | Fix | After | TU flip |
| --- | --- | --- | --- | --- | --- | --- |
| fn_80243C70.patch | fn_80243C70 | game/ItemPanelDraw.cpp | 99.97% | `#pragma push` / `opt_lifetimes off` / `pop` around the fn | 100% | yes, included (whole TU 100%, SHA OK) |
| card_unpack_v1.patch | card_unpack_v1 | game/CardUnpackV1.c | 98.99% | opt_lifetimes off | 100% | yes, included |
| fn_801F8A34.patch | fn_801F8A34 | game/fn_801F8A34.cpp | 98.16% | opt_common_subs off | 100% | yes, included |
| fn_8021E0FC.patch | fn_8021E0FC | game/anon_8021BC44.cpp | 92.99% | opt_propagation off | 100% | no: TU still has fn_8021C070/C778/D780/DAB8 < 100% |
| clItemBoxManager_Update_Inner.patch | clItemBoxManager_Update_Inner | game/clItemBoxManager_nm1.cpp | 99.74% | opt_lifetimes off | 100% | no: SoundDriver_GetOrCreate and 3 DoublyLinkedList fns < 100% |
| fn_80246DE4.patch | fn_80246DE4 | game/RaceDigits.cpp | 99.96% | optimization_level 3 around DigitHud's ctor, plus flip work: functions reordered to the target order (DigitHud ctor, Update, DigitPanel ctor), DigitOwner/DigitListBase members made out-of-line in this TU via `RACE_DIGITS_OUTLINE` in include/game/RaceDigitsPrivate.h (other TUs keep the inline versions), `main(0)` through a new inline pointer ctor so DigitHud's ctor doesn't need DigitOwner(), `#pragma defer_codegen on` before the last two dtors so ~DigitList still inlines ~DigitListBase, and the TU added to DATA_ALIGN4_WEAK_TUS (its .data was 8-aligned) | all 7 fns 100% | yes, included (updated 2026-11-07 18:50; clean build main.dol OK) |
| fn_8028EAA8.patch | fn_8028EAA8 | triforce/amnet_nm2_rest.c | 99.28% | opt_dead_assignments off + `case 3: break;` in the dev->kind switch (gives the target's second `b`) | 100% | no: fn_8028D8CC (98.42%) is in the same TU |
| FrameUpdate.patch | FrameUpdate | game/FrameUpdate.c | 93.66% | GC/1.3.2 (was 3.0a5) + opt_common_subs off; the FrameBackup field at 0x18 is one `unsigned long long qw18` (0x14 is padding before it), so the copy loads 0x18/0x1C into a register pair the way the target does. include/game/FrameUpdate_private.h changes; TaMode_FrameUpdate (the other includer) is unchanged at 99.48% | 100% | yes, included (clean build main.dol OK) |

Not needed any more: STLContainer_DisposeRecursive and fn_801987C4 are already
100% on current main (fixed after the sweep table was generated).

## Matching-flip patches for TUs already at 100% (thread B, 2026-11-07)

From docs/flip_hints.md. Verified on a throwaway branch off main: all four applied together, clean build, main.dol OK (+13 functions).

| Patch | TU | Issue | Blocker | Fix |
| --- | --- | --- | --- | --- |
| DNLensflare.patch | game/DNLensflare.cpp | #492 | unrenamed weak `__dt__16clMapEffectPartsFv` grows the DOL by 0x60 | rename it to dtor_8016A270, then flip |
| anon_80214B3C.patch | game/anon_80214B3C.cpp | #495 | the TU emits vtable lbl_804EDA98 (multiply-defined) | `virtual void _key();` key stub in CoinChallengeMode, then flip |
| anon_80226670.patch | game/anon_80226670.cpp | #493 | emits vtable lbl_804EDF64 + unrenamed weak `__dt__9SceneBaseFv` | key stub + rename to dtor_8007D0D4, then flip |
| STLContainer.patch | game/STLContainer.cpp | #2281 | CW puts __sinit last, the target has it first (text shifted 0x4C) | hand-written static init first + `.ctors` entry (fakematch), then flip |

## Pool / TU-merge patches (thread B, 2026-11-07)

See docs/merge_plans.md for the full list of plans. Files are in `merge/`.

| Patch | Function | Kind | Result |
| --- | --- | --- | --- |
| merge/anon_8020AF08_nm1_pool.patch | fn_8020B234 (#2361) | link-ready: TU owns .rodata 0x803C2E50..0x803C3508, three static arrays | 97.54% -> 99.86%, clean build main.dol OK |
| merge/fn_80192F04_codegen_probe.patch | fn_80192F04 (#2394) | probe only (the data is owned by the Fog TU; merge needed) | all instructions match |
| merge/fn_801913B0_codegen_probe.patch | fn_801913B0 (#2439) | probe only | pool fixed, about 10 lines left |

## Full sweep over onmokoworks-claimed TUs (2026-11-07 18:00)

Every below-100% function in an onmokoworks-claimed TU (323 of them, report at
main 295cfd3) was swept:
- 62 functions missing from docs/pragmasweep_results.md (large or < 80%): 6
  compilers x 0-2 of the 8 opt_* pragmas + 30 declaration orders. No new 0.
- The other 261: own cc / 1.3.2 / 2.6 / 1.3 x 0-2 of a second pragma set
  (optimization_level 3/2, optimize_for_size, fp_contract off, unroll/vectorize
  off, opt_lifetimes, opt_common_subs). New 0: fn_80246DE4 (above). Also
  fn_8021E0FC again (optimization_level 2 works too).
- Near misses left by the sweep: fn_8028EAA8 (amnet_nm2_rest) 49 -> 1 with
  GC/1.3.2 + optimization_level 3; FrameUpdate 107 -> 2 with GC/1.3.2 +
  opt_common_subs off (own cc is 3.0a5). Solved later: see FrameUpdate.patch.

## Hand fixes (R2, 2026-11-07)

Verified on main with the patch applied: clean build (`rm -rf build/GNLJ82/src build/GNLJ82/ok`), main.dol OK.

| Patch | Function | TU | Issue | Before | Fix | After | TU flip |
| --- | --- | --- | --- | --- | --- | --- | --- |
| VfxSlotMgr.patch | VfxSlotMgr_Update | game/VfxSlotMgr.cpp | #2369 | 99.94% | copy `*position` then `*target` into locals in the caller and call BuildCamera directly (SetCamera's by-value params took their stack slots in the opposite order) | 100% | yes, included |
