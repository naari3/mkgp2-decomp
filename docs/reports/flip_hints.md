# Flip hints for onmokoworks-claimed TUs at 100% (2026-11-07)

Read-only diagnosis by naari3's thread B of the 21 TUs that docs/reports/claim_audit.md lists as "all functions 100%". Nothing in these TUs or their issues was changed on main. Each fix below was applied on a throwaway local branch, and all four applied together give a clean build (`rm -rf build/GNLJ82/src`) with `main.dol: OK`. Ready-to-apply patches are in `docs/wip/flip_hints/<TU>.patch` (`git apply`).

## Already Matching (17): only the claim is still open

These are already `Object(Matching, ...)` in configure.py on main, so nothing blocks a flip. The issues can just be closed:

#491 FileLoader_Open, #2184 GabyouItemFlight, #2199 objview/fn_801972E0, #2321 fn_801F7344, #2209 KartShellRibbonDraw, #2218 dlistutil/fn_80184F24, #2265 anon_8021F088_nm_80220A54, #2232 anon_802124FC_nm1, #2235 anon_80207E3C_nm1, #2236 fn_801FB778, #2253 ItemBoxConstruct, #2258 PlayerData_Construct, #2277 anon_802052E0_nm1, #2283 RaceDigitUpdate, #2289 KartChoiceSelect, #2293 anon_80205DCC, #2314 objview/fn_801987C4.

## Still NonMatching (4): blocker and verified fix

| Issue | TU | What breaks when flipped | Fix (verified main.dol OK) |
| --- | --- | --- | --- |
| #492 | game/DNLensflare.cpp | DOL grows by 0x60: an unrenamed weak copy `__dt__16clMapEffectPartsFv` (0x48 + its extab/extabindex entry) is linked in | Add `"__dt__16clMapEffectPartsFv": "dtor_8016A270"` to the TU's block in tools/extab_user_renames.json (the same mapping the other clMapEffectParts TUs use), then the linker drops the copy. Flip to Matching. |
| #495 | game/anon_80214B3C.cpp | `multiply-defined clCGameYI_vtable_804EDA98` + `undefined GameModeBase::Draw/Update`: `~CoinChallengeMode()` is the key function, so the TU emits the vtable, which lives in unowned auto .data | Declare an undefined key stub before the dtor: `virtual void _key();` in `struct CoinChallengeMode` (a new slot appended after the inherited ones, so no offsets move). Flip to Matching. |
| #493 | game/anon_80226670.cpp | `multiply-defined clCSSceneNextRaceGP_vtable_804EDF64` + `undefined clCSSceneJoinMsg::Draw()` (vtable emitted, same cause); after the stub, DOL grows by 0x60 from an unrenamed weak `__dt__9SceneBaseFv` | Add `virtual void _key();` as the first virtual in `struct clCSSceneJoinMsg`, and add `"__dt__9SceneBaseFv": "dtor_8007D0D4"` to the TU's renames. Flip to Matching. |
| #2281 | game/STLContainer.cpp | Same size, but text is shifted 0x4C: CW emits `__sinit_STLContainer_cpp` (STLContainer_GlobalInit_854) LAST, and the target has it FIRST at 0x80038934 | fakematch: write the static init by hand as the first function (`STLContainer_HeaderInit((STLTree *)STLContainer_GlobalInit_854_bss_80598554, &policy, &compare); __register_global_object(STLContainer_GlobalInit_854_bss_80598554, STLContainer_Dtor, sDtorChain);`, declaring `STLCompare compare;` before `STLPolicy policy;` for the 0x8/0xC slots), register it with `__declspec(section ".ctors") static void (*const sInitEntry)(void) = ...;`, and replace `STLTree STLContainer_GlobalInit_854_bss_80598554;` with raw storage `int STLContainer_GlobalInit_854_bss_80598554[sizeof(STLTree) / 4];` after a local `static char sDtorChain[12];` so the .bss order holds. Natural code: `STLTree STLContainer_GlobalInit_854_bss_80598554;`. Flip to Matching. |

General lessons (also in docs/thread_tips.md, thread B):
- `multiply-defined lbl_<vtable>` on a flip = the TU emits a vtable that lives in unowned .data. Declare an undefined `virtual void _key();` FIRST among the class's virtuals so it becomes the key function.
- DOL bigger by exactly a weak function's size = an unrenamed weak inline copy. Map it to the existing out-of-TU name in extab_user_renames.json, and the linker drops it.
- Text shifted by the __sinit size = CW put the static initializer at the TU end. Hand-write it first plus a `.ctors` entry.

## acsocket `addi rX, rBufOff, 0x0` (acBind, acAccept, acModifyMyIPaddr, acInetAddr, acConnect): investigation (2026-11-07, mid-range thread)

All five targets do the same thing: `lwz r5, 0x10(State)` (`State.bufOff`), then `addi r24, r5, 0x0` into a callee-saved reg, then later `add r24, r0(bufAddr), r24`. acAccept also has `addi r29, r4, 0x4`. Status: **not solved**. What is now ruled out:

- **Compiler versions.** We compiled acsocket_nm5 with all 20 GC compilers (1.0 to 3.0a5.2). Up to 1.2.5n, *every* register copy is emitted as `addi rX, rY, 0`, including the argument saves (`addi r27, r3, 0`). The target uses `mr` for those, so it is not ≤1.2.5n. From 1.3 on, copies are always `mr`, and no source form produced an `addi …, 0`.
- **Source forms, tried under 1.3 / 1.3.2 / 2.6:**
  - `bufOff + n`, with n coming from: a literal, a local, a `static inline` param, a plain `static` fn under `-inline auto` / `deferred`, a 1-trip loop, a `const` array element, pointer differences (`buf - Buf`), or a ternary.
  - bufOff retyped as a `u8*`, `u32*` or `BH*` pointer field, with `&p[0]`, `&h->len`, and `&h->len` together with `&h->addr` (+0/+4).
  - Out-pointer helpers (`GetSocketBuffer(0, &off)`).
  - A two-definition `off` (`off = …; off = k->bufAddr + off`).
  - `opt_propagation`, `opt_common_subs` and the other `opt_*` pragmas.

  None of these produced it.
- **Where 1.3+ does emit it in matched code.** Scanning every Matching game/HSD TU shows that `addi rX, rY, 0x0` only comes from a *section-anchor (pooled) base*: the TU defines the objects, and the object sits at anchor+0. Examples are DisplayBuffersReset, StrPcb_Lifetime and KartItemAudio_PlaySEByItemId. There the immediate is a section offset that is only resolved at emit time, so it is never folded. In acsocket, rY is a *loaded value* (`State.bufOff`), not an address, so that mechanism does not apply directly.
- **A side effect to avoid.** `*off = k->bufAddr + *off;` in acBind's `ClearBindBuffer` cuts the diff to only this one instruction (41 → 3 lines). But objdiff fuzzy drops from 96.76 to 96.41, so it was not applied.

Untested idea: the `+0` / `+4` immediates may be section offsets of TU-local objects, i.e. the device-side offset is computed from a `.bss` object's position (`(u32)&local_obj - (u32)&anchor`). That would need the TU to own `acsocket_nm7_bss_806A12A0` / `acsocket_nm7_bss_806A14A0`, which belong to acsocket.c. Repro harness: `/tmp/claude-0/rp/rp.py` (ephemeral). It compiles a file with the triforce_am flags under a list of compilers and flags each `addi rX, rY, 0`.

## What triggers section-anchor pooling (R5, 2026-11-07)

In KartItemAudio_PlaySEByItemId (GC/1.3.2), the TU's .rodata is addressed through one pooled base (`...rodata.0@l` in the .o, then `addi rX, base, 0x0` for the object at +0). The trigger is the struct copy `Vec3 pos = KartItemAudio_PlaySEByItemId_rodata_802EDD24;` inside the function. Replace it with `Vec3 pos;` and every reference in the function goes back to per-symbol `lis/addi` (diff 4 -> 493).

These do *not* pool (amnet flags and KartItemAudio flags both tested):
- A TU that only defines several const objects (global or static) and passes or loads their addresses.
- A struct copy from a const object in another function of the same TU.
- A dead struct copy (`{ T t = obj; (void)t; }`) in the function itself. This was tried as a fakematch for fn_8028D8CC; it gets removed before the pooling decision.

So `addi rX, rY, 0` on 1.3+ points to a function that does a *live* struct copy of a const object the TU owns.
