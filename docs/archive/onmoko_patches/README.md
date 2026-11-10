# Pragma fixes for onmokoworks-claimed TUs (verified, not applied)

## Landed on main (2026-11-08)

onmokoworks released most claims, so these patches were applied on main and
are kept here only for reference: fn_80246DE4.patch (RaceDigits linked as
Matching, eb5bf52), amnet_nm2_rest.patch and merge/cobj_lobj_merge.patch
(b40edd9), THPDec_GetBit.patch, TExp2TevDesc.patch, BackupReadRecord.patch,
JointTracks_fn_80240378.patch (partial gains, 2026-11-08). Do not apply them again.

## Landed 2026-11-08 (asm->C (A) thread)

FrameUpdate, PCBCommPhase5, STLContainer applied as-is (b2d2c8c). PCBCommPhase1 and
ItemHitPropagation no longer applied after onmokoworks' rewrites; the same fixes were
ported by hand (98e933a). All five TUs are Matching. CoursePropCtor, VfxSlotMgr and
card_unpack_v1 were already Matching on main.

## Status on main 610292b (re-verified 2026-11-07 21:00, mid-range thread)

Each patch was applied **alone** to a throwaway checkout of main, then built from clean (`rm -rf build/GNLJ82/src build/GNLJ82/ok`, ninja). Baseline on that main: main.dol OK, 7251 matched functions (report.json `matched_functions`). "+fns" is the change against the baseline.

| Patch | Applies | main.dol | Flip to Matching | +fns | Depends on / conflicts with |
| --- | --- | --- | --- | --- | --- |
| AI_UpdateItemUseLogic.patch | **applied on main (52fc734)** | OK | yes | +1 | - |
| DNLensflare.patch | yes | OK | yes (already 100%) | 0 | touches tools/extab_user_renames.json, as does anon_80226670 (different TU blocks, both apply) |
| FrameUpdate.patch | yes | OK | yes | +1 | - |
| ItemHitPropagation.patch | yes | OK | yes | +2 | - |
| PCBComm_UpdateSyncPhase1.patch | yes | OK | yes | +1 | regenerated with 1-line configure.py context; the old version conflicted with Phase5 (adjacent lines). Both now apply in either order |
| PCBComm_UpdateSyncPhase5.patch | yes | OK | yes | +1 | same as Phase1 |
| STLContainer.patch | yes | OK | yes (already 100%) | 0 | - |
| VfxSlotMgr.patch | yes | OK | yes | +1 | - |
| amnet_nm2_rest.patch | yes | OK | no (fn_8028D8CC 99.83%) | +1 | **supersedes fn_8028EAA8.patch** (same file, contains its change); apply only one |
| fn_8028EAA8.patch | yes | OK | no | +1 | conflicts with amnet_nm2_rest.patch, so use that one instead |
| anon_80214B3C.patch | yes | OK | yes (already 100%) | 0 | - |
| anon_80226670.patch | yes | OK | yes (already 100%) | 0 | see DNLensflare |
| card_unpack_v1.patch | yes | OK | yes | +1 | - |
| cobj_data_nm2.patch | yes | OK | yes (data-only) | 0 | the cobj owner may move these strings in a CObjInfoInit / cobj merge |
| fn_8021E0FC.patch | **applied on main (52fc734)** | OK | no (4 other fns < 100%) | +1 | - |
| fn_80243C70.patch | yes | OK | yes | +1 | - |
| fn_80246DE4.patch | yes | OK | yes | +1 | - |
| merge/anon_8020AF08_nm1_pool.patch | yes | OK | no (99.86%) | 0 | edits config/GNLJ82/splits.txt |
| merge/fn_801913B0_codegen_probe.patch | yes | OK | no (probe) | 0 | probe only; the real fix needs the Fog-TU data merge |
| merge/fn_80192F04_codegen_probe.patch | yes | OK | no (probe) | +1 | probe only, same as above |
| fn_801F8A34.patch | **obsolete** | - | - | - | already on main (Codex batch ecd8bf9/5034e3f, fn 100%, TU Matching) |
| clItemBoxManager_Update_Inner.patch | **obsolete** | - | - | - | onmokoworks fixed it differently on main (ListIter rewrite); Update_Inner is 100% on main |

**All together:** every patch except the two obsolete ones and fn_8028EAA8.patch, applied in alphabetical order (top dir, then merge/), clean build gives main.dol OK and 7264 matched functions (**+13**). That equals the sum of the single-patch gains, so no two patches interfere. The patches with "new blank line at EOF" warnings (card_unpack_v1, fn_80243C70, fn_8028EAA8, amnet_nm2_rest) still apply cleanly.

These patches come from the zero-diff hits in docs/reports/pragmasweep_results.md
(tools/pragmasweep.py). They were verified by R5 on a throwaway branch off main
ce0e1c8, 2026-11-07. The TU sources on main are untouched: the
TUs are claimed by onmokoworks, so the owner applies them (`git apply docs/archive/onmoko_patches/<name>.patch`).

Verification: all five source patches applied together, then a clean build
(`rm -rf build/GNLJ82/src build/GNLJ82/ok`, ninja). main.dol SHA OK and every
listed function at 100% in report.json (7248 matched functions on that build;
before count not measured). Each Matching flip was then checked
on its own with a fresh link; main.dol stayed OK.

| Patch | Function | TU | Before | Fix | After | TU flip |
| --- | --- | --- | --- | --- | --- | --- |
| fn_80243C70.patch | fn_80243C70 | game/ItemPanelDraw.cpp | 99.97% | `#pragma push` / `opt_lifetimes off` / `pop` around the fn | 100% | yes, included (whole TU 100%, SHA OK). APPLIED on main 2026-11-08 by R5 |
| card_unpack_v1.patch | card_unpack_v1 | game/CardUnpackV1.c | 98.99% | opt_lifetimes off | 100% | yes, included |
| fn_801F8A34.patch | fn_801F8A34 | game/fn_801F8A34.cpp | 98.16% | opt_common_subs off | 100% | yes, included |
| fn_8021E0FC.patch | fn_8021E0FC | game/anon_8021BC44.cpp | 92.99% | opt_propagation off | 100% | no: TU still has fn_8021C070/C778/D780/DAB8 < 100% |
| clItemBoxManager_Update_Inner.patch | clItemBoxManager_Update_Inner | game/clItemBoxManager_nm1.cpp | 99.74% | opt_lifetimes off | 100% | no: SoundDriver_GetOrCreate and 3 DoublyLinkedList fns < 100% |
| fn_80246DE4.patch | fn_80246DE4 | game/RaceDigits.cpp | 99.96% | optimization_level 3 around DigitHud's ctor, plus flip work: functions reordered to the target order (DigitHud ctor, Update, DigitPanel ctor), DigitOwner/DigitListBase members made out-of-line in this TU via `RACE_DIGITS_OUTLINE` in include/game/RaceDigitsPrivate.h (other TUs keep the inline versions), `main(0)` through a new inline pointer ctor so DigitHud's ctor doesn't need DigitOwner(), `#pragma defer_codegen on` before the last two dtors so ~DigitList still inlines ~DigitListBase, and the TU added to DATA_ALIGN4_WEAK_TUS (its .data was 8-aligned) | all 7 fns 100% | LANDED on main 2026-11-08 (TU unclaimed, claim #2675) |
| fn_8028EAA8.patch | fn_8028EAA8 | triforce/amnet_nm2_rest.c | 99.28% | opt_dead_assignments off + `case 3: break;` in the dev->kind switch (gives the target's second `b`) | 100% | no: fn_8028D8CC is in the same TU (see amnet_nm2_rest.patch) |
| amnet_nm2_rest.patch | fn_8028D8CC + fn_8028EAA8 | triforce/amnet_nm2_rest.c | 98.42% / 99.28% | fn_8028EAA8.patch plus, for fn_8028D8CC: opt_propagation off + opt_loop_invariants off; `base = BSWAP16(hdr[1]); base <<= 16; base |= BSWAP16(hdr[0]);`; ReadDeviceWordImpl returns `BSWAP32(*(u32*)buf)` with no local (fixes the lwz/rlwinm register pair) | 99.83% / 100% (clean build main.dol OK, 2026-11-07) | no: 17 diff lines left. The target puts `configs` straight into r30 and copies it with `addi r4, r30, 0x0` (ours: `addi r4,...; mr r30, r4` and `mr r4, r30`); case 0x29 swaps r4/r5 between `li 2` (dev->kind) and the &amnet_nm3_bss_80699140 base. Tried: decl orders, struct/array/char*/int views of the table, inline helpers, index vars, all compilers 1.3..2.7, 14 extra pragmas, 30-min cperm |
| FrameUpdate.patch | FrameUpdate | game/FrameUpdate.c | 93.66% | GC/1.3.2 (was 3.0a5) + opt_common_subs off; the FrameBackup field at 0x18 is one `unsigned long long qw18` (0x14 is padding before it), so the copy loads 0x18/0x1C into a register pair the way the target does. include/game/FrameUpdate_private.h changes; TaMode_FrameUpdate (the other includer) is unchanged at 99.48% | 100% | yes, included (clean build main.dol OK) |

Not needed any more: STLContainer_DisposeRecursive and fn_801987C4 are already
100% on current main (fixed after the sweep table was generated).

## Switch case-set patch (R6, 2026-11-07)

| Patch | Function | TU | Before | Fix | After | TU flip |
| --- | --- | --- | --- | --- | --- | --- |
| AI_UpdateItemUseLogic.patch | AI_UpdateItemUseLogic (#2404) | game/AI_UpdateItemUseLogic.cpp | 97.63% | the switch has `case 9: break;` (no `case 8`), so the compare tree gets the target's `cmpwi 8; beq; bge` node. Found by trying every subset of empty cases {0,5..11} | 100% | yes, included (clean build, main.dol OK) |

## Matching-flip patches for TUs already at 100% (thread B, 2026-11-07)

From docs/reports/flip_hints.md. Verified on a throwaway branch off main: all four applied together, clean build, main.dol OK (+13 functions).

| Patch | TU | Issue | Blocker | Fix |
| --- | --- | --- | --- | --- |
| DNLensflare.patch | game/DNLensflare.cpp | #492 | unrenamed weak `__dt__16clMapEffectPartsFv` grows the DOL by 0x60 | rename it to dtor_8016A270, then flip |
| anon_80214B3C.patch | game/anon_80214B3C.cpp | #495 | the TU emits vtable clCGameYI_vtable_804EDA98 (multiply-defined) | `virtual void _key();` key stub in CoinChallengeMode, then flip |
| anon_80226670.patch | game/anon_80226670.cpp | #493 | emits vtable clCSSceneNextRaceGP_vtable_804EDF64 + unrenamed weak `__dt__9SceneBaseFv` | key stub + rename to dtor_8007D0D4, then flip |
| STLContainer.patch | game/STLContainer.cpp | #2281 | CW puts __sinit last, the target has it first (text shifted 0x4C) | hand-written static init first + `.ctors` entry (fakematch), then flip |

## Pool / TU-merge patches (thread B, 2026-11-07)

See docs/reports/merge_plans.md for the full list of plans. Files are in `merge/`.

| Patch | Function | Kind | Result |
| --- | --- | --- | --- |
| merge/anon_8020AF08_nm1_pool.patch | fn_8020B234 (#2361) | link-ready: TU owns .rodata 0x803C2E50..0x803C3508, three static arrays | 97.54% -> 99.86%, clean build main.dol OK |
| merge/fn_80192F04_codegen_probe.patch | fn_80192F04 (#2394) | probe only (the data is owned by the Fog TU; merge needed) | all instructions match |
| merge/fn_801913B0_codegen_probe.patch | fn_801913B0 (#2439) | probe only | pool fixed, about 10 lines left |
| merge/cobj_merge.patch | CObjInfoInit, HSD_CObjSetRoll (cobj_info_nm, cobj_nm4 #2270; also touches cobj_nm1 #2342, cobj_nm3 #2347) | link-ready whole-file merge (R6): the 12 cobj_* TUs (all but cobj_constants.c) become one cobj.c that owns .text 0x802C6430..0x802C8B48, .data 0x804FC4C8..0x804FC620, .sdata and .sbss. hsdCObj is split to 0x44 + the two dead-stripped assert strings (lbl_804FC50C/51C). fabs is a plain (weak) inline so SetRoll's out-of-line call resolves to MSL fabs, and cobj leaves DATA_ALIGN4_TUS so MWLD keeps the weak flag and strips the copy. | cobj 52/53 functions at 100% (CObjInfoInit and SetRoll now match); only HSD_CObjSetUpVector is left (97.08%, saved-register order up/cobj/pool vs cobj/pool/up), so the TU stays NonMatching. Clean build main.dol OK on e522333. With Configure Matching, the only DOL diff is SetUpVector (0x802C7A34..7D3C). |
| merge/lobj_merge.patch | LObjInfoInit (lobj_load_nm; also touches lobj_init_nm #2186) | link-ready whole-file merge (R6): the 10 lobj_* TUs become one lobj.c owning .text 0x802C4010..0x802C6430 plus .rodata/.data/.bss/.sdata/.sbss/.sdata2. LObjInfoInit uses the plain string literals (lbl_804FC480 shrinks to 0x21; new lbl_804FC4A4/4BC). SetupInit now auto-inlines HSD_LObjGetLightVector, so its {0,0,0} literals are the same objects (drops the extern HSD_LObj_803B94A0/AC and the lobj_vector_nm ctor-bridge entry). sbss vars get `= 0` initializers to keep definition order. | lobj 23/25 at 100% (LObjInfoInit now matches). HSD_LObjSetupInit (98.28%, reg alloc plus one unfolded `&ldir != NULL` test) and SetupSpecularInit (99.81%) were already NonMatching. .sdata2 has 50.0f/1048576.0f swapped, which needs fixing before Matching. Clean build main.dol OK. |
| merge/cobj_lobj_merge.patch | both of the above | the two patches touch neighboring lines in configure/splits/symbols, so use this one to apply both | clean build main.dol OK (on ba36dd1), cobj 52/53, lobj 23/25 |

## Full sweep over onmokoworks-claimed TUs (2026-11-07 18:00)

Every below-100% function in an onmokoworks-claimed TU (323 of them, report at
main 295cfd3) was swept:
- 62 functions missing from docs/reports/pragmasweep_results.md (large or < 80%): 6
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
| PCBComm_UpdateSyncPhase5.patch | PCBComm_UpdateSyncPhase5 | game/PCBCommPhase5.c | #2327 | 98.59% | chained `slot = slots = PCBCheckRecv_bss_805A6154; phase = phases = g_pcbSyncPhasePerPcb;` keeps the `mr r5,r31` copy; inline `first + 2` at the store (no `hostRole` local) fixes the out/value r5/r6 swap. `PCBCheckRecv_bss_806D11C8+0x4` vs `lbl_806D11CC` reloc is cosmetic (objdiff 100%) | 100% | yes, included |
| PCBComm_UpdateSyncPhase1.patch | PCBComm_UpdateSyncPhase1 | game/PCBCommPhase1.c | #2402 | 94.97% | same as Phase5: decls first (`phase` before `phases`), then chained `slot = slots = PCBCheckRecv_bss_805A6154; phase = phases = g_pcbSyncPhasePerPcb;`; `first + 2` inline at the store; in PublishTimers declare `cursor`/`out` in an inner block after `timer` is read (Phase5's layout) | 100% | yes, included |
| ItemHitPropagation.patch | Item_PropagateHitToAllDrivers, Item_PropagateHitToDriversInRadius | game/ItemHitPropagation.c | #2363 | 94.52% / 96.11% | the classifier reads `effects` through a separate kart-object type (`HitKartObject`), so case 2's `driver->effects` is reloaded instead of CSE'd (that freed r3 and fixed the whole register shift); add an empty `case 3: break;` before `default:` for the target's dead second `b` | 100% / 100% | yes, included |
| CoursePropCtor.patch | fn_8016E568 | game/mapeffect/CoursePropCtor.cpp | #2373 | 97.39% | TU owns `.data` 0x80491150..0x804911C4 (splits.txt): the four null-terminated item lists as separate static arrays, plus the global `sdata_806CF750_data_804911A0` typeinfo and `Scene_8016E1C0_data_804911AC` vtable (Scene_8016E1C0 still references the vtable by name). mwcc then addresses all of them off the section anchor (`addi r31+0x5c/0x0/0x1c/...`). Pick the list in an inline `SelectItems()` with a `return` per branch; that gives the `addi r0` + `mr r31, r0` at the join | 100% (data 100%) | yes, included |
| acsocket_nm7_acReadResponse.patch | acReadResponse | triforce/acsocket_nm7.c | #2443 | 98.83% | move the per-case read-out into `static inline void ReadOut(AcSock* k, u32 addrOff)` (decls `len, addr, lenOff, base, n`), so each case gets its own registers; in the caller declare `u32 addrOff;` before `AcSock* k = SOCK(s);` | 100% | no (fn_80292D18 96%, fn_80293070 74% left) |

### Diagnoses without a patch (R2)

- **DONE (asm->C (A), 2026-11-08):** fn_8017EFFC + fn_8017F1E8 merged into fn_8017EC90.cpp (the pool owner); the tables are its static arrays, so the anchor+offset `lwzx` comes out right. fn_8017EC90 and fn_8017F1E8 are 100% (also fixed SoundMenuDraw: `line+(y+3)`, `y+bottom+1`). fn_8017EFFC is 99.90%: only the epilogue has `lwz r28` after `lwz r0` in the target (pragmasweep all, 12-min cperm: no). The mapobject TUs (CE1C/DF00) do not need the pool: their diffs are register allocation. Original note:
- **miyazakiconsole / mapobject `lwzx` tables (fn_8017EFFC 97.8%, fn_8017F1E8 94.1%, and likely fn_8017EC90, fn_8017F538, fn_8017CE1C, fn_8017D660, fn_8017DF00).** The target indexes its tables as `addi rT, r31, 0x57c` (or `0x4c8`), then `lwzx rD, rT, idx`. The tables are separate .rodata objects (lbl_80376790 + 0xC, lbl_803766DC + 0xC), not part of lbl_80376220 (size 0x4A4). That is how mwcc addresses a static array that lives in the TU's own section: anchor plus object offset, then an indexed load. Source written as `(strings + 0x57c)[i]` always folds the offset into the displacement (`add; lwz 0x57c(r)`). Casts, member-array structs, references, locals and every psweep pragma failed to stop that. A fix needs all of 0x80376220..0x80376E10 owned by one TU (today fn_8017EC90.cpp owns it), with these tables as real static arrays, i.e. a merge of the TUs that share the pool. A struct with `char pad[0x57c]; unsigned int ids[13];` gets fn_8017EFFC from 97.79 to 98.15% but not to 100%.
- **Same section-anchor family:** CoursePropCtor fixed this way (see CoursePropCtor.patch above). The section was unowned (auto), so the TU could just take it over. mapeffect_nm1 fn_80179F60 (97.7%) has `addi r3, r31, 0x408`, then reads the quad from r3, off the .rodata pool mapeffect_rodata_80370870, which mapeffect_nm1.cpp doesn't own. Both need the pool defined as real static objects in the TU that owns the section.
- **DetermineTitle (RankLog.c) 98.47 -> 99.71%, WIP `docs/wip/RankLog_DetermineTitle_99.71.patch`.** Make the outer decls plain and order them as skip, checks, i, tbl, count, pool, pre. Inside the DetermineCurrentNameId inline, declare score, chara, k, j, i. What's left is a single chara/i r23/r20 swap; 20 minutes of cperm found nothing.
- **fn_801F894C (game/fn_801F894C.c, 97.44%, unclaimed).** The only diff: the target passes `tables->colorDesc` (offset 0) as `addi r3, r31, 0x0`, with r31 = &lbl_803BEDC0, while mine rematerializes `lis/addi lbl_803BEDC0`. Every cast and offset-0 spelling folds. This is the TU-local object behavior: lbl_803BEDC0 sits in dtor_801F8214.cpp's .rodata (0x803BEDC0..0x803BF020). So fn_801F894C has to be merged with dtor_801F8214 through fn_801F8728 (fn_801F8404 #2376 and fn_801F8728 #2395 are onmokoworks claims in between), with the tables defined in the merged TU.
- **CObjInfoInit (sysdolphin/baselib/cobj_info_nm.c, 99.94%).** (Done: merge/cobj_merge.patch; LObjInfoInit: merge/lobj_merge.patch.) The target addresses the class-name strings as `hsdCObj + 0x134 / 0x14C`, so hsdCObj (0x804FC4C8) and the strings (0x804FC5FC, in cobj_data_nm2) are in one TU's .data. It needs the cobj merge (cobj_data_nm1 + cobj.c data + cobj_data_nm2 + cobj_info_nm .text). See the R4 cobj_data_nm2 note below. **Done as merge/cobj_merge.patch (R6).**
- **acsocket_nm2..5 (acModifyMyIPaddr, acInetAddr, acConnect, acBind; 94.7..96.8%, unclaimed).** They all share one unsolved idiom. The target computes the board offset as `lwz r5, bufOff; addi rOff, r5, 0x0; ... add rOff, bufAddr, rOff`, with rOff the lowest saved register. Inline-param `State.bufOff + n`, pointer `(u8*)bufOff + n`, SockAddr/BufDev chains, `off += k->bufAddr`, and the order of the Buf/off assignments all failed (best: acModifyMyIPaddr 97.76% with `off += k->bufAddr;`).

## Data-only TU flip (R4, 2026-11-07)

| Patch | TU | Fix | Verified |
| --- | --- | --- | --- |
| cobj_data_nm2.patch | sysdolphin/baselib/cobj_data_nm2.c | The TU defines its `.data` 0x804FC560..0x804FC620 itself (strings, three Vec3s, and CObjInfoInit's `"sysdolphin_base_library"` / `"hsd_cobj"` as `lbl_804FC5FC`), each object sized up to the next one, under `force_active`, then flips to Matching. It doesn't include cobj_private.h (that header declares the strings at their string lengths). Left for the cobj owner because CObjInfoInit / the cobj merge would move these strings. | clean build off main 835bac3: main.dol OK |

## Partial fixes (mid-range thread, 2026-11-07 21:40)

| Patch | Function | TU | Issue | Before | Fix | After | TU flip |
| --- | --- | --- | --- | --- | --- | --- | --- |
| ClSound_InitSoundSystem.patch (**applied on main, 52fc734**) | ClSound_InitSoundSystem | game/clsound/ClSound_InitSoundSystem.c | #2234 | 97.35% | `#pragma opt_common_subs off` around the fn (from pragmasweep, 161 → 57 diff lines); in the ReadSoundFile inline write `end = length - 1; end = end + start;` (gets the target's `subi; add` into the same register) | 99.53% (build main.dol OK; the TU stays NonMatching, so it is not linked) | no: about 20 lines of r26/r27 coloring left, plus `mr r0, r3; …; mr r4, r0` around ARInit's result. Casts/locals don't help; 25-min cperm found only the `end + start` order |
| THPDec_GetBit.patch | __THPGetBit | thp/THPDec.c (GC/1.2.5) | #2295 | 55.24% | `#pragma opt_propagation off` + `opt_lifetimes off` around the fn (pragmasweep, 43 → 17 diff lines); other THPDec fns unchanged | 64.16% | no: the loop is laid out differently (target enters past a shared `subi p,1` at the loop head and puts the `p[1]==0` exit last); loop rewrites and a 15-min cperm didn't fix it |
| TExp2TevDesc.patch | TExp2TevDesc + HSD_TExpSetReg | sysdolphin/baselib/texp_nm1.c | #2225 | 98.01% / 97.89% | `opt_propagation off` around TExp2TevDesc; `optimization_level 3` around HSD_TExpSetReg (found with `pragmasweep --objdiff --set all`) | 99.98% / 99.61% (build main.dol OK) | no: the rest is string/table offsets off the texp data pool (base lbl_804FD988), so texp_nm1 needs merging into the TU that owns .data from 0x804FD988 |
| BackupReadRecord.patch | BackupReadRecord | triforce/ambackup_nm2.c | | 89.88% | `#pragma opt_propagation off` around the fn | 90.98% | no (small gain only) |
| HSD_CObjSetUpVector.patch | HSD_CObjSetUpVector | sysdolphin/baselib/cobj_nm3.c | | 97.08% | `#pragma optimization_level 3` around the fn | 99.85% (build main.dol OK) | no |
| JointTracks_fn_80240378.patch | fn_80240378 | game/JointTracks.cpp | | 98.42% | `#pragma opt_propagation off` around the fn | 98.75% | no (small gain) |

Checked without a patch:
- **sprite fn_801A4F38 (98.13%).** It needs the voice tables (`addi rX, r31, 0x0/0x1C/0x54/0xBC` off lbl_80496C38) as TU-owned `.data` objects. Giving the TU `.data 0x80496C38..0x80496D5C` with the real arrays breaks `dtk split` with a link-order cycle: fn_801A1798.c (text before) owns the switch jumptable at .data 0x8049A060 (after). So the original was one voice TU spanning about fn_801A1798..fn_801A4F38 (text) and 0x80496C38..0x8049A094 (data), and it needs that merge.
- **sprite fn_801A7D0C (99.63%).** The TU already owns its .bss pool. What's left is `addi r4, r31, 0x190; addi r4, r4, 0x40; lwzx` for the item column, against ours `add; lwz 0x40`. Pointer/array/cast forms and pragmas didn't help.
- **THPDec.** Its `addi rX, rY, 0x0` are GC ≤1.2.5n register copies, not anchors.
- **0x80240000+ lane (2026-11-07 23:30).** 20-min cperm runs (base = current source) gave nothing on HSD_CObjSetRoll, HSD_LObjSetupSpecularInit, HSD_TExpMakeDag, amnet_nm3 fn_8028C644, amcoin_nm2 fn_8028A3EC and fn_80243464. All of them are FPR/GPR coloring. CardSetupFlowInitial fn_8024AD8C: the `lwz self->list` gets hoisted above the `stw lbl_806D19B8` because `self` is `__restrict`. Passing `self->list` straight to the call fixes the order but then loads it after the call (4 → 3 lines).
- **pragmasweep caveat.** Its score is unified-diff lines, which can disagree with objdiff. In this lane fn_80282F54 went 102 → 59 lines but 96.52 → 84.78%, and JointTracks fn_80240378 / HSD_CObjSetUpVector / HSD_TExpSetReg also lost %, while amjvs_nm3 fn_8028AAC0 didn't move. Always check report.json before keeping a pragma.
