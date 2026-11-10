# leversweep results

106 near misses swept by `tools/leversweep.py batch` (diagnosis-triggered levers).
"fired" = both triggers matched, "improved" = fewer diff lines than the current source, "matched" = objdiff 100% (0 diff lines alone is not enough).

| lever | rule | landed by | fired (fns) | variants | improved | matched |
| --- | --- | --- | --- | --- | --- | --- |
| restrict-input-ptrs | restrict-input-ptrs | fa1d62e (§30) | 0 | 0 | 0 | 0 |
| arg-order-prototype | arg-order-prototype | 28b9fb6 (§37) | 0 | 0 | 0 | 0 |
| index-for-walk | addr-on-demand | 025713e | 0 | 0 | 0 | 0 |
| inline-to-named-locals | inline-boundary | a4d82de, 963b6e1 | 54 | 6349 | 11 | 0 |
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
| sum3-regroup | three-term-sum-grouping | 3bf2c6a | 0 | 0 | 0 | 0 |

## Improvements

| fn | TU | % | base lines | best lines | objdiff % | lever | variant |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `acBind` | triforce/acsocket_nm5 | 97.65 | 13 | 11 | 97.65 -> 96.12 | inline-to-named-locals | [ClearBindBuffer] GetSocketBuffer@52 locals front |
| `fn_801B4548` | game/sprite/fn_801A1798 | 99.93 | 36 | 29 | 99.92 -> 99.86 | inline-to-named-locals | FindNearestVoiceKart801B_p47@1997 subst front order best_p47,distance_p47_,e_p47,nearest_p47_,i_p47_ |
| `KartPhysics_ApplyCollisionForce` | game/KartPhysics_ApplyCollisionForce | 98.64 | 54 | 46 | 98.35 -> 97.61 | inline-to-named-locals | apply_push@1498 subst front order timer,scale_,dz_,dy_,dx_ |
| `fn_8022ACE4` | game/EnemyFace | 98.61 | 60 | 56 | 98.49 -> 98.48 | inline-to-named-locals | TirePosition@1788 locals front order z,y,x |
| `Object_DriveAnimAndSkin` | game/Object_DriveAnimAndSkin | 99.56 | 66 | 58 | 99.5 -> 99.13 | inline-to-named-locals | RequestDrive@262 locals front |
| `clNormal3D_Exec` | game/clNormal3D_Exec | 99.20 | 130 | 94 | 99.14 -> 99.32 | inline-to-named-locals | AnimateExec@1146 deep front node,i,cursor | site  |
| `fn_8021C778` | game/anon_8021BC44_nm1 | 99.71 | 108 | 104 | 99.7 -> 99.68 | inline-to-named-locals | StripNameSpaces@2823 deep front i,buf_ | site  |
| `ranking_display` | game/ranking_display | 96.10 | 130 | 128 | 96.09 -> 96.09 | inline-to-named-locals | SetTrack@1198 subst front |
| `fn_80234840` | game/FlowCardCheck_nm2 | 95.97 | 426 | 417 | 95.97 -> 95.79 | inline-to-named-locals | SetCharaGroupForPlayer@2701 subst front |
| `fn_8022BFA8` | game/EnmyFaceEffect | 89.26 | 964 | 944 | 88.11 -> 88.16 | inline-to-named-locals | FillFaceUV@3877 subst front |
| `fn_8018B31C` | game/bitread/fn_8018B31C | 94.41 | 1440 | 1432 | 94.34 -> 94.36 | inline-to-named-locals | WriteBits@2100 subst front |

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
