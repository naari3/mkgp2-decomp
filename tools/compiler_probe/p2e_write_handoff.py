#!/usr/bin/env python3
# One-shot HANDOFF.md writer for batch_research_phase2e (atomic write + parse check).
import os
import re
import json
import tempfile

NOTE = '''# Phase 2e research: dead-counter SOLVED (invisible-use), per-site coloring levers, mtx-loop still open (2026-06-11, batch_research_phase2e)

## Headline results
1. SOLVED: the "dead-counter-in-ctr-loop" idiom (CarObject_HandleItemEffect 0x8004F858 loop 1).
   The counter is NOT dead in the original IR - it has an INVISIBLE USE: it is passed as an
   extra (ignored) argument to the post-loop call. `ItemStateGuard_IsActive(guard, i)` under a
   K&R empty-paren extern makes the web live; regalloc coalesces i straight into r4 (the arg
   slot, vacated because itemId moved to r31), so the use costs ZERO instructions and the loop
   region becomes byte-identical (li r4,0 / addi r4,r4,1 / bdnz, no read anywhere).
2. CarObject_HandleItemEffect taken 98.62% -> 99.93% (494 insns, 7 diff rows left, all one web:
   `handled` colored r29 vs target r22). Paste-ready patch: tools/compiler_probe/p2e_handleitemeffect_9993.patch.
3. REFUTED (correction to cw132-dead-counter-ctr-loop-hardblock.md): the class is NOT a hard
   block, and "solving the counter cascade-fixes the lane-clear site permutations" is false -
   the counter was fixed and the 84 permutation rows persisted until separately solved (below).
4. CORRECTION to cw132-mrsrinit-phase2c-research.md hypothesis: post-splice optimization DOES
   include iterative DCE (probes g1/g2: a dead counter added to the exact CalcMaxSpeed helper
   whose `mr` init survives is deleted, both dead-in-callee and live-in-callee/dead-at-site).
   Only copy/const FOLDING is FE-only. So no spliced web can survive by being dead; every
   surviving "dead-looking" web has a real use hidden by coalescing.

## Observations (facts)
- Binary-wide mining (p2e_mine_deadctr2.py): 76 ctr loops with an up-counter never read between
  its init and the next write. Inspected cases (fn_801DCCE4, ItemAliasTable_LookupSlotIndex,
  OSCreateHeap) are all live via RETURN-VALUE coalescing: the counter is the return value on the
  hit path, allocated to r3, so the "read" is the implicit blr - zero instructions. 46 of 76
  have `mr rX,rY` inits (the MainUpdate mtx-loop family, see below).
- h3 probe (p2e_deadctr4.c): counter as ignored 2nd call arg survives; in a minimal fn it costs
  one `mr r4,r5` because the itemId param occupies r4; in the real fn (itemId saved to r31) it
  coalesces to zero instructions. All 8 previous hardblock probes plus volatile / register
  volatile / exceptions-on / big-preopt-helper / non-leaf-helper / count-param variants stay
  negative (p2e_deadctr.c / p2e_deadctr2.c).
- ONE-HOME-PER-VARIABLE: CW 1.3.2 gives a named variable a single register home across all its
  disjoint live ranges. Verified: making the boost-site owner a fn-scope variable unified all
  three sites to one color. In the target, ALL FIVE owner/obj webs across the switch (3 lane-
  clear sites + boosts at 0x17/0x141/0x142) are r29 -> the original used one fn-scope obj.
  Its r29 home is forced by interference: inside each lane-clear block, 7 block-locals + obj
  fill the whole stmw pool r22-r29, leaving obj only r29.
- Per-site decl-order coloring: lane-clear written as per-case BLOCKS (not helpers) lets each
  site take its own decl order. Direction (first-declared -> lowest vs highest) OSCILLATES per
  configuration and per site; it is cheap to read off a build and re-tune (2 iterations here).
  Decl orders that match target (with fn-scope obj declared among fn locals, any position):
    site1 (case 0xe group):  tbl, i, owner, effectState, mediaReq, cursor, itemId
    site2 (case 0xc group):  itemId, cursor, owner, effectState, mediaReq, tbl, i
    site3 (case 0x141):      itemId, cursor, owner, effectState, mediaReq, i, tbl
  (block-local `ItemStateBlock *q` declared last in each; shadowing `int itemId` in-block is fine)
- Static-inline helper copies per site (KartItem_CancelLanes_inl/2/3 with per-copy decl order)
  also work for the lane-clear bodies (84 -> 14 diff rows) but cannot give the boost-site owner
  r29; the block + fn-scope-obj form supersedes them.
- Residual (source-closed this batch): `handled` (u8, fn-scope, written in every switch arm,
  read once after) colors r29, sharing with obj (they never interfere); target has r22. Inert:
  7 fn-scope decl permutations, register keyword on handled/obj, handled=1 statement motion
  (changes schedule = worse). 7 diff rows = li/mr/clrlwi of that single web.

## mtx-multiply loop (CarObject_MainUpdate 0x8004DA44, flavor 5) - still open, mechanism narrowed
- Target loop traits: NO strength reduction on out (slwi rK,2 + stfsx for every store, out base
  r6 materialized once), k+=4 kept twice (unmerged), a-row elements CSEd into 4 regs per row
  (source row-locals), b loads folded to r1 const offsets, dead i web kept (init `mr r4,r5`).
- The same loop body appears in 14+ unmatched fns (Camera_RotateByYaw, KartMovement_RotateByYaw /
  _Init / _CollisionUpdate, TornadoEffect_ComposeRenderMatrix, ItemEffectSpin_TickWorker,
  ExplosionTumble_Update, TornadoLift_Update, ItemEffectImpact_Tick, fn_801DEF94 family x6,
  fn_8019A9BC, fn_8019C6B4, ...; see results_p2e_mine2.tsv `mr` rows) -> a shared (header-)inline
  MtxConcat-like helper; solving it unlocks all of them.
- Probe results (p2e_mtxmul*.c): every -O4/-O3 build SRs the first-row stores into a pointer IV,
  merges k+=4+4 into +8, and deletes i. -O2 produces the no-SR stfsx shape but no ctr loop.
  Helper vs standalone vs direct: same. `k = 0; for (i = k; ...)` opaque-init: no. volatile
  float *out: ignored (identical output). #pragma optimization_level 2 island: ignored by GC/1.3.2.
  Accumulator-chain spelling (f = a0*b[0]; f += a1*b[4]; ...) fixes the fmuls first-pair
  reassociation and the a-row local CSE - keep it for any retry.
- Reading (hypothesis): the target shape looks like O2-grade loop codegen finished by O4-grade
  late backend (ctr conversion, scheduling, regalloc). No source lever found under production
  flags. Untried axes for a next batch: two nested loops (4-row x 1 inside), `*(out + k)`
  per-store pointer arithmetic, unsigned/short k, and checking whether i has an invisible use of
  the h3 kind through a different call signature (r4 is occupied by &s.mA at the next call, so
  the plain extra-arg trick does not fit MainUpdate).

## Per-fn status
- CarObject_HandleItemEffect 0x8004F858: 99.93%, 7 rows (handled web color). Patch saved;
  promote NOT committed (TU must stay sha1-green). Next session: hunt the handled-r22 lever
  (scope of handled, boost-result spelling, switch-arm write forms).
- CarObject_MainUpdate 0x8004D404: parked, no in-TU attempt this batch (research only).
- KartItem_ApplyImpactReflectAndDampVelocity 0x8004B140 (priority 3) and
  CarObject_ProcessWarpAndDash 0x8004D1A8 (priority 4): NOT attempted - budget consumed by
  priorities 1-2. Note for priority 3: re-examine the chain li-0 with the invisible-use lens
  (is the 0 a variable with a hidden use - ignored call arg or return-coalesced web?) before
  any more spelling probes.

## Probe harness added (tools/compiler_probe/)
p2e_run.py (deadctr/mtx classifiers), p2e_deadctr{,2,3,4}.c, p2e_mtxmul{,2,3,4,5}.c,
p2e_mine_deadctr{,2}.py (binary-wide miners), results_p2e_*.tsv, target_mainupdate.txt,
p2e_handleitemeffect_9993.patch (apply onto src/game/auto_ONKARTHIT_block.c for retry).
'''

HARDBLOCK_APPEND = '''
## SUPERSEDED (2026-06-11, batch_research_phase2e)

This class is NOT a hard block. The counter is live via an INVISIBLE USE: in
CarObject_HandleItemEffect the loop counter is passed as an extra (ignored) argument to the
post-loop call (`ItemStateGuard_IsActive(guard, i)` with a K&R empty-paren extern); regalloc
coalesces i into the arg register (r4, vacated by the itemId->r31 save) so the use emits zero
instructions. Verified in-TU: loop region byte-identical, fn at 99.93%. Binary-wide, every
"dead" ctr-loop up-counter inspected has such a hidden use (most commonly: the counter IS the
return value on the break path, coalesced to r3/blr). The secondary cascade hypothesis (counter
web fixing the lane-clear site permutations) is REFUTED - those needed per-site decl-order
tuning + a fn-scope obj variable (see cw132-phase2e-research.md). Precan update: a ctr-loop
addi rX,rX,1 with no visible read => check whether rX is an arg slot of the next bl or the
return register on an exit path; reproduce with an ignored extra arg / returned counter, do NOT
park.
'''

MRSR_APPEND = '''
## Correction (2026-06-11, batch_research_phase2e)

The hypothesis "const-prop does not re-run on the spliced webs" must be narrowed: post-splice
optimization DOES include iterative DCE. Adding a dead up-counter to this very CalcMaxSpeed
helper gets it deleted (both dead-in-callee and live-in-callee/ignored-at-site forms; probes
p2e_deadctr3.c g1/g2) while the mr init still survives in the same build. Only copy/const
FOLDING is FE-only. Consequence: no spliced web survives by deadness; surviving "dead-looking"
webs always have a coalesced-invisible use.
'''

data = {
    "batch_id": "batch_research_phase2e",
    "sub_summary": ("P1 dead-counter SOLVED (invisible-use via ignored extra call arg; K&R extern): "
                    "HandleItemEffect 98.62->99.93 (7 rows left, handled web r29 vs r22). New levers: "
                    "one-home-per-variable (fn-scope obj forced to r29 by block-local interference), "
                    "per-site block decl-order tuning. Corrections: post-splice DCE exists (mrsrinit "
                    "note hypothesis narrowed); dead-counter hardblock note SUPERSEDED; counter-cascade "
                    "hypothesis refuted. P2 mtx loop: target = O2-shape body + O4 backend, no source "
                    "lever found, 14+ sibling fns identified. P3/P4 untouched."),
    "results": [
        {
            "addr": "0x8004F858",
            "name": "CarObject_HandleItemEffect",
            "status": "skipped",
            "src_path": None,
            "objdiff_percent": None,
            "notes": ("best 99.929% (494/494 insns, 7 diff rows, all = handled u8 web colored r29 vs "
                      "target r22). Dead counter SOLVED: ++i in loop 1 + ItemStateGuard_IsActive(guard, i) "
                      "under K&R empty-paren extern (i coalesces into r4 at the bl, zero extra "
                      "instructions). Lane-clear sites 1/2/3 + both late boost sites matched via per-case "
                      "blocks with per-site decl orders + fn-scope obj (one-home r29). Paste-ready patch: "
                      "tools/compiler_probe/p2e_handleitemeffect_9993.patch (includes extern/struct edits: "
                      "IsActive -> empty-paren; lbl_806D26F8/2704/270C/2710/2714 -> extern const float; "
                      "KartMovementSpeedView +field300 @0x300; typed forward decl). handled-color lever "
                      "not found in ~12 probes (decl perms, register kw, statement motion)."),
        },
        {
            "addr": "0x8004D404",
            "name": "CarObject_MainUpdate",
            "status": "skipped",
            "src_path": None,
            "objdiff_percent": None,
            "notes": ("research only, no in-TU attempt. mtx loop: every O4/O3 source form SRs row-1 "
                      "stores + merges k increments + DCEs i; -O2 gives the no-SR stfsx shape but no ctr; "
                      "volatile out / opt_level pragma island / opaque init all inert. Same loop in 14+ "
                      "unmatched fns (shared header-inline helper) - see docs note + results_p2e_mine2.tsv."),
        },
        {
            "addr": "0x8004B140",
            "name": "KartItem_ApplyImpactReflectAndDampVelocity",
            "status": "skipped",
            "src_path": None,
            "objdiff_percent": None,
            "notes": ("not attempted (budget). Next: re-examine the chain li-0 with the invisible-use "
                      "lens before more spelling probes."),
        },
        {
            "addr": "0x8004D1A8",
            "name": "CarObject_ProcessWarpAndDash",
            "status": "skipped",
            "src_path": None,
            "objdiff_percent": None,
            "notes": "not attempted (budget).",
        },
    ],
    "configure_py": {"add_objects": []},
    "splits_txt": {"add_entries": []},
    "symbols_txt": {"set_scope": [], "set_attr": [], "rename": []},
    "docs_notes": [
        {"path": "docs/notes/cw132-phase2e-research.md", "content": NOTE},
        {"path": "docs/notes/cw132-dead-counter-ctr-loop-hardblock.md", "content": HARDBLOCK_APPEND},
        {"path": "docs/notes/cw132-mrsrinit-phase2c-research.md", "content": MRSR_APPEND},
    ],
    "build_verified": {
        "command": "ninja build/GNLJ82/ok",
        "sha1_ok": True,
        "funcs_matched_delta": 0,
    },
    "blocked_reason": ("HandleItemEffect: 7 diff rows left, all the handled web register color "
                       "(r29 vs r22); no source lever found this batch. MainUpdate mtx loop: no source "
                       "spelling reproduces the no-SR/unmerged-k/retained-i shape under production flags."),
    "user_attention": None,
}

HEADER = '''# HANDOFF batch_research_phase2e

Phase 2e research batch. Priority 1 idiom (dead-counter-in-ctr-loop) SOLVED - the counter has an
invisible use (ignored extra call arg, coalesced to zero instructions). CarObject_HandleItemEffect
driven 98.62% -> 99.93% in-TU (7 diff rows = one register color on the `handled` web), patch saved
at tools/compiler_probe/p2e_handleitemeffect_9993.patch; TU reverted, build green (sha1 OK).
Priority 2 (mtx loop SR) mechanism narrowed but unsolved; priorities 3-4 not attempted (budget).

'''

FOOTER = '''

## Appendix: how to retry CarObject_HandleItemEffect (99.93%)

`git apply tools/compiler_probe/p2e_handleitemeffect_9993.patch` on a clean
src/game/auto_ONKARTHIT_block.c, then `ninja build/GNLJ82/src/game/auto_ONKARTHIT_block.o` and
objdiff. The patch contains all TU edits (externs, struct field, fn body). The only residue is
the `handled` web color; every other byte of the 0x7B8 fn matches, including both scan loops,
the 20-case switch, three lane-clear expansions and all three boost expansions.

Diff rows (target vs patch build): rows 70/187/249/311/401/432/469, all li/mr/clrlwi on
handled (T r22 / M r29).
'''

content = HEADER + '```json\n' + json.dumps(data, indent=2, ensure_ascii=False) + '\n```\n' + FOOTER

root = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
fd, tmp = tempfile.mkstemp(prefix='.', suffix='.tmp', dir=root)
with os.fdopen(fd, 'w', encoding='utf-8') as f:
    f.write(content)
os.replace(tmp, os.path.join(root, 'HANDOFF.md'))

m = re.search(r'```json\n(.*?)```', open(os.path.join(root, 'HANDOFF.md'), encoding='utf-8').read(), re.S)
d = json.loads(m.group(1))
print('HANDOFF.md ok:', d['batch_id'], len(d['results']), 'results,', len(d['docs_notes']), 'notes')
