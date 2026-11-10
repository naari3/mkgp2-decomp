# leversweep results

109 near misses swept by `tools/leversweep.py batch` (diagnosis-triggered levers).
"fired" = both triggers matched, "improved" = fewer diff lines than the current source, "matched" = objdiff 100% (0 diff lines alone is not enough).

| lever | rule | landed by | fired (fns) | variants | improved | matched |
| --- | --- | --- | --- | --- | --- | --- |
| restrict-input-ptrs | restrict-input-ptrs | fa1d62e (§30) | 0 | 0 | 0 | 0 |
| arg-order-prototype | arg-order-prototype | 28b9fb6 (§37) | 0 | 0 | 0 | 0 |
| index-for-walk | addr-on-demand | 025713e | 0 | 0 | 0 | 0 |
| inline-to-named-locals | inline-boundary | a4d82de, 963b6e1 | 0 | 0 | 0 | 0 |
| mul-fuse | inline-mul-blocks-fmadd | d38113c (§39) | 0 | 0 | 0 | 0 |
| local-array-init | local-array-init | 5eca6fc | 0 | 0 | 0 | 0 |
| single-expr | single-expr-local | 0b362350 | 0 | 0 | 0 | 0 |
| try-scope-inside-if | try-scope-inside-if | 11f056f | 0 | 0 | 0 | 0 |
| nonconst-zero-arm | nonconst-zero-arm | gave_up clFlowCourse_Dtor | 0 | 0 | 0 | 0 |
| dead-def-split | dead-def-split | 8d77ba2 | 0 | 0 | 0 | 0 |
| block-local-counter | later-loops-block-local-counter | b879fcb | 0 | 0 | 0 | 0 |
| chain-assign-split | chain-assign-split | f96d5c26 | 0 | 0 | 0 | 0 |
| void-to-int | nonvoid-no-return | b61e1de | 0 | 0 | 0 | 0 |
| narrow-cast-toggle | dead-truncation-reschedules-block | dd11664 | 0 | 0 | 0 | 0 |
| sum3-regroup | three-term-sum-grouping | 3bf2c6a | 21 | 392 | 1 | 0 |

## Improvements

| fn | TU | % | base lines | best lines | objdiff % | lever | variant |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `SpecialFace_RaycastSegment` | game/SpecialFaceMesh_Raycast | 96.16 | 243 | 241 | 96.08 -> 92.35 | sum3-regroup | sum 0 as `(az + ay) + ax` |

## Levers not automated here

| lever | rule | class | landed by | why |
| --- | --- | --- | --- | --- |
| inline-asm r2/r13 fixed offsets -> symbol refs | - | auto (nothing left) | 71b5ffd4 | grep: no game TU has a numeric r2/r13 displacement in inline asm any more (only TRK, already matching) |
| split the pool at `addi rX, anchor, N` | anchor-addi-object-boundary | semi (detect only) | §40 | `leversweep.py detect` lists the functions and offsets; the split edits the pool source and symbols.txt |
| rolled-loop + opt_unroll_instr_count | loop-unroll-budget | semi | 833c85a | pragma half is automatic (pragmasweep --set extended sweeps opt_unroll_instr_count 8/16/32); rolling a hand-unrolled loop back needs the loop count and the induction step, which differ per site |
| base vtable store in the ctor body | base-init-in-body | semi | §36 | needs the base class vtable symbol and a ctor that has address locals; trigger (prologue lis/addi swap) is cheap but there were 2 C++ ctors near misses with that shape, done by hand |
| avoid IRO CSE temps | - | semi | 3cc4b0e | the rewrite (read through a cast pointer / hoist before) is a fakematch-flavoured choice per site; shapesweep hoist covers the hoist half, the trigger needs a mwtrace TEMPNEW trace |
| pool-owner TU merges | merge-pool-owner | semi | 7653d99 | pool_audit.py finds them; the merge edits splits.txt/configure.py/symbols and has to respect claims |
| TU merges (correct structure) | merge-pool-owner | manual | 5d5f466b | tu_audit.py proposes; each merge is a splits/configure/extab job checked against main.dol |
