# Flip hints for onmokoworks-claimed TUs at 100% (2026-11-07)

Read-only diagnosis by naari3's thread B of the 21 TUs that docs/claim_audit.md lists as "all functions 100%". Nothing in these TUs or their issues was changed on main. Each fix below was applied on a throwaway local branch, and all four applied together give a clean build (`rm -rf build/GNLJ82/src`) with `main.dol: OK`. Ready-to-apply patches are in `/mnt/project-files/wip/flip_hints/<TU>.patch` (`git apply`).

## Already Matching (17): only the claim is still open

These are already `Object(Matching, ...)` in configure.py on main, so nothing blocks a flip. The issues can just be closed:

#491 FileLoader_Open, #2184 GabyouItemFlight, #2199 objview/fn_801972E0, #2321 fn_801F7344, #2209 KartShellRibbonDraw, #2218 dlistutil/fn_80184F24, #2265 anon_8021F088_nm_80220A54, #2232 anon_802124FC_nm1, #2235 anon_80207E3C_nm1, #2236 fn_801FB778, #2253 ItemBoxConstruct, #2258 PlayerData_Construct, #2277 anon_802052E0_nm1, #2283 RaceDigitUpdate, #2289 KartChoiceSelect, #2293 anon_80205DCC, #2314 objview/fn_801987C4.

## Still NonMatching (4): blocker and verified fix

| Issue | TU | What breaks when flipped | Fix (verified main.dol OK) |
| --- | --- | --- | --- |
| #492 | game/DNLensflare.cpp | DOL grows by 0x60: an unrenamed weak copy `__dt__16clMapEffectPartsFv` (0x48 + its extab/extabindex entry) is linked in | Add `"__dt__16clMapEffectPartsFv": "dtor_8016A270"` to the TU's block in tools/extab_user_renames.json (the same mapping the other clMapEffectParts TUs use), then the linker drops the copy. Flip to Matching. |
| #495 | game/anon_80214B3C.cpp | `multiply-defined lbl_804EDA98` + `undefined GameModeBase::Draw/Update`: `~CoinChallengeMode()` is the key function, so the TU emits the vtable, which lives in unowned auto .data | Declare an undefined key stub before the dtor: `virtual void _key();` in `struct CoinChallengeMode` (a new slot appended after the inherited ones, so no offsets move). Flip to Matching. |
| #493 | game/anon_80226670.cpp | `multiply-defined lbl_804EDF64` + `undefined clCSSceneJoinMsg::Draw()` (vtable emitted, same cause); after the stub, DOL grows by 0x60 from an unrenamed weak `__dt__9SceneBaseFv` | Add `virtual void _key();` as the first virtual in `struct clCSSceneJoinMsg`, and add `"__dt__9SceneBaseFv": "dtor_8007D0D4"` to the TU's renames. Flip to Matching. |
| #2281 | game/STLContainer.cpp | Same size, but text is shifted 0x4C: CW emits `__sinit_STLContainer_cpp` (STLContainer_GlobalInit_854) LAST, and the target has it FIRST at 0x80038934 | fakematch: write the static init by hand as the first function (`STLContainer_HeaderInit((STLTree *)lbl_80598554, &policy, &compare); __register_global_object(lbl_80598554, STLContainer_Dtor, sDtorChain);`, declaring `STLCompare compare;` before `STLPolicy policy;` for the 0x8/0xC slots), register it with `__declspec(section ".ctors") static void (*const sInitEntry)(void) = ...;`, and replace `STLTree lbl_80598554;` with raw storage `int lbl_80598554[sizeof(STLTree) / 4];` after a local `static char sDtorChain[12];` so the .bss order holds. Natural code: `STLTree lbl_80598554;`. Flip to Matching. |

General lessons (also in setup/TIPS.md, thread B):
- `multiply-defined lbl_<vtable>` on a flip = the TU emits a vtable that lives in unowned .data. Declare an undefined `virtual void _key();` FIRST among the class's virtuals so it becomes the key function.
- DOL bigger by exactly a weak function's size = an unrenamed weak inline copy. Map it to the existing out-of-TU name in extab_user_renames.json, and the linker drops it.
- Text shifted by the __sinit size = CW put the static initializer at the TU end. Hand-write it first plus a `.ctors` entry.
