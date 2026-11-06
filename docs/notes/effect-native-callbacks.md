# Native Effect callback observations

## 2026-10-23 — ordinary-tooling OrbitSpark trial

OrbitSpark at `800C55C0..800C57E4`: separating the double-returning `fn_8027E9E8` result into a float local removes spurious f31 preservation and gives the exact 548-byte text size, frame40, automatic EH8 and index12. A compound pulse expression and a separately named pulse produce identical 99.70803% codegen; half/amplitude FPR1/2 and multiply operand identities remain different. Three structural approaches were exhausted, so retain this complete draft as NonMatching, with zero genuine matched gain. This is an observed residual, not proof that every source expression is closed. No ASM/manual EH or foreign-data ownership workaround was used.

Main independently rebuilt the unchanged native body with actual source input (fallback absent): CHECK exited1 and SHA-1 was `c99d5ad2906e0ca02b35620505c1db9f1c95a061`. Direct objdiff confirmed text99.70803%, EH/index100%. Restoring the NonMatching declaration and running `all_source`, `progress`, `report.json`, and `ok` foreground exited0 with target SHA-1 `ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65`; actual final input is the target fallback. No genuine C gain is claimed.

This was the ordinary-tool arm of a disjoint two-function experiment. Tool output volume and wall time are not directly causal evidence because the other arm handles a different function.

## c15_u13_20261106
Source: Codex worker c15_u13_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 548 B.

c15_u13: OrbitSpark 800C55C0 singleton promoted from 99.70803 to native100. Literal pulse constants first resolve half/amplitude f1/f2 homes (99.85401). Writing pulse=((1.0f+wave)/2.0f)/2.0f+0.5f instead of multiply-by-half resolves two remaining operand orientations through reciprocal lowering; emitted sequence is target fmuls f0,f0,f1 and fmadds f0,f0,f1,f1. Existing sdata2 postprocess maps literals to lbl_806D54B8/C0 with no retained data added. Text548/extab8/index12 all100, source-linked final symbol800C55C0/548 and full DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 verified.
