# Matching and acceptance rules (shared between contributors)

This page is the one place for the rules both sides of the project (naari3's
Claude threads and onmokoworks's Codex/Claude workers) use to decide whether a
change is acceptable and how to get there. It is a summary: the long-form
history is in `docs/per_fn_matching_strategy.md` and `docs/notes/`.

If a rule here is wrong or missing, fix it in a small commit and say so in the
commit message, so the other side sees it.

## 1. Coordination

- **Claim before you start.** Open a GitHub issue titled
  `[unit-claim] retrofit:<configure.py path>` (or `newtu:<unit>`), label
  `unit-claim`, before touching a TU. `tools/claim_unit.py` does this.
  Close it (`completed` or `not_planned` with a short status comment) when you
  stop.
- **Check open claims first.** GitHub search tokenizes titles, so searching a
  full TU name can miss a claim. List all open `unit-claim` titles and grep, or
  search a directory prefix.
- **Never touch a TU with someone else's open claim**, even indirectly (for
  example as part of a TU merge, a shared `splits.txt` block, or a rename in
  `tools/extab_user_renames.json` that belongs to that TU).
- **Big changes get announced first.** Changes to `tools/`, the build rules in
  `configure.py`, TU splits/merges that cross several claims, and anything
  that renumbers shared data should be mentioned in the commit/PR description
  and to the other side before landing. Small per-TU edits do not need this.
- **Shared lists:** insert new entries next to neighbours from the same address
  range in `configure.py`, `config/GNLJ82/splits.txt`, `symbols.txt`,
  `tools/extab_user_renames.json`, `tools/extab_order.json`,
  `DATA_ALIGN4_TUS`, `SDATA2_ALIGN4_TUS`. Never append at the end, never
  reformat or reorder lines you do not own.

## 2. What "done" means

A change can land on `main` (directly or by PR) when all of these hold:

1. Rebased on the latest `origin/main`.
2. **A full build** gives `main.dol: OK`:
   `rm -f build/GNLJ82/main.dol && ninja`. Check ninja's exit code, not only
   the last line. Since `tools/extab_slices.py`, ninja tracks
   `tools/extab_user_renames.json`, `tools/extab_order.json` (per TU: an edit
   rebuilds only the TUs whose entries changed) and the `tools/postprocess_*.py`
   / `reorder_extab.py` scripts, so the old clean step
   (`rm -rf build/GNLJ82/src`) is no longer needed. It is still harmless, and
   still needed on a checkout older than that change.
3. The report's function % is not the final word. The report normalizes some
   symbol names, so a TU can show 100% and still break the DOL. Always trust
   the SHA-1 (and `doldiff` for the first differing byte) over the report.
4. A TU flips to `Matching` only when every function in it is 100% and the DOL
   still links byte-identical. A TU with one unmatched function stays
   `NonMatching` even if the rest is perfect.

## 3. What source is acceptable

- **Natural code first.** Prefer code a person would have written: real types,
  real control flow, C++ classes where the target has vtables/extab.
- **Fakematches are allowed but must be marked** (rule from 2026-10-26):

  ```c
  /* fakematch (permuter): <what this fixes>
   * natural: <the code the original most likely had> */
  ```

  This covers per-function `#pragma opt_*` / `#pragma scheduling` tricks,
  permuter output, odd casts that exist only to steer register allocation, and
  `__rlwimi`-style intrinsics where plain C would also be correct.
- **onmokoworks's side does not write fakematches.** Its Codex workers are
  told not to, and its progress numbers count only natural C/C++. A marked
  fakematch from either side is still fine on `main`; it just is not counted
  as finished there, and those functions stay candidates for a natural
  rewrite. ASM bodies, manual EH and opcode-embedding are counted the same way.
- **No manual EH or hand-written extab in new work** unless the TU already
  uses it and there is no C/C++ form that emits the same table. Prefer letting
  `-Cpp_exceptions on` / C++ objects with destructors generate extab.
- **Asm that is asm in the original stays asm.** Dolphin SDK
  (`PPCArch`, `OSContext`, `OSCache`, `OSInterrupt`, PS `mtx`/`vec`), TRK
  `targimpl`, MusyX `sndSqrt`/`sndCos`/reverb/chorus, `HSD_SaveContext`,
  `HSD_MtxInverseConcat` are hand-written asm in the original sources. Do not
  count them as "remaining work".
- Inline-asm bodies with hard-coded small-data addresses
  (`addi r3, r13, -0x7AE8`) must use relocations instead (`la r3, sym(r13)`,
  `sym@ha` / `sym@l`), with the symbol declared with a size
  (`extern unsigned char sym[N];`). Otherwise objdiff cannot match them.

## 4. Compiler version (`mw_version`)

Defaults per lib block in `configure.py`: game `GC/1.3.2`, Dolphin SDK
`GC/1.2.5n`, sysdolphin/HSD `GC/1.3.2`, `.init` `GC/1.0`. Override per
`Object(..., mw_version=...)` only with evidence from the target asm:

| Telltale in target | Try |
| --- | --- |
| Field load scheduled above `stw r0, 0x14(r1)` in a tiny wrapper | `GC/2.6` + read through a `const` self (`const T *self`) |
| Loads hoisted over stores / interleaved `lfs; lwz; lfs` before stores | `GC/2.6` |
| `x \| ~0xFF` as `li rN, -0x100; or` (1.3.2 gives `oris/ori`); `li -0x100; rlwimi` colour inserts | `GC/2.6` |
| `stmw`/`lmw` prologues instead of `_savegpr` calls | `GC/2.6` + `-use_lmw_stmw on` |
| Target does not auto-inline earlier-defined functions | add `-inline noauto` |
| Leaf with `addi rX, rY, 0` for an offset-0 member (no `mr`) | `GC/1.2.5n` |
| Some byte-compare / extab-order shapes (StrPcb) | `GC/1.3` (then check `tools/extab_order.json`) |
| C++ TU that needs newer template/ctor behaviour (ZoneList, ItemBox factory) | `GC/2.7` |

Most game TUs at `0x801FC1E0..` already build with `GC/2.6`. Switching a
whole TU's version is a cheap first probe, but check every function in the TU
still matches, not just the one you are working on. `GC/3.0a*` does not compile
the game's C++.

**Whole-TU version and flag sweeps (onmokoworks, 2026-11-07).** Recompiling
each `NonMatching` TU with every version above (and `GC/2.0`, `GC/2.5`,
`GC/1.3.2r`, `GC/3.0a5`) and scoring the object with
`objdiff-cli diff -1 <target.o> -2 <base.o> --format json` found three TUs
that went straight to 100% (`fn_800D4174` 1.3, `fn_801D680C` 2.5,
`fn_801D5C88` 1.2.5n) and eleven that moved closer. A second pass over flags
found `-O4,s` (instead of `-O4,p`) better for `PCBCommSendPeers`,
`EnemyFace`, `anon_8021A7C8_nm1` and `fn_801B9928`. Setting `mw_version` or
`extra_cflags` on a `NonMatching` TU is SHA-safe (the object is not linked),
so these are cheap to land even before the TU matches. Get the exact compile
command with `ninja -t commands <obj>` and write sweep objects outside
`build/GNLJ82/src`. Run the sweep in its own worktree: `ninja -t` holds
`build.ninja` open, which made a concurrent `configure.py` fail on Windows.

Always run configure as
`python3 configure.py --binutils build/binutils --compilers build/compilers --wrapper build/tools/wibo`;
without those flags ninja tries to download tools and fails.

## 5. Data, literals and pools

- **Float literals are fine anywhere.** `tools/postprocess_sdata2.py` runs on
  every compile and renames the compiler's anonymous `@N` `.sdata2` constants
  to the shared `lbl_806DAxxx` names by matching target relocations. Writing
  `0.5f` instead of `extern const float lbl_X;` often fixes FPR order
  (clamps, `x -= k; if (x < lo) x = lo;`). Use `extern const float lbl_X`
  when two identical constants exist (the postprocess maps a literal to the
  first one), or to stop constant folding.
- **Owned literals another TU needs by name:** postprocess_sdata2 exports a
  literal under the target's global name when the target defines it in this
  TU. For `.data`/`.rodata` labels use a rename
  `"@108": "global:lbl_XXXX"` in `tools/extab_user_renames.json`.
- **`@N` numbers shift when source changes.** In a C++ TU with `@N` renames,
  re-dump `objdump -t` of the raw mwcc object after any edit and fix the json;
  an unrenamed `@N` becomes `@etb_...` and the SHA fails while the report still
  says 100%.
- **Pooled base registers.** `addi rX, rBase, 0x0` (or `lis/addi` once, then
  `rX + off`) means the original TU owned that data section and touched 3+
  objects in it. The fix is to give the TU its `.data`/`.rodata` range in
  `splits.txt` and define every object in order, not to fake it with pointer
  arithmetic. If a vtable defined there loses its only C user, wrap it in
  `#pragma force_active on/reset`.
- **Over-split TUs.** If a near miss differs only in `addi rX, r31, OFF` where
  `OFF` reaches data belonging to a neighbouring split TU, the original was one
  file. Merge the split TUs back into one (concatenate sources, merge the
  `splits.txt` blocks, delete stale `build/GNLJ82/asm/*.s`). Keep the original
  file name (it matters for `__FILE__` strings). Only do this when no part of
  the merge is claimed by someone else, and announce it (rule 1).
- **Identical instruction, still `DIFF_ARG_MISMATCH` (pooled offsets).**
  objdiff resolves `addi/lfs rX, rBase, OFF` inside an owned pool to the data
  symbol at that address. If `symbols.txt` has one big target object
  (e.g. `lbl_X size:0x44`) where the source defines two (`lbl_X` + `lbl_Y`),
  the same instruction reads `lbl_X+0x20` vs `lbl_Y` and counts as a miss.
  Fix: split the object in `symbols.txt` to match the source objects
  (e263a5ca, Jungle16ACtor fn_8016AB58 99.79 -> 100). Find them with
  `objdiff-cli diff -p . -u main/<unit> -o out.json <fn>`: same `formatted`
  text on both sides, `R_PPC_NONE` relocation, left addend != 0.
  Found 2026-11-08 in: fn_8017EFFC (16 of 18 diff lines), fn_801F7604 (10/14),
  fn_801F3BD8 (8/12), TaMode_FrameUpdate (6/21), fn_8023AC14 (4/22),
  Race_PerFrameTickAndAudio, fn_801F36D0, fn_80209C88, fn_80283154.
- **Jump tables** need the TU to own the table (`.data start:end:` in
  `splits.txt`). If the owned range starts at 4 mod 8, add the TU to
  `DATA_ALIGN4_TUS` (`.sdata2` equivalent: `SDATA2_ALIGN4_TUS`).
- **Read-only tables:** `extern const T tbl[N]`. Non-const changes load
  scheduling.
- **s64 globals** split by dtk into `XHi`/`XLo`: merge into one 8-byte symbol in
  `symbols.txt`.

## 6. C++ / extab conventions

- `lwz r12, 0(r3); lwz r12, X(r12)` is a real C++ `virtual` call (slot
  `(X-8)/4`). `if (p) p->vt[8](p, 1)` is `delete p` with a virtual dtor.
- Singleton getters / allocators with a 16-byte extab and `DELETEPOINTER` are
  `new T(...)` with an inline ctor. Declare
  `void *operator new(unsigned long); void operator delete(void *);` (do not
  define an inline `operator delete`). Rename `__ct__...` per TU through
  `tools/extab_user_renames.json`.
- A C++ TU with renames needs `extab_padding=b""` on its `Object` so the rename
  postprocess runs.
- **Singleton instance reads** that the target compiles as
  `cmplwi r3, 0; bne; li r3, 0` (a defensive null check on the global) use
  `SINGLETON_INSTANCE(g)` from `include/game/singleton.h` (it expands to
  `((g) == 0 ? 0 : (g))`). See `docs/notes/singleton-getter.md`. Prefer the
  macro over open-coding the ternary.
- When the compiler emits functions with extab in a different order than the
  target, add the TU to `tools/extab_order.json`. `reorder_extab.py` silently
  skips an entry whose function set does not equal the real extabindex rows.
- **Merging TUs that mix manual and automatic extab** (asm functions or C
  functions with `.extab_user` entries next to non-leaf C/C++ functions that
  get automatic extab) is not blocked: the object then has two
  extab/extabindex pairs, and `reorder_extab.py` interleaves them once the
  merged TU's key in `tools/extab_order.json` lists every function that has an
  extabindex row, in target order. Also: rename the automatic `@N` extab and
  extabindex symbols to the target `@etb_`/`@eti_` names in the TU's
  `tools/extab_user_renames.json` key; wrap a C++ part in
  `#pragma cplusplus on` / `#pragma cplusplus off` (not `reset`); and put
  `#pragma exceptions off` / `reset` around a C function that keeps a manual
  entry, or it gets an automatic one too. Worked example: the
  VSMode/BtMode merge (`src/game/VSMode_FrameUpdate.c`, 122d9dbc).
- A weak inline destructor that the compiler emits into a TU may be appended
  to that TU's own `tools/extab_order.json` key; new rename pairs may be
  added inside a TU's own `tools/extab_user_renames.json` key. Do not edit
  other TUs' keys, even to "clean up" (one of our workers did; it was
  reverted).
- Mangled names: map them to the project's names through
  `tools/extab_user_renames.json`, never by editing symbols to mangled names.

## 7. Before you give up on a function

Things that solved "only registers/schedule differ" cases on this project,
roughly in the order worth trying:

1. Compiler version per TU (section 4).
2. Literal floats instead of `extern` labels, or the reverse.
3. Declaration order, block-scoped temporaries, `for (int i...)` scope.
4. Inline helpers (`static inline`) for repeated bodies; by-value vs
   `const &` iterators in list code.
5. `if (a || b == X) return;` for `cmpwi; bne body; b end` early returns;
   empty `case N: break;` for an extra switch-tree node.
6. Per-function `#pragma opt_common_subs off` / `opt_propagation off` /
   `opt_dead_assignments off` / `opt_strength_reduction off` (mark fakematch),
   then re-create the one CSE you lost by hand with a named local.
7. Permuter. decomp-permuter works for C TUs; naari3's side also has a text
   permuter for C++ (`cperm.py`, kept outside the repo, ask if you want it).
   In practice it rarely moved the last register swaps here; new source ideas
   did.
8. Two shapes that closed 2-line diffs on 2026-11-08:
   - Loop step order (target bumps the pointer before the count): walk with
     a separate index, `int count = 0, i = 0; while (t[i].name) { i++; count++; }`
     (CollisionFile_Load).
   - Globals used as call arguments but kept in saved registers (target
     `lwz r29,g; mr r4,r29`, ours `lwz r4,g; mr r29,r4`): declare the locals
     without initializers and assign them inside the first call,
     `f(p, cup = g_cupId, round = g_roundIndex)` (AI_CalcGPTargetSpeed).
   - An inline member that returns a class by value (`list->end()`) can make
     MWCC emit the function after the ones that follow it. Build the
     iterator directly instead (`Iter pos(&list->anchor)`, Scene_8014E0C4).
   - A load scheduled across a store in the target (`li r0,N; lwz rX,g;
     stw r0,field`, ours keeps the load after the store) means MWCC knew the
     two could not alias. Write the natural order (store, then the load) and
     give the compiler that knowledge: `__restrict` on the pointer params
     (RankLog_OnMatchEnd), or a `const` view of a global that the TU only
     reads (fn_801FCBCC/fn_801FCD9C; mark the const as fakematch if the
     global is written elsewhere).
   - Byte stores of a shifted word that put `clrlwi`/`extrwi` in a different
     slot: write the mask, `PUT((v >> 8) & 0xFF)` (jvsio fn_80282CDC).

When you stop, record the function in `docs/gave_up.md` with the current %,
the remaining diff in one line, and where the WIP lives, so the next person
starts from there instead of from zero.
9. Stack slot order (GC/2.6, ItemEffect_Projectile draft, 2026-11-08): local
   aggregates get frame slots in ASCENDING SIZE order, and declaration order
   only breaks ties. So if the target has a 12-byte vector above two 12-byte
   scratch arrays, no declaration order will reproduce it. The vector has to be
   bigger, e.g. 16 bytes with a pad member. Two adjacent int fields copied with
   `lwz,lwz,stw,stw` are one 8-byte struct copy.
