# Equivalent C for asm-only functions (`NON_MATCHING`)

Decided by naari3 on 2026-11-10 (09:03Z) as an exception to "land asm -> C only
at 100 %". Reason: the PC port (naari3/mkgp2-pc, which merges this repository)
cannot use inline PowerPC asm. About 40 game functions (about 15,500
instructions) were asm-only on that day, among them CarObject_MainUpdate and
VSMode_FrameUpdate.

## The rule

A game function that is still inline asm may get a behaviourally equivalent C
or C++ version next to the asm, under `NON_MATCHING`:

```c
#ifdef NON_MATCHING
/* NON_MATCHING: equivalent C, 97.3 % (register allocation in the item loop). */
void Foo_Update(Foo *self) {
    ...
}
#else
asm void Foo_Update(Foo *self) { /* 0x80012345 size:0x1F0 */
    nofralloc
    ...
}
#endif
```

- When the C side needs types or helpers that are defined further down the
  file, wrap the asm in `#ifndef NON_MATCHING` ... `#endif` and put the C in an
  `#ifdef NON_MATCHING` block at the end of the file; a forward declaration
  `asm void Foo(void);` gets the same guard with the C prototype in the other
  arm. The check tool understands both layouts.
- The default build never defines `NON_MATCHING`: it still assembles the asm,
  main.dol stays byte-identical, the report does not change. Nothing in
  configure.py, splits.txt or symbols.txt may change for the C side.
- The C side has to compile: `python3 tools/nonmatching_check.py` builds every
  unit that has such a block with `-DNON_MATCHING` (object goes to
  `build/GNLJ82/nonmatching/`, never linked) and prints the objdiff percentage
  of each guarded function against the target. Run it before pushing; a unit
  that does not compile is a failed landing.
- "Equivalent" means: same calls in the same order with the same arguments,
  same stores, same control flow. Register choice, instruction order, stack
  layout, pooled-vs-direct addressing and the like may differ. Write it from
  the target asm, not from memory of what the function ought to do. Put the
  percentage and what is known to differ in the comment on the first line of
  the block.
- Check equivalence, not only the percentage: `python3 tools/nonmatching_audit.py
  UNIT FN` compares the call sequence, the non-stack stores and the compare
  shapes of the two versions. The check tool also lists UNKNOWN SYMBOLS:
  undefined symbols of the NON_MATCHING object that symbols.txt does not have
  (a function that was never declared and so returns `int`, a name that was
  renamed since the draft was written, a mangled ctor without a rename). Both
  must be clean or explained before pushing.
- Give callees real prototypes on the C side (guard the old `extern void
  Foo();` with `#ifdef NON_MATCHING` and put the prototype in the other arm):
  an unprototyped call passes `float` as `double`, which is only harmless on
  PowerPC.
- Write natural code: no fakematch tricks, no pragmas whose only purpose is
  the last few percent. Types and field names over raw offsets where the TU
  already has them; this code is what the port runs and what a later matching
  attempt starts from.
- A helper, type or prototype that only the C side needs goes inside the same
  `#ifdef NON_MATCHING` (or its own one), so the default compile cannot change.
- If the C++ side makes the compiler emit a mangled symbol that the binary
  has under another name (a ctor/dtor of a class view, a vtable), add the
  rename to this TU's block in `tools/extab_user_renames.json` (text edit,
  never `json.dump`). The default object does not contain these symbols, so
  the default build is unaffected; the check tool applies the renames.
- A whole-TU draft patch from `docs/wip/` can be folded in mechanically:
  apply it to a copy of the file and write `diff -D NON_MATCHING old new`
  back; every hunk becomes an `#ifndef NON_MATCHING` / `#else` / `#endif`
  block.
- The manual `.extab_user` records of the asm function stay as they are.
- When somebody later matches the function, the guard and the asm go away and
  it is an ordinary 100 % landing.

This does not change anything for functions that already are C: a
non-matching C function is still landed by the existing rules (unit goes
`NonMatching`, or it waits in `docs/wip/`), not hidden behind this guard.

## Claims and bookkeeping

- Claim the TU as usual (`[unit-claim] retrofit:<configure.py path>`), close
  the claim when the block is pushed.
- `python3 tools/nonmatching_check.py --list` prints the units and functions
  that have a C side. `tools/scan_asm_fns.py` keeps counting them as asm.
- `docs/gave_up.md` rows for these functions stay: they describe what blocks
  the 100 % match, which the guard does not solve.

## Status (2026-11-10)

All game functions that are still inline asm have a C side (33 functions, 21 units):
`python3 tools/nonmatching_check.py --list`. What remains asm-only is real
SDK/runtime asm (`src/dolphin/os`, `base`, `mtx`, `src/musyx/runtime`, `src/init`).

How each C side was checked: it compiles with the unit's own flags, links against
known symbols only (no UNKNOWN SYMBOLS), and `tools/nonmatching_audit.py UNIT FN`
shows the same sequence of calls as the target. Nothing was run. A low percentage
means a different code shape, not a known behaviour difference. Lowest ones
(`python3 tools/nonmatching_check.py` prints all): the six this-adjusting thunks
and tiny getters in auto_ONKARTHIT_block / fn_8005249C.. (0 %, plain C calls
instead of a tail branch), fn_801232E0 (7 %, table fill written as a loop),
card_save_trigger (22 %, struct copy as a loop), card_read_state_machine (60 %),
RaceContext_InitDefaults (75 %), CarObject_MainUpdate (81 %),
CardSave_Tick_CaptureAndStart (83 %), Tachometer_RenderDigits (84 %),
SoundMgr_Play (89 %); the rest are 90 % or more.

CGameCoin_Update notes: fields of CGameCoin past 0x80 are named in the local
`CGameCoinTail` view (lane, laneTarget, jump/hit timers, wheel joints); the names
are guesses from use. The three camera calls keep their current symbol names
(`CObj_LoadIntoGX(scene, &eye)`, `CObj_ApplyViewport(scene, &at)`,
`CObj_ApplyScissor(scene, &pos)` used as a position getter) although they look
like eye/interest setters and getters.
