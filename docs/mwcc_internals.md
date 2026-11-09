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
7. **Post-RA scheduler** `scheduleinstructions(TRUE)`: only blocks NOT already
   scheduled in step 4, so in practice the prologue/epilogue and blocks created
   later. The order of ordinary code is decided once, before registers exist.

## Vreg numbering

`allocate_local_vregs` hands out virtual registers in this order: objects of
exception regions, then **arguments**, then **named locals** (in the order of
the function's `locals` list), then `open_fe_temp_registers()` marks the start
of temps, then **frontend temps** (`@N`, inline temporaries), then backend
temps as PCode is generated. mwccdbg's `variables.txt` and regalloc dumps show
the numbers.

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

- `python3 tools/mwccdbg.py UNIT FN [--trace]` dumps the PCode after each
  pass and the colouring; `--trace` (GC/2.6 stand-in) also records, inside the
  real compiler, the scheduler DAG and every pick (`sched.json`) and every move
  the coalescer saw (`coalesce.json`) via tools/mwccdbg_trace.py.
- `python3 tools/mwsched.py explain UNIT FN [--run]`: for each pair of
  instructions in the other order than the target, the dependence chain or the
  pick key (critical / uncovering / height / rank / order / not ready / unit
  busy) that decided it. `log` prints the DAG and every pick; `coalesce` lists
  every move with its outcome (phys / temp / named roots).
- `python3 tools/regfix.py diag|probe UNIT FN`: register-only near misses.

GC/2.6 breakpoint addresses used by the tracer: scheduleblock 0x507D80 (DAG
ready 0x507E34, pick 0x507E9B), coalescenodes move check 0x57BB83,
colorinstructions 0x508610, simplifygraph 0x5089B0, colorgraph 0x508890.
