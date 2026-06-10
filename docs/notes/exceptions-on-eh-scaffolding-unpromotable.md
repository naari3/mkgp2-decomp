# Precan class: -Cpp_exceptions on EH scaffolding (bl __unexpected islands) is un-promotable under approach B (2026-06-10, KartItem_Dtor 0x8004E2B0)

Observation (fact): KartItem_Dtor target asm has the full exceptions-on shape: `mr r31, r1` frame-pointer prologue, back-chain epilogue (`lwz r10, 0x0(r1); lwz r0, 0x4(r10); mr r1, r10`), and 12 dead landing-pad islands `addi r3, r31, 0xNN; bl __unexpected; L: b L`, all referenced by a 404-byte SPECIFICATION extab. `#pragma exceptions off` (approach B) suppresses every one of these, so no C source can match inside a mega-bundle that forces B (manual-extab asm_fns at lower addresses; approach A auto-emit would link its extab ahead of .extab_user and reverse the target address order, cf. per_fn_matching_strategy.md sec 14.1 mix-failure).

Precan rule: before dispatching a promote inside an asm_fn bundle, grep the target fn range for `bl __unexpected` (or `mr r31, r1` right after the callee-saved stores). A hit => skip the single-fn dispatch. Unlock paths (TU-level, not 1-fn): promote head-first in address order so a leading contiguous run can use approach A, or retrofit the bundle as .cpp with real classes + throw() specs.

Precedent: src/game/dtor_801FEA70.c deliberately kept its SPECIFICATION + __unexpected dtors as asm_fn (see its header comment). No fn containing a __unexpected island has ever been matched from C in this repo.

## auto_ONKARTHIT_block.c precan sweep (2026-06-10, main agent)

`bl __unexpected` grep over the whole TU marks 12 fns as un-promotable under the
current bundle configuration (pre-marked blocked in .orchestrator/state.json, do
not dispatch promote subs for these):

- `KartItem_Dtor` 0x8004E2B0 (12 islands, 404-byte SPECIFICATION extab)
- `dtor_8005278C` 0x8005278C, `dtor_800528B0` 0x800528B0, `dtor_8005292C` 0x8005292C,
  `dtor_800529A8` 0x800529A8 (0xB0), `dtor_80052A58` 0x80052A58, `dtor_80052AD4` 0x80052AD4,
  `dtor_80052B50` 0x80052B50, `dtor_80052BCC` 0x80052BCC, `dtor_80052C48` 0x80052C48,
  `dtor_80052CC4` 0x80052CC4, `dtor_80052D40` 0x80052D40 (tail dtor group, mostly 0x7C,
  1 island each, 40-byte SPECIFICATION extabs)

dtor-named siblings WITHOUT islands (e.g. dtor_80052200, dtor_800524CC, 8-byte
extabs) are not in this class and remain dispatchable.

## Precan rule UPDATE (2026-06-11, StlList_InsertBefore 0x80052684)

The `bl __unexpected` grep is INSUFFICIENT. StlList_InsertBefore carries the full
exceptions-on scaffolding (FP prologue `mr r31, r1`, back-chain epilogue, EH state
store `stw r1, 0x24(r31)`, dead cleanup island `bl MemoryManager_TimedFree` parked
behind an unconditional `b`) with NO `bl __unexpected` call - the cleanup handler
frees an Alloc-ed node instead of calling __unexpected.

Updated precan check (either marks the class, 0 probes):
1. `bl __unexpected` anywhere in the fn range, OR
2. FP prologue: `mr rX, r1` immediately after the callee-saved stores, paired with
   the back-chain epilogue (`lwz r10/r11, 0x0(r1)` ... `mr r1, r10/r11`).

auto_ONKARTHIT_block.c class membership grows to 13 fns: the original 12 (KartItem_Dtor
+ 11 tail dtors) + StlList_InsertBefore 0x80052684.
