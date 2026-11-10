# mkgp2-decomp matching tips (shared across threads)

Kept until 2026-11-09 as TIPS.md in the Claude project's shared folder; now here so
everyone working on the repo sees it. Newer, curated rules live in docs/matching_rules.md,
docs/regalloc_patterns.md and docs/gave_up.md; this file is the longer running log.

Starting a cloud thread (2026-11-09): run `bash tools/cloud_setup.sh` from the repo root as a
BACKGROUND command (Bash `run_in_background: true`) and read docs/matching_rules.md,
docs/gave_up.md, the board and your target's asm while it runs; you are notified when it exits
(`.setup_done` exists once it has finished). It restores the newest shared build snapshot
(tools/build_cache.py, $MKGP2_SHARE/build-cache/, keyed by a main commit, newest 3 kept) and
rebuilds only what changed since that commit: ~30 s on a hit versus ~5.5 min cold (dtk split
~150 s single-threaded + ~3000 mwcc compiles ~145 s). The snapshot includes build/mweppc with
its native compilers. When it ends on a newer main commit than the snapshot it refreshes the
cache in the background, so the next thread starts closer. A restore sets every tracked file
to mtime 2000-01-01 and touches only `git diff SNAPSHOT HEAD`, otherwise the fresh clone's
mtimes make ninja rebuild everything; so never `save` from a tree with uncommitted edits
(`save` refuses that, and also refuses when HEAD is not on origin/main or ninja has work left).

Talking to onmokoworks's workers: do not ask naari3 to relay. `tools/cloud_setup.sh` installs
git hooks (`tools/install_githooks.sh n3`) so every pull/rebase and every land.sh run prints the
board messages still open for us; act on them or answer them. Read and write the board in
docs/agents/ (README.md there): `python3 tools/agent_board.py open --for n3` at the start of
a thread, `post --from n3 ...` to send (writes docs/agents/to_onmokoworks.md, append only,
merge=union), reply with `--re <id> --status done|seen|declined|answer`. Never comment on
their unit-claim issues; put hints for their claimed TUs on the board instead.

Logging a fix in the rewrite-rule catalog (tools/patterns/, docs/asm_to_source.md):
1. Land the source change first (tools/helpers/land.sh). Record the rule only AFTER it says
   LANDED, so the commit id is the rebased one on main:
   `python3 -I tools/rewrite_rules.py record --fn FN --unit UNIT --rule ID --outcome landed --commit SHA`
   (`record` also resolves a stale pre-rebase id from main by subject / function name).
2. A new lever needs a rule line in tools/patterns/rules.jsonl (evidence = this fn) and, if it
   gets a write-up, a docs/regalloc_patterns.md section. Take the section number from
   `python3 -I tools/rewrite_rules.py check` ("next free section") right before landing, and
   refer to rules by id, not by section number, elsewhere. land.sh runs `check --strict` after
   its rebase and stops if two threads took the same number.
3. `python3 -I tools/rewrite_rules.py check --fix` repairs hits whose commit is not on main
   and adds landed hits to their rule's evidence; commit tools/patterns/ afterwards.

Compiler source (2026-11-09): `build/mweppc` (tools/install_mweppc.sh, run by cloud_setup.sh) is the
C source of mwcceppc GC/2.0-2.7. Read docs/mwcc_internals.md before diagnosing; it has the exact
coalescing rule (named<->named / named<->temp copies never merge), the scheduler's pick keys and the
__restrict / const-pointer alias rule. Order diffs: `python3 tools/mwsched.py explain UNIT FN --run`.
When stuck: trace (mwsched explain/coalesce, regfix diag), read the deciding function in build/mweppc,
then change the input it reads. gave_up.md rows must cite the compiler rule (see its header).

Register-only near miss, first steps (2026-11-09; automatic rewrite search found 0 new
matches over 51 fns, the wins came from diagnosis + a hand rewrite):
1. `python3 tools/regfix.py diag UNIT FN` -> which vregs are off, on which source lines, and
   the allocator edits that would give the target (named local vs temp, numbering order).
2. `python3 tools/regfix.py probe UNIT FN` -> one compile per lever that landed before
   (each opt_* pragma, un-naming same-value locals with/without each pragma, each inline
   expansion) plus the decl-order solver on every structural lever. "same" everywhere means
   the fix is a source-shape change the levers do not cover; read the diag and rewrite by hand.
   Instruction-ORDER diffs (same opcodes, different order): `regfix diag UNIT FN --sched`
   traces the real GC/2.6 scheduler (tools/mwsched.py) and says why ours picked A before B
   (dependence / uncovering / height ...), with the source lines.
   The diag output also ends with two lever sections: source levers that landed by hand
   (inline-wrapper-named-locals, indexed-vs-walking-pointer, base-init-in-body) and the
   leversweep levers whose triggers fire (rule ids, with the `leversweep.py fn` command).
   `regfix diag UNIT FN --tracesweep [--run]` writes a tracesweep template whose axes are the
   diagnosed lines (hoist into a named local, call with named locals, walking -> indexed)
   and whose `// want:` predicate is the diag conclusion. Batch over gave_up rows:
   `tools/regfix_diagsweep.py` (11-09: 163 fns, 0 new matches, 3 improved; results in
   docs/sweeps/regfix/diagsweep_shard*.jsonl). So: use it for one function, not as a sweep.
   diag also prints target `addi rX,anchor,N` whose address lands inside a symbol (rule
   anchor-addi-object-boundary, regalloc_patterns 40): split the symbol there.
   (since 11-09 22:00Z the address is resolved from symbols.txt; before that the hint could name
   the wrong base symbol), and function-level counters that drive >= 2 `for` loops when a saved
   GPR is off (rule later-loops-block-local-counter, regalloc_patterns 46).
   Not register-only? `python3 tools/nonreg_classify.py LIST` says what the other diff is
   (length:copy/address/extend/load/branch/mixed, order, opcode, stack, symbol);
   counts for the 11-09 gave_up rows are in docs/nonreg_census.md.
3. `python3 tools/regfix.py fix UNIT FN` still runs the catalog moves (inline[ / boolnorm /
   expand-void / unname / pragma-*) with the solver; worth one run, not a sweep.

Helper scripts in tools/helpers/ (run from the repo root; see tools/README.md):
- `b.sh` full configure+build, prints SHA-1 result and matched function counts
- `runs.py LO HI` list runs of still-unsplit (auto_*) functions in an address range, with sizes and EH-action flags
- `asmr.py LO HI` print target asm for every function in a range
- `mksplit.py TU LO HI` print the splits.txt block incl. extab/extabindex ranges
- `addtu.py TU LO HI [Matching|NonMatching] ['extra_cflags=[...]']` insert splits block + configure.py Object line in address order
- `fd.py game/Foo FnName` diff my compiled function vs target (labels normalized)
- `try.py src/game/Foo.c game/Foo FnName < variants` try source variants (blocks separated by `====`, first block = text to replace)
- `rep.py Unit` per-function fuzzy % from report.json
- `doldiff.py` first differing bytes between orig and built main.dol (when text is 100% but SHA fails)

Gotchas found:
1. Unreferenced functions are dead-stripped by MWLD when the object has a .comment section (all mwcc objects). Symptom: SHA fails, later functions shifted. Fix: put the TU in `DATA_ALIGN4_TUS` in configure.py (drops .comment) or add the symbol to a FORCEACTIVE mechanism.
2. A TU that owns switch jump tables needs a `.data start: end:` line in splits.txt. If the table starts at a 4-byte (not 8) boundary, add the TU to `DATA_ALIGN4_TUS` in configure.py (added in PR #191), otherwise data shifts by 4.
3. sdata2 floats/tables read-only: declare `extern const float` / `extern const float tbl[N]`. Non-const changes load scheduling.
4. Functions with frames in C TUs need `extra_cflags=["-Cpp_exceptions on"]` + `#pragma exceptions on` around them to auto-emit extab 8-byte entries.
5. Bodies that appear inlined in several functions are static inline helpers (C89: declarations at block start).
6. (group 3) Singleton allocators whose target extab is 16 bytes with a DELETEPOINTER action (0x8a..., ref MemoryManager_TimedFree) are C++ `new T` with an inline ctor: wrap in `#pragma cplusplus on` / `reset`, declare `void *operator new(unsigned long); void operator delete(void*);`, use `extern "C"` on the function, and add `extab_padding=b"\x00\x00"` to the Object. Symptom if done in plain C with Alloc(): SHA fails with every later section shifted by 8 per function.
7. (group 3) A function inlined into callers earlier in the same TU: define it `inline` (non-static) at the top of the TU (weak copy emitted after first caller) and put the strong definition in its own tiny TU at the real address.

Group 4 findings (PR #196):
6. C++ vptr placement follows declaration order: put `virtual ~X();` BEFORE data members or the vptr lands after them.
7. `if (p) delete p;` (virtual dtor) gives the doubled `cmplwi; beq; beq`. Inlined base dtor = `if (self) self->vt = base;`, two-level chain = nested `if (self) { vt=A; if (self) vt=B; }`.
8. `if ((db = lbl) == 0) db = 0;` reproduces `lwz r3,lbl; cmplwi r3,0; bne +8; li r3,0` (GameModeBase_FrameUpdate residual shape).
9. `bool f() { return x <= 0; }` -> `li 1; cntlzw; rlwnm`. Toggling a `bool` (not u8) array gives `cntlzw; srwi 5` instead of `extrwi`.
10. tools/reorder_extab.py ignored TUs whose extabindex order already matched but extab order did not; fixed in PR #196 (out-of-line inline base dtor entries come FIRST in extab). Declare such TUs in tools/extab_order.json.
11. Float literals (0.7f etc.) instead of `extern float lbl_806Dxxxx` avoid CSE into f31 across calls; postprocess_sdata2 maps them back.
6. `__restrict` on pointer params works in CW C (`float (*__restrict src)[4]`): fixes copies the target software-pipelines (next load before previous store).
7. main is moving fast (direct pushes sweeping small standalone functions across all ranges). `git fetch origin main` and check `git grep <FnName> origin/main -- src` before starting a function, and rebase often. Prefer multi-function units in your range.
12. Stuck byte-copy schedules (target loads src[1] before storing dst[0]) usually mean the source pointer was `__restrict`; try it on the parameter.
13. A loop over a global buffer whose induction regs come out swapped often matches when moved into a `static inline` helper taking (ptr, len).
14. Small defined-earlier functions get auto-inlined into later callers (`-inline auto`); wrap the callee in `#pragma auto_inline off` / `reset` when the target keeps the `bl`.

## 8. Weak inline copies shared across TUs (group 3)
If an inline function (e.g. an inline base dtor) gets a weak out-of-line copy in your TU, and the target's extab/other code points at a copy that lives in ANOTHER TU (the original linker kept only the first weak copy), rename your weak copy to that TU's symbol in extab_user_renames.json (e.g. `"__dt__6FxBaseFv": "dtor_8013EB50"`) and list that name in extab_order. Otherwise your copy stays alive (extabindex references it) and shifts .text. Also never reuse a class name whose weak dtor already exists in another TU of yours. Ninja does not track the JSON: `touch` the source after editing renames.

## 9. TexMgr locals (group 3)
`TexMgr_Init` is really the TexMgr ctor and `dtor_800869D0` its (inline, empty) dtor. A function with a stack TexMgr gets an extab action `02000008 800869d0` covering only the code after TexMgr_Init. Model it as `struct TexMgr { char data[0x230]; TexMgr(); ~TexMgr() {} };` declared in a `{ }` block starting where TexMgr_Init was called, and rename `__ct__6TexMgrFv`→`TexMgr_Init`, `__dt__6TexMgrFv`→`dtor_800869D0` (list dtor_800869D0 in extab_order as a dead weak copy).
- (G3) Float register numbering off by a swap (f1/f2) even though every expression variant compiles the same? Try float literals (`1.0f`) instead of `extern const float lbl_806Dxxxx` — literals allocate differently; postprocess_sdata2 maps them back. Fixed 3 TrophyFx fns in ResultFx.c.
- (G3) TU owns switch tables in .data at a 4-byte boundary AND carries weak inline copies (shared dtors)? DATA_ALIGN4_TUS drops .comment and breaks weak flags ("multiply-defined"). Add it to DATA_ALIGN4_WEAK_TUS instead (tools/postprocess_data_align4_keep_comment.py, after PR #206 merges).
- (G3) `neg r0,r3; or r0,r0,r3; srwi. r0,r0,31` before a branch = `if (!(((unsigned)(-(int)p | (int)p)) >> 31))` (CW didn't fold a bool-ish helper).

## MusyX (0x80298988..0x802BD07C) tools (group 8)
- Source: `git clone --depth 1 https://github.com/AxioDL/musyx.git` (older version than upstream: some functions need adapting).
- Flags: GC/1.3.2 + game cflags_base, `-DMUSY_TARGET=1`, `-i <musyx>/include -i <musyx>/src/musyx/runtime -i include/libc` (NOT include/MSL_C: sqrt clash).
- `tools/helpers/`: `cmp.py` (compile + per-function compare vs main.dol; `MKROOT` env = repo root, outputs to /home/claude/work/out), `mxc.sh file.c [-D...]` (cmp with musyx flags; set MUSYX=clone path), `mxident.py obj.o [lo hi]` (for every function in obj, list same-size target functions whose masked bytes match), `seqmap.py obj.o 0xSTART` (pair obj functions in order with target functions from START to spot size drift).
- cmp.py expects build/tools/wibo, build/compilers and build/binutils from the normal setup.

## Group 7 (finished 2026-10-25)
- Every function in 0x8024D764..0x802557B4 and the Runtime MWRTTI now has a C/C++ TU (PRs #239, #259, #264, #270). The remaining partial matches are listed in memory group7-status.md.
- GC/2.6 game TUs: functions come out in reverse source order. A factory `new X` whose ctor the target calls out of line needs `#pragma dont_inline on/reset`; when the ctor is inlined, drop the pragma.
- A section-relative .rodata string pool (`lis/addi rN, lbl_<TU rodata start>` then `addi r3, rN, off`) can be written as `const char *strs = lbl_xxx;` at the top of the fn, then `strs + off`. Declaring it first gives the target's register order.
- Float constants: plain literals (`360.0f`) reproduce the target's per-block reloads. `extern const float lbl_806DC...` lets CW CSE/hoist them.
- `x[i] = Wrap(x[i] += k*d)` vs two statements changes the fmadds destination register; inline helpers that use the constants directly (no range parameter) matched.
- A list find loop matched only with a small iterator struct (`It(node)`, `operator++`, `operator!=`), with Begin = `It(list->first)` and End = `It(sentinel)`.
- postprocess_extab_user.py only knows .c/.cpp keys, so a `.cp` runtime file gets no renames. Name it .cpp.
- A TU without extab must not have `extab_padding` in configure.py ("No extab section found").
- Gecko `__unexpected`: string pool 4-aligned at 0x803F1CE0, base CSE'd in r30; no flag combo reproduced it.

## NonMatching thread r4-6 (0x8015A6E4..0x8024D764), 2026-10-25
- `lwz r3,off(r3)` scheduled BEFORE `stw r0,0x14(r1)`: GC/2.6 + read through a const pointee (`*(void *const *)((const char*)self+off)` or `const T *self`). 1.3.2 never does it. Same shape still open in fn_801DBA34, fn_801EC698/6CC, fn_801DF318/358, KartItem_* (ONKARTHIT).
- GC/2.6 also hoists loads over stores only for const sources: non-const src ptr keeps load/store order (PhysicsState_SetPosition).
- Early `li r3,-1; blr` instead of `beqlr` under 2.6: `#pragma peephole off/reset` around the fn (fn_80203E30).
- A C++ fn that `delete`s a class whose dtor is implicit gets emitted AFTER the following functions (weak dtor generation). Declare the dtor out-of-line (`virtual ~X();`) + rename `__dt__` in extab_user_renames (anon_801FE3BC).
- TU emitting vtables that live elsewhere ("multiply-defined lbl_804..."): add an undefined `virtual void _key();` declared BEFORE the dtor so the key function is not defined here.
- Out-of-line base dtor copy first in extab: list in tools/extab_order.json (dtor_801FE870.cpp).
- Arg order: GPR and FPR args are numbered separately, so `f(float,float,void*,int)` and `f(void*,int,float,float)` both put the args in r3/r4/f1/f2. Only the source order (and so the scheduling) differs. The prototype order fixed RnkDisp_SetPosition.
- To convert ONE asm fn in a multi-asm TU with manual `.extab_user` entries, write it under `#pragma exceptions on` and list every fn of the TU in tools/extab_order.json (clFlowCup_Dtor). The open `extern void Foo();` decls of the asm sections must become real prototypes once C++ code calls them.
- A ternary `x == 1 ? 4 : 0` gives branchless code. `int r = 0; if (x == 1) r = 4;` only gets the right registers inside a static inline helper that returns r (clFlowCup_Dtor).
- A local aggregate initializer copied from a zero .rodata template (`lwz` x12 then `stw`) can be written as `Quad q = lbl_template;` (`extern const Quad`) followed by per-field stores. The TU does not need to own the .rodata (NokoNoko_Update).
- A value that `x = a*b; p->f = x; if (x >= K)` compares without a reload needs a local temp. With `p->f += ...; if (p->f >= K)` CW reloads.
- bf2/fd normalization artefacts, not real diffs: `subi rX,rY,0x1` vs `addi -1`, `psq_st/psq_l` disassembled as `xs*`/`lq`.
- (PR #263/#273) Pool base hoisted to the function entry (`lis/addi rX, lbl_A@ha/@l`, then `addi rY,rX,off`): the TU must DEFINE the objects (static or global) and the function must reference at least 3 distinct ones directly. Add `.rodata`/`.data start..end` to the TU in splits.txt. Labels other TUs use become global (`extern const T lbl = {...}` in C++). Split the defined objects the way the target addresses them: `addi rX,base,0x30; lhau` means a separate object at +0x30, and an `addi base,0x14C` vtable store means the vtable is its own object (clFlowRound).
- A vtable you now define in the TU, whose only remaining user is an asm ctor reaching it through the pool base, gets dead-stripped together with the virtuals: main.dol shrinks and functions vanish from the elf. Wrap it in `#pragma force_active on/reset` until the ctor is C.
- Load order of two globals passed to an inline ctor (JumpDistanceMode_Init PlayerCar): reading one of them through a `static inline int GetCC() { return g_ccClass; }` getter changed which one is loaded first. The arg/param order alone did not.
- lit.py writes files back with LF. On CRLF sources (clFlowRound.c, clFlowItemSelect_*.c, clFlowChara_Update.c) it leaves a whole-file diff even when nothing matched: `git checkout` those.
- (clFlowKart_Init) A ctor whose pool base is loaded in the prologue (before the first call) needs the TU to OWN the .rodata range; then the old "pool initializes after the first call / Vec copy folds offsets / table index reassociates" residues all disappear. Unused neighbour objects stay global (extern "C") so they are emitted in place; a path literal ("cone.dat") at the end of the range works as a plain literal with `#pragma readonly_strings on`. A table load the target does AFTER a call (`ch = g_characterId; if (GetCoinMilage() < tbl[ch])`) must index the array directly: an inline `indexed_value(tbl, ch)` helper let CW hoist the load above the call.
- Regalloc, self above a loop IV: CW gives strength-reduced IVs the highest callee regs and a parameter the lowest. Target shape `mr r31,r3; mr r30,r31; li r29,0` (self r31, IV r30, i r29; e.g. HUD_FrameUpdate) reproduces only with `T *self = (T *)arg;` as the FIRST local (param `void *arg`) plus a user pointer walker declared after it (`T *p = self; ... p = (T *)((char *)p + stride)`). A TU-owned pool base still outranks a local self, so clFlowRound_Update (self r31 above the pool) stays unsolved.
- (PR #291) `new T(...)` with -Cpp_exceptions on keeps the allocated pointer in a callee-saved reg (r28) for the extab cleanup action (MemoryManager_TimedFree). A real `new` + a ctor declared on a struct sized like the target (pad to the Alloc size) reproduces it; rename `__ct__...` to the real ctor name per TU in extab_user_renames.json (clFlowCup_Update).
- A `const T *` inline parameter is a separate variable: it blocks CSE of a field load across a branch. Locals of an inline get stack slots in declaration order (UpdateGameplay).
- A store constant sharing the LAST call-arg register (`li r5,0` used for stores and as arg3) usually means the callee takes fewer args than you declared: drop trailing zero args (fn_801699D8 takes 2, fn_801B85DC 3).
- Load order of `x`/`y` from an extern table row (lfsx x before `add` for y): declare the table `extern const T[]`.
- `p->f += input()->v` loading `p->f` before the null check: fetch `InputState *st = input();` into a local first.
- A switch/if whose fall-through `b` targets the instruction AFTER the next statement's `lwz` of the same field: read it into a local (`st = self->x08; switch (st) {case -1: ...; st = self->x08; } if (st != -1)`). bf2 hides branch targets, so only the DOL checksum shows this; locate with `cmp -l` + DOL section table.
Remaining in range (not done, why), as of PR #247:
- anon_801FEBD8: 100% code, but the RTTI type-name strings come out in .data. The target has them in .rodata (0x803C0238..), the bases in .data 0x804EC200.. and the RTTI in .sdata 0x806D01E0... Needs data splits or a string section fix.
- anon_801FC1E0: fn_801FC644/801FCBCC/801FCD9C/801FCF58 were never written (0%).
- anon_80202BCC: 3 fns at 61% (jump table / data).
- Other anon_* g6 fns, plus clFlow*/ItemSelectState/CoinChallenge, sit at 91-99.9% with regalloc residue.
- asm bodies still in, with the reason each is stuck:
  - TexMgr_Apply: regalloc, i/self swapped.
  - clFlowItemSelect_CommitSlotAnim: separate induction pointers.
  - clFlowKart_UpdateDisplay: lwzx threshold form.
  - clFlowItem_Draw: walker regalloc; the C body is in `#if 0`.
  - SpriteAnimParamBlock_Reload: dead row counter.
  - clFlowRound_Dtor: DONE in PR #273 (TU owns .data 0x8049AE70..0x8049AFD0).
  - JumpDistanceMode_InitTimerDisplay: about 20 lines off. The tens-digit value is computed after `fn_80121E10` instead of before, and one `lis` gets scheduled differently. C draft: docs/wip/notes/JumpDistanceMode_InitTimerDisplay_draft.cpp. (clFlowRound_Dtor draft: notes/clFlowRound_Dtor_draft.cpp.)
  - Done after #247: JumpDistanceMode_Init (#263), clFlowRound_Draw/Dtor, clFlowCup_Draw, fn_802021B0 (#273).
  - SoundMgr_Play: C draft notes/SoundMgr_Play_draft.c is structurally equal. About 40 normalized lines remain, all register numbering (find-loop walker r6/r7, bubble i/q swapped).
  - clFlowRound_Init: draft notes/clFlowRound_Init_draft.cpp. Only the 4-iteration slot loop differs: the target uses an offset IV (`addi r0,r27,0x2c; stwx r6,r31,r0`) and mine a pointer IV (`stw 44(r29)`). Tried 2D-array, ctor form, unsigned, do-while and pointer forms.
  - clFlowKart_Init: DONE in PR #283 (TU owns .rodata 0x8039E508..0x8039E9F8).
  - clFlowRound_Update: instruction stream equal (normalized 0 apart from the regalloc-driven scheduling in PlaceArrows); only self=r31 vs pool base fails, see the regalloc tip above. Drafts: notes/clFlowRound_Update_draft.cpp (user-pointer form), notes/clFlowRound_Update_draft_paramself.cpp. Needs `__rlwimi(c, a, 0, 24, 31)` for the alpha insert and a `switch (x7C) { case -1: ... }` for the beq/b shape.
  - clFlowCup_Init: not attempted. It has the same offset-IV `addi r0,rI,0x124; stwx` slot loop that blocks clFlowRound_Init, plus a ctr-unrolled zeroing loop. The pool (.data 0x8049AD58) is already owned by clFlowCup.c.
  - Done in PR #291: JumpDistanceMode_HandlePhysics, JumpDistanceMode_UpdateGameplay, clFlowCup_Update.
  - CopyKartMovement: needs `__restrict`-like aliasing plus GPR parity; not solved.

## NonMatching sweep, SDK/libs 0x8024D764..end (2026-10-25)
- Only non-auto NonMatching object there was jobj_anim_all.c; matched in PR #218. Fix: natural recursive HSD_JObjReqAnimAllByFlags in jobj.c (inlines HSD_JObjReqAnimByFlags) + `#pragma inline_max_size(600)`. TIP: when a target inlines recursion/callees deeper than yours, `-inline level=`/`inline_depth` do nothing on CW 1.3.2, but `#pragma inline_max_size(N)` does (non-monotonic, sweep N).
- Still unsplit/stuck (auto_ asm, range thread 7 left them): __ppc_eabi_init (__init_user/__init_cpp/_ExitProcess, 0x8025D08C): old prologue `mflr; stw r0,4(r1); stwu` = GC 1.x; 1.x at -O2/-O3 matches everything except two extra `b .+4` before the loop (source shape not found). OSExec (__OSGetExecParams, __OSBootDol + 6 fns 0x802581E8..0x80258B44), PAD fn_8026031C/__PADDisableRecalibration, TRK msgbuf/targimpl/ddh/gdev, Runtime 0x80270C48..0x802731B4 parts still open.

## Group 6 notes (YesNo selector / collision / card rewards, 0x801FC1E0..0x8024D764)
- After any rename change in tools/extab_user_renames.json, do a CLEAN build (`rm -rf build/GNLJ82/src`). Ninja does not track the JSON, and stale objects keep old fn_ names (link errors like undefined fn_80271884/fn_80270D6C).
- Runtime names are real now: `__construct_new_array`, `__destroy_new_array`, `__construct_array`, `__destroy_arr`, `__cvt_fp2unsigned`, `__div2i`. Do not rename them to fn_.
- A struct copy from a rodata Vec that the target reloads after member stores is a NON-const extern (`extern Vec lbl;`). With `const`, CW hoists the load and unrolls loops differently.
- CW register numbering follows declaration order. Declaring loop locals at function top in the target's order (earlier = higher reg) fixed nested-loop allocation.
- Volatile sqrt stack slots: deeper inline nesting gets lower slots. Match the slot order by flattening or nesting the inline sqrt helper.
- Next unsplit work in G6 starts at 0x80209A84 (card reward state, then FlowFader fn_8020A6CC.. and ItemDisplay). Parked residuals are listed in PRs #198/#203/#210/#220.
- (G3 wrap-up) Group 3 stopped at 0x8014388C. Next unit 0x8014388C..0x80144430 = ModelFx family (base vtable EE48: dtor_80143F0C + 4 thin wrappers, derived dtors 8014388C/80143F8C/80144258, ctors 8014393C/8014403C/80144308). The derived ctors index rodata struct CSPartsResultStage_rodata_80361970 (0x29C) with `addi base,off; lwzx` = 2D member arrays [cup][mode]. Unmatched list for G3 range: 0x801077C8–0x801223E8 and 0x8014388C–0x8015A6E4.
- (G3) "Pooled" rodata access (`lis/addi r31` once, then `addi r3,r31,0x2b4; lwz r4,8(r3)` or `addi r4,r31,0x164; lfsx`) did not reproduce with an extern struct (CW folds the offsets). PoseChar ctor (fn_80143450) stays asm for that reason; likely needs the TU to own the .rodata.
- (G3) HSD JObj inlines with exact asserts (0x25D dirty, 0x47C GetMtxPtr, 0x495/0x496 CopyMtx, 0x383/0x38F/0x39B GetScaleXYZ, 0x3E4 GetTranslation, 0x2FA GetRotationY) are in src/game/PodiumPose.c — take MtxPtr (float(*)[4]) params, not float*, so the stack-mtx null assert folds away; use extern lbl_806D7AA0/AA8/AC0 not string literals (literals land in .sdata).

## Range 1 notes (0x80003100..0x8009B98C, 2026-10-25)
- Writable globals that dtk puts in `.sdata2`: declare `extern T *const lbl;` and write via `*(T **)&lbl = x`. That fixed the "global load scheduled above prologue saves" pattern and the no-reload-after-member-store pattern (Sci2Card_Lifetime.cpp).
- Section-base string pools (`lis rN, lbl_X@ha; addi rN,...` then `addi r3, rN, 0x434`): the TU must own the original .rodata range. Define every object in order, using byte/word arrays for float tables and `\x` escapes for SJIS. Split any multi-string blob symbol in symbols.txt. Example: PcbDebugOverlay.c owns 0x80311E38..0x803123B0.
- CW unrolled loops with early return or `li r5,i` constants: check whether the target's count variable is a separate inline helper. PcbSync_CountJoinedPcbsAdvancedKarts needed `n = CountJoined()` as an inline.
- Leftovers in range 1:
  - Terrain_GetGroundHeight / FindTriangleAtPosition / WallEdgeTest are NonMatching at ~98%. The edge-test zero gets hoisted out of the loop, and the parameter register order differs.
  - Sci2Card_Tick and AllocAndOpenSci2 use the pool base lbl_803114D0. They need one TU covering 0x8007660C..0x8007723C plus .rodata 0x803114D0..0x803115F0 (Init/BuildPacket/Lifetime are currently separate TUs and would have to merge).
  - FinalLapBanner_Init uses pool FinalLapBanner_Init_rodata_803123B0, same approach.
  - StrPcb_Init/Shutdown are parked (notes/StrPcb_Lifetime.md).
  - PcbIdToIpAndModify uses pool lbl_80310DE0.
  - Untouched: big UI pages (SystemInfo_UI, CardData*, TestPages), ShadowBillboard, clDrawMan, TransitionEffect, CreditMgr, CardTask*, Sci2Card print/receipt state machines, NameCheck.

## Group 2 notes (0x8009B98C..0x801077C8, wrap-up 2026-10-25, PRs #193/#202/#222)
- CW evaluates call args right to left: `f(a, Rand(), Rand())` calls the LAST Rand first. Write the calls inline and do not hoist them into temps.
- Clamp constants (`F += k; if (1.0 < F) F = 1.0;`), GetSpawnPosition(v, 0, 0, x) zeros, and repeated struct-init values (`s.a = s.b = 2.0`) often want literals (`1.0f`) rather than `extern const float lbl`. When only the FPR numbering differs, brute-force the literal/extern subsets (script: /tmp/claude-0/g2/litsearch.py, which is gone after this session; easy to rewrite).
- C++ with ResCtrl locals (VfxBannerSequence_Tick.cpp): `struct ResCtrl{...; ResCtrl(); ~ResCtrl(){}}`, `extab_padding=b"", extra_cflags=["-Cpp_exceptions on"]`, and renames `__ct__7ResCtrlFv`->ResCtrl_Init, `__dt__7ResCtrlFv`->dtor_80082960. The ctor call position and extab ranges follow the declaration scopes: put each ResCtrl in its own `{ }` block around its use.
- A TU-local anchor (`addi rX, rBase, off` off a hoisted .rodata/.data base) works with `extern unsigned char lbl[]` plus byte offsets, except when the offset is 0 (CW emits mr). DrawEffect_KartDustRing_Update is stuck at 98% for that reason.
- Parked NonMatching (98-99.9%, regalloc or stack-slot order): ItemObject_SpawnWithAlias, Item_OrbitAnchorKart, ItemObject_Tick_Kind28_BananaTrioSpawner, DrawEffect_KartDustRing_Update, DrawEffect_Cb_WheelSpark_Bind4D, DrawEffect_ReleaseCallbackResources, EffectVfx84_85_BoostChargeRing_Tick.
- Not done: WarpDashMgr_Init and CourseData_LoadPathTable (EH, m2c drafts dropped). DebugStageSelect_UpdateInput needs RTTI strings in .rodata. The remaining auto_* blobs in the range are untouched.
- MusyX in mkgp2 = version 2.0.2 (`-DMUSY_VERSION_MAJOR=2 -DMUSY_VERSION_MINOR=0 -DMUSY_VERSION_PATCH=2`). Lib "musyx" in configure.py (PR #223) adds `-i include/musyx_libc` (plain math.h, avoids libc inline sqrtf statics in .sdata2) before `-i include/libc`. Upstream functions missing from the binary are usually just dead-stripped, not version differences.
- Local builds keep stale .o after tools/extab_user_renames.json edits (ninja doesn't track the json): `rm -rf build/GNLJ82/src` if undefined fn_ names appear.
- Dolphin SDK in group 8 range: SI/EXI = Apr 17 2003, dvd.c = Jul 23 2003 (= mkdd dvd.c). EXIBios needs `-schedule off`; DVD needs `-char signed`.
- (NonMatching r1-3) `notes/sweep.py obj fn...` compiles one TU with every GC version x common flags and prints diff counts; only ItemCharacterRender was fixed that way (GC/2.6). Remaining list with diff sizes: notes/nonmatching_r1-3.md. A GC/2.x TU whose jump table sits on a 4-byte boundary goes in DATA_ALIGN4_TUS; postprocess_data_alignment.py now drops the orphan .sdata2 literal left by postprocess_sdata2 (else small data shifts by 8). FD_ISSET-style tests match when the mask is recomputed inline instead of reusing the variable. try.py's diff count ignored lines containing `.L` (missed branch diffs): confirm with fd.py.

## HSD baselib part 1 (0x802BCF94..0x802CA77C) DONE 2026-10-25
- Every TU in the range is in configure.py: dobj (Matching), tobj (NonMatching 36/42, #272), state (NonMatching), tev (Matching), mobj, lobj, cobj (NonMatching 45/53, #268), aobj, fobj. pobj belongs to part 2.
- Newer-HSD deltas vs melee:
  - Class infos gain an `update` slot (DObj +0x44, TObj +0x48, MObj +0x4C, LObj/CObj +0x40), and *Anim calls `HSD_AObjInterpretAnim(aobj, x, METHOD(x)->update)`.
  - Update funcs clamp with an inline `if(x<=lo)return lo; if(x>=hi)return hi; return x;`.
  - TObj has `u16 desc_id` at +0x4A.
  - Assert line numbers shift per file. `tools/asfix.py obj map src` in the thread rewrote them automatically from `li r4` diffs.
- MWLD here does NOT always dead-strip unreferenced statics (tev kept HSD_TevStage2Index and ChanUpdateFunc; I had to delete them). Lay out sbss with globals first, then statics in reverse declaration order.
- Still NonMatching:
  - state: SetupChannelMode, SetMaterialColor
  - mobj: MakeTExp, InfoInit
  - lobj: SetupInit, SetupSpecularInit, GetLightVector
  - cobj: top/bottom-half camera, SetCurrent, upvec2roll, roll2upvec, SetUpVector, SetRoll, InfoInit
  - tobj: TObjUpdateFunc, MakeTextureMtx, TObjSetupMtx, SetupTextureCoordGen, TObjMakeTExp, AssignResources
  Most of these are register or schedule differences. TObjUpdateFunc (0x5CC vs 0x2FC) has real extra code.
- The vendored headers in libs/melee/src/sysdolphin/baselib are what the build uses. Keep any header edit in sync there.

## MusyX part 3 (0x802AE204..0x802B6DCC) — DONE (PR #227)
- Units: synthvoice, synth_ac, synth_adsr, synth_dbtab (data-only TU, .data 0x804F64B8..0x804F6C40), synth_vsamples, s_data, hw_dspctrl, hw_volconv, snd3d. Whole upstream files, each owning its data; unreferenced statics/functions are dead-stripped by the linker, so splits ranges just cover what the target keeps.
- hw_volconv/snd3d need `-fp_contract off`. snd3d uses the libc inline sqrtf (copied into the .c; its weak _half/_three are dropped at link) and `em->flags & 0x180` (upstream gates it on version >2.0.2).
- After changing splits.txt, `touch` the .c: ninja doesn't rebuild the object, and postprocess_sdata2 then leaves stale *UND* lbl_ refs.
- Rebasing symbols.txt renames across busy main: re-apply renames by address with a script instead of resolving conflicts by hand.

## MusyX part 4 (0x802B6DCC..0x802BCF94, done: PRs #230, #245)
- File order: snd_init 0x802B6DCC, snd_math 0x802B6F38, snd_midictrl 0x802B7098, snd_service 0x802B93A8, hardware 0x802B967C, hw_aramdma 0x802BA730, hw_dolphin 0x802BB460, hw_memory 0x802BB9B0, reverb_fx 0x802BBA3C, reverb 0x802BBAD8, chorus_fx 0x802BC754..0x802BCF94 (then HSD dobj.c). snd3d.c (ends 0x802B6DCC) belongs to part 3.
- Upstream 2.0.2 sources mostly match as-is. Unused functions can stay in the file: MWLD dead-strips them.
- A file with several static arrays (snd_midictrl, hw_aramdma) must OWN its .bss/.sbss/.data: with `extern` arrays each one gets its own lis/addi and the function grows (one `...bss.0` base register in the original). Derive ranges from `nm -n -S obj` sizes + the target symbol of the first variable.
- `-fp_contract off` per object for snd_math, hardware, reverb (fmadds/fnmsub otherwise).
- Tail-call-only tiny functions (hwInitStream, hwFrameDone, salStartAi...) are byte-identical duplicates: name them by source order, not by mxident.
- (SDK sweep, 2026-10-25, later) Matched: __ppc_eabi_init (GC/1.0 + `#pragma peephole off` gives the odd `b;b;b`), OSExec (dolsdk2004 verbatim), fn_8026031C = DEMOPuts (`-char signed`), Pad.c (__PADDisableRecalibration only), Gecko_ExceptionPPC (PR #249: pikmin2 source, GC/2.6 `-RTTI on -str nopool`, weak std::exception copies renamed to game's dtor_80038DD4/fn_80038E1C/lbl_803F5710, `extab_padding=b"\x02\x55"` for uninitialized catch(...) padding; `dtk extab clean` wipes any patch you make in postprocess, so padding must come from extab_padding). Also: postprocess_extab_user.py only looks up `.c`/`.cpp` keys, so a `.cp` TU never gets its renames.
- Still open: MWRTTI __dynamic_cast (fn_80271340, + bad_cast dtor/what fn_802715A4/fn_80271600, TU 0x80271340..0x8027160C, rodata 0x803F1C78..0x803F1CC8, sdata 0x806D0B68..0x806D0B78, data 0x804F47A8..0x804F47C8). Draft at docs/wip/notes/MWRTTI.draft.cpp is structurally identical; only 2 register swaps left (rtti r11<->r12, base offset r12<->r31). Local declaration order matters a lot here (d_offset before bases, a `name` local): brute-forcing decl permutations got it from 187 to 48 diff lines.

### Range 1 notes, part 2 (2026-10-25, thread 4u7gci)
- `cntlzw rX; li r4,1; rlwnm r3,r4,rX,31,31` comes from `x <= 0`. For an int return, write `return --n <= 0 ? 1 : 0;`, because a bare `<=` in C++ adds a clrlwi.
- Float constants that are reloaded in every basic block are literals (`0.0f`), not `extern const float`, because the extern version gets CSE'd. postprocess_sdata2 only names them correctly once the code layout matches.
- A member whose dtor is inline but which has no ctor makes the enclosing inline ctor keep a `this` copy (`mr r26`) for cleanup. To avoid it, store the member as raw `unsigned char m[N]` and destroy it with `((T *)m)->~T();`. This keeps the nested `addic.` null checks.
- You can clean-build against the latest main without touching your working tree. Run `git worktree add /tmp/x <sha>` and merge origin/main there. Symlink build/{compilers,binutils,tools} and orig/GNLJ82/sys into the worktree, then run configure + ninja.
- cLNormal3DWrap.cpp: all 28 functions are 100%, but the TU is still NonMatching. The target uses virtual dtors with RTTI, and the names are in .rodata (this CW puts them in .data). It also emits the weak template base dtor last in the TU, while ours comes right after the ctor.
- Sci2Card_Tick (separate NonMatching TU): it was 98.9% while it sat inside the pool-owning TU. Strings addressed from a pool base only get the shared `r31` base when the pool is defined in the same TU.
- (G3) Item tick leaf TUs (0x80107xxx..0x8011Dxxx, `game/fn_XXXX.c`, `-Cpp_exceptions on`): sdata2 (r2) floats as `extern const float` (non-const blocks load hoisting); sdata (r13) as plain `extern float`. If a const is held in f31 across a call or loads are scheduled differently, use float literals (postprocess_sdata2 renames them back) — fixed 4 more fns. A C switch's jumptable: add `.data start:jt end:jt+4*n` to the leaf's split; if jt%8==4 also add the TU to DATA_ALIGN4_TUS. Case order in source = order of case bodies by address (duplicated bodies aren't merged, e.g. `case 0,4,6,9,5,7,8`).
- (G3) `lbz; cmpwi r0,1` (no extsb) = `*(char *)(p + off) == 1`; `lbz; extsb; cmpwi` = `(signed char)`; `cmplwi` = unsigned char.
- (NonMatching r1-3, PR #255) `tools/helpers/lit.py src/game/Foo.c game/Foo FnName [k]` (needs fd.py beside it; fd.py writes to /tmp/claude-0/d) tries every subset (up to k) of `lbl_806Dxxxx` float uses in one function as literals (value read from the DOL) and keeps a 0-diff result. It fixed 17 of 88 FPR-allocation residuals in one unattended run (effects/KartFx ticks). Run it first on any NonMatching that only differs in FPR numbers. decomp-permuter (C only) works with notes' mkperm-style compile.sh but is slow (~1 it/s) and its score is misleading here.

## MusyX part 1 + THP (0x80298988..0x802A36F0): seq/synth DONE (PR #232), THP 20/26 (PR #251)
- seq.c/synth.c: upstream 2.0.2 with per-object `-fp_contract off`. seq.c SetTickDelta needs `(float)fmod(...)`/`(float)floor(...)` and an explicit `double fmod(double,double);` prototype.
- THP decoder 0x80298988..0x8029C33C = `src/thp/THPDec.c` (lib `thp`, GC/1.2.5, cflags_base + `-fp_contract off`), NonMatching. It is an OLDER THP than dolsdk2004/melee: custom THPFileInfo layout (see the struct comments), IDCT is C loops around asm blocks. melee's THPDec.c helps for the parsers only.
- CW inline asm: a hardcoded `r0` inside an asm block stops the compiler from using r0 anywhere in the function. Use a `register u32 tmp` instead (this fixed THPDecDecode).
- Register vars: allocation follows declaration order (first-declared callee-saved one gets the highest reg). Volatile loop vars are also assigned in declaration order. For float consts: `register f32 bias, cc2c6a, cc2c6s, cc2, cc4;` then assign in load order.
- Perf-counter idiom (fn_8029B54C/BA2C/BCF0): THPPerfRec[10] at THPDec_bss_806A4A40, macro with `{ u32 d = end-start; u32 m = max; if (d > m) m = d; max = m; }` (a ternary gives the wrong branch shape). The array must be `extern`: if it is defined in the TU, mwcc hoists its address to the function entry.
- Left (all regalloc/order): __THPHuffDecode/Tab (`add r0,valPtr,Vij` operand order, 2 lines each), fn_8029B54C (vs computed in j's reg, 2 lines), __THPDecodeBlock, fn_80299D58 (68 lines, ws<->itmp0 and cc4<->bias swaps; WIP docs/wip/notes/thp/fn_80299D58.wip.c with //DB..//DE decl block), __THPGetBit (loop shape).
- Brute-force tools: docs/wip/notes/thp/{hill.py,permsel.py} swap/permute decl lines between `//DB` and `//DE` and score with cmp.py (`--only` that function). asm2c.py turns dtk asm into a CW asm body with a register->var map.

## HSD baselib part 3 (0x802DA1A8..0x802E88D0) DONE 2026-10-25 (PRs #229/#246/#254/#276)
- Range contents: wobj, fog, perf, list, object, quatlib, memory, shadow, archive, random, bytecode, class, hash, texp, texpdag, debug (HSD, melee-based, `sysdolphin_melee` lib), then **zlib 1.2.1** (0x802E53E4..0x802E88D0: adler32, crc32, zutil, inflate, inftrees, inffast; lib `zlib` in configure.py), plus `triforce/jvsboot.c` (fn_802E5380, JVS bring-up).
- zlib: the stock 1.2.1 source (github madler/zlib tag v1.2.1) matches with GC/1.3.2 `-O0,s -inline off -Cpp_exceptions on`. The target has extab entries for C code; without exceptions on, the extab/extabindex sections shrink and main.dol FAILs while every function still shows 100%.
- **objdiff fuzzy can show 100% for a unit whose functions are still named fn_XXXX in symbols.txt** (it pairs by name and falls back loosely). Rename the target symbols first, then trust the score. The main.dol SHA is the real check.
- MWLD dead-strips unreferenced functions and also data objects, so extra melee functions are harmless. Strings live in one pooled .data object, though, so drop the static strings and asserts of functions mkgp2 doesn't have (otherwise later string offsets shift).
- A zero local aggregate initializer (`GXColor c = {0};`) puts its template in .sbss2 (fog.c). Local aggregate initializers in general are loaded from an @NN template at the point of declaration, so declare them in an inner block where the target first loads them (jvsboot.c).
- The bytecode `sinf`/`asinf`... calls hit the double MSL functions: use `static inline float mk_sinf(float x){ return sin(x); }` wrappers (they give the frsp after the call). A plain `#define sinf sin` misses the frsp.
- `if ((f0 = f0) == 0.0F)` was needed once to get the target load order (bytecode atan2 case).
- mkgp2 HSD vs melee: TETev has an extra `a_range` byte; TECnst `comp`/`ctype` are u8, with a `range` byte (size 0x14). texpdag has a new range pass (`CalcRange`, called from HSD_TExpSimplify). Recursive `HSD_TExpUnref` written as a switch gets inlined 2 levels like the target.
- Left over (NonMatching): texp TExp2TevDesc (callee-saved register permutation only) and HSD_TExpSetReg (float-constant hoisting, `x<0?0:x` as srawi/andc). texpdag: assign_reg/order_dag/CalcDistance/MakeDag are 97-99.7% (temp register swaps); SimplifySrc 88%, SimplifyThis 96%, SimplifyByMerge 33% (mkgp2 version is 0x17C8 bytes vs melee 0xA04), HSD_TExpSimplify reg swap.
- Helper scripts (ephemeral, /home/claude/work/hsd): tv.py (try line variants, keep the best), asl.py (align HSD_ASSERT line numbers to the target), blmap.py, refs.py (data/callees referenced by a target range).
- (G2) objdiff can show a switch function at 100% even when the case bodies are in the wrong order. The jump table relocs pair loosely, so only main.dol catches it (bytes differ inside the .data jump table). Fix it by ordering the case labels in the source by the address of their bodies.
- (G2) u64 kart status flag test `lwz 0x304; lis/li r5,0; and/and/xor/xor/or.; bne; b; li r5,1` (bool shares the mask's zero register): write it as `static inline u8 has_flag(KartStatus *st, u64 mask) { u8 r; if ((st->flags & mask) == 0) r = 0; else r = 1; return r; }` taking the STATUS POINTER (`KartStatus *st = *(KartStatus **)(drv + 0x304)`), not the u64 value. A later `st->flags & 2` reuses the loaded words. Passing the u64 by value gives `beq; li 1` or a different coloring. Fixed Teresa_TrackToKart_Sub.

## Group 8 Triforce AM/net (0x8028250C..0x80294E6C) DONE 2026-10-25 (PRs #282, #300)
- Triforce AM TUs (amsock/amsrv/acsocket/amuart/amsys...) use GC/1.3.2 `-inline noauto` + `-use_lmw_stmw on`.
- Leftover NonMatching (all register allocation): amnet 10 fns, amsrv fn_80291134/fn_8029121C, acsocket 12 (target keeps Buf in a reg, `addi r26,r5,0`), amuart fn_8029345C, amsys fn_80294810 (r3/r4 swap) + fn_80293DD4 (switch state machine with fallthrough).
- MWCC idioms found: branchless index clamp only matches as a macro `&a[(s) & -((u32)(s) <= 63)]` (inline fn shifts regs); `beq; b` on a single compare = one-case `switch`; struct assignment gives lwz/stw pairs without memcpy; bitfields give rlwimi; `x = FALSE; x = (cond);` pattern; `~flags & N` gives `not` + beq; take `p = &arr[0]` local instead of repeated global struct access; expression grouping `off + (len + 0x1F)` avoids CSE.
- perm.py prints BEST but restores the original file: apply the order by hand.
- (G2) `(float)sin(x)` inside a float expression gave swapped FPR operands (fmadds/fmuls order) in every form I tried; an inline wrapper `static inline float sinf(float x) { return sin(x); }` fixed it. For `(1 + sin) * 0.5` the target wanted `/ 2.0f` (CW turns it into a *0.5 with a different operand order). Fixed Dispatch16To1d and Dispatch24To29.
- (G2) CW evaluates nested call arguments right to left: target `alias = Lookup(); kart = GetTarget(); f(drv, kart, alias)` came from `f(drv, GetTarget(self), Lookup(id))` written inline; a named `alias` temp swapped two saved registers (ChainShell_GrabAndArc_Sub).
- (G2) When the code after a state switch runs only for one state (other states return), put that common code INSIDE that case and end with `break;`. A `return;` per case plus a code tail after the switch leaves dead `b` instructions (Teresa_GrabAndArc_Sub).
- (G2) Stack-slot order for by-value Vec temps: the function's own temps go on top in source order; temps and locals of inline helpers go below them, and deeper inline nesting goes lower still. Scalars (int/float locals whose address is taken) go below all aggregates. So when a target's copies sit in "odd" order, split the code into inline helpers until the depths match (ItemObject_Tick_Kind3dTo3f_GreenShell: rebound/fade helpers at depth 1, the shatter burst at depth 2 via a one-line wrapper for the other cases).
- (G2) SoundMgr_PlaySE_Positional / _WithChannel, Item_BounceOffWall, DrawEffect_ItemHitBurst_Spawn, Item_ProbeLateralGroundPitch etc. take Vec by value: declaring them that way gives the target's per-call stack copies in the right order, with no named locals (Dossun_State1And2_HeldOrFly).
- (G2) `lbz; clrlwi` for an anim id from a table int: write `tbl[i].anim & 0xFF`, not `(unsigned char)tbl[i].anim` (the cast moved the mulli) (ItemObject_Tick_DispatchShellGroup).
- (G2) Doubled `b .Lend; b .Lend` after an if/else that both return: the source was `if (c) {...} else {...; return;} return;` (Dossun_State1And2_HeldOrFly).

## Leftover follow-up (2026-10-25, PR #348)
- RTTI type-name strings: `#pragma readonly_strings on` in a `-RTTI on` C++ TU moves the `@NN` class-name strings from .data to .rodata, as in the target. The type_info objects stay in .sdata and the base lists in .data. anon_801FEBD8 / cLNormal3DWrap still need TU merging plus ownership of those shared RTTI ranges. For example, 0x803C0238.. holds the clMn* names for 0x801FEBD8..0x80201xxx, so the real class names are clMnTimeLightsSpr, clYTaskInterface and so on.
- cLNormal3DWrap weak base dtor order: defining the template dtor out of class at the end of the file moves dtor_800897B8 last, but Mgr_Dtor then no longer inlines it (0x104 instead of 0x130). Still open. (thread B, later) With real virtual dtors + `-RTTI on` + `#pragma readonly_strings on` at the end of the TU, `-inline noauto,deferred` and the functions written in REVERSE address order, every function size, .data (base list, derived vt, base vt), .rodata (names) and .sdata (type_info) order match the target; owning .rodata 0x80312810..50, .data 0x803FE458..80, .sdata 0x806CEFD0..E0. Only the weak base dtor copy still lands right after the ctor (10 bytes of bl offsets differ). dtk refuses a split TU for the weak copy ("reversed extab group"). WIP: wip/cLNormal3DWrap_rtti_deferred_wip.cpp + .patch.
- acLib (#348): merging the 3 TUs and owning .bss/.sbss matched fn_80255640. The `bge end; b dflt; b dflt` tree came from `case 1: ... case 0: break; case 2: default: ...`.

## Fakematch rule (naari3, 2026-10-26)
- A fakematch is code that matches but is not what a human would write, for example permuter output like `if (x && x && x) {}`, `(0, v)`, or an offset in a variable. It is allowed, but mark it with a `/* fakematch (...): why */` comment, and put the natural code the original most likely had in that comment, e.g.
  `/* fakematch (permuter): the dummy test fixes the block order.\n * Natural code: inner = a * b * *(float *)(p + 0x10C); */`
- Example: src/game/Item_OrbitAnchorKart.c, src/game/ItemHandheldRender.c.
- Permuter pipeline notes: [near-miss thread], PRs #349-#356. Seeding a second permuter pass from the best first-pass output found 4 more matches.

## Lessons from onmokoworks' native C++ splits (main 2026-10-26, 0x8023CC74..0x8024D244, 82/90 fns, no asm/manual EH)
Source: their commits + docs/notes/*-20261026.md. They took UNSPLIT auto_* ranges straight to genuine C++ with compiler-generated EH.
- Small TUs: 1-5 functions per TU (one class lifecycle, or even one function). Each gets its own splits.txt block (extab + extabindex + .text) and `Object(..., extab_padding=b"", extra_cflags=["-Cpp_exceptions on"])`. The empty extab_padding only routes the TU through the postprocess rename hook; no manual EH is involved.
- The compiler's anonymous EH labels (`@67`, `@68`, ...) can be renamed in tools/extab_user_renames.json to the target names (`"@67": "@etb_8001E368"`, `"@68": "@eti_8002B598"`). That is what lets a C++ TU with automatic EH link at the target's extab addresses. The @N numbers shift whenever you add or move a declaration, even if the code bytes stay the same, so re-dump the .o symbols after every header edit.
- Rename the mangled C++ names to the existing target symbols in the same JSON: `__nw__FUl`->Alloc, `__dl__FPv`->MemoryManager_TimedFree, `__vt__X`->lbl_..., `__ct__/__dt__`->the existing fn. Weak inline-dtor copies (VHolder, FlowFaderI, ResCtrl) are aliased to the copy that already lives in another TU, so the linker drops the duplicate text/EH/index. Template mangling counts the whole name: `__dt__21VHolder<10FlowFaderI>Fv` (21, not 20). Check the real name with `nm` before you write the mapping.
- Pick the source shape from the target's EH actions: DELETEPOINTER means a real `new T(...)` with an inline ctor. DESTROYBASE / DESTROYMEMBER means an inline base ctor or dtor plus member objects. SPECIFICATION islands mean `throw()` members (e.g. VHolder members); the owner itself has none. DESTROYLOCAL means a stack ResCtrl / TextManager in a `{}` scope.
- Reuse the shared class models in include/game/FlowScene.h (VHolder<T>, FlowSceneList, SceneListImpl, FlowFaderI/F, ResCtrl). Write only a narrow, per-TU "view" struct for the owner's fields. Two classes with the same layout are still different types, so give each view its own name (ODR).
- `(constant == x) == 1` keeps the fcmpu/mfcr/extrwi boolean sequence. `-use_lmw_stmw on` is set per TU.
- Verify each live EH/index record on its own. The aggregate extab % includes discarded weak copies, so a low aggregate can be fine. A full DOL SHA match is the real test.
- Stop rule they follow: after 3 structural attempts, keep the function NonMatching in its own TU. No permuter or asm fallback.

### Applying this to the ~480 inline-asm game functions
- 521/549 of them sit in "asm + manual `.extab_user`" TUs (see notes/leftover_survey.md). These TUs already run through the postprocess rename hook. You can convert one function at a time: write it as real C++ under `#pragma exceptions on`, delete its manual extab_/extabindex_ entries, and map the compiler's `@N` labels to the same `@etb_/@eti_` names the manual entries used. Keep the TU's other asm functions as they are, and list every function of the TU in tools/extab_order.json (clFlowCup_Dtor pattern).
- When the asm TU's extab order is NOT reversed, split it into per-class TUs as above instead of growing one big TU. This shrinks the regalloc/ordering blast radius and avoids reorder_extab work.
- The FlowScene.h / VHolder / ResCtrl models cover most of the scene/flow/card code in G5/G6. Check them before you invent new structs.

## asm → C++ conversion thread (2026-10-26, PR #360 KartTireFX)
- Only 41 of the ~460 remaining inline-asm game fns have real EH actions; ~305 have an empty 8-byte extab, so EH was never what kept them asm. Inline asm already counts as matched: converting gains no function count, only real source (+data %). Commit only 100% conversions.
- Whole-TU conversion works best on TUs that are 100% asm and untouched (no earlier C attempt). KartTireFX (13 fns) went to 100% C++ with owned .rodata.
- `-inline deferred` explains a target .rodata whose function-local aggregate initializers appear first and in REVERSE function order: write the functions in reverse address order, build with `-inline deferred` (text + extab come out reversed = target order), .rodata stays in parse order. Inline-expanded literals (assert strings in JObj inlines) land last.
- HSD JObj inlines for this version (KartTireFX.cpp): MtxIsDirty assert 0x25d, SetRotationX 0x2a4/0x2a5, SetScale 0x316/0x317, GetMtxPtr 0x47c, CopyMtx 0x495/0x496. The SetMtxDirty macro form gives the `cmplwi; beq; bne; __assert` shape.
- A reload of the dst jobj after `HSD_JObjGetMtxPtr(src)` = helper inline taking (jobj, mtx) called as `Helper(self->dst, GetMtxPtr(self->src))` (args evaluated right to left). Register order of a `root = f(); Dirty(root);` local flips vs `DirtyInline(f())`.
- `if (p) delete p;` keeps the explicit null check before a non-virtual out-of-line dtor call; bare `delete p` drops it.
- Removing an unused inline shifts the compiler's @N numbers: re-dump nm and update the renames after any source edit.
- Small near-misses parked (EH matched exactly, body not): clItemBox_FactoryCreate (lwz hoisted above stw r31), ItemObjectManager_Init (`mr r30,r0` vs direct addi), BtMode_Init (needs the bt-mode file's .rodata pool 0x80320960, i.e. a merged BtMode_Dtor+VSMode_Init+BtMode_Init+dtor_800A0688 TU).
- (asm→C thread, #361-#364) Early-return `bge L; b end` / `beq L; b end` pair (instead of one inverted branch): the check is the LAST operand of an `||` early return, e.g. `if (!fn(&v) || v.z < c) return;` or `if (!obj || !visible || (flags & 2)) return;`. A separate `if (...) return;` gives the single inverted branch. Value-returning version: `if (x != 0) return x;` (MJObj_InitMember_RGBA).
- (asm→C thread) `lbz; cmpwi` with no extsb = plain `char` field (char is unsigned here but the compare stays signed). C++ virtual calls (`lwz r12,0(r3); lwz r12,N(r12)`): `#pragma cplusplus on` in the .c with extern "C" functions (CardTaskManager_Tick). Some TUs need `-use_lmw_stmw on` when the asm used stmw.
- (asm→C thread) Range test `cmpwi r,HI; bge skip; cmpwi r,LO; bge do; b skip` = a `switch` with consecutive cases LO..HI-1 sharing one body (ItemSelect_GiveItemOrQueueDrop: `case 0x7b: ... case 0x87: state = 3;`). An `if (x >= LO && x < HI)` gives the wrong register choice and no `b`.
- (asm→C thread) Multi-dim table offsets (`mulli a,0x1c20; mulli b,0x320; ...; lfs 0x15c0(r)`) matched only as a real array cast: `(*(float (*)[3][9][2][2][50])(base + 0x15c0))[a][b][c][d][e]` (TaRecord_GetTime_*). The flat `base + a*0x1c20 + ...` sum swaps the add operands.
- (asm→C thread, #366) `addi r0, r3, lbl@l; stw r31; mr r31, r0` (instead of `addi r31, r3, lbl@l` right after the save) = the loop walks a pointer. Index the global instead: `memset(lbl + i * 0x1c, ...)`, `Free(g_mediaBuffers[i].data)`. This fixed SyncSlot_Reset and FreeMediaBuffers, which were parked for that prologue.
- (asm→C thread, #366) C++ implicit `operator=` (memberwise struct copy) makes CW emit the calling function LAST in .text. Write the memberwise `operator=` in the class body to keep source order. 8-byte members copied as `lwz r5; lwz r0; stw r5; stw r0` = `unsigned int w[2]` array members (HeapStats BootState).
- (asm→C thread, #366) A shared .rodata string pool base (`addi r31, r4, lbl@l`, then `addi r3, r31, 0x6ac`) that the TU does not own: `char *str = (char *)lbl;` declared first, with the first use written `&str[0x6ac]` (HeapStats_DumpForTag). `const char *` or `str + off` on the first use lets CW rematerialize lis/addi at every call.
- (asm→C thread) Map extab @N names by function, not by object offset, when tools/extab_order.json reorders a TU: `objdump -r -j extabindex obj` lists fn -> @N. An extab record referenced from .data needs `"@N": "global:@etb_..."`.
- (asm→C thread) Parked after a few probes: AssocTree_Init (lbz scheduled after the two zero stores), card_send_read_cmd_init (if/else re-tests the u8 result), Vec3_Lerp (fmadds order), plus the list in memory asm-to-cpp-thread.

## cperm.py: text permuter for C AND C++ TUs (R5 thread, 2026-11-07)
- `tools/helpers/cperm.py` (no pycparser, so C++ works). Run from the repo root after a normal build:
  `python3 cperm.py src/game/Foo.cpp game/Foo fn_XXXX --minutes 10 --out /tmp/cp_fn` (regions auto-detected: the target fn, found by name or via its mangled name in tools/extab_user_renames.json, plus every `inline` helper in the file; override with `--region '<unique line prefix>'`, repeatable). `--cc 2.6` overrides the compiler.
- It compiles with the TU's own ninja command (incl. postprocess_extab_user / sdata2), disassembles with dtk and hill-climbs a weighted asm diff (same mnemonic 1, other op 3, insert/delete 5). ~50 compiles/s on 4 cores for small TUs. Best sources go to OUT/best_NNNNN.cpp; it stops at 0.
- Mutations: swap adjacent statements, move/split declarations, commute + * & | == != ^ operands, flip comparisons, `!= 0` <-> `? 1 : 0`, ++/-- pre/post, hoist a member read into a local, retype a local, extra `{}` scopes, `register`.
- Temp copies are written next to the source as `src/<dir>/.cperm_wN.<ext>` (needed for relative includes); do not `git add -A` while it runs.
- A 0 is only a candidate: copy it in, clean up the fakery (mark fakematch per docs/per_fn_matching_strategy.md), rebuild, and check the full main.dol SHA. `@N` rename shifts are invisible to the score (see the TitleNameHud gotcha: re-dump `objdump -t` of the raw .o and fix tools/extab_user_renames.json).
- `cbatch.sh LIST MINUTES OUTDIR` runs it over "src obj fn" lines; results in OUTDIR/log.txt.

## R2 thread (2026-11-07): register-swap fixes that worked
- Callee-saved GPR/FPR swaps inside a loop or block: move that block into a `static inline` helper that takes the object pointer (e.g. `Slot_Tick(ks->karts[i])`, `RYPair_Spawn(p)`, `Popup_CountIdle(o)`). Inlined params get allocated differently; fixed fn_8015D9F0, fn_80160588 and most of fn_8015CD74.
- `u8 flag = 0; if (a || b) flag = 1;` reg swap -> `bool flag = a || b;` (fn_80160E04).
- `if (Get())` producing `bne; li r0,0; b; mr r0,rX` = inline `return !p ? 0 : p;` (the `if (!p) p = 0` form gives a single bne).
- Three pointers into one row (`r,g,b`) allocated in reverse: declare `b; g; r = tbl[i]; b = r + 2; g = r + 1;` (fn_8015D4F8).
- A u8 arg used directly (no clrlwi on entry): declare the param as `unsigned char`, including in pass-through callers.
- A function whose target uses a *different* label for the same double magic constant (lbl_806D8840 vs lbl_806D86D0): tools/postprocess_sdata2.py now retargets those relocs (commit 871a9a6). Rebuild the .o after editing the tool (ninja does not track it).
- An extra var copy like `float d = y - k; alpha -= d * c;` can flip FPR order of a sub/mul pair.
- 8-byte `subi r3,r3,N; b target` functions are CW multiple-inheritance thunks. Write `struct B0 { pad; virtual void key(); }; struct B1 { virtual ~B1(); virtual ... }; struct C : B0, B1 { virtual void key(); overrides... }; void C::key() { delete this; }` so the vtable and its `@N@method__1CF...` thunks are emitted in the TU, then map the thunk and its callee names in tools/extab_user_renames.json. The TU needs `.cpp`, `extab_padding=b""` and `-Cpp_exceptions on` (the key function must generate an extab, otherwise `dtk extab clean` fails). Function-level 100%; TU stays NonMatching (commit 1ed4905).

## autosweep.py: unattended sweep of mechanical fixes (2026-11-07)
- `tools/helpers/autosweep.py` (needs cperm.py beside it). Run from the repo root after a full build:
  - `autosweep.py list` lists NonMatching fns per NonMatching TU, skipping TUs named in any open `unit-claim` issue (title or body; `--all` keeps them).
  - `autosweep.py cc --flags --jobs 4 --out /tmp/as` rebuilds each TU with GC/1.2.5n,1.3,1.3.2,1.3.2r,2.0,2.5,2.6,2.7 x {none, -use_lmw_stmw on, -inline deferred, -fp_contract off} and reports HIT (a fn reaches 0 and no fn gets worse) or `impr` (total diff drops). ~5 min for 148 TUs on 4 cores. `autosweep.py apply game/Foo 2.6 ["-use_lmw_stmw on"]` edits the Object line.
  - `autosweep.py perm --max-score 40 --minutes 5 --out /tmp/as` runs cperm.py on every report-NonMatching fn with score <= N, smallest first, using the best compiler from `cc`. Resumable (skips fns with OUT/perm/<fn>/done); wrap it in `timeout` under a harness-tracked background Bash (2h max).
- Scoring normalizes `.L_` labels, `@N`, `jumptable_*` and relocated symbol operands (`X@ha/@l/@sda21` -> `S@..`), because objdiff tolerates name drift (lbl_X vs ...bss.0). cperm.py got the same normalization, so switch tables and data-symbol renames no longer block a 0.
- First full run (main 8ea9e21, 148 unclaimed TUs, 241 fns): **no compiler-switch hits left** (other threads already harvested them). Largest drops, worth a manual look with that compiler: ranking_display 1310->514 (1.3), fn_801F27B4 1922->1133 (1.2.5n), fn_801C9288 2338->1668 (1.2.5n), CollisionFile_Load 79->30 (1.3), fn_801ECA14 118->78 (1.2.5n). 86 fns are within score 40.

## More patterns from R5 (2026-11-07 afternoon)
- Extra dead `b` after `cmpwi 0; bge case0; b end; b end`: write `switch (s) { case 2: break; default: break; case 0: ...; }` (no case 1 even if 1 does nothing). Matched KartWheelSmokeOrbital_Tick, same as EffectStarBurst.
- `lwz r0,p; cmplwi; bne L; li r0,0; L:` (pointer null-check select): write `!p ? 0 : p`. `p ? p : 0` gives `beq; b; li`. Matched TransitionEffect_GetOrCreate.
- TU whose fns are all 100% but fails SHA when flipped to Matching: check the .o function order vs target (objdump -t). MWCC sometimes emits functions in reverse source order; swap the definitions in source (HudFind).
- Quick win scan: units in report.json whose functions are all 100% but configure.py says NonMatching -> flip each, incremental ninja (~5s), keep the ones with main.dol OK (10 TUs in aa1df21).
- Real C++ ctor shape `lis r6/addi r6 base vt; stw r6; addi r0 own vt; stw r0`: base class with `virtual ~Base();` (declared only), derived ctor out of line, rename ctor/vtables in extab_user_renames.json, EH-free -> add TU to the ctor-bridge list in configure.py (accepts "objview/..." paths now).

## asm → C thread B (2026-11-07, clFlowItem_Draw/Update matched)
- Regalloc-only residues on loops over sub-objects: write each sub-object's work as a small `static inline` taking the sub-object pointer (IconPack_Draw(icons), ItemGrid_Draw(grid), ItemSel_Begin(sel)). The strength-reduced walker of a loop that is the LAST use of the inline parameter then reuses the parameter register (no `mr rX, rY` copy), and an inline parameter can share a callee-saved reg with an unrelated local (clFlowItem_Update: sel shared r31 with &g_playerData). Plain locals never did this.
- Later loops in the same inline with their own scoped counter (`for (int k = 0; ...)`) instead of reusing `i`: a shared `i` merges the webs and shifts every callee-saved color by one.
- Fast iteration: compile one-line/whole-file source variants with the TU's own `ninja -t commands` line in parallel and diff the fn (normalize `bl`/@ha/@l/@sda21). ~50 variants in under a minute found both.
- (thread B, clFlowItemSelect_Init 12dc847) The reverse case also happens: `li rA,0; mr rB,rA; mr rC,rA` (one zero copied into several loop counters/IVs) needs counters SHARED at function scope (`int i, j;` reused by those loops); scoped `for (int i` gives separate `li`. Hill-climb which loops share: flip one loop's `int` at a time.
- `lwz r0,g; cmpwi r0; mr rX,r0` vs target `lwz rX,g` for a clamped global copy: write `if ((c = g) < 0 || c >= 13) c = 0;`.
- Two array args to an inline ctor loaded in the wrong order: declare the read-only table `const` (`extern const int clFlowItemSelect_Init_rodata_8039B3C8[3]`).
- A free-standing draft can be diffed without touching the TU: compile it with the TU's ninja command line into a scratch dir and diff the mangled name against the target fn (bl targets normalized).

## Pooled-data `lis` scheduled early in a ctor = the TU owns its .rodata (R2, 2026-11-07)
- Symptom: target ctor does `lis rA, base_vt@ha; lis rB, own_vt@ha; stw r0; lis rC, lbl_POOL@ha; ... addi rX, rC, lbl_POOL@l` (pool lis/addi interleaved with, or ahead of, the vtable stores and member-ctor calls), while ours puts the pool lis/addi after them. `pool + 0x5a4` on an `extern const char lbl_POOL[]` can never reproduce it.
- Cause: the original TU defined that rodata itself and CW addresses it through the section anchor (`...rodata.0`). Fix: give the TU a `.rodata start:..end:` split covering the whole pool (start = the base the code uses, end = where the next TU's rodata starts), define every object in the TU with its exact bytes (strings as literals, tables as typed arrays; pointers in tables as real initializers), and reference the objects by name, not via `base + off`. Any symbol other TUs (or auto sdata/data) reference must keep its `lbl_XXXXXXXX` name (extern "C").
- The class's other functions (draw/update/dtor, often separate split TUs right before the ctor) belong to the same TU: merge them (one source, one split entry, drop their Object lines). If some of them need `-use_lmw_stmw on` and the ctor does not, wrap them in `#pragma use_lmw_stmw on` / `reset`.
- Landed: f7f294f SoundProp (objview/fn_8018A70C + its dtor), 16b4f8d Cave16A (mapeffect, + Scene_8016ACD4). Candidates with the same shape: Jungle16A, objview fn_801987C4/fn_801967F0/fn_8018CFC4/fn_80187410, resultscene ResultPartY ctor fn_8015C41C (pool resultscene_rodata_803682B0, rodata 0x803682B0..0x80369238, two pointer tables at 0x80368EAC/0x80369054).
- Byte dump helper: read the DOL at a VMA (parse the 18-entry DOL header) or copy the `.obj` blocks from build/GNLJ82/asm/auto_06_*_rodata.s.
- Outcome of the 4-thread permuter sweep (2026-11-07 11:40-14:20; 89 fns with score <= 40, then 17 with 41..150): **cperm found 0 matches**. Only improvements came out (acBind 43->4, AI_CalcTargetSpeed_PairTracking 34->14, BackupWriteRecord 64->31, RankLog_OnMatchEnd 23->8, fn_80282CDC 26->12, HSD_TExpSimplify 32->16). The shard threads still landed matches by hand: RaceScene_FrameUpdate (f36235a), and TObjInfoInit / HSD_TObjSetup after merging 10 tobj TUs (0195f28). Takeaway: random text permutation is used up here. What remains needs structural changes (TU merges, shared section bases, class layout), not more permuter time. To reseed from a best output, copy it into the source's own directory (relative includes) and run `cperm.py src/<dir>/.seed_fn.c <obj> <fn>`.

## PMF constant temporaries in .data + `-inline deferred` order (R2, 391b111 clItemBox)
- If a __sinit copies 12-byte {0, -1, fn} records from `.data` (base reg + offsets, with a second
  pointer reg like `addi r11, r29, 0x48` as the destination), those records are mwcc's compiler
  temporaries for member-function-pointer constants (`&Cls::Method`). Write a real
  `typedef int (Cls::*Step)(); Step tbl[] = { &Cls::A, ... };` and rename `A__3ClsFv` to the
  C symbol in tools/extab_user_renames.json. Every other `&Cls::A` in the TU (ctor
  `step(&Cls::A)`) adds a temp too, so all of those functions must be in the same TU.
- The temps are created at parse time (source order). If the target's order does not
  match the text order, compile with `-inline deferred` (which emits functions in reverse
  source order) and write the source in reverse address order.
- When you merge TUs whose extab was referenced from auto data, keep the
  `"@N": "global:@etb_<addr>"` rename for the new @N (see the nm output for extab offsets).

## Local declaration order decides register coloring (asm→C thread B, 2026-11-07)
- For a diff that is only a register permutation (e.g. one loop pointer r25 vs r26), move every local to C-style declarations at the top of the function and brute-force their ORDER. CW numbers user variables by declaration order, and that number breaks coloring ties. CharaSelect_SetupCharacterDisplay (4 lines, R1 had tried permuter + GC/2.6) matched with 1 of 1500 random orders (664ab80). Keep a comment that the order is load-bearing.
- Script: write N shuffled copies, then `xargs -P6` over a compile+diff helper (~25 compiles/s on 4 cores). It does NOT move compiler temps (CSE'd `kart*4`, pool bases): clFlowKart_UpdateDisplay and clFlowRound_Update did not budge.
- Over-split class TU merge recipe (clFlowChara 07e057e, 8 TUs): one .cpp in .text order with per-function `#pragma exceptions on/off` and `#pragma use_lmw_stmw on/reset`; unify duplicate extern "C" prototypes (use void* params and casts at call sites); rename clashing local typedefs; move the old TUs' tools/extab_user_renames.json entries under the new path; list every function (plus weak inline dtors such as `dtor_800869D0`) in tools/extab_order.json. A vtable only reached through a pool base (`base+0x224`) needs `#pragma force_active on`, or mwld deadstrips it together with the virtuals. After a json change, delete the .o (ninja does not track the json).

## One shared loop index across several loops (R2, 032ddac)
- Effect_KartAuraCompound_Update was 94.7% with the regs of the hoisted `li 0`/`li 1` constants swapped and a `li r29,0; mr r31,r29` index init. Declaration-order brute force did nothing. Using ONE function-scope `int i;` for all three `for` loops (instead of `for (int i ...)` in each) matched it exactly. Try this whenever a function has several sibling loops and only constant/index registers are off.

## Dead `b` after an early return = an unrolled 1-iteration loop (R2, bb39da1)
If the target has `li r3,1; b end; b next` (an unreachable branch) and the data is indexed by a channel with count 1, write the original loop `for (chan = 0; chan < 1; chan++)`. In ambackup_nm3, one loop per if/else branch matched; one loop around the whole if/else hoisted the address constants instead.
- (thread B, 2026-11-07) 0x8020E2D8..0x8020F220 (anon_8020E2D8/E3D0*/fn_8020E388/E3AC, the "FadeLogo" classes) was ONE RTTI TU (the duplicate clYTaskManager name/type_info is just CW emitting the template twice; earlier note saying "two TUs" was wrong). Real names from the type_info: PopupRoot=clYTaskInterface, PopupTask=clCTaskInterface, FadeLogoScene=clTimeupDisp, TaskListBase=clYTaskManager<clCTaskInterface>, FadeTaskBase=clTimeupInterface, FadeLogo=clTimeupTime, TaskListImpl=clCTaskManager. A full RTTI re-merge was abandoned (data/rodata/sdata emission order never matched). Instead nm2 was flipped in place (6621d03): keep every vtable out of the TU with undefined key stubs (`virtual void _keyB();` etc., new slots appended last so offsets don't move; a stub must be declared FIRST in the class to beat a non-inline dtor as key function), and when a weak inline copy (here ~TaskListBase, fn_8020EC70) would otherwise only be emitted with the vtable (at TU end), emit it in place with a same-layout twin class whose non-inline dtor has the same body and whose __vt__ is renamed to the real lbl_. Linking a TU that emits RTTI/vtable data you don't own shifts all .data (local @NNN names + __RTTI__ can't dedupe).

## pragmasweep.py: compiler x opt_* pragma x declaration-order sweep (2026-11-07, mid-range thread)
- In the repo: `tools/pragmasweep.py`. Run from the repo root after a normal build. It never edits the repo: each variant is compiled from a scratch copy next to the source with the TU's own `ninja -t commands` line (about 0.01 s per compile with wibo, so ~220 variants take 2 s).
- One function: `python3 tools/pragmasweep.py fn game/Foo FN [--decl 200] [--cc 1.3,2.6] [--k 2]`. It tries GC/1.2.5n,1.3,1.3.2,2.0,2.6,2.7 (the TU's own first) x {no pragma, each of opt_common_subs / opt_propagation / opt_lifetimes / opt_dead_assignments / opt_loop_invariants / opt_strength_reduction / peephole / scheduling `off`, and every pair}. The pragmas are wrapped around the function with `#pragma push/pop`. `--decl N` then tries N orders of the plain declarations at the top of the body on the 3 best settings. Output is ranked by diff lines, and the best source goes to /tmp/pragmasweep/<FN>.best.<ext>.
- C++ members are found through tools/extab_user_renames.json (target name -> mangled) and, if needed, `--demangled 'Class::Method()'`.
- All near misses: `python3 tools/pragmasweep.py batch --min 80 --decl 60 --md docs/pragmasweep_results.md` (resumable cache in /tmp/pragmasweep/cache.json; the table also shows who claims each TU).
- To apply a hit: set `mw_version` on the Object, put the pragmas right before the function (or copy them from the best source), clean build, and check main.dol.
- Hits so far: fn_80204218 13 -> 4 (GC/1.3 + opt_propagation off), CollisionFile_Load 79 -> 4 (GC/1.3 + opt_propagation off); R5 matched BackupWriteRecord the same way (72618d2).
- cLNormal3DWrap weak base dtor (R1 thread, 2026-11-07 17:20): on top of the deferred WIP, none of these put dtor_800897B8 last while Mgr_Dtor still inlines it. Tried: explicit instantiation (`template class ...;`) at the top; an explicit specialization instead of the template; an out-of-class inline definition at the top, at the end, or between Ctor and Dtor; `#pragma auto_inline on` around the definition; `-inline auto/on/level=8,deferred`; a dead static function referencing it (static functions are not stripped); and every GC compiler version (1.0..1.2.5n even put it 7th). The rule is simple. An inline dtor's out-of-line copy is emitted right after the first compiled function whose codegen references it (Mgr_Ctor's EH cleanup). A non-inline or later-defined dtor is emitted last but never inlined.
- SOLVED cLNormal3DWrap (R1, 8c62f13): to emit a weak template base dtor LAST while the derived dtor still inlines it, turn the template into an explicit specialization (`template <> class clNodeManager<char *, clNormal3D *> {...}`, same mangled name). Declare the dtor in class, and define it out of class and NON-inline before every function, wrapped in `#pragma auto_inline on` / `off`. A non-inline function is emitted where it is defined (with -inline deferred and reversed source, defined first = emitted last). auto_inline lets the derived dtor inline it even under noauto. Then put its extab entry where the target has it (after the ctor) with tools/extab_order.json. A template member defined out of class is never inlined, because it is instantiated at the end of the TU. Careful with sed on configure.py: a global substitution on "-inline ..." silently changes other TUs' flags (e.g. clItemBox -> undefined @etb at link).

## Small form changes that moved near-misses (R2, 5ab64ec / 597cbc8)
- Shift-then-mask helpers: `u32 a = Step() << 1; ... return (a & M1) | (b & M2) | (c & 3);` allocated differently from `u32 a = Step(); return ((a << 1) & M1) | ...` (random_nm1 30 -> 4 diff lines).
- Float literal vs extern const: `1.0f` as a call arg (two identical args) or a `15.0f` clamp changed load order and fadds operand order even though both resolve to the same sdata2 label. Try both spellings per site.
- Inline wrapper `TaskIter Remove(TaskIter it) { return it = entries.erase(it); }` reproduces a result -> param slot -> caller copy chain (fn_8020F080 wip3).

### Weak inline copy placement via `#pragma defer_codegen on` (from R5, RaceDigits fn_80246DE4)
Put `#pragma defer_codegen on` right before the last functions (e.g. `inline Base::~Base(){...}` then `Derived::~Derived(){}`).
The inline defined after its user still inlines, and its out-of-line weak copy is emitted after the users, at the end of the file.
Don't enable it for the whole file, because that reverses emission order.
If a ctor inlining the dtor pulls the weak copy forward, route through a different (e.g. inline pointer) ctor.
Alternative used for cLNormal3DWrap: an explicit specialization with a non-inline def wrapped in `#pragma auto_inline on/off`.

- (R2 2026-11-07, PCBComm_UpdateSyncPhase5) If the target has `li r31, sym@sda21; mr r5, r31` but mine rematerializes `li r5, sym@sda21`, write the copies as chained assignments (`p = base = sym;`) instead of `base = sym; p = base;`. Dropping a small local (`int v = first + 2;`) and writing the expression at its use can fix an unrolled-loop r5/r6 swap.

- (R2 2026-11-07, ItemHitPropagation) If the target reloads `p->field` where mine reuses an earlier load, and the earlier load sits in an inline helper, have the helper read it through a different struct type with the same layout, e.g. `((KartObj*)p)->field`. mwcc doesn't CSE loads across distinct member types, and freeing that register can fix a whole run of r3/r4 shifts. A dead duplicate `b end` right after a switch's compare tree comes from an empty `case N: break;` placed before `default: break;`.

### Section-anchor addressing (`addi rX, rBase, 0x0` / `addi rX, r31, off; lwzx`) (R2, 2026-11-07)
If the target loads a data/rodata base once (lis/addi into r31) and then makes pointers with `addi rX, r31, off`, including an explicit `addi ..., 0x0`, those are separate objects that live in **this TU's own section**. mwcc addresses every object defined in the TU (static or global) relative to the section anchor. You get the same code only when the TU owns that range in splits.txt and defines the objects as real arrays/structs. Writing `(char*)lbl_X + off` folds the offset into displacements and never matches. Example: CoursePropCtor fn_8016E568 went 97.39 -> 100 by taking over the unowned `.data 0x80491150..0x804911C4` (docs/onmoko_patches/CoursePropCtor.patch). A global object that other TUs still reference by name can stay a global definition. To find candidates, grep near-miss target asm for `addi r\d+, r\d+, 0x0$`.
- pragmasweep caveat (2026-11-07 23:50): the ranking is unified-diff lines, not objdiff %. A big line drop can still LOWER fuzzy % (jvsio fn_80282F54 102→59 lines but 96.5→84.8%). Rebuild and check report.json before keeping a pragma.
- pragmasweep `--objdiff` (2026-11-08): scores every variant with objdiff-cli on the raw .o, as (100 - fuzzy%) * 100, so 348 = 96.52%. The ranking then matches report.json. Use it for anything that isn't a near-zero diff.

## `addi rX, rBase, 0x0` from one big const table = several pooled objects (2026-11-08, mid-range thread)

If the target loads a table address once (`lis/addi r30, lbl_X@l`) and then
passes `addi r4, r30, 0x0`, `addi r4, r30, 0x28`, `0x40`... to memcpy etc.,
`lbl_X` is not one array. It is several TU-owned objects, and the TU pools
them off one section base. (CW pools when a function touches 3+ objects of
the section; the first object sits at offset 0, so you get `addi …, 0x0`.)
Split the array into one object per offset the target uses, define them in
order in the owning TU, reference each by name, and update symbols.txt.
Example: amnet fn_8028D8CC, amnet_setup_nm_rodata_803F2798[36] -> 5 tables (99.83 -> 99.97).
This does NOT explain the acsocket `lwz r5, bufOff; addi r29, r5, 0x0`
copy: there the source register is a loaded value, not a section base.
That one is still open (opt_lifetimes off gets acModifyMyIPaddr to 97.88
with only that addi left).

## TU boundary audit (tools/tu_audit.py, main 935a1487, 2026-11-08)
- `python3 tools/tu_audit.py --claims claims.txt` (after ninja) writes docs/tu_boundary_audit.md: MERGE (private .rodata/.sdata2 literals, jump tables, static fns used by >1 TU => one original TU; "smallest merge" per near-miss fn), SPLIT (TU data clusters line up with a function cut), OWN (unowned data used by one TU), SINIT, CC (prologue style vs mw_version; currently clean). `validate` re-finds the tobj/cobj/lobj/texpdag merges, RaceHud split and RankPanel rodata. (Superseded 2026-11-09 18:47Z: a merge that takes the Matching flag from some TUs is no longer held back or discounted. Land it when main.dol is OK and the count of 100% functions rises, matching_rules section 2 rule 5; clFlowCourse itself was merged in 5d5f466.) OWN rows are the cheapest wins.

- (mid-range 2026-11-08, 5154888 DNFlash Spawn) Target walks a const table with a real pointer (`addi rP, rBase, 0x414; lfs 0(rP); lfsu 4(rP); lfs 4(rP)`) and `addi r4, rBase, 0x408; lfsx` while ours folds everything to `lfs 0x414(rBase)`: the tables are separate objects in a pooled .rodata that another TU owns (splits: which TU's .rodata covers the label). Merge the function into the owner TU and index the real objects (`lbl_X[i]`, not a struct overlay or a pointer param of an inline). A struct overlay of the same bytes always folds the offsets.

- (mid-range 2026-11-08, 590a109 MinimapHud::UpdateMarkers 85->97.6) Target keeps float locals in stack slots across calls (`stfs f0,0xc(r1)` at init, `lfs ..(r1)` after calls) while ours keeps them in FPRs: pass them to the inline helper as POINTERS (`void F(T *h, float *px, float *pz)` + `F(this, &px, &pz)`). Reference params (`float &px`) get scalar-replaced like plain locals; pointer params keep the address-taken slots.

## Long straight-line copy runs: the scheduler works in 26-statement regions (asm->C (A), 2026-11-08)
In a long run of `dst->x = src->x;` copies (lwz/stw pipelined as "lwz; lwz; stw; lwz; stw ..."),
MWCC (GC/2.6 here) restarts scheduling every 26 statements, so the pipeline breaks
(`stw; stw; lwz; lwz`) at fixed statement counts, not at fields. If the break lands
on the wrong word, change how many statements cover the words: e.g. a pair copy plus
two word copies replaced by one 16-byte struct copy moved the break to the right
place (PlayStats_CopyStatsBlock 98.64 -> 100, 4493f6f8). Count the target's
pipeline breaks and make each run exactly 26 statements.

## Automation helpers (2026-11-08, "Find automatable steps" thread)
- `bash tools/helpers/land.sh [--queue ID] [--dry-run] [--clean]`: run with your change COMMITTED. Fetch + rebase on origin/main, build, check ninja rc AND `main.dol: OK`, print totals + per-changed-TU function %, push to main (retry; re-rebase on races), `queue.py done ID`. On SHA failure it runs extab_renumber on changed TUs and prints the first differing DOL bytes. It does not touch claims: close your issue yourself.
- `python3 tools/extab_renumber.py src/game/Foo.cpp [--write]` (main 1a1b08d): fixes the `@N -> @etb_/@eti_` keys of one TU after literals/decls shift the numbers. `--all-changed` checks every TU changed vs origin/main. RISKY = an old @N now names a .sdata2 literal (broke main.dol in b853d71). Only --write TUs you hold the claim for.
- `python3 -I tools/helpers/flipcheck.py [--claims titles.txt] [--try]`: NonMatching TUs whose functions are all 100% (skips TUs with inline asm); --try flips each in configure.py, builds, reports, reverts. Also prints `queue.py done` commands for open queue items already at 100%. First run flipped fn_801046C4 (5f96fe9).
- main 7858633 (PR #2906, merged 2026-11-08): ninja tracks tools/extab_user_renames.json / extab_order.json (per-TU slices, restat) and the postprocess scripts. The `rm -rf build/GNLJ82/src` clean step is no longer needed; the first build after pulling rebuilds everything once.

### u8 clamp temp coloring (asm-A, GXChannel_PushChannelColors 0815728c)
If the target clamps into a temp and then `clrlwi`s into the value (`li r0,0xff / srawi r0 / andc r0 / clrlwi r6,r0,24`), write
`int val; ... val = (x > 0xFF ? 0xFF : x < 0 ? 0 : x) & 0xFF;`. A `u8 val` gives the same instructions but recolors the whole function, and `val &= 0xFF` as its own statement puts the clamp straight into val.
For `a.r = a.g = val` chains, the store evaluated first (the rightmost) reuses the early-loaded index register and the rest reload it: pick the chain order to match.

### TU owns .data with a vtable it can't emit (asm-A, clMiyoshiCardCreate, wip/asm-a/miyoshi_tick_data_1insn.patch)
When a switch jump table sits after other .data objects that belong to the TU (tables, typeinfo, vtable), define them all as plain C data in address order before the function, and add the `.data` split. The compiler's own switch table (`@N`) then lands right after them. A vtable the compiler won't emit (undefined key function) can be defined as `void *__vt__11Class[] = {...}` and referenced by its mangled name. The same goes for dtor slots (`__dt__11ClassFv`). The existing extab_user_renames entries map both to the target names. .data came out 100% on the first try.

## KartPreview ctor (autopipe3, 2026-11-08): signs of a real C++ ctor in an "asm + manual extab" fn
- Early return whose `mr r3,this` is hoisted ABOVE the test (`mr r3,r28; ...; lwz r0,..; cmpwi; blt epilog; cmpwi; blt body; b epilog`, test value in r0 not r3) = a real C++ ctor with `if (a < 0 || a >= N) return;`. An extern "C" function returning `p` never hoists it.
- EH actions `0x0A80001A MemoryManager_TimedFree` + `0x8680001C dtor_X` per allocation = `m = new T(...)` inside a ctor whose base has an out-of-line dtor. Model it like PreviewModel.c: `struct Base { void *vptr; Base() { vptr = lbl_base_vt; } ~Base(); };` (rename `__dt__4BaseFv` -> dtor_X), derived ctor stores its own vptr, `#pragma cplusplus on` + `extern "C" {}` around the TU's C functions, map `__nw__FUl`/`__dl__FPv`/`__ct__...` and the new `@N` extab/extabindex in tools/extab_user_renames.json, delete the manual extab. This took fn_8013CC24 from 59 diff lines to 4 (wip/kartpreview_ctor/).
- In C++ mode, TU-owned `const` objects referenced from other TUs need an `extern const ...;` declaration first (const = internal linkage in C++), or the link fails with undefined lbl_.

### Open pattern: "first access folded, rest through a materialized pointer" (asm-A, 2026-11-08)
DIAGNOSED (mid, 11-08): this is a compiler-local static object reached via the section anchor. See docs/regalloc_patterns.md §13. The fix is to own the pooled section and define real `static const` locals; pointer arithmetic on an extern pool can never produce it.
Seen in at least 4 near-misses: CSPartsHolders fn_8014D038 (rot=base+0xEF4: x via 0xef4(base), y/z via r3),
PCBCheck_RecvLinkData (addi r27,base,0x204; addi r27,r27,0x2c), EffectVfx29_30_Item4SubFlame_Tick
(&keys[i] in r4, keys[i] off r3), KartFx_BoostExhaustRayTick (struct copy `KartFx_BoostExhaustRayTick_data_8041A280[1] = resources->colors`:
first 3 words off r31, last 3 off r3=r31+0x534). Our MWCC always folds every access into displacements.
Not fixed by: pragmas (opt_* / peephole / scheduling / optimization_level), GC/1.0..2.7, auto_inline,
copy/assign ctors on the element type, separate pointer variables. If you crack it, it likely fixes all four.
- (autopipe3, CoinSystem_UpdateAll asm->C) Write float constants as LITERALS (`360.0f`), not as `extern const float lbl_806D7428`: the extern form changes FPR coloring and load order everywhere (140 -> 34 diff lines on a 0xC9C fn). Score drafts with sda21 names normalized: postprocess_sdata2 only maps literals to the right lbl_ once the instruction offsets line up, so raw diffs show wrong names until then. A TU whose switch table sits in a shared .data blob needs `.data start:<table> end:<table+4n>` in splits.txt.

- (R4 11-08, 5eeda5b) Switch compare-tree branch direction: for `cmpwi x,1; beq case1; blt L; b L`
  where ours has `bge` in place of `blt`, the case set is wrong, not the layout. `case 0: break;` gives
  bge; empty cases on the upper side (`case 2: case 3: break;`) give blt with identical code size.

## mwcc-debugger: why a register went where it did (2026-11-09)
`python3 tools/mwccdbg_install.py` once, then `python3 tools/mwccdbg.py <unit> <fn>` (about 10 s, one run at a time: fixed gdb port).
It dumps MWCC's AST / per-pass PCode / colouring order (GC/1.3.2 code is debugged with GC/2.6: identical output checked on dtor_801F8214) and lists, in colouring order, the virtual registers whose register differs from the target, with the first one marked. Colouring goes from the highest vreg number down and picks the lowest free register, so the fix is about vreg NUMBERING (creation order in the backend), not decl order of inlined locals (renamed to @NN temps). Dumps: build/mwccdbg/out/<fn>/.

## leversweep: today's hand levers as triggered rewrites (11-09)

- `python3 tools/leversweep.py fn UNIT FN --show` tries every lever whose trigger fits the objdiff
  diagnosis; `batch --min 90` runs all near misses (174 fns in about 4 minutes); `selftest` replays
  three past landings; `summary` rewrites `docs/sweeps/leversweep/summary.md`.
- Levers work per scope: the function body and every TU inline it calls (3 levels deep).
- Result of the first batch: 1 match (PCBCheck_ProcessLinks, dead-def-split, a5a84ae), about 30
  line-count improvements, of which only 8 raise objdiff %. Fewer diff lines often LOWERS objdiff %.
- Added 19:50: `mul-fuse` (§39, both directions: products through an inline mul helper, or helpers /
  single-use product locals written back so they fuse, plus fp_contract on/off) and `local-array-init`
  (5eca6fc, both directions; only tables defined in the TU, extern tables would need their values).
  Batch over 169 near misses: 0 matches, 1 small objdiff gain (ExplosionTumble_Init).
- Added 21:20: lever `single-expr` (0b362350; local assigned once and read once -> one expression,
  also inside TU inlines) and `leversweep.py detect` (regalloc_patterns 40, detect only): lists near
  misses whose target forms `addi rX, anchor, N` for an N our build never forms, in
  `docs/sweeps/leversweep/anchor_detect.md`. Full rerun after the TU merges (169 fns): 0 matches;
  TaMode_Init 99.63 -> 99.66 landed.
- Not automated (need a decision a regex cannot make): rolled loop + unroll budget (which loop),
  base vtable store in the ctor body, avoiding IRO CSE temps, pool-owner TU merges.
- Do not run bare `python3 configure.py`: it regenerates build.ninja with the compiler download
  rule (blocked host). Use `--binutils build/binutils --compilers build/compilers --wrapper build/tools/wibo`.

### tools/merge_tus.py: merging a run of over-split C TUs (2026-11-09, race voice unit)
- `python3 tools/merge_tus.py plan --first ADDR --last ADDR` lists the TUs and flag differences; `apply` writes one source (each TU preprocessed with its own flags, identifiers suffixed `_pN`), and rewrites splits.txt, configure.py, extab_user_renames.json and extab_order.json; `prune-renames` after the first ninja. The docstring has the details.
- merge_tus.py lessons from the Sci2Card 23-TU merge (11-09): (1) the merged Object line needs `extab_padding=b""`, otherwise the extab postprocess never runs and the `_pN` renames are not applied; (2) `prune-renames` must be given an object built BEFORE the renames took effect (it is now safe to run twice); (3) `--pool file.c --pool-sec .rodata:START:END` puts a data2c pool at the top, then fix the object boundaries by hand: every `addi rX,anchor,N` in the target is an object start (§40), so split the data2c blobs there and add the symbols to symbols.txt; (4) tables the functions use with a real type must be defined with that type in the pool (drop the per-section typedef/extern), casts through `&lbl` compile differently; (5) inline asm bodies and each TU's own `#pragma` lines survive the merge now.
- merge_tus.py and C++ (test-menu merge, 11-09): `.c` and `.cpp` TUs can be mixed; each section is wrapped in `#pragma cplusplus on/off`, declarations inside `extern "C" { }` count as top-level, C++ keywords are never suffixed. `--pool-global` keeps data2c's scope instead of making every pool object `static`: use it when most functions name ONE pool object (`lis/addi sym`, must stay a global) and only a few use the anchor; then make just the anchored objects `static` by hand (CardCreate_Page). data2c lists the externs the pool needs on stderr: prepend `void f();` / `extern char lbl[];` lines. A merge does not have to cover the whole original TU: units that own no data section can stay split and reference the pool by extern (13 of 36 merged). Classes with mangled members are not handled (the `_pN` suffix would change the mangled names).
- merge_tus.py, fn_801B7EF8 merge (11-09, 18 units, C/C++ with classes): (1) exceptions / lmw / -O4,s of each section now come from the TU's real compile command, because a lib group can set `-Cpp_exceptions on` for every unit (missing this gave `new` without the exception-safe saved register and dropped extab entries); (2) `prune-renames` also maps mangled names whose class names got the `_pN` suffix (`__ct__16CourseSprite_p17Fiii` -> the TU's old rename of `__ct__12CourseSpriteFiii`), so run it after the first ninja and build again; (3) a .bss pool shared by sections goes at the top, unsuffixed, inside `#pragma cplusplus on` + `extern "C" { }`: a C TU lays .bss out in first-use order, C++ in definition order; sections that declared the objects with their own types get `#define name_pN ((T **)name)`.
- Inline-wrapper lever seen three times in `Sci2Card_BuildRetryReceiptLine`: when the target keeps call results in the "wrong" saved registers or does not coalesce a copy, wrap the call (or a two-arm `if` returning a pointer) in a `static inline` returning the value; the inline result is a frontend temp numbered differently from named locals (414 -> 114 -> 4 diff lines). The last 4 lines (address of the scratch buffer created before the destination address) went away by writing 25 unrolled byte stores as `for (i = 0; i < 25; i++) buf[i] = 'A'; buf[i] = 0;`.
- The 53 race voice TUs (0x801A1798..0x801B70EC) are now `game/sprite/fn_801A1798.c`. The merged text is preprocessed output: tidy a section only when you work on it, and keep the `_pN` suffix on names that differ between sections.
- After a merge, read the target's `addi rX,anchor,N` offsets to find the real object boundaries of the pool (regalloc_patterns 40) before touching the functions. tools/data2c.py emits the pool objects (now also `.string16` and mixed word/relocation objects).
- Editing symbols.txt triggers a full resplit (more than 2 minutes): run ninja with a long timeout.
- Rebase conflicts in the two extab json files are per-TU keys: take origin/main and re-apply only your TU's key.
- regfix model (11-09 late): three more allocator rules, all local dumps (276) now
  reproduce. (a) r31 reserved as frame pointer (it shows up as a neighbour) = 28
  free GPRs, not 29 (fn_801E4AF4). (b) a function that spills is coloured twice;
  the dumps now hold the LAST pass, and spill temporaries of that pass are never
  the stuck-simplify pick (`regalloc-*-meta.txt`, fn_8018B31C). (c) inline asm that
  names machine registers retains them: fewer free registers, detected from spill
  costs being present (THPDec fn_80299D58). Old dumps: delete
  `build/mwccdbg/out/FN` or rerun diag to regenerate.

### tools/reloc_only_detect.py: near misses that differ only in relocations (11-09)
- `python3 tools/reloc_only_detect.py [--min 90] [--md docs/sweeps/reloc_only.md]` compares our object with the target per function (instruction words with the relocated bits masked). A hit has identical code and only a relocation symbol/addend differs: split the pool symbol in symbols.txt at the listed offsets (6cbe52d8) or fix pool ownership. After 6cbe52d8 the whole project has 0 such functions; rerun after symbols.txt or pool changes.
- §43 (`new T(...)` written as Alloc + ctor call) has no candidate left among the >= 80% near misses (scan of `x = Alloc(..); if (x) ...` in near-miss bodies: CardCreate_Page only, and its diff is the .data anchor, see gave_up). No leversweep lever added.
- leversweep lever `block-local-counter` (regalloc_patterns 46, 11-09): wraps the later loops of a shared function-level counter in `{ int i; for (...) }` (plus per-loop variants and "first counter declared last"). Batch over the >= 85% near misses: fires on 2 functions only (fn_8018E538, fn_8018B31C), 0 matches. fn_8018E538 gets every register (24 -> 4 lines) but objdiff drops to 96.4 because the `li r29,0; mr r31,r29` IV-init copy is still missing (same finding as the gave_up row).
- `python3 tools/fmt_args_detect.py [--all] [--md docs/sweeps/fmt_args.md]` (rule debug-format-arg-count, regalloc_patterns 49): compares the `%` conversions of each varargs call's format string (read from the DOL through the literal, `lbl_X`, or `pool + 0xNN`) with the arguments passed. 11-09: 0 mismatches inside near-miss functions; `--all` lists 26 in matched code (mostly calls whose first `%` string is not the format, plus `"%s retry %d"` with one argument in FileLoader_LoadBin/Open, harmless there).
- fn_801C9288 merged into game/clFlowRound.c (11-09, Matching): a near miss that sits right before its data owner's TU is worth retrying after the owner's compiler/flags were corrected. On GC/1.3.2 as its own TU it was 91.3% and the 11-08 merge draft 89.7%; inside the TU on its real flags (GC/2.6, -inline deferred, defined ahead of Draw under `#pragma defer_codegen off`) the same source gave 96.8%, and the rest was a declaration-order sweep of the three case-block locals (`int anim; param; pos;`, assigned pos, param, anim) plus `opt_common_subs off` for the reloaded offset constant. The callers in the TU kept calling it (no auto-inline).

- merge_tus.py `--suffix-base N` + `--pool-external` (11-09): extend an already merged TU. Run `apply` on the
  new range into a scratch unit with the same pool file, then append its sections to the merged file, join the two
  splits.txt blocks and the two entries in extab_user_renames.json / extab_order.json, drop the scratch Object line,
  build, `prune-renames`, build. Pool tables indexed as `table[i].field` need the real element type at the
  definition (hoist the section's struct above the pool); `(*(T (*)[])&lbl)[i]` over a `void *[]` definition
  gives `addi r0,r3,0 / slwi r3,r4,3` instead of `addi r3,r3,0 / slwi r0,r0,3`.
- Unreferenced string literals in the target's .rodata (debug format strings between two referenced objects): put them in a never-called `static` function at the right source position. MWCC emits the function and its strings, mwld strips the function; keep the strings with an `"@N": "active:lbl_XXXXXXXX"` rename (tools/postprocess_extab_user.py sets the force_active flag in .comment; `scope:global`/`force_active` in symbols.txt gets rewritten away by dtk). `"#align4": ".rodata"` in the same rename block pins a section to 4-byte alignment. Example: src/game/EnmyFaceEffect.cpp.
- Vtable sits between two functions' switch tables in .data (not at the end of the TU's .data): the TU was built with `-inline deferred -RTTI on`, where each vtable/RTTI name is emitted with the class's key function. Reverse the function order in the source (deferred emits last-defined first). Example: src/game/EnmyFaceEffect.cpp (clEFacePoly vtable, jump tables, clEFacePolyEffect vtable). Rule `deferred-vtable-key-function-order`.
- A unit whose functions are all 100% but which cannot be flipped: compare exception tables per function with the split object (`objdump -t/-r` on `build/GNLJ82/obj/UNIT.o` vs `build/GNLJ82/src/UNIT.o`, entry size per function). Smaller entries on our side mean missing actions: DELETEPOINTER = the site is a real `new T(args)` (declare a small class whose ctor is renamed to the init function), DESTROYBASE = the class has a base with a dtor, DESTROYLOCAL with no dtor call in the code = the local's class has an empty inline dtor (`ResCtrl` / dtor_80082960); the PC range of that action gives the block scope of the local. A weak dtor whose table entry sits first in the target goes into tools/extab_order.json. Worked example: src/game/DbgMenu.cpp.
- Flip fails with main.dol LONGER than the target: a weak inline copy (`__dt__...` in `objdump -t`, flag `w`) has no rename to the address of the shared copy, so mwld keeps it as a new function. Rename it in tools/extab_user_renames.json (template arguments change the mangled length, e.g. `__dt__21VHolder<10FlowFaderI>Fv`). Flip fails with main.dol SHORTER: an unreferenced object was stripped; a file-scope `const` array is internal in C++ (write `extern const`) and needs `#pragma force_active on/reset`. Examples: DNLensflare.cpp, FAllDisp.cpp (11-09).
- float literals, not `extern const float lbl_806Dxxxx` (FlashFadeOverlay_Draw 99.65 -> 100, 11-09): a constant read
  through an extern is a memory load the optimizer cannot treat as a constant, so its vreg is created and coloured
  differently (14 FPR operand rows here). tools/postprocess_sdata2.py renames the anonymous literal symbols to the
  target's `lbl_` names, so literals need no .sdata2 split. With literals the natural shape matched:
  `u0 = k * (16.0f - u); pu = k * (16.0f + u); u1 = 1.0f - pu;` (a named product local stops the fnmsubs fusion).
- tools/float_literal_sweep.py (11-09): blanket `extern float` -> literal over 56 near misses: 1 better
  (KartMovement_Init 782 -> 739), 0 matches, most slightly worse, because those bodies were shaped around the extern
  loads (named `one`/`scale` locals, split statements). The literal is a precondition, not the fix: on
  FlashFadeOverlay_Draw the plain swap changed nothing (44 diff lines), the match came from rewriting the block in
  its natural form afterwards (statement groups in 6 orders x named/unnamed product, scored with objdiff).
  Use `float_literal_sweep.py UNIT FN` to get the literal text, then reshape by hand. Table: docs/sweeps/float_literal.md.
- `python3 -I tools/flagsweep.py [flags]` recompiles every NonMatching unit with extra compiler flags and lists functions that get closer. 11-09 run with `-inline deferred` over 126 units: no function improves (most get worse), so the EnmyFaceEffect gain (fn_8022D9E4 99.81 -> 100) needs the full recipe (deferred + reversed function order + real classes), not the flag alone. Try other flags (`-use_lmw_stmw on`, `-RTTI on`, `-opt ...`) with the same tool.
- merge_tus append pitfalls (last test-menu pages, 11-10): (1) never run `prune-renames` before the merged file compiles: it
  prunes against the stale object and drops every new rename (rebuild them from `nm` + `merge_tus.unsuffix_mangled`, chaining
  through the unsuffixed entry, e.g. `__ct__15ServiceMenu_p34Fi` -> `ServiceMenu_Init`); (2) `__declspec(weak)` gets suffixed
  (`weak_p27`): strip it; (3) a section that switches to `#pragma cplusplus off` half way needs `struct T_pN` in the pool casts.
- The containers in the game are the real Metrowerks MSL C++ (`std::deque`, `Metrowerks::cdeque`, `std::vector`, `std::length_error`); the genuine CW GC 2.5 headers compiled with GC/2.6 reproduce them exactly (7 stuck deque functions at once). Do not hand-write them: `python3 tools/fetch_msl.py`, name mapping and instantiation-order rules in `docs/notes/msl_cpp.md`.
- KartMovement_RotateByYaw 100% (11-10), matrix/vector inline shapes worth porting to other kartmove near misses:
  (1) vector transform: copy the input first and store straight into the vector, one expression per component with the
  translation on the left, `float x = v->x, y = v->y, z = v->z; v->x = m->m[3][0] + (z*m->m[2][0] + (m->m[0][0]*x + y*m->m[1][0]));`
  (named `rx/ry/rz` accumulators with `+=` statements gave 26 FPR vregs off; matrix loads are CSE'd over two inlined
  calls, so every numbering detail shows); (2) Identity = 2-D zero loop + `a->m[0][0] = a->m[1][1] = a->m[2][2] = a->m[3][3] = 1.0f;`;
  (3) Multiply with `Matrix44 product; float *out = (float *)product.m; int j; int index; int i; float value;` and
  `out[index+j] = value` / `index += 4`; (4) `float c, s;` declared before `double radians`; (5) the member update
  (`k->yaw += angle`) before the first inline call.
- leversweep lever `chain-assign-split` (11-10): `a = b = c = K;` as separate statements in both orders. Fired on 7 near
  misses, 2 small gains, 0 matches.
- fn_8019A9BC 98.11 -> 100 (11-10), FPR-only diff with more live floats than volatile registers. Read the target's
  saved registers as "coloured last = lowest number": (1) float literals (constants become shared temps);
  (2) statements whose loads/constants sit in LOW volatile registers were created LATE: `QuatMatrix(&rotation, &q)`
  moved above the block that saves `position` and zeroes the translation (189 -> 104); (3) the nine quaternion
  products are declared in the classic order `xx yy zz xy xz yz wx wy wz` (the fmuls order in the asm is the
  scheduler's, not the source's; the saved/volatile split gives the decl order) (104 -> 43); (4) the value in the
  LAST saved register (`w`, f25) is a function-level named local, not an inline local: `float c = (float)cos(..); q.w = c;`
  in the caller (43 -> 0).
- Empty counted loop that the target keeps (`li r0,12; mtctr; bdnz` with no body, fn_8019C6B4): write it counting DOWN,
  `for (int i = 12; i > 0; i--) {}` (or `i != 12`, `while (n--)`). The `i < 12; i++` form is deleted by IRO, the others
  survive to the backend, which turns them into the bare ctr loop.
- PCBComm_Process 95.8 -> 99.22 (11-10), recipes: (1) `li rX,1; mulli rX,rX,SIZE` (a constant index that was not
  folded) = the statement sits in a one-trip loop whose counter feeds the index with an offset:
  `for (n = 0; n < 1; n++) f(base, n + 1);` (`g[n]` alone folds; `n - 1` gives `li 0; mulli`); (2) `add rP,base,off;
  lwzu rV,FIELD(rP)` = a pointer local that is reassigned to the field address (`sel = base + off; sel = (T *)&sel->field;`),
  a fresh `T **p = &sel->field` folds into `lwzx`; (3) `addi rB,anchor,OBJ; addi r0,off,FIELD; lhzx` = the field offset
  written before the index: `(u8 *)obj + FIELD + i * sizeof(T)`; `obj + (off + FIELD)` folds FIELD into the anchor offset;
  (4) saved registers of locals that live in two blocks: declare them once at function top, before the first
  initialised local (`update`), in the order of the target's registers (r30 first). Tool: scratch `opd.py`-style scoring
  (diff with registers masked) finds the instruction shape first; objdiff score only after the shape is right.
- `leversweep.py fn|batch --pairs N` (11-10, regalloc_patterns 62): after the single-lever pass, 3-way merges the best N
  variants per lever that changed the diff with those of every other lever (non-overlapping edits only) and scores the
  pairs. Results of the 99.x run: docs/sweeps/leversweep_pairs/.
- leversweep lever `void-to-int` (11-10, regalloc_patterns 66): `void f()` -> `int f()` / `unsigned char f()` with no
  return statement (TU prototypes rewritten; a header prototype makes the variant fail, change the header by hand).
  Run over every 99.x near miss + gave_up row with a void definition: 63 void functions fired, 0 better; 17 could not be tested because a header declares them.
- leversweep `--pairs 3` over the 99.x set + gave_up rows (11-10): 134 functions, 514 pair variants, 0 matches; 4
  functions had a pair as their best asm-line score, none of them a better objdiff percentage. Table:
  docs/sweeps/leversweep_pairs/summary.md.

- ExplosionTumble_Init 94.86 -> 97.91 (11-10): the fn_8019A9BC recipe transfers to other kart-movement
  TUs (cos in the caller as a named local, classic product order, NormalizeCopy reading y and x before
  the struct copy). Naming the quaternion components as locals `x, z, y, w` in the matrix inline gave
  the last few points; the tail's saved FPR order (w=f29 in the target) did not move with any
  declaration order.
- PCBComm_Process 99.22 -> 99.31 (11-10): read the target's saved-register sharing to get the colouring
  order (here `off` shares r24 with `accepted`, whose 0 value is dead inside the accept block, so
  `accepted` was coloured before `off`), then move declarations until mwtrace COLOR lines show that
  order. A walking pointer declared as a block local after the other block locals went last as wanted.
  Open: a frontend CSE temp cannot be numbered below a named local with any lever known so far.
- PCBComm_Process 99.31 -> 99.95 (11-10): three small recipes.
  (a) A CSE temp that must colour after a named local: make it a named block local declared right
  after that local, and write every use so that nothing folds: `(u8 *)&arr[0].field + off` gives
  `addi r0,base; add rX,r0,off` + displacement, `(u8 *)arr + K + off` gives `addi r4,base; addi r0,off,K; lhzx`.
  (b) r4/r5 swapped between an address temp and a value used three times: drop the value's named
  local and repeat the expression (the CSE temp colours before the address temp).
  (c) `addi r4,base; mr r3,r4; add r4,r4,n` for memcpy(dst, base + n): `src = base; dst = src; src += n;`.
- `-inline deferred` string order (JointTracks / MapAnim.cpp, 11-10): a `static inline` helper pools its string
  literals where the CALLER is generated; a plain `static` helper that deferred auto-inlining swallows pools them
  at its own source position (it is still compiled; mwld strips the unused copy). Line numbers that DEscend with
  the address (0x1ED, 0x1B1, 0x18E, 0x164) are the sign of a deferred TU: reverse the source order and put the
  helpers between the functions. A TU without `-rostr` puts literals in .data, not .rodata.
- ExplosionTumble_Init 97.91 -> 98.90 (11-10): count asm diff lines, not the objdiff percent, while
  hunting registers: the NormalizeCopy form that makes both expansions register-exact LOWERED the
  percent (97.18) until the other blocks were fixed too. Frontend CSE temps of repeated loads
  (`up.x`, `v.y`, ...) are numbered by STATEMENT order, so permute the statements of a cross product
  (6 orders) before anything else; result locals are propagated and do nothing. Values that overflow
  the volatile FPRs go to saved registers lowest-first, so "w in f29" means w is coloured first of the
  overflowers: an inline return value plus direct `q->x` reads did it.

- 11-10 clNormal3D_SetScale 100: three saved values (table r31, count r30, loop cursor r27) where the cursor
  must OPEN a new saved register. An inline local (frontend temp) is always coloured before the caller's named
  locals, so the cursor took the freed r30. Fix: write the inline's loop out in the function and declare its
  locals as named locals `node; i; table; count; cursor;` (last declared = lowest vreg = coloured last).
  Sweep all declaration orders (120 here, 2 gave 0 diff lines). leversweep inline-to-named-locals could not
  do it (all variants failed to compile in this `.c` + `#pragma cplusplus` TU), so try by hand when it reports compile_fail.

- 11-10 leversweep `inline-to-named-locals` now has a `deep` mode (nested block locals and `for (int i` of the inline
  become named locals; first k at the function front, the rest right before the expanded code, all orders) and no
  longer renames struct members. It reproduces the clNormal3D_SetScale match by itself. Batch over 106 near misses:
  0 matches, clNormal3D_Exec 130 -> 94 lines (by hand 78, 99.47). Hill-climbing the declaration order of ALL
  inline locals written out was worse than writing out only the inline the diag points at.
  Sweep pitfall: check that the variant compiled (grep FAILED), a stale .o gives a constant score.
- 11-10 `tools/oob_read_detect.py` (regalloc_patterns 90 detector): lists .text relocations `symbol+addend` in our
  objects whose addend is past the symbol's size in symbols.txt (a struct/array view laid over a neighbour).
  First run on all near misses: only fn_801A6538, and those were symbols.txt splitting 8-byte OSTime objects and a
  6-byte struct into halves (merged; objdiff % unchanged because it resolves by address). So §90 has no further
  candidates among today's near misses; rerun after new asm -> C conversions (`--md docs/sweeps/oob_read.md`).

## shapediag: what kind of diff is it, when it is not register-only (2026-11-10)

`python3 tools/regfix.py diag UNIT FN` used to stop with "not a register-only
diff". It now prints the output of `tools/shapediag.py` at that point, so one
command gives hints for any near miss. Standalone:

    python3 tools/shapediag.py fn UNIT FN [-v] [--src ALT_SOURCE] [--ours OBJ]
    python3 tools/shapediag.py batch --md docs/reports/shapediag_census.md
    python3 tools/shapediag.py classes | selftest | replay

It needs no compiler model: objdump of both objects, alignment with register
names abstracted, then every differing run is put in a class (about 40:
`order:args`, `order:const`, `order:store`, `order:load`, `order:expr`,
`order:loopstep`, `order:epilogue`, `order:regswap`, `copy:target-extra`,
`copy:direction`, `load:target-reloads`, `address:pool`, `saved-regs`,
`select:*`, `loop:ctr`, `call:inline`, `reloc:symbol`, `stack:offset`, ...)
and each class prints the levers that fixed it before, with the
regalloc_patterns / matching_rules section. `--src FILE` compiles a variant
with the unit's command, so you can ask "what kind of diff does this rewrite
leave" without touching the tree.

- Read the classes top down: structural ones (saved registers, calls, loops,
  pools) are printed first because they usually cause the others.
- `opcode counts, target minus ours` in the header is the quick sign
  (`lfs+3` = a second load set, section 87; `mr+1` = a kept copy, section 76).
- Relocations are compared by where they point (name, or position in the
  object's own section), so an anchor / `@N` on our side is not a diff. A
  `reloc:symbol` row that names a `jumptable_*` for a float load means stale
  `@N` renames in tools/extab_user_renames.json (found and fixed for
  clFlowCourse.cpp this way).
- It is a clue, not a rewriter, and big shuffled blocks (below about 95%)
  produce noise after the first two or three classes.
- New pattern: add a lever line (or a detector) to `CLASSES` in the tool and a
  case to `SELFTESTS` / `REPLAY`; update docs/regfix_coverage.md.
- Census of all current non-matching functions: docs/reports/shapediag_census.md.

### shapediag replay over every recorded fix (2026-11-10)

`python3 tools/shapediag_replay.py run` takes every landed fix that has a
commit (tools/patterns/hits.jsonl + the Codex table in regalloc_patterns.md,
263 cases), extracts the tree just before the fix, compiles the TU with that
tree's own command and asks shapediag what the diff was. `report` rates it
against `EXPECT` (rule -> classes that carry that lever). Result in
docs/reports/shapediag_replay.md, rows in docs/sweeps/shapediag/replay.jsonl:
228 of 263 reproduce; 89 of those are register-only (regfix territory), 139
differ in the instruction sequence. Rated: 82 hit, 4 miss, 15 colouring levers
where shapediag showed another (real, but secondary) class, 3 structural
levers invisible in the code (pool/data merges). The Codex notes were used to
add about 25 lever lines to the classes (inline helper per operand, literal
vs extern for reloaded constants, full switch case domain, `== 1` vs `> 0`).
When a new fix lands with a hits.jsonl row, rerun `run` (restartable) and
check that its row is a hit; if not, add the lever to the class it fired.
Needs history: `git fetch --shallow-since=2026-10-24 origin main`; the
trees take about 10 GB with `--keep`.
