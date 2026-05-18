# CW 1.3.2 duplicate-literal equality dead block idiom

Observed in `KartMovement_CanReceiveItem` (0x8003F5E8, batch_text_8003f5e8_kartmovement_can, 2026-05-18).

## Pattern

Target asm:

```
    cmpwi r0, -0x1
    bne   .L1
    li    r3, 0
    blr
.L1:
    bne   .L2          ; cr0 still from cmpwi r0,-1 -> always taken
    li    r3, 0        ; DEAD
    blr                ; DEAD
.L2:
    cmpwi r0, 0x17
    ...
```

3-instruction dead block (12 bytes) sits between two `bne` branches that share the same cr0 from a single `cmpwi`. The second `bne` is unconditional in practice because the preceding fall-through implies the value was not equal to the literal.

Ghidra decompiler removes this as "unreachable block (ram,0x...)".

## C source idiom that reproduces it

```c
if (state == -1) return 0;
if (state == -1) return 0;     // duplicate literal guard
if (state == 0x17) return 0;
if (state == 0x1c) return 0;
```

CW 1.3.2 dedups the `cmpwi` (cr0 is still live from the first compare) but does NOT prune the unreachable `li 0; blr` body — it emits both the `bne` and the dead return.

## Discovery heuristic

When target asm shows two consecutive `bne L; li 0; blr; L: bne L2; li 0; blr; L2:` sharing one `cmpwi`, the C source likely contains two literal `if (x == K)` checks against the SAME constant K. Write them verbatim instead of dedup'ing in C.

Sibling idiom for C++ scoped objects: `if (this) if (this)` (§14.3, deleting-destructor offset-0 subobject). The present idiom extends the pattern to integer equality literals.

## Suggested catalog placement

Add as new row to docs/per_fn_matching_strategy.md §10.6 (bundle promote idioms) or §14.3 (successful idioms). The pattern is reusable for any sub-agent encountering a 12-byte dead block after a literal-equality compare.
