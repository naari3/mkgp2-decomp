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
