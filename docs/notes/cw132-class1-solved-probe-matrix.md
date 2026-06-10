# HANDOFF: class-1 hard-block final probe (Phase 0, batch_research_class1_phase0)

Date: 2026-06-11. Budget used: ~45 min of 75.

## VERDICT: SOLVED

The class-1 branch-over-branch bool materialization is NOT a compiler-variant or
pragma issue. It is a plain C source form that all prior probes missed: an
if/else with the **arms in swapped order driven by an explicit `== 0` compare**.

### Recipe (byte-identical on GC/1.3.2 with exact TU flags)

```c
u8 b;
if ((d->flags & 0x80ULL) == 0) {
    b = 0;
} else {
    b = 1;
}
if (b == 1) {
    return 0;
}
```

or equivalently the ternary form (also TARGET, and on more compiler versions):

```c
u8 b = ((d->flags & 0x80ULL) == 0) ? 0 : 1;
```

Both emit, under the unmodified TU baseline
(GC/1.3.2, `-O4,p -Cpp_exceptions on -use_lmw_stmw on` + cflags_base, no pragmas):

```
li   r4, 0x0          # mask hi
lwz  r0, 0x10(r3)
lwz  r5, 0x14(r3)
li   r3, 0x80         # mask lo
and  r0, r0, r4
and  r3, r5, r3
xor  r3, r3, r4
xor  r0, r0, r4
or.  r0, r3, r0
bne  L1               # 40 82 00 08
b    L2               # 48 00 00 08  <- empty fallthrough arm
L1:
li   r4, 0x1          # 38 80 00 01
L2:
clrlwi r0, r4, 24     # 54 80 06 3E
cmplwi r0, 0x1
bne  ...
```

Instruction-for-instruction AND register-for-register identical to the real
KartItem_OnKartHit site at 0x8004A284..0x8004A2A4 (verified against
src/game/auto_ONKARTHIT_block.c lines 1573-1589), including the r4 reuse
(bool coalesced with the zero mask-hi register) and the encodings.

### Why every prior form failed (observed + mechanism hypothesis)

- Observation: CW preserves *source arm order* for `if ((x & m) == 0) ... else ...`
  but canonicalizes `!`-negated conditions (probeF `!(x & m)` with identical arm
  order still inverts). All ~26 prior forms had the "b = 1" arm reached by
  fallthrough (or used `!`/`!=`), so the branch folder collapsed
  `bcond L1; b L2; L1:` into the 1-insn-shorter invert.
- Mechanism hypothesis (consistent with all observations, not proven): with
  then=0 / else=1 order, codegen emits a full diamond
  `bne L1; li rD,0; b L2; L1: li rD,1; L2:`. Branch folding cannot collapse a
  diamond with two non-empty arms. Later, register coalescing/cleanup removes
  the redundant `li rD,0` (rD shares the register that already holds the u64
  mask hi word = 0), leaving the "wasteful" `bne L1; b L2; L1:` pair intact
  because the folding pass has already run.
- Corollary for Phase 1: the deletion of the `li 0` arm likely depends on the
  bool register coalescing with an existing zero (here the mask-hi `li r4,0`).
  All 19 sites in the TU follow the u64-flag-test pattern, so the same zero
  register should be available at every site; verify per site.

## Probe matrix (all results)

Harness: `tmp_probe/probe.py` (compile standalone tmp_min.c with exact TU
flags, `dtk elf disasm`, classify the 5-line pattern). Classifications:
TARGET = `bne L1; b L2; L1: li rX,1; L2:` (non-invert, wanted)
invert = `beq L2; li rX,1; L2:`
branchless = subic/subfe
other = anything else (e.g. full diamond with explicit li 0, or isel)

Probe source forms (tmp_probe/tmp_min.c), all on `(d->flags & 0x80ULL)` with
flags at struct offset 0x10 (same as real site):

| form | source | result @ GC/1.3.2 base |
|---|---|---|
| A | `if (f&m) b=1; else b=0;` | invert |
| B | `b = (f&m) ? 1 : 0;` | invert |
| C | `b=0; if (f&m) goto set; goto done; set: b=1; done:` | invert |
| D | `b = (f&m) != 0;` | branchless |
| E | `if ((f&m)==0) b=0; else b=1;` | **TARGET** |
| F | `if (!(f&m)) b=0; else b=1;` | invert |
| G | `b=1; if ((f&m)==0) b=0;` | other (full diamond, andi-based) |
| H | `b = ((f&m)==0) ? 0 : 1;` | **TARGET** |

### Axis 1: compiler variants x baseline flags (tmp_probe/results_axis1.tsv)

Local mwcceppc.exe inventory (build/compilers, size / sha1 first 12):

| variant | size | sha1-12 | E | H | notes |
|---|---|---|---|---|---|
| GC/1.0 | 1438208 | 1880894d2706 | other | TARGET | |
| GC/1.1 | 1653760 | c662dc222d90 | other | TARGET | |
| GC/1.1p1 | 1653760 | 73dc1588d7fb | other | TARGET | new rev, no behavior delta vs 1.1 here |
| GC/1.2.5 | 1651200 | 03187e49c58c | other | TARGET | |
| GC/1.2.5n | 1651200 | ef0480e9b4a4 | other | TARGET | |
| GC/1.3 | 2053120 | b18d7887262e | TARGET | TARGET | |
| GC/1.3.2 | 2058752 | d8f9c36d62f6 | TARGET | TARGET | TU baseline (banner: "Version 2.4.2 build 81", May 7 2002) |
| GC/1.3.2r | 2058752 | 7acceb12b91f | TARGET | TARGET | Cuyler rodata-pooling patch of 1.3.2 |
| GC/2.0 | 2064896 | ef148743ee72 | TARGET | TARGET | |
| GC/2.0p1 | 2064896 | 74bc177b10d1 | TARGET | TARGET | |
| GC/2.5 | 2066944 | 539c0b31d515 | TARGET | TARGET | |
| GC/2.6 | 2066432 | 1110a7a9924a | TARGET | TARGET | |
| GC/2.7 | 2068992 | 100dd3a2898a | TARGET | TARGET | |
| GC/3.0a3..3.0a5.2 (7 builds) | ~3.0-3.1M | (see tsv) | branchless | branchless | 3.0 collapses E/H to subfe |
| Wii/* (9 builds) | - | - | branchless | branchless | same as 3.0 |

Pre-discovery negative (forms A-D only): ALL 29 compilers produced
invert/branchless/other, zero TARGET. Compiler patch revision is NOT the
differentiator; 1.1p1 / 1.3 / 1.3.2r / 2.0p1 / 3.0a* / Wii* now probed and
recorded (closes the "patch rev" unknown in 14.2).

### Axis 2: pragma sweep on GC/1.3.2 x forms A-D (tmp_probe/results_axis2.tsv)

Full pragma enumeration extracted from the 1.3.2 binary string table is below.
62 prelude rows probed; ALL negative for the target shape on forms A-D. Notable
non-invert outcomes (still not TARGET):

- `global_optimizer off`: probeA becomes full diamond `beq; li 1; b; li 0` (explicit li 0, no coalesce)
- `optimization_level 0|1`: same full diamond; probeC STILL inverts (the
  bne/b/L1 fold happens even at level 0 -> folding is not a disableable opt)
- `gen_isel on`: emits isel (not valid for gekko)
- everything else (peephole off, scheduling off, all opt_* off, combos):
  identical to baseline invert.

Negative axes closed: peephole/scheduling/global_optimizer/opt_* pragmas,
optimization_level pragma 0-4, codegen pragmas (ppc_opt_bclr_bcctr, gen_fsel,
defer_codegen, optimizewithasm, disable_registers, profile, ibm_stackframe,
no_register_save_helpers, switch_tables, prepare_compress, gprfloatcopy,
block_assign, has8bytebitfields, optEH/optEH2, misaligned_mem_access,
side_effects, etc.).

### Axis 3: -opt suboptions

SKIPPED (solved before reaching it). -opt suboption space documented below for
reference; no evidence it is needed.

## Reference: CW 1.3.2 option/pragma space (for future probes)

-opt suboptions (from `-help all`, file tmp_probe/help_132_all.txt):
`off|none, on, all|full, [no]space, [no]speed, level=0..4, [no]cse|[no]commonsubs,
[no]deadcode, [no]deadstore, [no]lifetimes, [no]loop[invariants], [no]prop[agation],
[no]strength, [no]dead, [no]peep[hole], display|dump`

PPC codegen flags: `-common, -fp_contract|-maf, -func_align, -pool[data],
-profile, -rostr, -schedule on|off, -use_lmw_stmw, -vector`

Pragmas (extracted from binary string table; optimizer/codegen-relevant subset):
`opt_common_subs, opt_loop_invariants, opt_propagation, opt_unroll_loops,
opt_lifetimes, opt_strength_reduction, opt_strength_reduction_strict,
opt_dead_code, opt_dead_assignments, opt_vectorize_loops, opt_pointer_analysis,
peephole, global_optimizer, optimization_level, optimize_for_size, scheduling,
defer_codegen, inline_bottom_up, auto_inline, dont_inline, always_inline,
inline_depth, inline_max_size, inline_max_total_size, gen_fsel, gen_isel,
ppc_opt_bclr_bcctr, bc_range, switch_tables, prepare_compress, gprfloatcopy,
disable_registers, profile, ibm_stackframe, no_register_save_helpers,
use_lmw_stmw, optimizewithasm, pool_data, fp_contract, optEH, optEH2,
suppress_init_code, side_effects, block_assign, has8bytebitfields,
explicit_zero_data, readonly_strings, misaligned_mem_access,
unsafe_global_reg_vars, ignore_global_reg_vars, longlong_prepeval,
float_constants, experimental, ppc_unroll_speculative,
ppc_unroll_instructions_limit, ppc_unroll_factor_limit, opt_unroll_count,
opt_unroll_instr_count, opt_pointer_analysis_mode, processor, function_align`
(plus front-end/warning pragmas; full dump reproducible via
`tmp_probe` python snippet over the exe string table)

## Action items for Phase 1 (class-1 salvage)

1. Update docs/per_fn_matching_strategy.md 14.2 KartItem_OnKartHit row:
   class 1 SOLVED via `== 0` arm-order form; record probeE/probeH recipes and
   that compiler rev / pragmas are ruled out (negatives above).
2. Apply recipe to the 19 sites / 9 fns (OnKartHit x7, CarObject_OnItemHit,
   ApplyImpactReflect, ApplyImpactImpulse, KartItem_Tick, KartItem_PerFrameStep,
   UpdateCoinSpeedBonus, UpdateShadowBillboardAndViewport,
   KartItem_TickStatusEffectsByFlag x7). Prefer the if/else probeE form;
   probeH (ternary) as fallback. Where the bool feeds `if (b == 1)`-style
   compares the surrounding cmplwi/bne also matches as shown above.
3. Watch the coalesce precondition: target keeps NO `li rD,0`; the rD must be
   the register already holding the u64 mask hi zero. If a site's mask hi is
   nonzero, re-derive (no such site seen yet).

## Files

- tmp_probe/tmp_min.c        : 8 probe forms (A-H)
- tmp_probe/probe.py         : compile+disasm+classify harness
- tmp_probe/run_axis1.py     : compiler sweep (results_axis1.tsv, post-discovery run incl. E-H)
- tmp_probe/run_axis2.py     : pragma sweep (results_axis2.tsv, forms A-D, all negative)
- tmp_probe/help_132_all.txt : full `-help all` dump of GC/1.3.2

## sub_summary

```json
{
  "verdict": "solved",
  "recipe": "u8 b; if ((flags & MASKULL) == 0) { b = 0; } else { b = 1; } -- explicit ==0 compare with then-arm=0 / else-arm=1; ternary ((f&m)==0)?0:1 equivalent. Plain GC/1.3.2 -O4,p TU baseline, no pragma/flag changes needed. Byte-identical incl. register allocation vs real OnKartHit site.",
  "key_negative": "compiler patch revs (1.1p1/1.3/1.3.2r/2.0p1/3.0a*/Wii*) and all 62 pragma preludes on 1.3.2 do NOT produce the shape for the previously-tried forms; the differentiator is source arm order + explicit ==0 (CW canonicalizes ! but preserves ==0 arm order)",
  "probes": 91,
  "next": "Phase 1 go: apply recipe to 19 sites / 9 fns; update 14.2"
}
```
