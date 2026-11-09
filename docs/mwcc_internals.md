# MWCC internals: where the compiler decides registers and order

When a near miss is "same instructions, different registers" or "same
instructions, different order", the answer is in the compiler's backend, and
we have its source. Read this page, then read the source; do not guess.

## The source

[doldecomp/mweppc](https://github.com/doldecomp/mweppc) is a CC0 (public
domain) C decompilation of `mwcceppc.exe` GC/2.0, 2.0p2, 2.5, 2.6 and 2.7,
proven equivalent function by function. `sh tools/install_mweppc.sh` puts it in
`build/mweppc` at a pinned commit (`tools/cloud_setup.sh` runs it). Version
differences are `#if VERSION ...` blocks; we mostly use GC/2.6 (our GC/1.3.2
units are close but not covered: the debugger maps 1.3..2.7 to 2.6).

`tools/install_mweppc.sh --build` (cloud_setup.sh runs it) also builds native
Linux compilers `build/mweppc/build/GC_{2_0,2_5,2_6,2_7}/native/mwcceppc`
(needs archive.org for the MSL runtime; the project's cloud environment allows
it). Checked 2026-11-09: byte-identical code for all 415 of our GC/2.0-2.7
units against the original exe under wibo (16 objects differ only in the 2
extab padding bytes decomp-toolkit fixes). Same command-line flags, no wibo,
and the source can be patched to print any decision (frontend included).

## Where to look (paths under build/mweppc/src/compiler/)

| Question | File : function |
| --- | --- |
| Order of backend passes | backend/CodeGen.c : the function around `scheduleinstructions(FALSE)` (~line 1450-1540) |
| Which vreg number a variable gets | backend/CodeGen.c : `allocate_local_vregs`; backend/Registers.c : `assign_register_to_variable`; backend/RegisterInfo.c : `open_fe_temp_registers` |
| Interference (who is live together) | backend/InterferenceGraph.c : `buildinterferencematrix` |
| Copy coalescing (`mr`/`fmr` deleted or kept) | backend/InterferenceGraph.c : `coalescenodes` |
| Simplify / spill choice / colouring | backend/Coloring.c : `simplifygraph`, `colorgraph`; backend/SpillCode.c : `estimatespillcosts` |
| Volatile / saved register order | backend/Registers.c : `volatile_registers`, `obtain_nonvolatile_register`; backend/RegisterInfo.c (`init_target_registers`) |
| Instruction scheduler | backend/Scheduler.c : `scheduleblock`, `selectinstruction`, `findsuccessors` |
| Latencies and units (Gekko = 750 model) | backend/MachineSimulation750.c : `instruction_timing`, `can_issue` |
| Opcode rank (scheduler tiebreak), flags | backend/OpcodeInfo.c : `opcodeinfo` |
| May two memory accesses alias | optimizer/Alias.c : `gather_alias_info`, `may_alias_alias`, `make_distinct_virtual_alias` |
| `__restrict` / pointer-to-const params | backend/CodeGen.c : `move_assigned_argument`; optimizer/Alias.c : `make_distinct_virtual_alias` |
| Peephole (`mr` -> `addi`, merges) | backend/Peephole.c |
| Backend CSE / copy / add propagation, loop opts | optimizer/ValueNumbering.c, CopyPropagation.c, AddPropagation.c, LoopOptimization.c, StrengthReduction.c |
| Frontend (IR) optimiser: CSE temps, induction vars, unrolling | optimizer/Iro*.c (IroCSE.c, IroLoop.c, IroUnrollLoop.c, IroLinearForm.c) |

## Backend pass order (GC/2.6, -O4)

1. Frontend IR optimisation (CSE temps `@N`, range splitting, unrolling).
2. PCode generation; argument copies `mr vreg, r3..` at the entry.
3. `globallyoptimizepcode`: backend CSE, copy/add propagation, loop code motion
   and strength reduction (these are the `after-*` dumps of mwccdbg).
4. `peepholemergeblocks`, then the **pre-RA scheduler** `scheduleinstructions(FALSE)`
   (only when scheduling is on; skips prologue/epilogue blocks). It marks every
   block it scheduled.
5. `peepholeoptimizeforward`, then **register colouring** per class (GPR, FPR):
   liveness, dead code removal, interference, **coalescing**, simplify, colour;
   spill and repeat if needed.
6. Post-colouring value numbering, frame sizes, prologue/epilogue, peephole.
7. **Post-RA scheduler** `scheduleinstructions(TRUE)`: every block whose
   `fScheduled` flag is clear. `deletepcode`, `insertpcodebefore` and
   `insertpcodeafter` (PCode.c) clear it, so besides the prologue/epilogue any
   block that lost a coalesced `mr`, got spill code or was changed by peephole
   is scheduled AGAIN, now with real registers (no opcode-rank key, and WAR/WAW
   on machine registers). Only blocks left untouched since step 4 keep their
   pre-RA order. Example: the fn_801D7610 epilogue `lwz r30`/`lwz r0` order.
   The SBLOCK lines of mwtrace say which pass scheduled each block.

## Vreg numbering

`allocate_local_vregs` hands out virtual registers in this order: objects of
exception regions, then **arguments**, then **named locals** (in the order of
the function's `locals` list), then `open_fe_temp_registers()` marks the start
of temps, then **frontend temps** (`@N`, inline temporaries), then backend
temps as PCode is generated. The `locals` list is built by prepending, so
frontend temps come out in REVERSE creation order: the last `@N` created gets
the lowest number (RankingMgr_UpdatePositions: `@99` r34, `@98` r35, `@94`
r36, ...). `python3 tools/mwtrace.py UNIT FN --only VREG` prints the list.

The full order, lowest number first (GC/2.6, `allocate_local_vregs`, then
codegen):

1. objects of exception regions;
2. arguments;
3. named locals, in REVERSE declaration order (the last declared local gets
   the lowest number: NameCheck_CardName `j` r33, `i` r34, ... `base` r37);
4. frontend `@temps`, in REVERSE creation order;
5. "toc" objects: a section anchor or address used more than once
   (`...rodata.0`);
6. backend temps, in code generation order (statement order, and within a
   statement the order `InstrSelection.c` evaluates operands);
7. registers created by the backend loop optimiser (CTR counters, strength
   reduced IVs, hoisted `lis`).

Backend CSE (`ValueNumbering.c`, per extended basic block) creates no
registers: a CSE'd value keeps the number of its first computation.

Why the number matters: simplify pushes low-degree vregs in ascending order
and colouring pops them in reverse, so among values live at the same time the
HIGHER number is coloured FIRST and gets the lower volatile register, or `r31`
when it needs a saved one.

### Who made each @temp (`mwtrace.py --only TEMPNEW,VREG`)

`TEMPNEW @N caller= outer=` names the compiler function that created each
temp (labels also use `@N` names; ignore `newlabel`/`statement` rows):

| creator | what it is |
| --- | --- |
| `IRO_CommonSubs` | frontend CSE of a repeated expression (a repeated load, `x % 2`, ...) |
| `SplitOffRange` | a named local with several independent live ranges, split into temps |
| `CInline_SetupArgsExpression` / `CInline_Expand` | inline function arguments / return value |
| `LinearizeExpr1`, `GenerateExpr1TempAssignment` | comma / `?:` / call results the IR needs in a temp |
| `IRO_FindLoops` | loop induction variables and IR loop-invariant hoists |
| `createfloatconstant` | float literals (become loads from the pool) |

A value that must be numbered AFTER some backend temp therefore must not be
any of these: it has to be computed by code generation itself, at a point
after that temp. Working example, fn_801EE36C (3cc4b0e): `previous.x` was
CSE'd by `IRO_CommonSubs` into `@140` (numbered before every backend temp)
and coloured after the `0.0125f` constant; the target colours it first. Two
changes made it a backend temp numbered after the constant: the scale is
computed before `delta`, and the second use reads `((float*)&self->previous)[0]`
so the IR optimiser no longer sees two equal loads (backend value numbering
still merges them, keeping the later first-codegen number).

Which live range of a named local keeps its name (`IRO_SplitLifetimes`,
IROUseDef.c): the local's def list is built by prepending, so it starts at the
LAST def in the function. Ranges are collected starting from the head of that
list; the first range collected and the LAST range collected keep the named
variable, every range in between becomes a `SplitOffRange` temp. With three
loops `for (mode = 0; ...)` that is: loop 3 named, loop 2 temp, loop 1 named
(the earliest range is always collected last). For loop 1 to become a temp
too, `mode` needs one more range that starts before loop 1 and survives
copy propagation and dead-store removal (TitleCheck_NewClearedRecord_Race; a
`mode = pd->b19A` used once is propagated away, used twice it changes the
code). Only DLOCALs not live across a call, not volatile and not address-taken
are split (`usedAtCall`, `noregister`).

Notes from NameCheck_ScanBannedWords (11-09, read from IROUseDef.c / Coloring.c /
InterferenceGraph.c and checked against traces):

- `FindDefsAndUses` ends with `MakeDef(var, NULL, NULL, TRUE)` for every
  variable, so the head of each def list is an ENTRY def. The first range
  collected is the one reachable from function entry (normally empty); after it
  every range is split off except the last one collected, the earliest in the
  function. A function-level `word` with 7 loops kept its name only in the first
  loop; the other 6 were `SplitOffRange` temps, created latest loop first.
  Variables are processed in order of first appearance in the IR.
- `colorgraph` takes the LOWEST-numbered free register among volatiles plus
  the saved registers already handed out (r19 before r21), and only then a new
  saved register (r31 downward). So which loop counter gets r19/r20/r21 is
  decided by when its node is coloured relative to the first allocation of
  each register. A loop counter that must take the register allocated in the
  middle needs a split temp created in that window: run the loop on the
  variable whose split temps are created there (found-block loop on `k`).
- The value of a call wrapped in a trivial `static inline` lives in an inline
  fe temp, numbered above every IRO temp, so it is coloured before FindLoops
  IV temps. `close = find_code(...)` instead of `close = strstr(...)` moved
  `close` ahead of the delimiter-pair IV with no code change.
- `named = &global` for a global outside the anchor pool and outside sdata is
  always `addi tmp; mr named,tmp` (Operands.c makes a fresh temp, and
  `coalescenodes` never merges named with temp). A target `addi rN,r3,x@l`
  straight into the register means the holder is a temp (IV or split range).
- Simplify degree counts coalesced-away vregs: a neighbour that was merged
  into another node stays in the adjacency array and is never decremented.
  Each merged copy (call-result temp, inline argument copy) that is live while
  a long-lived node is live adds 1 to that node's degree for good, which
  decides whether it falls to a later sweep (= coloured earlier).

A def range does not need a use: `IRO_SplitLifetimes` collects ranges from the
def list, so a DEAD store still forms a range if it is still there. Dead stores
are removed by `IRO_UseDef(copts.deadstore, ...)` in the loop just before the
split, so under `#pragma opt_dead_assignments off` a dead `int mode = 0;` keeps
an earliest range and loop 1 becomes a `SplitOffRange` temp
(TitleCheck_NewClearedRecord_Race: 28 -> 6 lines, tools/tracesweep/).

Open cases with the same root cause, no source shape found yet (11-09;
templates and results for each in tools/tracesweep/*.tmpl):

- clFlowCourse_Dtor: `extra` (named, or IRO CSE `@110`) must be numbered after
  the backend temps of `selected % 2`. A `?:` would give a codegen result
  register, but `gen_COND` turns `c ? 4 : 0` with a comparison condition into
  a branchless select (`TOC_use_isel`, InstrSelection.c `gen_COND`), +1 insn.
  `gen_COND`'s one-branch path (`COND_has_const` 1 or 2: exactly one arm is a
  non-zero `EINTCONST`) allocates the result register first and emits
  `li 4; cmp; bne; li 0` as in the target. With `reverse ? 4 : zero`, `zero`
  a local = 0, the whole block matches, but only under `opt_propagation off`
  (otherwise `zero` folds to 0 = case 6, `andc` select), and that pragma
  breaks both delete loops (IV pointer init not folded). Needs a zero arm that
  is not a constant after IRO.
- EffectVfx10_KartTrail_Tick: correction 11-09 (tracesweep): the anchor is
  the backend temp r44 (`addi r44, r43, ...rodata.0`), and COLOR shows r44,
  `item` (r33) and `self` (r32) coloured before every other vreg. They are
  pushed in a later simplify pass because their degree is >= K, so their order
  is decided by the remaining degree in that pass (ascending number among the
  ones that drop below K together), not by numbering alone. The target pushes
  self, anchor, then item: `item` must still have degree >= K when the pass
  visits it.
- NameCheck_CardName: the table pointers are `LinearizeExpr1` temps (`@60`,
  `@61`) and must be numbered after the `lhz` of `cursor[i]`; written directly
  in the loop, the pointer folds into the load (`add` + `lhz -31560(r3)`).
  Backend loop optimisation creates new registers only for CTR counts, the
  divisor of a non-power-of-two step, `lis` of large bounds and strength
  reduced induction pointers (LoopOptimization.c, StrengthReduction.c), not
  for a hoisted invariant (it keeps its codegen number). So `converted` can
  be "late" only as a codegen temp computed in the loop after the `lhz` that
  does not fold into the load's displacement; no such shape found yet.
  Solved in principle 11-09: with the tables declared as `static const` rodata
  objects of the TU (addressed through the section anchor), a mock TU gives
  `subi r4, r31, 0x7b48` / `lhz r5` exactly: the anchor-relative address is
  generated at its use in the loop (after the lhz) and hoisted by the backend.
  The real fix is rodata ownership: the pool at 0x80318270 (anchor + 0x10000)
  spans NameCheck_CardName, NameCheck_ScanBanned and RaceData_8009BEF4.

## Coalescing (`coalescenodes`)

Walks blocks and instructions in order. For each move `mr a,b` / `fmr a,b`
(not a side-effect move) it takes the union-find roots of `a` and `b` and:

- same root: the move is deleted;
- the roots interfere: kept;
- **both are virtual and not both temps: kept.** Only temp<->temp copies and
  copies to/from a machine register (`r3` argument or call result, ...) are
  ever merged. A copy between two named variables, or between a named variable
  and a temp, always stays as an `mr`.
- otherwise merged into the lower number; the merged node's interferences are
  ORed into the survivor. The merged node keeps its row in the matrix, so its
  neighbours still count it in their degree (regfix calls this "coalesced
  nodes never leave the graph").

A move's destination does not interfere with its source at that move
(`buildinterferencematrix`), which is what makes merging possible. A vreg used
as a load/store base interferes with `r0`.

Consequences seen in gave_up.md: "copy into a named local is not coalesced"
(RankingMgr_UpdatePositions, Card_VerifyChecksum, Sci2Card_Tick) is rule 3;
"inline temps get coalesced" is the temp<->temp case. A value that must stay in
`r3` (call result kept live) is a temp coalesced INTO machine r3: every value
live alongside it then avoids r3.

## Colouring (`simplifygraph`, `colorgraph`)

Simplify: loop over vregs in ascending number, skipping pushed and coalesced
ones; push every vreg whose remaining degree is below the number of available
registers, decrementing its neighbours; repeat until no change. If vregs are
left, spill: pick the lowest `spillCost / degree` (vregs created by spill code
are never picked), push it, and loop again. The push list is popped in reverse
(last pushed = coloured first).

Colour: for each vreg, the volatile registers (`r0, r3..r12` / `f0..f13`) not
held by an already-coloured neighbour; take the lowest. If none, take the next
saved register from the nonvolatile list (r31 downwards, shared across the
function: once handed out it is added to the volatile mask for later vregs).
`tools/regfix.py` implements exactly this and checks itself against the real
colouring on every run.

## Scheduler (`scheduleblock`, `selectinstruction`)

List scheduling, one basic block at a time, Gekko uses the 750 model: issue
width 2, one instruction per unit per cycle (LSU, FPU, IU1/IU2, SRU, BPU),
latency lfs/lwz 2, fadds/fmuls/fmadds 3, stores 2.

DAG (built bottom-up): register true dependences get the producer's latency;
WAR and WAW edges get latency 0 for GPR/FPR (the 750 renames registers) but
still order the two; memory edges load->later store and store->later
load/store are added only where `may_alias` says the two can alias; calls,
side-effect and serialising instructions order against everything.
`height` = longest latency path to the end of the block, `latest` =
critical path - height.

Each cycle, up to 2 picks. Candidates are ready nodes (no unscheduled preds,
`earliest <= cycle`, unit free), walked in the block's ORIGINAL order. The
first is the incumbent; a later candidate replaces it if, in this order:

1. it is critical (`latest <= cycle`) and the incumbent is not (a non-critical
   candidate is never weighed against a critical incumbent);
2. it **uncovers** more nodes: successors whose only remaining pred it is;
3. it is higher;
4. (pre-RA only) its opcode rank is lower (stores 1, ALU/FPU 2, loads 3);
5. otherwise the earlier instruction stays.

So statement order is only the last tiebreak. To move an instruction, change
the DAG: add or remove a dependence (a shared variable gives a WAR edge, a
memory edge disappears with `__restrict`/const), or change what it uncovers.

### Post-RA scheduling: which blocks are scheduled twice

`scheduleinstructions(TRUE)` (after colouring, prologue/epilogue and the final
`peepholemergeblocks(TRUE)`) schedules every block with more than 2
instructions whose `fScheduled` flag is clear. `deletepcode`,
`insertpcodebefore` and `insertpcodeafter` clear it; `appendpcode` does not.
So a block is scheduled a second time, now with physical registers (WAR/WAW
on real registers, no opcode-rank key), when after the pre-RA pass:

- a copy in it disappeared: coalesced (`coalescenodes`) or coloured into the
  same register and deleted as `mr rX,rX` (Coloring.c, after `colorgraph`);
- regalloc removed dead code in it (`InterferenceGraph.c`) or spill code was
  inserted;
- post-colouring value numbering (`removecommonsubexpressions(func, 1)`)
  removed a redundant instruction;
- the final block merge deleted its trailing `b` to the next block.

The epilogue: `peepholemergeblocks(TRUE)` moves the restore loads
(`lwz r31..`, `lwz r0,lr`, `mtlr`) out of the epilogue block into the last
block with `appendpcode` (up to the `addi r1`, a side effect). If that last block
kept its pre-RA flag, the restores stay in generation order (`lwz r31`,
`lwz r30`, `lwz r0`); if it is re-scheduled, `lwz r0` moves up for the `mtlr`.
An epilogue that differs only in where `lwz r0` sits therefore says: in the
original, something in the last block was deleted or inserted by regalloc.

`python3 tools/mwsched.py resched UNIT FN` tests this for every block: it
recompiles with the trace build's what-if knob `MWCC_TRACE_RESCHED=<block>`
and reports blocks whose post-RA re-scheduling gives the target. On
2026-11-09, of 183 near misses at 90-99.99%, three match with the last block or all blocks re-scheduled:
fn_801D7610 and CardData_InitDefaults (last block / epilogue) and fn_80245E6C
(block B31). The source fix is then to make regalloc change that block, e.g.
with a copy that coalesces or ends up in the same register.

## Alias analysis and `__restrict`

`gather_alias_info` gives every load/store an alias: a single object, part of
an object (offset/size), or a set. `may_alias_alias`: two parts of the same
object alias only if their byte ranges overlap; anything reached through an
unknown pointer is the worst-case set and aliases everything.

A pointer **parameter** gets its own "distinct virtual" object at the entry
copy (`move_assigned_argument` -> `make_distinct_virtual_alias`) when it is
`__restrict`, or (GC/2.5+) when it points to const (non-POD classes excluded).
Accesses through it then no longer alias other memory. Example: fn_8019EB9C
(regalloc_patterns §30): with `Matrix44 *a`, every `stfs` to `out` waited for
all loads from `a`, so the final `fadds x` uncovered nothing and lost to the z
chain; `const Matrix44 *__restrict a` removes those edges.

## Tools

- `python3 tools/mwtrace.py UNIT FN [--only KINDS]`: compiles the unit with the
  native mweppc build patched with tools/mweppc_trace/trace.patch and prints
  every decision for FN: vreg numbering (VREG), each copy the coalescer saw
  (COALESCE ... same|interfere|named|merge), colouring order with neighbours
  (COLOR, plus IGNODE for every vreg incl. coalesced ones), the PCode right
  before and after register allocation (PCODE pre|post), scheduler DAG
  (SBLOCK/SNODE) and picks with their keys (SPICK). Line formats are in the
  docstring of tools/mwtrace.py. SSKIP lists blocks the scheduler skipped and
  why (already-scheduled / too-short / prolog-epilog).
  ~0.1 s, no gdb, parallel-safe; GC/1.x units use the 2.6 build (same code for
  2437 of our 2470 GC/1.3.2 units; float-heavy math units differ). The patch
  only writes the trace file; the patched compilers still give identical code
  on all our GC/2.x units.

- `python3 tools/tracesweep.py run UNIT FN TEMPLATE [--want EXPR] [--probe EXPR]`:
  a permuter over a hand-written template (choice points `{{a | b}}`, linked
  `{{name: ...}}`, decl-order permutations `{{%name: a | b | c}}`), compiled with
  the native traced compiler and ranked first by a predicate over this trace
  (`T.vreg/kind/reg/creator`, `T.vmatch(regex, post=True)` on PCode), then by
  diff lines; the top ones are re-scored with the real compiler and objdiff.
  ~0.02-0.1 s a variant on 4 cores (9k NameCheck variants in 50 s). Write the
  mechanism as `--want`, then put the idioms you suspect in the template.
  `selftest` replays landed fixes (fn_801EE36C, fn_8019EB9C).

- `python3 tools/mwccdbg.py UNIT FN [--trace]` dumps the PCode after each
  pass and the colouring; `--trace` (GC/2.6 stand-in) also records, inside the
  real compiler, the scheduler DAG and every pick (`sched.json`) and every move
  the coalescer saw (`coalesce.json`) via tools/mwccdbg_trace.py.
- `python3 tools/mwsched.py explain UNIT FN`: uses the native trace when
  build/mweppc is built (`--gdb` for the debugger dumps) and explains each
  block from the schedule that was emitted (its post-RA one if it was
  scheduled twice). For each pair of instructions in the other order than the
  target it gives the dependence chain or the pick key (critical / uncovering /
  height / rank / order / not ready / unit busy) that decided it. `log` prints
  the DAG and every pick; `coalesce` lists every move with its outcome (phys /
  temp / named roots); `resched` is the post-RA what-if above.
- `python3 tools/regfix.py diag|probe UNIT FN`: register-only near misses.

GC/2.6 breakpoint addresses used by the tracer: scheduleblock 0x507D80 (DAG
ready 0x507E34, pick 0x507E9B), coalescenodes move check 0x57BB83,
colorinstructions 0x508610, simplifygraph 0x5089B0, colorgraph 0x508890.

## GC/1.x backend (1.0 .. 1.2.5n): an older generation, not covered by mweppc

The compilers split into two generations by their source files (the
`__FILE__` strings of the asserts in each exe):

- **GC/1.0, 1.1, 1.1p1, 1.2.5, 1.2.5n**: 99 files. No `Alias.c`,
  `Arguments.c`, `InterferenceGraph.c`, `RegisterInfo.c`, `PCodeInfo.c`,
  `IroPointerAnalysis*.c`, `IroLinearForm.c`, `IroUnrollLoop.c`; `Registers.c`
  and `StackFrameEABI.c` instead. Code generation, the opcode numbering
  (`PC_STW` = 49, `PC_ADDI` = 63, ...) and the machine models (latency tables)
  are the same as 2.x.
- **GC/1.3, 1.3.2, 1.3.2r** have the same 112 files as GC/2.0..2.7, which is
  why the 2.6 stand-in fits our 1.3.2 units.

So for 1.2.5 units, Alias.c / `__restrict` / const-pointer reasoning from the
sections above does not apply. What we know of 1.2.5 (Ghidra, see
`tools/mwcc1x/README.md`; addresses in GC/1.2.5 `mwcceppc.exe`):

| 2.x name | 1.2.5 | Notes |
| --- | --- | --- |
| `scheduleinstructions` | 0x4CCAE0 | picks the machine table, schedules every block with > 2 instructions whose "scheduled" flag (block +0x2E bit 8) is clear, then sets it |
| `scheduleblock` | 0x4CCBF0 | same list scheduler as 2.x (DAG built bottom-up, appended in pick order) |
| `selectinstruction` | 0x4CCDC0 | same keys as 2.x: critical, then uncovers more, then higher, then (pre-RA only) opcode rank, then original order |
| `findsuccessors` | 0x4CCF10 | register edges via 0x4CD7C0, memory edges below, calls/side effects serialise |
| `addsuccessor` | 0x4CD910 | edge latency = producer latency, or 0 for WAR/WAW when the model renames |
| memory, pointer access | 0x4CD2F0 | see the rule below |
| memory, named object | 0x4CD4A0 / 0x4CD650 | the second one for flag 0x20000 accesses |
| `insertpcodeafter/before`, `deletepcode` | 0x49CF90 / 0x49CFD0 / 0x49D010 | clear the scheduled flag, as in 2.x |
| 604 / 750 / ... machine tables | 0x5763F8 (604, 4-issue), 0x577640 (750), 0x574D70 (default) | latency table of the 604 at 0x576418, 6 bytes per opcode, same values as MachineSimulation604.c |

Driver (0x4351C0, the CodeGen.c function that calls 0x4CCAE0 twice): the
pre-RA pass runs only when the scheduling mode byte is 2, the post-RA pass
when it is non-zero. `#pragma scheduling off` turns both off.

**Memory dependences in 1.2.5 (no alias analysis).** Every load/store is
either a *named-object* access (its displacement operand carries an Object:
a global, or a local off r1) or a *pointer* access (displacement only, flag
0x40, the 2.x `fIsPtrOp`). The scheduler keeps one list of loads and one of
stores and adds an edge when:

- pointer access vs pointer access: **always**, whatever the base register
  or offsets (two stores through `info`, through two different parameters, an
  int and a float field: all ordered);
- named object vs the same object: always (no offset/size check, so
  `G.a` and `G.b` are ordered);
- named object vs a different named object: never;
- pointer access vs named object: unless the object is a local whose
  address is never taken.

Consequence: in a 1.2.5 unit, a target that puts an independent
instruction *before* the first of two stores through the same pointer (e.g.
`addi rP; stw b,0x410(r3); ...; stw rP,0x400(r3)`) cannot come from either
scheduler pass: with the store->store edge (latency 3) the first store is
always higher than the `addi`. That block was not scheduled at all, i.e. it is
code-generation order: the unit (or a `#pragma scheduling off` region) was
compiled unscheduled. `__THPGetBit` (thp/THPDec, 80.9 -> 100 %) was exactly
this; see regalloc_patterns §33.

**Other 1.x passes seen with the debugger.** `tools/mwccdbg.py` maps 1.2.5 to
GC/1.1 (same file set, and for `__THPGetBit` the same code). Its dumps show
the 1.x pass order: initial code, copy propagation, pre-RA scheduling,
peephole-forward, register allocation, prologue/epilogue, peephole, post-RA
scheduling. Two 1.x behaviours that matter for matching:

- copy propagation removes a copy whenever it can propagate to all of its
  uses (an inline argument copy, `c = b`, a local `THPFileInfo *i = info`);
  a copy survives only if one of its uses is reached by another definition
  or comes after the source is redefined;
- peephole-forward (like 2.x `adjustforward`) sinks an in-place
  `addi rX,rX,imm` to just before the block's branch (or the next use of
  rX), and since that clears the scheduled flag the block is scheduled again
  post-RA. Writing the add out of place (`q = p + 3`, coalesced into the
  same register later) keeps it where the source put it.
