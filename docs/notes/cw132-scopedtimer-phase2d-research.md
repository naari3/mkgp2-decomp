# ScopedTimer subi/lwz scheduler pair: SOLVED via one-expression dtor tail (2026-06-11, batch_research_scopedtimer_phase2d)

## Verdict

- SOLVED in plain C, no inline asm, no helper tricks. CarObject_FrameUpdate
  0x8004DECC promoted asm_fn -> C in `src/game/auto_ONKARTHIT_block.c`,
  full-dol SHA-1 OK.
- The lever: the elapsed-ticks -> microseconds computation must reach the
  int-to-float conversion as ONE expression tree, with NO named integer temp
  anywhere inside it. A float temp for the final ms value is harmless.

## Observations (facts; GC/1.3.2 production flags `-O4,p -inline auto` etc.)

1. Target survey (`build/GNLJ82/asm`, 150 `subi rX, rY, 0x217d` insns over 60 fns):
   the dominant context (113 sites) is the canonical inlined-dtor block
   `lis 0x8000; lis 0x431c; lwz 0xf8; lis 0x4330; subi -0x217d; lwz start; srwi; stw cookie`.
   The target binary ALSO contains the inverse order: 0x8008C468 (CardTask
   area) has `lwz r7,0x8(r1)` BEFORE the subi. That site has no
   Profiler_RecordFrame and no id slot (elapsed-ms compare via fcmpo) -> both
   orders are reachable by the original compiler; the order is
   context-dependent, not a CW-version artifact.
2. Probe matrix (tools/compiler_probe/sct_min.c / sct_cpp.c / sct_more.c,
   results_sct_axis1/2.tsv; classifier = subi-vs-nearest-r1-lwz order):
   - p0 direct two-statement (us temp) ........................ miss (lwz first)
   - p1 static inline dtor helper, Tm* param .................. miss (byte-identical to p0)
   - p2 helper by-value (start,id) ............................ miss
   - p3 helper w/ diff+us split ............................... miss
   - p4 helper w/ named denominator temp ...................... order flips but block destroyed
     (denominator hoisted ABOVE the OSGetTick call; not usable)
   - p5 helper-in-helper (ElapsedUs nested) ................... miss
   - p6 ctor+dtor both helpers ................................ miss
   - p7 TRUE one-expression (whole conversion nested in the
     Profiler_RecordFrame argument; volatile-id struct) ....... TARGET, full block
     byte-matches CarObject_FrameUpdate incl. late `lwz r3,0xc(r1)` id load
   - p8 same but `float ms` temp then call .................... TARGET
   - q0 real C++ class, dtor with `unsigned int us` temp ...... miss (exceptions on AND off)
   - q1 real C++ class, one-expression dtor ................... TARGET (exceptions on AND off)
   - r0 `end = OSGetTick();` then one-expression rest ......... miss
   - r1 canonical out-of-line dtor shape (this-based loads,
     one-expression) .......................................... TARGET (`subi` before `lwz r7,0x0(r31)`,
     target register family r6/r7/r4, mulhwu r0,r6,r4)
   - r2 `diff = OSGetTick() - tm.start;` then one-expression .. miss
   - r3 us-temp control ....................................... miss
3. The static-inline-helper axis (Phase 2c transfer hypothesis) is NEGATIVE for
   this flavor: inliner splicing alone does not change the pair order; helper
   and direct spellings compile byte-identically here.
4. C vs C++ front end is irrelevant: C p7 == C++ q1, C p0 == C++ q0.
   `-Cpp_exceptions on/off` is irrelevant in both.
5. cam-in-r3 / title-tracker idiom spelling matters in the same fn:
   `void *t; t = lbl_806D10A0; if (t != lbl_806D10A0) {} else if (t == 0) t = 0;`
   with `(unsigned int)t` cast only at the call site folds to the target
   `lwz; cmplwi; bne; li 0` shape. Casting the loads instead
   (`t = (unsigned int)lbl...; if (t != (unsigned int)lbl...)`) un-folds it into
   `cmplw r0,r0; mr r3,r0; bne; cmplwi; bne` (+3 insns / +0xC .text shift).
   Plain implicit `unsigned int t = lbl_806D10A0` (the 97% handoff appendix
   spelling) is a hard ERROR in CW 1.3.2 C ("illegal implicit conversion"),
   not a warning. (probe: tools/compiler_probe/sct_cam_idiom.c)
6. In-TU application: only the dtor tail spelling and the void*-t idiom were
   needed on top of the 97% handoff appendix C; extern retypes are TU-internal,
   no configure.py / splits.txt / symbols.txt changes. postprocess_sdata2
   renamed the @N conversion cookie to lbl_806D27D0 once offsets aligned, as
   documented in the FrameUpdate handoff.

## Hypotheses (inference, kept separate)

- Mechanism: a named integer temp splits the computation into two expression
  trees; the code generator then emits the start-reload (numerator operand) in
  an earlier tree position, and the scheduler keeps the load first (its normal
  load-latency-first tie-break). When the whole conversion is one tree, CW
  generates the division-magic materialization (`lis+subi`) ahead of the start
  reload in pre-schedule order and the scheduler preserves that. Not verified
  at IR level; consistent with all 16 probes.
- The lwz-first target site 0x8008C468 was likely hand-written timing code
  whose source naturally used an integer temp (it compares elapsed ms). The
  113 subi-first sites are all inlined copies of the ScopedTimer dtor whose
  original body was one-expression, i.e. close to
  `Profiler_RecordFrame(m_slot, (float)(((OSGetTick() - m_start) * 8) /
  ((*(unsigned int*)0x800000F8 / 4) / 125000)) / lbl_806D27C8);`
  This matches the "natural dtor probes" inference in
  cpp-scoped-timer-pattern.md once the endTick temp is removed (see the
  Phase 2d addendum there).

## Recipe (program-wide: ~30 pending callers + canonical dtor cleanup)

1. ScopedTimer ctor: local struct `{ unsigned int start; volatile unsigned int id; }`,
   `tm.id = ID; tm.start = OSGetTick();` (volatile-id memory forcing, unchanged
   from the FrameUpdate 97% handoff).
2. ScopedTimer dtor tail: SINGLE expression, no integer temp:

   ```c
   Profiler_RecordFrame(
       tm.id,
       (float)(((OSGetTick() - tm.start) * 8) /
               ((*(unsigned int *)0x800000F8 / 4) / 125000)) /
           lbl_806D27C8);
   ```

   Do NOT introduce `us` / `diff` / `end` temps. A `float ms` temp is OK if a
   caller needs it.
3. `lbl_806D27C8` extern as `const float`; the 2^52 cookie needs no extern
   (postprocess_sdata2 renames the anonymous @N once .text offsets align).
4. Candidates: 60 target fns contain the magic subi; 113 sites are the
   canonical dtor block (multi-site fns incl. BootDispatcher x9,
   DrawManager_GetOrCreate x18, RenderObj_ItemStateMachine x18). CarObject_Init
   0x8004E618 (same TU, block at sp+0x10/0x14) is the nearest sibling; not
   promoted this batch (0x7BC asm body = a full matching job beyond the
   research budget), recipe applies as-is.
5. Canonical `__dt__11ScopedTimerFv` (game/FlowDispatcher_ScopedTimer.c): the
   raw opword shim is now replaceable in principle (probe r1 hits with the
   exact register family). Needs its own batch: that matched TU also pins
   stack layout / extab; verify nothing else regresses.

## Files

- tools/compiler_probe/sct_min.c (p0-p8), sct_cpp.c (q0/q1), sct_more.c (r0-r3),
  sct_cam_idiom.c (idiom spellings)
- tools/compiler_probe/run_sct_axis1.py (driver + classifier),
  results_sct_axis1.tsv / results_sct_axis2.tsv
- src/game/auto_ONKARTHIT_block.c: CarObject_FrameUpdate now C (commit 31b54fa)
