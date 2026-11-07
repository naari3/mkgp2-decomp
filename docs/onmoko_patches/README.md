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
