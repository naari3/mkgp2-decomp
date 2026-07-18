# CW 1.3.2: global-array base address CSE web ownership (2026-07-19, TransparentDraw)

Context: TransparentDraw_SortAndDispatch (0x80065C9C) walks a 32-slot global table
(lbl_805987E0, .bss) in 5 loops; target holds the table base in r31 for the whole fn
with per-loop `mr rX, r31` walker inits, and the addi lands IN r31.

Observation (probed):
- With a user variable `TDrawSlot *base = lbl_805987E0;` + `base[i]` guards, CW
  copy-props the init into the first loop preheader and the coalescer gives the
  lis/addi to the first loop's walker web; `base` gets a `mr r31, rX` copy => +1 insn
  vs target and register mirror. No source-order / decl-order variant flips the
  ownership.
- Spelling ALL loop guards with the global name (`lbl_805987E0[i].owner` etc., no user
  base var) makes CW create a function-scope CSE web for the address that OWNS the
  addi (r31), with each loop's strength-reduced walker initialized `mr rX, r31`
  => byte-identical.
- Hit-block (cold, break path) accesses spelled `lbl_805987E0[i].entry` still
  rematerialize lis/addi + mulli; they do NOT reuse the CSE web. Guard-walker and
  cold-body spelling can both be the global name.
- Inner-loop reads of the OUTER slot (`a->dist` compared inside an inner j-loop) must
  go through a pointer declared inside the outer body: `TDrawSlot *a =
  &lbl_805987E0[k];` => SR walker with direct field offsets (0x8(r5)). Spelling
  `base[k].dist` inside the inner loop instead makes LICM hoist per-field address
  temps (`addi r5, r7, 0x8` / `addi r6, r7, 0x4`) that the target does not have.
- ctr-loops (no calls) emit secondary increments pointer-first (`addi ptr, 0x14; addi
  idx, 1`); counter loops (calls inside, or ctr taken by an inner loop) emit
  idx-first. With global-index spelling both fall out automatically.

Also in this TU (TransparentDraw_DestroyEntry 0x80065B74, asm_fn park): 63/63
instruction content reachable in C (HSD ref_DEC shape:
`noref = rc == 0xFFFF; if (noref) { expired = noref; } else { obj->refcount = rc - 1;
noref = rc == 0; expired = noref; }` with u8 noref + int expired gives the extrwi.
materialization, beq/b branch-over-branch, extrwi else-arm bool and cmpwi join), but
the 3-web callee rotation (target self=r31/obj=r30/flag=r29) is source-closed: ~16
probes (static helpers, e-local, decl order, register kw, int/short/3rd param,
#pragma exceptions on/off and TU-level -Cpp_exceptions, -lang=c++) all give
flag=r31/self=r30/obj=r29. Same park class as CarObject_ProcessWarpAndDash
(cw132-allocator-phase2f-research.md). Note: `mr r31, r4; mr. r30, r3` (flag-first)
IS the natural CW output for `(this, short flag)` dtors that call before testing flag
- dtor_80064CD4 and clCGameDemo_Dtor targets have exactly that pattern;
TransparentDraw's target is the unusual one.
