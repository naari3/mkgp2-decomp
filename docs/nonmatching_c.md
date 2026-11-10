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
- Write natural code: no fakematch tricks, no pragmas whose only purpose is
  the last few percent. Types and field names over raw offsets where the TU
  already has them; this code is what the port runs and what a later matching
  attempt starts from.
- A helper, type or prototype that only the C side needs goes inside the same
  `#ifdef NON_MATCHING` (or its own one), so the default compile cannot change.
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
