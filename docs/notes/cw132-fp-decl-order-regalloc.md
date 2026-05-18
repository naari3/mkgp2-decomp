# CW 1.3.2 fp register allocation order tied to declaration order

Observed in KartMovement_SetPosition @ 0x8019A4A0 (batch_text_8019a4a0_kartmove_setpos).

## Rule

CW 1.3.2 with `-O4,p -fp hardware -inline auto` assigns floating-point registers (f0, f1, f2, ...) to local `float` declarators in **declaration order**, not in use-first order.

A single comma-list declarator (`float a, b, c;`) and three separate declarators (`float a; float b; float c;`) behave the same way: the LEFT-MOST / TOP-MOST identifier gets f0, the next gets f1, etc.

## Implication for matching

When the target asm uses high-numbered fp regs first (e.g. f2 for the variable accessed first in source), the temp must be declared LAST in its own group. Example:

```c
// produces f0=x, f1=y, f2=z
float x, y, z;

// produces f0=z, f1=y, f2=x   <-- matches target with x=f2
float z, y, x;
```

## Empirical evidence

KartMovement_SetPosition stores `pos->x` to offsets 0x88, 0x40 (and optionally 0x4C). Target asm:

```
lfs f2, 0x0(r4)   ; x -> f2
lfs f1, 0x4(r4)   ; y -> f1
lfs f0, 0x8(r4)   ; z -> f0
```

With `float x, y, z; x = pos->x; y = pos->y; z = pos->z;` CW produced the inverse coloring (x=f0, y=f1, z=f2), matching 97.5%. Changing the decl to `float z, y, x;` (assignments and uses unchanged) flipped the coloring to match (100%, SHA-1 OK).

## When to apply

- Vec3 / matrix copies where the target asm clearly uses fp regs in reverse decl order.
- Diff symptoms: identical instruction count and addressing, but the bottom 5 bits of the fp register field differ across all 3 floats.

Combined with strategic interleaving (e.g. deferring the last load until after the first store) this idiom can pin both regalloc and scheduler down with no other compiler-flag dance.

## Same rule for GPRs (int / pointer locals)

The decl-order coloring rule also applies to general-purpose registers (r3-r10 range), not just fp regs. Observed in `ItemSelect_AddSlotItem` @ 0x80060D80 (batch_text_80060d40_itemselect).

Target asm: `cursor=r6, mode=r7, i=r8`. Required source decl order:

```c
SlotEntry *cursor;
int mode;
int i;
```

Reordering to `int mode; SlotEntry *cursor; int i;` flipped to `mode=r6, cursor=r7, i=r8` and broke SHA-1.

Mixing types (pointer + int + int) in the decl list does not change the rule — first-declared identifier gets the lowest GPR number in the allocation pool.

### Diff symptom (GPR variant)

Identical instruction count and addressing, but register numbers in `r` fields differ by a consistent offset across the affected variables. Reorder the decl list to match the target's register order.
